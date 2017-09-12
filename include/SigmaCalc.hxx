#ifndef SigmaCalc_H
#define SigmaCalc_H

#include "DEMPEvent.hxx"
#include "Asymmetry.hxx"

#include <vector>

class SigmaCalc
{
public:
  SigmaCalc(DEMPEvent* in_Event);

  DEMPEvent * Event;

  vector<Asymmetry*>* Asyms;

  double sigma_t();
  double sigma_l();
  double sigma_tt();
  double sigma_lt();
  double sigma_uu();

  double Sigma_k(int k);

  double sigma_ut();

  double epsilon();
};


#endif
