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

using namespace std;

TFile * WorkFile;

int main(){
  int nEvents;
  cout << "Enter the number of events: " << endl;
  cin >> nEvents;

  double DEG = 180/TMath::Pi();

  WorkFile = new TFile("../data/output/test.root");

  double beamE_MeV = 11000;

  Particle * ScatElectron;

  double elecMassMeV = 0.511;
  double elecERange[2] = {0.1*beamE_MeV,0.9*beamE_MeV};
  double elecThetaRange[2] = {5/DEG, 25/DEG};
  double elecPhiRange[2] = {0, 360/DEG};

  ScatteredParticleGen * ElecGen =
    new ScatteredParticleGen(elecMassMeV,
                             elecERange,
                             elecThetaRange,
                             elecPhiRange);
  Particle * BeamParticle =
    new Particle(0.511, 0, 0, beamE_MeV);

  Particle * TargetParticle =
    new Particle(940, 0, 0, 0);

  ProductGen * ProtonPionGen = new ProductGen();
  ProtonPionGen->SetIncident(BeamParticle);
  ProtonPionGen->SetTarget(TargetParticle);

  Particle * ProdProton;
  Particle * ProdPion;

  for (int i=0; i<nEvents; i++){
    ScatElectron = ElecGen->GetParticle();
    // cout << ScatElectron->Px() << '\t'
    //      << ScatElectron->Py() << '\t'
    //      << ScatElectron->Pz() << '\t'
    //      << endl;
    ProtonPionGen->Solve(ScatElectron);
    //ProtonPionGen->PrintPars();
    ProdPion = ProtonPionGen->ProdPion();
    ProdProton = ProtonPionGen->ProdProton();

    //    ProtonPionGen->PrintPars();

    cout << "Initial Energy: "
      << BeamParticle->E()+TargetParticle->E() << endl
      << "Final Energy: "
      << ProdPion->E()+ProdProton->E()+ScatElectron->E() << endl
      << "Difference: "
      << BeamParticle->E()+TargetParticle->E() -
      (ProdPion->E()+ProdProton->E()+ScatElectron->E()) << endl;
      }

      return 0;
}
