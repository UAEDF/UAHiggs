#ifndef __MyVertex_H__
#define __MyVertex_H__

#include "TObject.h"
#include "MyTracks.h"

class MyVertex : public TObject {

  public :
    MyVertex(){;}
    ~MyVertex(){;}

    Int_t    id;

    Double_t x,y,z;
    Double_t xerr,yerr,zerr;
    Double_t ex,ey,ez;    

    Double_t SumPtTracks;
    
    Bool_t validity;  
    Bool_t fake    ;
    Double_t chi2n ;
    Double_t chi2 ;
    Int_t    ndof ;
   
    Int_t  ntracks ;  

    //MyPart      Part;
    //Int_t       pdgId,status,mo1,mo2,da1,da2;
    //std::string name;

  private:

  ClassDef (MyVertex,1)
};

#endif

