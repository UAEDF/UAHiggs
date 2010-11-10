
// Package:     UAHiggsTree
// Class:       UAHiggsTree
// author:      Xavier Janssen
// Date:        22/03/2010 
//
// Description: Function to retrieve Gsf Electron 

// system include files
#include <memory>
#include <string>
#include <iostream>
   
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Genaral Tracks and Vertex
//#include "DataFormats/TrackReco/interface/Track.h"
//#include "DataFormats/TrackReco/interface/TrackFwd.h"
//#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "DataFormats/VertexReco/src/Vertex.cc"
//#include "DataFormats/VertexReco/interface/VertexFwd.h"

// Gsf Electron
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronIsoCollection.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronIsoNumCollection.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/ClusterShape.h"
#include "DataFormats/EgammaReco/interface/BasicClusterShapeAssociation.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/Common/interface/ValueMap.h"

// Candidates
#include "DataFormats/Candidate/interface/CandAssociation.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

// CaloTower
//#include "DataFormats/CaloTowers/interface/CaloTower.h"
//#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"

// Isolation
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"

// UAHiggsTree UAHiggs class declaration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"

//Tracks and conversion

#include "DataFormats/TrackReco/interface/Track.h"
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "RecoEgamma/EgammaTools/interface/ConversionInfo.h"

void UAHiggsTree::GetRecoElectron(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                                          const string GsfElectronCollection_ ,vector<MyElectron>& ElecVector )
{
   using namespace std;
   using namespace edm;

   ElecVector.clear();

   // Get Gsf Electron Collection 
   Handle<reco::GsfElectronCollection> gsfElectronsHandle;
   try {
     iEvent.getByLabel(GsfElectronCollection_,gsfElectronsHandle);
   } catch ( cms::Exception& ex ) {
     printf("Error! can't get GsfElectronCollection_ collection \n");
   }
   const reco::GsfElectronCollection gsfElectrons = *(gsfElectronsHandle.product());

   // get the association of the clusters to their shapes for EB
   edm::Handle<reco::BasicClusterShapeAssociationCollection> barrelClShpHandle ;
   try { 
     iEvent.getByLabel ("hybridSuperClusters","hybridShapeAssoc", barrelClShpHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get ECAL barrel Cluster Shape Collection\n");
   }
   const reco::BasicClusterShapeAssociationCollection& barrelClShpMap = *barrelClShpHandle ;


   // Tracker Isolation handle (Guillelmo)
   edm::Handle< reco::GsfElectronIsoCollection > tkIsolationHandle;
   try {
     iEvent.getByLabel(trckIsolationProducer_, tkIsolationHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get tracker isolation product\n");
   }


   // Another way of getting electron info
   edm::Handle< edm::View<reco::Candidate> > emObjectHandle;
   try {
     iEvent.getByLabel("pixelMatchGsfElectrons",emObjectHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get emObjectHandle Collection\n");
   }
 
   

   
   // Loop on Gsf Electron
   for (reco::GsfElectronCollection::const_iterator iElectron = gsfElectrons.begin();
        iElectron!= gsfElectrons.end();iElectron++) {
    
   
     MyElectron electron;

     unsigned int iEl = iElectron - gsfElectrons.begin();
     reco::GsfElectronRef eRef(gsfElectronsHandle,iEl);

     // Gsf Electron General 

     electron.pt  = iElectron->pt(); 
     electron.px  = iElectron->px(); 
     electron.py  = iElectron->py(); 
     electron.pz  = iElectron->pz(); 
     electron.e   = iElectron->superCluster()->energy(); 
     electron.eta = iElectron->eta(); 
     electron.phi = iElectron->phi(); 

     electron.Part.v.SetPxPyPzE(iElectron->px(),
                                iElectron->py(),
                                iElectron->pz(),  
                                iElectron->superCluster()->energy());
     electron.Part.charge = iElectron->charge(); 

     electron.eSupClusOverP      = iElectron->eSuperClusterOverP()              ;
     electron.eSeedClusOverPout  = iElectron->eSeedClusterOverPout()            ;
     electron.PIn                = iElectron->trackMomentumAtVtx().R();
     electron.POut               = iElectron->trackMomentumOut().R();
     
     
     electron.dEtaSupClusTrVtx   = iElectron->deltaEtaSuperClusterTrackAtVtx()  ;
     electron.dEtaSeedClusTrCalo = iElectron->deltaEtaSeedClusterTrackAtCalo()  ; 
     electron.dPhiSupClusTrVtx   = iElectron->deltaPhiSuperClusterTrackAtVtx()  ; 
     electron.dPhiSeedClusTrCalo = iElectron->deltaPhiSeedClusterTrackAtCalo()  ; 
     electron.isEScaleCorr       = iElectron->isEnergyScaleCorrected()          ; 
     electron.isMomentumCorr     = iElectron->isMomentumCorrected()             ; 
     electron.isEcalDriven       = iElectron->ecalDrivenSeed()                  ;
     electron.isTrackerDriven    = iElectron->trackerDrivenSeed()               ;
     electron.nClus              = iElectron->basicClustersSize()                ; 
     electron.classification     = iElectron->classification()                  ; 
     electron.fbrem              = iElectron->fbrem()                           ; 
     
     
     //fiducial
     
     electron.isBarrel           = iElectron->isEB()				;
     electron.isEndCap           = iElectron->isEE()				;
     
      
     // Shower Shape variables
     
     
    electron.E15                     = iElectron->e1x5();
    electron.E25Max                  = iElectron->e2x5Max();
    electron.E55                     = iElectron->e5x5();
    electron.CovEtaEta               = iElectron->sigmaEtaEta();
    electron.CoviEtaiEta             = iElectron->sigmaIetaIeta();
    electron.HadronicOverEm          = iElectron->hcalOverEcal();
    electron.HcalDepth1OverEcal      = iElectron->hcalDepth1OverEcal();
    electron.HcalDepth2OverEcal      = iElectron->hcalDepth2OverEcal();

  //  electron.expectedInnerHits = 0; 
    
  //  try{
  //   printf("Ciao\n");
    edm::Handle<edm::ValueMap<int> > vmEl;
    iEvent.getByLabel("expectedHitsEle",vmEl);
    // fill corrected expected inner hits
    electron.expectedInnerHits      =  (*vmEl)[eRef];
    //cout<<(*vmEl)[eRef]<<endl;
   // cou<<"ciao"<<endl;
  //  printf("Ciao\n");
   //  }
   // catch ( ... ) {
   //  printf("Can't access expectedHitsEle\n");
   // }
   
     
     
     // Gsf Track Info
     
     
     if (iElectron->gsfTrack().isNonnull()){ 

     reco::GsfTrackRef etrack =(*iElectron).gsfTrack();
     electron.GsfTrack.Part.v.SetPxPyPzE(etrack->momentum().x(),
                                         etrack->momentum().y(),
                                         etrack->momentum().z(),
                                         sqrt(etrack->momentum().mag2()+MASS_EL*MASS_EL)); 
     electron.GsfTrack.Part.charge = etrack->charge(); 
     electron.GsfTrack.nhit  =  etrack->hitPattern().numberOfValidHits();
     electron.GsfTrack.chi2n =  etrack->normalizedChi2();
     electron.GsfTrack.dz    =  etrack->dz();
     electron.GsfTrack.d0    =  etrack->d0();
     electron.GsfTrack.edz   =  etrack->dzError();
     electron.GsfTrack.ed0   =  etrack->d0Error();
     electron.GsfTrack.ept   =  etrack->ptError();

     electron.GsfTrack.vx    =  etrack->vertex().x();
     electron.GsfTrack.vy    =  etrack->vertex().y();
     electron.GsfTrack.vz    =  etrack->vertex().z();

     electron.GsfTrack.quality[0] = etrack->quality(reco::TrackBase::qualityByName("loose"));
     electron.GsfTrack.quality[1] = etrack->quality(reco::TrackBase::qualityByName("tight"));
     electron.GsfTrack.quality[2] = etrack->quality(reco::TrackBase::qualityByName("highPurity"));
 
     electron.GsfTrack.vtxid.clear();
     electron.GsfTrack.vtxdxy.clear();
     electron.GsfTrack.vtxdz.clear();
     
     for ( int i = 0 ; i != vtxid ; i++ )
     {
        electron.GsfTrack.vtxid.push_back( i ); 
        electron.GsfTrack.vtxdxy.push_back( etrack->dxy( vtxid_xyz[i] ) );
        electron.GsfTrack.vtxdz.push_back(  etrack->dz( vtxid_xyz[i] )  );
     }

     
     }

    
     // Closest CTF Track Info
     
     
     if (iElectron->closestCtfTrackRef().isNonnull()){ 

     reco::TrackRef ctftrack =(*iElectron).closestCtfTrackRef();
     
     electron.TrackerTrack.Part.v.SetPxPyPzE(ctftrack->momentum().x(),
                                         ctftrack->momentum().y(),
                                         ctftrack->momentum().z(),
                                         sqrt(ctftrack->momentum().mag2()+MASS_EL*MASS_EL)); 
     electron.TrackerTrack.Part.charge = ctftrack->charge(); 
     electron.TrackerTrack.nhit  =  ctftrack->hitPattern().numberOfValidHits();
     electron.TrackerTrack.chi2n =  ctftrack->normalizedChi2();
     electron.TrackerTrack.dz    =  ctftrack->dz();
     electron.TrackerTrack.d0    =  ctftrack->d0();
     electron.TrackerTrack.edz   =  ctftrack->dzError();
     electron.TrackerTrack.ed0   =  ctftrack->d0Error();
     electron.TrackerTrack.ept   =  ctftrack->ptError();

     electron.TrackerTrack.vx    =  ctftrack->vertex().x();
     electron.TrackerTrack.vy    =  ctftrack->vertex().y();
     electron.TrackerTrack.vz    =  ctftrack->vertex().z();

     electron.TrackerTrack.quality[0] = ctftrack->quality(reco::TrackBase::qualityByName("loose"));
     electron.TrackerTrack.quality[1] = ctftrack->quality(reco::TrackBase::qualityByName("tight"));
     electron.TrackerTrack.quality[2] = ctftrack->quality(reco::TrackBase::qualityByName("highPurity"));
 
     electron.TrackerTrack.vtxid.clear();
     electron.TrackerTrack.vtxdxy.clear();
     electron.TrackerTrack.vtxdz.clear();
     
     for ( int i = 0 ; i != vtxid ; i++ )
     {
        electron.TrackerTrack.vtxid.push_back( i ); 
        electron.TrackerTrack.vtxdxy.push_back( ctftrack->dxy( vtxid_xyz[i] ) );
        electron.TrackerTrack.vtxdz.push_back(  ctftrack->dz( vtxid_xyz[i] )  );
     }

     
     }

    
    
    
    
    
    
     //Isolation Variables
     
    electron.EcalRecHitIsoDr04           = iElectron ->dr04EcalRecHitSumEt();
    electron.HcalDepth1TowerSumEtDr04    = iElectron ->dr04HcalDepth1TowerSumEt();
    electron.HcalDepth2TowerSumEtDr04    = iElectron ->dr04HcalDepth2TowerSumEt();
    electron.TrackIsolationDr04          = iElectron ->dr04TkSumPt();
    electron.EcalRecHitIsoDr03           = iElectron ->dr03EcalRecHitSumEt();
    electron.HcalTowerSumEtDr03          = iElectron ->dr03HcalTowerSumEt();
    electron.HcalDepth1TowerSumEtDr03    = iElectron ->dr03HcalDepth1TowerSumEt();
    electron.HcalDepth2TowerSumEtDr03    = iElectron ->dr03HcalDepth2TowerSumEt();
    electron.TrackIsolationDr03          = iElectron ->dr03TkSumPt();
         
    
     // Conversion variables
     
     
     edm::Handle<reco::TrackCollection> tracks;
     iEvent.getByLabel("generalTracks", tracks);
     ConversionFinder convFinder;
     
     ConversionInfo convInfo = convFinder.getConversionInfo(*iElectron, tracks, 3.8112);
     electron.dist_conv   = convInfo.dist();
     electron.dcot_conv   = convInfo.dcot();
     //cout<<convInfo.dist()<<"    "<<convInfo.dcot()<<endl;
     
     
     
    // Id boolean (don't use them now)

    try{
    
     //Read eID results
      std::vector<edm::Handle<edm::ValueMap<float> > > eIDValueMap(4); 
      //Robust-Loose 
      iEvent.getByLabel( "eidRobustLoose" , eIDValueMap[0] ); 
      const edm::ValueMap<float> & eIDmapRL = * eIDValueMap[0] ;
      //Robust-Tight 
      iEvent.getByLabel( "eidRobustTight" , eIDValueMap[1] ); 
      const edm::ValueMap<float> & eIDmapRT = * eIDValueMap[1] ;
      //Loose 
      iEvent.getByLabel( "eidLoose" , eIDValueMap[2] ); 
      const edm::ValueMap<float> & eIDmapL = * eIDValueMap[2] ;
     //Tight 
      iEvent.getByLabel( "eidTight" , eIDValueMap[3] ); 
      const edm::ValueMap<float> & eIDmapT = * eIDValueMap[3] ;
 
   
     
       electron.eidRobustLoose =        eIDmapRL[eRef] ;
       electron.eidRobustTight =        eIDmapRT[eRef] ;
       electron.eidLoose       =        eIDmapL[eRef]  ;
       electron.eidTight       =        eIDmapT[eRef] ;
            
     
    
    }
    catch ( cms::Exception& ex ) {
   //  printf("Can't store Tk isolation variables from Majid\n");
   }
     
     
    
 
     
     ElecVector.push_back(electron);
     ++iEl;

   } // End Loop on Gsf Electron


}

void UAHiggsTree::InitRecoElectron( vector<string> gsfelectrons, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = gsfelectrons.begin(); icoll!= gsfelectrons.end();icoll++){
      tree->Branch( icoll->c_str(), &(allElectrons[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllElectrons( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> gsfelectrons, vector<MyElectron> allElectrons[5] )
{
  for (unsigned int i=0; i!= gsfelectrons.size(); i++){
       GetRecoElectron(iEvent,iSetup,gsfelectrons.at(i),allElectrons[i]);
       }

}
