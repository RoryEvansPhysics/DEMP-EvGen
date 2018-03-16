/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Rory Evans, Feb. 2018.
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef MatterEffects_H
#define MatterEffects_H

#include "Particle.hxx"

class MatterEffects{
private:
  double eta(double aZ);

public:
  double b(double aZ);
  double X0(double aZ, double aA);
  Particle* MultiScatter(Particle* P, double radlen);
  Particle* IonLoss(Particle* P, double a, double z, double rho, double t);
  Particle* BremLoss(Particle* P, double abt);
};

#endif
