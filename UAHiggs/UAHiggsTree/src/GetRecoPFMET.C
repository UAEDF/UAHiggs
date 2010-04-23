// UAHiggsTree UAHiggs class declaration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"

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

// Candidates
#include "DataFormats/Candidate/interface/CandAssociation.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

//DataFormats
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"


void UAHiggsTree::GetRecoPFMET(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                                       const string
						       PFMETCollection_, vector<MyMET>& METVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;

   METVector.clear();
   
   
   Handle<PFMETCollection> met;
   iEvent.getByLabel(PFMETCollection_, met);

   for(reco::PFMETCollection::const_iterator met_iter=met->begin(); 
      met_iter != met->end(); met_iter++)
    {
      
      MyMET mymet;
     
      mymet.pt=met_iter->pt();
      mymet.phi=met_iter->phi();
      mymet.eta=met_iter->eta();
      
      
      METVector.push_back(mymet);
         

    }

}


void UAHiggsTree::InitRecoPFMET( vector<string> PFMETs, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = PFMETs.begin(); icoll!= PFMETs.end();icoll++){
      tree->Branch( icoll->c_str(), &(allPFMETs[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllPFMETs( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> PFMETs, vector<MyMET> allPFMETs[5] )
{
  for (unsigned int i=0; i!= PFMETs.size(); i++){
       GetRecoPFMET(iEvent,iSetup,PFMETs.at(i),allPFMETs[i]);
       }

}
