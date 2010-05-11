//  system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//DataFormats

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/TrackJet.h"
#include "DataFormats/JetReco/interface/TrackJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/BTauReco/interface/TrackCountingTagInfo.h"
#include "DataFormats/BTauReco/interface/JetTag.h"

// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"



void UAHiggsTree::GetRecoTrackJet(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const string TrackJetCollection_ , vector<MyJet>& JetVector )
{

  using namespace std;
  using namespace edm;
  using namespace reco;

  JetVector.clear();
   
//   Handle<JetTagCollection> bjetsHandle;
//   iEvent.getByLabel(BJetCollection_,bjetsHandle);
 //  const JetTagCollection &bjets = *(bjetsHandle.product());
 //  JetTagCollection::const_iterator bjet = bjets.begin(); 

   Handle<TrackJetCollection> TrackJets;
   iEvent.getByLabel(TrackJetCollection_,TrackJets);
  

 //  for(TrackJetCollection::const_iterator jet=TrackJets->begin();jet!=TrackJets->end();jet++,bjet++){
   for(TrackJetCollection::const_iterator jet=TrackJets->begin();jet!=TrackJets->end();jet++){
          
    
     double discriminator=-100;
    
     
     MyJet myjet;
     
     myjet.pt             = jet->pt();
     myjet.eta            = jet->eta();
     myjet.phi            = jet->phi();
     myjet.e              = jet->energy();
     myjet.px             = jet->px();
     myjet.py             = jet->py();
     myjet.pz             = jet->pz();
     
  
   //  if(bjet->second>0.001 && bjet->second<1000) {
   //  discriminator=bjet->second;
   //  bjet++;
   //  }
   //  else{discriminator=-100;bjet++;}
    
     myjet.discriminator  = discriminator;
     
     
     JetVector.push_back(myjet);
  
   }//loop over jets

}


void UAHiggsTree::InitRecoTrackJet( vector<string> TrackJets, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = TrackJets.begin(); icoll!= TrackJets.end();icoll++){
      tree->Branch( icoll->c_str(), &(allTrackJets[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllTrackJets( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> TrackJets, vector<MyJet> allTrackJets[5] )
{
  for (unsigned int i=0; i!= TrackJets.size(); i++){
       GetRecoTrackJet(iEvent,iSetup,TrackJets.at(i),allTrackJets[i]);
       }

}
