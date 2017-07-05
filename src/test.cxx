#include "Particle.hxx"
#include <iostream>

using namespace std;

int test(){
  Particle x;
  x.SetXYZT(1,1,1,1);
  cout << x.Theta()<< endl;;
  return 0;
}
