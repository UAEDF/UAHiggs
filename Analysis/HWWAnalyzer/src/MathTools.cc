#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"

double HWWAnalyzer::deltaR(double eta1, double eta2, double phi1, double phi2) 
{
  double dphi = fabs(phi1-phi2);
  if(dphi > M_PI) 
    {
      dphi = (2*M_PI - dphi);
    }
  double deta = fabs(eta1-eta2);
  return sqrt(dphi*dphi + deta*deta);
}
double HWWAnalyzer::deltaphi(double phi1, double phi2) 
{
  double dphi = fabs(phi1-phi2);
  if(dphi > M_PI) 
    {
      dphi = (2*M_PI - dphi);
    }
  return dphi;
}
double HWWAnalyzer::CorrectPhi(double phi, double x, double y)
{
  if(phi>0 && x<0 && y<0)phi+=M_PI;
  if(phi<0 && x>0 && y<0)phi=(2*M_PI-fabs(phi));
  if(phi<0 && x<0 && y>0)phi=(M_PI-fabs(phi));
  if(y<0)phi-=(2*M_PI);//without this you have 0<phi<2pi, but with this
  return phi;//you get -pi<phi<pi
}
