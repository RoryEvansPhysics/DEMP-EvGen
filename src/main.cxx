//C++lib includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//Root includes
#include "TRandom.h"
#include "TFile.h"

//Project includes
#include "Particle.hxx"
#include "Frame.hxx"

using namespace std;

TFile * WorkFile;

int main(){
  int nEvents;
  cout << "Enter the number of events: " << endl;
  cin >> nEvents;

  WorkFile = new TFile("../data/output/test.root");

  for (int i = 0; i<nEvents; i++){
    Frame * f = Frame::RandFrame();
    cout << f->Electron->Px() << "\t";
    cout << f->Pion->Px() << "\t";
    cout << f->Proton->Px() << endl;
  }
}
