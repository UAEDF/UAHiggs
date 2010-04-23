
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Trigger Inclides
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"


// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"



void UAHiggsTree::GetHLTrig(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;
  
  vector<Handle<TriggerResults> > trhv;
  iEvent.getManyByType(trhv);
  const int nt(trhv.size());
  
  TriggerNames triggerNames;
  
  for(int ntt=0;ntt<nt;ntt++){
    triggerNames.init(*trhv[ntt]);
    vector<string> hltNames = triggerNames.triggerNames();
   // cout<<"hlt names size is "<<hltNames.size()<<endl;
    int n = 0;
    for(vector<string>::const_iterator i = hltNames.begin();i!= hltNames.end(); i++){
                  //     cout << "ntt,n,trigger: " << ntt<<","<<n<<","<<*i << " "
		//	    << (*trhv[ntt]).accept(n) << endl;
      for(vector<string>::iterator requested_hlt_bit=hlt_bits.begin();//hlt_bits request by user
	  requested_hlt_bit!=hlt_bits.end();requested_hlt_bit++){
	if(*i == *requested_hlt_bit){
	  HLTrig.HLTmap[*requested_hlt_bit]=(*trhv[ntt]).accept(n);
	}
      }
      n++;
    }//for i 
  }//for ntt

  try{Handle<bool> pm;
  iEvent.getByLabel("preselectionMarker",pm);
  EvtId.PreselMarker=*pm;}
  catch(...){;}
   
}
