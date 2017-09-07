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

//Project includes
#include "Particle.hxx"
#include "Frame.hxx"
#include "CustomRand.hxx"
#include "ScatteredParticleGen.hxx"
#include "ProductGen.hxx"
#include "TreeBuilder.hxx"
#include "Constants.hxx"
#include "SigmaL.hxx"
#include "SigmaT.hxx"
#include "SigmaTT.hxx"
#include "SigmaLT.hxx"

using namespace std;
using namespace constants;

TFile * WorkFile;

int main(){
  int nEvents;
  cout << "Enter the number of events: " << endl;
  cin >> nEvents;

  WorkFile = new TFile("../data/output/test.root");

  double beamE_MeV = 11000;

  // Declare vertex particles
  Particle * VertBeamElec = new Particle(elec_mass_mev,
                                         0, 0, beamE_MeV);
  VertBeamElec->SetPid(pid_elec);
  VertBeamElec->SetName("VertBeamElec");

  Particle * VertTargNeut = new Particle(neutron_mass_mev,
                                         0, 0, 0);
  VertTargNeut->SetPid(pid_neut);
  VertTargNeut->SetName("VertTargNeut");

  Particle * VertScatElec = new Particle();
  VertScatElec->SetMass(elec_mass_mev);
  VertScatElec->SetPid(pid_elec);
  VertScatElec->SetName("VertScatElec");

  Particle * VertProdPion = new Particle();
  VertProdPion->SetMass(pi_mass_mev);
  VertProdPion->SetPid(pid_pion);
  VertProdPion->SetName("VertProdPion");

  Particle * VertProdProt = new Particle();
  VertProdProt->SetMass(proton_mass_mev);
  VertProdProt->SetPid(pid_prot);
  VertProdProt->SetName("VertProdProt");


  double elecERange[2] = {0.1*beamE_MeV,0.9*beamE_MeV};
  double elecThetaRange[2] = {5/DEG, 25/DEG};
  double elecPhiRange[2] = {0, 360/DEG};

  ScatteredParticleGen * ElecGen =
    new ScatteredParticleGen(elec_mass_mev,
                             elecERange,
                             elecThetaRange,
                             elecPhiRange);

  Particle * Photon = new Particle();

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

  double sigma_l;
  double sigma_t;
  double sigma_tt;
  double sigma_lt;

  Output -> AddDouble(&qsq_GeV,"qsq_GeV");
  Output -> AddDouble(&w_GeV,"w_GeV");
  Output -> AddDouble(&t_GeV,"t_GeV");
  Output -> AddDouble(&sigma_l,"sigma_l");
  Output -> AddDouble(&sigma_t,"sigma_t");
  Output -> AddDouble(&sigma_tt,"sigma_tt");
  Output -> AddDouble(&sigma_lt,"sigma_lt");

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

    qsq_MeV = -(Photon->Mag2());
    qsq_GeV = qsq_MeV/1000000;

    w_MeV = (*Photon+*VertTargNeut).Mag();
    w_GeV = w_MeV/1000;

    t_MeV = (*Photon-*VertProdPion).Mag2();
    t_GeV = t_MeV/1000000;

    sigma_l = MySigmaL(qsq_GeV,-t_GeV,w_GeV);
    sigma_t = MySigmaT(qsq_GeV,-t_GeV,w_GeV);
    sigma_lt = MySigmaLT(qsq_GeV,-t_GeV,w_GeV);
    sigma_tt = MySigmaTT(qsq_GeV,-t_GeV,w_GeV);

    //cout << sigma_l << endl;

    Output->Fill();
  }

  Output->Save();

  cout << "Successful Events: \t" << nSuccess << endl;
  cout << "Failed Events: \t\t" << nFail << endl;
  return 0;
}
