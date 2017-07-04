#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>

/* #include <TSystem.h> */
/* #include <TString.h> */
/* #include <TStyle.h> */
/* #include <Riostream.h> */
/* #include <TObjString.h> */
/* #include <TNamed.h> */
/* #include <TPRegexp.h> */
/* #include <TObjArray.h> */
/* #include <TChain.h> */
/* #include <TMath.h> */
/* #include <TH1.h> */
/* #include <TH1F.h> */
/* #include <TH2F.h> */
/* #include <TFile.h> */
/* #include <TROOT.h> */
/* #include <TF1.h> */
/* #include <TGraph.h> */
/* #include <TGraphErrors.h> */
/* #include <TCanvas.h> */
/* #include <TDatime.h> */
/* #include <TError.h> */
/* #include <TVirtualFitter.h> */
/* #include <TSQLServer.h> */
/* #include <TSQLResult.h> */
/* #include <TSQLRow.h> */
/* #include <TCut.h> */
/* #include <TMultiGraph.h> */
/* #include <TCutG.h> */
/* #include <TLorentzVector.h> */
/* #include <TMath.h> */
/* #include <TPaletteAxis.h> */
/* #include <TRandom3.h> */
/* #include <TLorentzVector.h> */
/* #include <TSystem.h> */
/* #include <TString.h> */
/* #include <TStyle.h> */
/* #include <Riostream.h> */
/* #include "TObjString.h" */
/* #include <TNamed.h> */
/* #include <TPRegexp.h> */
/* #include <TObjArray.h> */
/* #include <TChain.h> */
/* #include <TMath.h> */
/* #include <TH1.h> */
/* #include <TH1F.h> */
/* #include <TH2F.h> */
/* #include <TFile.h> */
/* #include <TROOT.h> */
/* #include <TF1.h> */
/* #include <TGraph.h> */
/* #include <TGraphErrors.h> */
/* #include <TCanvas.h> */
/* #include <TDatime.h> */
/* #include <TError.h> */
/* #include <TVirtualFitter.h> */
/* #include <TSQLServer.h> */
/* #include <TSQLResult.h> */
/* #include <TSQLRow.h> */
/* #include <TCut.h> */
/* #include <TMultiGraph.h> */
/* #include <TCutG.h> */
/* #include <TLorentzVector.h> */
/* #include <TMath.h> */
/* #include <TPaletteAxis.h> */
/* #include <TRandom2.h> */

#include <TLorentzVector.h>
#include <TRandom2.h>
#include <TMath.h>

using namespace std;
using std::setw;
using std::setprecision;
using std::cout;
using std::cin;
using std::endl;

Int_t           fNt;               // number of decay particles
Double_t        fMass[18] = {0};   // masses of particles
Double_t        fBeta[3]= {0};     // betas of decaying particle
Double_t        fTeCmTm;           // total energy in the C.M. minus the total mass
Double_t        fWtMax;            // maximum weigth
TLorentzVector  fDecPro[18];       // kinematics of the generated particles

TLorentzVector  fProtonCM;
TLorentzVector  fPionCM;

const Int_t kMAXP = 18;


/* void initialize() { */
/* } */

////////////////////////////////////////////////////////////////////////////////
/// The PDK function.
Double_t PDK(Double_t a, Double_t b, Double_t c) {
  Double_t x = (a-b-c)*(a+b+c)*(a-b+c)*(a+b-c);
  x = TMath::Sqrt(x)/(2*a);
  return x;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// Special max function
Int_t DoubleMax(const void *a, const void *b) {
  Double_t aa = * ((Double_t *) a);
  Double_t bb = * ((Double_t *) b);
  if (aa > bb) return  1;
  if (aa < bb) return -1;
  return 0;

}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///  Generate a random final state.
///  The function returns the weight of the current event.
///  The TLorentzVector of each decay product can be obtained using GetDecay(n).
///
/// Note that Momentum, Energy units are Gev/C, GeV
Double_t Generate()
{

  TRandom2 *fsiRandom;
  fsiRandom = new TRandom2(0);
  fsiRandom->GetSeed();

  Double_t rno[kMAXP];
   rno[0] = 0;
   Int_t n;
   if (fNt>2) {
      /* for (n=1; n<fNt-1; n++)  rno[n]=gRandom->Rndm();   // fNt-2 random numbers */
      for (n=1; n<fNt-1; n++)  rno[n]=fsiRandom->Rndm();   // fNt-2 random numbers
      qsort(rno+1 ,fNt-2 ,sizeof(Double_t) ,DoubleMax);  // sort them
   }
   rno[fNt-1] = 1;

   Double_t invMas[kMAXP], sum=0;
   for (n=0; n<fNt; n++) {
      sum      += fMass[n];
      invMas[n] = rno[n]*fTeCmTm + sum;
   }

   //
   //-----> compute the weight of the current event
   //
   Double_t wt=fWtMax;
   Double_t pd[kMAXP];
   for (n=0; n<fNt-1; n++) {
      pd[n] = PDK(invMas[n+1],invMas[n],fMass[n+1]);
      wt *= pd[n];
   }

   //
   //-----> complete specification of event (Raubold-Lynch method)
   //
   fDecPro[0].SetPxPyPzE(0, pd[0], 0 , TMath::Sqrt(pd[0]*pd[0]+fMass[0]*fMass[0]) );

   Int_t i=1;
   Int_t j;
   while (1) {
      fDecPro[i].SetPxPyPzE(0, -pd[i-1], 0 , TMath::Sqrt(pd[i-1]*pd[i-1]+fMass[i]*fMass[i]) );

      /* Double_t cZ   = 2*gRandom->Rndm() - 1; */
      Double_t cZ   = 2*fsiRandom->Rndm() - 1;
      Double_t sZ   = TMath::Sqrt(1-cZ*cZ);
      /* Double_t angY = 2*TMath::Pi() * gRandom->Rndm(); */
      Double_t angY = 2*TMath::Pi() * fsiRandom->Rndm();
      Double_t cY   = TMath::Cos(angY);
      Double_t sY   = TMath::Sin(angY);
      for (j=0; j<=i; j++) {
         TLorentzVector *v = fDecPro+j;
         Double_t x = v->Px();
         Double_t y = v->Py();
         v->SetPx( cZ*x - sZ*y );
         v->SetPy( sZ*x + cZ*y );   // rotation around Z
         x = v->Px();
         Double_t z = v->Pz();
         v->SetPx( cY*x - sY*z );
         v->SetPz( sY*x + cY*z );   // rotation around Y
      }

      if (i == (fNt-1)) break;

      Double_t beta = pd[i] / sqrt(pd[i]*pd[i] + invMas[i]*invMas[i]);
      for (j=0; j<=i; j++) fDecPro[j].Boost(0,beta,0);
      i++;
   }


   fProtonCM = fDecPro[0];
   fPionCM = fDecPro[1];

   
   /* cout << "------------- CM -------------" << endl; */
   /* cout << setw(12) << "Paritcle"  << setw(12) << "X"  */
   /* 	<< setw(12) << "Y" 	   << setw(12) << "Z"  */
   /* 	<< setw(12) << "Mass"      << setw(12) << "Theta" */
   /* 	<< setw(12) << "Phi" */
   /* 	<< endl; */

   /* for ( int ii = 0; ii < 2; ii++ ) { */
   /*   cout << setw(12) << ii + 1 */
   /* 	  << setw(12) << fDecPro[ii].X() */
   /* 	  << setw(12) << fDecPro[ii].Y() */
   /* 	  << setw(12) << fDecPro[ii].Z() */
   /* 	  << setw(12) << fDecPro[ii].M() */
   /* 	  << setw(12) << fDecPro[ii].Theta() * 57.29 */
   /* 	  << setw(12) << fDecPro[ii].Phi() * 57.29 */
   /* 	  << endl; */
   /* } */

   /* cout << endl; */
   /* cout << setw(12) << "Proton" */
   /* 	<< setw(12) << fProtonCM.X() */
   /* 	<< setw(12) << fProtonCM.Y() */
   /* 	<< setw(12) << fProtonCM.Z() */
   /* 	<< setw(12) << fProtonCM.M() */
   /* 	<< setw(12) << fProtonCM.Theta() * 57.29 */
   /* 	<< setw(12) << fProtonCM.Phi() * 57.29 */
   /* 	<< endl; */
   /* cout << setw(12) << "Pion" */
   /* 	<< setw(12) << fPionCM.X() */
   /* 	<< setw(12) << fPionCM.Y() */
   /* 	<< setw(12) << fPionCM.Z() */
   /* 	<< setw(12) << fPionCM.M() */
   /* 	<< setw(12) << fPionCM.Theta() * 57.29 */
   /* 	<< setw(12) << fPionCM.Phi() * 57.29 */
   /* 	<< endl; */
   
   //
   //---> final boost of all particles
   //
   for (n=0;n<fNt;n++) fDecPro[n].Boost(fBeta[0],fBeta[1],fBeta[2]);

   /* cout << "------------- Lab -------------" << endl; */
   /* for ( int ii = 0; ii < 2; ii++ ) { */
   /*   cout << setw(12) << ii + 1 */
   /* 	  << setw(12) << fDecPro[ii].X() */
   /* 	  << setw(12) << fDecPro[ii].Y() */
   /* 	  << setw(12) << fDecPro[ii].Z() */
   /* 	  << setw(12) << fDecPro[ii].M() */
   /* 	  << setw(12) << fDecPro[ii].Theta() * 57.29 */
   /* 	  << setw(12) << fDecPro[ii].Phi() * 57.29 */
   /* 	  << endl; */
   /* } */
   /* cout << endl << endl; */

   //
   //---> return the weight of event
   //
   return wt;
}


////////////////////////////////////////////////////////////////////////////////
/// Return Lorentz vector corresponding to decay n
TLorentzVector GetDecay(Int_t n)
{
   /* if (n>fNt) return 0; */
   return fDecPro[n];
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// Return Lorentz vector corresponding to decay n
TLorentzVector GetProtonCM()
{
   /* if (n>fNt) return 0; */
   return fProtonCM;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// Return Lorentz vector corresponding to decay n
TLorentzVector GetPionCM()
{
   /* if (n>fNt) return 0; */
   return fPionCM;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// Input:
///  - TLorentzVector &P:    decay particle (Momentum, Energy units are Gev/C, GeV)
///  - Int_t nt:             number of decay products
///  - Double_t *mass:       array of decay product masses
///  - Option_t *opt:        default -> constant cross section
///                       "Fermi" -> Fermi energy dependence
/// Return value:
///  - kTRUE:      the decay is permitted by kinematics
///  - kFALSE:     the decay is forbidden by kinematics
///
Bool_t SetDecay(TLorentzVector &P, Int_t nt, const Double_t *mass, Option_t *opt) {
   Int_t n;
   fNt = nt;
   if (fNt<2 || fNt>18) return kFALSE;  // no more then 18 particle

   //
   //
   //
   fTeCmTm = P.Mag();           // total energy in C.M. minus the sum of the masses
   for (n=0;n<fNt;n++) {
      fMass[n]  = mass[n];
      fTeCmTm  -= mass[n];
   }

   if (fTeCmTm<=0) return kFALSE;    // not enough energy for this decay

   //
   //------> the max weight depends on opt:
   //   opt == "Fermi"  --> fermi energy dependence for cross section
   //   else            --> constant cross section as function of TECM (default)
   //
   if (strcasecmp(opt,"fermi")==0) {
      // ffq[] = pi * (2*pi)**(FNt-2) / (FNt-2)!
      Double_t ffq[] = {0
                     ,3.141592, 19.73921, 62.01255, 129.8788, 204.0131
                     ,256.3704, 268.4705, 240.9780, 189.2637
                     ,132.1308,  83.0202,  47.4210,  24.8295
                     ,12.0006,   5.3858,   2.2560,   0.8859 };
      fWtMax = TMath::Power(fTeCmTm,fNt-2) * ffq[fNt-1] / P.Mag();

   } else {
      Double_t emmax = fTeCmTm + fMass[0];
      Double_t emmin = 0;
      Double_t wtmax = 1;
      for (n=1; n<fNt; n++) {
         emmin += fMass[n-1];
         emmax += fMass[n];
         wtmax *= PDK(emmax, emmin, fMass[n]);
      }
      fWtMax = 1/wtmax;
   }

   //
   //---->  save the betas of the decaying particle
   //
   if (P.Beta()) {
      Double_t w = P.Beta()/P.Rho();
      fBeta[0] = P(0)*w;
      fBeta[1] = P(1)*w;
      fBeta[2] = P(2)*w;
   }
   else fBeta[0]=fBeta[1]=fBeta[2]=0;

   return kTRUE;
}
////////////////////////////////////////////////////////////////////////////////
