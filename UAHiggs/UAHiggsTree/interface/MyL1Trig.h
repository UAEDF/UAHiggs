#ifndef __MyL1Trig_H__
#define __MyL1Trig_H__

#include "TObject.h"
#include <map>
using namespace std;

class MyL1Trig : public TObject {

  public :
  MyL1Trig(){;}
  ~MyL1Trig(){;}

  bool PhysTrigWord[128];
  bool TechTrigWord[64];
  
  map<string,bool> L1map;

void Reset(){
  for (int i = 0; i < 128; i++) PhysTrigWord[i] =  false ;
  for (int i = 0; i < 64 ; i++) TechTrigWord[i] =  false ;
  this->L1map.clear();
}

 

  private:

  ClassDef (MyL1Trig,1)
};

#endif
