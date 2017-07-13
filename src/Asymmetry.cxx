/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Asymmetry class implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Asymmetry.hxx"

#include <string>
#include <algorithm>
#include <vector>
#include <array>

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TGraph.h"

using namespace std;
using namespace TMath;

extern TFile WorkFile;

Asymmetry::Asymmetry(char * AsyName_in, char * Func_in)//,
		     // double in_Qsq[] = {}, bool refit = false)
{
  double in_Qsq[] = {4.107, 4.335};
  bool refit = true;
  AsyNameStr = AsyName_in;
  FuncForm = Func_in;
  if (refit) Parameterize(in_Qsq);
  else SetPars();
  
}

int Asymmetry::Parameterize(double in_Qsq[])
{
  nQsq = sizeof(in_Qsq)/sizeof(in_Qsq[0]);
  if (nQsq == 0) {
    return Parameterize();
  }

  //Go to default work file if not extern not available
  if (WorkFile.IsZombie())
    WorkFile.Open("../Output/test.root");
  
  TTree *GK_Raw = (TTree*)WorkFile.Get("GK_Raw");
  
  char tfnamestr[100] = "%s%i";
  char plotstr[100] = "tp:%s";
  char cutstr[100] = "Qsq==%d";

  
  int i = 0;
  char tempname1[100];
  char tempname2[100];
  char tempname3[100];

  TGraph *gtemp;
  
  for (i = 0; i < nQsq; i++){
    Qsq[i] = in_Qsq[i];

    sprintf(tempname1, tfnamestr, AsyNameStr.c_str(), i);
    cout << tempname1 << endl;
    AsyFunction[i] =  TF1(tempname1, FuncForm.c_str());

    sprintf(tempname2, plotstr, AsyNameStr.c_str());
    sprintf(tempname3, cutstr, Qsq[i]);

    int n = GK_Raw->Draw(plotstr, cutstr, "goff");

    gtemp = new TGraph(n, GK_Raw->GetV1(), GK_Raw->GetV2());
    gtemp -> Fit(tempname1);
    
  }

  return 0;

  
  

  
}

int Asymmetry::Parameterize()
{
  cout << "Warning: Not yet Implemented" << endl;
  cout << "Please supply Qsq values" << endl;
  return 1;
}
