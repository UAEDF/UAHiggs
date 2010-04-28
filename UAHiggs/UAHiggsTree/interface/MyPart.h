#ifndef __MyPart_H__
#define __MyPart_H__

#include "TObject.h"
#include "TLorentzVector.h"

class MyPart : public TObject {

  public :
    MyPart(){;}
    ~MyPart(){;}

  // private:

    Double_t       charge;
    TLorentzVector v;

    TLorentzVector vmpi(){
    	Double_t mpion = 139.57018;
        TLorentzVector vm;
        vm.SetPtEtaPhiM( this->v.Pt() , this->v.Eta() , this->v.Phi() , mpion );
        return vm;
        };

  private:

    ClassDef (MyPart,1)
};



#endif


