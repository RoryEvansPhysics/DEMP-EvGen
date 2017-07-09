/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Class to contain all information on each particle in the event.
Includes: TLorentz vector with momenta information.
          Charge, PID, etc.
	  Access functions for E, theta, etc.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Particle_H
#define Particle_H

#include "TLorentzVector.h"

class Particle:public TLorentzVector
{
  int pid;
  int charge;
  double mass;

public:
  int GetPid();
  int GetCharge();
  double GetMass();
  void SetPid(int x);
  void SetCharge(int x);
  void SetMass(double x);
  
};
#endif
