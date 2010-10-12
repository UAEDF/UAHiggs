#ifndef __LeptonPair_H__
#define __LeptonPair_H__

#include <vector>
using namespace std;
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "../include/MuonPlots.h"
#include "../include/MyMuon.h"
#include "../include/ElectronPlots.h"
#include "../include/MyElectron.h"
#include "TLorentzVector.h"

class LeptonPair : public TObject {


  private :
  
  MyElectron* e1;
  MyElectron* e2;
  MyMuon*     m1;
  MyMuon*     m2;
  
  public :
  
    LeptonPair(){ 
    this->type = "none" ;};
    virtual ~LeptonPair(){;};
    void fillLeptonPair(MyElectron& ele1,MyElectron& ele2);
    void fillLeptonPair(MyMuon& mu1,MyMuon& mu2);
    void fillLeptonPair(MyElectron& ele1,MyMuon& mu2);
    void fillLeptonPair(MyMuon& mu1,MyElectron& ele2);
    
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
    
    bool isInside(MyMuon*);
    bool isInside(MyElectron*);
    void PrintPair(int);
    
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

    ClassDef (LeptonPair,1)
};



#endif
