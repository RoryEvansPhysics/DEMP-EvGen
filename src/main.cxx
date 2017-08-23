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
    Output->Fill();
  }

  Output->Save();

  cout << "Successful Events: \t" << nSuccess << endl;
  cout << "Failed Events: \t\t" << nFail << endl;
  return 0;
}
