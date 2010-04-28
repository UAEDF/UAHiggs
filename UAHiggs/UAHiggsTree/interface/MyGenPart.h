#ifndef __MyGenPart_H__
#define __MyGenPart_H__

#include "TObject.h"
#include "TLorentzVector.h"

#include <string>

class MyGenPart : public TObject {

  public :
  MyGenPart(){;}
  ~MyGenPart(){;}

  Double_t pt,eta,phi,charge,e,px,py,pz,m; 
  TLorentzVector v;
  Int_t    pdgId,status,mo1,mo2,da1,da2;
  std::string   name; 

  private:

  ClassDef (MyGenPart,1)
};

#endif
