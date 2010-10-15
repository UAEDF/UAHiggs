#ifndef __EfficiencyPlots_H__
#define __EfficiencyPlots_H__

#include <vector>
using namespace std;
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TDirectory.h"
#include "TVector3.h"
#include "./MyGenPart.h"
#include "./MyElectron.h"
#include "./MyMuon.h"

class EfficiencyPlots : public TObject {

  public :
    EfficiencyPlots();
    EfficiencyPlots(TString);
    virtual ~EfficiencyPlots();

    TString Recocoll;
    
    TH1F* pt_gen; 
    TH1F* eta_gen; 
    TH1F* phi_gen; 


    TH1F* nMatched;
    TH1F* dR;
    TH1F* dPt;
    TH1F* deta;
    TH1F* dphi;
 
    TH1F* pt_rec;
    TH1F* eta_rec;
    TH1F* phi_rec;

    TH1F* pt_eff;
    TH1F* eta_eff;
    TH1F* phi_eff;

    void init();
 
    void fill(vector<MyGenPart*>&, vector<MyGenPart*>& , double = 1.);
    void fill(vector<MyGenPart*>&, vector<MyElectron*>& , double = 1.);
    void fill(vector<MyGenPart*>&, vector<MyMuon*>&     , double = 1.);

    void fill(vector<TVector3>& , vector<TVector3>& , double = 1.);

    //void fill(vector<MyLeptonReco>& , double = 1., int = -1);
    //void fill(vector<MyLeptonReco*>& , double = 1., int = -1);
    //void fill(MyLeptonReco& , double = 1., int = -1);
    
    void write();
    
    ClassDef (EfficiencyPlots,1)
};



#endif


