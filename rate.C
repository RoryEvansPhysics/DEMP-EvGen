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


void rate () {


  // "abs(ScatElec_Theta_Col-16)<8&&abs(Pion_Theta_Col-13)<5&&abs(RecoilProton_Theta_Col-16)<8&&abs((ScatElec_Mom_Col_GeV)-6)<5&&abs(Pion_Mom_Col_GeV-6)<5&&abs(RecoilProton_Mom_Col_GeV-6)<5")

  TFile *f1 = new TFile("./RootFiles/DVMP_Ee_11_Events_90000000_File_1.root","r"); 


  if ( !f1 ) { cout << "File does not exists" << endl; return; }

  TTree* t1 = (TTree*) f1->Get("t1");

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
  
  Double_t RecoilProton_Energy_Col,RecoilProton_MomX_Col,RecoilProton_MomY_Col,RecoilProton_MomZ_Col,RecoilProton_Mom_Col; 
  Double_t RecoilProton_Phi_Col,RecoilProton_Theta_Col;
  Double_t RecoilProton_Corrected_Energy_Col_GeV, RecoilProton_Corrected_Mom_Col_GeV, RecoilProton_Mom_Col_GeV; 
  
  t1->SetBranchAddress("Epsilon", &Epsilon );
  t1->SetBranchAddress("Qsq", &Qsq );
  t1->SetBranchAddress("T", &T );
  t1->SetBranchAddress("W", &W );
  t1->SetBranchAddress("WSq_GeV", &WSq_GeV );
  t1->SetBranchAddress("T_GeV",   &T_GeV );
  t1->SetBranchAddress("W_GeV",   &W_GeV );
  t1->SetBranchAddress("Qsq_GeV", &Qsq_GeV );
  t1->SetBranchAddress("x", &x );
  t1->SetBranchAddress("y", &y );
  t1->SetBranchAddress("z", &z );
  t1->SetBranchAddress("ZASig_L",  &ZASig_L );
  t1->SetBranchAddress("ZASig_T",  &ZASig_T );
  t1->SetBranchAddress("ZASig_LT", &ZASig_LT );
  t1->SetBranchAddress("ZASig_TT", &ZASig_TT );
  t1->SetBranchAddress("ZASigma_Lab", &ZASigma_Lab);

  t1->SetBranchAddress("Neutron_Energy_Col", &Neutron_Energy_Col );
  t1->SetBranchAddress("Neutron_MomX_Col", &Neutron_MomX_Col );
  t1->SetBranchAddress("Neutron_MomY_Col", &Neutron_MomY_Col );
  t1->SetBranchAddress("Neutron_MomZ_Col", &Neutron_MomZ_Col );
  t1->SetBranchAddress("Neutron_Mom_Col", &Neutron_Mom_Col );
  t1->SetBranchAddress("Neutron_Theta_Col", &Neutron_Theta_Col );
  t1->SetBranchAddress("Neutron_Phi_Col", &Neutron_Phi_Col);
  
  t1->SetBranchAddress("ScatElec_Energy_Col_GeV", &ScatElec_Energy_Col_GeV );
  t1->SetBranchAddress("ScatElec_MomX_Col", &ScatElec_MomX_Col );
  t1->SetBranchAddress("ScatElec_MomY_Col", &ScatElec_MomY_Col );
  t1->SetBranchAddress("ScatElec_MomZ_Col", &ScatElec_MomZ_Col );
  t1->SetBranchAddress("ScatElec_Mom_Col_GeV", &ScatElec_Mom_Col_GeV );
  t1->SetBranchAddress("ScatElec_Theta_Col", &ScatElec_Theta_Col );
  t1->SetBranchAddress("ScatElec_Phi_Col", &ScatElec_Phi_Col );
  t1->SetBranchAddress("ScatElec_Corrected_Energy_Col_GeV", &ScatElec_Corrected_Energy_Col_GeV );
  t1->SetBranchAddress("ScatElec_Corrected_Mom_Col_GeV",    &ScatElec_Corrected_Mom_Col_GeV );
  
  t1->SetBranchAddress("Pion_Energy_Col", &Pion_Energy_Col );
  t1->SetBranchAddress("Pion_MomX_Col", &Pion_MomX_Col );
  t1->SetBranchAddress("Pion_MomY_Col", &Pion_MomY_Col );
  t1->SetBranchAddress("Pion_MomZ_Col", &Pion_MomZ_Col );
  t1->SetBranchAddress("Pion_Mom_Col", &Pion_Mom_Col );
  t1->SetBranchAddress("Pion_Theta_Col", &Pion_Theta_Col );
  t1->SetBranchAddress("Pion_Phi_Col", &Pion_Phi_Col );
  t1->SetBranchAddress("Pion_Corrected_Energy_Col_GeV", &Pion_Corrected_Energy_Col_GeV );
  t1->SetBranchAddress("Pion_Corrected_Mom_Col_GeV", &Pion_Corrected_Mom_Col_GeV );
  t1->SetBranchAddress("Pion_Mom_Col_GeV", &Pion_Mom_Col_GeV );

  t1->SetBranchAddress("RecoilProton_Energy_Col", &RecoilProton_Energy_Col );
  t1->SetBranchAddress("RecoilProton_MomX_Col", &RecoilProton_MomX_Col );
  t1->SetBranchAddress("RecoilProton_MomY_Col", &RecoilProton_MomY_Col );
  t1->SetBranchAddress("RecoilProton_MomZ_Col", &RecoilProton_MomZ_Col );
  t1->SetBranchAddress("RecoilProton_Mom_Col", &RecoilProton_Mom_Col );
  t1->SetBranchAddress("RecoilProton_Theta_Col", &RecoilProton_Theta_Col );
  t1->SetBranchAddress("RecoilProton_Phi_Col", &RecoilProton_Phi_Col );
  t1->SetBranchAddress("RecoilProton_Corrected_Energy_Col_GeV", &RecoilProton_Corrected_Energy_Col_GeV );
  t1->SetBranchAddress("RecoilProton_Corrected_Mom_Col_GeV", &RecoilProton_Corrected_Mom_Col_GeV );
  t1->SetBranchAddress("RecoilProton_Mom_Col_GeV", &RecoilProton_Mom_Col_GeV );
  t1->SetBranchAddress("EventWeight", &EventWeight);
  t1->SetBranchAddress("ZASigma_UU", &ZASigma_UU);
  t1->SetBranchAddress("ZASigma_UT", &ZASigma_UT);
  t1->SetBranchAddress("Coef_ZA_1", &Coef_ZA_1);
  t1->SetBranchAddress("Coef_ZA_2", &Coef_ZA_2);
  t1->SetBranchAddress("Coef_ZA_3", &Coef_ZA_3);
  t1->SetBranchAddress("Coef_ZA_4", &Coef_ZA_4);
  t1->SetBranchAddress("Coef_ZA_5", &Coef_ZA_5);
  t1->SetBranchAddress("Coef_ZA_6", &Coef_ZA_6);
  t1->SetBranchAddress("NRecorded", &NRecorded);
  t1->SetBranchAddress("NGenerated",&NGenerated);
  t1->SetBranchAddress("EnergyConserve", &EnergyConserve);
  t1->SetBranchAddress("XMomConserve", &XMomConserve);
  t1->SetBranchAddress("YMomConserve", &YMomConserve);
  t1->SetBranchAddress("ZMomConserve", &ZMomConserve);

  TH1F *hUU = new TH1F( "hUU" , "Sigma UU", 1000, 0.0 , 1.0 );
  TH1F *hUT = new TH1F( "hUT" , "Sigma UT", 1000, 0.0 , 1.0 );
  TH1F *ht  = new TH1F( "ht"  , "-t",       1000, 0.0 , 2.0 );
  TH1F *hw  = new TH1F( "hw"  , "w",        1000, 0.0 , 5.0 );
  TH1F *hq  = new TH1F( "hq"  , "Qsq",      1000, 0.0 , 10.0 );

  // int N_entries = 100000;
  Long64_t N_entries   = t1->GetEntries();
  double event_weight  = 0;
  double Ratio         = 0.013;
  Long64_t N_Total     = N_entries * Ratio; 
  const double Lumi    = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
  const double uBcm2   = 1e-30;
  const double nBcm2   = 1e-30; // ub to cm-2
  const double PI      = 3.1415926;
  const double DEG2RAD = PI/180.0;
  double EBeam         = 11.0; // GeV
  double PSF           = ( EBeam * ( 0.9 - 0.1 ) * 
			   ( sin( 29.0 * DEG2RAD) - sin( 7.0 * DEG2RAD ) ) * 2 * PI * 
			   ( sin( 19.0 * DEG2RAD) - sin( 7.0 * DEG2RAD ) ) * 2 * PI );
  double fLumi    = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
  double fuBcm2   = 1e-30;
  double fPI      = 3.1415926;
  double fDEG2RAD = fPI/180.0;
  double fEBeam   = 11.0; // GeV
  double fPSF     = fEBeam * ( 0.9 - 0.1 ) * ( sin(30.0*fDEG2RAD) - sin(5.0*fDEG2RAD) ) * 2*fPI * ( sin(18.0*fDEG2RAD) - sin(5.0*fDEG2RAD) ) * 2*fPI;

  cout << setw(10) << "Generated" << setw(10) << "Recorded" 
       << setw(12) << "w"         << setw(12) << "-t"       << setw(12) << "Qsq"    << setw(12) << "Epsilon" 
       << setw(14) << "Sig_L"     << setw(14) << "Sig_T"    << setw(14) << "Sig_LT" << setw(14) << "Sig_TT" 
       << setw(14) << "Sigma_UU"  << setw(14) << "Sigma_UT" << setw(14) << "Sigma"
       << setw(12) << "Weight" 
       << endl;
  
  int fCount1 = 0;
  int fCount2 = 0;
  int fCount3 = 0;
  int fCount4 = 0;

  
  Long64_t i;
  double fRate = 0.0;
  double fRatio = 0.0;
  double fMaxWeight = 0;
  double fMaxSigma = 0;

  cout << setw(12) << "Sigma" << setw(12) << "EventWeight" << setw(10) << "PSF" << setw(10) << "N_Total" 
       << setw(10) << "Bcm" << setw(10) << "Lumi" << setw(14) << "Rate" << endl;
  for( i = 0; i < N_entries; i++ ) {
    
    t1->GetEntry(i);
    
    if( 
       // ( EventWeight > 0 )                                                       && 
       ( EnergyConserve == 1 )                                                   &&
       ( XMomConserve == 1 )                                                     &&
       ( YMomConserve == 1 )                                                     &&
       ( ZMomConserve == 1 )                                                     &&
       ( T_GeV < 1.2 )                                                           &&
       ( Qsq_GeV > 0.1 )                                                         &&
       ( WSq_GeV > 3.961 )                                                       &&
       ( ScatElec_Theta_Col        > 8.0   && ScatElec_Theta_Col        < 24.0 ) && ( ScatElec_Mom_Col_GeV      > 1.0   && ScatElec_Mom_Col_GeV      < 11.0 ) && 
       ( Pion_Theta_Col            > 8.0   && Pion_Theta_Col            < 18.0 ) && ( Pion_Mom_Col_GeV          > 1.0   && Pion_Mom_Col_GeV          < 11.0 ) &&
       ( RecoilProton_Theta_Col    > 8.0   && RecoilProton_Theta_Col    < 24.0 ) && ( RecoilProton_Mom_Col_GeV  > 1.0   && RecoilProton_Mom_Col_GeV  < 11.0 ) 
    	) 
      {
	
    	ht->Fill(T_GeV);
    	hw->Fill(W_GeV);
    	hq->Fill(Qsq_GeV);
	
    	fCount4++;
    	// fRate += ZASigma_Lab * PSF * nBcm2 * Lumi;
    	fRate += EventWeight;

      }
  }
  
  fRatio = ( 1.0 * NRecorded ) / ( 1.0 * NGenerated ) ;
  cout << "Total generated evetns = " << NGenerated << "    total recorded evetns = " << NRecorded << "   ratio = " << fRatio
       << endl;
  cout << "Total events passed the condition = " << fCount4 << endl;
  cout << "Rate = " << fRate << endl;

  TCanvas *canv=new TCanvas("canv","Sigma", 1600, 800);
  canv->cd(0);
  canv->SetFillColor(17);
  canv->Divide(2,2);
  canv->cd(1)->SetLogy();
  hUU->SetLineColor(kBlue);
  hUT->SetLineColor(kRed);
  hUU->Draw();
  hUT->Draw("same");

  canv->cd(2);  ht->Draw();
  canv->cd(3);  hw->Draw();
  canv->cd(4);  hq->Draw();

  canv->Update();

  return;
}

