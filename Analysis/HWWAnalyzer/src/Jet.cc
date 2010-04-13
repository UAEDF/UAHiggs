#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"
void HWWAnalyzer::DoJetAnalysis(const edm::Event& iEvent){
  (m->RecJets).clear();
  (m->RecPFJetsIC5).clear();
  (m->RecPFJetsSC5).clear();
  (m->GenJets).clear();

   // get calo jet collection
   Handle<CaloJetCollection> jets;
   iEvent.getByLabel(JetCollection_, jets);

   // get gen jet collection
   Handle<GenJetCollection> genjets;
   iEvent.getByLabel("iterativeCone5GenJets", genjets);

   typedef std::vector<double> AlphaCollection;
   Handle<AlphaCollection> Jet_AlphaHandle;
   iEvent.getByLabel("jetvertexalpha","Var",Jet_AlphaHandle);
   AlphaCollection Jet_Alpha = *(Jet_AlphaHandle.product());

   vector<double>::const_iterator it_alpha = Jet_Alpha.begin();

   //get the jet discriminator for b-tagging
   Handle<JetTagCollection> bjetsHandle;
   iEvent.getByLabel(BJetCollection_,bjetsHandle);
   const JetTagCollection &bjets = *(bjetsHandle.product());

   JetTagCollection::const_iterator bjet = bjets.begin(); 

   cout<<"===== Gen Jets ==========="<<endl;
   for(GenJetCollection::const_iterator genjet=genjets->begin();genjet!=genjets->end();genjet++){
     double j_et=0;
     double j_eta=0;
     double j_phi=0;
     j_et=genjet->et();
     j_eta=genjet->eta();
     j_phi=genjet->phi();

     myobject myjet;
     myjet.pt=j_et;
     myjet.eta=j_eta;
     myjet.phi=j_phi;

     (m->GenJets).push_back(myjet);
     
   }//loop over jets

   cout<<"==== Calo Jets IC 5 ============"<<endl;
   for(CaloJetCollection::const_iterator jet=jets->begin();jet!=jets->end(),bjet!=bjets.end();jet++,bjet++,it_alpha++){
     double alpha=0;
     double j_et=0;
     double j_eta=0;
     double j_phi=0;
     double discriminator=0;
     j_et=jet->et();
     j_eta=jet->eta();
     j_phi=jet->phi();
     discriminator=bjet->second;
     alpha=*it_alpha;

     myobject myjet;
     myjet.pt=j_et;
     myjet.eta=j_eta;
     myjet.phi=j_phi;
     myjet.alpha=alpha;
     myjet.discriminator=discriminator;

     if(j_et>20. && fabs(j_eta)<2.5){
       cout << "->   Jet ET: " << j_et 
	    << " eta: " << j_eta 
	    << " phi: " << j_phi 
	    << " alpha: "<<alpha<<endl;
     }
     
     (m->RecJets).push_back(myjet);
     
   }//loop over jets

   //=================== PF jets iterative cone =================================

   Handle<PFJetCollection> PFjetsIC5;
   iEvent.getByLabel(JetCollection2_, PFjetsIC5);
   //   it_alpha = Jet_Alpha.begin();

   cout<<"================"<<endl;
   for(PFJetCollection::const_iterator jet=PFjetsIC5->begin();jet!=PFjetsIC5->end();jet++){
     //     double alpha=0;
     double j_et=0;
     double j_eta=0;
     double j_phi=0;
     j_et=jet->et();
     j_eta=jet->eta();
     j_phi=jet->phi();
     //     alpha=*it_alpha;

     myobject myjet;
     myjet.pt=j_et;
     myjet.eta=j_eta;
     myjet.phi=j_phi;
     //myjet.alpha=alpha;

     if(j_et>20. && fabs(j_eta)<2.5){
       cout << "->   PF Jet Iterative Cone5 ET  : " << j_et 
	    << " eta: " << j_eta 
	    << " phi: " << j_phi<<endl; 
       //	    << " alpha: "<<alpha<<endl;
     }
     
     (m->RecPFJetsIC5).push_back(myjet);
     
   }//loop over jets

   //=================== PF jets sis cone =================================

   Handle<PFJetCollection> PFjetsSC5;
   iEvent.getByLabel(JetCollection3_, PFjetsSC5);
   //it_alpha = Jet_Alpha.begin();

   cout<<"================"<<endl;
   for(PFJetCollection::const_iterator jet=PFjetsSC5->begin();jet!=PFjetsSC5->end();jet++){
     //double alpha=0;
     double j_et=0;
     double j_eta=0;
     double j_phi=0;
     j_et=jet->et();
     j_eta=jet->eta();
     j_phi=jet->phi();
     //alpha=*it_alpha;

     myobject myjet;
     myjet.pt=j_et;
     myjet.eta=j_eta;
     myjet.phi=j_phi;
     //myjet.alpha=alpha;

     if(j_et>20. && fabs(j_eta)<2.5){
       cout << "->   PF Jet Sis cone5 ET : " << j_et 
	    << " eta: " << j_eta 
	    << " phi: " << j_phi<<endl; 
       //	    << " alpha: "<<alpha<<endl;
     }
     
     (m->RecPFJetsSC5).push_back(myjet);
     
   }//loop over jets


}
