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
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/BTauReco/interface/TrackCountingTagInfo.h"
#include "DataFormats/BTauReco/interface/JetTag.h"

//Tracks and vertices


#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"
#include "UAHiggs/UAHiggsTree/interface/MyTracks.h"


void UAHiggsTree::GetRecoPFJet(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const string PFJetCollection_ , vector<MyJet>& JetVector )
{
  
  using namespace std;
  using namespace edm;
  using namespace reco;

  JetVector.clear();
   
     Handle<reco::PFJetCollection> hJetProduct;
     iEvent.getByLabel(PFJetCollection_, hJetProduct);
 
 
     Handle<reco::JetTagCollection> hTrackCountingHighEffBJetTags;
      iEvent.getByLabel("TCHE"+PFJetCollection_, hTrackCountingHighEffBJetTags);
// BJetCollection_

  //  const reco::PFJetCollection inJets = *(hJetProduct.product());  


  // loop through all jets
   for (reco::PFJetCollection::const_iterator jet = hJetProduct->begin(); 
       jet != hJetProduct->end(); ++jet) {
    
    reco::PFJetRef jetRef(hJetProduct, jet - hJetProduct->begin());    
    reco::JetBaseRef jetBaseRef(jetRef);

     double discriminator=-100;
      
     MyJet myjet;
     
     myjet.pt             = jet->pt();
     myjet.eta            = jet->eta();
     myjet.phi            = jet->phi();
     myjet.e              = jet->energy();
     myjet.px             = jet->px();
     myjet.py             = jet->py();
     myjet.pz             = jet->pz();
     myjet.Area           = jet->jetArea();
   //  myjet.rho            = *(rho.product());
     myjet.ChargedHadronEnergy = jet->chargedHadronEnergy();
     myjet.NeutralHadronEnergy = jet->neutralHadronEnergy();
     myjet.ChargedEmEnergy = jet->chargedEmEnergy();
     myjet.ChargedMuEnergy = jet->chargedMuEnergy();
     myjet.NeutralEmEnergy = jet->neutralEmEnergy();
     myjet.ChargedMultiplicity = jet->chargedMultiplicity();
     myjet.NeutralMultiplicity = jet->neutralMultiplicity();
     myjet.MuonMultiplicity = jet->muonMultiplicity();   

   //  cout<<PFJetCollection_<<" pt, eta : "<<jet->pt()<<" , "<<jet->eta()<<endl;



 //  if(bjet->second>0.001 && bjet->second<1000) {
 //    discriminator=bjet->second;
 //    bjet++;
 //    }
 //    else{discriminator=-100;bjet++;}
       
     myjet.discriminator  = (*(hTrackCountingHighEffBJetTags.product()))[jetBaseRef];  

     //Get neutral candidates
     
      Double_t px =0;
      Double_t py =0;
      Double_t pz =0;
      
     
      std::vector<reco::PFCandidatePtr> vcand = jet->getPFConstituents();
      for(unsigned int i=0; i<vcand.size();i++){
         
	 if(jet->getPFConstituents().at(i).isAvailable()){
         reco::PFCandidatePtr cand = jet->getPFConstituents().at(i);
	 
	 if((cand.get())->charge() == 0){
	    px += (cand.get())-> px();
	    py += (cand.get())-> py();
	    pz += (cand.get())-> pz();
	   
	    }
	 
	 }
	}
     
     myjet.neutralPx = px;
     myjet.neutralPy = py;
     myjet.neutralPz = pz;
    
     
     
     
     // ----Get Tracks associated to PF Jet
     myjet.nTracks = 0;
     
  /*   if(jet->getTrackRefs().isAvailable()){
     
       reco::TrackRefVector vtracks = jet->getTrackRefs();
       myjet.nTracks = vtracks.size();
       MyTracks track;
       for(unsigned int i=0; i<vtracks.size();i++){
         if(jet->getTrackRefs().at(i).isAvailable()){
	 reco::TrackRef trackref = jet->getTrackRefs().at(i);
         
         track.Part.v.SetPxPyPzE(trackref->momentum().x(),
                                         trackref->momentum().y(),
                                         trackref->momentum().z(),
                                         sqrt(trackref->momentum().mag2()+MASS_MU*MASS_MU));

    	 track.Part.charge = trackref->charge();
    	 track.numberOfValidTkHits    =  trackref->hitPattern().numberOfValidTrackerHits();
    	 track.numberOfValidMuonHits  =  trackref->hitPattern().numberOfValidMuonHits();
     
  	 //  cout<<trackref->hitPattern().numberOfValidTrackerHits()<<endl;
  	 //  cout<<trackref->hitPattern().numberOfValidMuonHits()<<endl;
     
     
    	 track.numberOfValidStripHits    =  trackref->hitPattern().numberOfValidStripHits();
   	 track.numberOfValidPixelHits    =  trackref->hitPattern().numberOfValidPixelHits();
   	 track.numberOfValidMuonRPCHits  =  trackref->hitPattern().numberOfValidMuonRPCHits();
   	 track.numberOfValidMuonCSCHits  =  trackref->hitPattern().numberOfValidMuonCSCHits();
   	 track.numberOfValidMuonDTHits   =  trackref->hitPattern().numberOfValidMuonDTHits();
     
    
    
   	 track.nhit  =  trackref->hitPattern().numberOfValidHits();
   	 track.chi2n =  trackref->normalizedChi2();
   	 track.dz    =  trackref->dz();
         track.d0    =  trackref->d0();

   	 track.edz   =  trackref->dzError();
         track.ed0   =  trackref->d0Error();
         track.ept   =  trackref->ptError();

         track.vx    =  trackref->vertex().x();
         track.vy    =  trackref->vertex().y();
         track.vz    =  trackref->vertex().z();

         track.quality[0] = trackref->quality(reco::TrackBase::qualityByName("loose"));
         track.quality[1] = trackref->quality(reco::TrackBase::qualityByName("tight"));
         track.quality[2] = trackref->quality(reco::TrackBase::qualityByName("highPurity"));

         track.vtxid.clear();
         track.vtxdxy.clear();
         track.vtxdz.clear();  
     
         for ( int j = 0 ; j != vtxid ; j++ )
          {
           track.vtxid.push_back( j );
           track.vtxdxy.push_back( trackref->dxy( vtxid_xyz[j] ) );
           track.vtxdz.push_back(  trackref->dz( vtxid_xyz[j] )  );
          }
         }	 
	 
     else {
     
      track.d0 = -999;
      for ( int j = 0 ; j != vtxid ; j++ )
       {
         
	  track.vtxid.push_back( j );
          track.vtxdxy.push_back( -999 );
          track.vtxdz.push_back( -999 );
       }
      }
      myjet.tracks.push_back(track);
     
      } // end loop over track for 1 jet
      } // track collection available
   //   cout<<myjet.nTracks<<endl;*/
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


void UAHiggsTree::GetAllPFJets( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> PFJets, vector<MyJet> allPFJets[15] )
{
  for (unsigned int i=0; i!= PFJets.size(); i++){
       GetRecoPFJet(iEvent,iSetup,PFJets.at(i),allPFJets[i]);
       }

}
