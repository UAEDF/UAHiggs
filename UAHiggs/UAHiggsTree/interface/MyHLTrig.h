#ifndef __MyHLTrig_H__
#define __MyHLTrig_H__

#include "TObject.h"
#include <map>
using namespace std;

class MyHLTrig : public TObject {

  public :
  MyHLTrig();
  virtual ~MyHLTrig();

 
  
  map<string,bool> HLTmap;

//  void Reset();
 

  private:

  ClassDef (MyHLTrig,1)
};

#endif
