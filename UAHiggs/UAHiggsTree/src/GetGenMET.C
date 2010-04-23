// Package:     UAHiggsTree
// Class:       UAHiggsTree
// author:      Xavier Janssen
// Date:        10/12/2009 
//
// Description: Function to retrieve Generated Kinematic et al.

//  system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


// DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"


void UAHiggsTree::GetGenMET(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const string GenMETCollection_ , vector<MyGenMET>& METVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;

   METVector.clear();
  
   Handle<GenMETCollection> met;
   iEvent.getByLabel(GenMETCollection_, met);

   for(reco::GenMETCollection::const_iterator met_iter=met->begin(); 
      met_iter != met->end(); met_iter++)
    {
      
      MyGenMET mymet;
     
      mymet.pt=met_iter->pt();
      mymet.phi=met_iter->phi();
      mymet.eta=met_iter->eta();
      
      
      METVector.push_back(mymet);
         

    } 

}



void UAHiggsTree::InitGenMET( vector<string> GenMETs, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = GenMETs.begin(); icoll!= GenMETs.end();icoll++){
      tree->Branch( icoll->c_str(), &(allGenMETs[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllGenMETs( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> GenMETs, vector<MyGenMET> allGenMETs[5] )
{
  for (unsigned int i=0; i!= GenMETs.size(); i++){
       GetGenMET(iEvent,iSetup,GenMETs.at(i),allGenMETs[i]);
       }

}
