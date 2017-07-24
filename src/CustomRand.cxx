#include "CustomRand.h"

#include "TRandom2.h"


CustomRand::CustomRand(char * fname,
                       double ERange[2], double ThetaRange[2],
                       double PhiRange[2])
{
  PartSet = true;
  char PhiName[100] = "Phi_%g";
  sprintf(PhiName, PhiName, fname);

}


double CustomRand::Phi()
{
  return PhiRand->GetRandom();
}
double CustomRand::Theta()
{
  return ThetaRand->GetRandom();
}
double CustomRand::E()
{
  return ERand->GetRandom();
}

