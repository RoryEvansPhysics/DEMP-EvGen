/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Declaration of constants for use throughout the program
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Constants_H
#define Constants_H

#include "TMath.h"

namespace constants{

  const double elec_mass_mev = 0.511;
  const double proton_mass_mev = 938.272;
  const double pi_mass_mev = 139.57;
  const double neutron_mass_mev =  939.565;

  const double DEG = 180/TMath::Pi();

  const int pid_pion = -211;
  const int pid_prot = 2212;
  const int pid_elec = 11;
  const int pid_neut = 0;

}

#endif
