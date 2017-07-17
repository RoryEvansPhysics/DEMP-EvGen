/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Frame Class
  Contains three Particle objects
  Currently just a prototype
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Frame.hxx"
#include "Particle.hxx"

#include "TRandom2.h"


Frame* Frame::RandFrame()
{
  TRandom2 * Rand = new TRandom2(0);
  double px_elec = 500 * Rand->Uniform(0,1);
  double py_elec = 500 * Rand->Uniform(0,1);
  double pz_elec = 500 * Rand->Uniform(0,1);

  double px_pion = 500 * Rand->Uniform(0,1);
  double py_pion = 500 * Rand->Uniform(0,1);
  double pz_pion = 500 * Rand->Uniform(0,1);

  Frame* F = new Frame();
  F->Electron = new Particle(.511, px_elec, py_elec, pz_elec);
  F->Pion = new Particle(212, px_pion, py_pion, pz_pion);
  F->Proton = new Particle(1000, *(F->Electron), *(F->Pion));

  return F;
}
