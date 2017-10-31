#include "TTree.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"

void Test()
{
  gStyle->SetOptStat(0);

  TFile* f1 = new TFile("../build/Output.root");
  TTree* t1 = (TTree*)f1->Get("Output");

  TCanvas* c1 = new TCanvas("c1","c1");

  t1->Draw("qsq_GeV:x_B","weight>0","colz");

  TCanvas* c2 = new TCanvas("c2","c2");

  t1->Draw("qsq_GeV:x_B","weight<0","colz");

}
