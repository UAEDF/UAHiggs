
#ifndef __LeptonPairPlots_H__
#define __LeptonPairPlots_H__

#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "./MyMuon.h"
#include "./MyElectron.h"
#include "./LeptonPair.h"




class LeptonPairPlots : public TObject {

  public :
    LeptonPairPlots();
    LeptonPairPlots(TString);
    virtual ~LeptonPairPlots();

    TString LeptonPaircoll;
    
    // Pair properties
    
     TH1F* phimax; 
     TH1F* phimin; 
     TH1F* etamax; 
     TH1F* etamin; 
     TH1F* ptmax; 
     TH1F* ptmin; 
     TH1F* dPhi; 
     TH1F* dEta; 
     TH1F* pMet; 
     TH1F* Met; 
     TH1F* mll; 
     TH1F* pt;
     TH1F* eta;
     TH1F* phi;
     
     
     void init();
     void fill(vector<LeptonPair*>& ,double met , double metphi , double = 1.);
     void fill(LeptonPair& ,double met , double metphi , double = 1);
     void write();
    
    
    ClassDef (LeptonPairPlots,1)
};



#endif


