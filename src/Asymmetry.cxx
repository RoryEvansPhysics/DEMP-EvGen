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

extern TFile * WorkFile;
TTree * GK_Raw;

Asymmetry::Asymmetry(char * in_AsyName, char * in_Func,
                     vector<double> in_Qsq, bool refit)
{
  AsyNameStr = in_AsyName;
  FuncForm = in_Func;
  if (refit) Parameterize(in_Qsq);
  else SetPars();
}

int Asymmetry::Parameterize(vector<double> in_Qsq)
{
  //Go to default work file if not extern not available
  if (WorkFile->IsZombie()){
    WorkFile = new TFile("../output/test.root");
    cout << "File Opened" << endl;
  }

  GK_Raw = (TTree*)WorkFile->Get("GK_Raw");

  nQsq = in_Qsq.size();
  if (nQsq == 0) {
    return Parameterize();
  }

  else{
    Qsq = in_Qsq;
    cout << nQsq << endl;
  }

  char tfnamestr[100] = "%s%i";
  char plotstr[100] = "tp:%s";
  char cutstr[100] = "q2==%g";

  int i = 0;
  char tempname1[100];
  char tempname2[100];
  char tempname3[100];
  TGraph *gtemp;

  for (i = 0; i < nQsq; i++){

    cout << Qsq[i] << endl;

    sprintf(tempname1, tfnamestr, AsyNameStr, i);
    AsyFunction.push_back(new TF1(tempname1, FuncForm));
    sprintf(tempname2, plotstr, AsyNameStr);
    cout << tempname2 << endl;
    sprintf(tempname3, cutstr, Qsq[i]);

    int n = GK_Raw->Draw(tempname2, tempname3, "goff");

    gtemp = new TGraph(n, GK_Raw->GetV1(), GK_Raw->GetV2());
    gtemp -> Fit(tempname1);
  }

  return 0;


}

int Asymmetry::Parameterize()
{
  int n_all_Qsq = GK_Raw->Draw("q2","","goff");
  double * all_Qsq = GK_Raw->GetV1();
  Qsq = *(new vector<double>(all_Qsq, all_Qsq + n_all_Qsq));
  sort(Qsq.begin(), Qsq.end());
  vector<double>::iterator it = unique(Qsq.begin(), Qsq.end());
  Qsq.resize(distance(Qsq.begin(), it));
  nQsq = Qsq.size();
  Parameterize(Qsq);
  cout << nQsq << endl;
  return 0;
}

int Asymmetry::SetPars()
{
  cout << "WARNING: Not Implemented" << endl;
  cout << "Use Parameterize" << endl;
  return 1;
}
