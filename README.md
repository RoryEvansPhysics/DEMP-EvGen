# DEMP-EvGen
Event generator for Deep Exclusive Meson Production

## Particle Class

The Particle class inherits from the root TLorentzVector class so that its functions are immediately accessible through the Particle objects. It's member variables include the position of the particle's production vertex (vx, vy, vz), its mass, charge, and its GEMC compatible id.

## Frame Class

The Frame class represents an inertial reference frame (i.e. center of mass frame, lab frame, etc.) and all particles of the event w.r.t. that frame. The Frame object stores Particle objects as members. The Boost function applied to the Frame returns a different Frame containing the same particles, Lorentz boosted by the function argument.

## Event Class

The  Event class (planned) contains all Frames of interest. This class is where the actual event generation occurs. The main function will produce only one of these objects each loop.

## Asymmetry Class

The Asymmetry class calculates asymmetry amplitudes based on Monte-Carlo data by Goloskokov and Kroll. The asymmetry objects are persistent between events.

## Customrand Class

A class to hold various distribution functions for randomly generated variables, such as scattered electron energy. These functions should be persistent between events, and will provide fast random numbers.