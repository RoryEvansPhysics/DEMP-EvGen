/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Implementation of Particle class. See Particle.hxx
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Particle.hxx"

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
