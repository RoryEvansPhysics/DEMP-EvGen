#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <TSystem.h>
#include <TString.h>
#include <TStyle.h>
#include <Riostream.h>
#include "TObjString.h"
#include <TNamed.h>
#include <TPRegexp.h>
#include <TObjArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TDatime.h>
#include <TError.h>
#include <TVirtualFitter.h>
#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
#include <TCut.h>
#include <TMultiGraph.h>
#include <TCutG.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TPaletteAxis.h>
#include <TRandom3.h>
//#include "SIDIS_Acceptance.h"
const double MeV2GeV=0.001;
using namespace std;

void proton() {

  const int fN = 10;

  TFile *f1[fN];
  TTree *t1[fN];
  TString s1[fN];
  
  int fCount1 = 0, fCount2 = 0, fCount3 = 0, fCount4 = 0;
  double fGenEvents = 0, fRecEvents = 0;
  Long64_t i,j;
  double fRate = 0.0;

  TH1F *hp        = new TH1F( "hp"        , "Momentum(MeV/c)",   10000, 0.0 , 10000.0  );
  TH1F *he        = new TH1F( "he"        , "Energy(MeV)",       10000, 0.0 , 10000.0  );
  TH1F *hpAcc     = new TH1F( "hpAcc"     , "Momentum(MeV/c) Acceptance",   10000, 0.0 , 10000.0  );
  TH1F *heAcc     = new TH1F( "heAcc"     , "Energy(MeV) Acceptance",       10000, 0.0 , 10000.0  );

  for ( i = 0; i < fN; i++ ) {

    s1[i] = Form("RootFiles/DEMP_Ee_11_Events_10000000_File_%i.root",i);

    f1[i] = new TFile(s1[i],"r");

    if ( !f1[i] ) { cout << "File does not exists" << endl; return; }
    t1[i] = (TTree*) f1[i]->Get("t1");

    cout << "Total events in file: " << s1[i] << setw(10) << t1[i]->GetEntries() << endl;
  
    Double_t RecoilProton_Energy_Col,RecoilProton_MomX_Col,RecoilProton_MomY_Col,RecoilProton_MomZ_Col,RecoilProton_Mom_Col; 
    Double_t RecoilProton_Phi_Col,RecoilProton_Theta_Col;

    t1[i]->SetBranchAddress("RecoilProton_Energy_Col", &RecoilProton_Energy_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomX_Col", &RecoilProton_MomX_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomY_Col", &RecoilProton_MomY_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomZ_Col", &RecoilProton_MomZ_Col );
    t1[i]->SetBranchAddress("RecoilProton_Mom_Col", &RecoilProton_Mom_Col );
    t1[i]->SetBranchAddress("RecoilProton_Theta_Col", &RecoilProton_Theta_Col );
    t1[i]->SetBranchAddress("RecoilProton_Phi_Col", &RecoilProton_Phi_Col );

    Long64_t N_entries = t1[i]->GetEntries();
    for( j = 0; j < N_entries; j++ ) {
    
      t1[i]->GetEntry(j);
      hp->Fill(RecoilProton_Mom_Col);
      he->Fill(RecoilProton_Energy_Col);

      if ( RecoilProton_Theta_Col > 6 && RecoilProton_Theta_Col < 24 ) {
	hpAcc->Fill(RecoilProton_Mom_Col);
	heAcc->Fill(RecoilProton_Energy_Col);
      }

		  
    }
  }

  TCanvas *canv=new TCanvas("canv","Sigma", 1200, 1000);  canv->cd(0);   canv->SetFillColor(17);
  canv->Divide(2,2);
  canv->cd(1);   hp->Draw();
  canv->cd(2);   he->Draw();
  canv->cd(3);   hpAcc->Draw();
  canv->cd(4);   heAcc->Draw();
  canv->Update();
  canv->SaveAs("Proton_Momentum.png");

  return;
}
