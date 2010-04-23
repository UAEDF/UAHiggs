#ifndef __MyL1Trig_H__
#define __MyL1Trig_H__

#include "TObject.h"
#include <map>
using namespace std;

class MyL1Trig : public TObject {

  public :
  MyL1Trig();
  virtual ~MyL1Trig();

  bool PhysTrigWord[128];
  bool TechTrigWord[64];
  
  map<string,bool> L1map;

//  void Reset();
 

  private:

  ClassDef (MyL1Trig,1)
};

#endif
