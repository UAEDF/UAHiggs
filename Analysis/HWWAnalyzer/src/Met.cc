#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"
void HWWAnalyzer::DoMetAnalysis(const edm::Event& iEvent){
  (m->RecMet).clear();
  (m->RecPFMet).clear();
  (m->GenMet).clear();

  
  Handle<GenMETCollection> genmet;
  iEvent.getByLabel(GenMetCollection_,genmet);

  Handle<CaloMETCollection> met;
  iEvent.getByLabel(MetCollection_, met);


  cout<<"===== gen met ==========="<<endl;
  for(reco::GenMETCollection::const_iterator met_iter=genmet->begin(); 
      met_iter != genmet->end(); met_iter++)
    {
      
      myobject mymet;
      mymet.pt=met_iter->pt();
      mymet.px=met_iter->px();
      mymet.py=met_iter->py();
      mymet.phi=met_iter->phi();
      (m->GenMet).push_back(mymet);
      cout<<"GenMet is : "<<mymet.pt<<endl;      

    }

  cout<<"===== calo met ==========="<<endl;
  for(reco::CaloMETCollection::const_iterator met_iter=met->begin(); 
      met_iter != met->end(); met_iter++)
    {
      
      myobject mymet;
      mymet.pt=met_iter->pt();
      mymet.px=met_iter->px();
      mymet.py=met_iter->py();
      mymet.phi=met_iter->phi();
      (m->RecMet).push_back(mymet);
      cout<<"CaloMet is : "<<mymet.pt<<endl;      

    }

  //============== PF Met ==================================

  Handle<PFMETCollection> PFmet;
  iEvent.getByLabel(MetCollection2_, PFmet);

  cout<<"================"<<endl;
  for(reco::PFMETCollection::const_iterator met_iter=PFmet->begin(); 
      met_iter != PFmet->end(); met_iter++)
    {
      
      myobject mymet;
      mymet.pt=met_iter->pt();
      mymet.px=met_iter->px();
      mymet.py=met_iter->py();
      mymet.phi=met_iter->phi();
      (m->RecPFMet).push_back(mymet);
      cout<<"PFMet is : "<<mymet.pt<<endl;

    }
  
}
