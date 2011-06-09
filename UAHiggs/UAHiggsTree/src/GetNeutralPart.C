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
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"


// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"
#include "UAHiggs/UAHiggsTree/interface/MyTracks.h"


void UAHiggsTree::GetNeutralPart(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const string PFCollection_ , vector<MyNeutralPart>& NeutralPartVector )
{
  
  using namespace std;
  using namespace edm;
  using namespace reco;

  NeutralPartVector.clear();
   
  Handle<PFCandidateCollection> pfCandidates;
  iEvent.getByLabel( PFCollection_, pfCandidates);

  for(PFCandidateCollection::const_iterator cand=pfCandidates->begin();cand!=pfCandidates->end();cand++){
  MyNeutralPart myneutral;
  
    if(cand->charge() == 0){
	 myneutral.px = cand-> px();
	 myneutral.py = cand-> py();
	 myneutral.pz = cand-> pz();
         myneutral.eta = cand-> eta();
    
    }
  NeutralPartVector.push_back(myneutral); 
     
 }
}
     


void UAHiggsTree::InitNeutralPart( vector<string> PFNeutralParts, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = PFNeutralParts.begin(); icoll!= PFNeutralParts.end();icoll++){
      tree->Branch( icoll->c_str(), &(allNeutrals[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllNeutralParts( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> PFNeutralParts, vector<MyNeutralPart> allNeutrals[15] )
{
  for (unsigned int i=0; i!= PFNeutralParts.size(); i++){
       GetNeutralPart(iEvent,iSetup,PFNeutralParts.at(i),allNeutrals[i]);
       }

}
