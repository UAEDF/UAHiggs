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

/*
   // get the association of the clusters to their shapes for EE
   edm::Handle<reco::BasicClusterShapeAssociationCollection> endcapClShpHandle ;
   try {
     iEvent.getByLabel ("islandBasicClusters","islandEndcapShapeAssoc", endcapClShpHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get ECAL endcap Cluster Shape Collection\n");
   }
   const reco::BasicClusterShapeAssociationCollection& endcapClShpMap = *endcapClShpHandle ;
*/

   // Tracker Isolation handle (Guillelmo)
   edm::Handle< reco::GsfElectronIsoCollection > tkIsolationHandle;
   try {
     iEvent.getByLabel(trckIsolationProducer_, tkIsolationHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get tracker isolation product\n");
   }

 /*  // Tracker Isolation handle (Majid)
   edm::Handle< edm::ValueMap<reco::IsoDeposit> > tkIsolationHandleMajid;
   try { iEvent.getByLabel("eleIsoDepositTk", tkIsolationHandleMajid); }
   catch ( cms::Exception& ex ) { printf("Can't get tracker isolation product\n"); }
   const edm::ValueMap<reco::IsoDeposit>& tkIsolationVal = *tkIsolationHandleMajid;

   // eidHandle (Majid) 
   edm::Handle< edm::ValueMap<float> > eidHandle;
   try {iEvent.getByLabel("eidTight",eidHandle);}
   catch ( cms::Exception& ex ) { printf("Can't get electron identification product\n"); }
   const edm::ValueMap<float>& eidVal = *eidHandle;

   // EcalIsolationHandle (Majid)
   edm::Handle< edm::ValueMap<double> > EcalIsolationHandle;
   try { iEvent.getByLabel("eleIsoFromDepsEcalFromHits", EcalIsolationHandle); }
   catch ( cms::Exception& ex ) { printf("Can't get ecal Jurassic isolation product\n"); }
   const edm::ValueMap<double>& EcalIsolationVal = *EcalIsolationHandle;

*/





/* 
   // Get the association vector
   edm::Handle< reco::CandViewDoubleAssociations > hcalIsolationHandle;
   try {
     iEvent.getByLabel(HcalIsolationProducer_,hcalIsolationHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get hcalIsolationHandle Collection\n");
   }

 
   if(hcalIsolationHandle->size() != tkIsolationHandle->size()){
     printf("hcalIsolationHandle and tkIsolationHandle have different sizes");
     printf("(%d vs. %d)\n",hcalIsolationHandle->size(),tkIsolationHandle->size());
     assert(0);
   }
*/

   // Another way of getting electron info
   edm::Handle< edm::View<reco::Candidate> > emObjectHandle;
   try {
     iEvent.getByLabel("pixelMatchGsfElectrons",emObjectHandle);
   }
   catch ( cms::Exception& ex ) {
     printf("Can't get emObjectHandle Collection\n");
   }
 


   int iEl = 0;

   // Loop on Gsf Electron
   for (reco::GsfElectronCollection::const_iterator iElectron = gsfElectrons.begin();
        iElectron!= gsfElectrons.end();iElectron++) {
 
     MyElectron electron;

     // Majid:
     Ref<reco::GsfElectronCollection> electronRAWRef(gsfElectronsHandle,iEl);

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
     electron.dEtaSupClusTrVtx   = iElectron->deltaEtaSuperClusterTrackAtVtx()  ;
     electron.dEtaSeedClusTrCalo = iElectron->deltaEtaSeedClusterTrackAtCalo()  ; 
     electron.dPhiSupClusTrVtx   = iElectron->deltaPhiSuperClusterTrackAtVtx()  ; 
     electron.dPhiSeedClusTrCalo = iElectron->deltaPhiSeedClusterTrackAtCalo()  ; 
     electron.hadronicOverEm     = iElectron->hadronicOverEm()                  ; 
     electron.isEScaleCorr       = iElectron->isEnergyScaleCorrected()          ; 
     electron.isMomentumCorr     = iElectron->isMomentumCorrected()             ; 
     //electron.nClus              = iElectron->numberOfClusters()                ; 
     electron.classification     = iElectron->classification()                  ; 

     // Gsf Track Info
     reco::GsfTrackRef etrack =(*iElectron).gsfTrack();
     electron.GsfTrack.Part.v.SetPxPyPzE(etrack->momentum().x(),
                                         etrack->momentum().y(),
                                         etrack->momentum().z(),
                                         sqrt(etrack->momentum().mag2()+MASS_EL*MASS_EL)); 
     electron.GsfTrack.Part.charge = etrack->charge(); 
     electron.GsfTrack.nhit  =  etrack->recHitsSize();
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

    // Extra Idolation Majid:

    try{
    
    edm::Handle< edm::ValueMap<reco::IsoDeposit> > tkIsolationHandleMajid;
    iEvent.getByLabel("eleIsoDepositTk", tkIsolationHandleMajid); 
   const edm::ValueMap<reco::IsoDeposit>& tkIsolationVal = *tkIsolationHandleMajid;

   // eidHandle (Majid) 
   edm::Handle< edm::ValueMap<float> > eidHandle;
   iEvent.getByLabel("eidTight",eidHandle);
   const edm::ValueMap<float>& eidVal = *eidHandle;

   // EcalIsolationHandle (Majid)
   edm::Handle< edm::ValueMap<double> > EcalIsolationHandle;
   iEvent.getByLabel("eleIsoFromDepsEcalFromHits", EcalIsolationHandle); 
   const edm::ValueMap<double>& EcalIsolationVal = *EcalIsolationHandle;
    
    
  //  cout << "itr: " << iElectron->eta() << " " <<  iElectron->phi() << endl; 
  //  cout << "RAW: " << electronRAWRef->eta() << " " << electronRAWRef->phi() <<endl ;

    // ... TrackerIsolation (Majid)
    reco::SuperClusterRef sc = iElectron->get<reco::SuperClusterRef> () ;
    reco::isodeposit::Direction electronDir(iElectron->eta(), iElectron->phi());
    reco::IsoDeposit::Veto EleVeto;
    EleVeto.vetoDir = electronDir;
    EleVeto.dR = 0.015;
    reco::IsoDeposit::Vetos AllVetos;
    AllVetos.push_back(EleVeto);
    electron.TrackerIsolationMajid = tkIsolationVal[electronRAWRef].depositAndCountWithin(0.4,AllVetos,0.).first;

    // ... eidTight (Majid)
    electron.eidTight = eidVal[electronRAWRef];

    // ... ecal jurassic isolation (Majid)
    electron.EcalJurassicIsolation= EcalIsolationVal[electronRAWRef];
    }
    catch ( cms::Exception& ex ) {
     printf("Can't store Tk isolation variables from Majid\n");
   }
     // Extra Isolation variables


     // Extra shape variables
/*
     bool hasBarrel=true ;
     bool hasEndcap=true ;
     reco::SuperClusterRef sclusRef = iElectron->get<reco::SuperClusterRef> () ;
     reco::BasicClusterShapeAssociationCollection::const_iterator seedShpItr ;
     seedShpItr = barrelClShpMap.find (sclusRef->seed ()) ;
     if ( seedShpItr==barrelClShpMap.end ())  {
	hasBarrel=false ;
	seedShpItr=endcapClShpMap.find (sclusRef->seed ()) ;
	if ( seedShpItr==endcapClShpMap.end () ) hasEndcap=false;
     }
     if (hasBarrel || hasEndcap) {
	const reco::ClusterShapeRef& sClShape = seedShpItr->val;
        electron.e3x3  = sClShape->e3x3()   ;
        electron.e5x5  = sClShape->e5x5()   ;
     } else {
        electron.e3x3  = -999.0 ;
        electron.e5x5  = -999.0 ;
     }
*/

     // Store electron
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

