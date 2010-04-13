// -*- C++ -*-
//
// Package:    HWWAnalyzer
// Class:      HWWAnalyzer
// 
/**\class HWWAnalyzer HWWAnalyzer.cc Analysis/HWWAnalyzer/src/HWWAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Majid Hashemi
//         Created:  Sun Apr 22 07:55:14 CEST 2007
// $Id$
//
//


#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"

// ------------ method called once each job just before starting event loop  ------------
void 
HWWAnalyzer::beginJob(const edm::EventSetup&)
{
  cout<<"==============>>>>begin job start ==="<<endl;
      hOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" ) ;
      t=new TTree("t","tree");
      m=new myevent;
      t->Branch("myevent","myevent",&m,256000,1);
  cout<<"==============>>>>begin job end ==="<<endl;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HWWAnalyzer::endJob() {

       
   hOutputFile->Write() ;
   hOutputFile->Close() ;


}

HWWAnalyzer::HWWAnalyzer(const edm::ParameterSet& iConfig)
{
  cout<<"==============>>>>constructor==="<<endl;
  fOutputFileName = iConfig.getUntrackedParameter<string>("HistOutFile"); 

  TowerCollection_      = iConfig.getParameter<edm::InputTag>("towers");
  TrackCollection_      = iConfig.getParameter<edm::InputTag>("tracks");
  JetCollection_        = iConfig.getParameter<edm::InputTag>("jets");
  JetCollection2_        = iConfig.getParameter<edm::InputTag>("PFjetsIC5");
  JetCollection3_        = iConfig.getParameter<edm::InputTag>("PFjetsSC5");
  BJetCollection_        = iConfig.getParameter<edm::InputTag>("bjets");
  MetCollection_        = iConfig.getParameter<edm::InputTag>("met");
  MetCollection2_        = iConfig.getParameter<edm::InputTag>("PFmet");
  GenMetCollection_      = iConfig.getParameter<edm::InputTag>("genmet");
  GsfElectronCollection_   = iConfig.getParameter<edm::InputTag>("gsfelectrons");
  PreSelectedMuonCollection_       = iConfig.getParameter<edm::InputTag>("preselectedmuons");
  BarrelClusters_ = iConfig.getParameter<edm::InputTag>("BarrelClusters");
  EndCapClusters_ = iConfig.getParameter<edm::InputTag>("EndCapClusters");

//   EleTrackerIsolationParameters_ = iConfig.getParameter<edm::ParameterSet>("EleTkIsolationParameters");
  EleHcalIsolationParameters_ = iConfig.getParameter<edm::ParameterSet>("EleHcalIsolationParameters");
  EleEcalIsolationParameters_ = iConfig.getParameter<edm::ParameterSet>("EleEcalIsolationParameters");
  TrackIsolationLabel_ = iConfig.getParameter<string>("TrackIsolationLabel");
  EcalJurassicIsolationLabel_ = iConfig.getParameter<string>("EcalJurassicIsolationLabel");
  eid_ = iConfig.getParameter<string>("WhichElectronID");
//   barrelClusterShapeAssocProducer_ = iConfig.getParameter<string>("barrelClusterShapeAssociation");
//   endcapClusterShapeAssocProducer_ = iConfig.getParameter<string>("endcapClusterShapeAssociation");
  KFProducerLabel_ = iConfig.getParameter<string>("KFactorLabel");
  StoreTracks  = iConfig.getParameter<bool>("StoreTracks");

  //for soups
  ItIsASoup = iConfig.getParameter<bool>("ItIsASoup");
  Process_ID = iConfig.getParameter<string>("Process_ID");//AlpgenProcessID if running on Chowder

  ChannelsToAnalyze   = iConfig.getParameter<vector<string> >("channels");
  CheckMCTruth    = iConfig.getParameter<string>("CheckMCTruth");
  PrintHLTNames    = iConfig.getParameter<bool>("PrintHLTNames");
  hlt_bits   = iConfig.getParameter<vector<string> >("requested_hlt_bits");
  HepMCcollection_  = iConfig.getParameter<edm::InputTag>("hep_mc");

//for pdf analysis
  
  dopdf=iConfig.getParameter<bool>("do_pdf_analysis");
  i1=iConfig.getParameter<int>("first_incoming_particle");
  i2=iConfig.getParameter<int>("second_incoming_particle");
  i3=iConfig.getParameter<int>("first_outgoing_particle");
  i4=iConfig.getParameter<int>("second_outgoing_particle");
  ErrorNAME1=iConfig.getParameter<string>("PDFSetNameForErrors1");
  ErrorNAME2=iConfig.getParameter<string>("PDFSetNameForErrors2");
  RefNAME1=iConfig.getParameter<string>("PDFSetNameForReference1");
  RefNAME2=iConfig.getParameter<string>("PDFSetNameForReference2");
  Ref_ErrorNAME_1=iConfig.getParameter<string>("PDFSetNameForReference_and_Errors1");
  Ref_ErrorNAME_2=iConfig.getParameter<string>("PDFSetNameForReference_and_Errors2");
  Ref_ErrorNAME_3=iConfig.getParameter<string>("PDFSetNameForReference_and_Errors3");
  Ref_ErrorNAME_4=iConfig.getParameter<string>("PDFSetNameForReference_and_Errors4");
  events_to_print=iConfig.getParameter<int>("NumberOfEventsToPrint");



}


HWWAnalyzer::~HWWAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
HWWAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  ThisEvent="";

  if(CheckMCTruth=="OnReco")
    DoMCOnRecoAnalysis(iEvent);
  if(CheckMCTruth=="OnAOD")
    DoMCOnAODAnalysis(iEvent);


  AnalyzeThisEvent=false;
  for(vector<string>::iterator its=ChannelsToAnalyze.begin();its!=ChannelsToAnalyze.end();its++){
    if(*its=="all" || ThisEvent==*its)AnalyzeThisEvent=true;
  }

  if(AnalyzeThisEvent){


    DoHLTAnalysis(iEvent);

    DoVertexAnalysis(iEvent);

    if(StoreTracks)DoTrackAnalysis(iEvent);

    DoElectronAnalysis(iEvent);

    DoMuonAnalysis(iEvent);

    DoJetAnalysis(iEvent);

    DoMetAnalysis(iEvent); 
    
    // if(dopdf==true)DoPdfAnalysis(iEvent);
    
    t->Fill();
  }//if this event should be analyzed
}//analyze



//define this as a plug-in
//DEFINE_FWK_MODULE(HWWAnalyzer);


DEFINE_SEAL_MODULE();
DEFINE_FWK_MODULE (HWWAnalyzer) ;
