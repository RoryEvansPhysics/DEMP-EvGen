#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <TSystem.h>
#include <TString.h>
#include <TStyle.h>
#include <Riostream.h>
#include "TObjString.h"
#include <TNamed.h>
#include <TPRegexp.h>
#include <TObjArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TDatime.h>
#include <TError.h>
#include <TVirtualFitter.h>
#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
#include <TCut.h>
#include <TMultiGraph.h>
#include <TCutG.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TPaletteAxis.h>
#include <TRandom3.h>
//#include "SIDIS_Acceptance.h"
const double MeV2GeV=0.001;
using namespace std;


void demp_elec() {

  // ppiOut << "3" << " \t " << fEventWeight << " \t " << fZASigma_Lab << " \t " << fSSAsym << " \t " << "0" << " \t "  
  // 	     << fx << " \t " << fT_GeV << " \t " << fW_GeV << " \t " << fQsq_GeV  << " \t " << fEpsilon << endl;
        // Electron
  // ppiOut << setw(10) << "2" 	 << setw(10) << "-1" 	 << setw(10) << "1" 	 << setw(10) << "11" 	 << setw(10) << "0" 	 << setw(10) << "0" 
  // 	 << setw(16) << fScatElec_MomX_Col_GeV  
  // 	 << setw(16) << fScatElec_MomY_Col_GeV   
  // 	 << setw(16) << fScatElec_MomZ_Col_GeV  
  // 	 << setw(16) << fScatElec_Energy_Col_GeV
  // 	 << setw(16) << fElectron_Mass_GeV
  // 	 << setw(16) << fVertex_X
  // 	 << setw(16) << fVertex_Y
  // 	 << setw(16) << fVertex_Z
  // 	 << endl;

    
  const int fN = 20;
  TString s1[fN];

  ofstream oelec("demp_electron.lund");

  int fNParticle, fPol;
  double fWeight, fSigma, fSSasym, fx, fT, fW, fQsq, fEpsilon;
  int fIndex, fCharge;
  std::string line;

  for ( int i = 0; i < fN; i++ ) {
    s1[i] = "LundFiles/DEMP_Ee_11_Events_200000_File_";
    s1[i] += i;
    s1[i] += ".lund";
    cout << s1[i] << endl;

    std::ifstream input( s1[i] );

    for( std::string line; getline( , line ); )  {
      
      


    }
	
  }


}
