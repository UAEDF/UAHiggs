#include "../include/MuonPlots.h"
#include "../include/MyMuon.h"




//ClassImp(MuonPlots)

MuonPlots::MuonPlots(){
  Muoncoll = "none";
  this->init();
}

MuonPlots::MuonPlots(TString collname){
  Muoncoll = collname;
  this->init();
}




MuonPlots::~MuonPlots(){ }


void MuonPlots::init(){
 
// Basic Properties    
   
       pt = new TH1F("pt_"+Muoncoll,"pt_"+Muoncoll+";pt;#events",40,0,200); 
       eta = new TH1F("eta_"+Muoncoll,"eta_"+Muoncoll+";eta;#events",40,-10,10); 
       phi = new TH1F("phi_"+Muoncoll,"phi_"+Muoncoll+";phi;#events",30,-TMath::Pi(),TMath::Pi()); 
       d0   = new  TH1F("d0_"+Muoncoll,"d0_"+Muoncoll+";d0;#events",100,0,0.1);
    
   
    // Isolation properties            
       
       isoR03sumPt       = new TH1F("isoR03sumPt_"+Muoncoll,"isoR03sumPt_"+Muoncoll+";isoR03sumPt;#events",100,0,50);
       isoR03emEt        = new TH1F("isoR03emEt_"+Muoncoll,"isoR03emEt_"+Muoncoll+";isoR03emEt;#events",100,0,50); 
       isoR03hadEt       = new TH1F("isoR03hadEt_"+Muoncoll,"isoR03hadEt_"+Muoncoll+";isoR03hadEt;#events",100,0,10);
       isoR03hoEt        = new TH1F("isoR03hoEt_"+Muoncoll,"isoR03hoEt_"+Muoncoll+";isoR03hoEt;#events",100,0,0.05);
       isoR03nTracks     = new TH1F("isoR03nTracks_"+Muoncoll,"isoR03nTracks_"+Muoncoll+";isoR03nTracks;#events",20,0,20); 
       isoR03nJets       = new TH1F("isoR03nJets_"+Muoncoll,"isoR03nJets_"+Muoncoll+";isoR03nJets;#events",10,0,10); 
       
       isoR05sumPt       = new TH1F("isoR05sumPt_"+Muoncoll,"isoR05sumPt_"+Muoncoll+";isoR05sumPt;#events",100,0,50);
       isoR05emEt        = new TH1F("isoR05emEt_"+Muoncoll,"isoR05emEt_"+Muoncoll+";isoR05emEt;#events",100,0,50); 
       isoR05hadEt       = new TH1F("isoR05hadEt_"+Muoncoll,"isoR05hadEt_"+Muoncoll+";isoR05hadEt;#events",100,0,10);
       isoR05hoEt        = new TH1F("isoR05hoEt_"+Muoncoll,"isoR05hoEt_"+Muoncoll+";isoR05hoEt;#events",100,0,05);
       isoR05nTracks     = new TH1F("isoR05nTracks_"+Muoncoll,"isoR05nTracks_"+Muoncoll+";isoR05nTracks;#events",20,0,20); 
       isoR05nJets       = new TH1F("isoR05nJets_"+Muoncoll,"isoR05nJets_"+Muoncoll+";isoR05nJets;#events",10,0,10); 
       
       isolationCombined03 = new TH1F("isolationCombined03"+Muoncoll,"isolationCombined03"+Muoncoll+";isolationCombined03;#events",100,0,0.5); 
       
       calEnergyEm     = new TH1F("calEnergyEm_"+Muoncoll,"calEnergyEm_"+Muoncoll+";calEnergyEm;#events",100,-1,10); 
       calEnergyHad    = new TH1F("calEnergyHad_"+Muoncoll,"calEnergyHad_"+Muoncoll+";calEnergyHad;#events",100,0,30); 
       calEnergyHo     = new TH1F("calEnergyHo_"+Muoncoll,"calEnergyHo_"+Muoncoll+";calEnergyHo;#events",100,-1,5); 
       calEnergyEmS9     = new TH1F("calEnergyEmS9_"+Muoncoll,"calEnergyEmS9_"+Muoncoll+";calEnergyEmS9;#events",100,-1,10); 
       calEnergyHadS9    = new TH1F("calEnergyHadS9_"+Muoncoll,"calEnergyHadS9_"+Muoncoll+";calEnergyHadS9;#events",100,0,30); 
       calEnergyHoS9     = new TH1F("calEnergyHoS9_"+Muoncoll,"calEnergyHoS9_"+Muoncoll+";calEnergyHoS9;#events",100,-1,5); 
        
       // Muon Id
    
       
       IsGlobalMuon       = new TH1F("IsGlobalMuon_"+Muoncoll,"IsGlobalMuon_"+Muoncoll+";IsGlobalMuon;#events",2,0,2);
       IsTrackerMuon      = new TH1F("IsTrackerMuon_"+Muoncoll,"IsTrackerMuon_"+Muoncoll+";IsTrackerMuon;#events",2,0,2);
       IsStandaloneMuon   = new TH1F("IsStandaloneMuon_"+Muoncoll,"IsStandaloneMuon_"+Muoncoll+";IsStandaloneMuon;#events",2,0,2);
       IsCaloMuon         = new TH1F("IsCaloMuon_"+Muoncoll,"IsCaloMuon_"+Muoncoll+";IsCaloMuon;#events",2,0,2);
     
       AllGlobalMuons                           = new TH1F("AllGlobalMuons_"+Muoncoll,"AllGlobalMuons_"+Muoncoll+";AllGlobalMuons;#events",2,0,2);
       AllStandAloneMuons                       = new TH1F("AllStandAloneMuons_"+Muoncoll,"AllStandAloneMuons_"+Muoncoll+";AllStandAloneMuons;#events",2,0,2);
       AllTrackerMuons                          = new TH1F("AllTrackerMuons_"+Muoncoll,"AllTrackerMuons_"+Muoncoll+";AllTrackerMuons;#events",2,0,2);
       TrackerMuonArbitrated                    = new TH1F("TrackerMuonArbitrated_"+Muoncoll,"TrackerMuonArbitrated_"+Muoncoll+";TrackerMuonArbitrated;#events",2,0,2);
       AllArbitrated                            = new TH1F("AllArbitrated_"+Muoncoll,"AllArbitrated_"+Muoncoll+";AllArbitrated;#events",2,0,2);
       GlobalMuonPromptTight                    = new TH1F("GlobalMuonPromptTight_"+Muoncoll,"GlobalMuonPromptTight_"+Muoncoll+";GlobalMuonPromptTight;#events",2,0,2);
       TMLastStationLoose                       = new TH1F("TMLastStationLoose_"+Muoncoll,"TMLastStationLoose_"+Muoncoll+";TMLastStationLoose;#events",2,0,2);
       TMLastStationTight                       = new TH1F("TMLastStationTight_"+Muoncoll,"TMLastStationTight_"+Muoncoll+";TMLastStationTight;#events",2,0,2);
       TM2DCompatibilityLoose                   = new TH1F("TM2DCompatibilityLoose_"+Muoncoll,"TM2DCompatibilityLoose_"+Muoncoll+";TM2DCompatibilityLoose;#events",2,0,2);
       TM2DCompatibilityTight                   = new TH1F("TM2DCompatibilityTight_"+Muoncoll,"TM2DCompatibilityTight_"+Muoncoll+";TM2DCompatibilityTight;#events",2,0,2);
       TMOneStationLoose                        = new TH1F("TMOneStationLoose_"+Muoncoll,"TMOneStationLoose_"+Muoncoll+";TMOneStationLoose;#events",2,0,2);
       TMOneStationTight                        = new TH1F("TMOneStationTight_"+Muoncoll,"TMOneStationTight_"+Muoncoll+";TMOneStationTight;#events",2,0,2);
       TMLastStationOptimizedLowPtLoose         = new TH1F("TMLastStationOptimizedLowPtLoose_"+Muoncoll,"TMLastStationOptimizedLowPtLoose_"+Muoncoll+";TMLastStationOptimizedLowPtLoose;#events",2,0,2);
       TMLastStationOptimizedLowPtTight         = new TH1F("TMLastStationOptimizedLowPtTight_"+Muoncoll,"TMLastStationOptimizedLowPtTight_"+Muoncoll+";TMLastStationOptimizedLowPtTight;#events",2,0,2);
       GMTkChiCompatibility                     = new TH1F("GMTkChiCompatibility_"+Muoncoll,"GMTkChiCompatibility_"+Muoncoll+";GMTkChiCompatibility;#events",2,0,2);
       GMStaChiCompatibility                    = new TH1F("GMStaChiCompatibility_"+Muoncoll,"GMStaChiCompatibility_"+Muoncoll+";GMStaChiCompatibility;#events",2,0,2);
       GMTkKinkTight                            = new TH1F("GMTkKinkTight_"+Muoncoll,"GMTkKinkTight_"+Muoncoll+";GMTkKinkTight;#events",2,0,2);
       TMLastStationAngLoose                    = new TH1F("TMLastStationAngLoose_"+Muoncoll,"TMLastStationAngLoose_"+Muoncoll+";TMLastStationAngLoose;#events",2,0,2);
       TMLastStationAngTight                    = new TH1F("TMLastStationAngTight_"+Muoncoll,"TMLastStationAngTight_"+Muoncoll+";TMLastStationAngTight;#events",2,0,2);
       TMOneStationAngLoose                     = new TH1F("TMOneStationAngLoose_"+Muoncoll,"TMOneStationAngLoose_"+Muoncoll+";TMOneStationAngLoose;#events",2,0,2);
       TMOneStationAngTight                     = new TH1F("TMOneStationAngTight_"+Muoncoll,"TMOneStationAngTight_"+Muoncoll+";TMOneStationAngTight;#events",2,0,2);
       TMLastStationOptimizedBarrelLowPtLoose   = new TH1F("TMLastStationOptimizedBarrelLowPtLoose_"+Muoncoll,"TMLastStationOptimizedBarrelLowPtLoose_"+Muoncoll+";TMLastStationOptimizedBarrelLowPtLoose;#events",2,0,2);
       TMLastStationOptimizedBarrelLowPtTight   = new TH1F("TMLastStationOptimizedBarrelLowPtTight_"+Muoncoll,"TMLastStationOptimizedBarrelLowPtTight_"+Muoncoll+";TMLastStationOptimizedBarrelLowPtTight;#events",2,0,2);
       
       
       InnerTrackPixelHits= new TH1F("nInnerTrackPixelHits_"+Muoncoll,"nInnerTrackPixelHits_"+Muoncoll+";nInnerTrackPixelHits;#events",10,0,10);
       InnerTrackStripHits= new TH1F("nInnerTrackStripHits_"+Muoncoll,"nInnerTrackStripHits_"+Muoncoll+";nInnerTrackStripHits;#events",20,0,20); 
       InnerTrackchi2= new TH1F("InnerTrackchi2_"+Muoncoll,"InnerTrackchi2_"+Muoncoll+";InnerTrackchi2;#events",100,0,10);
       InnerTrackPt= new TH1F("InnerTrackPt_"+Muoncoll,"InnerTrackPt_"+Muoncoll+";InnerTrackPt;#events",40,0,200);
   
       OuterTrackMuonHits= new TH1F("nOuterTrackMuonHits_"+Muoncoll,"nOuterTrackMuonHits_"+Muoncoll+";nOuterTrackMuonHits;#events",20,0,20);
       OuterTrackchi2= new TH1F("OuterTrackchi2_"+Muoncoll,"OuterTrackchi2_"+Muoncoll+";OuterTrackchi2;#events",100,0,10);
       OuterTrackPt= new TH1F("OuterTrackPt_"+Muoncoll,"OuterTrackPt_"+Muoncoll+";OuterTrackPt;#events",40,0,200);
     
       GlobalTrackPixelHits = new TH1F("nGlobalTrackPixelHits_"+Muoncoll,"nGlobalTrackPixelHits_"+Muoncoll+";nGlobalTrackPixelHits;#events",10,0,10);
       GlobalTrackStripHits = new TH1F("nGlobalTrackStripHits_"+Muoncoll,"nGlobalTrackStripHits_"+Muoncoll+";nGlobalTrackStripHits;#events",20,0,20); 
       GlobalTrackMuonHits  = new TH1F("nGlobalTrackMuonHits_"+Muoncoll,"nGlobalTrackMuonHits_"+Muoncoll+";nGlobalTrackMuonHits;#events",20,0,20);  
       GlobalTrackTotalHits = new TH1F("nGlobalTrackTotalHits_"+Muoncoll,"nGlobalTrackTotalHits_"+Muoncoll+";nGlobalTrackTotalHits;#events",600,0,60);  
       GlobalTrackchi2      = new TH1F("GlobalTrackchi2_"+Muoncoll,"GlobalTrackchi2_"+Muoncoll+";GlobalTrackchi2;#events",100,0,10);
       GlobalTrackPt        = new TH1F("GlobalTrackPt_"+Muoncoll,"GlobalTrackPt_"+Muoncoll+";GlobalTrackPt;#events",40,0,200);
    
    pt->Sumw2(); 
    eta->Sumw2(); 
    phi->Sumw2(); 
    isoR03sumPt      ->Sumw2();
    isoR03emEt       ->Sumw2(); 
    isoR03hadEt      ->Sumw2();
    isoR03hoEt       ->Sumw2();
    isoR03nTracks    ->Sumw2(); 
    isoR03nJets      ->Sumw2(); 
    isoR05sumPt      ->Sumw2();
    isoR05emEt       ->Sumw2(); 
    isoR05hadEt      ->Sumw2();
    isoR05hoEt       ->Sumw2();
    isoR05nTracks    ->Sumw2(); 
    isoR05nJets      ->Sumw2(); 
    isolationCombined03->Sumw2();
    calEnergyEm     ->Sumw2();
    calEnergyHad    ->Sumw2();
    calEnergyHo     ->Sumw2();
    calEnergyEmS9   ->Sumw2();
    calEnergyHadS9  ->Sumw2();
    calEnergyHoS9   ->Sumw2();
    IsGlobalMuon       ->Sumw2();
    IsTrackerMuon      ->Sumw2();
    IsStandaloneMuon   ->Sumw2();
    IsCaloMuon         ->Sumw2();
    
    
    
    
    
    
    
    
    
    // Muon Id
    
     
     AllGlobalMuons                           ->Sumw2();
     AllStandAloneMuons                       ->Sumw2();
     AllTrackerMuons                          ->Sumw2();
     TrackerMuonArbitrated                    ->Sumw2();
     AllArbitrated                            ->Sumw2();
     GlobalMuonPromptTight                    ->Sumw2();
     TMLastStationLoose                       ->Sumw2();
     TMLastStationTight                       ->Sumw2();
     TM2DCompatibilityLoose                   ->Sumw2();
     TM2DCompatibilityTight                   ->Sumw2();
     TMOneStationLoose                        ->Sumw2();
     TMOneStationTight                        ->Sumw2();
     TMLastStationOptimizedLowPtLoose         ->Sumw2();
     TMLastStationOptimizedLowPtTight         ->Sumw2();
     GMTkChiCompatibility                     ->Sumw2();
     GMStaChiCompatibility                    ->Sumw2();
     GMTkKinkTight                            ->Sumw2();
     TMLastStationAngLoose                    ->Sumw2();
     TMLastStationAngTight                    ->Sumw2();
     TMOneStationAngLoose                     ->Sumw2();
     TMOneStationAngTight                     ->Sumw2();
     TMLastStationOptimizedBarrelLowPtLoose   ->Sumw2();
     TMLastStationOptimizedBarrelLowPtTight   ->Sumw2();
      d0->Sumw2();
  
  
     InnerTrackPixelHits    ->Sumw2();
     InnerTrackStripHits    ->Sumw2(); 
     InnerTrackchi2         ->Sumw2();
     InnerTrackPt           ->Sumw2();
   
     OuterTrackMuonHits     ->Sumw2();
     GlobalTrackStripHits   ->Sumw2(); 
     OuterTrackchi2         ->Sumw2();
     OuterTrackPt           ->Sumw2();
     
     GlobalTrackPixelHits   ->Sumw2();
     GlobalTrackStripHits   ->Sumw2(); 
     GlobalTrackMuonHits    ->Sumw2();  
     GlobalTrackTotalHits   ->Sumw2();  
     GlobalTrackchi2        ->Sumw2();
     GlobalTrackPt          ->Sumw2(); 
  
  
  
  
  
  
//  ->Sumw2();
  
}


void MuonPlots::fill(vector<MyMuon>& Muoncoll, double weight, int vtxId ){

    vector<MyMuon*> *muo = new vector<MyMuon*>();
    for(vector<MyMuon>::iterator it_mu = Muoncoll.begin() ; it_mu != Muoncoll.end() ; ++it_mu){
        (*muo).push_back(&*it_mu);
     	}
    fill(*muo,weight,vtxId);
 //   delete muo;
}

void MuonPlots::fill(MyMuon& muon, double weight, int vtxId ){

    vector<MyMuon*> *muo = new vector<MyMuon*>();
    (*muo).push_back(&muon);
    fill(*muo,weight,vtxId);
 
}

void MuonPlots::fill(vector<MyMuon*>& Muoncoll, double weight, int vtxId){
   
   for(vector<MyMuon*>::iterator it_mu = Muoncoll.begin();it_mu != Muoncoll.end();++it_mu){
   
     pt->Fill((*it_mu)->pt,weight); 
     eta->Fill((*it_mu)->eta,weight); 
     phi->Fill((*it_mu)->phi,weight); 
    
    // Basic properties            
        isoR03sumPt      ->Fill((*it_mu)->isoR03sumPt,weight);
        isoR03emEt       ->Fill((*it_mu)->isoR03emEt,weight); 
        isoR03hadEt      ->Fill((*it_mu)->isoR03hadEt,weight);
        isoR03hoEt       ->Fill((*it_mu)->isoR03hoEt,weight);
        isoR03nTracks    ->Fill((*it_mu)->isoR03nTracks,weight); 
        isoR03nJets      ->Fill((*it_mu)->isoR03nJets,weight); 
       
        isoR05sumPt      ->Fill((*it_mu)->isoR05sumPt,weight);
        isoR05emEt       ->Fill((*it_mu)->isoR05emEt,weight); 
        isoR05hadEt      ->Fill((*it_mu)->isoR05hadEt,weight);
        isoR05hoEt       ->Fill((*it_mu)->isoR05hoEt,weight);
        isoR05nTracks    ->Fill((*it_mu)->isoR05nTracks,weight); 
        isoR05nJets      ->Fill((*it_mu)->isoR05nJets,weight); 
       
        isolationCombined03 ->Fill(((*it_mu)->isoR03sumPt+(*it_mu)->isoR03emEt+(*it_mu)->isoR03hadEt)/(*it_mu)->pt,weight);
	
	
	calEnergyEm      ->Fill((*it_mu)->calEnergyEm,weight); 
        calEnergyHad     ->Fill((*it_mu)->calEnergyHad,weight); 
        calEnergyHo      ->Fill((*it_mu)->calEnergyHo,weight); 
        calEnergyEmS9    ->Fill((*it_mu)->calEnergyEmS9,weight); 
        calEnergyHadS9   ->Fill((*it_mu)->calEnergyHadS9,weight); 
        calEnergyHoS9    ->Fill((*it_mu)->calEnergyHoS9,weight); 
        
        IsGlobalMuon      ->Fill((*it_mu)->IsGlobalMuon,weight);
        IsTrackerMuon     ->Fill((*it_mu)->IsTrackerMuon,weight);
        IsStandaloneMuon  ->Fill((*it_mu)->IsStandaloneMuon,weight);
        IsCaloMuon        ->Fill((*it_mu)->IsCaloMuon,weight);
    
    // Muon Id
    
     
        AllGlobalMuons                          ->Fill((*it_mu)->AllGlobalMuons,weight);
        AllGlobalMuons                          ->Fill((*it_mu)->AllGlobalMuons,weight);
        AllTrackerMuons                         ->Fill((*it_mu)->AllTrackerMuons,weight);
        TrackerMuonArbitrated                   ->Fill((*it_mu)->TrackerMuonArbitrated,weight);
        AllArbitrated                           ->Fill((*it_mu)->AllArbitrated,weight);
        GlobalMuonPromptTight                   ->Fill((*it_mu)->GlobalMuonPromptTight,weight);
        TMLastStationLoose                      ->Fill((*it_mu)->TMLastStationLoose,weight);
        TMLastStationTight                      ->Fill((*it_mu)->TMLastStationTight,weight);
        TM2DCompatibilityLoose                  ->Fill((*it_mu)->TM2DCompatibilityLoose,weight);
        TM2DCompatibilityTight                  ->Fill((*it_mu)->TM2DCompatibilityTight,weight);
        TMOneStationLoose                       ->Fill((*it_mu)->TMOneStationLoose,weight);
        TMOneStationTight                       ->Fill((*it_mu)->TMOneStationTight,weight);
        TMLastStationOptimizedLowPtLoose        ->Fill((*it_mu)->TMLastStationOptimizedLowPtLoose,weight);
        TMLastStationOptimizedLowPtTight        ->Fill((*it_mu)->TMLastStationOptimizedLowPtTight,weight);
        GMTkChiCompatibility                    ->Fill((*it_mu)->GMTkChiCompatibility,weight);
        GMStaChiCompatibility                   ->Fill((*it_mu)->GMStaChiCompatibility,weight);
        GMTkKinkTight                           ->Fill((*it_mu)->GMTkKinkTight,weight);
        TMLastStationAngLoose                   ->Fill((*it_mu)->TMLastStationAngLoose,weight);
        TMLastStationAngTight                   ->Fill((*it_mu)->TMLastStationAngTight,weight);
        TMOneStationAngLoose                    ->Fill((*it_mu)->TMOneStationAngLoose,weight);
        TMOneStationAngTight                    ->Fill((*it_mu)->TMOneStationAngTight,weight);
        TMLastStationOptimizedBarrelLowPtLoose  ->Fill((*it_mu)->TMLastStationOptimizedBarrelLowPtLoose,weight);
        TMLastStationOptimizedBarrelLowPtTight  ->Fill((*it_mu)->TMLastStationOptimizedBarrelLowPtTight,weight);
   
        InnerTrackPixelHits    ->Fill((*it_mu)->innerTrack.numberOfValidPixelHits,weight);
        InnerTrackStripHits    ->Fill((*it_mu)->innerTrack.numberOfValidStripHits,weight); 
        InnerTrackchi2         ->Fill((*it_mu)->innerTrack.chi2n,weight);
        InnerTrackPt           ->Fill((*it_mu)->innerTrack.Part.v.Pt(),weight);
   
        OuterTrackMuonHits     ->Fill((*it_mu)->outerTrack.numberOfValidMuonHits,weight);
        OuterTrackchi2         ->Fill((*it_mu)->outerTrack.chi2n,weight);
        OuterTrackPt           ->Fill((*it_mu)->outerTrack.Part.v.Pt(),weight);
     
        GlobalTrackPixelHits   ->Fill((*it_mu)->globalTrack.numberOfValidPixelHits,weight);
        GlobalTrackStripHits   ->Fill((*it_mu)->globalTrack.numberOfValidStripHits,weight); 
        GlobalTrackMuonHits    ->Fill((*it_mu)->globalTrack.numberOfValidMuonHits,weight);  
        GlobalTrackTotalHits   ->Fill((*it_mu)->globalTrack.nhit,weight);  
        GlobalTrackchi2        ->Fill((*it_mu)->globalTrack.chi2n,weight);
        GlobalTrackPt          ->Fill((*it_mu)->globalTrack.Part.v.Pt(),weight); 
  
   
   //vertex
    
      
     if(vtxId>=0) d0 ->Fill((*it_mu)->globalTrack.vtxdxy.at(vtxId),weight);
    
   
   // ->Fill(it_mu->,weight);    
     
   }
  

  
  }  



void MuonPlots::write(){
  
  gDirectory->mkdir("MuonPlots_"+Muoncoll);
  gDirectory->cd("MuonPlots_"+Muoncoll);
  
      pt->Write(); 
     eta->Write(); 
     phi->Write(); 
    
    // Basic properties            
        isoR03sumPt      ->Write();
        isoR03emEt  ->Write(); 
        isoR03hadEt        ->Write();
        isoR03hoEt        ->Write();
        isoR03nTracks   ->Write(); 
        isoR03nJets ->Write(); 
        
	isolationCombined03->Write();
	
	
	isoR05sumPt      ->Write();
        isoR05emEt  ->Write(); 
        isoR05hadEt        ->Write();
        isoR05hoEt        ->Write();
        isoR05nTracks   ->Write(); 
        isoR05nJets ->Write(); 
            
	calEnergyEm   ->Write();
        calEnergyHad  ->Write();
    calEnergyHo   ->Write();
    calEnergyEmS9 ->Write();
    calEnergyHadS9->Write();
    calEnergyHoS9 ->Write();

    IsGlobalMuon       ->Write();
    IsTrackerMuon      ->Write();
    IsStandaloneMuon   ->Write();
    IsCaloMuon         ->Write();
    
    // Muon Id
    
     
        AllGlobalMuons                           ->Write();
        AllStandAloneMuons                       ->Write();
        AllTrackerMuons                          ->Write();
        TrackerMuonArbitrated                    ->Write();
        AllArbitrated                            ->Write();
        GlobalMuonPromptTight                    ->Write();
        TMLastStationLoose                       ->Write();
        TMLastStationTight                       ->Write();
        TM2DCompatibilityLoose                   ->Write();
        TM2DCompatibilityTight                   ->Write();
        TMOneStationLoose                        ->Write();
        TMOneStationTight                        ->Write();
        TMLastStationOptimizedLowPtLoose         ->Write();
        TMLastStationOptimizedLowPtTight         ->Write();
        GMTkChiCompatibility                     ->Write();
        GMStaChiCompatibility                    ->Write();
        GMTkKinkTight                            ->Write();
        TMLastStationAngLoose                    ->Write();
        TMLastStationAngTight                    ->Write();
        TMOneStationAngLoose                     ->Write();
        TMOneStationAngTight                     ->Write();
        TMLastStationOptimizedBarrelLowPtLoose   ->Write();
        TMLastStationOptimizedBarrelLowPtTight   ->Write();       
     
     
        InnerTrackPixelHits    ->Write();
     InnerTrackStripHits    ->Write(); 
     InnerTrackchi2         ->Write();
     InnerTrackPt           ->Write();
   
     OuterTrackMuonHits     ->Write();
     OuterTrackchi2         ->Write();
     OuterTrackPt           ->Write();
     
     GlobalTrackPixelHits   ->Write();
     GlobalTrackStripHits   ->Write(); 
     GlobalTrackMuonHits    ->Write();  
     GlobalTrackTotalHits   ->Write();  
     GlobalTrackchi2        ->Write();
     GlobalTrackPt          ->Write(); 
  
  
  
  d0->Write();
 // ->Write()->Write();
  

  gDirectory->cd("../");
}



