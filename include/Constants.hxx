/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Declaration of constants for use throughout the program
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Constants_H
#define Constants_H

#include "TMath.h"

namespace constants{

  const double electron_mass_mev = 0.511;
  const double proton_mass_mev = 938.272;
  const double pion_mass_mev = 139.57;
  const double neutron_mass_mev =  939.565;

  const double DEG = 180/TMath::Pi();

  const int pid_pion = -211;
  const int pid_prot = 2212;
  const int pid_elec = 11;
  const int pid_neut = 0;

  const double EBeam = 11000;
  const double PSF = (EBeam*0.9-EBeam*0.1)
    * (28.0-5.0)/DEG * 2*TMath::Pi()
    *(EBeam*0.9-EBeam*0.1)
    * (60.0-0.0)/DEG * 2*TMath::Pi();
  const double Lumi = 1.0e36;
  const double nBcm2 = 1e-33;

  const double alpha = 1.0/137.0;
}

#endif
