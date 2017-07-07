/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Class to contain all information on each particle in the event.
Includes: TLorentz vector with momenta information.
          Charge, PID, etc.
	  Access functions for E, theta, etc.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Particle_H
#define Particle_H

class Particle : public TLorentzVector
{
  int pid;
}
#endif
