
#include "../include/MyGenPart.h"
#include "../include/MyMuon.h"
#include "../include/MyElectron.h"

void PrintGenPart ( MyGenPart *gp ) {

   cout << "---------------- GenPart Print() ---- BEGIN -------------" << endl;
   cout << " Type, Pt , Eta , Phi , charge : " << gp->name << " "  << gp->pt << " " << gp->eta << " " << gp->phi << " " << gp->charge << endl ;
   cout << "---------------- GenPart Print() ---- END ---------------" << endl;

}


void PrintRecoElectron ( MyElectron *ele ) {

   cout << "---------------- Reco Electron Print() ---- BEGIN -------------" << endl;
   cout << " Pt , Eta , Phi , charge : " << ele->pt << " " << ele->eta << " " << ele->phi << " " << ele->Part.charge << endl ; 
   cout << "---------------- Reco Electron Print() ---- END ---------------" << endl;

}



void PrintRecoMuon ( MyMuon *muo , int vtxId , int iLevel = 1 ) {

   cout << "---------------- Reco Muon Print() -------- BEGIN ---------" << endl;
   cout << " Pt , Eta , Phi , charge : " << muo->pt << " " << muo->eta << " " << muo->phi << " " << muo->Part.charge << endl ; 

 if (iLevel>0) {
   cout << " --- Muon Type --- " << endl;
   cout << " Global , Tracker, StanAlone, Calo : " << muo->IsGlobalMuon << " " << muo->IsTrackerMuon << " " << muo->IsStandaloneMuon << " " << muo->IsCaloMuon << endl;
   cout << " --- Tracks --- " << endl;
   cout << " innerTrack Pt , Eta , Phi : " <<  muo->innerTrack.Part.v.Pt() << " " << muo->innerTrack.Part.v.Eta() << " " <<  muo->innerTrack.Part.v.Phi() << endl;
   cout << " outerTrack Pt , Eta , Phi : " <<  muo->outerTrack.Part.v.Pt() << " " << muo->outerTrack.Part.v.Eta() << " " <<  muo->outerTrack.Part.v.Phi() << endl;
   cout << " globalTrack Pt , Eta , Phi : " <<  muo->globalTrack.Part.v.Pt() << " " << muo->globalTrack.Part.v.Eta() << " " <<  muo->globalTrack.Part.v.Phi() << endl;
   cout << " ---- D0 ---- " << endl;

   cout << " innerTrack  D0 = " << muo->innerTrack.vtxdxy.at(vtxId) << endl;
   cout << " outerTrack  D0 = " << muo->outerTrack.vtxdxy.at(vtxId) << endl;
   cout << " globalTrack D0 = " << muo->globalTrack.vtxdxy.at(vtxId) << endl;
   cout << " --- Iso ---- " << endl;
   cout << " isoR03sumPt   = " << muo->isoR03sumPt  << endl;
   cout << " isoR03emEt    = " << muo->isoR03emEt   << endl;
   cout << " isoR03hadEt   = " << muo->isoR03hadEt  << endl;
   //cout << " isoR03hoEt    = " << muo->isoR03hoEt   << endl;
   //cout << " isoR03nTracks = " << muo->isoR03nTracks<< endl;
   //cout << " isoR03nJets   = " << muo->isoR03nJets  << endl;
   cout << " --> isoGlobal = " << ( muo->isoR03sumPt + muo->isoR03emEt + muo->isoR03hadEt ) / muo->pt << endl;
   cout << " --- Hits ---- " << endl;
   cout << " innerTrack Tracker Pix, Strip , Muon : " << muo->innerTrack.numberOfValidTkHits    << " " 
                                                       << muo->innerTrack.numberOfValidPixelHits << " " 
                                                       << muo->innerTrack.numberOfValidStripHits << " " 
                                                       << muo->innerTrack.numberOfValidMuonHits << endl ; 
   cout << " outerTrack Tracker Pix, Strip , Muon : " << muo->outerTrack.numberOfValidTkHits    << " " 
                                                       << muo->outerTrack.numberOfValidPixelHits << " " 
                                                       << muo->outerTrack.numberOfValidStripHits << " " 
                                                       << muo->outerTrack.numberOfValidMuonHits << endl ; 
   cout << " globalTrack Tracker Pix, Strip , Muon : " << muo->globalTrack.numberOfValidTkHits    << " " 
                                                       << muo->globalTrack.numberOfValidPixelHits << " " 
                                                       << muo->globalTrack.numberOfValidStripHits << " " 
                                                       << muo->globalTrack.numberOfValidMuonHits << endl ; 
   cout << " ---- Chi2 ---- " << endl;
   cout << " innerTrack   Chi2n = " << muo->innerTrack.chi2n << endl;
   cout << " outerTrack   Chi2n = " << muo->outerTrack.chi2n << endl;
   cout << " globalTrack   Chi2n = " << muo->globalTrack.chi2n << endl;
   cout << " ----  Id ----- " << endl;
   cout << " AllGlobalMuons          : " << muo->AllGlobalMuons           << endl;   
   cout << " AllStandAloneMuons      : " << muo->AllStandAloneMuons       << endl;   
   cout << " AllTrackerMuons         : " << muo->AllTrackerMuons          << endl;   
   cout << " TrackerMuonArbitrated   : " << muo->TrackerMuonArbitrated    << endl;   
   cout << " AllArbitrateds          : " << muo->AllArbitrated            << endl;   
   cout << " GlobalMuonPromptTight   : " << muo->GlobalMuonPromptTight    << endl;   
   cout << " TMLastStationLoose      : " << muo->TMLastStationLoose       << endl;   
   cout << " TMLastStationTight      : " << muo->TMLastStationTight       << endl;   
   cout << " TM2DCompatibilityLoose  : " << muo->TM2DCompatibilityLoose   << endl;   
   cout << " TM2DCompatibilityTight  : " << muo->TM2DCompatibilityTight   << endl;   
   cout << " TMOneStationLoose       : " << muo->TMOneStationLoose        << endl;   
   cout << " TMOneStationTight       : " << muo->TMOneStationTight        << endl;   
   cout << " TMLastStationOptimizedLowPtLoose      : " << muo->TMLastStationOptimizedLowPtLoose       << endl;   
   cout << " TMLastStationOptimizedLowPtTight      : " << muo->TMLastStationOptimizedLowPtTight       << endl;   
   cout << " GMTkChiCompatibility    : " << muo->GMTkChiCompatibility     << endl;   
   cout << " GMStaChiCompatibility   : " << muo->GMStaChiCompatibility    << endl;   
   cout << " GMTkKinkTight           : " << muo->GMTkKinkTight            << endl;   
   cout << " TMLastStationAngLoose   : " << muo->TMLastStationAngLoose    << endl;   
   cout << " TMLastStationAngTight   : " << muo->TMLastStationAngTight    << endl;   
   cout << " TMOneStationAngLoose    : " << muo->TMOneStationAngLoose     << endl;   
   cout << " TMOneStationAngTight    : " << muo->TMOneStationAngTight     << endl;   
   cout << " TMLastStationOptimizedBarrelLowPtLoose      : " << muo->TMLastStationOptimizedBarrelLowPtLoose       << endl;   
   cout << " TMLastStationOptimizedBarrelLowPtTight      : " << muo->TMLastStationOptimizedBarrelLowPtTight       << endl;   
 }
   cout << "---------------- Reco Muon Print() ------ END -------------"  << endl;

}

