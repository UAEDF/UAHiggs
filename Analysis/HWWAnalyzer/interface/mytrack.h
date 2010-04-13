#ifndef __MYTRACK_HH__
#define __MYTRACK_HH__
#include "TROOT.h"
#include "TObject.h"
#include <vector>
class mytrack : public TObject {
public :
  mytrack(){;}
  ~mytrack(){;}
  double px,py,pz,pt,eta,phi,charge,E;
  double ipx,ipy;
  double iperr_x,iperr_y;
  double Vz,Chi2,Ndof,VHits;
  ClassDef (mytrack,1)
};
#endif
