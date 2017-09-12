/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Asymmetry class implementation
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Asymmetry.hxx"

#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <stdlib.h>

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
    // cout << "File Opened" << endl;
  }

  GK_Raw = (TTree*)WorkFile->Get("GK_Raw");

  nQsq = in_Qsq.size();
  if (nQsq == 0) {
    return Parameterize();
  }

  else{
    Qsq_Vec = in_Qsq;
  }

  char tfnamestr[100] = "%s%i";
  char plotstr[100] = "tp:%s";
  char cutstr[100] = "q2==%g";

  int i = 0;
  char tempname1[100];
  char tempname2[100];
  char tempname3[100];
  TGraph *gtemp;

  int n;

  double param2;

  for (i = 0; i < nQsq; i++){

    sprintf(tempname1, tfnamestr, AsyNameStr, i);
    AsyFunction.push_back(new TF1(tempname1, FuncForm));
    sprintf(tempname2, plotstr, AsyNameStr);
    sprintf(tempname3, cutstr, Qsq_Vec[i]);

    n = GK_Raw->Draw(tempname2, tempname3, "goff");

    param2 = GK_Raw->GetV2()[n-1];
    AsyFunction.at(i)->FixParameter(2,param2);

    gtemp = new TGraph(n, GK_Raw->GetV1(), GK_Raw->GetV2());
    gtemp -> Fit(tempname1, "q");
  }

  return 0;


}

int Asymmetry::Parameterize()
{
  int n_all_Qsq = GK_Raw->Draw("q2","","goff");
  double * all_Qsq = GK_Raw->GetV1();
  Qsq_Vec = *(new vector<double>(all_Qsq, all_Qsq + n_all_Qsq));
  sort(Qsq_Vec.begin(), Qsq_Vec.end());
  vector<double>::iterator it = unique(Qsq_Vec.begin(),
                                       Qsq_Vec.end());
  Qsq_Vec.resize(distance(Qsq_Vec.begin(), it));
  nQsq = Qsq_Vec.size();
  Parameterize(Qsq_Vec);
  // cout << nQsq << endl;
  return 0;
}

double Asymmetry::Extrap(double x0, double x1, double x2,
                         double y1, double y2)
{
  if (x1==x2) {
    //cout << "Equal x's Passed" << endl;
    return y2;
  }
  else if (y1==y2) {
    //cout << "Equal y's Passed" << endl;
    return y2;
  }

  else {
    Double_t m = (y1-y2)/(x1-x2);
    Double_t b = y1-(m*x1);

    Double_t y0 = (m*x0)+b;

    return y0;

  }

}

double Asymmetry::GetAsyAmp(double Qsq, double tp)
{
  double x0, x1=0, x2;
  double y0, y1, y2;
  x0 = Qsq;
  // Special case where only one Qsq was supplied to
  // Parameterize
  if (nQsq == 0){
    cerr << "Error: Qsq list not initialized" << endl;
    exit(EXIT_FAILURE);
  }
  if (nQsq == 1){
    cerr << "Warning: Only only one Qsq value in use." << endl;
    cerr << "No extrapolation between fits." << endl;
    return AsyFunction[0]->Eval(tp);
  }

  // Find nearest value in Qsq_Vec < Qsq
  int n_low = 0;
  int n_high = 0;
  for (n_low = 0; n_low < nQsq; n_low++){
    if (Qsq < Qsq_Vec[n_low+1]) break;
  }

  // Special case where Qsq < any(Qsq_Vec)
  // (also cover Qsq_Vec[0] < Qsq < Qsq_Vec[1]
  if (n_low == 0)
    n_high = 1;
  // Special case where Qsq > any(Qsq_Vec)
  else if (n_low == nQsq){
    n_low = nQsq-2;
    n_high = nQsq-1;
  }
  //Usual case
  else
    n_high = n_low + 1;

  x1 = Qsq_Vec[n_low];
  x2 = Qsq_Vec[n_high];
  y1 = AsyFunction[n_low]->Eval(tp);
  y2 = AsyFunction[n_high]->Eval(tp);

  //cout<<x1<<"\t"<<x2<<"\t"<<y1<<"\t"<<y2<<endl;

  y0 = Extrap(x0, x1, x2, y1, y2);
  return y0;

}

int Asymmetry::SetPars()
{
  cerr << "Warning: Not Implemented" << endl;
  cerr << "Use Parameterize" << endl;
  return 1;
}
