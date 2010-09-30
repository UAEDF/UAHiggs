#ifndef __UAHiggsTree_H__
#define __UAHiggsTree_H__
/* 
 class          : UAHiggsTree 
 Description    : Test HWW UAHiggs Class
 Original Author: Xavier Janssen <xjanssen@cern.ch> 
 Created        : Wed Nov 18 10:39:03 CET 2009
 */


// system include files
#include <string>
#include <vector>
using namespace std;


// ROOT
#include "TFile.h"
#include "TTree.h"

// CMSSW Include files (Minimal)
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Point 3D
#include "DataFormats/Math/interface/Point3D.h"


// UAHiggsTree UAHiggs class decleration

// Particle Masses
#include "UAHiggs/UAHiggsTree/interface/MassParticles.h"


// Particle Definition
#include "UAHiggs/UAHiggsTree/interface/MyPart.h"

// ... EvtId and trigger
#include "UAHiggs/UAHiggsTree/interface/MyEvtId.h"
#include "UAHiggs/UAHiggsTree/interface/MyL1Trig.h"
#include "UAHiggs/UAHiggsTree/interface/MyHLTrig.h"

// ... Gen Objects
#include "UAHiggs/UAHiggsTree/interface/MyGenPart.h"
#include "UAHiggs/UAHiggsTree/interface/MyGenJet.h"
#include "UAHiggs/UAHiggsTree/interface/MyGenKin.h"
#include "UAHiggs/UAHiggsTree/interface/MyGenMET.h"

// Reco Tracks and vertex
#include "UAHiggs/UAHiggsTree/interface/MyBeamSpot.h"
#include "UAHiggs/UAHiggsTree/interface/MyVertex.h" 
#include "UAHiggs/UAHiggsTree/interface/MyTracks.h" 
#include "UAHiggs/UAHiggsTree/interface/MyElectron.h" 
#include "UAHiggs/UAHiggsTree/interface/MyMuon.h" 
#include "UAHiggs/UAHiggsTree/interface/MyMET.h" 
// Reco Electron


// Reco Muon


// Reco Jets

#include "UAHiggs/UAHiggsTree/interface/MyJet.h" 

// Reco Electron


// Reco Muon


// Reco Jets




class UAHiggsTree : public edm::EDAnalyzer {
   public:
      explicit UAHiggsTree(const edm::ParameterSet&);
      ~UAHiggsTree();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

     
      // ----------Initializing functions------------------------------

      virtual void InitRecoElectron( vector<string>, TTree*); 
      virtual void InitRecoMuon( vector<string>, TTree*); 
      
      virtual void InitRecoCaloMET( vector<string>, TTree*); 
      virtual void InitRecoPFMET( vector<string>, TTree*); 
      virtual void InitRecoTcMET( vector<string>, TTree*); 
      virtual void InitGenMET( vector<string>, TTree*); 
     
      virtual void InitRecoCaloJet( vector<string>, TTree*); 
      virtual void InitRecoPFJet( vector<string>, TTree*); 
      virtual void InitRecoTrackJet( vector<string>, TTree*); 
      virtual void InitGenJet( vector<string>, TTree*); 
     
      virtual void InitRecoVertex( vector<string>, TTree*); 
      virtual void InitRecoTrack ( vector<string>, TTree*); 
      
      
      // ----------Functions------------------------------

          
      virtual void GetGenPart(const edm::Event&, const edm::EventSetup&);  
      
      virtual void GetGenKin (const edm::Event&);  
      virtual void GetGenJet(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyGenJet>&);
      
      virtual void GetGenMET(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyGenMET>&);

     
      virtual void GetEvtId(const edm::Event&);
      virtual void GetL1Trig(const edm::Event&, const edm::EventSetup& );
      virtual void GetHLTrig(const edm::Event&, const edm::EventSetup& );
      bool hasFired(const std::string& triggerName,
   		const edm::TriggerNames& triggerNames,
  		const edm::TriggerResults& triggerResults) const;
      
      virtual void GetRecoVertex(const edm::Event& , const edm::EventSetup& ,
                                 const string    , vector<MyVertex>& );

      virtual void GetRecoTrack(const edm::Event& , const edm::EventSetup& ,
                                 const string    , vector<MyTracks>& );

      virtual void GetRecoElectron(const edm::Event& , const edm::EventSetup& ,
                                                     const string , vector<MyElectron>&); 

      virtual void GetRecoMuon(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyMuon>&);

      
      virtual void GetRecoCaloMET(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyMET>&);

      
      virtual void GetRecoPFMET(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyMET>&);

     
      virtual void GetRecoTcMET(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyMET>&);

      virtual void GetRecoCaloJet(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyJet>&);

      
      virtual void GetRecoPFJet(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyJet>&);

     
      virtual void GetRecoTrackJet(const edm::Event& , const edm::EventSetup& ,
                                                 const string ,  vector<MyJet>&);

     
       
 
      //  -------Get all collections ----------------------------------------
      
      virtual void GetAllElectrons(const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyElectron> allElectrons[5]);
      virtual void GetAllMuons    (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyMuon> allMuons[5]);
      
      virtual void GetAllCaloMETs  (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyMET> allCaloMETs[5]);
      virtual void GetAllPFMETs    (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyMET> allPFMETs[5]);
      virtual void GetAllTcMETs    (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyMET> allTcMETs[5]);
      virtual void GetAllGenMETs   (const edm::Event&, const edm::EventSetup& ,const vector<string>, vector<MyGenMET> allGenMETs[5]);
      
      virtual void GetAllCaloJets  (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyJet>   allCaloJets[5]);
      virtual void GetAllPFJets    (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyJet>   allPFJets[5]);
      virtual void GetAllTrackJets (const edm::Event&, const edm::EventSetup& , const vector<string>, vector<MyJet>   allTrackJets[5]);
      virtual void GetAllGenJets   (const edm::Event&, const edm::EventSetup& ,const vector<string>, vector<MyGenJet> allGenJets[5]);
      
      virtual void GetAllVertexs (const edm::Event&, const edm::EventSetup& ,const vector<string>, vector<MyVertex> allVertexs[5]);
      virtual void GetAllTracks  (const edm::Event&, const edm::EventSetup& ,const vector<string>, vector<MyTracks> allTracks[5]);
     
     
      // ----------member data ---------------------------

      // ----------Config data --------------------------- 

      // Modules to execute

      bool StoreGenPart;
      bool StoreGenKine;
      bool doJetVertexAlpha;

      vector<string> gsfelectrons;
      vector<string> muons;
      
      vector<string> genmets;
      vector<string> calomets;
      vector<string> pfmets;
      vector<string> tcmets;
      
      vector<string> genjets;
      vector<string> calojets;
      vector<string> pfjets;
      vector<string> trackjets;
       
      vector<string> hlt_bits;
      vector<string> L1_bits;
      
      vector<string> vertexs;
      vector<string> tracks;
      
      // Data Collection
      edm::InputTag genPartColl_ ;
      edm::InputTag hepMCColl_ ;      

      // Gfs electron Collections
      
      edm::InputTag  HcalIsolationProducer_;
      edm::InputTag  trckIsolationProducer_;
     
      // Muon Collections 
      
      // Jet Collections
      
      edm::InputTag  CaloJetAK5Collection_;
      
      // bJet Collection
      
      edm::InputTag  BJetCollection_;
      
      // ----------Tree & File ---------------------------

      string fOutputFileName ;
      TFile*   fout;
      TTree*   tree; 

 //   MyEvent* evt;

      // --------- Tree Content -------------------------- 

 //  public:   

      MyEvtId           EvtId;
      MyL1Trig          L1Trig;
      MyHLTrig          HLTrig;
      MyGenKin          GenKin;

      vector<MyGenPart> GenPart;
      vector<MyGenPart> GenElec;
      vector<MyGenPart> GenMu;
      vector<MyGenPart> GenNu;

      vector<MyGenJet>  GenJet;

      MyBeamSpot        beamSpot;
      vector<MyVertex>  primaryVertex;
      vector<MyTracks>  generalTracks;  

      vector<MyElectron> gsfElec;
      
      vector<MyElectron> allElectrons[5];
      vector<MyMuon>     allMuons[5];
      
      vector<MyMET>      allCaloMETs[5];
      vector<MyMET>      allPFMETs[5];
      vector<MyMET>      allTcMETs[5];
      vector<MyGenMET>   allGenMETs[5];
      
      vector<MyJet>      allCaloJets[5];
      vector<MyJet>      allPFJets[5];
      vector<MyJet>      allTrackJets[5];
      vector<MyGenJet>   allGenJets[5];
    
      vector<MyVertex>   allVertexs[5];
      vector<MyTracks>   allTracks[5];
      
      vector<MyMuon>     globalMuon;

      vector<MyJet>      caloJetAK5;
      
      // --------- Vtx ID --------------------------


      Int_t vtxid;
      vector<math::XYZPoint> vtxid_xyz;
      bool fill_L1_map;
      
      map<int,string> L1_map;
      map<int,string> HLT_map;
};


#endif
