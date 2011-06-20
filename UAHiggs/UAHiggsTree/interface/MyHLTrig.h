#ifndef __MyHLTrig_H__
#define __MyHLTrig_H__

#include "TObject.h"
#include <map>
using namespace std;

class MyHLTrig : public TObject {

  public :
  MyHLTrig(){;}
  ~MyHLTrig(){this->Reset();}

  map<string,bool> HLTmap;
  map<string,double> HLTprescale;

void Reset(){
  this->HLTmap.clear();
  this->HLTprescale.clear();
}


  private:

  ClassDef (MyHLTrig,1)
};

#endif



