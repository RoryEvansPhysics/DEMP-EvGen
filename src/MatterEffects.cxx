/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Rory Evans, Feb. 2018.
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "TMath.h"
#include "TRandom3.h"
#include "Particle.hxx"
#include "MatterEffects.hxx"
#include "Constants.hxx"

using namespace TMath;

Particle* MatterEffects::MultiScatter(Particle* P, double radlen)
{
  double mstheta, msphi, mstheta0;
  double beta; //Particle veolcity in units of c.

  Particle * Pms = new Particle(P->M(), 0, 0, P->P());
  Pms->SetCharge(P->GetCharge());
  Pms->SetMass(P->GetMass());
  Pms->SetPid(P->GetPid());

  char *p_name = P->GetName();
  char ms_name[100];

  strcpy(ms_name, p_name);
  strcat(ms_name, "_MS");

  //Pms->SetName(ms_name);

  beta = P->P()/Sqrt(Power(P->M(),2)+Power(P->P(),2));
  mstheta0 = 13.6/(beta*(P->P()))*Abs(P->GetCharge())*Sqrt(radlen)
    * (1+0.38*Log(radlen));

  mstheta = gRandom->Gaus(0, mstheta0);

  msphi = 2*Pi()*gRandom->Rndm() - Pi();

  Pms->RotateX(mstheta);
  Pms->RotateZ(msphi);

  Pms->RotateX(P->Theta());
  Pms->RotateZ(P->Phi());

  return Pms;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Following functions adapted from eloss.h from
Zafar Ahmed's Generator (in turn adapted from SIMC)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

double MatterEffects::eta(double aZ)
{
  //Phys.Rev.D 12,1884 A46
  return log( 1440 * pow( aZ , -2. / 3. ) ) / log( 183 * pow( aZ , -1. / 3. ) );
}

double MatterEffects::b(double aZ)
{
  //Phys.Rev.D 12,1884 A45
  if ( aZ!=0 )
    return 4. / 3. * ( 1 + 1. / 9. * ( aZ + 1 ) / ( aZ + eta( aZ ) ) / log( 183 * pow( aZ , -1/3. ) ) );
  else
    return 0;
}

double MatterEffects::X0(double aZ, double aA)
{
  double Lrad,Lrad_prime,f_Z;
  if ( aZ==1 )
    {
      Lrad=5.31;
      Lrad_prime=6.144;
    }
  else if ( aZ==2 )
    {
      Lrad=4.79;
      Lrad_prime=5.621;
    }
  else if ( aZ==3 )
    {
      Lrad=4.74;
      Lrad_prime=5.805;
    }
  else if ( aZ==4 )
    {
      Lrad=4.71;
      Lrad_prime=5.924;
    }
  else
    {
      Lrad       = log( 184.15 * pow( aZ , -1./3.));
      Lrad_prime = log( 1194.  * pow( aZ , -2./3.));
    }

  double a = constants::alpha * aZ;

  a = a * a;

  f_Z = a * ( 1./(1+a) + 0.20206 - 0.0369 * a + 0.0083 * a * a - 0.002 * a * a * a );

  if ( aZ!=0 && aA!=0 ) {
    return 716.408 * aA / ( aZ * aZ * ( Lrad - f_Z ) + aZ * Lrad_prime );
  }
  else
    return 0;

}

Particle* MatterEffects::BremLoss( Particle* P, Double_t abt)
{
  Particle* Pbrem = new Particle();
  Pbrem->SetCharge(P->GetCharge());
  Pbrem->SetMass(P->GetMass());
  Pbrem->SetPid(P->GetPid());

  double aE0 = P->E();

  //std::cout << aE0 << "\t";

  double result = 0;
  if ( abt!=0 )
    result = aE0 * pow( gRandom->Rndm() * 0.999 , 1. / abt );

  if ( result > ( aE0 - constants::electron_mass_mev) )
    result = aE0 - constants::electron_mass_mev;

  if ( result < 0 )
    result = 0;

  //std::cout << result << std::endl;

  Pbrem->SetThetaPhiE(P->Theta(),P->Phi(),result);

  char *p_name = P->GetName();
  char ms_name[100];

  strcpy(ms_name, p_name);
  strcat(ms_name, "_Brem");

  //Pms->SetName(ms_name);

  return Pbrem;
}

Particle * MatterEffects::IonLoss(Particle* P, double a, double z, double rho, double t )
{

  Particle* Pil = new Particle();
  Pil->SetCharge(P->GetCharge());
  Pil->SetMass(P->GetMass());
  Pil->SetPid(P->GetPid());

  double mass = P->GetMass();
  double aE0 = P->E();

  //std::cout << aE0 << "\t";

  double lK = 0.307075;  // Page 398. cm^2/g for A=1 g/mol

  double lbetasq = 1 - mass * mass / ( aE0 * aE0 );

  double lxi = lK / 2 * z / a * t / lbetasq;  //aT: g/cm^2

  double lhbarwsq = 28.816 * 28.816 * rho * z / a * 1e-12;  //Page 398 MeV arho is density of absorber

  double j = 0.200;

  double Delta_p = lxi * ( log( 2 * mass * lxi / lhbarwsq ) + j ); // Equation 32.12

  double lw = 4 * lxi;

  double result = 0;

  if ( z != 0 && a != 0 && t != 0 && rho != 0 )

    result = gRandom->Landau( Delta_p , lw );

  if ( result > ( aE0 - mass ) )
    result = aE0 - mass;

  if ( result < 0 )
    result = 0;

  //td::cout << result << std::endl;

  Pil->SetThetaPhiE(P->Theta(),P->Phi(),P->E()-result);

  char *p_name = P->GetName();
  char ms_name[100];

  strcpy(ms_name, p_name);
  strcat(ms_name, "_Ion");

  //Pms->SetName(ms_name);

  return Pil;
}
