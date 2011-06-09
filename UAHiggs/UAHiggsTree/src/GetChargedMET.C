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
//#include "DataFormats/METReco/interface/MET.h"
//#include "DataFormats/METReco/interface/METCollection.h"
#include "RecoMET/METAlgorithms/interface/PFSpecificAlgo.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"



void UAHiggsTree::GetChargedMET(const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   using namespace std;
   using namespace edm;
   using namespace reco;
   
   
   ChargedMET.clear();
   ChargedPlusNeutralMET.clear();
  
   edm::Handle<edm::ValueMap<reco::PFMET> > vmH;
   edm::Handle<edm::ValueMap<reco::PFMET> > vmCNH;
   edm::Handle<reco::VertexCollection> vtxH;

   iEvent.getByLabel("chargedMetProducer",vmH); 
   iEvent.getByLabel("chargedPlusNeutralMetProducer",vmCNH); 
   iEvent.getByLabel("offlinePrimaryVerticesDA",vtxH);
 
   for ( int i=0 ; i < (signed) vtxH->size() ; ++i ) {

     MyMET mymet;
     mymet.pt = (*vmH)[reco::VertexRef(vtxH,i)].pt()  ;
     mymet.phi= (*vmH)[reco::VertexRef(vtxH,i)].phi() ;
     mymet.eta= (*vmH)[reco::VertexRef(vtxH,i)].eta() ;
     ChargedMET.push_back(mymet);

     MyMET mymetCN;
     mymetCN.pt = (*vmCNH)[reco::VertexRef(vtxH,i)].pt()  ;
     mymetCN.phi= (*vmCNH)[reco::VertexRef(vtxH,i)].phi() ;
     mymetCN.eta= (*vmCNH)[reco::VertexRef(vtxH,i)].eta() ;
     ChargedPlusNeutralMET.push_back(mymetCN);


   }

/*   
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
*/

}
