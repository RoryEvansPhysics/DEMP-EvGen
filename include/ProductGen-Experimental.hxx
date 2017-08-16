#ifndef ProductGen_H
#define ProductGen_H

#include "Particle.hxx"
#include "CustomRand.hxx"

#include "TF1.h"

#include <vector>

#include "RConfigure.h"
#ifndef R__HAS_MATHMORE
#error MathMore not installed. Rebuild root with GSL and MathMore.
#else
#include "Math/MultiRootFinder.h"
#include "Math/WrappedMultiTF1.h"
#endif

using namespace std;

class ProductGen
{
  Particle * Target;
  Particle * Incident;
  Particle * Scattered;

  vector<TF1> EqnSys;
  vector<ROOT::Math::WrappedMultiTF1> WrappedEqns;

  ROOT::Math::MultiRootFinder * Finder;

  double pars[15];

  static const int nEqns = 6;

  static double PconsX(double * x, double * p);
  static double PconsY(double * x, double * p);
  static double PconsZ(double * x, double * p);

  static double Econs(double * x, double * p);

  static double AngleTheta(double * x, double * p);
  static double AnglePhi(double * x, double * p);

  static double W(double * x, double * p);
  static double T(double * x, double * p);

  void SetPars();

  CustomRand * AngleGen;

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
