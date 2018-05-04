# DEMP-EvGen
Event generator for Deep Exclusive Meson Production

## Building

To build the event generator, the compiler needs acces to both a compiled installation of CERN ROOT and its source code. ROOT version 6.08.06 or later is supported, and must be installed with the MathMore package enabled. Be sure not to change the location of either the ROOT source or compiled files after installation, as this will interfere with ROOT's built in CMake configurators.

CMake is also required. CMake 2.8 is the minimum supported version, and CMake 3 has been tested as well.

After downloading the source create a build directory and cd to it. Take note of the location of the source directory (where CMakeLists.txt should be stored) and run the commands:

```
cmake <source directory>
make
```

The event generator can now be run using:

```
./main
```

## Configuration

The file Config.json contains all the configuration options. Simply replace the default values as desired and run ./main in your build directory.

## Particle Class

The Particle class inherits from the root TLorentzVector class so that its functions are immediately accessible through the Particle objects. It's member variables include its mass, charge, and its GEMC compatible id.

## Event Class

The Event class contains all particles of a single event, in one frame of reference. It includes methods enabling transformation to other frames of reference and coordinate systems.

## Asymmetry Class

The Asymmetry class calculates asymmetry amplitudes based on Monte-Carlo data by Goloskokov and Kroll. The asymmetry objects are persistent between events.

## Customrand Class

A class to hold various distribution functions for randomly generated variables, such as scattered electron energy. These functions should be persistent between events, and will provide fast random numbers.