#include "FSI.hxx"

#include "TMath.h"

#include "CustomRand.hxx"
#include "Particle.hxx"
#include "Constants.hxx"
#include 

#include <stdio.h>
#include "json/json.h"

using namespace std;
using namespace constants;
using namespace TMath;

FSI::FSI()
{
  double ERange[2] = {0,1};
  double ThetaRange[2] = {0,Pi()};
  double PhiRange[2] = {0,2*Pi()};
  char fname[100] = "FSI";
  SpherePicker = new CustomRand(fname, ERange, ThetaRange, PhiRange);

  extern Json::Value obj;
  ProtGen = new TargetGen(proton_mass_mev, obj["fermi_momentum"].asBool());

  CoP = new TVector3();

  VertInPion = new Particle(pion_mass_mev, "", pid_pion);
  VertTargProt = new Particle(proton_mass_mev, "", pid_prot);

  CMInPion = new Particle(pion_mass_mev, "", pid_pion);
  CMTargProt = new Particle(proton_mass_mev, "", pid_prot);

  VertOutPion = new Particle(pion_mass_mev, "", pid_pion);
  VertOutProt = new Particle(proton_mass_mev, "", pid_prot);

  CMOutPion = new Particle(pion_mass_mev, "", pid_pion);
  CMOutProt = new Particle(proton_mass_mev, "", pid_prot);
}

void FSI::Generate()
{

  *VertTargProt = *ProtGen->GetParticle();

  *CMInPion = *VertInPion;
  *CMTargProt = *VertTargProt;

  //cout << "Pion Momentum Before:\t"<<CMInPion->P() << endl;
  //cout << "Proton Momentum Before:\t"<<CMTargProt->P()<<endl;

  *CoP = ((VertInPion->Vect()+VertTargProt->Vect())*
          (1.0/(VertInPion->E()+VertTargProt->E())));


  CMInPion->Boost(-(*CoP));
  //cout << "Pion Momentum After:\t"<<CMInPion->P() << endl;
  CMTargProt->Boost(-(*CoP));
  //cout << "Proton Momentum After:\t"<<CMTargProt->P()<<endl;

  theta_pion = SpherePicker->Theta();
  phi_pion = SpherePicker->Phi();

  a = Sqrt(Power(pion_mass_mev, 2)+Power(CMInPion->P(), 2))
    + Sqrt(Power(proton_mass_mev, 2)+Power(CMTargProt->P(), 2));
  //cout<<a<<endl;
  b = Power(pion_mass_mev, 2);
  //cout<<b<<endl;
  c = Power(proton_mass_mev, 2);
  //cout<<c<<endl;

  x = (Power(a, 4)+Power(b, 2)-2*a*a*b-2*a*a*c-2*b*c)/(4*a*a);

  //cout<<x<<endl;

  p_pion = Sqrt(x);

  //cout<<p_pion<<endl;

  CMOutPion->SetThetaPhiP(theta_pion, phi_pion, p_pion);
  //cout << "Pion final P:\t" << CMOutPion->P() << endl;
  CMOutProt->SetVectM(-(CMOutPion->Vect()), proton_mass_mev);
  //cout << "Prot final P:\t" << CMOutProt->P() << endl;

  *VertOutPion = *CMOutPion;
  *VertOutProt = *CMOutProt;

  VertOutProt->Boost((*CoP));
  VertOutPion->Boost((*CoP));

 //cout << "Boost x:\t" << CoP->X() <<endl;
 //cout << "Prot x: \t" << CMOutProt->X()<<endl;
 //cout << "Boost y:\t" << CoP->Y() <<endl;
 //cout << "Prot y: \t" << CMOutProt->Y()<<endl;
 //cout << "Boost z:\t" << CoP->Z() <<endl;
 //cout << "Prot z: \t" << CMOutProt->Z()<<endl;
 //cout << "CM E:\t" << CMOutProt->E()<<endl;
 //cout << "Vert E:\t" << VertOutProt->E()<<endl;

}
