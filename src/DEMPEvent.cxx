#include "DEMPEvent.hxx"
#include "Particle.hxx"
#include "Constants.hxx"

#include "TMath.h"
#include "TVector3.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

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

DEMPEvent::DEMPEvent(char* prefix)
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

  char be_name[100];
  strcpy(be_name, prefix);
  strcat(be_name, "BeamElec");
  BeamElec = new Particle(electron_mass_mev, be_name, pid_elec);
  BeamElec->SetName(be_name);

  char tn_name[100];
  strcpy(tn_name, prefix);
  strcat(tn_name, "TargNeut");
  TargNeut = new Particle(neutron_mass_mev, tn_name, pid_neut);

  char se_name[100];
  strcpy(se_name, prefix);
  strcat(se_name, "ScatElec");
  ScatElec = new Particle(electron_mass_mev, se_name, pid_elec);

  char ppi_name[100];
  strcpy(ppi_name, prefix);
  strcat(ppi_name, "ProdPion");
  ProdPion = new Particle(pion_mass_mev, ppi_name, pid_pion);

  char ppr_name[100];
  strcpy(ppr_name, prefix);
  strcat(ppr_name, "ProdProt");
  ProdProt = new Particle(proton_mass_mev, ppr_name, pid_prot);

  VirtPhot = new Particle();
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

TVector3 DEMPEvent::CoM()
{
  return (BeamElec->Vect() + TargNeut->Vect())*(1/(BeamElec->E()+TargNeut->E()));
}

DEMPEvent DEMPEvent::operator = (const DEMPEvent& q)
{
  *(this->BeamElec) = *(q.BeamElec);
  *(this->TargNeut) = *(q.TargNeut);
  *(this->ScatElec) = *(q.ScatElec);
  *(this->ProdPion) = *(q.ProdPion);
  *(this->ProdProt) = *(q.ProdProt);
  *(this->VirtPhot) = *(q.VirtPhot);
}

void DEMPEvent::Boost(TVector3 boostvect)
{
  //std::cout << boostvect.Z() << std::endl;
  //std::cout << BeamElec->T() << std::endl;
  BeamElec->Boost(boostvect);
  //std::cout << BeamElec->T() << std::endl;
  TargNeut->Boost(boostvect);
  ScatElec->Boost(boostvect);
  ProdProt->Boost(boostvect);
  ProdPion->Boost(boostvect);
  VirtPhot->Boost(boostvect);
}
