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
// #include <TTree.h>
#include "TRandom.h"
#include "TRandom2.h"
//#include "SIDIS_Acceptance.h"
const double MeV2GeV=0.001;
using namespace std;


void max () {

  TRandom2 *fRandom;
  fRandom = new TRandom2(0);
  fRandom->GetSeed();

  cout << "\n";
  const int fNFiles = 10;
  string input_filename[fNFiles];
  Long64_t i , j;

  TFile *f1[fNFiles];
  TTree* t1[fNFiles];
  TH1F *hSigma[fNFiles];

  TCanvas *canv=new TCanvas("canv","Sigma", 1800, 900);
  canv->cd(0);
  // canv->SetFillColor(17);
  canv->Divide(3,3);

  gStyle->SetOptStat(1);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.3);

  for ( i = 0; i < fNFiles; i++ ) { 

    // input_filename[i] = Form("./RootFiles/DVMP_Ee_11_Events_100000000_File_%i.root",i+1); 
    input_filename[i] = Form("./RootFiles/DEMP_Test_Ee_11_Generated_Events_100_File_%i.root",i+10000); 
    f1[i] = new TFile(input_filename[i].c_str(),"r"); 
    if ( !f1 ) { cout << "File does not exists" << endl; return; }
    t1[i] = (TTree*) f1[i]->Get("t1");

    int NRecorded;
    int NGenerated;
    Double_t ZASig_T;
    Double_t ZASig_L;
    Double_t ZASig_LT;
    Double_t ZASig_TT;

    Double_t Epsilon, Qsq, T, W, x, y, z, ZASigmaLab, ZASigma_Lab, WSq_GeV, T_GeV, W_GeV, Qsq_GeV;
    Double_t EnergyConserve, XMomConserve, YMomConserve, ZMomConserve;
    Double_t ZASigma_UU, ZASigma_UT, EventWeight;
    Double_t Neutron_Energy_Col,Neutron_MomX_Col,Neutron_MomY_Col,Neutron_MomZ_Col,Neutron_Mom_Col; 
    Double_t Neutron_Phi_Col,Neutron_Theta_Col, Coef_ZA_1, Coef_ZA_2, Coef_ZA_3, Coef_ZA_4, Coef_ZA_5, Coef_ZA_6;

    Double_t ScatElec_Energy_Col_GeV,ScatElec_MomX_Col,ScatElec_MomY_Col,ScatElec_MomZ_Col,ScatElec_Mom_Col_GeV; 
    Double_t ScatElec_Phi_Col,ScatElec_Theta_Col;

    Double_t ScatElec_Corrected_Energy_Col_GeV,ScatElec_Corrected_Mom_Col_GeV; 
    Double_t ScatElec_Corrected_MomX_Col,ScatElec_Corrected_MomY_Col,ScatElec_Corrected_MomZ_Col;
    Double_t ScatElec_Corrected_Phi_Col,ScatElec_Corrected_Theta_Col;

    Double_t Pion_Energy_Col,Pion_MomX_Col,Pion_MomY_Col,Pion_MomZ_Col, Pion_Mom_Col; 
    Double_t Pion_Phi_Col,Pion_Theta_Col;
  
    Double_t Pion_Corrected_Energy_Col_GeV, Pion_Corrected_Mom_Col_GeV, Pion_Mom_Col_GeV; 
    Double_t Pion_Corrected_MomX_Col,Pion_Corrected_MomY_Col,Pion_Corrected_MomZ_Col;
    Double_t Pion_Corrected_Phi_Col, Pion_Corrected_Theta_Col;
  
    Double_t RecoilProton_Energy_Col, RecoilProton_Energy_Col_GeV, RecoilProton_MomX_Col,RecoilProton_MomY_Col,RecoilProton_MomZ_Col,RecoilProton_Mom_Col; 
    Double_t RecoilProton_Phi_Col,RecoilProton_Theta_Col;
    Double_t RecoilProton_Corrected_Energy_Col_GeV, RecoilProton_Corrected_Mom_Col_GeV, RecoilProton_Mom_Col_GeV; 
  
    t1[i]->SetBranchAddress("Epsilon", &Epsilon );
    t1[i]->SetBranchAddress("Qsq", &Qsq );
    t1[i]->SetBranchAddress("T", &T );
    t1[i]->SetBranchAddress("W", &W );
    t1[i]->SetBranchAddress("WSq_GeV", &WSq_GeV );
    t1[i]->SetBranchAddress("T_GeV",   &T_GeV );
    t1[i]->SetBranchAddress("W_GeV",   &W_GeV );
    t1[i]->SetBranchAddress("Qsq_GeV", &Qsq_GeV );
    t1[i]->SetBranchAddress("x", &x );
    t1[i]->SetBranchAddress("y", &y );
    t1[i]->SetBranchAddress("z", &z );
    t1[i]->SetBranchAddress("ZASig_L",  &ZASig_L );
    t1[i]->SetBranchAddress("ZASig_T",  &ZASig_T );
    t1[i]->SetBranchAddress("ZASig_LT", &ZASig_LT );
    t1[i]->SetBranchAddress("ZASig_TT", &ZASig_TT );
    t1[i]->SetBranchAddress("ZASigma_Lab", &ZASigma_Lab);

    t1[i]->SetBranchAddress("Neutron_Energy_Col", &Neutron_Energy_Col );
    t1[i]->SetBranchAddress("Neutron_MomX_Col", &Neutron_MomX_Col );
    t1[i]->SetBranchAddress("Neutron_MomY_Col", &Neutron_MomY_Col );
    t1[i]->SetBranchAddress("Neutron_MomZ_Col", &Neutron_MomZ_Col );
    t1[i]->SetBranchAddress("Neutron_Mom_Col", &Neutron_Mom_Col );
    t1[i]->SetBranchAddress("Neutron_Theta_Col", &Neutron_Theta_Col );
    t1[i]->SetBranchAddress("Neutron_Phi_Col", &Neutron_Phi_Col);
  
    t1[i]->SetBranchAddress("ScatElec_Energy_Col_GeV", &ScatElec_Energy_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_MomX_Col", &ScatElec_MomX_Col );
    t1[i]->SetBranchAddress("ScatElec_MomY_Col", &ScatElec_MomY_Col );
    t1[i]->SetBranchAddress("ScatElec_MomZ_Col", &ScatElec_MomZ_Col );
    t1[i]->SetBranchAddress("ScatElec_Mom_Col_GeV", &ScatElec_Mom_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_Theta_Col", &ScatElec_Theta_Col );
    t1[i]->SetBranchAddress("ScatElec_Phi_Col", &ScatElec_Phi_Col );
    t1[i]->SetBranchAddress("ScatElec_Corrected_Energy_Col_GeV", &ScatElec_Corrected_Energy_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_Corrected_Mom_Col_GeV",    &ScatElec_Corrected_Mom_Col_GeV );
  
    t1[i]->SetBranchAddress("Pion_Energy_Col", &Pion_Energy_Col );
    t1[i]->SetBranchAddress("Pion_MomX_Col", &Pion_MomX_Col );
    t1[i]->SetBranchAddress("Pion_MomY_Col", &Pion_MomY_Col );
    t1[i]->SetBranchAddress("Pion_MomZ_Col", &Pion_MomZ_Col );
    t1[i]->SetBranchAddress("Pion_Mom_Col", &Pion_Mom_Col );
    t1[i]->SetBranchAddress("Pion_Theta_Col", &Pion_Theta_Col );
    t1[i]->SetBranchAddress("Pion_Phi_Col", &Pion_Phi_Col );
    t1[i]->SetBranchAddress("Pion_Corrected_Energy_Col_GeV", &Pion_Corrected_Energy_Col_GeV );
    t1[i]->SetBranchAddress("Pion_Corrected_Mom_Col_GeV", &Pion_Corrected_Mom_Col_GeV );
    t1[i]->SetBranchAddress("Pion_Mom_Col_GeV", &Pion_Mom_Col_GeV );

    t1[i]->SetBranchAddress("RecoilProton_Energy_Col", &RecoilProton_Energy_Col );
    t1[i]->SetBranchAddress("RecoilProton_Energy_Col_GeV", &RecoilProton_Energy_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_MomX_Col", &RecoilProton_MomX_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomY_Col", &RecoilProton_MomY_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomZ_Col", &RecoilProton_MomZ_Col );
    t1[i]->SetBranchAddress("RecoilProton_Mom_Col", &RecoilProton_Mom_Col );
    t1[i]->SetBranchAddress("RecoilProton_Theta_Col", &RecoilProton_Theta_Col );
    t1[i]->SetBranchAddress("RecoilProton_Phi_Col", &RecoilProton_Phi_Col );
    t1[i]->SetBranchAddress("RecoilProton_Corrected_Energy_Col_GeV", &RecoilProton_Corrected_Energy_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_Corrected_Mom_Col_GeV", &RecoilProton_Corrected_Mom_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_Mom_Col_GeV", &RecoilProton_Mom_Col_GeV );
    t1[i]->SetBranchAddress("EventWeight", &EventWeight);
    t1[i]->SetBranchAddress("ZASigma_UU", &ZASigma_UU);
    t1[i]->SetBranchAddress("ZASigma_UT", &ZASigma_UT);
    t1[i]->SetBranchAddress("Coef_ZA_1", &Coef_ZA_1);
    t1[i]->SetBranchAddress("Coef_ZA_2", &Coef_ZA_2);
    t1[i]->SetBranchAddress("Coef_ZA_3", &Coef_ZA_3);
    t1[i]->SetBranchAddress("Coef_ZA_4", &Coef_ZA_4);
    t1[i]->SetBranchAddress("Coef_ZA_5", &Coef_ZA_5);
    t1[i]->SetBranchAddress("Coef_ZA_6", &Coef_ZA_6);
    t1[i]->SetBranchAddress("NRecorded", &NRecorded);
    t1[i]->SetBranchAddress("NGenerated",&NGenerated);
    t1[i]->SetBranchAddress("EnergyConserve", &EnergyConserve);
    t1[i]->SetBranchAddress("XMomConserve", &XMomConserve);
    t1[i]->SetBranchAddress("YMomConserve", &YMomConserve);
    t1[i]->SetBranchAddress("ZMomConserve", &ZMomConserve);

    // int N_entries = 100000;
    Long64_t N_entries   = t1[i]->GetEntries();
    double fMaxSigma = 0;

    for( j = 0; j < N_entries; j++ ) {
    
      t1[i]->GetEntry(j);
    
      if( 
	 ( EnergyConserve              == 1   )   &&
	 ( XMomConserve                == 1   )   &&
	 ( YMomConserve                == 1   )   &&
	 ( ZMomConserve                == 1   )   &&
	 ( T_GeV                       < 1.2  )   &&
	 // ( Qsq_GeV                     > 1    )   &&
	 // ( RecoilProton_Energy_Col_GeV > 1.0  )   && 
	 ( RecoilProton_Theta_Col      > 8.0  )   && 
	 ( RecoilProton_Theta_Col      < 24.0 ) 
	  )
	{

	  if ( RecoilProton_Mom_Col_GeV < 0.2 )
	    continue;

	  if ( ZASigma_Lab > 2.0 )
	    continue;
	
	  if ( fMaxSigma < ZASigma_Lab ) {
	    fMaxSigma = ZASigma_Lab;

	  }
	}
    }
  
    // cout << setw(20) << "Event" << setw(20) << "Sigma" << setw(20) << "Sigma_max * Rand" 
    // 	 << endl;

    hSigma[i] = new TH1F( Form("hSigma_%i",i+1)  , Form("Sigma_%i",i+1), 1000, 0.0 , fMaxSigma );

    double fSigmaEvetns = 0;
    for( j = 0; j < N_entries; j++ ) {
    
      t1[i]->GetEntry(j);
    
      if( 
	 ( EnergyConserve              == 1   )   &&
	 ( XMomConserve                == 1   )   &&
	 ( YMomConserve                == 1   )   &&
	 ( ZMomConserve                == 1   )   &&
	 ( T_GeV                       < 1.2  )   &&
	 // ( Qsq_GeV                     > 1    )   &&
	 // ( RecoilProton_Energy_Col_GeV > 1.0  )   && 
	 ( RecoilProton_Theta_Col      > 8.0  )   && 
	 ( RecoilProton_Theta_Col      < 24.0 ) 
	  )
	{



	  if ( RecoilProton_Mom_Col_GeV < 0.2 )
	    continue;

	  if ( ZASigma_Lab > 2.0 )
	    continue;

	  double fRandSigma = fMaxSigma * fRandom->Uniform( 0 , 1 );
	  if ( ZASigma_Lab > fRandSigma ) {
	    
	    // cout << setw(20) << j << setw(20) << ZASigma_Lab << setw(20) << fRandSigma
	    // << endl;
	    
	    hSigma[i]->Fill(ZASigma_Lab);
	    fSigmaEvetns ++;

	  }

	}
    }

    canv->cd(i+1)->SetLogy();
    hSigma[i]->Draw();
    canv->Update();

      cout << "File: " << input_filename[i].c_str()
	   << setw(16) << "Max Sigma: " << setw(16) << fMaxSigma
	   << "  Total events: " << setw(12) << N_entries
	   << "  Total evetns distributed according to crossection: " << setw(12) << fSigmaEvetns 
	   << endl;

  }

  canv->SaveAs("Sigma.png");
      
  return;
}

