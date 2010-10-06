#include "../include/MuonPlots.h"
#include "../include/LeptonPairPlots.h"
#include "../include/MyMuon.h"
#include "../include/MyElectron.h"
#include "../include/LeptonPair.h"



//ClassImp(LeptonPairPlots)

LeptonPairPlots::LeptonPairPlots(){
  LeptonPaircoll = "none";
  this->init();
}

LeptonPairPlots::LeptonPairPlots(TString collname){
  LeptonPaircoll = collname;
  this->init();
}




LeptonPairPlots::~LeptonPairPlots(){ }


void LeptonPairPlots::init(){
   
    phimin = new TH1F("phimin_"+LeptonPaircoll,"phimin_"+LeptonPaircoll+";phimin;#events",30,-TMath::Pi(),TMath::Pi()); 
    phimax = new TH1F("phimax_"+LeptonPaircoll,"phimax_"+LeptonPaircoll+";phimax;#events",30,-TMath::Pi(),TMath::Pi()); 
    etamin = new TH1F("etamin_"+LeptonPaircoll,"etamin_"+LeptonPaircoll+";etamin;#events",40,-3,3); 
    etamax = new TH1F("etamax_"+LeptonPaircoll,"etamax_"+LeptonPaircoll+";etamax;#events",40,-3,3); 
    ptmin = new TH1F("ptmin_"+LeptonPaircoll,"ptmin_"+LeptonPaircoll+";ptmin;#events",100,0,200); 
    ptmax = new TH1F("ptmax_"+LeptonPaircoll,"ptmax_"+LeptonPaircoll+";ptmax;#events",100,0,200); 
    dPhi = new TH1F("dPhi_"+LeptonPaircoll,"dPhi_"+LeptonPaircoll+";dPhi;#events",30,0,TMath::Pi()); 
    dEta = new TH1F("dEta_"+LeptonPaircoll,"dEta_"+LeptonPaircoll+";dEta;#events",40,0,4); 
    pMet = new TH1F("pMet_"+LeptonPaircoll,"pMet_"+LeptonPaircoll+";pMet;#events",100,0,200); 
    Met = new TH1F("Met_"+LeptonPaircoll,"Met_"+LeptonPaircoll+";Met;#events",100,0,200); 
    mll = new TH1F("mll_"+LeptonPaircoll,"mll_"+LeptonPaircoll+";mll;#events",100,0,200); 
    pt = new TH1F("pt_"+LeptonPaircoll,"pt_"+LeptonPaircoll+";pt;#events",100,0,200); 
    eta = new TH1F("eta_"+LeptonPaircoll,"eta_"+LeptonPaircoll+";eta;#events",40,-3,3); 
    phi = new TH1F("phi_"+LeptonPaircoll,"phi_"+LeptonPaircoll+";phi;#events",30,-TMath::Pi(),TMath::Pi()); 
     


    phimin ->Sumw2();
    phimax ->Sumw2();
    etamin ->Sumw2();
    etamax ->Sumw2();
    ptmin  ->Sumw2();
    ptmax  ->Sumw2();
    dPhi   ->Sumw2();
    dEta   ->Sumw2();
    pMet   ->Sumw2();
    Met    ->Sumw2();
    mll    ->Sumw2();
    pt     ->Sumw2();
    eta    ->Sumw2();
    phi    ->Sumw2();




}



void LeptonPairPlots::fill(LeptonPair& leptonPair, double met , double metphi ,double weight){

    vector<LeptonPair*> *pair = new vector<LeptonPair*>();
    (*pair).push_back(&leptonPair);
    fill(*pair,met,metphi,weight);
 
}


void LeptonPairPlots::fill(vector<LeptonPair*>& LeptonPaircoll, double met , double metphi , double weight){
   
   for(vector<LeptonPair*>::iterator itp = LeptonPaircoll.begin();itp != LeptonPaircoll.end();++itp){
   
    phimin  ->Fill((*itp)->getPhiMin(),weight); 
    phimax  ->Fill((*itp)->getPhiMax(),weight); 
    etamin  ->Fill((*itp)->getEtaMin(),weight); 
    etamax  ->Fill((*itp)->getEtaMax(),weight); 
    ptmin   ->Fill((*itp)->getPtMin(),weight); 
    ptmax   ->Fill((*itp)->getPtMax(),weight); 
    dPhi    ->Fill((*itp)->getDeltaPhi(),weight); 
    dEta    ->Fill((*itp)->getDeltaEta(),weight); 
    pMet    ->Fill((*itp)->getProjectedMet(met,metphi),weight); 
    Met     ->Fill(met,weight); 
    mll     ->Fill((*itp)->getMll(),weight); 
    pt      ->Fill((*itp)->get4v().Pt(),weight); 
    eta     ->Fill((*itp)->get4v().Eta(),weight); 
    phi     ->Fill((*itp)->get4v().Phi(),weight); 
    
   }
  }  



void LeptonPairPlots::write(){
  
  gDirectory->mkdir("LeptonPairPlots_"+LeptonPaircoll);
  gDirectory->cd("LeptonPairPlots_"+LeptonPaircoll);
  
    phimin  ->Write(); 
    phimax  ->Write(); 
    etamin  ->Write(); 
    etamax  ->Write(); 
    ptmin   ->Write(); 
    ptmax   ->Write(); 
    dPhi    ->Write(); 
    dEta    ->Write(); 
    pMet    ->Write(); 
    Met     ->Write(); 
    mll     ->Write(); 
    pt      ->Write(); 
    eta     ->Write(); 
    phi     ->Write();  
   
  gDirectory->cd("../");
}



