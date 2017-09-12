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
  int nEvents;
  cout << "Enter the number of events: " << endl;
  cin >> nEvents;

  WorkFile = new TFile("../data/output/test.root");

  double beamE_MeV = 11000;

  DEMPEvent* VertEvent = new DEMPEvent();
  SigmaCalc* Sig = new SigmaCalc(VertEvent);

  // Declare vertex particles
  Particle * VertBeamElec = new Particle(elec_mass_mev,
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
  VertScatElec->SetMass(elec_mass_mev);
  VertScatElec->SetPid(pid_elec);
  VertScatElec->SetName("VertScatElec");
  VertEvent->ScatElec = VertScatElec;

  Particle * VertProdPion = new Particle();
  VertProdPion->SetMass(pi_mass_mev);
  VertProdPion->SetPid(pid_pion);
  VertProdPion->SetName("VertProdPion");
  VertEvent->ProdPion = VertProdPion;

  Particle * VertProdProt = new Particle();
  VertProdProt->SetMass(proton_mass_mev);
  VertProdProt->SetPid(pid_prot);
  VertProdProt->SetName("VertProdProt");
  VertEvent->ProdProt = VertProdProt;

  double elecERange[2] = {0.1*beamE_MeV,0.9*beamE_MeV};
  double elecThetaRange[2] = {5/DEG, 25/DEG};
  double elecPhiRange[2] = {0, 360/DEG};

  ScatteredParticleGen * ElecGen =
    new ScatteredParticleGen(elec_mass_mev,
                             elecERange,
                             elecThetaRange,
                             elecPhiRange);

  Particle * Photon = new Particle();
  VertEvent->VirtPhot = Photon;

  ProductGen * ProtonPionGen = new ProductGen(Photon,
                                              VertTargNeut);

  int nSuccess = 0;
  int nFail = 0;

  int event_status = 0;

  TreeBuilder * Output = new TreeBuilder("Output");

  Output -> AddParticle(VertBeamElec);
  Output -> AddParticle(VertProdPion);
  Output -> AddParticle(VertProdProt);
  Output -> AddParticle(VertScatElec);
  Output -> AddParticle(VertTargNeut);

  double qsq_MeV, qsq_GeV;
  double t_MeV, t_GeV;
  double w_MeV, w_GeV;
  double s_MeV, s_GeV;

  double t_min_MeV, t_min_GeV;
  double t_prime_GeV;

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


  Output -> AddDouble(&qsq_GeV,"qsq_GeV");
  Output -> AddDouble(&w_GeV,"w_GeV");
  Output -> AddDouble(&t_GeV,"t_GeV");
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

    qsq_GeV = VertEvent->qsq_GeV();
    w_GeV = VertEvent->w_GeV();
    t_GeV = VertEvent->t_GeV();

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
    sigma_k5 = Sig->Sigma_k(5);

    Output->Fill();
  }


  Output->Save();

  cout << "Successful Events: \t" << nSuccess << endl;
  cout << "Failed Events: \t\t" << nFail << endl;
  return 0;
}
