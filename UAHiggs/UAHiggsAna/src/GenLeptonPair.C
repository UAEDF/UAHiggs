#include "../include/MyGenPart.h"
#include "../include/GenLeptonPair.h"
#include "../include/MassParticles.h"
#include "TLorentzVector.h"

ClassImp(GenLeptonPair)

void GenLeptonPair::fillGenLeptonPair(MyGenPart& l1, MyGenPart& l2){
this->l1 = &l1;
this->l2 = &l2;
if( (fabs(l1.pdgId) ==11)  &&  (fabs(l2.pdgId) ==11)   )this->type = "ee";
if( (fabs(l1.pdgId) ==11)  &&  (fabs(l2.pdgId) ==13)   )this->type = "em";
if( (fabs(l1.pdgId) ==13)  &&  (fabs(l2.pdgId) ==11)   )this->type = "me";
if( (fabs(l1.pdgId) ==13)  &&  (fabs(l2.pdgId) ==13)   )this->type = "mm";
}



Double_t GenLeptonPair::getPtMax(){
 Double_t ptmax = this->l1->pt;
 return ptmax;
 }
 
Double_t GenLeptonPair::getPtMin(){
 Double_t ptmin = this->l2->pt;
 return ptmin;
 } 
 
Double_t GenLeptonPair::getMll(){

 Double_t ELepton1 = 0;
 Double_t ELepton2 = 0;
 Double_t mll = 0;

 if(this->type == "ee") { 
   ELepton1 = sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2));
   ELepton2 = sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_EL,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->l1->px+this->l2->px),2)-pow((this->l1->py+this->l2->py),2)-pow((this->l1->pz+this->l2->pz),2));
 }
 if(this->type == "em") {
   ELepton1 = sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2));
   ELepton2 = sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_MU,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->l1->px+this->l2->px),2)-pow((this->l1->py+this->l2->py),2)-pow((this->l1->pz+this->l2->pz),2));
 }
 if(this->type == "me") {
   ELepton1 = sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_MU,2));
   ELepton2 = sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_EL,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->l1->px+this->l2->px),2)-pow((this->l1->py+this->l2->py),2)-pow((this->l1->pz+this->l2->pz),2));
 }
 if(this->type == "mm") { 
   ELepton1 = sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_MU,2));
   ELepton2 = sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_MU,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->l1->px+this->l2->px),2)-pow((this->l1->py+this->l2->py),2)-pow((this->l1->pz+this->l2->pz),2));
 }
 
 //if(this->type == "ee") mll = sqrt(pow((this->e1->e+this->e2->e),2)-pow((this->e1->px+this->e2->px),2)-pow((this->e1->py+this->e2->py),2)-pow((this->e1->pz+this->e2->pz),2));  
 //if(this->type == "em") mll = sqrt(pow((this->e1->e+this->m2->e),2)-pow((this->e1->px+this->m2->px),2)-pow((this->e1->py+this->m2->py),2)-pow((this->e1->pz+this->m2->pz),2));
 //if(this->type == "me") mll = sqrt(pow((this->m1->e+this->e2->e),2)-pow((this->m1->px+this->e2->px),2)-pow((this->m1->py+this->e2->py),2)-pow((this->m1->pz+this->e2->pz),2));
 //if(this->type == "mm") mll = sqrt(pow((this->m1->e+this->m2->e),2)-pow((this->m1->px+this->m2->px),2)-pow((this->m1->py+this->m2->py),2)-pow((this->m1->pz+this->m2->pz),2));
 //if(this->type == "ee") cout << mll << endl;
 
 return mll;
 } 

Double_t GenLeptonPair::getPhiMax(){
 Double_t phi = this->l1->phi;
 return phi;
 }

 Double_t GenLeptonPair::getPhiMin(){
 Double_t phi = this->l2->phi;
 return phi;
 return 0; 
 }
 
 Double_t GenLeptonPair::getEtaMax(){
 Double_t eta = this->l1->eta;
 return eta;
 }
 
 Double_t GenLeptonPair::getEtaMin(){
 Double_t eta = this->l2->eta;
 return eta;
 }
 
 Double_t GenLeptonPair::getDeltaPhi(){
 Double_t dphi = deltaphi( this->getPhiMax(),this->getPhiMin() );
 return dphi;
 }
 
 Double_t GenLeptonPair::getDeltaEta(){
 Double_t deta = fabs( this->getEtaMax() - this->getEtaMin() );
 return deta;
 }
 
 TLorentzVector GenLeptonPair::get4v(){
   TLorentzVector v;
   if(this->type == "ee") v.SetPxPyPzE((this->l1->px+this->l2->px),(this->l1->py+this->l2->py),(this->l1->pz+this->l2->pz),(sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2))+sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_EL,2))));
   if(this->type == "em") v.SetPxPyPzE((this->l1->px+this->l2->px),(this->l1->py+this->l2->py),(this->l1->pz+this->l2->pz),(sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2))+sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_MU,2))));
   if(this->type == "me") v.SetPxPyPzE((this->l1->px+this->l2->px),(this->l1->py+this->l2->py),(this->l1->pz+this->l2->pz),(sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2))+sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2))));
   if(this->type == "mm") v.SetPxPyPzE((this->l1->px+this->l2->px),(this->l1->py+this->l2->py),(this->l1->pz+this->l2->pz),(sqrt(pow(this->l1->px,2)+pow(this->l1->py,2)+pow(this->l1->pz,2)+pow(MASS_EL,2))+sqrt(pow(this->l2->px,2)+pow(this->l2->py,2)+pow(this->l2->pz,2)+pow(MASS_MU,2))));
   return v;
 }
 
 
 void GenLeptonPair::setPrimaryState(TString state){
      if(state == "ee") this->isPrimary_ee = true;
      if(state == "mm") this->isPrimary_mm = true;
      if(state == "tt") this->isPrimary_tt = true;
      if(state == "em") this->isPrimary_em = true;
      if(state == "et") this->isPrimary_et = true;
      if(state == "mt") this->isPrimary_mt = true;
      if(state == "nl") this->isPrimary_nl = true;
      
  }
 
 
 
 
 
 
 
 Double_t GenLeptonPair::getProjectedMet(double met, double metphi){
   double pmet=0;
   double dphi = min( deltaphi( metphi,this->getPhiMax()) , deltaphi(metphi,this->getPhiMin()) );
   if(dphi < M_PI/2) pmet = met*sin(dphi);
   else              pmet = met;
   return pmet;
 }
 
bool GenLeptonPair::isInside(MyGenPart* l){
     if( (this->l1 == l) || (this->l2 == l) )return true;
     else return false;
     }
 
  
