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
    Double_t e,pt,eta,phi,px,py,pz;
    Double_t alpha,beta,discriminator;


  private:

  ClassDef (MyJet,1)
};

#endif
