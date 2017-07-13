#include "Particle.hxx"
#include "Asymmetry.hxx"
#include <iostream>
#include <string>

using namespace std;

int test(){
  Particle x;
  x.SetXYZT(1,1,1,1);
  cout << x.Theta()<< endl;

  
  char asyname[] = "asy";
  char func[] = "[0]+[1]*x";
  double y[2] = {4.107, 4.335};
  Asymmetry asy(asyname, func);
  
}
