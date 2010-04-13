#ifndef __MyGenJet_H__
#define __MyGenJet_H__

#include "TObject.h"
#include "TLorentzVector.h"
#include <vector>

// UAHiggsTree UAHiggs class declaration
#include "UAHiggs/UAHiggsTree/interface/MyGenPart.h"


class MyGenJet : public TObject {

  public :
  MyGenJet();
  virtual ~MyGenJet();

  // Filler
  // GetGenJet(  vector<MyGenJet> *GenJet );

  Double_t et;
  Double_t pt,eta,phi,e,px,py,pz; 
  Int_t    npart;

  std::vector<MyGenPart> JetPart;

  private:

  ClassDef (MyGenJet,1)
};

#endif
