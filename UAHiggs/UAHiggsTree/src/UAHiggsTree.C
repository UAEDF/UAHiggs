// -*- C++ -*-
//
// Package:    UAHiggsTree
// Class:      UAHiggsTree
// 
/**\class UAHiggsTree UAHiggsTree.cc UAHiggs/UAHiggsTree/src/UAHiggsTree.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  "local user"
//         Created:  Wed Nov 18 10:39:03 CET 2009
// $Id$
//
//


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

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

/*
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
*/



// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
UAHiggsTree::UAHiggsTree(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

   // Get output filename
   fOutputFileName = iConfig.getUntrackedParameter<string>("fileName");

   // Modules to execute 

   StoreGenPart = iConfig.getParameter<bool>("StoreGenPart");
   StoreGenKine = iConfig.getParameter<bool>("StoreGenKine");

   // Define DATA Collection
   genPartColl_             = iConfig.getParameter<edm::InputTag>("genPartColl") ; 
   hepMCColl_               = iConfig.getParameter<edm::InputTag>("hepMCColl") ;
   GsfElectronCollection_   = iConfig.getParameter<edm::InputTag>("gsfelectrons");
   HcalIsolationProducer_   = iConfig.getParameter<edm::InputTag>("hcalIsolation"); 
   trckIsolationProducer_   = iConfig.getParameter<edm::InputTag>("trckIsolation");
   globalMuonCollection_    = iConfig.getParameter<edm::InputTag>("muons");

}


UAHiggsTree::~UAHiggsTree()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
UAHiggsTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // EvtId and L1 trig
   GetEvtId(iEvent); 
   GetL1Trig(iEvent,iSetup);

   // Generator level
   if (StoreGenPart) GetGenPart(iEvent,iSetup);
   if (StoreGenKine) GetGenKin (iEvent);
   if (StoreGenPart) GetGenJet (iEvent,iSetup,"antikt5GenJets",GenJet); 

   // Reset vtx id and vector
   vtxid = 0;
   vtxid_xyz.clear();
   
   // ... BeamSpot

   edm::Handle<reco::BeamSpot>      beamSpotHandle;
   iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
   const reco::BeamSpot* theBeamSpot = beamSpotHandle.product();
   beamSpot.x           = theBeamSpot->position().x();
   beamSpot.y           = theBeamSpot->position().y();
   beamSpot.z           = theBeamSpot->position().z();
   beamSpot.sigmaZ      = theBeamSpot->sigmaZ();
   beamSpot.dxdz        = theBeamSpot->dxdz();
   beamSpot.dydz        = theBeamSpot->dydz();
   beamSpot.BeamWidthX  = theBeamSpot->BeamWidthX() ;
   beamSpot.BeamWidthY  = theBeamSpot->BeamWidthY() ;
   beamSpot.ex          = theBeamSpot->x0Error();
   beamSpot.ey          = theBeamSpot->y0Error();
   beamSpot.ez          = theBeamSpot->z0Error();
   beamSpot.esigmaZ     = theBeamSpot->sigmaZ0Error();
   beamSpot.edxdz       = theBeamSpot->dxdzError();
   beamSpot.edydz       = theBeamSpot->dydzError();
   beamSpot.eBeamWidthX = theBeamSpot->BeamWidthXError();
   beamSpot.eBeamWidthY = theBeamSpot->BeamWidthYError();

   // BeamSpot is vtx with id=0 
   vtxid++;
   vtxid_xyz.push_back(theBeamSpot->position());

   // ... Vertex
   GetRecoVertex(iEvent,iSetup,"offlinePrimaryVertices",primaryVertex);
   // ... Tracks
   GetRecoTracks(iEvent,iSetup,"generalTracks",generalTracks);

   // ... Electron
   GetRecoElectron(iEvent,iSetup,gsfElec);

   // ... Muon
   GetRecoMuon(iEvent,iSetup,globalMuon);

/*
   // Tests
  
   edm::ESHandle<L1GtTriggerMenu> menuRcd;
   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
   const L1GtTriggerMenu* menu = menuRcd.product();

   for (CItAlgo algo = menu->gtAlgorithmMap().begin(); 
                algo!=menu->gtAlgorithmMap().end(); 
                ++algo) 
   {
     cout << "Name: " << (algo->second).algoName() 
          << " Alias: " << (algo->second).algoAlias() 
          << " Bit: " << (algo->second).algoBitNumber()
           << " Result: " << l1AlgorithmResult(iEvent, iSetup, (algo->second).algoName() )
          << std::endl;
   }
  
   // cout << l1AlgorithmResult(iEvent, iSetup,"L1_SingleEG15") << endl;

   edm::Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
   iEvent.getByLabel("gtDigis",L1GTRR);
   for (int i=0 ; i <128 ; i++) 
     cout << "PhysicsTriggerWord :" << i << " " << L1GTRR->decisionWord()[i] << endl;
   for (int i=0 ; i <64  ; i++)
     cout << "technicalTriggerWord :" << i << " " << L1GTRR->technicalTriggerWord()[i] << endl;

*/

   tree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
UAHiggsTree::beginJob()
{
   fout = new TFile(fOutputFileName.c_str(), "RECREATE" ) ;
   tree = new TTree("tree","tree");
   //evt  = new MyEvent;
   // tree->Branch("MyEvent","MyEvent",&evt);

   // General Event Info 
   tree->Branch("EvtId",&EvtId);   
   tree->Branch("L1Trig",&L1Trig);

   // MC Informations
   if (StoreGenPart) tree->Branch("GenPart",&GenPart);
   if (StoreGenKine) tree->Branch("GenKin",&GenKin);
   if (StoreGenPart) tree->Branch("GenElec",&GenElec);
   if (StoreGenPart) tree->Branch("GenMu",&GenMu);
   if (StoreGenPart) tree->Branch("GenNu",&GenNu);
   
   if (StoreGenPart) tree->Branch("GenJet",&GenJet);
   


   // MC Vertex (Sim and Gen) ??? 

   // RECO Information

   tree->Branch("beamSpot",&beamSpot);
   tree->Branch("primaryVertex",&primaryVertex);
   tree->Branch("generalTracks",&generalTracks);
   tree->Branch("gsfElec",&gsfElec);
   tree->Branch("globalMuon",&globalMuon);
   

}

// ------------ method called once each job just after ending the event loop  ------------
void 
UAHiggsTree::endJob() 
{
   fout->Write() ;
   fout->Close() ; 
//   delete evt;
//   delete tree;
//   delete fout;
}

//define this as a plug-in
DEFINE_FWK_MODULE(UAHiggsTree);
