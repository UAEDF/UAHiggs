#ifndef __MyElectron_H__
#define __MyElectron_H__

#include <vector>
#include "TObject.h"
#include "Analysis/HWWGenPart/interface/MyPart.h"
#include "Analysis/HWWGenPart/interface/MyTracks.h"
//#include "Analysis/HWWGenPart/interface/MySupClus.h"

class MyElectron : public TObject {

  public :
    MyElectron();
    virtual ~MyElectron();
    Double_t e,pt,eta,phi,px,py,pz;


    MyPart      Part;
    MyTracks    GsfTrack;    
//    MySupClus   SupClus;
    
    // Basic properties            
    Double_t    eSupClusOverP      ;
    Double_t    eSeedClusOverPout  ; 
    Double_t    dEtaSupClusTrVtx   ; 
    Double_t    dEtaSeedClusTrCalo ; 
    Double_t    dPhiSupClusTrVtx   ; 
    Double_t    dPhiSeedClusTrCalo ; 
    Double_t    hadronicOverEm     ; 
    Bool_t      isEScaleCorr       ; 
    Bool_t      isMomentumCorr     ; 
    //Int_t       nClus              ; 
    Int_t       classification     ; 

    // Extra Isolation variables (Majid)
    Double_t    TrackerIsolationMajid;
    Float_t     eidTight;
    Double_t    EcalJurassicIsolation;

    // Extra shape variables
    Double_t    e3x3 ; 
    Double_t    e5x5 ;

  private:

  ClassDef (MyElectron,1)
};

#endif

