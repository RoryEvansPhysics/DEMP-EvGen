//C++lib includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//Root includes
#include "TRandom.h"

//Project includes
#include "Particle.cxx"
#include "Frame.cxx"

int main(){
  int nEvents;
  cout << "Enter the number of events: " << endl;
  cin >> nEvents;

  for (int i = 0; i<nEvents; i++){
    Frame * f = Frame::RandFrame();
    cout << f->Electron->Px() << "\t";
    cout << f->Pion->Px() << "\t";
    cout << f->Proton->Px() << endl;
  }
}
