// Package:     HWWGenPart
// Class:       HWWGenPart
// author:      Xavier Janssen
// Date:        10/12/2009 
//
// Description: Function to retrieve Evt Id information

//  system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Trigger Inclides
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

//
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
using namespace l1extra;


// HWWGenPart Analysis class decleration
#include "Analysis/HWWGenPart/interface/HWWGenPart.h"

bool L1TrigDebug = false;

void HWWGenPart::GetL1Trig(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace std;

  // Tests

/*
  if (L1TrigDebug)
  {  
   edm::ESHandle<L1GtTriggerMenu> menuRcd;
   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
   const L1GtTriggerMenu* menu = menuRcd.product();

   for (CItAlgo algo = menu->gtAlgorithmMap().begin(); 
                algo!=menu->gtAlgorithmMap().end(); 
                ++algo) 
   {
     cout << "Name: " << (algo->second).algoName() 
          << " Alias: " << (algo->second).algoAlias() 
          << " Bit: " << (algo->second).algoBitNumber()
           << " Result: " << l1AlgorithmResult(iEvent, iSetup, (algo->second).algoName() )
          << std::endl;
   }
  }
  cout << "L1_SingleEG1   = " << l1AlgorithmResult(iEvent, iSetup, "L1_SingleEG1") << endl;
*/

   // L1 Trigger bits

   edm::Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
   iEvent.getByLabel("gtDigis",L1GTRR);
   for (int i=0 ; i <128 ; i++) 
   {
     if (L1TrigDebug) cout << "PhysicsTriggerWord :" << i << " " << L1GTRR->decisionWord()[i] << endl;
     L1Trig.PhysTrigWord[i] = L1GTRR->decisionWord()[i];
   }
   for (int i=0 ; i <64  ; i++)
   {
    if (L1TrigDebug) cout << "technicalTriggerWord :" << i << " " << L1GTRR->technicalTriggerWord()[i] << endl;
    L1Trig.TechTrigWord[i] = L1GTRR->technicalTriggerWord()[i]; 
   }

/*
   // L1 extra particles 
   edm::Handle<l1extra::L1EmParticleCollection> L1TrigEmColl;
   iEvent.getByLabel("l1extraParticles",L1TrigEmColl);
   // for ( size_t iL1TEm = 0; iL1TEmColl < L1TrigEmColl->size(); ++iL1TEm ){
   int ii=0; 
   for ( l1extra::L1EmParticleCollection::const_iterator l1part = L1TrigEmColl->begin() ;
         l1part !=L1TrigEmColl->end() ; ++l1part ) { 
       cout << "l1part: " << ii << endl;
       cout << "       type= " << l1part->type() << endl; 
       cout << "       bx  = " << l1part->bx() << endl;
       ++ii;
   }
*/

}

