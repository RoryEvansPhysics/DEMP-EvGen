#include "Particle.cxx"
#include "Asymmetry.cxx"
#include <iostream>
#include <string>

using namespace std;

TFile * WorkFile;

int test(){
  Particle* x = new Particle();
  x->SetXYZT(1,1,1,1);
  x->SetPid(10);
  cout << x->Theta()<< endl;

  Particle* y = new Particle(.5, 0, 0, 12000);

  Particle* z = new Particle(900, *x, *y);

  cout << y->Pz() << endl;
  cout << z->Pz() << endl;

  // WorkFile = new TFile("../output/test.root");

  // char asyname[] = "asy";
  // char func[] = "[0]+[1]*x";
  // Asymmetry * asy = new Asymmetry(asyname, func);

  // cout << asy->GetAsyAmp(4, 1) << endl;
  // cout << asy->GetAsyAmp(5, 1) << endl;
  // cout << asy->GetAsyAmp(12, 1)<< endl;

  return 0;
}
