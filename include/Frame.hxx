/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Frame Class
  Contains three Particle objects
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Frame_H
#define Frame_H

#include "Particle.hxx"

class Frame
{
public:
  Particle* Electron;
  Particle* Proton;
  Particle* Pion;
  static Frame* RandFrame(); // Return a randomly generated frame.
};

#endif
