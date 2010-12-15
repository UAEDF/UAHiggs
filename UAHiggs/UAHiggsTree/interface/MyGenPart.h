#ifndef __MyGenPart_H__
#define __MyGenPart_H__

#include "TObject.h"
#include "TLorentzVector.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "MyPart.h"

class MyGenPart : public TObject {

  public :
  MyGenPart(){;}
  ~MyGenPart(){;}

  MyPart Part;
  Double_t pt,eta,phi,charge,e,px,py,pz,m; 
  //TLorentzVector v;
  Int_t    pdgId,status,mo1,mo2,da1,da2;
  std::string   name; 
 
  bool operator< ( const MyGenPart& genpart)
  {
  return this->pt < genpart.pt;
  }	
 // bool operator== ( const MyGenPart genpart)
 // {
//  return (*this).pt == genpart.pt;
//  }	
 
 
  private:

  ClassDef (MyGenPart,2)
};

#endif
