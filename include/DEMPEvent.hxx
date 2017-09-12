#ifndef DEMPEvent_H
#define DEMPEvent_H

#include "Particle.hxx"

class DEMPEvent
{
public:

  Particle * BeamElec;
  Particle * TargNeut;
  Particle * ScatElec;
  Particle * ProdProt;
  Particle * ProdPion;

  Particle * VirtPhot;

  double qsq_GeV();
  double t_GeV();
  double w_GeV();

  double t_para_GeV();
  double t_prime_GeV();

  double Phi();
  double Phi_s();
  double Theta();

  double P_T = 1;


};

#endif
