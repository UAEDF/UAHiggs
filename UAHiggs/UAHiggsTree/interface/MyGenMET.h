#ifndef __MyGenMET_H__
#define __MyGenMET_H__

#include "TObject.h"
#include "TLorentzVector.h"
#include <vector>

// UAHiggsTree UAHiggs class declaration
#include "MyGenPart.h"


class MyGenMET : public TObject {

  public :
  MyGenMET(){;}
  ~MyGenMET(){;}

  // Filler
  // GetGenMET(  vector<MyGenMET> *GenMET );

  Double_t et;
  Double_t pt,eta,phi,e,px,py,pz; 
  Int_t    npart;

  std::vector<MyGenPart> METPart;

  private:

  ClassDef (MyGenMET,1)
};

#endif
