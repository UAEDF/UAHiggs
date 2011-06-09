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
// $Id: UAHiggsTree.C,v 1.11 2011/03/14 12:59:11 selvaggi Exp $
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

//----------------Trigger------------------------
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"


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



#include "TRandom.h"
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
   
   HcalIsolationProducer_   = iConfig.getParameter<edm::InputTag>("hcalIsolation"); 
   trckIsolationProducer_   = iConfig.getParameter<edm::InputTag>("trckIsolation");
   
   BJetCollection_          = iConfig.getParameter<edm::InputTag>("bjets");
   
   gsfelectrons             = iConfig.getParameter<vector<string> >("requested_gsfelectrons");
   muons                    = iConfig.getParameter<vector<string> >("requested_muons");
   
   genmets                   = iConfig.getParameter<vector<string> >("requested_genmets");
   calomets                  = iConfig.getParameter<vector<string> >("requested_calomets");
   pfmets                    = iConfig.getParameter<vector<string> >("requested_pfmets");
   tcmets                    = iConfig.getParameter<vector<string> >("requested_tcmets");

   genjets                   = iConfig.getParameter<vector<string> >("requested_genjets");
   calojets                  = iConfig.getParameter<vector<string> >("requested_calojets");
   pfjets                    = iConfig.getParameter<vector<string> >("requested_pfjets");
   neutrals                    = iConfig.getParameter<vector<string> >("requested_neutrals");
   trackjets                 = iConfig.getParameter<vector<string> >("requested_trackjets");

   //Trigger inputs
   hlt_bits   = iConfig.getParameter<vector<string> >("requested_hlt_bits");
   L1_bits    = iConfig.getParameter<vector<string> >("requested_L1_bits");

   //Vertex, Tracks
   
   vertexs                 = iConfig.getParameter<vector<string> >("requested_vertexs");
   tracks                  = iConfig.getParameter<vector<string> >("requested_tracks");


   // --- Lepton Preselection ------------
 
   DoSingleLeptonPreselection = iConfig.getParameter<bool>("doSingleLeptonPreselection");
   DoLeptonPairPreselection   = iConfig.getParameter<bool>("doLeptonPairPreselection");
   DoRandomPreskim            = iConfig.getParameter<bool>("doRandomPreskim");
   
   
   SingleLeptonPtCut          = iConfig.getParameter<double>("singleLeptonPtCut");
   LeptonPairPtCut            = iConfig.getParameter<double>("leptonPairPtCut");
   preskimFraction            = iConfig.getParameter<double>("fractionOfEvents");  



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
   bool keepEvent = true;
   
   //cout <<" EvtId and L1,HLT trig "<<endl;
   GetEvtId(iEvent); 
   GetL1Trig(iEvent,iSetup);
   GetHLTrig(iEvent,iSetup);
   
   //cout <<" Generator level"<<endl;
   if (StoreGenPart) GetGenPart(iEvent,iSetup);
   if (StoreGenKine) { GetGenKin (iEvent) ; ntot_kfac+=GenKin.kfactor ; }
   if (StoreGenPart) GetAllGenJets(iEvent,iSetup,genjets,allGenJets); 
  // if (StoreGenPart) GetAllGenMETs(iEvent,iSetup,genmets,allGenMETs);
   
   ntot++;
   
   // ---- only do for WW bck in VVto4L ------
  /* int nWmin  =0;
   int nWplus =0;
   for(vector<MyGenPart>::iterator itgen=GenPart.begin();itgen!=GenPart.end();itgen++){
      if(itgen->name=="W+")++nWplus;
      if(itgen->name=="W-")++nWmin ;
      }
   if( (nWmin ==1 && nWplus ==1) ) ++ntot;
   // cout<<nWplus<<","<<nWmin<<endl;   */
   //-------------------------------------------
   
   
   GetPUSumInfo(iEvent);  
 
   //cout <<" Reset vtx id and vector"<<endl;
   vtxid = 0;
   vtxid_xyz.clear();
   
   //cout <<" ... BeamSpot"<<endl;

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

   //cout <<" BeamSpot is vtx with id=0 "<<endl;
   vtxid++;
   vtxid_xyz.push_back(theBeamSpot->position());

   //cout <<" ... Vertex"<<endl;
   GetAllVertexs(iEvent,iSetup,vertexs,allVertexs);
   //cout <<" ... Tracks"<<endl;
   //GetAllTracks(iEvent,iSetup,tracks,allTracks);
   //GetAllNeutralParts(iEvent,iSetup,neutrals,allNeutrals);

   //cout <<" ... Electron"<<endl;
   GetAllElectrons(iEvent,iSetup,gsfelectrons,allElectrons);
   
   //cout <<" ... Muon"<<endl;
   GetAllMuons(iEvent,iSetup,muons,allMuons);
   
   //cout <<" ... Jet"<<endl;
   GetAllCaloJets  (iEvent,iSetup,calojets,allCaloJets);
   GetAllPFJets    (iEvent,iSetup,pfjets,  allPFJets);
   GetAllTrackJets (iEvent,iSetup,trackjets,allTrackJets);
   //cout <<"    MET"<<endl;
   
   GetAllCaloMETs(iEvent,iSetup,calomets,allCaloMETs);
   GetAllPFMETs(iEvent,iSetup,pfmets,allPFMETs);
   GetAllTcMETs(iEvent,iSetup,tcmets,allTcMETs);
   GetChargedMET(iEvent,iSetup);


   
   if(DoSingleLeptonPreselection) {
      keepEvent = PassLeptonFilter(allElectrons,allMuons,SingleLeptonPtCut);      
    //  cout<<keepEvent<<endl;
      if (keepEvent) { 
        n_single_presel++;
        if (StoreGenKine) n_single_presel_kfac+=GenKin.kfactor ; 
      }
   }
   //--------------- WARNING!!! CHECK IF NOT VVTo4L -----------------------------------------
   if(DoLeptonPairPreselection)   {
     // cout<<keepEvent<<endl;
      keepEvent = keepEvent && PassLeptonPairFilter(allElectrons,allMuons,LeptonPairPtCut);// && (nWmin ==1 && nWplus ==1); 
     // cout<<keepEvent<<endl;
      if(keepEvent) {
        n_pair_presel++;
        if (StoreGenKine) n_pair_presel_kfac+=GenKin.kfactor ;
      }
    /*  else {
      cout<<"----- ele -----"<<endl;
      for(vector<MyElectron>::iterator itele = allElectrons[0].begin() ; itele != allElectrons[0].end() ; ++itele){
        cout<<"pt,eta,charge: " <<itele->pt<<","<<itele->eta<<","<<itele->Part.charge<<endl;
       }
      cout<<"----- mu -----"<<endl;
      for(vector<MyMuon>::iterator itele = allMuons[0].begin() ; itele != allMuons[0].end() ; ++itele){
        cout<<"pt,eta,charge: " <<itele->pt<<","<<itele->eta<<","<<itele->Part.charge<<endl;
       }
      
      }*/
      
      
   
   
   }   
      
   
  
   // if( (gRandom->Rndm() > preskimFraction) && (DoRandomPreskim) ) {keepEvent = false; n_random_rej++;}
   
   
   if(keepEvent)tree->Fill();
   //cout<<"ntot = "<<ntot<<endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
UAHiggsTree::beginJob()
{
   fout       = new TFile(fOutputFileName.c_str(), "RECREATE" ) ;
   tree       = new TTree("tree","tree");
   tree_extra = new TTree("tree_extra","tree_extra");
   
   tree_extra ->Branch("ntot",&ntot); 
   tree_extra ->Branch("ntot_kfac",&ntot_kfac); 
   tree_extra ->Branch("n_single_presel",&n_single_presel);
   tree_extra ->Branch("n_single_presel_kfac",&n_single_presel_kfac);
   tree_extra ->Branch("n_pair_presel",&n_pair_presel); 
   tree_extra ->Branch("n_pair_presel_kfac",&n_pair_presel_kfac); 
   tree_extra ->Branch("n_random_rej",&n_random_rej); 
   tree_extra ->Branch("preskimFraction",&preskimFraction); 
   tree_extra ->Branch("DoSingleLeptonPreselection",&DoSingleLeptonPreselection );
   tree_extra ->Branch("DoLeptonPairPreselection",&DoLeptonPairPreselection   );
   tree_extra ->Branch("DoRandomPreskim",&DoRandomPreskim  );
   tree_extra ->Branch("SingleLeptonPtCut",&SingleLeptonPtCut  );
   tree_extra ->Branch("LeptonPairPtCut",&LeptonPairPtCut  );
  
   
   //evt  = new MyEvent;
   // tree->Branch("MyEvent","MyEvent",&evt);

   // General Event Info 
   tree->Branch("EvtId",&EvtId);   
   tree->Branch("L1Trig",&L1Trig);
   tree->Branch("HLTrig",&HLTrig);
   
   // MC Informations
   if (StoreGenPart) tree->Branch("GenPart",&GenPart);
   if (StoreGenKine) tree->Branch("GenKin",&GenKin);
   if (StoreGenPart) tree->Branch("GenElec",&GenElec);
   if (StoreGenPart) tree->Branch("GenMu",&GenMu);
   if (StoreGenPart) tree->Branch("GenNu",&GenNu);
   //if (StoreGenPart) tree->Branch("GenJet",&GenJet);
   tree->Branch("puinfo",&pusuminfo);  
 
   if (StoreGenPart) InitGenMET(genmets,tree);
   if (StoreGenPart) InitGenJet(genjets,tree);

   // MC Vertex (Sim and Gen) ??? 

   // RECO Information

   InitRecoElectron(gsfelectrons,tree);
   InitRecoMuon(muons,tree);
   
   InitRecoCaloMET(calomets,tree);
   InitRecoTcMET  (tcmets,tree);
   InitRecoPFMET  (pfmets,tree);
   tree->Branch("iVtxChargedMet",&iVtxChargedMET);
   tree->Branch("ChargedMet",&ChargedMET);
   tree->Branch("ChargedPlusNeutralMet",&ChargedPlusNeutralMET);
   
   InitRecoCaloJet (calojets,tree);
   InitRecoPFJet   (pfjets,tree);
   InitNeutralPart (neutrals,tree);
   InitRecoTrackJet(trackjets,tree);
   
   tree->Branch("beamSpot",&beamSpot);
   InitRecoVertex  (vertexs,tree);
   InitRecoTrack (tracks,tree);
   
   // fill L1 map only once
   fill_L1_map = true;
   
   ntot=0;
   ntot_kfac=0;
   n_single_presel=0;
   n_single_presel_kfac=0;
   n_pair_presel=0;
   n_pair_presel_kfac=0;
   n_random_rej=0;
   run=0;
}


//-- method called to for each run
void UAHiggsTree::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
  using namespace std;
  using namespace edm;

  bool changed = true;
  isValidHltConfig_ = hltConfig.init(iRun,iSetup,"HLT",changed);
 // cout<<isValidHltConfig_<<endl;
 }
   

// ------------ method called once each job just after ending the event loop  ------------
void 
UAHiggsTree::endJob() 
{
   tree_extra -> Fill();
  
   fout->Write() ;
   fout->Close() ; 

    




//   delete evt;
//   delete tree;
//   delete fout;
}

//define this as a plug-in
DEFINE_FWK_MODULE(UAHiggsTree);
