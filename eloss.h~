//--------------------------------------------------------------------------
// Authors: Zafar Ahmed, Garth Huber.
// Date: Feb 23, 2016
// 
//--------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <cmath>

using std::setw;
using std::setprecision;
using std::cout;
using std::cin;
using std::endl;
using namespace std;


// This code is taken from SAMC
// ------------------------------------------------------------------------------------------------------------------ 
// Thes values are used in calculation of Bremsstrahlung and ionization of of Electron in target and air.
Double_t ALPHA           = 1.0/137.0;
Double_t ELECTRON_MASS   = 0.510998918; //MeV

// Helium
Double_t fHelium_Z       = 2.0;
Double_t fHelium_A       = 4.002602;
Double_t fHelium_Density = 1.345e-3;  // g/cm^3. Taken from https://hallaweb.jlab.org/wiki/index.php/Solid_Background

// Air
double total             = 0.000124 + 0.755267 + 0.231781 + 0.012827;  //total mass of component of air
Double_t fAir_Z          = int( 6 * 0.000124 / total + 7 * 0.755267 / total + 8 * 0.231781 / total + 18* 0.012827 / total);
Double_t fAir_A          = fAir_Z / 0.499;
Double_t fAir_Density    = 1.205e-03;


// ------------------------------------------------------------------------------------------------------------------ 
// This code is taken from SAMC
double eta(double aZ)
{
  //Phys.Rev.D 12,1884 A46
  return log( 1440 * pow( aZ , -2. / 3. ) ) / log( 183 * pow( aZ , -1. / 3. ) );
}
// ------------------------------------------------------------------------------------------------------------------ 

// ------------------------------------------------------------------------------------------------------------------ 
// This code is taken from SAMC
double b(double aZ)
{
  //Phys.Rev.D 12,1884 A45
  if ( aZ!=0 )
    return 4. / 3. * ( 1 + 1. / 9. * ( aZ + 1 ) / ( aZ + eta( aZ ) ) / log( 183 * pow( aZ , -1/3. ) ) );
  else
    return 0;
}
// ------------------------------------------------------------------------------------------------------------------ 

// ------------------------------------------------------------------------------------------------------------------ 
// This code is taken from SAMC
double X0(double aZ, double aA)
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
  
    double a = ALPHA * aZ;

    a = a * a;

    f_Z = a * ( 1./(1+a) + 0.20206 - 0.0369 * a + 0.0083 * a * a - 0.002 * a * a * a );

    if ( aZ!=0 && aA!=0 ) {
      return 716.408 * aA / ( aZ * aZ * ( Lrad - f_Z ) + aZ * Lrad_prime );
    }
    else
      return 0;
  
}
// ------------------------------------------------------------------------------------------------------------------ 

// ------------------------------------------------------------------------------------------------------------------ 
// This code is taken from SAMC
double Bremsstrahlung( Double_t aE0, Double_t abt)
{
  
  double result = 0;
  if ( abt!=0 )
    result = aE0 * pow( gRandom->Rndm() * 0.999 , 1. / abt );
  
  if ( result > ( aE0 - ELECTRON_MASS) )
    result = aE0 - ELECTRON_MASS;
  
  if ( result < 0 )
    result = 0;

  return result;
}
// ------------------------------------------------------------------------------------------------------------------ 

// ------------------------------------------------------------------------------------------------------------------ 
// This code is taken from SAMC
double IonLoss( double aE0, double a, double z, double rho, double t )
{
  const double ELECTRON_MASS = 0.510998918;  // MeV

  double lK = 0.307075;  // Page 398. cm^2/g for A=1 g/mol

  double lbetasq = 1 - ELECTRON_MASS * ELECTRON_MASS / ( aE0 * aE0 );

  double lxi = lK / 2 * z / a * t / lbetasq;  //aT: g/cm^2

  double lhbarwsq = 28.816 * 28.816 * rho * z / a * 1e-12;  //Page 398 MeV arho is density of absorber

  double j = 0.200;

  double Delta_p = lxi * ( log( 2 * ELECTRON_MASS * lxi / lhbarwsq ) + j ); // Equation 32.12

  double lw = 4 * lxi;

  double result = 0;

  if ( z != 0 && a != 0 && t != 0 && rho != 0 )

  result = gRandom->Landau( Delta_p , lw );

  if ( result > ( aE0 - ELECTRON_MASS ) )
    result = aE0 - ELECTRON_MASS;

  if ( result < 0 )
    result = 0;

  return result;
}

// ------------------------------------------------------------------------------------------------------------------ 
