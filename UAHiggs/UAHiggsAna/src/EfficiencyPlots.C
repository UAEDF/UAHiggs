#include "../include/EfficiencyPlots.h"
#include "../include/MyGenPart.h"
#include "../include/MyElectron.h"
#include "../include/MyMuon.h"

//ClassImp(EfficiencyPlots)

EfficiencyPlots::EfficiencyPlots(){
  Recocoll = "none";
  this->init();
}

EfficiencyPlots::EfficiencyPlots(TString collname){
  Recocoll = collname;
  this->init();
}

EfficiencyPlots::~EfficiencyPlots(){ }


void EfficiencyPlots::init(){
 
// Particle basic properties
    
    pt_gen  = new TH1F("pt_gen_"+Recocoll,"pt_gen_"+Recocoll+";pt;#events",40,0,200); 
    eta_gen = new TH1F("eta_gen_"+Recocoll,"eta_gen_"+Recocoll+";eta;#events",40,-5,5); 
    phi_gen = new TH1F("phi_gen_"+Recocoll,"phi_gen_"+Recocoll+";phi;#events",30,-TMath::Pi(),TMath::Pi()); 

    nMatched = new TH1F("nMatched_"+Recocoll,"nMatched_"+Recocoll+";nMatched;#events",10,0,10);
    dR       = new TH1F("dR_"+Recocoll,"dR_"+Recocoll+";Delta R ;#events",50,0.,0.5);
    dPt      = new TH1F("dPt_"+Recocoll,"dPt_"+Recocoll+";Delta Pt;#events",40,-10.,10.);
    deta      = new TH1F("deta_"+Recocoll,"deta_"+Recocoll+";Delta eta;#events",50,-0.5,0.5);
    dphi      = new TH1F("dphi_"+Recocoll,"dphi_"+Recocoll+";Delta phi;#events",50,-0.5,0.5);

    pt_rec  = new TH1F("pt_rec_"+Recocoll,"pt_rec_"+Recocoll+";pt;#events",40,0,200);
    eta_rec = new TH1F("eta_rec_"+Recocoll,"eta_rec_"+Recocoll+";eta;#events",40,-5,5);
    phi_rec = new TH1F("phi_rec_"+Recocoll,"phi_rec_"+Recocoll+";phi;#events",30,-TMath::Pi(),TMath::Pi());

    pt_eff  = new TH1F("pt_eff_"+Recocoll,"pt_eff_"+Recocoll+";pt;Efficiency",40,0,200);
    eta_eff = new TH1F("eta_eff_"+Recocoll,"eta_eff_"+Recocoll+";eta;Efficiency",40,-5,5);
    phi_eff = new TH1F("phi_eff_"+Recocoll,"phi_eff_"+Recocoll+";phi;Efficiency",30,-TMath::Pi(),TMath::Pi());

    pt_gen->Sumw2(); 
    eta_gen->Sumw2(); 
    phi_gen->Sumw2(); 
    
    nMatched->Sumw2(); 
    dR->Sumw2(); 
    dPt->Sumw2(); 
    deta->Sumw2(); 
    dphi->Sumw2(); 
    pt_rec->Sumw2(); 
    eta_rec->Sumw2(); 
    phi_rec->Sumw2(); 

    pt_eff->Sumw2(); 
    eta_eff->Sumw2(); 
    phi_eff->Sumw2(); 
 
}

// Overloading for: vector<MyGenPart*>&, vector<MyGenPart*>& 

void EfficiencyPlots::fill( vector<MyGenPart*>& GenColl ,  vector<MyGenPart*>&  RecColl, double weight ){

   vector<TVector3> vgen ;
   vector<TVector3> vrec ;
   for(vector<MyGenPart*>::iterator itgen = GenColl.begin() ; itgen != GenColl.end() ; ++itgen){
     TVector3 v;
     v.SetPtEtaPhi( (*itgen)->pt , (*itgen)->eta , (*itgen)->phi );
     vgen.push_back(v);
   }
   for(vector<MyGenPart*>::iterator itrec = RecColl.begin() ; itrec != RecColl.end() ; ++itrec){
     TVector3 v;
     v.SetPtEtaPhi( (*itrec)->pt , (*itrec)->eta , (*itrec)->phi );
     vrec.push_back(v);
   }
   this->fill(vgen,vrec,weight);
} 

// Overloading for: vector<MyGenPart*>&, vector<MyElectron*>&  

void EfficiencyPlots::fill( vector<MyGenPart*>& GenColl ,  vector<MyElectron*>&  RecColl, double weight ){

   vector<TVector3> vgen ;
   vector<TVector3> vrec ;
   for(vector<MyGenPart*>::iterator itgen = GenColl.begin() ; itgen != GenColl.end() ; ++itgen){
     TVector3 v;
     v.SetPtEtaPhi( (*itgen)->pt , (*itgen)->eta , (*itgen)->phi );
     vgen.push_back(v);
   }
   for(vector<MyElectron*>::iterator itrec = RecColl.begin() ; itrec != RecColl.end() ; ++itrec){
     TVector3 v;
     v.SetPtEtaPhi( (*itrec)->pt , (*itrec)->eta , (*itrec)->phi );
     vrec.push_back(v);
   }
   this->fill(vgen,vrec,weight);
} 
   
//  Overloading for: vector<MyGenPart*>&, vector<MyMuon*>&  

void EfficiencyPlots::fill( vector<MyGenPart*>& GenColl ,  vector<MyMuon*>&  RecColl, double weight ){

   vector<TVector3> vgen ;
   vector<TVector3> vrec ;
   for(vector<MyGenPart*>::iterator itgen = GenColl.begin() ; itgen != GenColl.end() ; ++itgen){
     TVector3 v;
     v.SetPtEtaPhi( (*itgen)->pt , (*itgen)->eta , (*itgen)->phi );
     vgen.push_back(v);
   }
   for(vector<MyMuon*>::iterator itrec = RecColl.begin() ; itrec != RecColl.end() ; ++itrec){
     TVector3 v;
     v.SetPtEtaPhi( (*itrec)->pt , (*itrec)->eta , (*itrec)->phi );
     vrec.push_back(v);
   }
   this->fill(vgen,vrec,weight);

} 

// REAL Filling code

void EfficiencyPlots::fill( vector<TVector3>& vgen , vector<TVector3>& vrec , double weight ){
  for(vector<TVector3>::iterator itgen = vgen.begin() ; itgen != vgen.end() ; ++itgen){
     float nMatch = 0. ;
     pt_gen ->Fill( itgen->Pt()  , weight );  
     eta_gen->Fill( itgen->Eta() , weight ); 
     phi_gen->Fill( itgen->Phi() , weight );  
     for(vector<TVector3>::iterator itrec = vrec.begin() ; itrec != vrec.end() ; ++itrec){
        if ( isMatched ( *itgen , *itrec ) ) {
           nMatch++;
           pt_rec ->Fill( itgen->Pt()  , weight );  
           eta_rec->Fill( itgen->Eta() , weight );  
           phi_rec->Fill( itgen->Phi() , weight );  
           dR->Fill ( deltaR( itgen->Eta() , itrec->Eta() , itgen->Phi() , itrec->Phi()  ) , weight ); 
           dPt->Fill( itgen->Pt() - itrec->Pt() , weight ); 
           deta->Fill( itgen->Eta() - itrec->Eta() , weight ); 
           dphi->Fill( itgen->Phi() - itrec->Phi() , weight ); 
        } 
     }
     nMatched->Fill( nMatch , weight );  
  }
}


void EfficiencyPlots::write(){
  
  gDirectory->mkdir("EfficiencyPlots_"+Recocoll);
  gDirectory->cd("EfficiencyPlots_"+Recocoll);
  
      pt_gen->Write(); 
     eta_gen->Write(); 
     phi_gen->Write(); 

     nMatched->Write();
     dR->Write();
     dPt->Write();
     deta->Write();
     dphi->Write();

      pt_rec->Write();
     eta_rec->Write();
     phi_rec->Write();

      pt_eff->Divide(pt_rec,pt_gen,1.,1.,"B");
     eta_eff->Divide(eta_rec,eta_gen,1.,1.,"B");
     phi_eff->Divide(phi_rec,phi_gen,1.,1.,"B");

      pt_eff->Write();
     eta_eff->Write();
     phi_eff->Write();
 
  gDirectory->cd("../");
}





/*  
   for(vector<MyGenPart*>::iterator itgen = GenColl.begin() ; itgen != GenColl.end() ; ++itgen){
      float nMatch = 0. ;
      pt_gen ->Fill( (*itgen)->pt  , weight );  
      eta_gen->Fill( (*itgen)->eta , weight );  
      phi_gen->Fill( (*itgen)->phi , weight );  
      for(vector<MyElectron*>::iterator itrec = RecColl.begin() ; itrec != RecColl.end() ; ++itrec){
        if ( isMatched ( *itgen , *itrec ) ) {
          nMatch++;
          pt_rec ->Fill( (*itgen)->pt  , weight );  
          eta_rec->Fill( (*itgen)->eta , weight );  
          phi_rec->Fill( (*itgen)->phi , weight );  
          dR->Fill ( deltaR( (*itgen)->eta , (*itrec)->eta , (*itgen)->phi , (*itrec)->phi  ) , weight ); 
          dPt->Fill( (*itgen)->pt - (*itrec)->pt , weight ); 
        } 
      }
      nMatched->Fill( nMatch , weight );  
   }
*/


