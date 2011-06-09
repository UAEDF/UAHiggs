// Description: Function to retrieve Generated Kinematic et al.

// DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"


// UABaseTree Analysis class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"


bool PUSumInfoDebug = true ;

void UAHiggsTree::GetPUSumInfo(const edm::Event& iEvent)
{

  using namespace std;
  using namespace edm;
  using namespace reco;


   pusuminfo.Reset();
   if ( ! iEvent.isRealData() ) {
     edm::Handle<vector<PileupSummaryInfo> > puInfoH;
     try {
       iEvent.getByLabel(pusuminfo_,puInfoH);
       iEvent.getByLabel("addPileupInfo",puInfoH);
      
       for(unsigned it=0; it<puInfoH->size(); ++it ){
         pusuminfo.nPU = puInfoH->at(it).getPU_NumInteractions() ;
         for(int i=0; i<puInfoH->at(it).getPU_NumInteractions();i++){
           pusuminfo.zposition.push_back(puInfoH->at(it).getPU_zpositions()[i]);
           pusuminfo.sumpT_lowpT.push_back(puInfoH->at(it).getPU_sumpT_lowpT()[i]);
           pusuminfo.sumpT_highpT.push_back(puInfoH->at(it).getPU_sumpT_highpT()[i]);
           pusuminfo.ntrks_lowpT.push_back(puInfoH->at(it).getPU_ntrks_lowpT()[i]);
           pusuminfo.ntrks_highpT.push_back(puInfoH->at(it).getPU_ntrks_highpT()[i]);
      
        }
       
       
       } 
   
     }
     catch (...){
      cout << "[UABaseTree::GetPUSumInfo] Was not able to retrieve PU Summary" << endl;
     }
   }   

   Handle<double>  rho;
   Handle<double>  rhoiso;
   edm::Handle<std::vector<double> > rs;
   try {
    iEvent.getByLabel(InputTag("kt6PFJets:rho"),rho);
    iEvent.getByLabel(InputTag("kt6PFJetsIso:rho"),rhoiso);
    iEvent.getByLabel(edm::InputTag("kt6PFJetsEta","rhos"),rs);
    pusuminfo.median_rho = *(rho.product()) ;
    pusuminfo.rho_iso = *(rhoiso.product()) ;
    for(unsigned i=0; i<rs->size(); ++i){
    pusuminfo.rho_eta.push_back(rs->at(i));
    }
   }
   
   catch (...){
    cout << "[UABaseTree::GetPUSumInfo] Was not able to retrieve rho densities" << endl;
   }
   
  // if(PUSumInfoDebug) pusuminfo.Print();
}

