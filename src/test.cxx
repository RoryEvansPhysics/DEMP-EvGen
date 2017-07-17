#include "Particle.cxx"
#include "Asymmetry.cxx"
#include <iostream>
#include <string>

using namespace std;

TFile * WorkFile;

int test(){
  Particle x;
  x.SetXYZT(1,1,1,1);
  x.SetPid(10);
  cout << x.Theta()<< endl;


  WorkFile = new TFile("../output/test.root");

  char asyname[] = "asy";
  char func[] = "[0]+[1]*x";
  const vector<double> y {4.107, 4.335};
  Asymmetry asy(asyname, func);


  return 0;
}
