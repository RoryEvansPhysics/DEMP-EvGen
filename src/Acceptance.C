#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TCut.h"

void Acceptance()
{

  gStyle->SetPalette(1);

  TFile * f = new TFile("../build/Output.root");
  TTree * t1 = (TTree*)f->Get("Output");

  TCut PiAngle = "(VertProdPion_theta>8)&&(VertProdPion_theta<16)";
  TCut EAngle = "(VertScatElec_theta>8)&&(VertScatElec_theta<24)";
  TCut PAngle = "(VertProdProt_theta>8)&&(VertProdProt_theta<24)";

  TCut Q1 = "qsq_GeV>1";
  TCut Q4 = "qsq_GeV>4";
  TCut Q5 = "qsq_GeV>5";

  TCut Weight = "weight";

  TCut t = "t_GeV > -1.2";
  TCut w = "w_GeV > 2";

  TCut Cut = PiAngle && EAngle && PAngle && w && t;

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(1,3);

  c1 -> cd(1);

  t1->Draw("VertScatElec_P:VertScatElec_theta",
           Weight * (Cut && Q1), "colz");
  TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp -> SetTitle("Electron, Q^{2}>1 GeV");
  gPad->SetLogz();


  c1 -> cd(2);

  t1->Draw("VertProdPion_P:VertProdPion_theta",
           Weight * (Cut && Q1), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp -> SetTitle("Pion, Q^{2}>1 GeV");
  gPad->SetLogz();

  c1 -> cd(3);

  t1->Draw("VertProdProt_P:VertProdProt_theta",
           Weight * (Cut && Q1), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp->SetTitle("Proton, Q^{2}>1 GeV");

  gPad->SetLogz();

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(1,3);

  c2 -> cd(1);

  t1->Draw("VertScatElec_P:VertScatElec_theta",
           Weight * (Cut && Q4), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp -> SetTitle("Electron, Q^{2}>4 GeV");
  gPad->SetLogz();

  c2 -> cd(2);

  t1->Draw("VertProdPion_P:VertProdPion_theta",
           Weight * (Cut && Q4), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp -> SetTitle("Pion, Q^{2}>4 GeV");
  gPad->SetLogz();

  c2 -> cd(3);

  t1->Draw("VertProdProt_P:VertProdProt_theta",
           Weight * (Cut && Q4), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp->SetTitle("Proton, Q^{2}>4 GeV");

  gPad->SetLogz();

  TCanvas *c3 = new TCanvas("c3","c3");
  c3->Divide(1,3);

  c3 -> cd(1);

  t1->Draw("VertScatElec_P:VertScatElec_theta",
           Weight * (Cut && Q5), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp -> SetTitle("Electron, Q^{2}>5 GeV");
  gPad->SetLogz();

  c3 -> cd(2);

  t1->Draw("VertProdPion_P:VertProdPion_theta",
           Weight * (Cut && Q5), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp -> SetTitle("Pion, Q^{2}>5 GeV");
  gPad->SetLogz();

  c3 -> cd(3);

  t1->Draw("VertProdProt_P:VertProdProt_theta",
           Weight * (Cut && Q5), "colz");
  htemp = (TH2F*)gPad->GetPrimitive("htemp");
  htemp->SetTitle("Proton, Q^{2}>5 GeV");

  gPad->SetLogz();


}
