
#include "CustomRand.hxx"

#include "TF1.h"
#include "TMath.h"
#include "TRandom3.h"

#include <stdio.h>

CustomRand::CustomRand(char * fname,
                       double ERange[2], double ThetaRange[2],
                       double PhiRange[2])
{
  PartSet = true;

  int seed = 0;

  r = new TRandom3(seed);

  char PhiName[100] = "Phi_%c";
  std::sprintf(PhiName, PhiName, fname);
  PhiRand = new TF1(PhiName, "1", PhiRange[0], PhiRange[1]);

  char ThetaName[100] = "Theta_%c";
  std::sprintf(ThetaName, ThetaName, fname);
  //double ThetaMin = ThetaRange[0]*TMath::Pi()/180;
  //double ThetaMax = ThetaRange[1]*TMath::Pi()/180;
  ThetaRand = new TF1(ThetaName, "1",
                      TMath::Cos(ThetaRange[0]),
                      TMath::Cos(ThetaRange[1]));


  char EName[100] = "E_%c";
  std::sprintf(EName, EName, fname);
  ERand = new TF1(EName, "1", ERange[0], ERange[1]);
}


double CustomRand::Phi()
{
  return PhiRand->GetRandom();
}
double CustomRand::Theta()
{
  return TMath::ACos(ThetaRand->GetRandom());

}
double CustomRand::E()
{
  return ERand->GetRandom();
}
