#ifndef ProductGen_H
#define ProductGen_H

#include "Particle.hxx"
#include "CustomRand.hxx"

#include "TF1.h"

#include <vector>


using namespace std;

class ProductGen
{

  double StepSize;
  double WTol;

  Particle * Target;
  Particle * Incident;
  Particle * Scattered;

  Particle * Proton;
  Particle * Pion;

  CustomRand * AngleGen;


  double Qsq();
  double W();

public:
  ProductGen();

  void SetIncident(Particle * inIncident);
  void SetTarget(Particle * inTarget);

  void Solve(Particle * inScattered);

  Particle * ProdPion();
  Particle * ProdProton();

  void PrintPars();
};

#endif
