#ifndef __MyJet_H__
#define __MyJet_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include "MyTracks.h"


class MyJet : public TObject {

  public :
    MyJet(){;}
    ~MyJet(){;}
    Double_t neutralPx;
    Double_t neutralPy;
    Double_t neutralPz;
   
    
    Double_t e,pt,eta,phi,px,py,pz;
    Double_t alpha,beta,discriminator;
    Double_t ChargedHadronEnergy;
    Double_t NeutralHadronEnergy;
    Double_t ChargedEmEnergy;
    Double_t ChargedMuEnergy;
    Double_t NeutralEmEnergy;
    Double_t Area;
    Double_t rho;
    Int_t    ChargedMultiplicity;
    Int_t    NeutralMultiplicity;
    Int_t    MuonMultiplicity;

    vector<MyTracks>    tracks;
    Int_t nTracks; 
  
  private:

  ClassDef (MyJet,1)
};

#endif
