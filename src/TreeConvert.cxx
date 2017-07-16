/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Convert .txt file into ROOT tree and store in .root file.
Specifically designed for aut_clas.txt from Goloskokov & Kroll.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "TFile.h"
#include "TTree.h"

using namespace std;

void GKConvert(string in_filepath, string out_filepath){
  ifstream in_filestream;

  in_filestream.open(in_filepath.c_str());
  
  if (! in_filestream){
    cout << "File not Found" << endl;
    exit(1);
  }

  //Skip to Data
  string line;
  int i;
  for (i = 0; i < 18; i++) {
    getline(in_filestream, line);
  }

  //Create a tree
  TFile out_TFile(out_filepath.c_str(), "UPDATE");

  gDirectory->Delete("GK_Raw;*");
  //This ensures only the most recent tree in in the file
  
  TTree GK_Raw("GK_Raw", "Asymmetry Data");
  
  //Initialize variables for each data column
  Double_t w, q2, tp, t, asy, asysfi, asy2fi, asyfpfs, asy3f;

  //Create branches for each variable
  GK_Raw.Branch("w", &w, "w/D");
  GK_Raw.Branch("q2", &q2, "q2/D");
  GK_Raw.Branch("tp", &tp, "tp/D");
  GK_Raw.Branch("t",&t,"t/D");
  GK_Raw.Branch("asy",&asy,"asy/D");
  GK_Raw.Branch("asysfi",&asysfi,"asysfi/D");
  GK_Raw.Branch("asy2fi",&asy2fi,"asy2fi/D");
  GK_Raw.Branch("asyfpfs",&asyfpfs,"asyfpfs/D");
  GK_Raw.Branch("asy3f",&asy3f,"asy3f/D");

  //Fill the tree
  while (!in_filestream.eof()) {
    in_filestream >> w >> q2 >> tp >> t >> asy >> asysfi >> asy2fi 
	  >> asyfpfs >> asy3f;
    //cout << w << "\t" << q2 << "\t" << tp <<"\t";
    //cout << t << "\t" << asy << "\t" << asysfi << "\t";
    //cout << asy2fi << "\t" << asyfpfs << "\t" << asy3f;
    //cout << endl;
    GK_Raw.Fill();
  }
  
  GK_Raw.Write();
}