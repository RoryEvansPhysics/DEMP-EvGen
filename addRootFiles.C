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


void addRootFiles() {

  const int fN = 10;

  double Electron_Mass                              = 0.511;
  double Electron_Mass_GeV                          = Electron_Mass/1000.0;
  double Proton_Mass                                = 939.57; // It is the mass of Neutron. The target is Neutron in SoLID DVMP.
  double Proton_Mass_GeV                            = Proton_Mass/1000.0;
  double Neutron_Mass                               = 938.27; // Its is the mass of Proton which in SoLID DVMP is outgoing reocil Proton
  double Neutron_Mass_GeV                           = Neutron_Mass/1000.0;
  double RecoilProton_Mass                          = 938.27;
  double RecoilProton_Mass_GeV                      = RecoilProton_Mass/1000.0;
  double Pion_Mass                                  = 139.57;
  double Pion_Mass_GeV                              = Pion_Mass/1000.0;

  TFile *f1[fN];
  TTree *t1[fN];
  TString s1[fN];

  // int N_entries = 100000;
  double event_weight  = 0;
  double Ratio         = 1.0;
  // Long64_t N_Total     = N_entries * Ratio; 
  const double nBcm2 = 1e-30; // ub to cm-2
  const double Lumi    = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
  const double uBcm2   = 1e-30;
  const double PI      = 3.1415926;
  const double DEG2RAD = PI/180.0;
  double EBeam         = 11.0; // GeV
  double PSF           = EBeam * ( 0.9 - 0.1 ) * ( ( sin(30.0*DEG2RAD) - sin(5.0*DEG2RAD) ) * 2*PI * 
						   ( sin(18.0*DEG2RAD) - sin(5.0*DEG2RAD) ) * 2*PI );
  double fLumi    = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
  double fuBcm2   = 1e-30;
  double fPI      = 3.1415926;
  double fDEG2RAD = fPI/180.0;
  double fEBeam   = 11.0; // GeV
  double fPSF     = fEBeam * ( 0.9 - 0.1 ) * ( sin(30.0*fDEG2RAD) - sin(5.0*fDEG2RAD) ) * 2*fPI * ( sin(18.0*fDEG2RAD) - sin(5.0*fDEG2RAD) ) * 2*fPI;
  
  int fCount1 = 0, fCount2 = 0, fCount3 = 0, fCount4 = 0;

  double fGenEvents = 0, fRecEvents = 0;
  
  Long64_t i,j;
  double fRate = 0.0;
  double fRatio = 0.0;
  double fMaxWeight = 0;

  TH1F *hUU = new TH1F( "hUU" , "Sigma UU", 1000, 0.0 , 1.0 );
  TH1F *hUT = new TH1F( "hUT" , "Sigma UT", 1000, 0.0 , 1.0 );
  TH1F *ht  = new TH1F( "ht"  , "-t", 1000, 0.0 , 10.0 );
  TH1F *hw  = new TH1F( "hw"  , "w",  1000, 0.0 , 10.0 );
  TH1F *hq  = new TH1F( "hq"  , "q",  1000, 0.0 , 20.0 );

  ofstream ppiOut ( "DEMP_11GeV_Acceptance.lund" );

  for ( i = 0; i < fN; i++ ) {

    s1[i] = "./RootFiles/DVMP_Ee_11_Events_60000000_File_";
    s1[i] += i + 1;
    s1[i] += ".root";
    f1[i] = new TFile(s1[i],"r");

    if ( !f1[i] ) { cout << "File does not exists" << endl; return; }
    t1[i] = (TTree*) f1[i]->Get("t1");

    cout << "Total events in file: " << s1[i] << setw(10) << t1[i]->GetEntries() << endl;
    // cout << setw(10) << "Generated" << setw(10) << "Recorded" 
    // 	 << setw(12) << "w"         << setw(12) << "-t"       << setw(12) << "Qsq"    << setw(12) << "Epsilon" 
    // 	 << setw(14) << "Sig_L"     << setw(14) << "Sig_T"    << setw(14) << "Sig_LT" << setw(14) << "Sig_TT" 
    // 	 << setw(14) << "Sigma_UU"  << setw(14) << "Sigma_UT" << setw(14) << "Sigma"
    // 	 << setw(12) << "Weight" 
    // 	 << endl;

    // cout << setw(20) << "Pion theta"        << setw(10) << "phi" << setw(10) << "energy" 
    // 	 << setw(20) << "ScatElec theta"    << setw(10) << "phi" 
    // 	 << setw(20) << "RecoiProton theta" << setw(10) << "phi" 
    // 	 << endl;

    // cout << "Number of particles" << " \t " << "sigma para" << " \t " << "sigma" << " \t " << "SSAsym" << " \t " << "0" << " \t "  
    // 	 << "x" << " \t " << "-t" << " \t " << "w" << " \t " << "Qsq"  << " \t " << "Epsilon" << endl;

    cout << setw(14) << "index" 
	 << setw(14) << "charge" 
	 << setw(14) << "type" 
	 << setw(14) << "PARTICLE ID" 
	 << setw(14) << "parent index" 
	 << setw(14) << "daughter index" 
	 << setw(16) << "momentum x"
	 << setw(16) << "momentum y"
	 << setw(16) << "momentum z"
	 << setw(16) << "E"
	 << setw(16) << "Mass"
	 << setw(16) << "Vertex X"
	 << setw(16) << "Vertex Y"
	 << setw(16) << "Vertex Z"
	 << endl;


    int NRecorded, NGenerated;
    Double_t ZASig_T, ZASig_L, ZASig_LT, ZASig_TT, Vertex_X, Vertex_Y, Vertex_Z, SSAsym;
    Double_t Epsilon, Qsq, T, W, x, y, z, ZASigmaLab, ZASigma_Lab, WSq_GeV, T_GeV, W_GeV, Qsq_GeV;
    Double_t EnergyConserve, XMomConserve, YMomConserve, ZMomConserve;
    Double_t ZASigma_UU, ZASigma_UUPara, ZASigma_UT, EventWeight;
    Double_t Neutron_Energy_Col,Neutron_MomX_Col,Neutron_MomY_Col,Neutron_MomZ_Col,Neutron_Mom_Col; 
    Double_t Neutron_Phi_Col,Neutron_Theta_Col, Coef_ZA_1, Coef_ZA_2, Coef_ZA_3, Coef_ZA_4, Coef_ZA_5, Coef_ZA_6;

    Double_t ScatElec_Energy_Col_GeV, ScatElec_MomX_Col,ScatElec_MomY_Col,ScatElec_MomZ_Col,ScatElec_Mom_Col_GeV; 
    Double_t ScatElec_MomX_Col_GeV,ScatElec_MomY_Col_GeV,ScatElec_MomZ_Col_GeV,ScatElec_Mom_Col_GeV_GeV; 
    Double_t ScatElec_Phi_Col,ScatElec_Theta_Col;
    Double_t ScatElec_Corrected_Energy_Col_GeV,ScatElec_Corrected_Mom_Col_GeV; 
    Double_t ScatElec_Corrected_MomX_Col,ScatElec_Corrected_MomY_Col,ScatElec_Corrected_MomZ_Col;
    Double_t ScatElec_Corrected_MomX_Col_GeV,ScatElec_Corrected_MomY_Col_GeV,ScatElec_Corrected_MomZ_Col_GeV;
    Double_t ScatElec_Corrected_Phi_Col,ScatElec_Corrected_Theta_Col;

    Double_t Pion_Energy_Col, Pion_MomX_Col,Pion_MomY_Col,Pion_MomZ_Col, Pion_Mom_Col; 
    Double_t Pion_Phi_Col,Pion_Theta_Col;
    Double_t Pion_Corrected_Energy_Col_GeV, Pion_Corrected_Mom_Col_GeV, Pion_Mom_Col_GeV;
    Double_t Pion_Corrected_MomX_Col,Pion_Corrected_MomY_Col,Pion_Corrected_MomZ_Col;
    Double_t Pion_Energy_Col_GeV, Pion_MomX_Col_GeV,Pion_MomY_Col_GeV,Pion_MomZ_Col_GeV;
    Double_t Pion_Corrected_Phi_Col, Pion_Corrected_Theta_Col;
  
    Double_t RecoilProton_Energy_Col,RecoilProton_MomX_Col,RecoilProton_MomY_Col,RecoilProton_MomZ_Col,RecoilProton_Mom_Col; 
    Double_t RecoilProton_Energy_Col_GeV,RecoilProton_MomX_Col_GeV,RecoilProton_MomY_Col_GeV,RecoilProton_MomZ_Col_GeV,RecoilProton_Mom_Col_GeV; 
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

    t1[i]->SetBranchAddress("ScatElec_MomX_Col_GeV", &ScatElec_MomX_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_MomY_Col_GeV", &ScatElec_MomY_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_MomZ_Col_GeV", &ScatElec_MomZ_Col_GeV );

    t1[i]->SetBranchAddress("ScatElec_Mom_Col_GeV", &ScatElec_Mom_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_Theta_Col", &ScatElec_Theta_Col );
    t1[i]->SetBranchAddress("ScatElec_Phi_Col", &ScatElec_Phi_Col );
    t1[i]->SetBranchAddress("ScatElec_Corrected_Energy_Col_GeV", &ScatElec_Corrected_Energy_Col_GeV );
    t1[i]->SetBranchAddress("ScatElec_Corrected_Mom_Col_GeV",    &ScatElec_Corrected_Mom_Col_GeV );
    t1[i]->SetBranchAddress("Pion_Energy_Col", &Pion_Energy_Col );
    t1[i]->SetBranchAddress("Pion_MomX_Col", &Pion_MomX_Col );
    t1[i]->SetBranchAddress("Pion_MomY_Col", &Pion_MomY_Col );
    t1[i]->SetBranchAddress("Pion_MomZ_Col", &Pion_MomZ_Col );

    t1[i]->SetBranchAddress("Pion_MomX_Col_GeV", &Pion_MomX_Col_GeV );
    t1[i]->SetBranchAddress("Pion_MomY_Col_GeV", &Pion_MomY_Col_GeV );
    t1[i]->SetBranchAddress("Pion_MomZ_Col_GeV", &Pion_MomZ_Col_GeV );
    t1[i]->SetBranchAddress("Pion_Energy_Col_GeV", &Pion_Energy_Col_GeV );

    t1[i]->SetBranchAddress("Pion_Mom_Col", &Pion_Mom_Col );
    t1[i]->SetBranchAddress("Pion_Theta_Col", &Pion_Theta_Col );
    t1[i]->SetBranchAddress("Pion_Phi_Col", &Pion_Phi_Col );
    t1[i]->SetBranchAddress("Pion_Corrected_Energy_Col_GeV", &Pion_Corrected_Energy_Col_GeV );
    t1[i]->SetBranchAddress("Pion_Corrected_Mom_Col_GeV", &Pion_Corrected_Mom_Col_GeV );
    t1[i]->SetBranchAddress("Pion_Mom_Col_GeV", &Pion_Mom_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_Energy_Col", &RecoilProton_Energy_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomX_Col", &RecoilProton_MomX_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomY_Col", &RecoilProton_MomY_Col );
    t1[i]->SetBranchAddress("RecoilProton_MomZ_Col", &RecoilProton_MomZ_Col );

    t1[i]->SetBranchAddress("RecoilProton_MomX_Col_GeV", &RecoilProton_MomX_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_MomY_Col_GeV", &RecoilProton_MomY_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_MomZ_Col_GeV", &RecoilProton_MomZ_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_Energy_Col_GeV", &RecoilProton_Energy_Col_GeV );

    t1[i]->SetBranchAddress("RecoilProton_Mom_Col", &RecoilProton_Mom_Col );
    t1[i]->SetBranchAddress("RecoilProton_Theta_Col", &RecoilProton_Theta_Col );
    t1[i]->SetBranchAddress("RecoilProton_Phi_Col", &RecoilProton_Phi_Col );
    t1[i]->SetBranchAddress("RecoilProton_Corrected_Energy_Col_GeV", &RecoilProton_Corrected_Energy_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_Corrected_Mom_Col_GeV", &RecoilProton_Corrected_Mom_Col_GeV );
    t1[i]->SetBranchAddress("RecoilProton_Mom_Col_GeV", &RecoilProton_Mom_Col_GeV );
    t1[i]->SetBranchAddress("EventWeight", &EventWeight);
    t1[i]->SetBranchAddress("ZASigma_UU",  &ZASigma_UU);
    t1[i]->SetBranchAddress("ZASigma_UU",  &ZASigma_UUPara);
    t1[i]->SetBranchAddress("ZASigma_UT",  &ZASigma_UT);
    t1[i]->SetBranchAddress("Coef_ZA_1",   &Coef_ZA_1);
    t1[i]->SetBranchAddress("Coef_ZA_2",   &Coef_ZA_2);
    t1[i]->SetBranchAddress("Coef_ZA_3",   &Coef_ZA_3);
    t1[i]->SetBranchAddress("Coef_ZA_4",   &Coef_ZA_4);
    t1[i]->SetBranchAddress("Coef_ZA_5",   &Coef_ZA_5);
    t1[i]->SetBranchAddress("Coef_ZA_6",   &Coef_ZA_6);
    t1[i]->SetBranchAddress("NRecorded",   &NRecorded);
    t1[i]->SetBranchAddress("NGenerated",  &NGenerated);
    t1[i]->SetBranchAddress("EnergyConserve",  &EnergyConserve);
    t1[i]->SetBranchAddress("XMomConserve",  &XMomConserve);
    t1[i]->SetBranchAddress("YMomConserve",  &YMomConserve);
    t1[i]->SetBranchAddress("ZMomConserve",  &ZMomConserve);

    t1[i]->SetBranchAddress("Vertex_X",  &Vertex_X);
    t1[i]->SetBranchAddress("Vertex_Y",  &Vertex_Y);
    t1[i]->SetBranchAddress("Vertex_Z",  &Vertex_Z);

    t1[i]->SetBranchAddress("SSAsym",  &SSAsym);

    Long64_t N_entries = t1[i]->GetEntries();
    for( j = 0; j < N_entries; j++ ) {
    
      t1[i]->GetEntry(j);
    
      if( 
	 ( EventWeight > 0 )                                                       && 
	 ( EnergyConserve == 1 )                                                   &&
	 ( XMomConserve == 1 )                                                     &&
	 ( YMomConserve == 1 )                                                     &&
	 ( ZMomConserve == 1 )                                                     &&
	 ( T_GeV < 1.2 )                                                           &&
	 ( Qsq_GeV > 0.1 )                                                         &&
	 ( WSq_GeV > 3.961 )                                                       &&
	 // ( ( ScatElec_Phi_Col        > 0.0   && ScatElec_Phi_Col        < 90.0 ) || ( ScatElec_Phi_Col        > 270.0   && ScatElec_Phi_Col        < 360.0 ) ) && 
	 // ( ( Pion_Phi_Col            > 0.0   && Pion_Phi_Col            < 90.0 ) || ( Pion_Phi_Col            > 270.0   && Pion_Phi_Col            < 360.0 ) ) && 
	 // ( ( RecoilProton_Phi_Col    > 0.0   && RecoilProton_Phi_Col    < 90.0 ) || ( RecoilProton_Phi_Col    > 270.0   && RecoilProton_Phi_Col    < 360.0 ) ) &&
	 ( ScatElec_Theta_Col        > 8.0   && ScatElec_Theta_Col        < 24.0 ) && ( ScatElec_Mom_Col_GeV      > 1.0   && ScatElec_Mom_Col_GeV      < 11.0 ) && 
	 ( Pion_Theta_Col            > 8.0   && Pion_Theta_Col            < 18.0 ) && ( Pion_Mom_Col_GeV          > 1.0   && Pion_Mom_Col_GeV          < 11.0 ) &&
	 ( RecoilProton_Theta_Col    > 8.0   && RecoilProton_Theta_Col    < 24.0 ) && ( RecoilProton_Mom_Col_GeV  > 1.0   && RecoilProton_Mom_Col_GeV  < 11.0 ) 
	 
	  ) 
	{
	
	  
	  // cout << setw(20) << Pion_Theta_Col          << setw(10) << Pion_Phi_Col            << setw(10) << Pion_Energy_Col_GeV
	  //      << setw(20) << ScatElec_Theta_Col      << setw(10) << ScatElec_Phi_Col
	  //      << setw(20) << RecoilProton_Theta_Col  << setw(10) << RecoilProton_Phi_Col
	  //      << endl;
	  
	  ht->Fill(T_GeV);
	  hw->Fill(W_GeV);
	  hq->Fill(Qsq_GeV);       

	  fCount4++;

	  fRate += EventWeight / fN;

	  cout << setw(14) << "3" << setw(14) << ZASigma_UUPara << setw(14) << ZASigma_Lab << setw(14) << SSAsym << setw(14) << "0" << setw(14)
	       << x << setw(16) << T_GeV << setw(16) << W_GeV << setw(16) << Qsq_GeV  << setw(16) << Epsilon << endl;
      
	  // Pion -
	  cout << setw(14) << "1" 
	       << setw(14) << "1" 
	       << setw(14) << "1" 
	       << setw(14) << "211" 
	       << setw(14) << "0" 
	       << setw(14) << "0" 
	       << setw(16) << Pion_MomX_Col_GeV    
	       << setw(16) << Pion_MomY_Col_GeV   
	       << setw(16) << Pion_MomZ_Col_GeV  
	       << setw(16) << Pion_Energy_Col_GeV
	       << setw(16) << Pion_Mass_GeV
	       << setw(16) << Vertex_X
	       << setw(16) << Vertex_Y
	       << setw(16) << Vertex_Z
	       << endl;
    
	  // Electron
	  cout << setw(14) << "2" 
	       << setw(14) << "-1" 
	       << setw(14) << "1" 
	       << setw(14) << "11" 
	       << setw(14) << "0" 
	       << setw(14) << "0" 
	       << setw(16) << ScatElec_MomX_Col_GeV  
	       << setw(16) << ScatElec_MomY_Col_GeV   
	       << setw(16) << ScatElec_MomZ_Col_GeV  
	       << setw(16) << ScatElec_Energy_Col_GeV
	       << setw(16) << Electron_Mass_GeV
	       << setw(16) << Vertex_X
	       << setw(16) << Vertex_Y
	       << setw(16) << Vertex_Z
	       << endl;
	  
	  // Proton
	  cout << setw(14) << "3" 
	       << setw(14) << "1" 
	       << setw(14) << "1" 
	       << setw(14) << "2212" 
	       << setw(14) << "0" 
	       << setw(14) << "0" 
	       << setw(16) << RecoilProton_MomX_Col_GeV    
	       << setw(16) << RecoilProton_MomY_Col_GeV   
	       << setw(16) << RecoilProton_MomZ_Col_GeV  
	       << setw(16) << RecoilProton_Energy_Col_GeV
	       << setw(16) << RecoilProton_Mass_GeV
	       << setw(16) << Vertex_X
	       << setw(16) << Vertex_Y
	       << setw(16) << Vertex_Z
	       << endl;

	  ppiOut << "3" << " \t " << ZASigma_UUPara << " \t " << ZASigma_Lab << " \t " << SSAsym << " \t " << "0" << " \t "  
		 << x << " \t " << T_GeV << " \t " << W_GeV << " \t " << Qsq_GeV  << " \t " << Epsilon << endl;
      
	  // Pion -
	  ppiOut << setw(10) << "1" 
		 << setw(10) << "1" 
		 << setw(10) << "1" 
		 << setw(10) << "211" 
		 << setw(10) << "0" 
		 << setw(10) << "0" 
		 << setw(16) << Pion_MomX_Col_GeV    
		 << setw(16) << Pion_MomY_Col_GeV   
		 << setw(16) << Pion_MomZ_Col_GeV  
		 << setw(16) << Pion_Energy_Col_GeV
		 << setw(16) << Pion_Mass_GeV
		 << setw(16) << Vertex_X
		 << setw(16) << Vertex_Y
		 << setw(16) << Vertex_Z
		 << endl;
    
	  // Electron
	  ppiOut << setw(10) << "2" 
		 << setw(10) << "-1" 
		 << setw(10) << "1" 
		 << setw(10) << "11" 
		 << setw(10) << "0" 
		 << setw(10) << "0" 
		 << setw(16) << ScatElec_MomX_Col_GeV  
		 << setw(16) << ScatElec_MomY_Col_GeV   
		 << setw(16) << ScatElec_MomZ_Col_GeV  
		 << setw(16) << ScatElec_Energy_Col_GeV
		 << setw(16) << Electron_Mass_GeV
		 << setw(16) << Vertex_X
		 << setw(16) << Vertex_Y
		 << setw(16) << Vertex_Z
		 << endl;
	  
	  // Proton
	  ppiOut << setw(10) << "3" 
		 << setw(10) << "1" 
		 << setw(10) << "1" 
		 << setw(10) << "2212" 
		 << setw(10) << "0" 
		 << setw(10) << "0" 
		 << setw(16) << RecoilProton_MomX_Col_GeV    
		 << setw(16) << RecoilProton_MomY_Col_GeV   
		 << setw(16) << RecoilProton_MomZ_Col_GeV  
		 << setw(16) << RecoilProton_Energy_Col_GeV
		 << setw(16) << RecoilProton_Mass_GeV
		 << setw(16) << Vertex_X
		 << setw(16) << Vertex_Y
		 << setw(16) << Vertex_Z
		 << endl;
	
	  if ( fCount4 == 5 )
	    return;
		  
	}
    }

    fGenEvents += NGenerated;
    fRecEvents += NRecorded;


  }

  cout << "Final generated evetns = " << fGenEvents 
       << "   recorded evetns = " << fRecEvents 
       << "   passed evetns = " << fCount4
       << "   ratio = " << fRecEvents/fGenEvents
       << "   rate = " << fRate 
       << endl;

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

