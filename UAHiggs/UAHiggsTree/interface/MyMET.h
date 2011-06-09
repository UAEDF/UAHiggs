#ifndef __MyMET_H__
#define __MyMET_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include "MyTracks.h"
//#include "UAHiggs/UAHiggsTree/interface/MySupClus.h"

class MyMET : public TObject {

  public :
    MyMET(){;}
    ~MyMET(){;}


    
    Double_t    pt,eta,phi;
    Double_t    significance;

  private:

  ClassDef (MyMET,1)
};

#endif
