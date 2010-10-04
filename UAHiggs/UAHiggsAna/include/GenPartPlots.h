#ifndef __GenPartPlots_H__
#define __GenPartPlots_H__

#include <vector>
using namespace std;
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "./MyGenPart.h"

class GenPartPlots : public TObject {

  public :
    GenPartPlots();
    GenPartPlots(TString);
    virtual ~GenPartPlots();

    TString genpartcoll;
    
    TH1F* ptmin; 
    TH1F* ptmax; 
    TH1F* etamin; 
    TH1F* etamax; 
    TH1F* phimin; 
    TH1F* phimax; 
    
    void init();
    void fill(vector<MyGenPart>& , double = 1.);
    void write();
    
    
    ClassDef (GenPartPlots,1)
};



#endif


