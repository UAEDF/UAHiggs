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
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/METCollection.h"

void UAHiggsTree::GetRecoTcMET(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                                       const string
						       TcMETCollection_, vector<MyMET>& METVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;
   
   
   METVector.clear();
   
   
   Handle<METCollection> met;
   iEvent.getByLabel(TcMETCollection_, met);

   for(reco::METCollection::const_iterator met_iter=met->begin(); 
      met_iter != met->end(); met_iter++)
    {
      
      MyMET mymet;
     
      mymet.pt=met_iter->pt();
      mymet.phi=met_iter->phi();
      mymet.eta=met_iter->eta();
      
      
      METVector.push_back(mymet);
         

    }


}


void UAHiggsTree::InitRecoTcMET( vector<string> TcMETs, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = TcMETs.begin(); icoll!= TcMETs.end();icoll++){
      tree->Branch( icoll->c_str(), &(allTcMETs[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllTcMETs( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> TcMETs, vector<MyMET> allTcMETs[5] )
{
  for (unsigned int i=0; i!= TcMETs.size(); i++){
       GetRecoTcMET(iEvent,iSetup,TcMETs.at(i),allTcMETs[i]);
       }

}
