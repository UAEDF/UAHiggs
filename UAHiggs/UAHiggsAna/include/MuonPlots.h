#ifndef __MuonPlots_H__
#define __MuonPlots_H__

#include <vector>
using namespace std;
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "./MyMuon.h"

class MuonPlots : public TObject {

  public :
    MuonPlots();
    MuonPlots(TString);
    virtual ~MuonPlots();

    TString Muoncoll;
    
    // Particle basic properties
    
    TH1F* pt; 
    TH1F* eta; 
    TH1F* phi; 
    
   
   // Basic properties            
    TH1F*   isoR03sumPt   ;
    TH1F*   isoR03emEt    ;
    TH1F*   isoR03hadEt   ;
    TH1F*   isoR03hoEt    ;
    TH1F*   isoR03nTracks ;
    TH1F*   isoR03nJets   ;
    TH1F*   isolationCombined03;
    
    
    TH1F*   isoR05sumPt   ;
    TH1F*   isoR05emEt    ;
    TH1F*   isoR05hadEt   ;
    TH1F*   isoR05hoEt    ;
    TH1F*   isoR05nTracks ;
    TH1F*   isoR05nJets   ;

    TH1F*   calEnergyEm   ;
    TH1F*   calEnergyHad  ;
    TH1F*   calEnergyHo   ;
    TH1F*   calEnergyEmS9 ;
    TH1F*   calEnergyHadS9;
    TH1F*   calEnergyHoS9 ;

    TH1F*   IsGlobalMuon     ;
    TH1F*   IsTrackerMuon    ;
    TH1F*   IsStandaloneMuon ;
    TH1F*   IsCaloMuon       ;
    
    // Muon Id
    
     
     TH1F*   AllGlobalMuons                           ;
     TH1F*   AllStandAloneMuons                       ;
     TH1F*   AllTrackerMuons                          ;
     TH1F*   TrackerMuonArbitrated                    ;
     TH1F*   AllArbitrated                            ;
     TH1F*   GlobalMuonPromptTight                    ;
     TH1F*   TMLastStationLoose                       ;
     TH1F*   TMLastStationTight                       ;
     TH1F*   TM2DCompatibilityLoose                   ;
     TH1F*   TM2DCompatibilityTight                   ;
     TH1F*   TMOneStationLoose                        ;
     TH1F*   TMOneStationTight                        ;
     TH1F*   TMLastStationOptimizedLowPtLoose         ;
     TH1F*   TMLastStationOptimizedLowPtTight         ;
     TH1F*   GMTkChiCompatibility                     ;
     TH1F*   GMStaChiCompatibility                    ;
     TH1F*   GMTkKinkTight                            ;
     TH1F*   TMLastStationAngLoose                    ;
     TH1F*   TMLastStationAngTight                    ;
     TH1F*   TMOneStationAngLoose                     ;
     TH1F*   TMOneStationAngTight                     ;
     TH1F*   TMLastStationOptimizedBarrelLowPtLoose   ;
     TH1F*   TMLastStationOptimizedBarrelLowPtTight   ;
     
     TH1F *  d0; 
    
     TH1F* nTrackerHits;
     TH1F* nMuonHits; 
     TH1F* chi2Track;
   
   
     void init();
     void fill(vector<MyMuon*>& , double = 1., int =1 );
     void fill(vector<MyMuon>& , double = 1., int =1 );
     void fill(MyMuon& , double = 1., int = -1);
     void write();
    
    
    ClassDef (MuonPlots,1)
};



#endif


