
#ifndef __GenLeptonPairPlots_H__
#define __GenLeptonPairPlots_H__

#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "./MyGenPart.h"
#include "./GenLeptonPair.h"




class GenLeptonPairPlots : public TObject {

  public :
    GenLeptonPairPlots();
    GenLeptonPairPlots(TString);
    virtual ~GenLeptonPairPlots();

    TString GenLeptonPaircoll;
    
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
     
     TH1F* isPrimary_ee;
     TH1F* isPrimary_mm;
     TH1F* isPrimary_tt;
     TH1F* isPrimary_em;
     TH1F* isPrimary_et;
     TH1F* isPrimary_mt;
     TH1F* isPrimary_nl;
     
     
     
     void init();
     void fill(vector<GenLeptonPair*>& ,double met , double metphi , double = 1.);
     void fill(GenLeptonPair& ,double met , double metphi , double = 1);
     void write();
    
    
    ClassDef (GenLeptonPairPlots,1)
};



#endif


