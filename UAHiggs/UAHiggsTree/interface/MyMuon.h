#ifndef __MyMuon_H__
#define __MyMuon_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include "MyTracks.h"
//#include "UAHiggs/UAHiggsTree/interface/MySupClus.h"

class MyMuon : public TObject {

  public :
    MyMuon(){;}
    ~MyMuon(){;}

    Double_t e,pt,eta,phi,px,py,pz;
    
    MyPart      Part;
    MyTracks    globalTrack;    // Track reconstructed in both tracked and muon detector
    MyTracks    innerTrack;     // Track reconstructed in the tracker only
    MyTracks    outerTrack;     // Track reconstructed in the muon detector only
    
    std::vector<Int_t>     vtxid;
    std::vector<Double_t>  tip     ;
    std::vector<Double_t>  tipErr  ;
    std::vector<Double_t>  ip      ;
    std::vector<Double_t>  ipErr   ;
    std::vector<Double_t>  tip2     ;
    std::vector<Double_t>  tip2Err  ;
    std::vector<Double_t>  ip2      ;
    std::vector<Double_t>  ip2Err   ;


    Int_t   nChambers;
    Int_t   nChambersMatched;
    
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

    Bool_t     IsGlobalMuon       ;
    Bool_t     IsTrackerMuon      ;
    Bool_t     IsStandaloneMuon   ;
    Bool_t     IsCaloMuon         ;
    
    // Muon Id
    
     
     Bool_t   AllGlobalMuons                           ;
     Bool_t   AllStandAloneMuons                       ;
     Bool_t   AllTrackerMuons                          ;
     Bool_t   TrackerMuonArbitrated                    ;
     Bool_t   AllArbitrated                            ;
     Bool_t   GlobalMuonPromptTight                    ;
     Bool_t   TMLastStationLoose                       ;
     Bool_t   TMLastStationTight                       ;
     Bool_t   TM2DCompatibilityLoose                   ;
     Bool_t   TM2DCompatibilityTight                   ;
     Bool_t   TMOneStationLoose                        ;
     Bool_t   TMOneStationTight                        ;
     Bool_t   TMLastStationOptimizedLowPtLoose         ;
     Bool_t   TMLastStationOptimizedLowPtTight         ;
     Bool_t   GMTkChiCompatibility                     ;
     Bool_t   GMStaChiCompatibility                    ;
     Bool_t   GMTkKinkTight                            ;
     Bool_t   TMLastStationAngLoose                    ;
     Bool_t   TMLastStationAngTight                    ;
     Bool_t   TMOneStationAngLoose                     ;
     Bool_t   TMOneStationAngTight                     ;
     Bool_t   TMLastStationOptimizedBarrelLowPtLoose   ;
     Bool_t   TMLastStationOptimizedBarrelLowPtTight   ;
     
    
   
 

  private:

  ClassDef (MyMuon,1)
};

#endif

