#ifndef __MyElectron_H__
#define __MyElectron_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include "MyTracks.h"
//#include "UAHiggs/UAHiggsTree/interface/MySupClus.h"

class MyElectron : public TObject {

  public :
    MyElectron(){;}
    ~MyElectron(){;}
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
    Double_t    fbrem              ; 
    
    Bool_t      isBarrel           ; 
    Bool_t      isEndCap           ;
    
    Bool_t      isEcalDriven       ;
    Bool_t      isTrackerDriven    ;
   
    Bool_t      isEScaleCorr       ; 
    Bool_t      isMomentumCorr     ; 
    //Int_t       nClus              ; 
    Int_t       classification     ; 
    
    

    // Extra Isolation variables 
    
   
    Double_t    EcalJurassicIsolation;
    Double_t    TrackIsolationDr04;
    Double_t    EcalIsolationDr03;
    Double_t    HcalIsolationDr03 ;
    
    
    // Id variables
    
     Bool_t    eidRobustLoose       ; 
     Bool_t    eidRobustTight       ;
     Bool_t    eidLoose             ;
     Bool_t    eidTight             ;
    
    // Extra shape variables
    
    Double_t E15                    ;                 
    Double_t E25Max                 ; 
    Double_t E55                    ;
    Double_t CovEtaEta              ;      
    Double_t CoviEtaiEta            ;     
    Double_t HadronicOverEm         ;  
    Double_t HcalDepth1OverEcal     ;    
    Double_t HcalDepth2OverEcal     ;
    
    
    
   
  private:



  ClassDef (MyElectron,1)
};

#endif

