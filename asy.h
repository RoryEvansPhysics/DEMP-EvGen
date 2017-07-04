#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "TGraph.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Rtypes.h"

using namespace std;

Double_t asyPar(Double_t q, Double_t tp, string file){
  
  ifstream f;
  f.open(file.c_str());

  vector<Double_t> q2, p0, p1, p2, p3, p4;
  Double_t q2x,p0x,p1x,p2x,p3x,p4x;

  while(!f.eof()){
    f >> q2x >> p0x >> p1x >> p2x >> p3x >> p4x;
    //    cout << q2x <<"\t" << p0x << endl;
    q2.push_back(q2x);
    p0.push_back(p0x);
    p1.push_back(p1x);
    p2.push_back(p2x);
    p3.push_back(p3x);
    p4.push_back(p4x);
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

  /* cout << "q2 = " << q2[n] << endl; */

  Double_t A = p0[n];
  A += p1[n]*tp;
  A += p2[n]*tp*tp;
  A += p3[n]*tp*tp*tp;
  A += p4[n]*tp*tp*tp*tp;

  return A;

}

Double_t asy(Double_t q, Double_t tp){
  return asyPar(q, tp, "asyout.txt");
}

Double_t asysfi(Double_t q, Double_t tp){
  return asyPar(q, tp, "asysfiout.txt");
}

Double_t asy2fi(Double_t q, Double_t tp){
  return asyPar(q, tp, "asy2fiout.txt");
}

Double_t asyfpfs(Double_t q, Double_t tp){
  return asyPar(q, tp, "asyfpfsout.txt");
}

Double_t asy3f(Double_t q, Double_t tp){
  return asyPar(q, tp, "asy3fout.txt");
}
