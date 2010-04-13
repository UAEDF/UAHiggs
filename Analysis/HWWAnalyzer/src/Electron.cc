#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"


void HWWAnalyzer::DoElectronAnalysis(const edm::Event& iEvent){
  (m->PreSelectedElectrons).clear();
  
  Handle<reco::GsfElectronCollection> gsfElectronsHandle;
  iEvent.getByLabel(GsfElectronCollection_,gsfElectronsHandle);
  const reco::GsfElectronCollection gsfElectrons = *(gsfElectronsHandle.product());

 // Handle<RefVector<GsfElectronCollection> > electronsRef;
 // iEvent.getByLabel(PreSelectedElectronCollection_,electronsRef);


  
  edm::Handle<CaloTowerCollection> towerHandle;
  iEvent.getByLabel(TowerCollection_, towerHandle);
  const CaloTowerCollection* towers = towerHandle.product();

  edm::Handle< edm::ValueMap<reco::IsoDeposit> > tkIsolationHandle;
  try { iEvent.getByLabel(TrackIsolationLabel_, tkIsolationHandle); }
  catch ( cms::Exception& ex ) { printf("Can't get tracker isolation product\n"); }
  const edm::ValueMap<reco::IsoDeposit>& tkIsolationVal = *tkIsolationHandle;

  edm::Handle< edm::ValueMap<double> > EcalIsolationHandle;
  try { iEvent.getByLabel(EcalJurassicIsolationLabel_, EcalIsolationHandle); }
  catch ( cms::Exception& ex ) { printf("Can't get ecal Jurassic isolation product\n"); }
  const edm::ValueMap<double>& EcalIsolationVal = *EcalIsolationHandle;

  edm::Handle< edm::ValueMap<float> > eidHandle;
  iEvent.getByLabel(eid_,eidHandle);
  const edm::ValueMap<float>& eidVal = *eidHandle;
  

  //////////////////Hcal Isolation/////////////////////
  double IsoConeSizeOutHcal_ = EleHcalIsolationParameters_.getParameter<double>("IsoConeSizeOut");
  double IsoConeSizeInHcal_ = EleHcalIsolationParameters_.getParameter<double>("IsoConeSizeIn");
  double IsoPtMinHcal_ = EleHcalIsolationParameters_.getParameter<double>("IsoPtMin");
  //////////////////Ecal Isolation/////////////////////
  double IsoConeSizeOutEcal_ = EleEcalIsolationParameters_.getParameter<double>("IsoConeSizeOut");
  double IsoConeSizeInEcal_ = EleEcalIsolationParameters_.getParameter<double>("IsoConeSizeIn");
  double IsoPtMinEcal_ = EleEcalIsolationParameters_.getParameter<double>("IsoPtMin");

  
  
  reco::GsfElectronCollection::const_iterator iElectron ;
  int i=0;

  cout<<"================"<<endl;
  for (iElectron = gsfElectrons.begin();iElectron!= gsfElectrons.end();iElectron++) {
 
    Ref<reco::GsfElectronCollection> electronRAWRef(gsfElectronsHandle,i);
 //   bool selected=true;
  //  if (find(electronsRef->begin(), electronsRef->end(),electronRAWRef)==electronsRef->end()) {
  //       selected=false;
  //  }
  //  if(!selected)continue;

    cout << "Electron: et= " << electronRAWRef->pt()
         << " eta= "         << electronRAWRef->eta()
         << " phi= "         << electronRAWRef->phi()<<endl;
    

//     //for Cluster shape for ele isolation
//     edm::Handle<reco::BasicClusterShapeAssociationCollection> clusterShapeHandle;
//     if (iElectron->classification()<100) {
//       //      iEvent.getByLabel("hybridSuperClusters","hybridShapeAssoc", clusterShapeHandle);
//       iEvent.getByLabel(BarrelClusters_, clusterShapeHandle);
//       cout<<"********* Association done for barrel"<<endl;
//     } else {
//       iEvent.getByLabel(EndCapClusters_, clusterShapeHandle);
//       //iEvent.getByLabel("multi5x5BasicClusters","multi5x5EndcapShapeAssoc", clusterShapeHandle);
//       //      iEvent.getByLabel("islandBasicClusters:islandEndcapShapeAssoc", clusterShapeHandle);
//       //      iEvent.getByLabel(endcapClusterShapeAssocProducer_, clusterShapeHandle);
//       cout<<"********* Association done for endcap"<<endl;
//     }
//     cout<<"====> Did the cluster shape association"<<endl;

//     reco::BasicClusterShapeAssociationCollection::const_iterator seedShpItr;
//     cout<<"====> seed eta is :"<<iElectron->superCluster()->seed()->eta()<<endl;
//     seedShpItr = clusterShapeHandle->find(iElectron->superCluster()->seed());
//     cout<<"====>>>> "<<endl; 
//     for(reco::BasicClusterShapeAssociationCollection::const_iterator itc=clusterShapeHandle->begin();itc!=clusterShapeHandle->end();itc++){
//       const reco::ClusterShapeRef& shapeRef = itc->val;
//       cout<<"e3x3 : "<<shapeRef->e3x3()<<endl;
//     }   
    
//     assert( seedShpItr != clusterShapeHandle->end() );
//     const reco::ClusterShapeRef& shapeRef = seedShpItr->val;

    myobject elo;
    elo.pt=iElectron->pt();
    elo.eta=iElectron->eta();
    elo.phi=iElectron->phi();
    elo.px=iElectron->px();
    elo.py=iElectron->py();
    elo.pz=iElectron->pz();
    elo.E=iElectron->energy();
    elo.charge=iElectron->charge();
    elo.classification = iElectron->classification();
    elo.HoverE         = iElectron->hadronicOverEm();
    elo.EseedPout      = iElectron->eSeedClusterOverPout();
    elo.dEta           = iElectron->deltaEtaSuperClusterTrackAtVtx();
    elo.dPhi           = iElectron->deltaPhiSuperClusterTrackAtVtx();
//     elo.s9s25=shapeRef->e3x3()/shapeRef->e5x5();
//     elo.sigmaEtaEta=sqrt(shapeRef->covEtaEta());

    //for tracker , hcal and ecal isolation 
    reco::SuperClusterRef sc = (gsfElectronsHandle->at(i)).superCluster();
    //    double et = sc.get()->energy()*sin(2*atan(exp(-sc.get()->eta())));

    //for tracker isolation offline
    reco::isodeposit::Direction electronDir(electronRAWRef->eta(), electronRAWRef->phi());
    reco::IsoDeposit::Veto EleVeto;
    EleVeto.vetoDir = electronDir;
    EleVeto.dR = 0.015;
    reco::IsoDeposit::Vetos AllVetos;
    AllVetos.push_back(EleVeto);
    double sumPt = tkIsolationVal[electronRAWRef].depositAndCountWithin(0.4,AllVetos,0.).first;
    //cout<<"sumPt from Analysis is : "<<sumPt<<endl;
    elo.TrackerIsolation=(sumPt);

    float eidResult = eidVal[electronRAWRef];
    cout<<"eid tight result is "<<eidResult<<endl;
    elo.eidTight=eidResult;

    //for ecal and hcal isolation offline
    double EcalEtSum =0.;
    double HcalEtSum =0.;

    //Take the SC position
    math::XYZPoint theCaloPosition = sc.get()->position();
    double candEta=sc.get()->eta();
    double candPhi=sc.get()->phi();

    //loop over towers for ecal isolation
    for(CaloTowerCollection::const_iterator trItr = towers->begin(); trItr != towers->end(); ++trItr){
    
      double this_pt  = trItr->emEt();
      if ( this_pt < IsoPtMinEcal_ ) 
	continue ;  
    
      double towerEta=trItr->eta();
      double towerPhi=trItr->phi();
      double twoPi= 2*M_PI;
      if(towerPhi<0) towerPhi+=twoPi;
      if(candPhi<0) candPhi+=twoPi;
      double deltaPhi=fabs(towerPhi-candPhi);
      if(deltaPhi>twoPi) deltaPhi-=twoPi;
      if(deltaPhi>M_PI) deltaPhi=twoPi-deltaPhi;
      double deltaEta = towerEta - candEta;
      
      
      double dr = deltaEta*deltaEta + deltaPhi*deltaPhi;
      if( dr < IsoConeSizeOutEcal_*IsoConeSizeOutEcal_ &&
	  dr >= IsoConeSizeInEcal_*IsoConeSizeInEcal_ )
	{
	  EcalEtSum += this_pt;
	}
      
    }//end loop over tracks

    elo.EcalIsolation=(EcalEtSum);

    //for ecal jurassic isolation
    double EcalJurassic = EcalIsolationVal[electronRAWRef];
    elo.EcalJurassicIsolation=(EcalJurassic);
    
    //loop over towers for hcal isolation
    for(CaloTowerCollection::const_iterator trItr = towers->begin(); trItr != towers->end(); ++trItr){
      
      double this_pt  = trItr->hadEt();
      if ( this_pt < IsoPtMinHcal_ ) 
	continue ;  
      
      double towerEta=trItr->eta();
      double towerPhi=trItr->phi();
      double twoPi= 2*M_PI;
      if(towerPhi<0) towerPhi+=twoPi;
      if(candPhi<0) candPhi+=twoPi;
      double deltaPhi=fabs(towerPhi-candPhi);
      if(deltaPhi>twoPi) deltaPhi-=twoPi;
      if(deltaPhi>M_PI) deltaPhi=twoPi-deltaPhi;
      double deltaEta = towerEta - candEta;
      
      
      double dr = deltaEta*deltaEta + deltaPhi*deltaPhi;
      if( dr < IsoConeSizeOutHcal_*IsoConeSizeOutHcal_ &&
	  dr >= IsoConeSizeInHcal_*IsoConeSizeInHcal_ )
	{
	  HcalEtSum += this_pt;
	}
      
    }//end loop over tracks

    elo.HcalIsolation=(HcalEtSum);




//     double isoValueEcal = myEcalIsolation.getEcalEtSum(&(gsfElectronsHandle->at(i)));
//     elo.EcalIsolation=(isoValueEcal/et);

//     //for hcal isolation
//     double isoValueHcal = myHcalIsolation.getTowerEtSum(&(gsfElectronsHandle->at(i)));
//     elo.HcalIsolation=(isoValueHcal/et);



//     double tkisol = (*tkIsolationHandle)[i].second; 
//     double hcalisol= (*HcalIsolationHandle)[i].second;
//     double ecalisol= (*EcalIsolationHandle)[i].second;
//     elo.TrackerIsolation=tkisol;
//     elo.HcalIsolation=hcalisol;
//     elo.EcalIsolation=ecalisol;
    (m->PreSelectedElectrons).push_back(elo); 
    i++;
  }//for loop on electrons
    


}
