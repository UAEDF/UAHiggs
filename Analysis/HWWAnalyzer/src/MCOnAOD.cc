#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"

void HWWAnalyzer::DoMCOnAODAnalysis(const edm::Event& iEvent){
  //MCNus is for status 1 nus, but genparticles are with status 3
  (m->MCNus).clear();
  (m->GenParticle).clear();


  int nmuons=0;
  int nelectrons=0;

  //Handle<objetc_type> is a container and is filled when getByLabel(...)
  //or getByType(...) are called
//   Handle<HepMCProduct> EvtHandle ;
//   iEvent.getByLabel( "source", EvtHandle ) ;
//   // iEvent.getByLabel( "VtxSmeared", EvtHandle ) ;
//   const HepMC::GenEvent* evt = EvtHandle->GetEvent() ;

   Handle< int > genProcessID;
   iEvent.getByLabel( "genEventProcID", genProcessID );
   int processId = *genProcessID;
   cout<<"Process ID : "<<processId<<endl;

   Handle< double > genEventScale;
   iEvent.getByLabel( "genEventScale", genEventScale );
   double ptHat = *genEventScale;
   (m->PtHat)=ptHat;

  cout<<"Now I am here ... "<<endl;

  //For Chowder
  if(ItIsASoup){
    edm::Handle<double> weightHandle;
    iEvent.getByLabel("weight", weightHandle);
    double weight = *weightHandle;
    (m->weight)=weight;
    if(processId==4){ //Chowder
      edm::Handle<int> ProcessIDHandle;
      iEvent.getByLabel(Process_ID, ProcessIDHandle);//Process_ID defined in cfg file
      processId= *ProcessIDHandle;
    }
  }
  //Now processId has its final value
  (m->ProcessId)=processId;

  //For MC@NLO
  if(!ItIsASoup){
    double weight = 1.0;
    Handle< double > genEventWeight;
    iEvent.getByLabel( "genEventWeight", genEventWeight );
    double Weight = *genEventWeight;
    if(Weight < 0) weight = -1.0; 
    (m->weight)=weight;
  }
  //For Signal
  edm::Handle<double> KFactor;

  try {
    iEvent.getByLabel(KFProducerLabel_,KFactor);
    double kfactor = *KFactor;
    (m->KFactor)=kfactor;
  }
  catch (...){;}
  //
  using namespace reco;
  //These two should be used for datasets produced with 1_6_9 or higher
  //  Handle<GenParticleCollection> genParticles;
  //  iEvent.getByLabel("genParticles", genParticles);
  Handle<CandidateCollection> genParticles;
  iEvent.getByLabel("genParticleCandidates", genParticles);
  for(CandidateCollection::const_iterator itGenPar = genParticles->begin(); itGenPar < genParticles->end(); itGenPar++) {
    int pid = itGenPar->pdgId();
    double status=itGenPar->status();
    double E=itGenPar->energy();
    double pt=itGenPar->pt();
    double eta=itGenPar->eta();
    double phi=itGenPar->phi();
    double px=itGenPar->px();
    double py=itGenPar->py();
    double pz=itGenPar->pz();
    int charge=0;
    if(pid>0)charge=+1;
    else if(pid<0)charge=-1;    

    if(status==3){

      myobject genpart;
      genpart.pt=pt;
      genpart.eta=eta;
      genpart.phi=phi;
      genpart.E=E;
      genpart.px=px;
      genpart.py=py;
      genpart.pz=pz;
      genpart.charge=charge;
      if(abs(pid)==6)
	genpart.name="top";
      if(abs(pid)==11){
	genpart.name="ele";
	nelectrons++;
      }
      if(abs(pid)==13){
	genpart.name="mu";
	nmuons++;
      }
      if(abs(pid)==15)
	genpart.name="tau";
      if(abs(pid)==12)
	genpart.name="nu_ele";
      if(abs(pid)==14)
	genpart.name="nu_mu";
      if(abs(pid)==16)
	genpart.name="nu_tau";
      if(abs(pid)==23)
	genpart.name="Z";
      if(abs(pid)==24)
	genpart.name="W";
      if(abs(pid)==25)
	genpart.name="H";
      if(abs(pid)==2212)
	genpart.name="p";
      if(abs(pid)>=1 && abs(pid)<=5)
	genpart.name="q";
      if(abs(pid)==21)
	genpart.name="g";
      (m->GenParticle).push_back(genpart);

      if(abs(pid)==25){
	cout<<"Higgs boson pt : "<<pt<<endl;
	continue;
      }


    }//if status == 3

    //Gen MET calculation
    if(status==1){
      if(abs(pid)==12 || abs(pid)==14 || abs(pid)==16){
	myobject gn;
	gn.px=px;
	gn.py=py;
	gn.pt=pt;
	(m->MCNus).push_back(gn);
      }
    }

  }//loop over MC particles in the event



  ThisEvent="";
  if(nmuons==2){ThisEvent="mm";}
  if(nelectrons==2){ThisEvent="ee";}
  if(nmuons==1 && nelectrons==1){ThisEvent="em";}
}
