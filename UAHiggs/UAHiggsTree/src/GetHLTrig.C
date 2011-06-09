#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Trigger Inclides
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"


// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"



void UAHiggsTree::GetHLTrig(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;
 
 
  edm::InputTag srcTriggerResults_("TriggerResults"); 
  if (srcTriggerResults_.process().empty()) {
    edm::InputTag srcTriggerEvent("hltTriggerSummaryAOD");
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByLabel(srcTriggerEvent,triggerEvent);
    string hltProcName = triggerEvent.provenance()->processName();
   //  cout<<"HLTriggerAnalyzer::analyze() INFO: HLT process="<<hltProcName<<endl;
    srcTriggerResults_ = edm::InputTag(srcTriggerResults_.label()+"::"+hltProcName);
  }
 
  edm::Handle<edm::TriggerResults> trgResults;
  iEvent.getByLabel(srcTriggerResults_,trgResults);
  const edm::TriggerNames& trgNames = iEvent.triggerNames(*trgResults);
 // for(unsigned i=0 ; i < trgNames.triggerNames().size() ; ++i)cout<<trgNames.triggerNames().at(i)<<endl;
 
 if(isValidHltConfig_){
   hlt_bits_complete.clear();
   for(vector<string>::iterator requested_hlt_bit=hlt_bits.begin() ; requested_hlt_bit!=hlt_bits.end();requested_hlt_bit++){
     for(unsigned i=0 ; i < trgNames.triggerNames().size() ; ++i){
     string str1 = *requested_hlt_bit;
     string str2 = trgNames.triggerNames().at(i);
     size_t found = str1.find("_v");
     //cout<<str1<<","<<str2<<","<<found<<","<<str1.compare(0,found,str2,0,found)<<endl;
     
     if(str1.compare(0,found,str2,0,found)==0)hlt_bits_complete.push_back(trgNames.triggerNames().at(i));
     }
   }
  }
  
  isValidHltConfig_ =false;

    // Loop on requested triggers by user (config file)
  for(vector<string>::iterator requested_hlt_bit=hlt_bits_complete.begin() ; requested_hlt_bit!=hlt_bits_complete.end();requested_hlt_bit++){
    HLTrig.HLTmap[*requested_hlt_bit]= hasFired(*requested_hlt_bit, trgNames,*trgResults);
    HLTrig.HLTprescale[*requested_hlt_bit]= hltConfig.prescaleValue(iEvent,iSetup,*requested_hlt_bit);
  //  if(hasFired(*requested_hlt_bit, trgNames,*trgResults)){  cout << (*requested_hlt_bit).c_str() << " = " << hasFired(*requested_hlt_bit, trgNames,*trgResults) <<" ,prescale: "<< hltConfig.prescaleValue(iEvent,iSetup,*requested_hlt_bit)<<endl ;
  // }
  }








/*  vector<Handle<TriggerResults> > trhv;
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
*/
  try{Handle<bool> pm;
  iEvent.getByLabel("preselectionMarker",pm);
  EvtId.PreselMarker=*pm;}
  catch(...){;}
   
}


bool UAHiggsTree::hasFired(const std::string& triggerName,
				 const edm::TriggerNames& triggerNames,
				 const edm::TriggerResults& triggerResults) const
{
  unsigned index = triggerNames.triggerIndex(triggerName);
  if (index>=triggerNames.size()) {
/*    if (unknownTriggers_.find(triggerName)==unknownTriggers_.end()) {
      cout<<"HLTriggerAnalyzer::hasFired() ERROR: "
	  <<"unknown trigger name "<<triggerName<<endl;
      unknownTriggers_.insert(triggerName);
    }
*/
    return false;
  }

  return triggerResults.accept(index);
}
