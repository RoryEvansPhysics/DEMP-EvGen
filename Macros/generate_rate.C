  /*C/C++ Includes{{{*/
  #include <stdio.h>
  #include <string>
  #include <iostream>
  #include <fstream>
  #include <vector>
  #include <algorithm>
  #include <map>
  #include <cmath>
  /*}}}*/
	
  /*ROOT Includes{{{*/
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
  //#include <TMatrix.h>
  /*}}}*/

#include "SIDIS_Acceptance.h"
const double MeV2GeV=0.001;
using namespace std;


void generate_rate(){
	gStyle->SetOptStat(0);

	const double Lumi = 1.0e36; // cm-2*s-1, for He3 nuclear not for nucleons
	const double KHz = 1e-3;
	const double nBcm2 = 1e-33;
    const double PI = 3.1415926;
    const double DEG2RAD = PI/180.0;
	const TString Target = "He3";
    const TString particle="pim";
	
    const Double_t EBeam = 11.0;
    const double Ratio = 20.7598; //11GeV
    //TFile* f1=new TFile("./RootFiles/SoLID_Excl_Targ_N_Ee_11_Events_20e6.root","r");
	
    //const Double_t EBeam = 11;
    //const double Ratio = 25.1826; //8.8GeV
    TFile* f1=new TFile("../build/Output.root","r");
    
	/*Define Rootfile and variables{{{*/
    int energy_flag =int(EBeam);//GeV
    TTree* t1 = (TTree*) f1->Get("Output");

    Double_t Epsilon, Qsq, T, W, x, y, z, ZASig_L, ZASig_T, ZASigmaPara;
    Double_t Neutron_Energy_Col,Neutron_MomX_Col,Neutron_MomY_Col,Neutron_MomZ_Col,Neutron_Mom_Col; 
    Double_t Neutron_Phi_Col,Neutron_Theta_Col;
    Double_t ScatElec_Energy_Col,ScatElec_MomX_Col,ScatElec_MomY_Col,ScatElec_MomZ_Col,ScatElec_Mom_Col; 
    Double_t ScatElec_Phi_Col,ScatElec_Theta_Col;
    Double_t Pion_Energy_Col,Pion_MomX_Col,Pion_MomY_Col,Pion_MomZ_Col,Pion_Mom_Col; 
    Double_t Pion_Phi_Col,Pion_Theta_Col;
    Double_t weight;

    t1->SetBranchAddress("epsilon", &Epsilon );
    t1->SetBranchAddress("qsq_GeV", &Qsq );
    t1->SetBranchAddress("negt", &T );
    t1->SetBranchAddress("w_GeV", &W );
    t1->SetBranchAddress("x_B", &x );
    t1->SetBranchAddress("Vertex_y", &y );
    t1->SetBranchAddress("Vertex_z", &z );
    t1->SetBranchAddress("sigma_l", &ZASig_L );
    t1->SetBranchAddress("sigma_t", &ZASig_T );
    t1->SetBranchAddress("sigma", &ZASigmaPara );
    t1->SetBranchAddress("weight", &weight);

    t1->SetBranchAddress("VertProdProt_E", &Neutron_Energy_Col );
    t1->SetBranchAddress("VertProdProt_Px", &Neutron_MomX_Col );
    t1->SetBranchAddress("VertProdProt_Py", &Neutron_MomY_Col );
    t1->SetBranchAddress("VertProdProt_Pz", &Neutron_MomZ_Col );
    t1->SetBranchAddress("VertProdProt_P", &Neutron_Mom_Col );
    t1->SetBranchAddress("VertProdProt_theta", &Neutron_Theta_Col );
    t1->SetBranchAddress("VertProdProt_phi", &Neutron_Phi_Col);

    t1->SetBranchAddress("VertScatElec_E", &ScatElec_Energy_Col );
    t1->SetBranchAddress("VertScatElec_Px", &ScatElec_MomX_Col );
    t1->SetBranchAddress("VertScatElec_Py", &ScatElec_MomY_Col );
    t1->SetBranchAddress("VertScatElec_Pz", &ScatElec_MomZ_Col );
    t1->SetBranchAddress("VertScatElec_P", &ScatElec_Mom_Col );
    t1->SetBranchAddress("VertScatElec_theta", &ScatElec_Theta_Col );
    t1->SetBranchAddress("VertScatElec_phi", &ScatElec_Phi_Col );
	
    t1->SetBranchAddress("VertProdPion_E", &Pion_Energy_Col );
    t1->SetBranchAddress("VertProdPion_Px", &Pion_MomX_Col );
    t1->SetBranchAddress("VertProdPion_Py", &Pion_MomY_Col );
    t1->SetBranchAddress("VertProdPion_Pz", &Pion_MomZ_Col );
    t1->SetBranchAddress("VertProdPion_P", &Pion_Mom_Col );
    t1->SetBranchAddress("VertProdPion_theta", &Pion_Theta_Col );
    t1->SetBranchAddress("VertProdPion_phi", &Pion_Phi_Col );
    /*}}}*/

	Long64_t N_entries=t1->GetEntries();
    Long64_t N_Total = N_entries * Ratio; 
    //CLEO
    SIDIS_Acceptance *accpt = new SIDIS_Acceptance();
    cout<<"A"<<endl;
	/*Define Histograms{{{*/
	int Nbinx=80;
	int Nbiny=80;
	int Nbin_theta=80;
	int Nbin_p=90;

	/*Kinematics Variables{{{*/
	//_________w vs t 
	//forward angle
	TH2F *hf_t_w=new TH2F("hf_t_w","t vs. w (forward angle) ",Nbinx,1.5,4.5,Nbiny,0.0,1.3);
	hf_t_w->GetXaxis()->SetTitle("W (GeV)");
	hf_t_w->GetYaxis()->SetTitle("t (GeV^{2})");
	//large angle
	TH2F *hl_t_w=new TH2F("hl_t_w","t vs. w (large angle) ",Nbinx,1.5,4.5,Nbiny,0.0,1.3);
    hl_t_w->GetXaxis()->SetTitle("W (GeV)");
	hl_t_w->GetYaxis()->SetTitle("t (GeV^{2})");
	//total
	TH2F *h_t_w=new TH2F("h_t_w","t vs. w (large+forward angles) ",Nbinx,1.5,4.5,Nbiny,0.0,1.3);
	h_t_w->GetXaxis()->SetTitle("W (GeV)");
	h_t_w->GetYaxis()->SetTitle("t (GeV^{2})");

	//______Q2 vs x 
	//forward angle
	TH2F *hf_Q2_x=new TH2F("hf_Q2_x","Q^{2} vs. x (forward)",Nbinx,0,0.7,Nbiny,0,10);
	hf_Q2_x->GetXaxis()->SetTitle("x_{bj}");
	hf_Q2_x->GetYaxis()->SetTitle("Q^2(GeV^{2})");
	//large angle
	TH2F *hl_Q2_x=new TH2F("hl_Q2_x","Q^{2} vs. x (large angle)",Nbinx,0,0.7,Nbiny,0,10);
	hl_Q2_x->GetXaxis()->SetTitle("x_{bj}");
	hl_Q2_x->GetYaxis()->SetTitle("Q^2(GeV^{2})");
	//total
	TH2F *h_Q2_x=new TH2F("h_Q2_x","Q^{2} vs. x (large+forward angles)",Nbinx,0,0.7,Nbiny,0,10);
	h_Q2_x->GetXaxis()->SetTitle("x_{bj}");
	h_Q2_x->GetYaxis()->SetTitle("Q^2(GeV^{2})");
    /*}}}*/

	/*electron{{{*/
	/*_____p vs theta for e{{{*/
	TH2F *ef_p_theta=new TH2F("ef_p_theta","P_{e-} vs. #theta_{e-}  (forward angle)",Nbin_theta,6.0,26.0,Nbin_p,0,10.0);
	//forward angle
	ef_p_theta->GetYaxis()->SetTitle("P_{e-}");
	ef_p_theta->GetXaxis()->SetTitle("#theta_{e-}");
	//large angle
	TH2F *el_p_theta=new TH2F("el_p_theta","P_{e-} vs. #theta_{e-} (large angle)",Nbin_theta,6.0,26.0,Nbin_p,0,10.0);
	el_p_theta->GetYaxis()->SetTitle("P_{e-}");
	el_p_theta->GetXaxis()->SetTitle("#theta_{e-}");
	//total
	TH2F *e_p_theta=new TH2F("e_p_theta","P_{e-} vs. #theta_{e-} (large+forward angle)",Nbin_theta,6.0,26.0,Nbin_p,0,10.0);
	e_p_theta->GetYaxis()->SetTitle("P_{e-}");
	e_p_theta->GetXaxis()->SetTitle("#theta_{e-}");
    /*}}}*/

	/*_____TH1F of theta for e{{{*/
	//forward angle
	TH1F *ef_theta=new TH1F("ef_theta","rate as function of #theta_{e-}  (forward angle)",Nbin_theta,6.0,26.0);
	ef_theta->GetYaxis()->SetTitle("rate (Hz)");
	ef_theta->GetXaxis()->SetTitle("#theta_{e-}");
	//large angle
	TH1F *el_theta=new TH1F("el_theta","rate as function of #theta_{e-} (large angle)",Nbin_theta,6.0,26.0);
	el_theta->GetYaxis()->SetTitle("rate (Hz)");
	el_theta->GetXaxis()->SetTitle("#theta_{e-}");
	//total
	TH1F *e_theta=new TH1F("e_theta","rate as function of #theta_{e-} (large+forward angle)",Nbin_theta,6.0,26.0);
	e_theta->GetYaxis()->SetTitle("rate (Hz)");
	e_theta->GetXaxis()->SetTitle("#theta_{e-}");
    /*}}}*/

	/*_____TH1F of p e{{{*/
	//forward angle
	TH1F *ef_p=new TH1F("ef_p","rate as function of P_{e-}  (forward angle)",Nbin_p,0.0,10.0);
	ef_p->GetYaxis()->SetTitle("rate (Hz)");
	ef_p->GetXaxis()->SetTitle("P_{e-}");
	//large angle
	TH1F *el_p=new TH1F("el_p","rate as function of P_{e-} (large angle)",Nbin_p,0.0,10.0);
	el_p->GetYaxis()->SetTitle("rate (Hz)");
	el_p->GetXaxis()->SetTitle("p_{e-}");
	//total
	TH1F *e_p=new TH1F("e_p","rate as function of p_{e-} (large+forward angle)",Nbin_p,0.0,10.0);
	e_p->GetYaxis()->SetTitle("rate (Hz)");
	e_p->GetXaxis()->SetTitle("P_{e-}");
    /*}}}*/
    
	/*}}}*/

	/*pion{{{*/
	/*_____p vs theta for pi-{{{*/
	TH2F *pf_p_theta=new TH2F("pf_p_theta",Form("P_{%s} vs. #theta_{%s}  (forward angle)",particle.Data(),particle.Data()),Nbin_theta,6.0,26.0,Nbin_p,0,10.);
	//forward angle
	pf_p_theta->GetYaxis()->SetTitle("P_{#pi-}");
	pf_p_theta->GetXaxis()->SetTitle("#theta_{#pi-}");
	//large angle
	TH2F *pl_p_theta=new TH2F("pl_p_theta",Form("P_{%s} vs. #theta_{%s}  (large angle)",particle.Data(),particle.Data()),Nbin_theta,6.0,26.0,Nbin_p,0,10.);
	pl_p_theta->GetYaxis()->SetTitle("P_{#pi-}");
	pl_p_theta->GetXaxis()->SetTitle("#theta_{#pi-}");
    //total
	TH2F *p_p_theta=new TH2F("p_p_theta",Form("P_{%s} vs. #theta_{%s}  (large+forward angle)",particle.Data(),particle.Data()),Nbin_theta,6.0,26.0,Nbin_p,0,10.);
	p_p_theta->GetYaxis()->SetTitle("P_{#pi-}");
	p_p_theta->GetXaxis()->SetTitle("#theta_{#pi-}");
    /*}}}*/
    
	/*_____TH1F of theta for pi-{{{*/
	//forward angle
	TH1F *pf_theta=new TH1F("pf_theta",Form("rate as function of #theta_{%s}  (forward angle)",particle.Data()),Nbin_theta,6.0,26.0);
	pf_theta->GetYaxis()->SetTitle("rate (Hz)");
	pf_theta->GetXaxis()->SetTitle("#theta_{pi-}");
	//large angle
	TH1F *pl_theta=new TH1F("pl_theta",Form("rate as function of #theta_{%s}  (large angle)",particle.Data()),Nbin_theta,6.0,26.0);
	pl_theta->GetYaxis()->SetTitle("rate (Hz)");
	pl_theta->GetXaxis()->SetTitle("#theta_{pi-}");
	//total
	TH1F *p_theta=new TH1F("p_theta",Form("rate as function of #theta_{%s}  (large+forward angle)",particle.Data()),Nbin_theta,6.0,26.0);
	p_theta->GetYaxis()->SetTitle("rate (Hz)");
	p_theta->GetXaxis()->SetTitle("#theta_{pi-}");
    /*}}}*/

	/*_____TH1F of p for pi-{{{*/
	//forward angle
	TH1F *pf_p=new TH1F("pf_p",Form("rate as function of P_{%s}  (forward angle)",particle.Data()),Nbin_p,0.0,10.);
	pf_p->GetYaxis()->SetTitle("rate (Hz)");
	pf_p->GetXaxis()->SetTitle("P_{N}");
	//large angle
	TH1F *pl_p=new TH1F("pl_p",Form("rate as function of P_{%s}  (forward angle)",particle.Data()),Nbin_p,0.0,10.);
	pl_p->GetYaxis()->SetTitle("rate (Hz)");
	pl_p->GetXaxis()->SetTitle("P_{N}");
	//total
	TH1F *p_p=new TH1F("p_p",Form("rate as function of P_{%s}  (large+forward angle)",particle.Data()),Nbin_p,0.0,10.);
	p_p->GetYaxis()->SetTitle("rate (Hz)");
	p_p->GetXaxis()->SetTitle("P_{N}");
	/*}}}*/
    
	/*}}}*/
	/*}}}*/
	
	double ele_rate_forward=0;
	double ele_rate_large=0;
	double pim_rate_forward=0;
	double pim_rate_large=0;
	double rate_forward=0;
	double rate_large=0;
	double total_rate=0;
    double PSF =(EBeam*0.9-EBeam*0.1) * (28.0-5.0)*DEG2RAD * 2*PI
               *(EBeam*0.9-EBeam*0.1) * (60.0-0.0)*DEG2RAD * 2*PI;
    for(Long64_t i=0;i<N_entries;i++){
		t1->GetEntry(i);

        // ScatElec_Mom_Col*=MeV2GeV;//into GeV
        // Neutron_Mom_Col*=MeV2GeV;//into GeV
        // Pion_Mom_Col*=MeV2GeV;//into GeV
        // Qsq *= MeV2GeV * MeV2GeV;
        // T *= MeV2GeV * MeV2GeV;
        // W *= MeV2GeV;

        if(ScatElec_Theta_Col>8&&ScatElec_Theta_Col<24&&ScatElec_Mom_Col>1.&&ScatElec_Mom_Col<11
          &&Pion_Theta_Col>8&&Pion_Theta_Col<16&&Pion_Mom_Col>1.&&Pion_Mom_Col<11
           &&Qsq>4.0&&ZASigmaPara>1e-33&&W>2&&Neutron_Theta_Col>8&&Neutron_Theta_Col<24
           &&Neutron_Mom_Col>0.5){//any additional cuts should be added in here
            /*Get acceptance of e and pi-{{{*/

            double ele_forward_acceptance = accpt->GetAcc("e-","forward", ScatElec_Mom_Col, ScatElec_Theta_Col);
            double ele_large_acceptance = accpt->GetAcc("e-","large", ScatElec_Mom_Col, ScatElec_Theta_Col);
			if(ScatElec_Mom_Col<1.0||ScatElec_Theta_Col>14.5||ScatElec_Theta_Col<8.0)//GeV, CLEO
				ele_forward_acceptance=0.0;//Farward-Angle EC Cut at 1 GeV
			if(ScatElec_Mom_Col<3.5||ScatElec_Theta_Col<16.0||ScatElec_Theta_Col>24)//GeV,CLEO
				ele_large_acceptance=0.0; //Larger-Angle EC Cut at 3 GeV
			if(ele_forward_acceptance>1.) 
				ele_forward_acceptance=1.0; 
			if(ele_large_acceptance>1.) 
				ele_large_acceptance=1.0; 

            double pim_forward_acceptance = accpt->GetAcc("pi-","forward", Pion_Mom_Col, Pion_Theta_Col);
            double pim_large_acceptance = accpt->GetAcc("pi-","large", Pion_Mom_Col, Pion_Theta_Col);
            if(Pion_Theta_Col>14.8||Pion_Theta_Col<8.0||Pion_Mom_Col<1.||Pion_Mom_Col>11.)//GeV, CLEO
                pim_forward_acceptance=0.0;
			if(Pion_Theta_Col<16.0||Pion_Theta_Col>24.0||Pion_Mom_Col<3.5||Pion_Mom_Col>11.)//GeV, CLEO
				pim_large_acceptance=0.0; 
			if(pim_forward_acceptance>1.) 
				pim_forward_acceptance=1.0; 
			if(pim_large_acceptance>1.) 
				pim_large_acceptance=1.0; 
            
            //double event_weight=ZASigmaPara*PSF/N_Total*nBcm2*Lumi ;   //in Hz
            double event_weight = weight;

			double ele_acceptance=(ele_forward_acceptance+ele_large_acceptance);
			double pim_acceptance=(pim_large_acceptance+pim_forward_acceptance);
			double forward_acceptance=ele_forward_acceptance*pim_acceptance;
			double large_acceptance=ele_large_acceptance*pim_acceptance;
			double total_acceptance=ele_acceptance*pim_acceptance;
            /*}}}*/

            /*Rates{{{*/	
            ele_rate_forward+=event_weight*ele_forward_acceptance;
            ele_rate_large+=event_weight*ele_large_acceptance;
            pim_rate_forward+=event_weight*pim_forward_acceptance;
            pim_rate_large+=event_weight*pim_large_acceptance;

            rate_forward+=event_weight*forward_acceptance;
            rate_large+=event_weight*large_acceptance;
            total_rate+=event_weight*total_acceptance;
    /*        cerr<<Form("--- eP=%f, eTheta=%f, pP=%f, pTheta=%f", ScatElec_Mom_Col,ScatElec_Theta_Col, Pion_Mom_Col,Pion_Theta_Col)<<endl;*/
            //cerr<<Form("--- weight=%f, ef_acc=%f, pf_acc=%f", event_weight, ele_forward_acceptance,pim_forward_acceptance)<<endl;
            //cerr<<Form("--- weight=%f, el_acc=%f, pl_acc=%f", event_weight, ele_large_acceptance,pim_large_acceptance)<<endl;

            /*}}}*/
            //event_weight=1./N_Total;
            //forward_acceptance = 1.0;
            //large_acceptance = 1.0;
            //total_acceptance = 1.0;
			/*fill histogram here{{{*/
            /*Kinematics{{{*/
			//T vs W
			hf_t_w->Fill(W,T,event_weight*forward_acceptance );
			hl_t_w->Fill(W,T,event_weight*large_acceptance );
			h_t_w->Fill( W,T,event_weight*total_acceptance );
			//Q2 vs x
			hf_Q2_x->Fill(x,Qsq,event_weight*forward_acceptance );
			hl_Q2_x->Fill(x,Qsq,event_weight*large_acceptance );
			h_Q2_x->Fill( x,Qsq,event_weight*total_acceptance );
            /*}}}*/

            /*Electrons{{{*/
			//p vs theta e
			ef_p_theta->Fill(ScatElec_Theta_Col,ScatElec_Mom_Col,event_weight*forward_acceptance );
			el_p_theta->Fill(ScatElec_Theta_Col,ScatElec_Mom_Col,event_weight*large_acceptance );
			e_p_theta->Fill( ScatElec_Theta_Col,ScatElec_Mom_Col,event_weight*total_acceptance );
			//TH1F theta
			ef_theta->Fill(ScatElec_Theta_Col,event_weight*forward_acceptance );
			el_theta->Fill(ScatElec_Theta_Col,event_weight*large_acceptance );
			e_theta->Fill( ScatElec_Theta_Col,event_weight*total_acceptance );
			//TH1F p
			ef_p->Fill(ScatElec_Mom_Col,event_weight*forward_acceptance );
			el_p->Fill(ScatElec_Mom_Col,event_weight*large_acceptance );
			e_p->Fill( ScatElec_Mom_Col,event_weight*total_acceptance );
           /*}}}*/

            /*Pions{{{*/
			//p vs theta g
			pf_p_theta->Fill(Pion_Theta_Col,Pion_Mom_Col, event_weight*forward_acceptance );
			pl_p_theta->Fill(Pion_Theta_Col,Pion_Mom_Col, event_weight*large_acceptance );
			p_p_theta->Fill( Pion_Theta_Col,Pion_Mom_Col, event_weight*total_acceptance );
			//TH1F theta
			pf_theta->Fill(Pion_Theta_Col,event_weight*forward_acceptance );
			pl_theta->Fill(Pion_Theta_Col,event_weight*large_acceptance );
			p_theta->Fill( Pion_Theta_Col,event_weight*total_acceptance );
			//TH1F p
			pf_p->Fill(Pion_Mom_Col,event_weight*forward_acceptance );
			pl_p->Fill(Pion_Mom_Col,event_weight*large_acceptance );
			p_p->Fill( Pion_Mom_Col,event_weight*total_acceptance );
            /*}}}*/

			/*}}}*/
		}

	}// events loop ends here

	/*Save Histo{{{*/
    TString outputfilename=Form("E_n_%dGeV.root", energy_flag);
    TFile *fout = new TFile(outputfilename.Data(),"recreate");
    fout->cd();
	h_t_w->Write();
	h_Q2_x->Write();
	//hf_t_w->Write();
	hf_Q2_x->Write();
	hl_t_w->Write();
	hl_Q2_x->Write();
	
	ef_p_theta->Write();
	ef_theta->Write();
	ef_p->Write();
	el_p_theta->Write();
	el_theta->Write();
	el_p->Write();
	e_p_theta->Write();
	e_theta->Write();
	e_p->Write();

	pf_p_theta->Write();
	pl_p_theta->Write();
	p_p_theta->Write();
	pf_theta->Write();
	pl_theta->Write();
	p_theta->Write();
	pf_p->Write();
	pl_p->Write();
	p_p->Write();
   	fout->Close();
	/*}}}*/

	/*Print&Save{{{*/
	ofstream outf(Form("%s_%d_he3_rate.dat", particle.Data(), energy_flag));

	outf<<"______Single integral rate (Hz)____________________"<<endl;
	outf<<"eletron rate_forward: "<<ele_rate_forward<<endl;
	outf<<"eletron rate_large: "<<ele_rate_large<<endl;
	outf<<"pimton rate_forward: "<<pim_rate_forward<<endl;
	outf<<"pimton rate_large: "<<pim_rate_large<<endl;

	outf<<"______forward and large angle integral rate____________________"<<endl;
	outf<<"rate_forward: "<<rate_forward<<endl;
	outf<<"rate_large: "<<rate_large<<endl;

	outf<<"______electron and pion coincidence rate____________________"<<endl;
	outf<<"rate: "<<total_rate<<endl;
	/*}}}*/

	/*Plot-New{{{*/
	/*Kinematics{{{*/
    TCanvas *can_forward=new TCanvas("can_forward","forward angle", 800,500);
    gPad->SetLogz(1);
    can_forward->Divide(2,1);
    can_forward->cd(1);
    hf_t_w->Draw("colz");
    can_forward->cd(2);
    hf_Q2_x->Draw("colz");
    can_forward->Print(Form("CLEO_%s_%d_Forward.png", particle.Data(),energy_flag));
    can_forward->Print(Form("CLEO_%s_%d_Forward.pdf", particle.Data(),energy_flag));

    TCanvas *can_large=new TCanvas("can_large","large angle", 800,500);
    gPad->SetLogz(1);
    can_large->Divide(2,1);
    can_large->cd(1);
    hl_t_w->Draw("colz");
    can_large->cd(2);
    hl_Q2_x->Draw("colz");
    can_large->Print(Form("CLEO_%s_%d_Large.png", particle.Data(),energy_flag));
    can_large->Print(Form("CLEO_%s_%d_Large.pdf", particle.Data(),energy_flag));

    TCanvas *can_total=new TCanvas("can_total","total", 800,500);
    gPad->SetLogz(1);
    can_total->Divide(2,1);
    can_total->cd(1);
    hf_t_w->Draw("");
    hl_t_w->SetMarkerColor(8); hl_t_w->Draw("same");
    can_total->cd(2);
    hf_Q2_x->Draw();
    hl_Q2_x->SetMarkerColor(8); hl_Q2_x->Draw("same");
    can_total->Print(Form("CLEO_%s_%d_Total.png", particle.Data(), energy_flag));
    can_total->Print(Form("CLEO_%s_%d_Total.pdf", particle.Data(), energy_flag));
   
    TCanvas *can_e=new TCanvas("can_e","Electron&Pion", 800,600);
    gPad->SetLogz(1);
    can_e->Divide(3,2);
    can_e->cd(1);
    e_p_theta->Draw("colz");
    can_e->cd(4);
    p_p_theta->Draw("colz");
    can_e->cd(2);
    e_p->Draw("colz");
    can_e->cd(5);
    p_p->Draw("colz");
    can_e->cd(3);
    e_theta->Draw("colz");
    can_e->cd(6);
    p_theta->Draw("colz");
    can_e->Print(Form("CLEO_%s_%d_Total2.png", particle.Data(), energy_flag));
    can_e->Print(Form("CLEO_%s_%d_Total2.pdf", particle.Data(), energy_flag));
    /*}}}*/

    delete accpt;
    f1->Close();

}

