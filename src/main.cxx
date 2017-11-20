//C++lib includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//Root includes
#include "TRandom.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TMath.h"
#include "TVector3.h"

//Project includes
#include "Particle.hxx"
#include "Frame.hxx"
#include "CustomRand.hxx"
#include "ScatteredParticleGen.hxx"
#include "ProductGen.hxx"
#include "TreeBuilder.hxx"
#include "Constants.hxx"
#include "DEMPEvent.hxx"
#include "SigmaCalc.hxx"

using namespace std;
using namespace constants;

TFile * WorkFile;

int main(){

  bool fermi = true;


  int nEvents;
  cout << "Enter the number of events: " << endl;
  cin >> nEvents;

  WorkFile = new TFile("../data/output/test.root");

  double beamE_MeV = 11000;

  DEMPEvent* VertEvent = new DEMPEvent();
  SigmaCalc* Sig = new SigmaCalc(VertEvent);

  // Declare vertex particles
  Particle * VertBeamElec = new Particle(electron_mass_mev,
                                         0, 0, beamE_MeV);
  VertBeamElec->SetPid(pid_elec);
  VertBeamElec->SetName("VertBeamElec");
  VertEvent->BeamElec = VertBeamElec;

  Particle * VertTargNeut = new Particle(neutron_mass_mev,
                                         0, 0, 0);
  VertTargNeut->SetPid(pid_neut);
  VertTargNeut->SetName("VertTargNeut");
  VertEvent->TargNeut = VertTargNeut;

  Particle * VertScatElec = new Particle();
  VertScatElec->SetMass(electron_mass_mev);
  VertScatElec->SetPid(pid_elec);
  VertScatElec->SetName("VertScatElec");
  VertEvent->ScatElec = VertScatElec;

  Particle * VertProdPion = new Particle();
  VertProdPion->SetMass(pion_mass_mev);
  VertProdPion->SetPid(pid_pion);
  VertProdPion->SetName("VertProdPion");
  VertEvent->ProdPion = VertProdPion;

  Particle * VertProdProt = new Particle();
  VertProdProt->SetMass(proton_mass_mev);
  VertProdProt->SetPid(pid_prot);
  VertProdProt->SetName("VertProdProt");
  VertEvent->ProdProt = VertProdProt;

  double elecERange[2] = {0.1*beamE_MeV,0.9*beamE_MeV};
  double elecThetaRange[2] = {6/DEG, 26/DEG};
  double elecPhiRange[2] = {0, 360/DEG};

  ScatteredParticleGen * ElecGen =
    new ScatteredParticleGen(electron_mass_mev,
                             elecERange,
                             elecThetaRange,
                             elecPhiRange);

  Particle * Photon = new Particle();
  VertEvent->VirtPhot = Photon;

  ProductGen * ProtonPionGen = new ProductGen(Photon,
                                              VertTargNeut);

  int nSuccess = 0;
  int nFail = 0;
  int nNeg = 0;

  int event_status = 0;

  TreeBuilder * Output = new TreeBuilder("Output");

  Output->AddEvent(VertEvent);

  double sigma_l;
  double sigma_t;
  double sigma_tt;
  double sigma_lt;

  double sigma_uu;
  double sigma_ut;

  double sigma_k0;
  double sigma_k1;
  double sigma_k2;
  double sigma_k3;
  double sigma_k4;

  double sigma_k5 = 0;

  double sigma;

  double weight;
  double epsilon;

  Output -> AddDouble(&sigma_l,"sigma_l");
  Output -> AddDouble(&sigma_t,"sigma_t");
  Output -> AddDouble(&sigma_tt,"sigma_tt");
  Output -> AddDouble(&sigma_lt,"sigma_lt");
  Output -> AddDouble(&sigma_uu,"sigma_uu");
  Output -> AddDouble(&sigma_ut,"sigma_ut");

  Output -> AddDouble(&sigma_k0,"sigma_k0");
  Output -> AddDouble(&sigma_k1,"sigma_k1");
  Output -> AddDouble(&sigma_k2,"sigma_k2");
  Output -> AddDouble(&sigma_k3,"sigma_k3");
  Output -> AddDouble(&sigma_k4,"sigma_k4");
  Output -> AddDouble(&sigma_k5,"sigma_k5");

  Output -> AddDouble(&sigma, "sigma");

  Output -> AddDouble(&weight,"weight");
  Output -> AddDouble(&epsilon, "epsilon");
  cout << "Starting Main Loop." << endl;

  for (int i=0; i<nEvents; i++){
    *VertScatElec = *ElecGen->GetParticle();
    *Photon = *VertBeamElec - *VertScatElec;
    event_status = ProtonPionGen->Solve();
    if (event_status == 0)
      nSuccess ++;
    if (event_status == 1){
      nFail ++;
      continue;
    }
    *VertProdPion = *ProtonPionGen->ProdPion();
    *VertProdProt = *ProtonPionGen->ProdProton();
    //    cout<<VertProdPion->GetPid() << endl;


    VertEvent->Update();

    sigma_l = Sig->sigma_l();
    sigma_t = Sig->sigma_t();
    sigma_lt = Sig->sigma_lt();
    sigma_tt = Sig->sigma_tt();
    sigma_uu = Sig->sigma_uu();
    sigma_ut = Sig->sigma_ut();

    sigma_k0 = Sig->Sigma_k(0);
    sigma_k1 = Sig->Sigma_k(1);
    sigma_k2 = Sig->Sigma_k(2);
    sigma_k3 = Sig->Sigma_k(3);
    sigma_k4 = Sig->Sigma_k(4);

    sigma = Sig->sigma();

<<<<<<< HEAD
    if (sigma<0) nNeg ++;
=======
    //if (sigma<0) continue;
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros

    weight = Sig->weight(nEvents);

    Output->Fill();
  }

  if (nSuccess>0)
    Output->Save();

  cout << "Successful Events: \t" << nSuccess << endl;
  cout << "Failed Events: \t\t" << nFail << endl;
  cout << "Negative Events: \t\t" << nNeg << endl;

  // Debug/Checks:

  if(nEvents == -1){

    cout << "Running Debug/Check Values" << endl;

<<<<<<< HEAD
    VertScatElec->SetThetaPhiE(22.1792/DEG, 58.8528/DEG, 4130.68);
=======
    VertScatElec->SetThetaPhiE(8.25269/DEG, 76.8565/DEG, 5786.06);
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros
    *Photon = *VertBeamElec - *VertScatElec;

    ProtonPionGen->Solve(13.326/DEG,239.229/DEG);

    *VertProdPion = *ProtonPionGen->ProdPion();
    *VertProdProt = *ProtonPionGen->ProdProton();

    VertEvent->Update();

    double qsq_GeV = *VertEvent->qsq_GeV;
    double w_GeV = *VertEvent->w_GeV;
    double t_GeV = *VertEvent->t_GeV;
    double t_prime_GeV = *VertEvent->t_prime_GeV;
    double phi = *VertEvent->Phi;
    double phi_s = *VertEvent->Phi_s;
    double theta = *VertEvent->Theta;

    sigma_l = Sig->sigma_l();
    sigma_t = Sig->sigma_t();
    sigma_lt = Sig->sigma_lt();
    sigma_tt = Sig->sigma_tt();
    sigma_uu = Sig->sigma_uu();
    sigma_ut = Sig->sigma_ut();

    sigma_k0 = Sig->Sigma_k(0);
    sigma_k1 = Sig->Sigma_k(1);
    sigma_k2 = Sig->Sigma_k(2);
    sigma_k3 = Sig->Sigma_k(3);
    sigma_k4 = Sig->Sigma_k(4);

    sigma = Sig->sigma();

    cout << "ElecE:\t" << VertScatElec->E()/1000 << endl;
    cout << "ElecTh:\t"<<VertScatElec->Theta()*DEG << endl;
    cout << "ElecPhi:\t"<<VertScatElec->Phi()*DEG << endl;

    cout << "PionE:\t"<<VertProdPion->E()/1000 << endl;
    cout << "PionTh:\t"<<VertProdPion->Theta()*DEG << endl;
    cout << "PionPhi:\t"<<VertProdPion->Phi()*DEG << endl;

    cout << "ProtE:\t"<<VertProdProt->E()/1000 << endl;
    cout << "ProtTh:\t"<<VertProdProt->Theta()*DEG << endl;
    cout << "ProtPhi:\t"<<VertProdProt->Phi()*DEG << endl;

    cout << "Qsq:\t" << qsq_GeV << endl;
    cout << "W:\t" << w_GeV << endl;
    cout << "t:\t" << t_GeV << endl;
    cout << "t\':\t"<< t_prime_GeV << endl;
    cout << "Phi:\t"<< phi << endl;
    cout << "Phi_s:\t"<< phi_s << endl;
    cout << "Theta: \t" << theta << endl;
    cout << endl;

    cout <<"sigma:\t"<< sigma << endl;
    cout <<"sigma_l:\t"<< sigma_l << endl;
    cout <<"sigma_t:\t"<< sigma_t << endl;
    cout <<"sigma_lt:\t"<< sigma_lt << endl;
    cout <<"sigma_tt:\t"<< sigma_tt << endl;
    cout <<"sigma_uu:\t"<< sigma_uu << endl;
    cout <<"sigma_ut:\t"<< sigma_ut << endl;
    cout <<"AsyP-Ps:\t"<< sigma_k0 << endl;
    cout <<"AsyPs:\t"<< sigma_k1 << endl;
    cout <<"Asy2P-Ps:\t"<< sigma_k2 << endl;
    cout <<"AsyP+Ps:\t"<< sigma_k3 << endl;
    cout <<"Asy3P-Ps:\t"<< sigma_k4 << endl;
    cout <<"Asy2P_Ps:\t"<< sigma_k5 << endl;
    cout <<"Epsilon: \t"<< Sig->epsilon() << endl;

    // Sig->Asyms->at(0)->PrintPars();

  }



  return 0;
}
