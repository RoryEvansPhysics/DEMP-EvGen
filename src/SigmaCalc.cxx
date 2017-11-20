#include <vector>

#include "TMath.h"

#include "DEMPEvent.hxx"
#include "Asymmetry.hxx"

#include "SigmaL.hxx"
#include "SigmaT.hxx"
#include "SigmaLT.hxx"
#include "SigmaTT.hxx"
#include "Constants.hxx"

#include "correction.h"

#include "SigmaCalc.hxx"

using namespace std;
using namespace constants;
using namespace TMath;

SigmaCalc::SigmaCalc(DEMPEvent* in_Event):Event(in_Event)
{
  vector<double> qsq;
  qsq.push_back(4.107);
  qsq.push_back(4.335);
  qsq.push_back(4.845);
  qsq.push_back(5.138);
  qsq.push_back(5.557);
  qsq.push_back(5.948);
  qsq.push_back(6.049);
  qsq.push_back(6.393);
  qsq.push_back(6.778);
  qsq.push_back(6.894);
  qsq.push_back(7.617);

  Asyms = new vector<Asymmetry*>(5);

  Asyms->at(0) =
    new Asymmetry("asy",
                  "[0]*exp([1]*x)+(-[2]-[0])*exp([3]*x)+[2]",
                  qsq, false);

  Asyms->at(1) =
    new Asymmetry("asysfi",
                  "[0]*exp([1]*x)+[2]",
                  qsq, false);
  Asyms->at(1)->Parameterize(qsq);

  Asyms->at(2) =
    new Asymmetry("asy2fi",
                  "[0]*exp([1]*x)+[2]",
                  qsq, false);

  Asyms->at(3) =
    new Asymmetry("asyfpfs",
                  "[0]*exp([1]*x)+[2]",
                  qsq, false);

  Asyms->at(4) =
    new Asymmetry("asy3f",
                  "[0]*exp([1]*x)+[2]",
                  qsq, false);

}

double SigmaCalc::sigma_l()
{
<<<<<<< HEAD
  if(*Event->t_GeV < -1.5)
    return 1e-6;
  else{
    return MySigmaL(*Event->qsq_GeV,
                    -*Event->t_GeV,
                    *Event->w_GeV);
  }
=======
  return MySigmaL(*Event->qsq_GeV,
                  -*Event->t_GeV,
                  *Event->w_GeV);
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros
}

double SigmaCalc::sigma_t()
{
<<<<<<< HEAD
  if (*Event->t_GeV < -1.5)
    return 1e-6;
  else{
    return MySigmaT(*Event->qsq_GeV,
                    -*Event->t_GeV,
                    *Event->w_GeV);
  }
=======
  return MySigmaT(*Event->qsq_GeV,
                  -*Event->t_GeV,
                  *Event->w_GeV);
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros
}

double SigmaCalc::sigma_tt()
{
<<<<<<< HEAD
  if (*Event->t_GeV < -1.5)
    return 1e-7;
  else{
    double sig_tt = MySigmaTT(*Event->qsq_GeV,
                              -*Event->t_GeV,
                              *Event->w_GeV);
    if ((sig_tt<0) && (Abs(sig_tt)>abs(this->sigma_t())))
      sig_tt = correctionToSigTT(sig_tt,
                                 this->sigma_t(),
                                 *Event->qsq_GeV);
    return sig_tt;
  }
=======
  double sig_tt = MySigmaTT(*Event->qsq_GeV,
                            -*Event->t_GeV,
                            *Event->w_GeV);
  if ((sig_tt<0) && (Abs(sig_tt)>abs(this->sigma_t())))
    sig_tt = correctionToSigTT(sig_tt,
                               this->sigma_t(),
                               *Event->qsq_GeV);
  return sig_tt;
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros
}

double SigmaCalc::sigma_lt()
{
<<<<<<< HEAD
  if (*Event->t_GeV < -1.5)
    return 1e-7;
  else{
    double sig_lt = MySigmaLT(*Event->qsq_GeV,
                              -*Event->t_GeV,
                              *Event->w_GeV);
    if ((sig_lt<0) && (Abs(sig_lt)>abs(this->sigma_t())))
      sig_lt = correctionToSigLT(sig_lt,
                                 this->sigma_t(),
                                 *Event->qsq_GeV);
    return sig_lt;
  }
=======
  double sig_lt = MySigmaLT(*Event->qsq_GeV,
                            -*Event->t_GeV,
                            *Event->w_GeV);
  if ((sig_lt<0) && (Abs(sig_lt)>abs(this->sigma_t())))
    sig_lt = correctionToSigLT(sig_lt,
                               this->sigma_t(),
                               *Event->qsq_GeV);
  return sig_lt;
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros
}

double SigmaCalc::epsilon()
{
  double q = Event->VirtPhot->P()/1000;
  double theta = *Event->Theta;

  return 1.0/(1.0 + 2.0*(q*q)/(*Event->qsq_GeV)*
<<<<<<< HEAD
              Power(Tan(theta/2),2));
=======
            Power(Tan(theta/2),2));
>>>>>>> 5c3c38b... Added some old analysis macros under /Macros

}

double SigmaCalc::sigma_uu()
{
  double phi = *Event->Phi;
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
  double sigk = this -> Asyms->at(k)
    ->GetAsyAmp(*Event->qsq_GeV,
                *Event->t_prime_GeV);
  // cout << sigk << endl;
  return sigk;
}

double SigmaCalc::sigma_ut()
{
  double phi = *Event->Phi;
  double phi_s = *Event->Phi_s;
  double theta = *Event->Theta;
  double pt = *Event->P_T;
  double sigut = Sin(phi - phi_s)*this->Sigma_k(0);
  //cout << sigut << endl;
  sigut += Sin(phi_s)*this->Sigma_k(1);
  sigut += Sin(2*phi-phi_s)*this->Sigma_k(2);
  sigut += Sin(phi+phi_s)*this->Sigma_k(3);
  sigut += Sin(3*phi-phi_s)*this->Sigma_k(4);

  sigut *= -pt/(Sqrt(1-Power(Sin(theta)*Sin(phi_s),2)));
  sigut *= this->sigma_uu();

  return sigut;
}

double SigmaCalc::sigma()
{
  return (this->sigma_uu()+sigma_ut())*this->fluxfactor();
}

double SigmaCalc::weight(int nGen)
{
  return (this->sigma())*PSF*nBcm2*Lumi/nGen;
}

double SigmaCalc::fluxfactor()
{
  double ff = alpha/(2*Power(Pi(),2));
  ff *= (Event->ScatElec->E())/(EBeam);
  ff /= *(Event->qsq_GeV);
  ff /= 1-this->epsilon();
  ff *= (Power((*Event->w_GeV)*1000,2))-Power(neutron_mass_mev,2);
  ff /= Power(neutron_mass_mev,2);
  return ff;
}
