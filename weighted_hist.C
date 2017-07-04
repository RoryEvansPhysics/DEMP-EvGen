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


void weighted_hist () {


  TFile* f1=new TFile("./RootFiles/DVMP_Ee_11_Events_500000_File_1.root","r"); 


  if ( !f1 ) {
    cout << "File does not exists" << endl;
    return;
  }

  TTree* t1 = (TTree*) f1->Get("t1");

  int NRecorded;
  int NGenerated;

  Double_t ZASig_T;
  Double_t ZASig_L;
  Double_t ZASig_LT;
  Double_t ZASig_TT;

  Double_t Epsilon, Qsq, T, W, x, y, z, ZASigmaLab, ZASigma_Lab, WSq_GeV, T_GeV, Qsq_GeV;
  Double_t ZASigma_UU, ZASigma_UT, EventWeight;
  Double_t Neutron_Energy_Col,Neutron_MomX_Col,Neutron_MomY_Col,Neutron_MomZ_Col,Neutron_Mom_Col; 
  Double_t Neutron_Phi_Col,Neutron_Theta_Col, Coef_ZA_1, Coef_ZA_2, Coef_ZA_3, Coef_ZA_4, Coef_ZA_5, Coef_ZA_6;

  Double_t ScatElec_Energy_Col,ScatElec_MomX_Col,ScatElec_MomY_Col,ScatElec_MomZ_Col,ScatElec_Mom_Col; 
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
  t1->SetBranchAddress("Qsq_GeV", &Qsq_GeV );

  t1->SetBranchAddress("x", &x );
  t1->SetBranchAddress("y", &y );
  t1->SetBranchAddress("z", &z );
  t1->SetBranchAddress("ZASig_L",  &ZASig_L );
  t1->SetBranchAddress("ZASig_T",  &ZASig_T );
  t1->SetBranchAddress("ZASig_LT", &ZASig_LT );
  t1->SetBranchAddress("ZASig_TT", &ZASig_TT );

  t1->SetBranchAddress("ZASigmaLab", &ZASigmaLab );  
  t1->SetBranchAddress("ZASigma_Lab", &ZASigma_Lab);


  t1->SetBranchAddress("Neutron_Energy_Col", &Neutron_Energy_Col );
  t1->SetBranchAddress("Neutron_MomX_Col", &Neutron_MomX_Col );
  t1->SetBranchAddress("Neutron_MomY_Col", &Neutron_MomY_Col );
  t1->SetBranchAddress("Neutron_MomZ_Col", &Neutron_MomZ_Col );
  t1->SetBranchAddress("Neutron_Mom_Col", &Neutron_Mom_Col );
  t1->SetBranchAddress("Neutron_Theta_Col", &Neutron_Theta_Col );
  t1->SetBranchAddress("Neutron_Phi_Col", &Neutron_Phi_Col);
  
  t1->SetBranchAddress("ScatElec_Energy_Col", &ScatElec_Energy_Col );
  t1->SetBranchAddress("ScatElec_MomX_Col", &ScatElec_MomX_Col );
  t1->SetBranchAddress("ScatElec_MomY_Col", &ScatElec_MomY_Col );
  t1->SetBranchAddress("ScatElec_MomZ_Col", &ScatElec_MomZ_Col );
  t1->SetBranchAddress("ScatElec_Mom_Col", &ScatElec_Mom_Col );
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
  t1->SetBranchAddress("EventWeight", &EventWeight );
  t1->SetBranchAddress("ZASigma_UU",  &ZASigma_UU);
  t1->SetBranchAddress("ZASigma_UT",  &ZASigma_UT);
  t1->SetBranchAddress("Coef_ZA_1",   &Coef_ZA_1);
  t1->SetBranchAddress("Coef_ZA_2",   &Coef_ZA_2);
  t1->SetBranchAddress("Coef_ZA_3",   &Coef_ZA_3);
  t1->SetBranchAddress("Coef_ZA_4",   &Coef_ZA_4);
  t1->SetBranchAddress("Coef_ZA_5",   &Coef_ZA_5);
  t1->SetBranchAddress("Coef_ZA_6",   &Coef_ZA_6);
  t1->SetBranchAddress("NRecorded",   &NRecorded);
  t1->SetBranchAddress("NGenerated",  &NGenerated);

  TH1F *hScatEeRaw = new TH1F( "hScatEeRaw" , "Scattered Electron's Energy Raw", 100 , 0.0 , 11.0 );
  hScatEeRaw->GetXaxis()->SetTitle("Scat. Elec. energy (GeV) Raw value");

  TH1F *hSigma = new TH1F( "hSigma" , "Cross section with cuts", 1000 , 0.0 , 0.001 );
  hSigma->GetXaxis()->SetTitle("Cross section");

  TH1F *hScatEe = new TH1F( "hScatEe" , "Scattered Electron's Energy ", 100 , 0.0 , 11.0 );
  hScatEe->GetXaxis()->SetTitle("Scat. Elec. energy (GeV)");

  TH1F *hScatEeWegiht = new TH1F( "hScatEeWegiht" , "Scattered Electron's Energy (Weight)", 100 , 0.0 , 11.0 );
  hScatEeWegiht->GetXaxis()->SetTitle("Scat. Elec. energy weight (GeV)");

  // int N_entries = 100000;
  Long64_t N_entries   = t1->GetEntries();
  double event_weight  = 0;
  double Ratio         = 1.0;
  Long64_t N_Total     = N_entries * Ratio; 
  const double Lumi    = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
  const double uBcm2   = 1e-30;
  const double PI      = 3.1415926;
  const double DEG2RAD = PI/180.0;
  double EBeam         = 11.0; // GeV
  double PSF           = EBeam * ( 0.9 - 0.1 ) * ( ( sin(30.0*DEG2RAD) - sin(5.0*DEG2RAD) ) * 2*PI * 
						   ( sin(18.0*DEG2RAD) - sin(5.0*DEG2RAD) ) * 2*PI );
  double total_rate;

  double fLumi    = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
  double fuBcm2   = 1e-30;
  double fPI      = 3.1415926;
  double fDEG2RAD = fPI/180.0;
  double fEBeam   = 11.0; // GeV
  double fPSF     = fEBeam * ( 0.9 - 0.1 ) * ( sin(30.0*fDEG2RAD) - sin(5.0*fDEG2RAD) ) * 2*fPI * ( sin(18.0*fDEG2RAD) - sin(5.0*fDEG2RAD) ) * 2*fPI;

  cout << setw(10) << "Generated" << setw(10) << "Recorded" 
       << setw(12) << "WSq" 
       // << setw(14) << "Sigma" 
       << setw(14) << "Sigma_UU" << setw(14) << "Sig_L" << setw(14) << "Sig_T" << setw(14) << "Sig_LT" << setw(14) << "Sig_TT" 
       // << setw(14) << "Sigma_UT" 
       // << setw(14) << "coef 1" << setw(14) << "coef 2" << setw(14) << "coef 3" << setw(14) << "coef 4" << setw(14) << "coef 5" << setw(14) << "coef 6" 
       << setw(12) << "Weight" 
       << endl;
  
  int fCount = 0;
  Long64_t i;
  for( i = 0; i < N_entries; i++ ) {
    
    t1->GetEntry(i);
    
    if( ( ScatElec_Theta_Col        > 8.0   && ScatElec_Theta_Col        < 24.0 ) && 
	( ScatElec_Mom_Col/1000.0   > 1.0   && ScatElec_Mom_Col/1000.0   < 11.0 ) && 
	( Pion_Theta_Col            > 8.0   && Pion_Theta_Col            < 18.0 ) && 
	( Pion_Mom_Col_GeV          > 1.0   && Pion_Mom_Col_GeV          < 11.0 ) && 
	( RecoilProton_Theta_Col    > 8.0   && RecoilProton_Theta_Col    < 24.0 ) && 
	( RecoilProton_Mom_Col_GeV  > 1.0   && RecoilProton_Mom_Col_GeV  < 11.0 ) && 
	( WSq_GeV                   > 3.61  && T_GeV                     < 1      && Qsq_GeV  > 1.0 ) ) {
      
      cout << "Event Weight = " << EventWeight << endl;
      
    }

  
  return;


  // for( i = 0; i < N_entries; i++ ) {

  //   t1->GetEntry(i);

  //   // hScatEeRaw->Fill( ScatElec_Corrected_Energy_Col_GeV );

  //   if( ( ScatElec_Theta_Col                  > 8.0   && ScatElec_Theta_Col                  < 24.0 ) && 
  // 	( ScatElec_Corrected_Mom_Col_GeV      > 1.0   && ScatElec_Corrected_Mom_Col_GeV      < 11.0 ) && 
  // 	( Pion_Theta_Col                      > 8.0   && Pion_Theta_Col                      < 18.0 ) && 
  // 	( Pion_Corrected_Mom_Col_GeV          > 1.0   && Pion_Corrected_Mom_Col_GeV          < 11.0 ) && 
  // 	( RecoilProton_Theta_Col              > 8.0   && RecoilProton_Theta_Col              < 24.0 ) && 
  // 	( RecoilProton_Corrected_Mom_Col_GeV  > 1.0   && RecoilProton_Corrected_Mom_Col_GeV  < 11.0 ) && 
  // 	( ZASigmaLab                          > 1e-33 && WSq_GeV                             > 3.61   && 
  // 	( WSq_GeV                             > 3.61   && 
  // 	  T_GeV                               < 1     && Qsq_GeV                             > 1.0 ) 
  //   	) {

  //     // if( ZASigmaLab > 1e-33 && WSq_GeV > 3.61 && T_GeV < 1 && Qsq_GeV > 1.0 ) {
      
  //     event_weight = ZASigmaLab * PSF * uBcm2 * Lumi / N_Total;   //in Hz

  //     hScatEeWegiht->Fill( ScatElec_Corrected_Energy_Col_GeV , event_weight );
  //     hScatEe->Fill( ScatElec_Corrected_Energy_Col_GeV );
  //     hSigma->Fill( ZASigmaLab );

  //     double n1 = (double) NGenerated;
  //     double n2 = (double) NRecorded;

  //     total_rate += EventWeight; //  * n2 / n1;

  //     cout << "Rate = " << total_rate << endl;

  //   }    

  // }

  cout << "Rate: " << total_rate << " Hz"<< endl;


  TCanvas *can_forward=new TCanvas("can_forward","forward angle", 1200,1200);
  gPad->SetLogz(1);
  can_forward->Divide(2,2);
  can_forward->cd(1);
  hScatEeRaw->Draw();
  can_forward->cd(2);
  hScatEe->Draw();
  can_forward->cd(3);
  hScatEeWegiht->Draw();
  can_forward->cd(4);
  hSigma->Draw();
  can_forward->Update();
  can_forward->SaveAs("scat_elec_energy_2.png");

  
  double integral = 0;
  for ( int ii = 0; ii < 100; ii++ ) {

    integral += hScatEeWegiht->GetBinContent(ii);

  }

  cout << "Integral = " << integral << endl;
  cout << "Integral 2 = " << hScatEeWegiht->Integral() << endl;


}
