#ifndef __ElectronPlots_H__
#define __ElectronPlots_H__

#include <vector>
using namespace std;
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "./MyElectron.h"

class ElectronPlots : public TObject {

  public :
    ElectronPlots();
    ElectronPlots(TString);
    virtual ~ElectronPlots();

    TString Electroncoll;
    
    // Particle basic properties
    
    TH1F* pt; 
    TH1F* eta; 
    TH1F* phi; 
    
    // Basic properties            
    TH1F*    eSupClusOverP      ;
    TH1F*    eSeedClusOverPout  ; 
    TH1F*    PIn        ;
    TH1F*    POut        ;
    TH1F*    dEtaSupClusTrVtx   ; 
    TH1F*    dEtaSeedClusTrCalo ; 
    TH1F*    dPhiSupClusTrVtx   ; 
    TH1F*    dPhiSeedClusTrCalo ; 
    TH1F*    fbrem              ; 
    
    TH1F*      isBarrel           ; 
    TH1F*      isEndCap           ;
    
    TH1F*      isEcalDriven       ;
    TH1F*      isTrackerDriven    ;
   
    TH1F*      isEScaleCorr       ; 
    TH1F*      isMomentumCorr     ; 
    TH1F*      nClus              ; 
    TH1F*      classification     ; 
    
    

    // Extra Isolation variables 
    
   
    TH1F*    EcalRecHitIsoDr04       ;
    TH1F*    HcalDepth1TowerSumEtDr04;
    TH1F*    HcalDepth2TowerSumEtDr04;
    TH1F*    TrackIsolationDr04      ;
    TH1F*    EcalRecHitIsoDr03       ;
    TH1F*    HcalTowerSumEtDr03      ;
    TH1F*    HcalDepth1TowerSumEtDr03;
    TH1F*    HcalDepth2TowerSumEtDr03;
    TH1F*    TrackIsolationDr03      ;
    
    
    TH1F*    IsolationCombinedEndCap03     ;  
    TH1F*    IsolationCombinedBarrel03     ;  
    
    
    // Id variables
    
    TH1F*    eidRobustLoose       ; 
    TH1F*    eidRobustTight       ;
    TH1F*    eidLoose             ;
    TH1F*    eidTight             ;
    
    // Extra shape variables
    
    TH1F* E15                    ;                 
    TH1F* E25Max                 ; 
    TH1F* E55                    ;
    TH1F* CovEtaEta              ;      
    TH1F* CoviEtaiEta            ;     
    TH1F* HadronicOverEm         ;  
    TH1F* HcalDepth1OverEcal     ;    
    TH1F* HcalDepth2OverEcal     ;
    
    TH1F* d0;
    
    
    // conversion variables
    
    TH1F* dist_conv   ;
    TH1F* dcot_conv ;
    
   
       
    
    void init();
    void fill(vector<MyElectron>& , double = 1., int = -1);
    void fill(vector<MyElectron*>& , double = 1., int = -1);
    void fill(MyElectron& , double = 1., int = -1);
    
    void write();
    
    
    ClassDef (ElectronPlots,1)
};



#endif


