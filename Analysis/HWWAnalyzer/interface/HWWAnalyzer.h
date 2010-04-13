// system include files
#include <memory>
#include <string>
#include <iostream>

//module definition
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESProducer.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/Framework/interface/eventsetupdata_registration_macro.h"

// user include files
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
//for geometry essource load
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Ref.h"


#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/JetTracksAssociation.h"
#include "DataFormats/BTauReco/interface/IsolatedTauTagInfo.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/ClusterShapeFwd.h"
#include "DataFormats/EgammaReco/interface/ClusterShape.h"
#include "RecoJets/JetAlgorithms/interface/ProtoJet.h"
#include "DataFormats/BTauReco/interface/TrackCountingTagInfo.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaReco/interface/BasicClusterShapeAssociation.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronIsoCollection.h"
#include "DataFormats/Candidate/interface/CandAssociation.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "RecoEgamma/EgammaIsolationAlgos/interface/ElectronTkIsolation.h"
#include "RecoEgamma/EgammaIsolationAlgos/interface/EgammaEcalIsolation.h"
#include "RecoEgamma/EgammaIsolationAlgos/interface/EgammaTowerIsolation.h"
#include "RecoEcal/EgammaClusterProducers/interface/Multi5x5ClusterProducer.h"


//for ecal isolation
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h" 
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"



#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

//for trigger results
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"
//#include "JetMETCorrections/Type1MET/interface/Type1METAlgo.h"

//for muon isolation
//===> this is old 169 #include "DataFormats/MuonReco/interface/MuIsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
//For Hep3Vector
#include <CLHEP/Vector/LorentzVector.h>
//for genparticles in AOD
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "Analysis/HWWAnalyzer/interface/myevent.h"


#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
//to understand string
using namespace std;

//to understand calojetcollection, calotowercollection, ...
using namespace reco;
using namespace muon;
using namespace edm;



//
// class decleration
//

class HWWAnalyzer : public edm::EDAnalyzer {

   public:
      explicit HWWAnalyzer(const edm::ParameterSet&);
      ~HWWAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      void DoMCOnRecoAnalysis(const edm::Event&);  
      void DoMCOnAODAnalysis(const edm::Event&);  
      void DoHLTAnalysis(const edm::Event&);
      void DoElectronAnalysis(const edm::Event&);
      void DoMuonAnalysis(const edm::Event&);
      void DoJetAnalysis(const edm::Event&); 
      void DoMetAnalysis(const edm::Event&);
      void DoTrackAnalysis(const edm::Event&);
      void DoVertexAnalysis(const edm::Event&);
      void DoPdfAnalysis(const edm::Event&);
      void PrintParticleInfo(const reco::Candidate*);
      double deltaR(double,double,double,double);
      double deltaphi(double,double);
      double CorrectPhi(double,double,double); 
      
      // ----------member data ---------------------------
  //=========== config parameters ==================
  string fOutputFileName ;

  edm::InputTag  TrackCollection_;
  edm::InputTag  TowerCollection_;
  edm::InputTag  JetCollection_;
  edm::InputTag  JetCollection2_;
  edm::InputTag  JetCollection3_;
  edm::InputTag  BJetCollection_;
  edm::InputTag  MetCollection_;
  edm::InputTag  GenMetCollection_;
  edm::InputTag  MetCollection2_;
  edm::InputTag  GsfElectronCollection_;
  edm::InputTag  PreSelectedMuonCollection_;
  edm::InputTag  BarrelClusters_;
  edm::InputTag  EndCapClusters_;
  edm::ParameterSet EleEcalIsolationParameters_;
  edm::ParameterSet EleHcalIsolationParameters_;
  edm::InputTag  HepMCcollection_;
  string TrackIsolationLabel_;
  string EcalJurassicIsolationLabel_;
  string eid_;
  string KFProducerLabel_;
  bool StoreTracks;  

  bool ItIsASoup;
  string Process_ID;
  string CheckMCTruth;
  bool PrintHLTNames;
  vector<string> ChannelsToAnalyze;
  vector<string> hlt_bits;

  bool AnalyzeThisEvent;
  string  ThisEvent;

  //for tracks
  const TrackCollection *tracks;
  
  //for pdf analysis
  
  string RefNAME1;
  string RefNAME2;
  int i1,i2,i3,i4;
  string ErrorNAME2;
  string ErrorNAME1;
  string Ref_ErrorNAME_1;
  string Ref_ErrorNAME_2;
  string Ref_ErrorNAME_3;
  string Ref_ErrorNAME_4;
  int events_to_print;
  bool dopdf;
  
  myevent *m; // for root tree definition
  TTree *t;


  TFile* hOutputFile ;

};
