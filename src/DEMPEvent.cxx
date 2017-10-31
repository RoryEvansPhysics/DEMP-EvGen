#include "DEMPEvent.hxx"
#include "Particle.hxx"
#include "Constants.hxx"

#include "TMath.h"

#include <iostream>

using namespace constants;

DEMPEvent::DEMPEvent()
{
  qsq_GeV = new double(0);
  t_GeV = new double(0);
  w_GeV = new double(0);
  t_para_GeV = new double(0);
  t_prime_GeV = new double(0);
  negt = new double(0);
  x_B = new double(0);
  Phi = new double(0);
  Phi_s = new double(0);
  Theta = new double(0);
  P_T = new double(0);
  Vertex_x = new double(0);
  Vertex_y = new double(0);
  Vertex_z = new double(0);

}
void DEMPEvent::Update()
{
  *qsq_GeV = -(VirtPhot->Mag2())/1000000;

  *w_GeV = (*VirtPhot+*TargNeut).Mag()/1000;

  *t_GeV = (*VirtPhot-*ProdPion).Mag2()/1000000;


  double E1 = VirtPhot->E();
  double P1 = VirtPhot->P();

  double E2 = ProdPion->E();
  double P2 = ProdPion->P();

  *t_para_GeV = (((E1-E2)*(E1-E2))-((P1-P2)*(P1-P2)))/1000000;

  *t_prime_GeV = (*t_GeV) - (*t_para_GeV);

  *negt = (-1.0)*(*t_GeV);

  *x_B = (*qsq_GeV)*1000000/(2*proton_mass_mev *
                          this->VirtPhot->E());

  *Phi_s = TMath::Pi() - ScatElec->Phi();

  *Phi = ProdPion->Phi() - ScatElec->Phi();

  *Theta = ScatElec->Theta();
}
