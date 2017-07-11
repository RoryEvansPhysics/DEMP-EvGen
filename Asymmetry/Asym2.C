#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "TGraph.h"
#include "TGraph2D.h"
#include "TMath.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Rtypes.h"

using namespace std;
using namespace TMath;

Double_t Extrap(Double_t x, Double_t x1, Double_t x2, Double_t y1, Double_t y2){

  if ((x1==x2)) {
    //cout << "Equal x's Passed" << endl;
    return y2;
  }
  else if ((y1==y2)) {
    //cout << "Equal y's Passed" << endl;
    return y2;
  }

  else {
    Double_t m = (y1-y2)/(x1-x2);
    Double_t b = y1-(m*x1);

    Double_t y = (m*x)+b;
    
    return y;
    
  }
}


Double_t Asymmetry(Double_t q, Double_t tp, string file){
  
  ifstream f;
  f.open(file.c_str());

  vector<Double_t> q2, p0, p1, p2;
  Double_t q2x,p0x,p1x,p2x;

  while(!f.eof()){
    f >> q2x >> p0x >> p1x >> p2x;
    if (f.eof()) break;
    //cout << q2x <<"\t" << p2x << endl;
    q2.push_back(q2x);
    p0.push_back(p0x);
    p1.push_back(p1x);
    p2.push_back(p2x);

  }
  //cout << "Done" << endl;

  int N = q2.size();
  //cout << N << endl;
  
  Double_t diff = 100.0;
  int n;
  
  for (int i = 0; i < N; i++) {
    //cout << "Hello?" << endl
    if (fabs(q2[i]-q)<diff) {
      diff = fabs(q2[i]-q);
      //cout << diff << endl;
      n = i;
    }
  }

  //cout << "q2 = " << q2[n] << endl;

  Double_t A1 = p0[n]*Exp(p1[n]*tp)+p2[n];

  int n2 = n;
  if (q < q2[n]) n2 = n-1;
  if (q > q2[n]) n2 = n+1;
  
  if (n==n2) return A1;

  if (n==0) n2 = n+1;
  if (n==N-1) n2 = n-1;

  //cout << q2[n] << "\t" << q2[n2] << "\t" << q << endl;
  //cout << n << "\t" << n2 << endl;

  double A2 = p0[n2]*Exp(p1[n2]*tp)+p2[n2];

  double A;
  A = Extrap(q,q2[n],q2[n2],A1,A2);

  //cout << A1 << "\t" << A2 << "\t" << A << endl;

  return A;
  
}

Double_t asy(Double_t q, Double_t tp){
  
  string file = "asyout.txt";

  ifstream f;
  f.open(file.c_str());

  vector<Double_t> q2, p0, p1, p2, p3;
  Double_t q2x,p0x,p1x,p2x, p3x;

  while(!f.eof()){
    f >> q2x >> p0x >> p1x >> p2x >> p3x;
    if (f.eof()) break;
    //cout << q2x <<"\t" << p0x << endl;
    q2.push_back(q2x);
    p0.push_back(p0x);
    p1.push_back(p1x);
    p2.push_back(p2x);
    p3.push_back(p3x);
  }
  //cout << "Done" << endl;

  int N = q2.size();
  //cout << N << endl;
  
  Double_t diff = 100.0;
  int n;
  
  for (int i = 0; i < N; i++) {
    //cout << "Hello?" << endl
    if (fabs(q2[i]-q)<diff) {
      diff = fabs(q2[i]-q);
      //cout << diff << endl;
      n = i;
    }
  }

  //cout << "q2 = " << q2[n] << endl;

  Double_t A1 = p0[n]*Exp(p1[n]*tp)+p2[n]-(p0[n]+p2[n])*Exp(p3[n]*tp);

  int n2 = n;
  if (q < q2[n]) n2 = n-1;
  if (q > q2[n]) n2 = n+1;
  
  if (n==n2) return A1;

  if (n==0) n2 = n+1;
  if (n==N-1) n2 = n-1;

  //cout << "q2 = " << q2[n] << endl;

  double A2 = p0[n2]*Exp(p1[n2]*tp)+p2[n2]-(p0[n2]+p2[n2])*Exp(p3[n2]*tp);
  double A;
  A = Extrap(q, q2[n], q2[n2], A1, A2);
  return A;
  

}



Double_t asysfi(Double_t q, Double_t tp){
  return Asymmetry(q, tp, "asysfiout.txt");
}

Double_t asy2fi(Double_t q, Double_t tp){
  return Asymmetry(q, tp, "asy2fiout.txt");
}

Double_t asyfpfs(Double_t q, Double_t tp){
  return Asymmetry(q, tp, "asyfpfsout.txt");
}

Double_t asy3f(Double_t q, Double_t tp){
  return Asymmetry(q, tp, "asy3fout.txt");
}

void test(){
  vector<double> x, y;
  double start = 0.0;
  double stop = 10;
  double xi, yi;
  for (int i = 0; i < 100; i++) {
    //cout << i << endl;
    xi = start + ((double)i*(stop-start)/100);
    //cout << xi << endl;
    yi = asy(xi, 0.00001);
    cout << yi << endl;;
    x.push_back(xi);
    y.push_back(yi);
  }
  TGraph *g1 = new TGraph(100, &x[0], &y[0]);
  g1->Draw();
}

void test2d(){
  vector<double> x, y, z;
  double x1 = 0.5, x2 = 10;
  double y1 = 0.0, y2 = 2;

  int N = 20;
  double xi, yi, zi;
  for (int i = 0; i < N; i++) {
    cout<<(double)i*100/N<<"\%"<<setw(10)<<endl;
    //cout << i << endl;
    for (int j = 0; j < N; j++) {
      //if (j%100==0) cout<<(double)j*100/N<<"\%"<<setw(10)<<"\r";
      //cout << j << endl;
      xi = x1 + (double)i*(x2-x1)/N;
      yi = y1 + (double)j*(y2-y1)/N;
      zi = asy(xi,yi);
      //cout << xi <<'\t'<<yi<<'\t'<<zi<<endl;

      x.push_back(xi);
      y.push_back(yi);
      z.push_back(zi);
    }
  }
  TGraph2D * g = new TGraph2D(N*N, &x[0],&y[0],&z[0]);
  g->Draw("TRI");
  
}
