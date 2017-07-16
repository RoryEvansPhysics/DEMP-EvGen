/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Asymmetry Class.
Loads asymmetry parameterization into TF2 object.
Persistent between events to minimize disk I/O.
Handles fitting of Monte-Carlo asymmetry data, 
extrapolation between fits.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Asymmetry_H
#define Asymmetry_H

#include <string>

#include "TF1.h"

class Asymmetry
{
  string root_filepath;// Name of .root file with Raws and/or
		       // parameters
  string AsyNameStr;   // Name of asymmetry
		       // (must match branch name)
  
  int nQsq;	       // Number of Qsq values
  double Qsq[nQsq];    // Qsq values
  TF1 FittingFunction[nQsq];
		       // General form of function to fit data

  int nPars;           // Number of pars in fitting function

  
  double Extrap(double x1, double x2, double y1, double y2);
		       // Extrapolation function

public:
  
  void Parameterize(); // Set pars from fitting

  void Parameterize(double in_Qsq[])
		       // Use only specified Qsq values
  
  double GetAsy(double qsq, double tp);
		       // Return asymmetry amplitude

  void SetFunc(string fitfunc, int n);
		       // Sets the fitting function from string
  
  
  
};
#endif
