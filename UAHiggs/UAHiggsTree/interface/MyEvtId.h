#ifndef __MyEvtId_H__
#define __MyEvtId_H__

#include "TObject.h"

typedef unsigned long long TimeValue_t;


class MyEvtId : public TObject {

  public :
  MyEvtId(){;}
  ~MyEvtId(){;}

  void Reset(){
  	Run =      0;
  	Evt =      0;
  	LumiSect = 0;
  	Time     = -1;
  	IsData   = false;
  	ExpType  = 0;
  	Bunch    = -1;
  	Orbit    = -1;
  	};
 
  UInt_t       Run ;
  UInt_t       Evt ;
  UInt_t       LumiSect ;
  TimeValue_t  Time;
  Bool_t       IsData;
  UInt_t       ExpType;
  Int_t        Bunch;
  Int_t        Orbit;   
  Bool_t       PreselMarker;
  // Int_t        Store; 

  private:

  ClassDef (MyEvtId,1)
};

#endif
