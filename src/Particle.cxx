/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Implementation of Particle class. See Particle.hxx
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Particle.hxx"
#include "TVector3.h"

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
  return mass;
}
void Particle::SetMass(double x)
{
  mass = x;
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
  SetVectM(pthis, mass);
}

Particle::Particle(double m, double px, double py, double pz)
{
  TVector3 v(px,py,pz);
  SetVectM(v, m);
  mass = m;
}

Particle::Particle(double m, TVector3& v)
{
  SetVectM(v,m);
  mass = m;
}

Particle::Particle(double m, Particle a, Particle b)
{
  mass = m;
  Complete(a,b);
}
