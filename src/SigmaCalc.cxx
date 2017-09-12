#include <vector>

#include "TMath.h"

#include "DEMPEvent.hxx"
#include "Asymmetry.hxx"

#include "SigmaL.hxx"
#include "SigmaT.hxx"
#include "SigmaLT.hxx"
#include "SigmaTT.hxx"

#include "SigmaCalc.hxx"

using namespace TMath;

SigmaCalc::SigmaCalc(DEMPEvent* in_Event):Event(in_Event)
{
  vector<double> qsq;
  qsq.push_back(4.107);
  qsq.push_back(4.335);
  qsq.push_back(4.845);
  qsq.push_back(5.138);
  qsq.push_back(5.948);
  qsq.push_back(6.049);
  qsq.push_back(6.393);
  qsq.push_back(6.778);
  qsq.push_back(6.894);
  qsq.push_back(7.617);

  Asyms = new vector<Asymmetry*>(5);

  Asyms->at(0) =
    new Asymmetry("asy",
                  "[0]*exp([1]*x)-([0]+[2])*exp([3]*x)+[2]",
                  qsq, true);
  Asyms->at(0)->Parameterize(qsq);

  Asyms->at(1) =
    new Asymmetry("asysfi",
                  "[0]*exp([1]*x)+[2]",
                  qsq, true);
  Asyms->at(1)->Parameterize(qsq);

  Asyms->at(2) =
    new Asymmetry("asy2fi",
                  "[0]*exp([1]*x)+[2]",
                  qsq, true);
  Asyms->at(2)->Parameterize(qsq);

  Asyms->at(3) =
    new Asymmetry("asyfpfs",
                  "[0]*exp([1]*x)+[2]",
                  qsq, true);
  Asyms->at(3)->Parameterize(qsq);

  Asyms->at(4) =
    new Asymmetry("asy3f",
                  "[0]*exp([1]*x)+[2]",
                  qsq, true);
  Asyms->at(4)->Parameterize(qsq);

}

double SigmaCalc::sigma_l()
{
  return MySigmaL(Event->qsq_GeV(),
                  -Event->t_GeV(),
                  Event->w_GeV());
}
double SigmaCalc::sigma_t()
{
  return MySigmaL(Event->qsq_GeV(),
                  -Event->t_GeV(),
                  Event->w_GeV());
}
double SigmaCalc::sigma_tt()
{
  return MySigmaTT(Event->qsq_GeV(),
                   -Event->t_GeV(),
                   Event->w_GeV());
}
double SigmaCalc::sigma_lt()
{
  return MySigmaLT(Event->qsq_GeV(),
                   -Event->t_GeV(),
                   Event->w_GeV());
}

double SigmaCalc::epsilon()
{
  double q = Event->VirtPhot->P();
  double theta = Event->Theta();

  return 1/(1 + 2*(q*q)/(Event->qsq_GeV())*
            Power(Tan(theta/2),2));

}

double SigmaCalc::sigma_uu()
{
  double phi = Event->Phi();
  double eps = this->epsilon();
  double siguu = this->sigma_t();
  siguu += eps*this->sigma_l();
  siguu += Sqrt(2*eps*(1+eps))*this->sigma_lt()*Cos(phi);
  siguu += eps*this->sigma_tt()*Cos(2*phi);
  siguu /= 2*Pi();
  return siguu;
}

double SigmaCalc::Sigma_k(int k)
{
  double sigk = this -> sigma_uu()
    * Asyms->at(k)->GetAsyAmp(Event->qsq_GeV(),
                              Event->t_prime_GeV());
  // cout << sigk << endl;
  return sigk;
}

double SigmaCalc::sigma_ut()
{
  double phi = Event->Phi();
  double phi_s = Event->Phi_s();
  double theta = Event->Theta();
  double pt = Event->P_T;
  double sigut = Sin(phi - phi_s)*this->Sigma_k(0);
  sigut += Sin(phi_s)*this->Sigma_k(1);
  sigut += Sin(2*phi-phi_s)*this->Sigma_k(2);
  sigut += Sin(phi+phi_s)*this->Sigma_k(3);
  sigut += Sin(3*phi-phi_s)*this->Sigma_k(4);

  sigut *= -pt/(Sqrt(1-Power(Sin(theta)*Sin(phi_s),2)));

  return sigut;
}
