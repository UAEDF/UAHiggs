#include "../include/MuonPlots.h"
#include "../include/MyMuon.h"
#include "../include/ElectronPlots.h"
#include "../include/MyElectron.h"
#include "../include/LeptonPair.h"
#include "../include/MassParticles.h"
#include "TLorentzVector.h"

ClassImp(LeptonPair)

void LeptonPair::fillLeptonPair(MyElectron& ele1, MyElectron& ele2){
this->e1 = &ele1;
this->e2 = &ele2;
this->m1 = 0;
this->m2 = 0;
this->type = "ee";
}

void LeptonPair::fillLeptonPair(MyElectron& ele1, MyMuon& mu2){
this->e1 = &ele1;
this->m2 = &mu2;
this->e2 = 0;
this->m1 = 0;
this->type = "em";
}

void LeptonPair::fillLeptonPair(MyMuon& mu1, MyMuon& mu2){
this->m1 = &mu1;
this->m2 = &mu2;
this->e1 = 0;
this->e2 = 0;
this->type = "mm";
}

void LeptonPair::fillLeptonPair(MyMuon& mu1, MyElectron& ele2){
this->m1 = &mu1;
this->e2 = &ele2;
this->e1 = 0;
this->m2 = 0;
this->type = "me";
}

Double_t LeptonPair::getPtMax(){
 Double_t ptmax = 0;
 if(this->type == "ee") ptmax = this->e1->pt;
 if(this->type == "em") ptmax = this->e1->pt;
 if(this->type == "me") ptmax = this->m1->pt;
 if(this->type == "mm") ptmax = this->m1->pt;
 return ptmax;
 }
 
Double_t LeptonPair::getPtMin(){
 Double_t ptmin = 0;
 if(this->type == "ee") ptmin = this->e2->pt;
 if(this->type == "em") ptmin = this->m2->pt;
 if(this->type == "me") ptmin = this->e2->pt;
 if(this->type == "mm") ptmin = this->m2->pt;
 return ptmin;
 } 
 
Double_t LeptonPair::getMll(){

 Double_t ELepton1 = 0;
 Double_t ELepton2 = 0;
 Double_t mll = 0;

 if(this->type == "ee") { 
   ELepton1 = sqrt(pow(this->e1->px,2)+pow(this->e1->py,2)+pow(this->e1->pz,2)+pow(MASS_EL,2));
   ELepton2 = sqrt(pow(this->e2->px,2)+pow(this->e2->py,2)+pow(this->e2->pz,2)+pow(MASS_EL,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->e1->px+this->e2->px),2)-pow((this->e1->py+this->e2->py),2)-pow((this->e1->pz+this->e2->pz),2));
 }
 if(this->type == "em") {
   ELepton1 = sqrt(pow(this->e1->px,2)+pow(this->e1->py,2)+pow(this->e1->pz,2)+pow(MASS_EL,2));
   ELepton2 = sqrt(pow(this->m2->px,2)+pow(this->m2->py,2)+pow(this->m2->pz,2)+pow(MASS_MU,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->e1->px+this->m2->px),2)-pow((this->e1->py+this->m2->py),2)-pow((this->e1->pz+this->m2->pz),2));
 }
 if(this->type == "me") {
   ELepton1 = sqrt(pow(this->m1->px,2)+pow(this->m1->py,2)+pow(this->m1->pz,2)+pow(MASS_MU,2));
   ELepton2 = sqrt(pow(this->e2->px,2)+pow(this->e2->py,2)+pow(this->e2->pz,2)+pow(MASS_EL,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->m1->px+this->e2->px),2)-pow((this->m1->py+this->e2->py),2)-pow((this->m1->pz+this->e2->pz),2));
 }
 if(this->type == "mm") { 
   ELepton1 = sqrt(pow(this->m1->px,2)+pow(this->m1->py,2)+pow(this->m1->pz,2)+pow(MASS_MU,2));
   ELepton2 = sqrt(pow(this->m2->px,2)+pow(this->m2->py,2)+pow(this->m2->pz,2)+pow(MASS_MU,2));
   mll = sqrt(pow((ELepton1+ELepton2),2)-pow((this->m1->px+this->m2->px),2)-pow((this->m1->py+this->m2->py),2)-pow((this->m1->pz+this->m2->pz),2));
 }
 
 //if(this->type == "ee") mll = sqrt(pow((this->e1->e+this->e2->e),2)-pow((this->e1->px+this->e2->px),2)-pow((this->e1->py+this->e2->py),2)-pow((this->e1->pz+this->e2->pz),2));  
 //if(this->type == "em") mll = sqrt(pow((this->e1->e+this->m2->e),2)-pow((this->e1->px+this->m2->px),2)-pow((this->e1->py+this->m2->py),2)-pow((this->e1->pz+this->m2->pz),2));
 //if(this->type == "me") mll = sqrt(pow((this->m1->e+this->e2->e),2)-pow((this->m1->px+this->e2->px),2)-pow((this->m1->py+this->e2->py),2)-pow((this->m1->pz+this->e2->pz),2));
 //if(this->type == "mm") mll = sqrt(pow((this->m1->e+this->m2->e),2)-pow((this->m1->px+this->m2->px),2)-pow((this->m1->py+this->m2->py),2)-pow((this->m1->pz+this->m2->pz),2));
 //if(this->type == "ee") cout << mll << endl;
 
 return mll;
 } 

Double_t LeptonPair::getPhiMax(){
 Double_t phi = 0;
 if(this->type == "ee") phi = this->e1->phi;
 if(this->type == "em") phi = this->e1->phi;
 if(this->type == "me") phi = this->m1->phi;
 if(this->type == "mm") phi = this->m1->phi;
 return phi;
 }

 Double_t LeptonPair::getPhiMin(){
 Double_t phi = 0;
 if(this->type == "ee") phi = this->e2->phi;
 if(this->type == "em") phi = this->m2->phi;
 if(this->type == "me") phi = this->e2->phi;
 if(this->type == "mm") phi = this->m2->phi;
 return phi;
 }
 
 Double_t LeptonPair::getEtaMax(){
 Double_t eta = 0;
 if(this->type == "ee") eta = this->e1->eta;
 if(this->type == "em") eta = this->e1->eta;
 if(this->type == "me") eta = this->m1->eta;
 if(this->type == "mm") eta = this->m1->eta;
 return eta;
 }
 
 Double_t LeptonPair::getEtaMin(){
 Double_t eta = 0;
 if(this->type == "ee") eta = this->e2->eta;
 if(this->type == "em") eta = this->m2->eta;
 if(this->type == "me") eta = this->e2->eta;
 if(this->type == "mm") eta = this->m2->eta;
 return eta;
 }
 
 Double_t LeptonPair::getDeltaPhi(){
 Double_t dphi = deltaphi( this->getPhiMax(),this->getPhiMin() );
 return dphi;
 }
 
 Double_t LeptonPair::getDeltaEta(){
 Double_t deta = fabs( this->getEtaMax() - this->getEtaMin() );
 return deta;
 }
 
 TLorentzVector LeptonPair::get4v(){
   TLorentzVector v;

   Double_t ELepton1 = 0;
   Double_t ELepton2 = 0;

   if(this->type == "ee") { 
     ELepton1 = sqrt(pow(this->e1->px,2)+pow(this->e1->py,2)+pow(this->e1->pz,2)+pow(MASS_EL,2));
     ELepton2 = sqrt(pow(this->e2->px,2)+pow(this->e2->py,2)+pow(this->e2->pz,2)+pow(MASS_EL,2));
   }
   if(this->type == "em") {
     ELepton1 = sqrt(pow(this->e1->px,2)+pow(this->e1->py,2)+pow(this->e1->pz,2)+pow(MASS_EL,2));
     ELepton2 = sqrt(pow(this->m2->px,2)+pow(this->m2->py,2)+pow(this->m2->pz,2)+pow(MASS_MU,2));
   }
   if(this->type == "me") {
     ELepton1 = sqrt(pow(this->m1->px,2)+pow(this->m1->py,2)+pow(this->m1->pz,2)+pow(MASS_MU,2));
     ELepton2 = sqrt(pow(this->e2->px,2)+pow(this->e2->py,2)+pow(this->e2->pz,2)+pow(MASS_EL,2));
   }
   if(this->type == "mm") { 
     ELepton1 = sqrt(pow(this->m1->px,2)+pow(this->m1->py,2)+pow(this->m1->pz,2)+pow(MASS_MU,2));
     ELepton2 = sqrt(pow(this->m2->px,2)+pow(this->m2->py,2)+pow(this->m2->pz,2)+pow(MASS_MU,2));
   }

   if(this->type == "ee") v.SetPxPyPzE((this->e1->px+this->e2->px),(this->e1->py+this->e2->py),(this->e1->pz+this->e2->pz),(ELepton1+ELepton2));
   if(this->type == "em") v.SetPxPyPzE((this->e1->px+this->m2->px),(this->e1->py+this->m2->py),(this->e1->pz+this->m2->pz),(ELepton1+ELepton2));
   if(this->type == "me") v.SetPxPyPzE((this->m1->px+this->e2->px),(this->m1->py+this->e2->py),(this->m1->pz+this->e2->pz),(ELepton1+ELepton2));
   if(this->type == "mm") v.SetPxPyPzE((this->m1->px+this->m2->px),(this->m1->py+this->m2->py),(this->m1->pz+this->m2->pz),(ELepton1+ELepton2));

   return v;
 }
 
 
 Double_t LeptonPair::getProjectedMet(double met, double metphi){
   double pmet=0;
   double dphi = min( deltaphi( metphi,this->getPhiMax()) , deltaphi(metphi,this->getPhiMin()) );
   if(dphi < M_PI/2) pmet = met*sin(dphi);
   else              pmet = met;
   return pmet;
 }
 
bool LeptonPair::isInside(MyMuon* mu){
     //cout << "Mu3Test: " << mu << endl;
     //cout << "Paire  : " << this->m1 << " " << this->m2 << endl;
     if( (this->m1 == mu) || (this->m2 == mu) )return true;
     else return false;
     }
 
bool LeptonPair::isInside(MyElectron* ele){
     if( (this->e1 == ele) || (this->e2 == ele) )return true;
     else return false;
     }
 
void LeptonPair::Print() {

  cout << "---------------- LeptonPair Print() ------------------------" << endl;
  cout << "Pair type : " << this->type << endl;
  cout << "Pt  min,max,pair   : " << this->getPtMin()  << " " << this->getPtMax()  << " " << this->get4v().Pt() << endl;
  cout << "Eta min,max,pair   : " << this->getEtaMin() << " " << this->getEtaMax() << " " << this->get4v().Eta() << endl;
  cout << "Phi min,max,pair   : " << this->getPhiMin() << " " << this->getPhiMax() << " " << this->get4v().Phi() << endl;
  cout << "Mll , Deta, Dphi   : " << this->getMll()    << " " << this->getDeltaEta() << " " << this->getDeltaPhi() << endl; 
  if (this->type == "ee") { this->e1->Print();  this->e2->Print() ; }
  if (this->type == "em") { this->e1->Print();  this->m2->Print() ; }
  if (this->type == "me") { this->m1->Print();  this->e2->Print() ; }
  if (this->type == "mm") { this->m1->Print();  this->m2->Print() ; }
  cout << "------------------------------------------------------------" << endl;

}



  
