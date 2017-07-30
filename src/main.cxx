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

  for (int i=0; i<nEvents; i++){
    ScatElectron = ElecGen->GetParticle();
    cout << ScatElectron->Px() << '\t'
         << ScatElectron->Py() << '\t'
         << ScatElectron->Pz() << '\t'
         << endl;
      }

  return 0;
}
