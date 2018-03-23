#ifndef DEMPEvent_H
#define DEMPEvent_H

#include "Particle.hxx"
#include "TVector3.h"

class DEMPEvent
{
public:

  DEMPEvent();
  DEMPEvent(char* prefix);

  void Boost(TVector3 boostvect);
  TVector3 CoM();

  Particle * BeamElec;
  Particle * TargNeut;
  Particle * ScatElec;
  Particle * ProdProt;
  Particle * ProdPion;

  Particle * VirtPhot;

  double* qsq_GeV;
  double* t_GeV;
  double* w_GeV;

  double* t_para_GeV;
  double* t_prime_GeV;
  double* negt;
  double* x_B;

  double* Phi;
  double* Phi_s;
  double* Theta;

  double* P_T;

  double* Vertex_x;
  double* Vertex_y;
  double* Vertex_z;

  void Update();

  DEMPEvent operator = (const DEMPEvent& q);

};

#endif
