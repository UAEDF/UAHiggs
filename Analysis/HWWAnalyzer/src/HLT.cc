#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"
void HWWAnalyzer::DoHLTAnalysis(const edm::Event& iEvent){
  (m->HLT).clear();
  (m->PreselectionMarker)=false;

  vector<Handle<TriggerResults> > trhv;
  iEvent.getManyByType(trhv);
  const int nt(trhv.size());
  
  TriggerNames triggerNames;
  
  for(int ntt=0;ntt<nt;ntt++){
    triggerNames.init(*trhv[ntt]);
    vector<string> hltNames = triggerNames.triggerNames();
    cout<<"hlt names size is "<<hltNames.size()<<endl;
    int n = 0;
    for(vector<string>::const_iterator i = hltNames.begin();i!= hltNames.end(); i++){
      if(PrintHLTNames)cout << "ntt,n,trigger: " << ntt<<","<<n<<","<<*i << " "
			    << (*trhv[ntt]).accept(n) << endl;
      for(vector<string>::iterator requested_hlt_bit=hlt_bits.begin();//hlt_bits request by user
	  requested_hlt_bit!=hlt_bits.end();requested_hlt_bit++){
	if(*i == *requested_hlt_bit){
	  (m->HLT)[*requested_hlt_bit]=(*trhv[ntt]).accept(n);
	}
      }
      n++;
    }//for i 
  }//for ntt

  try{Handle<bool> pm;
  iEvent.getByLabel("preselectionMarker",pm);
  (m->PreselectionMarker)=*pm;}
  catch(...){;}
}
