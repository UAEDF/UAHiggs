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
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"

void UAHiggsTree::GetRecoCaloMET(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                                       const string CaloMETCollection_, vector<MyMET>& METVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;

   METVector.clear();
   
   
   Handle<CaloMETCollection> met;
   iEvent.getByLabel(CaloMETCollection_, met);

   for(reco::CaloMETCollection::const_iterator met_iter=met->begin(); 
      met_iter != met->end(); met_iter++)
    {
      
      MyMET mymet;
     
      mymet.pt=met_iter->pt();
      mymet.phi=met_iter->phi();
      mymet.eta=met_iter->eta();
      
      
      METVector.push_back(mymet);
         

    }
}


void UAHiggsTree::InitRecoCaloMET( vector<string> CaloMETs, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = CaloMETs.begin(); icoll!= CaloMETs.end();icoll++){
      tree->Branch( icoll->c_str(), &(allCaloMETs[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllCaloMETs( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> CaloMETs, vector<MyMET> allCaloMETs[5] )
{
  for (unsigned int i=0; i!= CaloMETs.size(); i++){
       GetRecoCaloMET(iEvent,iSetup,CaloMETs.at(i),allCaloMETs[i]);
       }

}
