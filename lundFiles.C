#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TF1.h"
#include <string.h>

using std::setw;
using std::setprecision;
using std::cout;
using std::cin;
using std::endl;
using namespace std;

void lundFiles()
{

  gStyle->SetStatW(0.40);
  gStyle->SetStatH(0.20);
  gStyle->SetStatY(0.90);
  gStyle->SetTitleW(0.8);
  gStyle->SetTitleH(0.11);
  gStyle->SetOptFit(1);

  Int_t i, ii, j, k;


  ifstream ilund("./LundFiles/DVMP_Ee_11_Events_90000000_File_9.lund");
  Double_t x1, x2, x3, x4, x5, x6, x7, x8, x9, x10;
  Double_t y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14;


  for ( int k = 0; k < 20; k++ ){
      
    TString tSmallF;
    tSmallF = "./LundFiles/DEMP_Generated_11GeV_50k_File_";
    tSmallF += k;
    tSmallF += ".lund";
    ofstream olund(tSmallF);
      
    for ( int i = 0; i < 50000; i++ ){	
      ilund >> x1 >> x2 >> x3 >> x4 >> x5 >> x6 >> x7 >> x8 >> x9 >> x10;

      	if ( k > 9 ) { 
	  olund << setw(1)  << x1 << setw(14) << x2 << setw(14) << x3 
		<< setw(14) << x4 << setw(14) << x5 << setw(14) << x6 
		<< setw(14) << x7 << setw(14) << x8 << setw(14) << x9 
		<< setw(14) << x10 << endl;
	}
	
      for ( int j = 0; j < 3; j++ ){
	ilund >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> y7 >> y8 >> y9 >> y10 >> y11 >> y12 >> y13 >> y14;
	  
	if ( k > 9 ) { 
	  olund << setw(14) << y1  << setw(14) << y2  << setw(14) << y3  << setw(14) << y4  
		<< setw(14) << y5  << setw(14) << y6  << setw(14) << y7  << setw(14) << y8  
		<< setw(14) << y9  << setw(14) << y10 << setw(14) << y11 << setw(14) << y12 
		<< setw(14) << y13 << setw(14) << y14 << endl;
	}

      }		
    }
    olund.close();
  }
    
  
}

