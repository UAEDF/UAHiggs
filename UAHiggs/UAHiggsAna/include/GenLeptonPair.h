#ifndef __GenLeptonPair_H__
#define __GenLeptonPair_H__

#include <vector>
using namespace std;
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "../include/MyGenPart.h"

#include "TLorentzVector.h"

class GenLeptonPair : public TObject {


  private :
  
  MyGenPart*  l1;
  MyGenPart * l2;
  
  public :
  
    GenLeptonPair(){
    this->type = "none" ;
    this->isPrimary_ee = false;
    this->isPrimary_mm = false;
    this->isPrimary_tt = false;
    this->isPrimary_em = false;
    this->isPrimary_et = false;
    this->isPrimary_mt = false;
    this->isPrimary_nl = false;
    };
    virtual ~GenLeptonPair(){
   //   delete l1;
   //   delete l2;
    };
    void fillGenLeptonPair(MyGenPart& l1,MyGenPart& l2);
     
    TLorentzVector get4v();
    
    Double_t getPtMax();
    Double_t getPtMin();
    Double_t getMll();
    Double_t getPhiMax();
    Double_t getPhiMin();
    Double_t getEtaMax();
    Double_t getEtaMin();
    Double_t getDeltaPhi();
    Double_t getDeltaEta();
    Double_t getProjectedMet(double met, double metphi);
    
    bool isInside(MyGenPart*);
    
    bool isPrimary_ee;
    bool isPrimary_mm;
    bool isPrimary_tt;
    bool isPrimary_em;
    bool isPrimary_et;
    bool isPrimary_mt;
    bool isPrimary_nl;
    
   
    void setPrimaryState(TString);
    
    string type;

    double deltaphi(double phi1, double phi2) 
     {
     double dphi = fabs(phi1-phi2);
     if(dphi > M_PI) 
      {
      dphi = (2*M_PI - dphi);
      }
     return dphi;
    }

    ClassDef (GenLeptonPair,1)
};



#endif
