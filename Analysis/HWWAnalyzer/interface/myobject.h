#ifndef __MYOBJECT_HH__
#define __MYOBJECT_HH__
#include "TROOT.h"
#include "TObject.h"
using namespace std;
#include <vector>
#include "mytrack.h"
class myobject : public TObject {
public :
  myobject(){;}
  ~myobject(){;}

  double pt,eta,phi,charge,E,px,py,pz;
  double corrpt,corrpx,corrpy,corrphi;
  double DepositR03Ecal;
  double DepositR03Hcal;
  double DepositR03TrackerOfficial;
  double alpha;
  double discriminator;
  double HcalIsolation;
  double EcalIsolation;
  double TrackerIsolation;
  double EcalJurassicIsolation;
  int classification; 
  double HoverE;      
  double EseedPout;   
  double dEta;        
  double dPhi;        
  double s9s25;
  double sigmaEtaEta;
  bool eidTight;
  bool GlobalMuonPromptTight;
  bool TMOneStationLoose;
  bool TM2DCompatibilityLoose;
  string name;

  ClassDef (myobject,1)
};
#endif
