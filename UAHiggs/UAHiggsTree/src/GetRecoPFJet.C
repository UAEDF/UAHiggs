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
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/BTauReco/interface/TrackCountingTagInfo.h"
#include "DataFormats/BTauReco/interface/JetTag.h"

// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"



void UAHiggsTree::GetRecoPFJet(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const string PFJetCollection_ , vector<MyJet>& JetVector )
{

  using namespace std;
  using namespace edm;
  using namespace reco;

  JetVector.clear();
   
 //  Handle<JetTagCollection> bjetsHandle;
 //  iEvent.getByLabel(BJetCollection_,bjetsHandle);
 //  const JetTagCollection &bjets = *(bjetsHandle.product());

//   JetTagCollection::const_iterator bjet = bjets.begin(); 

   Handle<PFJetCollection> PFJets;
   iEvent.getByLabel(PFJetCollection_,PFJets);
  

//   for(PFJetCollection::const_iterator jet=PFJets->begin();jet!=PFJets->end();jet++,bjet++){
   for(PFJetCollection::const_iterator jet=PFJets->begin();jet!=PFJets->end();jet++){
         
    
     double discriminator=-100;
      
     MyJet myjet;
     
     myjet.pt             = jet->pt();
     myjet.eta            = jet->eta();
     myjet.phi            = jet->phi();
     myjet.e              = jet->energy();
     myjet.px             = jet->px();
     myjet.py             = jet->py();
     myjet.pz             = jet->pz();
   
     myjet.ChargedHadronEnergy = jet->chargedHadronEnergy();
     myjet.NeutralHadronEnergy = jet->neutralHadronEnergy();
     myjet.ChargedEmEnergy = jet->chargedEmEnergy();
     myjet.ChargedMuEnergy = jet->chargedMuEnergy();
     myjet.NeutralEmEnergy = jet->neutralEmEnergy();
     myjet.ChargedMultiplicity = jet->chargedMultiplicity();
     myjet.NeutralMultiplicity = jet->neutralMultiplicity();
     myjet.MuonMultiplicity = jet->muonMultiplicity();   





 //  if(bjet->second>0.001 && bjet->second<1000) {
 //    discriminator=bjet->second;
 //    bjet++;
 //    }
 //    else{discriminator=-100;bjet++;}
    
     myjet.discriminator  = discriminator;
  
     JetVector.push_back(myjet);
  
   }//loop over jets

}


void UAHiggsTree::InitRecoPFJet( vector<string> PFJets, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = PFJets.begin(); icoll!= PFJets.end();icoll++){
      tree->Branch( icoll->c_str(), &(allPFJets[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllPFJets( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> PFJets, vector<MyJet> allPFJets[5] )
{
  for (unsigned int i=0; i!= PFJets.size(); i++){
       GetRecoPFJet(iEvent,iSetup,PFJets.at(i),allPFJets[i]);
       }

}
