#include "DEMPEvent.hxx"
#include "Particle.hxx"
#include "Constants.hxx"

#include "TMath.h"

using namespace constants;

double DEMPEvent::qsq_GeV()
{
  return -(VirtPhot->Mag2())/1000000;
}

double DEMPEvent::w_GeV()
{
  return (*VirtPhot+*TargNeut).Mag()/1000;
}

double DEMPEvent::t_GeV()
{
  return (*VirtPhot-*ProdPion).Mag2()/1000000;
}

double DEMPEvent::t_para_GeV()
{
  double E1 = VirtPhot->E();
  double P1 = VirtPhot->P();

  double E2 = ProdPion->E();
  double P2 = ProdPion->P();

  return (((E1+E2)*(E1+E2))-((P1+P2)*(P1+P2)))/1000000;
}

double DEMPEvent::t_prime_GeV()
{
  return this->t_GeV() - this->t_para_GeV();
}

double DEMPEvent::Phi_s()
{
  return ScatElec->Phi() - TMath::Pi();
}

double DEMPEvent::Phi()
{
  ProdPion->Phi() - ScatElec->Phi();
}

double DEMPEvent::Theta()
{
  return ScatElec->Theta();
}
