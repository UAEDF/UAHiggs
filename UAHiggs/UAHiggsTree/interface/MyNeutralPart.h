#ifndef __MyNeutralPart_H__
#define __MyNeutralPart_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include "MyTracks.h"


class MyNeutralPart : public TObject {

  public :
    MyNeutralPart(){;}
    ~MyNeutralPart(){;}
    
    double px,py,pz,eta;
    
  private:

  ClassDef (MyNeutralPart,1)
};

#endif
