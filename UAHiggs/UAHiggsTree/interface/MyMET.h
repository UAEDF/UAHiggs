#ifndef __MyMET_H__
#define __MyMET_H__

#include <vector>
#include "TObject.h"
#include "UAHiggs/UAHiggsTree/interface/MyPart.h"
#include "UAHiggs/UAHiggsTree/interface/MyTracks.h"
//#include "UAHiggs/UAHiggsTree/interface/MySupClus.h"

class MyMET : public TObject {

  public :
    MyMET();
    virtual ~MyMET();


    
    Double_t    pt,eta,phi;
  

  private:

  ClassDef (MyMET,1)
};

#endif
