/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Asymmetry Class.
Loads asymmetry parameterization into TF2 object.
Persistent between events to minimize disk I/O.
Handles fitting of Monte-Carlo asymmetry data, 
extrapolation between fits.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef Asymmetry_H
#define Asymmetry_H

// #include <string>

#include "TF1.h"

class Asymmetry
{
  const char * root_filepath;// Name of .root file with Raws and/or
		       // parameters
  const char * AsyNameStr;   // Name of asymmetry
		       // (must match branch name)
  
  int nQsq;	       // Number of Qsq values
  double * Qsq;	       // Qsq values
  TF1 * AsyFunction;   // Asymmetry Functions

  char * FuncForm;     // General form of function to fit data

  int nPars;           // Number of pars in fitting function

  
  double Extrap(double x1, double x2, double y1, double y2);
		       // Extrapolation function
  
public:
  Asymmetry(char * AsyName_in, char * Func_in);//,
	    //	    double in_Qsq[] = {}, bool refit = true);

  void SetPars();      // Set Pars from file
  
  int Parameterize(); // Set pars from fitting

  //  int Parameterize(double in_Qsq[]);
		       // Use only specified Qsq values
  
  //  double GetAsy(double qsq, double tp);
		       // Return asymmetry amplitude

  //  void SetFunc(const string& fitfunc, int n);
		       // Sets the fitting function from string
  
  
  
};
#endif
