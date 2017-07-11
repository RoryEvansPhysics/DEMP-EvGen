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

void MakeTree(){
  
  //Convert data from txt file to a root tree.

  string file = "aut_clas.txt";
  ifstream file1;

  file1.open(file.c_str());
  
  if (! file1){
    cout << "File not Found" << endl;
    break;
  }

  //Skip to Data
  string line;
  int i;
  for (i = 0; i < 18; i++) {
    getline(file1, line);
  }

  //Create a tree
  TFile f("asym.root","recreate");
  TTree t1("t1", "Asymmetry Data");
  
  //Initialize variables for each data column
  Double_t w, q2, tp, t, asy, asysfi, asy2fi, asyfpfs, asy3f;

  //Create branches for each variable
  t1.Branch("w", &w, "w/D");
  t1.Branch("q2", &q2, "q2/D");
  t1.Branch("tp", &tp, "tp/D");
  t1.Branch("t",&t,"t/D");
  t1.Branch("asy",&asy,"asy/D");
  t1.Branch("asysfi",&asysfi,"asysfi/D");
  t1.Branch("asy2fi",&asy2fi,"asy2fi/D");
  t1.Branch("asyfpfs",&asyfpfs,"asyfpfs/D");
  t1.Branch("asy3f",&asy3f,"asy3f/D");

  //Fill the tree
  while (!file1.eof()) {
    file1 >> w >> q2 >> tp >> t >> asy >> asysfi >> asy2fi 
	  >> asyfpfs >> asy3f;
    cout << w << "\t" << q2 << "\t" << tp <<"\t";
    cout << t << "\t" << asy << "\t" << asysfi << "\t";
    cout << asy2fi << "\t" << asyfpfs << "\t" << asy3f;
    cout << endl;
    t1.Fill();
  }
  
  t1.Write();
  
}


void DrawFit(){
  
  //Draw all graphs as a function of t' and 
  //optionally generate parameter file.

  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.1);

  TFile *f1 = new TFile("asym.root");
  TTree *t1 = (TTree*)f1->Get("t1");

  bool makePars = true;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  //Retrieve an array of all w and q2 values.

  t1->Draw("w:q2","","goff");
  w1 = t1->GetV1();
  q2_1 = t1->GetV2();
  cout << w1[0] << "\t" << q2_1[0] << endl;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //Build vectors with only unique values of w and q2.

  vector<double> exclude;
  // exclude.push_back(4.335);
  exclude.push_back(4.355);
  exclude.push_back(4.740);
  // exclude.push_back(5.138);
  exclude.push_back(5.426);
  // exclude.push_back(5.948);
  // exclude.push_back(6.393);
  // exclude.push_back(6.894);

  vector<double> w2, q2_2;
  //cout << "1" << endl;

  vector<double>::iterator it;
  //cout << "2" << endl;
  

  double w = w1[0];
  double q2 = q2_1[0];

  int i = 0;
  
  while(w != 0){

    it = find(w2.begin(), w2.end(), w);
    if (it == w2.end()){
      w2.push_back(w);
      q2_2.push_back(q2);
      cout << w << "\t" << q2 << endl;
    }
    i++;
    
    w = w1[i];
    q2 = q2_1[i];


  }


  

  cout<<q2_2.size()<<endl;

  sort(q2_2.begin(), q2_2.end());
  sort(exclude.begin(), exclude.end());

  //q2_2.erase(remove(q2_2.begin(),q2_2.end(), 2), q2_2.end());

  vector<double>::iterator endRange;
  endRange = set_difference(q2_2.begin(), q2_2.end(), 
		 exclude.begin(), exclude.end(),
		 q2_2.begin());
  q2_2.erase(endRange, q2_2.end());
  

  int Nw = w2.size();
  int Nq = q2_2.size();
  int N = Nq;
  cout <<N <<endl;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  TCanvas *c1 = new TCanvas("c1", "Main Canvas");
  c1->Divide(3,2);

  TString cut;
  int n;

  TMultiGraph *mgasy = new TMultiGraph("mgasy","A_{UT}^{sin(#phi-#phi_{s})}");
  TMultiGraph *mgasysfi = new TMultiGraph("mgasysfi", "A_{UT}^{sin(#phi_{s})}");
  TMultiGraph *mgasy2fi = new TMultiGraph("mgasy2fi", "A_{UT}^{sin(2#phi-#phi_{s})}");
  TMultiGraph *mgasyfpfs = new TMultiGraph("mgasyfpfs", "A_{UT}^{sin(#phi+#phi_{s})}");
  TMultiGraph *mgasy3f = new TMultiGraph("mgasy3f", "A_{UT}^{sin(3#phi-#phi_{s})}");

  TLegend *leg = new TLegend(0,0,1,1);
  leg->SetHeader("Value of Q^{2} (GeV^{2}) and W (GeV)");

  //Vectors for fit parameters
  vector<Double_t> asyp0,asyp1,asyp2,asyp3,asyp4;
  vector<Double_t> asysfip0,asysfip1,asysfip2,asysfip3,asysfip4;
  vector<Double_t> asy2fip0,asy2fip1,asy2fip2,asy2fip3,asy2fip4;
  vector<Double_t> asyfpfsp0,asyfpfsp1,asyfpfsp2,asyfpfsp3,asyfpfsp4;
  vector<Double_t> asy3fp0,asy3fp1,asy3fp2,asy3fp3,asy3fp4;

  vector<Double_t> asychi, asysfichi, asy2fichi, asyfpfschi, asy3fchi;

  TF1 *fitting = new TF1("fitting","[0]*exp([1]*x)+(-[2]-[0])*exp([3]*x)+[2]");
  //fitting->SetParLimits(1,-100,-0.001);
  //fitting->SetParLimits(3,-100,-0.001);

  TF1 *fitting2 = new TF1("fitting2","[0]*exp([1]*x)+[2]");

  for (i = 0; i < N; i++) {
    /*
    w = w2[i];
    cout << w << endl;
    cut = "w==";
    stringstream stream;
    stream << fixed << setprecision(3) << w;
    cut += stream.str();
    cout << cut << endl;
    */
    
    q2 = q2_2[i];
    cut = "q2==";
    stringstream stream;
    stream << fixed << setprecision(3) << q2;
    cut += stream.str();
    cout << cut << endl;
    //Associated w value
    t1->Draw("w",cut,"goff");
    w = t1->GetV1()[0];
    
    n = t1->Draw("tp:asy",cut,"goff");
    //Put data in  vectors and add fake points
    vector<Double_t> faketp, fakeasy;
    double *x = t1->GetV1();
    double *y = t1->GetV2();
    for (int j = 0; j < n; j++) {
      faketp.push_back(x[j]);
      fakeasy.push_back(y[j]);
    }
    // for (j = 0; j < 5; j++) {
    //   faketp.push_back(0.1*j+0.6);
    //   fakeasy.push_back(fakeasy[n-1]);
    // }
    TGraph *g = new TGraph(n, &faketp[0],&fakeasy[0]);
    g->SetLineColor(kOrange-9 + i);
    g->SetLineWidth(2);
    g->SetMarkerColor(kOrange-9+i);
    g->SetMarkerStyle(20+i);
    mgasy->Add(g);
    fitting -> FixParameter(2,fakeasy[n-1]);
    g->Fit("fitting","MQ");
    TF1 *f = g->GetFunction("fitting");
    f->SetLineColor(kOrange-9 + i);

    asyp0.push_back(f->GetParameter(0));
    asyp1.push_back(f->GetParameter(1));
    asyp2.push_back(f->GetParameter(2));
    asyp3.push_back(f->GetParameter(3));
    asychi.push_back(f->GetChisquare()/f->GetNDF());

    g->SetFillColor(0);
    TString legentry = "Q^{2}=";
    stringstream stream;
    stream << fixed << setprecision(3) << q2;
    legentry += stream.str();
    legentry += ", W=";
    stringstream stream;
    stream << fixed << setprecision(3) << w;
    legentry += stream.str();
    leg->AddEntry(g, legentry);

    n = t1->Draw("tp:asysfi",cut,"goff");
    //Put data in  vectors and add fake points
    vector<Double_t> faketp, fakeasy;
    double *x = t1->GetV1();
    double *y = t1->GetV2();
    for (int j = 0; j < n; j++) {
      faketp.push_back(x[j]);
      fakeasy.push_back(y[j]);
    }
    // for (j = 0; j < 5; j++) {
    //   faketp.push_back(0.1*j+0.6);
    //   fakeasy.push_back(fakeasy[n-1]);
    // }
    TGraph *g = new TGraph(n, &faketp[0],&fakeasy[0]);
    g->SetLineColor(kOrange-9 + i);
    g->SetLineWidth(2);
    g->SetMarkerColor(kOrange-9+i);
    g->SetMarkerStyle(20+i);
    mgasysfi->Add(g);
    fitting2 -> FixParameter(2,fakeasy[n-1]);
    g->Fit("fitting2","MQ");
    TF1 *f = g->GetFunction("fitting2");
    f->SetLineColor(kOrange-9 + i);

    asysfip0.push_back(f->GetParameter(0));
    asysfip1.push_back(f->GetParameter(1));
    asysfip2.push_back(f->GetParameter(2));
    asysfichi.push_back(f->GetChisquare()/f->GetNDF());
  
    n = t1->Draw("tp:asy2fi",cut,"goff");
    //Put data in  vectors and add fake points
    vector<Double_t> faketp, fakeasy;
    double *x = t1->GetV1();
    double *y = t1->GetV2();
    for (int j = 0; j < n; j++) {
      faketp.push_back(x[j]);
      fakeasy.push_back(y[j]);
    }
    // for (j = 0; j < 5; j++) {
    //   faketp.push_back(0.1*j+0.6);
    //   fakeasy.push_back(fakeasy[n-1]);
    // }
    TGraph *g = new TGraph(n, &faketp[0],&fakeasy[0]);
    g->SetLineColor(kOrange-9 + i);
    g->SetLineWidth(2);
    g->SetMarkerColor(kOrange-9+i);
    g->SetMarkerStyle(20+i);
    mgasy2fi->Add(g);
    fitting2 -> FixParameter(2,fakeasy[n-1]);
    g->Fit("fitting2","MQ");
    TF1 *f = g->GetFunction("fitting2");
    f->SetLineColor(kOrange-9 + i);
    asy2fip0.push_back(f->GetParameter(0));
    asy2fip1.push_back(f->GetParameter(1));
    asy2fip2.push_back(f->GetParameter(2));
    asy2fip3.push_back(f->GetParameter(3));
    asy2fichi.push_back(f->GetChisquare()/f->GetNDF());    

    n = t1->Draw("tp:asyfpfs",cut,"goff");
    //Put data in  vectors and add fake points
    vector<Double_t> faketp, fakeasy;
    double *x = t1->GetV1();
    double *y = t1->GetV2();
    for (int j = 0; j < n; j++) {
      faketp.push_back(x[j]);
      fakeasy.push_back(y[j]);
    }
    // for (j = 0; j < 5; j++) {
    //   faketp.push_back(0.1*j+0.6);
    //   fakeasy.push_back(fakeasy[n-1]);
    // }
    TGraph *g = new TGraph(n, &faketp[0],&fakeasy[0]);
    g->SetLineColor(kOrange-9 + i);
    g->SetLineWidth(2);
    g->SetMarkerColor(kOrange-9+i);
    g->SetMarkerStyle(20+i);
    mgasyfpfs->Add(g);
    fitting2 -> FixParameter(2,fakeasy[n-1]);
    g->Fit("fitting2","MQ");
    TF1 *f = g->GetFunction("fitting2");
    f->SetLineColor(kOrange-9 + i);
    asyfpfsp0.push_back(f->GetParameter(0));
    asyfpfsp1.push_back(f->GetParameter(1));
    asyfpfsp2.push_back(f->GetParameter(2));
    asyfpfschi.push_back(f->GetChisquare()/f->GetNDF());

    n = t1->Draw("tp:asy3f",cut,"goff");
    //Put data in  vectors and add fake points
    vector<Double_t> faketp, fakeasy;
    double *x = t1->GetV1();
    double *y = t1->GetV2();
    for (int j = 0; j < n; j++) {
      faketp.push_back(x[j]);
      fakeasy.push_back(y[j]);
    }
    // for (j = 0; j < 5; j++) {
    //   faketp.push_back(0.1*j+0.6);
    //   fakeasy.push_back(fakeasy[n-1]);
    // }
    TGraph *g = new TGraph(n, &faketp[0],&fakeasy[0]);
    g->SetLineColor(kOrange-9 + i);
    g->SetLineWidth(2);
    g->SetMarkerColor(kOrange-9+i);
    g->SetMarkerStyle(20+i);
    mgasy3f->Add(g);
    fitting2 -> FixParameter(2,fakeasy[n-1]);
    g->Fit("fitting2","MQ");
    TF1 *f = g->GetFunction("fitting2");
    f->SetLineColor(kOrange-9 + i);
    asy3fp0.push_back(f->GetParameter(0));
    asy3fp1.push_back(f->GetParameter(1));
    asy3fp2.push_back(f->GetParameter(2));
    asy3fchi.push_back(f->GetChisquare()/f->GetNDF());
  }

  TString style("AP");
  
  c1->cd(1);
  mgasy->Draw(style);
  mgasy->GetXaxis()->SetTitle("t' (GeV^{2})");
  //mgasy->GetYaxis()->SetTitle("A_{UT}^{sin(#phi-#phi_{s})}");
  cout << "Check 1" <<endl;

  c1->cd(2);
  mgasysfi->Draw(style);
  mgasysfi->GetXaxis()->SetTitle("t' (GeV^{2})");
  //mgasysfi->GetYaxis()->SetTitle("A_{UT}^{sin(#phi_{s})}");
  cout << "Check 2" <<endl;

  c1->cd(3);
  mgasy2fi->Draw(style);
  mgasy2fi->GetXaxis()->SetTitle("t' (GeV^{2})");
  //mgasy2fi->GetYaxis()->SetTitle("A_{UT}^{sin(2#phi-#phi_{s})}");
  cout << "Check 3" <<endl;

  c1->cd(4);
  mgasyfpfs->Draw(style);
  mgasyfpfs->GetXaxis()->SetTitle("t' (GeV^{2})");
  //mgasyfpfs->GetYaxis()->SetTitle("A_{UT}^{sin(#phi+#phi_{s})}");
  cout << "Check 4" <<endl;

  c1->cd(5);
  mgasy3f->Draw(style);
  mgasy3f->GetXaxis()->SetTitle("t' (GeV^{2})");
  //mgasy3f->GetYaxis()->SetTitle("A_{UT}^{sin(3#phi-#phi_{s})}");
  cout << "Check 5" <<endl;

  c1->cd(6);
  leg->Draw(style);

  cout << "Check 6" <<endl;

  if (makePars){

      int width = 14;
      ofstream output, asyout, asysfiout, asy2fiout,asyfpfsout, asy3fout;
      output.open("Parameters.txt", fstream::out);
      asyout.open("asyout.txt",fstream::out);
      asysfiout.open("asysfiout.txt",fstream::out);
      asy2fiout.open("asy2fiout.txt",fstream::out);
      asyfpfsout.open("asyfpfsout.txt",fstream::out);
      asy3fout.open("asy3fout.txt",fstream::out);


      output << setw(width)<< "q2"<<setw(width)<<"asyP0"<<setw(width)
	     <<"asyP1"<<setw(width)<<"asyP2"<<setw(width)<<"asyP3"
	     <<setw(width)<<"chi2/N"<<endl;

      N = asyp0.size();

      for (i = 0; i < N; i++) {
	output<<setw(width)<<q2_2[i]<<setw(width);
	output<<setw(width)<<asyp0[i]<<setw(width);
	output<<setw(width)<<asyp1[i]<<setw(width);
	output<<setw(width)<<asyp2[i]<<setw(width);
	output<<setw(width)<<asyp3[i]<<setw(width);
	output<<setw(width)<<asychi[i]<<setw(width);
	output << endl;

	asyout<<setw(width)<<q2_2[i]<<setw(width);
	asyout<<setw(width)<<asyp0[i]<<setw(width);
	asyout<<setw(width)<<asyp1[i]<<setw(width);
	asyout<<setw(width)<<asyp2[i]<<setw(width);
	asyout<<setw(width)<<asyp3[i]<<setw(width);
	asyout << endl;
      }

      output<<setw(width)<<endl<<endl;
      output<<setw(width) << "q2"<<setw(width)<<"asysfiP0"<<setw(width)
	    <<"asysfiP1"<<setw(width)<<"asysfiP2"<<setw(width)
	    <<"chi2/N"<< endl;
      N = asysfip0.size();
      for (i = 0; i < N; i++) {
	output<<setw(width) << q2_2[i]<< setw(width);
	output<<setw(width)<<asysfip0[i]<<setw(width);
	output<<setw(width)<<asysfip1[i]<<setw(width);
	output<<setw(width)<<asysfip2[i]<<setw(width);
	output<<setw(width)<<asysfichi[i]<<setw(width);
	output << endl;

	asysfiout<<setw(width) << q2_2[i]<< setw(width);
	asysfiout<<setw(width)<<asysfip0[i]<<setw(width);
	asysfiout<<setw(width)<<asysfip1[i]<<setw(width);
	asysfiout<<setw(width)<<asysfip2[i]<<setw(width);
	asysfiout << endl;
      }

      output<<setw(width)<<endl<<endl;
      output<<setw(width) << "q2"<<setw(width)<<"asy2fiP0"<<setw(width)
	    <<"asy2fiP1"<<setw(width)<<"asy2fiP2"<<setw(width)
	    <<"chi2/N"<< endl;
      N = asy2fip0.size();
      for (i = 0; i < N; i++) {
	output<<setw(width)<<q2_2[i]<<setw(width);
	output<<setw(width)<<asy2fip0[i]<<setw(width);
	output<<setw(width)<<asy2fip1[i]<<setw(width);
	output<<setw(width)<<asy2fip2[i]<<setw(width);
	output<<setw(width)<<asy2fichi[i]<<setw(width);
	output << endl;

	asy2fiout<<setw(width)<<q2_2[i]<<setw(width);
	asy2fiout<<setw(width)<<asy2fip0[i]<<setw(width);
	asy2fiout<<setw(width)<<asy2fip1[i]<<setw(width);
	asy2fiout<<setw(width)<<asy2fip2[i]<<setw(width);
	asy2fiout << endl;
      }

      output<<setw(width)<<endl<<endl;
      output<<setw(width) << "q2"<<setw(width)<<"asyfpfsP0"<<setw(width)
	    <<"asyfpfsP1"<<setw(width)<<"asyfpfsP2"<<setw(width)
	    <<"chi2/N"<< endl;
      N = asyfpfsp0.size();
      for (i = 0; i < N; i++) {
	output<<setw(width)<<q2_2[i]<<setw(width);
	output<<setw(width)<<asyfpfsp0[i]<<setw(width);
	output<<setw(width)<<asyfpfsp1[i]<<setw(width);
	output<<setw(width)<<asyfpfsp2[i]<<setw(width);
	output<<setw(width)<<asyfpfschi[i]<<setw(width);
	output << endl;

	asyfpfsout<<setw(width)<<q2_2[i]<<setw(width);
	asyfpfsout<<setw(width)<<asyfpfsp0[i]<<setw(width);
	asyfpfsout<<setw(width)<<asyfpfsp1[i]<<setw(width);
	asyfpfsout<<setw(width)<<asyfpfsp2[i]<<setw(width);
	asyfpfsout << endl;
      }

      output<<setw(width)<<endl<<endl;
      output<<setw(width) << "q2"<<setw(width)<<"asy3fP0"<<setw(width)
	    <<"asy3fP1"<<setw(width)<<"asy3fP2"<<setw(width)
	    <<"chi2/N"<< endl;
      N = asy3fp0.size();
      for (i = 0; i < N; i++) {
	output<<setw(width)<<q2_2[i]<<setw(width);
	output<<setw(width)<<asy3fp0[i]<<setw(width);
	output<<setw(width)<<asy3fp1[i]<<setw(width);
	output<<setw(width)<<asy3fp2[i]<<setw(width);
	output<<setw(width)<<asy3fchi[i]<<setw(width);
	output << endl;

	asy3fout<<setw(width)<<q2_2[i]<<setw(width);
	asy3fout<<setw(width)<<asy3fp0[i]<<setw(width);
	asy3fout<<setw(width)<<asy3fp1[i]<<setw(width);
	asy3fout<<setw(width)<<asy3fp2[i]<<setw(width);
	asy3fout << endl;
      }
  }
}
