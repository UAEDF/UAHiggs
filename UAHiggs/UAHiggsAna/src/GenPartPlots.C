#include "../include/GenPartPlots.h"
#include "../include/MyGenPart.h"




ClassImp(GenPartPlots)

GenPartPlots::GenPartPlots(){
  genpartcoll = "none";
  this->init();
}

GenPartPlots::GenPartPlots(TString collname){
  genpartcoll = collname;
  this->init();
}




GenPartPlots::~GenPartPlots(){ }


void GenPartPlots::init(){
  etamin    = new TH1F("etamin_"+genpartcoll,"etamin_"+genpartcoll+";etamin;#events",40,-10,10);
  etamax    = new TH1F("etamax_"+genpartcoll,"etamax_"+genpartcoll+";etamax;#events",40,-10,10);
  ptmax     = new TH1F("ptmax_"+genpartcoll, "ptmax_"+genpartcoll+";ptmax;#events",50,0,100);
  ptmin     = new TH1F("ptmin_"+genpartcoll, "ptmin_"+genpartcoll+";ptmin;#events",50,0,100);
  phimax    = new TH1F("phimax_"+genpartcoll, "phimax_"+genpartcoll+";phimax;#events",30,-TMath::Pi(),TMath::Pi());
  phimin    = new TH1F("phimin_"+genpartcoll, "phimin_"+genpartcoll+";phimin;#events",30,-TMath::Pi(),TMath::Pi());
   
  etamin->Sumw2();
  etamax->Sumw2();
  ptmin ->Sumw2();
  ptmax ->Sumw2();
  phimin->Sumw2();
  phimax->Sumw2();

}

void GenPartPlots::fill(vector<MyGenPart>& genpartcoll, double weight){
  vector<MyGenPart> *GenLeptonsPlus  =  new vector<MyGenPart>;
  vector<MyGenPart> *GenLeptonsMinus =  new vector<MyGenPart> ;
  vector<MyGenPart> *maxpair         =  new vector<MyGenPart> ;
   
 
  
  
  
   for(vector<MyGenPart>::iterator it_gen = genpartcoll.begin();it_gen != genpartcoll.end();++it_gen){
  //   cout<<genpartcoll.size()<<endl;
     if((*it_gen).charge==1){
   //   cout<<(*it_gen).charge<<endl;
      GenLeptonsPlus->push_back(*it_gen);}
     else{
   //    cout<<(*it_gen).charge<<endl;
       GenLeptonsMinus->push_back(*it_gen);}
     }
  
  if(GenLeptonsPlus->size()==0 || GenLeptonsMinus->size()==0)return;
  
  vector<MyGenPart>::iterator maxleptonplus  = max_element(GenLeptonsPlus->begin(),GenLeptonsPlus->end());
  maxpair->push_back(*maxleptonplus);
//  cout<<(*maxleptonplus).pt<<endl;
  vector<MyGenPart>::iterator maxleptonminus = max_element(GenLeptonsMinus->begin(),GenLeptonsMinus->end());
  maxpair->push_back(*maxleptonminus);
  vector<MyGenPart>::iterator leptonMax = max_element(maxpair->begin(),maxpair->end());
//  cout<<(*leptonMax).pt<<"   "<<(*leptonMax).eta<<endl;
  vector<MyGenPart>::iterator leptonMin = min_element(maxpair->begin(),maxpair->end());
//  cout<<(*leptonMin).pt<<"   "<<(*leptonMin).eta<<endl;
  
  
  
  etamin->Fill(leptonMin->eta,weight);
  etamax->Fill(leptonMax->eta,weight);
  ptmin ->Fill(leptonMin->pt,weight);
  ptmax ->Fill(leptonMax->pt,weight);
  phimin->Fill(leptonMin->phi,weight);
  phimax->Fill(leptonMax->phi,weight);
  
  delete GenLeptonsPlus;
  delete GenLeptonsMinus;
  delete maxpair;
  }  



void GenPartPlots::write(){
  
  gDirectory->mkdir("GenPartPlots_"+genpartcoll);
  gDirectory->cd("GenPartPlots_"+genpartcoll);
  
  ptmin->Write();
  ptmax->Write();
  etamin->Write();
  etamax->Write();
  phimin->Write();
  phimax->Write();

  gDirectory->cd("../");
}



