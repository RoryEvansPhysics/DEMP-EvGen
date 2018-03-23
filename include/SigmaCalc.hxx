#ifndef SigmaCalc_H
#define SigmaCalc_H

#include "DEMPEvent.hxx"
#include "Asymmetry.hxx"

#include <vector>

class SigmaCalc
{
public:
  //SigmaCalc(DEMPEvent* in_Event);
  SigmaCalc(DEMPEvent* in_VertEvent,
            DEMPEvent* in_CofMEvent,
            DEMPEvent* in_RestEvent);

  DEMPEvent* VertEvent;
  DEMPEvent* CofMEvent;
  DEMPEvent* RestEvent;

  vector<Asymmetry*>* Asyms;

  double sigma_t();
  double sigma_l();
  double sigma_tt();
  double sigma_lt();
  double sigma_uu();

  double Sigma_k(int k);

  double sigma_ut();

  double fluxfactor_col();
  double fluxfactor_rf();

  double jacobian_cm();
  double jacobian_cm_col();

  double sigma();

  double epsilon();

  double weight(int nGen);
};


#endif
