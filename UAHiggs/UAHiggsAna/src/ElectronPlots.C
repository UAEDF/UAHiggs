#include "../include/ElectronPlots.h"
#include "../include/MyElectron.h"




//ClassImp(ElectronPlots)

ElectronPlots::ElectronPlots(){
  Electroncoll = "none";
  this->init();
}

ElectronPlots::ElectronPlots(TString collname){
  Electroncoll = collname;
  this->init();
}




ElectronPlots::~ElectronPlots(){ }


void ElectronPlots::init(){
 
// Particle basic properties
    
    pt = new TH1F("pt_"+Electroncoll,"pt_"+Electroncoll+";pt;#events",40,0,200); 
    eta = new TH1F("eta_"+Electroncoll,"eta_"+Electroncoll+";eta;#events",40,-10,10); 
    phi = new TH1F("phi_"+Electroncoll,"phi_"+Electroncoll+";phi;#events",30,-TMath::Pi(),TMath::Pi()); 
    
    // Basic properties            
       eSupClusOverP       = new TH1F("eSupClusOverP_"+Electroncoll,"eSupClusOverP_"+Electroncoll+";eSupClusOverP;#events",100,0,10);
       eSeedClusOverPout   = new TH1F("eSeedClusOverPout_"+Electroncoll,"eSeedClusOverPout_"+Electroncoll+";eSeedClusOverPout;#events",100,0,10); 
       PIn         = new TH1F("PIn_"+Electroncoll,"PIn_"+Electroncoll+";PIn;#events",40,0,200);
       POut         = new TH1F("POut_"+Electroncoll,"POut_"+Electroncoll+";POut;#events",40,0,200);
       dEtaSupClusTrVtx    = new TH1F("dEtaSupClusTrVtx_"+Electroncoll,"dEtaSupClusTrVtx_"+Electroncoll+";dEtaSupClusTrVtx;#events",100,-0.05,0.05); 
       dEtaSeedClusTrCalo  = new TH1F("dEtaSeedClusTrCalo_"+Electroncoll,"dEtaSeedClusTrCalo_"+Electroncoll+";dEtaSeedClusTrCalo;#events",100,-0.05,0.05); 
       dPhiSupClusTrVtx    = new TH1F("dPhiSupClusTrVtx_"+Electroncoll,"dPhiSupClusTrVtx_"+Electroncoll+";dPhiSupClusTrVtx;#events",100,-0.5,0.5); 
       dPhiSeedClusTrCalo  = new TH1F("dPhiSeedClusTrCalo_"+Electroncoll,"dPhiSeedClusTrCalo_"+Electroncoll+";dPhiSeedClusTrCalo;#events",100,-0.5,0.5); 
       fbrem               = new TH1F("fbrem_"+Electroncoll,"fbrem_"+Electroncoll+";fbrem;#events",100,-2,2); 
    
         isBarrel            = new TH1F("isBarrel_"+Electroncoll,"isBarrel_"+Electroncoll+";isBarrel;#events",2,0,2); 
         isEndCap            = new TH1F("isEndCap_"+Electroncoll,"isEndCap_"+Electroncoll+";isEndCap;#events",2,0,2);
    
         isEcalDriven        = new TH1F("isEcalDriven_"+Electroncoll,"isEcalDriven_"+Electroncoll+";isEcalDriven;#events",2,0,2);
         isTrackerDriven     = new TH1F("isTrackerDriven_"+Electroncoll,"isTrackerDriven_"+Electroncoll+";;#events",2,0,2);
   
         isEScaleCorr        = new TH1F("isEScaleCorr_"+Electroncoll,"isEScaleCorr_"+Electroncoll+";isEScaleCorr;#events",2,0,2); 
         isMomentumCorr      = new TH1F("isMomentumCorr_"+Electroncoll,"isMomentumCorr_"+Electroncoll+";isMomentumCorr;#events",2,0,2); 
         nClus               = new TH1F("nClus_"+Electroncoll,"nClus_"+Electroncoll+";nClus;#events",50,0,50); 
         classification      = new TH1F("classification_"+Electroncoll,"classification_"+Electroncoll+";classification;#events",5,0,5); 
    
    

    // Extra Isolation variables 
    
   
       EcalRecHitIsoDr04        = new TH1F("EcalRecHitIsoDr04_"+Electroncoll,"EcalRecHitIsoDr04_"+Electroncoll+";EcalRecHitIsoDr04;#events",100,-5,100);
       HcalDepth1TowerSumEtDr04 = new TH1F("HcalDepth1TowerSumEtDr04_"+Electroncoll,"HcalDepth1TowerSumEtDr04_"+Electroncoll+";HcalDepth1TowerSumEtDr04;#events",100,0,50);
       HcalDepth2TowerSumEtDr04 = new TH1F("HcalDepth2TowerSumEtDr04_"+Electroncoll,"HcalDepth2TowerSumEtDr04_"+Electroncoll+";HcalDepth2TowerSumEtDr04;#events",100,0,50);
       TrackIsolationDr04       = new TH1F("TrackIsolationDr04_"+Electroncoll,"TrackIsolationDr04_"+Electroncoll+";TrackIsolationDr04;#events",100,0,100);
       EcalRecHitIsoDr03        = new TH1F("EcalRecHitIsoDr03_"+Electroncoll,"EcalRecHitIsoDr03_"+Electroncoll+";EcalRecHitIsoDr03;#events",100,-0.1,1);
       HcalTowerSumEtDr03       = new TH1F("HcalTowerSumEtDr03_"+Electroncoll,"HcalTowerSumEtDr03_"+Electroncoll+";HcalTowerSumEtDr03;#events",100,0,1);
       HcalDepth1TowerSumEtDr03 = new TH1F("HcalDepth1TowerSumEtDr03_"+Electroncoll,"HcalDepth1TowerSumEtDr03_"+Electroncoll+";HcalDepth1TowerSumEtDr03;#events",100,0,20);
       HcalDepth2TowerSumEtDr03 = new TH1F("HcalDepth2TowerSumEtDr03_"+Electroncoll,"HcalDepth2TowerSumEtDr03_"+Electroncoll+";HcalDepth2TowerSumEtDr03;#events",100,0,20);
       TrackIsolationDr03       = new TH1F("TrackIsolationDr03_"+Electroncoll,"TrackIsolationDr03_"+Electroncoll+";TrackIsolationDr03;#events",100,0,0.1);
    
    
       IsolationCombinedEndCap03      = new TH1F("IsolationCombinedEndCap03_"+Electroncoll,"IsolationCombinedEndCap03_"+Electroncoll+";IsolationCombinedEndCap03;#events",100,0,0.1);  
       IsolationCombinedBarrel03      = new TH1F("IsolationCombinedBarrel03_"+Electroncoll,"IsolationCombinedBarrel03_"+Electroncoll+";IsolationCombinedBarrel03;#events",100,0,0.1);  
   
    
    // Id variables
    
       eidRobustLoose        = new TH1F("eidRobustLoose_"+Electroncoll,"eidRobustLoose_"+Electroncoll+";eidRobustLoose;#events",2,0,2); 
       eidRobustTight        = new TH1F("eidRobustTight_"+Electroncoll,"eidRobustTight_"+Electroncoll+";eidRobustTight;#events",2,0,2);
       eidLoose              = new TH1F("eidLoose_"+Electroncoll,"eidLoose_"+Electroncoll+";eidLoose;#events",2,0,2);
       eidTight              = new TH1F("eidTight_"+Electroncoll,"eidTight_"+Electroncoll+";eidTight;#events",2,0,2);
    
    // Extra shape variables
    
       E15                     = new TH1F("E15_"+Electroncoll,"E15_"+Electroncoll+";E15;#events",100,0,250);                 
       E25Max                  = new TH1F("E25Max_"+Electroncoll,"E25Max_"+Electroncoll+";E25Max;#events",100,0,250); 
       E55                     = new TH1F("E55_"+Electroncoll,"E55_"+Electroncoll+";E55;#events",100,0,300);
       CovEtaEta               = new TH1F("CovEtaEta_"+Electroncoll,"CovEtaEta_"+Electroncoll+";CovEtaEta;#events",100,0,0.1);      
       CoviEtaiEta             = new TH1F("CoviEtaiEta_"+Electroncoll,"CoviEtaiEta_"+Electroncoll+";CoviEtaiEta;#events",100,0,0.1);     
       HadronicOverEm          = new TH1F("HadronicOverEm_"+Electroncoll,"HadronicOverEm_"+Electroncoll+";HadronicOverEm;#events",100,0,1);  
       HcalDepth1OverEcal      = new TH1F("HcalDepth1OverEcal_"+Electroncoll,"HcalDepth1OverEcal_"+Electroncoll+";HcalDepth1OverEcal;#events",100,0,0.5);    
       HcalDepth2OverEcal      = new TH1F("HcalDepth2OverEcal_"+Electroncoll,"HcalDepth2OverEcal_"+Electroncoll+";HcalDepth2OverEcal;#events",100,0,0.5);
    
    // conversion variables
    
    dist_conv    = new TH1F("dist_conv_"+Electroncoll,"dist_conv_"+Electroncoll+";dist_conv;#events",100,-0.5,0.5);
    dcot_conv  = new TH1F("dcot_conv_"+Electroncoll,"dcot_conv_"+Electroncoll+";dcot_conv;#events",100,-0.5,0.5); 
 
    // vertex
   
   
    d0         = new  TH1F("d0_"+Electroncoll,"d0_"+Electroncoll+";d0;#events",100,0,0.1);
  
   //   = new TH1F("_"+Electroncoll,"_"+Electroncoll+";;#events",,,);
    
  // Particle basic properties
    
    pt->Sumw2(); 
    eta->Sumw2(); 
    phi->Sumw2(); 
    
    // Basic properties            
    eSupClusOverP      ->Sumw2();
    eSeedClusOverPout  ->Sumw2(); 
    PIn        ->Sumw2();
    POut        ->Sumw2();
    dEtaSupClusTrVtx   ->Sumw2(); 
    dEtaSeedClusTrCalo ->Sumw2(); 
    dPhiSupClusTrVtx   ->Sumw2(); 
    dPhiSeedClusTrCalo ->Sumw2(); 
    fbrem              ->Sumw2(); 
    
    isBarrel           ->Sumw2(); 
    isEndCap           ->Sumw2();
    
    isEcalDriven       ->Sumw2();
    isTrackerDriven    ->Sumw2();
   
    isEScaleCorr       ->Sumw2(); 
    isMomentumCorr     ->Sumw2(); 
    nClus              ->Sumw2(); 
    classification     ->Sumw2(); 
    
    

    // Extra Isolation variables 
    
   
    EcalRecHitIsoDr04       ->Sumw2();
    HcalDepth1TowerSumEtDr04->Sumw2();
    HcalDepth2TowerSumEtDr04->Sumw2();
    TrackIsolationDr04      ->Sumw2();
    EcalRecHitIsoDr03       ->Sumw2();
    HcalTowerSumEtDr03      ->Sumw2();
    HcalDepth1TowerSumEtDr03->Sumw2();
    HcalDepth2TowerSumEtDr03->Sumw2();
    TrackIsolationDr03      ->Sumw2();
    
    
    IsolationCombinedEndCap03     ->Sumw2();  
    IsolationCombinedBarrel03     ->Sumw2();  
    
 // Id variables
    
    eidRobustLoose       ->Sumw2(); 
    eidRobustTight       ->Sumw2();
    eidLoose             ->Sumw2();
    eidTight             ->Sumw2();
    
 // Extra shape variables
    
    E15                    ->Sumw2();                 
    E25Max                 ->Sumw2(); 
    E55                    ->Sumw2();
    CovEtaEta              ->Sumw2();      
    CoviEtaiEta            ->Sumw2();     
    HadronicOverEm         ->Sumw2();  
    HcalDepth1OverEcal     ->Sumw2();    
    HcalDepth2OverEcal     ->Sumw2();
    
    // conversion variables
    
    dist_conv   ->Sumw2();
    dcot_conv ->Sumw2();
    d0 ->Sumw2();
  
//  ->Sumw2();
  
}

void ElectronPlots::fill(vector<MyElectron>& Electroncoll, double weight, int vtxId ){

    vector<MyElectron*> *elec = new vector<MyElectron*>();
    for(vector<MyElectron>::iterator it_ele = Electroncoll.begin() ; it_ele != Electroncoll.end() ; ++it_ele){
        (*elec).push_back(&*it_ele);
     	}
    fill(*elec,weight,vtxId);
 //   delete elec;
}

void ElectronPlots::fill(MyElectron& electron, double weight, int vtxId ){

    vector<MyElectron*> *elec = new vector<MyElectron*>();
    (*elec).push_back(&electron);
    fill(*elec,weight,vtxId);
 
}



void ElectronPlots::fill(vector<MyElectron*>& Electroncoll, double weight, int vtxId ){
   
   for(vector<MyElectron*>::iterator it_ele = Electroncoll.begin();it_ele != Electroncoll.end();++it_ele){
   
         pt->Fill((*it_ele)->pt,weight); 
         eta->Fill((*it_ele)->eta,weight); 
         phi->Fill((*it_ele)->phi,weight); 
    
    // Basic properties            
        eSupClusOverP      ->Fill((*it_ele)->eSupClusOverP,weight);
        eSeedClusOverPout  ->Fill((*it_ele)->eSeedClusOverPout,weight); 
        PIn        ->Fill((*it_ele)->PIn,weight);
        POut        ->Fill((*it_ele)->POut,weight);
        dEtaSupClusTrVtx   ->Fill((*it_ele)->dEtaSupClusTrVtx,weight); 
        dEtaSeedClusTrCalo ->Fill((*it_ele)->dEtaSeedClusTrCalo,weight); 
        dPhiSupClusTrVtx   ->Fill((*it_ele)->dPhiSupClusTrVtx,weight); 
        dPhiSeedClusTrCalo ->Fill((*it_ele)->dPhiSeedClusTrCalo,weight); 
        fbrem              ->Fill((*it_ele)->fbrem,weight); 
    
          isBarrel           ->Fill((*it_ele)->isBarrel,weight); 
          isEndCap           ->Fill((*it_ele)->isEndCap,weight);
    
          isEcalDriven       ->Fill((*it_ele)->isEcalDriven,weight);
          isTrackerDriven    ->Fill((*it_ele)->isTrackerDriven,weight);
   
          isEScaleCorr       ->Fill((*it_ele)->isEScaleCorr,weight); 
          isMomentumCorr     ->Fill((*it_ele)->isMomentumCorr,weight); 
          nClus              ->Fill((*it_ele)->nClus,weight); 
          classification     ->Fill((*it_ele)->classification,weight); 
    
    
    
    // Extra Isolation variables 
    
   
        EcalRecHitIsoDr04       ->Fill((*it_ele)->EcalRecHitIsoDr04,weight);
        HcalDepth1TowerSumEtDr04->Fill((*it_ele)->HcalDepth1TowerSumEtDr04,weight);
        HcalDepth2TowerSumEtDr04->Fill((*it_ele)->HcalDepth2TowerSumEtDr04,weight);
        TrackIsolationDr04      ->Fill((*it_ele)->TrackIsolationDr04,weight);
        EcalRecHitIsoDr03       ->Fill((*it_ele)->EcalRecHitIsoDr03/(*it_ele)->pt,weight);
        HcalTowerSumEtDr03      ->Fill((*it_ele)->HcalTowerSumEtDr03/(*it_ele)->pt,weight);
        HcalDepth1TowerSumEtDr03->Fill((*it_ele)->HcalDepth1TowerSumEtDr03,weight);
        HcalDepth2TowerSumEtDr03->Fill((*it_ele)->HcalDepth2TowerSumEtDr03,weight);
        TrackIsolationDr03      ->Fill((*it_ele)->TrackIsolationDr03/(*it_ele)->pt,weight);
    
    
        IsolationCombinedEndCap03     ->Fill( ((*it_ele)->TrackIsolationDr03+(*it_ele)->EcalRecHitIsoDr03+(*it_ele)->HcalTowerSumEtDr03)/(*it_ele)->pt,weight);  
        IsolationCombinedBarrel03     ->Fill( ((*it_ele)->TrackIsolationDr03+max(Double_t(0),(*it_ele)->EcalRecHitIsoDr03-1.0)+(*it_ele)->HcalTowerSumEtDr03)/(*it_ele)->pt,weight);  
       
  
    // Id variables
    
        eidRobustLoose       ->Fill((*it_ele)->eidRobustLoose,weight); 
        eidRobustTight       ->Fill((*it_ele)->eidRobustTight,weight);
        eidLoose             ->Fill((*it_ele)->eidLoose,weight);
        eidTight             ->Fill((*it_ele)->eidTight,weight);
    
    // Extra shape variables
    
     E15                    ->Fill((*it_ele)->E15,weight);                 
     E25Max                 ->Fill((*it_ele)->E25Max,weight); 
     E55                    ->Fill((*it_ele)->E55,weight);
     CovEtaEta              ->Fill((*it_ele)->CovEtaEta,weight);      
     CoviEtaiEta            ->Fill((*it_ele)->CoviEtaiEta,weight);     
     HadronicOverEm         ->Fill((*it_ele)->HadronicOverEm,weight);  
     HcalDepth1OverEcal     ->Fill((*it_ele)->HcalDepth1OverEcal,weight);    
     HcalDepth2OverEcal     ->Fill((*it_ele)->HcalDepth2OverEcal,weight);
   
    // conversion variables
    
     dist_conv   ->Fill((*it_ele)->dist_conv,weight);
     dcot_conv ->Fill((*it_ele)->dcot_conv,weight);  
   
    //vertex
    
    
     if(vtxId>=0) d0 ->Fill((*it_ele)->GsfTrack.vtxdxy.at(vtxId),weight);
  
   }
  
//  ->Fill((*it_ele)->,weight);
  
  }  



void ElectronPlots::write(){
  
  gDirectory->mkdir("ElectronPlots_"+Electroncoll);
  gDirectory->cd("ElectronPlots_"+Electroncoll);
  
      pt->Write(); 
     eta->Write(); 
     phi->Write(); 
    
    // Basic properties            
        eSupClusOverP      ->Write();
        eSeedClusOverPout  ->Write(); 
        PIn        ->Write();
        POut        ->Write();
        dEtaSupClusTrVtx   ->Write(); 
        dEtaSeedClusTrCalo ->Write(); 
        dPhiSupClusTrVtx   ->Write(); 
        dPhiSeedClusTrCalo ->Write(); 
        fbrem              ->Write(); 
    
          isBarrel           ->Write(); 
          isEndCap           ->Write();
    
          isEcalDriven       ->Write();
          isTrackerDriven    ->Write();
   
          isEScaleCorr       ->Write(); 
          isMomentumCorr     ->Write(); 
          nClus              ->Write(); 
          classification     ->Write(); 
    
    

    // Extra Isolation variables 
    
   
        EcalRecHitIsoDr04       ->Write();
        HcalDepth1TowerSumEtDr04->Write();
        HcalDepth2TowerSumEtDr04->Write();
        TrackIsolationDr04      ->Write();
        EcalRecHitIsoDr03       ->Write();
        HcalTowerSumEtDr03      ->Write();
        HcalDepth1TowerSumEtDr03->Write();
        HcalDepth2TowerSumEtDr03->Write();
        TrackIsolationDr03      ->Write();
    
    
        IsolationCombinedEndCap03     ->Write();  
        IsolationCombinedBarrel03     ->Write();  
        
    
    // Id variables
    
        eidRobustLoose       ->Write(); 
        eidRobustTight       ->Write();
        eidLoose             ->Write();
        eidTight             ->Write();
    
    // Extra shape variables
    
     E15                    ->Write();                 
     E25Max                 ->Write(); 
     E55                    ->Write();
     CovEtaEta              ->Write();      
     CoviEtaiEta            ->Write();     
     HadronicOverEm         ->Write();  
     HcalDepth1OverEcal     ->Write();    
     HcalDepth2OverEcal     ->Write();
    
    // conversion variables
    
     dist_conv   ->Write();
     dcot_conv ->Write();
  
     d0->Write();
 // ->Write()->Write();
  

  gDirectory->cd("../");
}



