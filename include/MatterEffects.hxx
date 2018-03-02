/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Rory Evans, Feb. 2018.
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef MatterEffects_H
#define MatterEffects_H

#include "Particle.hxx"

class MatterEffects{
private:
  static double eta(double aZ);
  static double b(double aZ);

public:
  static double X0(double aZ, double aA);
  static Particle* MultiScatter(Particle* P, double radlen);
  static Particle* IonLoss(Particle* P, double a, double z, double rho, double t);
  static Particle* BremLoss(Particle* P, double radlen);
};

#endif
