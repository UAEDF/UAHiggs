#include "../include/GenLeptonPairPlots.h"
#include "../include/MyGenPart.h"
#include "../include/GenLeptonPair.h"



//ClassImp(LeptonPairPlots)

GenLeptonPairPlots::GenLeptonPairPlots(){
  GenLeptonPaircoll = "none";
  this->init();
}

GenLeptonPairPlots::GenLeptonPairPlots(TString collname){
  GenLeptonPaircoll = collname;
  this->init();
}




GenLeptonPairPlots::~GenLeptonPairPlots(){ }


void GenLeptonPairPlots::init(){
   
    phimin = new TH1F("phimin_"+GenLeptonPaircoll,"phimin_"+GenLeptonPaircoll+";phimin;#events",30,-TMath::Pi(),TMath::Pi()); 
    phimax = new TH1F("phimax_"+GenLeptonPaircoll,"phimax_"+GenLeptonPaircoll+";phimax;#events",30,-TMath::Pi(),TMath::Pi()); 
    etamin = new TH1F("etamin_"+GenLeptonPaircoll,"etamin_"+GenLeptonPaircoll+";etamin;#events",40,-3,3); 
    etamax = new TH1F("etamax_"+GenLeptonPaircoll,"etamax_"+GenLeptonPaircoll+";etamax;#events",40,-3,3); 
    ptmin = new TH1F("ptmin_"+GenLeptonPaircoll,"ptmin_"+GenLeptonPaircoll+";ptmin;#events",100,0,200); 
    ptmax = new TH1F("ptmax_"+GenLeptonPaircoll,"ptmax_"+GenLeptonPaircoll+";ptmax;#events",100,0,200); 
    dPhi = new TH1F("dPhi_"+GenLeptonPaircoll,"dPhi_"+GenLeptonPaircoll+";dPhi;#events",30,0,TMath::Pi()); 
    dEta = new TH1F("dEta_"+GenLeptonPaircoll,"dEta_"+GenLeptonPaircoll+";dEta;#events",40,0,4); 
    pMet = new TH1F("pMet_"+GenLeptonPaircoll,"pMet_"+GenLeptonPaircoll+";pMet;#events",100,0,200); 
    Met = new TH1F("Met_"+GenLeptonPaircoll,"Met_"+GenLeptonPaircoll+";Met;#events",100,0,200); 
    mll = new TH1F("mll_"+GenLeptonPaircoll,"mll_"+GenLeptonPaircoll+";mll;#events",100,0,200); 
    pt = new TH1F("pt_"+GenLeptonPaircoll,"pt_"+GenLeptonPaircoll+";pt;#events",100,0,200); 
    eta = new TH1F("eta_"+GenLeptonPaircoll,"eta_"+GenLeptonPaircoll+";eta;#events",40,-3,3); 
    phi = new TH1F("phi_"+GenLeptonPaircoll,"phi_"+GenLeptonPaircoll+";phi;#events",30,-TMath::Pi(),TMath::Pi()); 
     
    isPrimary_ee = new TH1F("isPrimary_ee_"+GenLeptonPaircoll,"isPrimary_ee_"+GenLeptonPaircoll+";isPrimary_ee;#events",2,0,2); 
    isPrimary_mm = new TH1F("isPrimary_mm_"+GenLeptonPaircoll,"isPrimary_mm_"+GenLeptonPaircoll+";isPrimary_mm;#events",2,0,2); 
    isPrimary_tt = new TH1F("isPrimary_tt_"+GenLeptonPaircoll,"isPrimary_tt_"+GenLeptonPaircoll+";isPrimary_tt;#events",2,0,2); 
    isPrimary_em = new TH1F("isPrimary_em_"+GenLeptonPaircoll,"isPrimary_em_"+GenLeptonPaircoll+";isPrimary_em;#events",2,0,2); 
    isPrimary_et = new TH1F("isPrimary_et_"+GenLeptonPaircoll,"isPrimary_et_"+GenLeptonPaircoll+";isPrimary_et;#events",2,0,2); 
    isPrimary_mt = new TH1F("isPrimary_tm_"+GenLeptonPaircoll,"isPrimary_mt_"+GenLeptonPaircoll+";isPrimary_tm;#events",2,0,2); 
    isPrimary_nl = new TH1F("isPrimary_nl_"+GenLeptonPaircoll,"isPrimary_nl_"+GenLeptonPaircoll+";isPrimary_nl;#events",2,0,2); 
    
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
    
    isPrimary_ee ->Sumw2();
    isPrimary_mm ->Sumw2();
    isPrimary_tt ->Sumw2();
    isPrimary_em ->Sumw2();
    isPrimary_et ->Sumw2();
    isPrimary_mt ->Sumw2();
    isPrimary_nl ->Sumw2();



}



void GenLeptonPairPlots::fill(GenLeptonPair& genLeptonPair, double met , double metphi ,double weight){

    vector<GenLeptonPair*> *pair = new vector<GenLeptonPair*>;
  //  cout << "LeptonPai pointor = " <<  &genLeptonPair << endl;
    (*pair).push_back(&genLeptonPair);
    fill(*pair,met,metphi,weight);
 
}


void GenLeptonPairPlots::fill(vector<GenLeptonPair*>& GenLeptonPaircoll, double met , double metphi , double weight){
   
 //  cout << "GenLeptonPair Size = " << GenLeptonPaircoll.size() << endl;
   
   for(vector<GenLeptonPair*>::iterator itp = GenLeptonPaircoll.begin();itp != GenLeptonPaircoll.end();++itp){
   
 //    cout << "Hello Pair" << endl;
   
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
    
    isPrimary_ee  -> Fill((*itp)->isPrimary_ee,weight);
    isPrimary_mm  -> Fill((*itp)->isPrimary_mm,weight);
    isPrimary_tt  -> Fill((*itp)->isPrimary_tt,weight);
    isPrimary_em  -> Fill((*itp)->isPrimary_em,weight);
    isPrimary_et  -> Fill((*itp)->isPrimary_et,weight);
    isPrimary_mt  -> Fill((*itp)->isPrimary_mt,weight);
    isPrimary_nl  -> Fill((*itp)->isPrimary_nl,weight);
    
    
   }
  }  



void GenLeptonPairPlots::write(){
  
  gDirectory->mkdir("GenLeptonPairPlots_"+GenLeptonPaircoll);
  gDirectory->cd("GenLeptonPairPlots_"+GenLeptonPaircoll);
  
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
    
    isPrimary_ee ->Write();
    isPrimary_mm ->Write();
    isPrimary_tt ->Write();
    isPrimary_em ->Write();
    isPrimary_et ->Write();
    isPrimary_mt ->Write();
    isPrimary_nl ->Write();

   
   
  gDirectory->cd("../");
}



