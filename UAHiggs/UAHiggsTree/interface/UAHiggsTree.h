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

// ... Gen Objects
#include "UAHiggs/UAHiggsTree/interface/MyGenPart.h"
#include "UAHiggs/UAHiggsTree/interface/MyGenJet.h"
#include "UAHiggs/UAHiggsTree/interface/MyGenKin.h"

// Reco Tracks and vertex
#include "UAHiggs/UAHiggsTree/interface/MyBeamSpot.h"
#include "UAHiggs/UAHiggsTree/interface/MyVertex.h" 
#include "UAHiggs/UAHiggsTree/interface/MyTracks.h" 
#include "UAHiggs/UAHiggsTree/interface/MyElectron.h" 
#include "UAHiggs/UAHiggsTree/interface/MyMuon.h" 

// Reco Electron


// Reco Muon


// Reco Jets

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

      // ----------Functions------------------------------

      virtual void GetGenPart(const edm::Event&, const edm::EventSetup&);  
      virtual void GetGenJet(const edm::Event&, const edm::EventSetup&,
                             const char[60]    , vector<MyGenJet>& );  
      virtual void GetGenKin (const edm::Event&);  

      virtual void GetEvtId(const edm::Event&);
      virtual void GetL1Trig(const edm::Event&, const edm::EventSetup& );

      virtual void GetRecoVertex(const edm::Event& , const edm::EventSetup& ,
                                 const char[60]    , vector<MyVertex>& );

      virtual void GetRecoTracks(const edm::Event& , const edm::EventSetup& ,
                                 const char[60]    , vector<MyTracks>& );

      virtual void GetRecoElectron(const edm::Event& , const edm::EventSetup& ,
                                                       vector<MyElectron>&); 

      virtual void GetRecoMuon(const edm::Event& , const edm::EventSetup& ,
                                                   vector<MyMuon>&);

      // ----------member data ---------------------------

      // ----------Config data --------------------------- 

      // Modules to execute

      bool StoreGenPart;
      bool StoreGenKine;

      // Data Collection
      edm::InputTag genPartColl_ ;
      edm::InputTag hepMCColl_ ;      

      // Gfs electron Collections
      edm::InputTag  GsfElectronCollection_;
      edm::InputTag  HcalIsolationProducer_;
      edm::InputTag  trckIsolationProducer_;
     
      // Muon Collections 
      edm::InputTag  globalMuonCollection_;

      // ----------Tree & File ---------------------------

      string fOutputFileName ;
      TFile*   fout;
      TTree*   tree; 

 //   MyEvent* evt;

      // --------- Tree Content -------------------------- 

 //  public:   

      MyEvtId           EvtId;
      MyL1Trig          L1Trig;

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
      vector<MyMuon>     globalMuon;

      // --------- Vtx ID --------------------------


      Int_t vtxid;
      vector<math::XYZPoint> vtxid_xyz;



};


#endif
