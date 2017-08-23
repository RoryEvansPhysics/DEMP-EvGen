/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Implementation of Particle class. See Particle.hxx
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Particle.hxx"
#include "TVector3.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

int Particle::GetPid()
{
  return pid;
}
void Particle::SetPid(int x)
{
  pid = x;
}
int Particle::GetCharge()
{
  return charge;
}
void Particle::SetCharge(int x)
{
  charge = x;
}
double Particle::GetMass()
{
  return proper_mass;
}
void Particle::SetMass(double x)
{
  proper_mass = x;
}
double Particle::GetVx()
{
  return vx;
}
double Particle::GetVy()
{
  return vy;
}
double Particle::GetVz()
{
  return vz;
}
void Particle::SetVx(double x)
{
  vx = x;
}
void Particle::SetVy(double x)
{
  vy = x;
}
void Particle::SetVz(double x)
{
  vz = x;
}

int Particle::Complete(Particle a, Particle b)
{
  TVector3 pa = a.Vect();
  TVector3 pb = b.Vect();
  TVector3 p0(0,0,0);
  TVector3 pthis = p0 - (pa+pb);
  SetVectM(pthis, proper_mass);
}

Particle::Particle(double m, double px, double py, double pz)
{
  TVector3 v(px,py,pz);
  SetVectM(v, m);
  proper_mass = m;
}

Particle::Particle(double m, TVector3& v)
{
  SetVectM(v,m);
  proper_mass = m;
}

Particle::Particle(double m, Particle a, Particle b)
{
  proper_mass = m;
  Complete(a,b);
}

Particle Particle::operator + (const Particle& q)
{
  Particle result;
  double Eresult = this->E() + q.E();
  TVector3 Presult = this->Vect()+q.Vect();
  result.SetE(Eresult);
  result.SetVect(Presult);
  return result;
}

Particle Particle::operator - (const Particle& q)
{
  Particle result;
  double Eresult = this->E() - q.E();
  TVector3 Presult = this->Vect()-q.Vect();
  result.SetE(Eresult);
  result.SetVect(Presult);
  return result;
}

// PID and Proper_should not change
// This operator overload makes sure these things stay
// the same as new particles are generated, and that
// the memory allocation remains persistant
Particle Particle::operator = (const Particle& q)
{
  this->SetPxPyPzE(q.Px(),q.Py(),q.Pz(),q.E());
}

double Particle::Pmag()
{
  return this->Vect().Mag();
}

char * Particle::GetName()
{
  return identifier;
}

void Particle::SetName(char * name)
{
  identifier = name;
}
