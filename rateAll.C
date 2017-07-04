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


void rateAll() {

  const int fN = 6;

  TFile *f1[fN];
  TTree *t1[fN];
  TString s1[fN];
  
  int fCount1 = 0, fCount2 = 0, fCount3 = 0, fCount4 = 0;
  double fGenEvents = 0, fRecEvents = 0;
  Long64_t i,j;
  double fRate = 0.0;

  TH1F *ht        = new TH1F( "ht"        , "-t",       500, 0.0 , 2.0  );
  TH1F *hw        = new TH1F( "hw"        , "w",        500, 0.0 , 5.0  );
  TH1F *hq        = new TH1F( "hq"        , "q",        500, 0.0 , 10.0 );
  TH1F *hWeight   = new TH1F( "hWeight"   , "Weight",   500, 0.0 , 10   );
  TH1F *hSig      = new TH1F( "hSig"      , "Sigma",    500, 0.0 , 0.5  );
  TH1F *hEps      = new TH1F( "hEps"      , "Epsilon",  500, 0.0 , 2.0  );
  TH2F *hQsqW     = new TH2F( "hQsqW"     , "Qsq vs W", 400,  0.0 , 10.0,  400, 0.0 , 5.0 );

  for ( i = 0; i < fN; i++ ) {

    s1[i] = "./RootFiles/DEMP_Ee_11_Events_3000000_File_";
    s1[i] += i;
    s1[i] += ".root";
    f1[i] = new TFile(s1[i],"r");

    if ( !f1[i] ) { cout << "File does not exists" << endl; return; }
    t1[i] = (TTree*) f1[i]->Get("t1");

    cout << "Total events in file: " << s1[i] << setw(10) << t1[i]->GetEntries() << endl;

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
    // Long64_t N_entries = 10000;
    for( j = 0; j < N_entries; j++ ) {
    
      t1[i]->GetEntry(j);
    
      if( 
	 // ( EventWeight > 0 )                                                       && 
	 // ( Epsilon < 0.99 )                                                        && 
	 // ( EventWeight < 1e-6 )                                                    && 
	 // ( EnergyConserve == 1 )                                                   &&
	 // ( XMomConserve == 1 )                                                     &&
	 // ( YMomConserve == 1 )                                                     &&
	 // ( ZMomConserve == 1 )                                                     &&
	 // ( T_GeV < 1.2 )                                                           &&
	 // ( Qsq_GeV > 0.1 )                                                         &&
	 // ( WSq_GeV > 3.961 )                                                       &&
	 ( ScatElec_Theta_Col        > 8.0   && ScatElec_Theta_Col        < 24.0 ) &&
	 ( Pion_Theta_Col            > 8.0   && Pion_Theta_Col            < 18.0 ) &&
	 ( RecoilProton_Theta_Col    > 8.0   && RecoilProton_Theta_Col    < 24.0 )
	  ) 
	{
		  
	  hQsqW->Fill( Qsq_GeV, W_GeV, EventWeight );
	  ht->Fill(T_GeV, EventWeight );
	  hw->Fill(W_GeV, EventWeight );
	  hq->Fill(Qsq_GeV, EventWeight );
	  hEps->Fill( Epsilon , EventWeight );
	  hWeight->Fill(EventWeight );
	  hSig->Fill( ZASigma_Lab );
	  
	  fCount4++;
	  fRate += EventWeight / fN;
		  
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
  canv->Divide(3,3);

  canv->cd(1);             hQsqW->Draw();
  canv->cd(2);             ht->Draw();
  canv->cd(3);             hw->Draw();
  canv->cd(4);             hq->Draw();
  canv->cd(5)->SetLogy();  hSig->Draw();
  canv->cd(6)->SetLogy();  hWeight->Draw();
  canv->cd(7);             hEps->Draw();

  canv->Update();
  canv->SaveAs("Kinematics.png");

  return;
}

