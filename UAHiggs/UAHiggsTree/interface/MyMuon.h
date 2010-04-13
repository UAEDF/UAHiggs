#ifndef __MyMuon_H__
#define __MyMuon_H__

#include <vector>
#include "TObject.h"
#include "UAHiggs/UAHiggsTree/interface/MyPart.h"
#include "UAHiggs/UAHiggsTree/interface/MyTracks.h"
//#include "UAHiggs/UAHiggsTree/interface/MySupClus.h"

class MyMuon : public TObject {

  public :
    MyMuon();
    virtual ~MyMuon();


    MyPart      Part;
    MyTracks    globalTrack;    // Track reconstructed in both tracked and muon detector
    MyTracks    innerTrack;     // Track reconstructed in the tracker only
    MyTracks    outerTrack;     // Track reconstructed in the muon detector only
    
    // Basic properties            
    Double_t   isoR03sumPt   ;
    Double_t   isoR03emEt    ;
    Double_t   isoR03hadEt   ;
    Double_t   isoR03hoEt    ;
    Int_t      isoR03nTracks ;
    Int_t      isoR03nJets   ;

    Double_t   isoR05sumPt   ;
    Double_t   isoR05emEt    ;
    Double_t   isoR05hadEt   ;
    Double_t   isoR05hoEt    ;
    Int_t      isoR05nTracks ;
    Int_t      isoR05nJets   ;

    Double_t   calEnergyEm   ;
    Double_t   calEnergyHad  ;
    Double_t   calEnergyHo   ;
    Double_t   calEnergyEmS9 ;
    Double_t   calEnergyHadS9;
    Double_t   calEnergyHoS9 ;

    Bool_t     TMOneStationLoose      ;  
    Bool_t     TM2DCompatibilityLoose ; 
    Bool_t     PromptTight            ;

  private:

  ClassDef (MyMuon,1)
};

#endif

