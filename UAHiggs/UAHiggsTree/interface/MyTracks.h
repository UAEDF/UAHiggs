#ifndef __MyTracks_H__
#define __MyTracks_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"

class MyTracks : public TObject {

  public :
    MyTracks(){;}
    ~MyTracks(){;}

    //Double_t px,py,pz,eta;

    MyPart      Part;

    Bool_t   quality[3];
    Int_t   nhit;
    Int_t   numberOfValidTkHits;
    Int_t   numberOfValidMuonHits;
    Int_t   numberOfValidPixelHits;
    Int_t   numberOfValidStripHits;  //can also look individual layer but do it later if needed ...
    Int_t   numberOfValidMuonCSCHits;
    Int_t   numberOfValidMuonDTHits;
    Int_t   numberOfValidMuonRPCHits;
    
    Double_t chi2n;
    Double_t dz  , d0 ;
    Double_t edz , ed0 , ept ; 
    Double_t vx, vy, vz ;

    std::vector<Int_t>     vtxid;
    std::vector<Double_t>  vtxdxy  ;
    std::vector<Double_t>  vtxdz   ;

  private:

  ClassDef (MyTracks,1)
};

#endif

