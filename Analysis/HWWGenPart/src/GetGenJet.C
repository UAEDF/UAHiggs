// Package:     HWWGenPart
// Class:       HWWGenPart
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
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// HWWGenPart Analysis class decleration
#include "Analysis/HWWGenPart/interface/HWWGenPart.h"


bool GenJetDebug = false;

void HWWGenPart::GetGenJet(const edm::Event& iEvent , const edm::EventSetup& iSetup,
                            const char collName[60] , vector<MyGenJet>& JetVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;

   // Clear

   GenJet.clear();
   

   // Handle to access PDG data from iSetup
   ESHandle <ParticleDataTable> pdt;
   iSetup.getData( pdt );


   // get gen jet collection
   Handle<GenJetCollection> genjets;
   iEvent.getByLabel(collName, genjets);

   for(GenJetCollection::const_iterator genjet=genjets->begin();genjet!=genjets->end();genjet++){ 
   
      MyGenJet Jet;

      Jet.et  = genjet->et();
      Jet.pt  = genjet->pt();
      Jet.eta = genjet->eta();
      Jet.phi = genjet->phi();
      Jet.e   = genjet->energy();
      Jet.px  = genjet->px();
      Jet.py  = genjet->py();
      Jet.pz  = genjet->pz();
      Jet.npart = genjet->nConstituents();

      Jet.JetPart.clear();

      if (GenJetDebug) cout << genjet->nConstituents() << endl;    
      std::vector <const reco::GenParticle*> mcparts = genjet->getGenConstituents();
      for (unsigned i = 0; i < mcparts.size (); i++) {
        const reco::GenParticle* p = mcparts[i]; 
        if (GenJetDebug) 
          cout    << i
                  << " " <<  p->pdgId()
                  << " " << (pdt->particle(p->pdgId()))->name()
                  << " " << p->pt()
                  << " " << p->eta()
                  << " " << p->phi()
                  << " " << p->charge()
                  << endl ;

         MyGenPart genpart;

         // Four vector

         genpart.pt   = p->pt();
         genpart.eta  = p->eta();
         genpart.phi  = p->phi();
         genpart.e    = p->energy();
         genpart.px   = p->px();
         genpart.py   = p->py();
         genpart.pz   = p->pz();
         genpart.m    = p->mass();
         genpart.v.SetPxPyPzE( p->px() , p->py() , p->pz() , p->energy() );

         // Extra properties

         genpart.charge  = p->charge();
         genpart.pdgId   = p->pdgId();
         genpart.name    = (pdt->particle(p->pdgId()))->name();
         genpart.status  = p->status();

         Jet.JetPart.push_back(genpart);

      }
      vector<int> i;

      JetVector.push_back(Jet);

   }
}
