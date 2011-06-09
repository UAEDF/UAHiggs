#ifndef __MyPUSumInfo_H__
#define __MyPUSumInfo_H__

#include <iostream>
#include <vector>
#include "TObject.h"

using namespace std;

class MyPUSumInfo : public TObject {

  public :
    MyPUSumInfo();
    virtual ~MyPUSumInfo();

    void Reset();
    void Print();

    Int_t             nPU          ;
    vector<Float_t>   zposition    ;
    vector<Float_t>   sumpT_lowpT  ;
    vector<Float_t>   sumpT_highpT ;
    vector<Int_t>     ntrks_lowpT  ;
    vector<Int_t>     ntrks_highpT ;
    Double_t          median_rho   ;
    Double_t          rho_iso      ;
    vector<Double_t>  rho_eta      ; //1st entry is eta = -4, 2nd entry is eta = -3, etc ... ( 9entries total)
  
  private:

    ClassDef (MyPUSumInfo,1)
};

#endif

