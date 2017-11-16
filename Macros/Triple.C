#include "TTree.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"

void Triple()
{
  gStyle->SetOptStat(0);
  TFile * f1 = new TFile("../build/Output.root");
  TTree * t1 = (TTree*)f1->Get("Output");

  TCut ElecTheta = "VertScatElec_theta>8 && VertScatElec_theta<24";
  TCut ElecMom = "VertScatElec_P>1 && VertScatElec_P<11";

  TCut PionTheta = "VertProdPion_theta>8 && VertProdPion_theta<16";
  TCut PionMom = "VertProdPion_P>1 && VertProdPion_P<11";

  TCut ProtTheta = "VertProdProt_theta>8 && VertProdProt_theta<24";
  TCut ProtMom = "VertProdProt_P>0.1";

  TCut W = "w_GeV>2 & t_GeV>-1.5";

  TCut Coin = ElecTheta
    && ElecMom
    && PionTheta
    && PionMom
    && ProtTheta
    && ProtMom
    && W;

  TCut Weight = "weight";

  TCanvas* c1 = new TCanvas("c1","c1");

  t1->Draw("qsq_GeV:x_B>>h1(100,0,0.8,100,0,9)",Weight*Coin,"colz");

  gPad -> SetLogz();
  TH2 *h1 = (TH2*)gDirectory->Get("h1");
  h1->SetTitle("Electron, Pion, and Proton Acceptance");
  h1->GetXaxis()->SetTitle("x_{B}");
  h1->GetYaxis()->SetTitle("Q^{2}");

  TCanvas* c2 = new TCanvas("c2","c2");
  c2->Divide(3,1);

  c2->cd(1);
  t1->Draw("VertScatElec_P:VertScatElec_theta>>h2(50,8,24,50,3,6)",
           Weight*Coin, "colz");

  c2->cd(2);
  t1->Draw("VertProdPion_P:VertProdPion_theta>>h3(50,8,24,50,4.5,8)",
           Weight*Coin, "colz");

  c2->cd(3);

  t1->Draw("VertProdProt_P:VertProdProt_theta>>h4(50,8,24,50,0.1,2)",
           Weight*Coin,"colz");

  gPad -> SetLogz();
}
