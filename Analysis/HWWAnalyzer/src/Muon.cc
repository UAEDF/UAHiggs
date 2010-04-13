#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"
void HWWAnalyzer::DoMuonAnalysis(const edm::Event& iEvent){

  (m->PreSelectedMuons).clear();
  

  Handle<MuonCollection> muonsHandle;
  iEvent.getByLabel(PreSelectedMuonCollection_,muonsHandle);
  const MuonCollection & muons = *(muonsHandle.product());
  

  cout<<"================"<<endl;
  MuonCollection::const_iterator muon;
  for(muon=muons.begin(); muon!=muons.end(); muon++){
    cout << "Muon: et= " << muon->pt()
         << " eta= "     << muon->eta()
         << " phi= "     << muon->phi()<<endl;
    double  DepInTracker= muon->isolationR03().sumPt;   
    double  DepInEcal   = muon->isolationR03().emEt;   
    double  DepInHcal   = muon->isolationR03().hadEt; 
    cout<<"Muon deposit in ecal,hcal,tracker : "
	<<DepInEcal<<" , "<<DepInHcal<<" , "<<DepInTracker<<endl;
    // to dump everything in the root file
    myobject muo;
    muo.pt=muon->pt();
    muo.eta=muon->eta();
    muo.phi=muon->phi();
    muo.px=muon->px();
    muo.py=muon->py();
    muo.pz=muon->pz();
    muo.E=muon->p();
    muo.charge=muon->charge();
    muo.DepositR03Ecal=DepInEcal;
    muo.DepositR03Hcal=DepInHcal;
    muo.DepositR03TrackerOfficial=DepInTracker;
/*  muo.GlobalMuonPromptTight=muon->isGood(Muon::GlobalMuonPromptTight);
    muo.TMOneStationLoose=muon->isGood(Muon::TMOneStationLoose);
    muo.TM2DCompatibilityLoose=muon->isGood(Muon::TM2DCompatibilityLoose);
*/
   
    muo.GlobalMuonPromptTight=muon::isGoodMuon(*muon,muon::GlobalMuonPromptTight);
    muo.TMOneStationLoose=muon::isGoodMuon(*muon,muon::TMOneStationLoose);
    muo.TM2DCompatibilityLoose=muon::isGoodMuon(*muon,muon::TM2DCompatibilityLoose);
    
    (m->PreSelectedMuons).push_back(muo);


   
  }//for muons
    

}
