//  system include files
#include <iostream>
#include <string>
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



void UAHiggsTree::GetRecoCaloJet(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const string CaloJetCollection_ , vector<MyJet>& JetVector )
{

  using namespace std;
  using namespace edm;
  using namespace reco;

  JetVector.clear();
   
 /*  size_t sz = CaloJetCollection_.size()-8;
   string algo = CaloJetCollection_.substr(0,sz);
   string JValpha = "JVA";
   string JVbeta  = "JVB";
   JValpha.append(algo);
   JVbeta.append(algo);
   
   typedef std::vector<double> AlphaCollection;
   typedef std::vector<double> BetaCollection;
  
   Handle<AlphaCollection> Jet_AlphaHandle;
   iEvent.getByLabel(JValpha,"Var",Jet_AlphaHandle);
   AlphaCollection Jet_Alpha = *(Jet_AlphaHandle.product());

   Handle<BetaCollection> Jet_BetaHandle;
   iEvent.getByLabel(JVbeta,"Var",Jet_BetaHandle);
   BetaCollection Jet_Beta = *(Jet_BetaHandle.product());
   
  
   vector<double>::const_iterator it_alpha = Jet_Alpha.begin();
   vector<double>::const_iterator it_beta =  Jet_Beta.begin();  
  */
  
   
 
 //  const JetTagCollection &bjets = *(bjetsHandle.product());

  // JetTagCollection::const_iterator bjet = bjets.begin(); 

   Handle<CaloJetCollection> CaloJets;
   iEvent.getByLabel(CaloJetCollection_,CaloJets);
  
   Handle<JetTagCollection> bjetsHandle;
   iEvent.getByLabel(BJetCollection_,bjetsHandle);

   
  
  
    for(CaloJetCollection::const_iterator jet=CaloJets->begin();jet!=CaloJets->end();jet++){//,it_alpha++,it_beta++){
  //   for(CaloJetCollection::const_iterator jet=CaloJets->begin();jet!=CaloJets->end();jet++,it_alpha++,it_beta++){ 
    
     reco::CaloJetRef jetRef(CaloJets, jet - CaloJets->begin());
     reco::JetBaseRef jetBaseRef(jetRef);

     double alpha=0;
     double beta=0;
     double discriminator=-100;
     
    // alpha=*it_alpha;
   //  beta=*it_beta;
     
     
     MyJet myjet;
     
     myjet.pt             = jet->pt();
     myjet.eta            = jet->eta();
     myjet.phi            = jet->phi();
     myjet.e              = jet->energy();
     myjet.px             = jet->px();
     myjet.py             = jet->py();
     myjet.pz             = jet->pz();
     myjet.alpha          = alpha;
     myjet.beta           = beta;
  
  
     discriminator =  (*(bjetsHandle.product()))[jetBaseRef];  
     
   
   
   
   //  if(bjet->second>0.001 && bjet->second<1000) {
  //   discriminator=bjet->second;
  //   bjet++;
  //   }
  //   else{discriminator=-100;bjet++;}
    
     myjet.discriminator  = discriminator;
   //  cout<<discriminator<<endl;
     JetVector.push_back(myjet);
  
   }//loop over jets

}


void UAHiggsTree::InitRecoCaloJet( vector<string> CaloJets, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = CaloJets.begin(); icoll!= CaloJets.end();icoll++){
      tree->Branch( icoll->c_str(), &(allCaloJets[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllCaloJets( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> CaloJets, vector<MyJet> allCaloJets[5] )
{
  for (unsigned int i=0; i!= CaloJets.size(); i++){
       GetRecoCaloJet(iEvent,iSetup,CaloJets.at(i),allCaloJets[i]);
       }

}
