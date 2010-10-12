
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
#include "TH1F.h"
#include "TGraph.h"
#include "TMultiGraph.h"      
#include "TGraphAsymmErrors.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"

#include "include/MyPart.h"
#include "include/MyEvtId.h"
#include "include/MyGenPart.h"
#include "include/MyGenKin.h"
#include "include/MyGenMET.h"
#include "include/MyGenJet.h"
#include "include/MyEvtId.h"
#include "include/MyVertex.h"
#include "include/MyTracks.h"
#include "include/MyBeamSpot.h"
#include "include/MyJet.h"
#include "include/MyL1Trig.h"
#include "include/MyHLTrig.h"
#include "include/MyElectron.h"
#include "include/MyMuon.h"
#include "include/MyMET.h"

#include "src/PrintTools.C"
#include "src/MatchTools.C"

#include "include/GenPartPlots.h"
#include "src/GenPartPlots.C"
#include "include/ElectronPlots.h"
#include "src/ElectronPlots.C"
#include "include/MuonPlots.h"
#include "src/MuonPlots.C"
#include "include/LeptonPair.h"
#include "src/LeptonPair.C"
#include "include/GenLeptonPair.h"
#include "src/GenLeptonPair.C"
#include "include/LeptonPairPlots.h"
#include "src/LeptonPairPlots.C"
#include "include/GenLeptonPairPlots.h"
#include "src/GenLeptonPairPlots.C"
#include "include/LinkDef.h"


#include "TMath.h" //M_PI is in TMath

#include "src/cuts.C"

double deltaEta(double eta1, double eta2) 
{
  double deta = fabs(eta1-eta2);
  
  return deta;
}


double deltaphi(double phi1, double phi2) 
{
  double dphi = fabs(phi1-phi2);
  if(dphi > M_PI) 
    {
      dphi = (2*M_PI - dphi);
    }
  return dphi;
}
double CorrectPhi(double phi, double x, double y)
{
  if(phi>0 && x<0 && y<0)phi+=M_PI;
  if(phi<0 && x>0 && y<0)phi=(2*M_PI-fabs(phi));
  if(phi<0 && x<0 && y>0)phi=(M_PI-fabs(phi));
  if(y<0)phi-=(2*M_PI);//without this you have 0<phi<2pi, but with this
  return phi;//you get -pi<phi<pi
}

double maxi(double x, double y, double z)
{
double maxi=max(x,max(y,z));
  return maxi;
}


int main(){

  
  double CrossSection;
  double Luminosity;
  string Data;
  double DataSampleWeight;
  string OutputRootFile;
  string OutputTextFile;
  
  //all gen leptons
 // vector<MyGenPart> *allGenLeptonsIII =   ;//all gen leptons
      
  double weight=1.; // weight here is 1 for all signal and WZ and ZZ but for WWmcnlo it can be -1
  double kfactor=1.;
  
  double nevanalyzed=0;
  double hltpassed=0;

  
  
  double nmu5    =0;
  double nel5    =0;
  double nmu10   =0;
  double nel10   =0;
  double npair5  =0;
  double npair10 =0;
 
  
  
  
  
  // ------------ L1 Trigger ---------------------
  
  double L1_SingleMuOpen=0;
  double L1_SingleMu0=0;
  double L1_SingleMu7=0;
  double L1_DoubleMu3=0;
  double L1_SingleMu20=0;
  double L1_SingleMu3=0;
  double L1_DoubleMuOpen=0;
  double L1_SingleEG1=0;
  double L1_SingleEG2=0;
  double L1_SingleEG5=0;
  double L1_SingleEG8=0;
  double L1_SingleEG20=0;
  double L1_DoubleEG5=0;
  
  
  
  
  // ------HLTrigger analysis -------------------
  
  double HLT_L1MuOpen=0;
  double HLT_L1Mu=0;
  double HLT_Mu5=0;
  double HLT_Mu9=0;
  double HLT_L1DoubleMuOpen=0;
  double HLT_DoubleMu0=0;
  double HLT_DoubleMu3=0;
  double HLT_L1SingleEG5=0;
//  double HLT_Ele15_SW_EleId_L1R=0;
  double HLT_Ele15_LW_L1R=0;
  double HLT_Ele15_SiStrip_L1R=0;
  
  
   
  
  double pteta_passed_ee     = 0;
  double pteta_passed_mm     = 0;
  double pteta_passed_em     = 0;
  double pteta_passed_me     = 0;
  double pteta_passed_mixed  = 0;
  double pteta_passed_all    = 0;
  
  double d0_passed_ee     = 0;
  double d0_passed_mm     = 0;
  double d0_passed_em     = 0;
  double d0_passed_me     = 0;
  double d0_passed_mixed   = 0;
  double d0_passed_all     = 0;
  
  double iso_passed_ee     = 0;
  double iso_passed_mm     = 0;
  double iso_passed_em     = 0;
  double iso_passed_me    = 0;
  double iso_passed_mixed  = 0;
  double iso_passed_all    = 0;
  
  double id_passed_ee     = 0;
  double id_passed_mm     = 0;
  double id_passed_em     = 0;
  double id_passed_me     = 0;
  double id_passed_mixed  = 0;
  double id_passed_all    = 0;
  
  double conv_passed_ee     = 0;
  double conv_passed_mm     = 0;
  double conv_passed_em     = 0;
  double conv_passed_me     = 0;
  double conv_passed_mixed  = 0;
  double conv_passed_all    = 0;
  
  double met_passed_ee     = 0;
  double met_passed_mm     = 0;
  double met_passed_em     = 0;
  double met_passed_me     = 0;
  double met_passed_mixed  = 0;
  double met_passed_all    = 0;
  
  double mll1_passed_ee     = 0;
  double mll1_passed_mm     = 0;
  double mll1_passed_em     = 0;
  double mll1_passed_me     = 0;
  double mll1_passed_mixed  = 0;
  double mll1_passed_all    = 0;
  
  double mll2_passed_ee     = 0;
  double mll2_passed_mm     = 0;
  double mll2_passed_em     = 0;
  double mll2_passed_me     = 0;
  double mll2_passed_mixed  = 0;
  double mll2_passed_all    = 0;
  
  double pmet_passed_ee     = 0;
  double pmet_passed_mm     = 0;
  double pmet_passed_em     = 0;
  double pmet_passed_me     = 0;
  double pmet_passed_mixed  = 0;
  double pmet_passed_all    = 0;
  
  double jetveto_passed_ee     = 0;
  double jetveto_passed_mm     = 0;
  double jetveto_passed_em     = 0;
  double jetveto_passed_me     = 0;
  double jetveto_passed_mixed  = 0;
  double jetveto_passed_all    = 0;
  
  double softmuons_passed_ee     = 0;
  double softmuons_passed_mm     = 0;
  double softmuons_passed_em     = 0;
  double softmuons_passed_me     = 0;
  double softmuons_passed_mixed  = 0;
  double softmuons_passed_all    = 0;
 
  
  double extraleptons_passed_ee     = 0;
  double extraleptons_passed_mm     = 0;
  double extraleptons_passed_em     = 0;
  double extraleptons_passed_me     = 0;
  double extraleptons_passed_mixed  = 0;
  double extraleptons_passed_all    = 0;
 
 
  double D_ee     = 0;
  double D_mm     = 0;
  double D_em     = 0;
  double D_me     = 0;
  double D_mixed  = 0;
  double D_all    = 0;
 
 
 
  //=================event loop

  int ntot=0;

  ifstream ConfigFile;
  ConfigFile.open("config/Config.txt");
  if(!ConfigFile){cout<<"Unable to read the config file";exit(1);}
  
  ConfigFile>>CrossSection;
  ConfigFile>>Luminosity;
  ConfigFile>>DataSampleWeight;
  ConfigFile>>Data;
  ConfigFile>>OutputRootFile;
  ConfigFile>>OutputTextFile;

 
  
  cout<<" Ok The Following input parameters were read : "<<endl;
  cout<<"===> CrossSection       : "<<CrossSection<<endl;
  cout<<"===> Data?              : "<<Data<<endl;
  cout<<"===> DataSampleWeight   : "<<DataSampleWeight<<endl;
  cout<<"===> Luminosity (pb-1)  : "<<Luminosity<<endl;
  cout<<"===> Output root file   : "<<OutputRootFile<<endl;
  cout<<"===> Output txt file    : "<<OutputTextFile<<endl;


 
  ElectronPlots* electrons_noCut          = new ElectronPlots("electrons_noCut");
  ElectronPlots* electrons_PtEtaCut       = new ElectronPlots("electrons_PtEtaCut");
  ElectronPlots* electrons_d0Cut          = new ElectronPlots("electrons_d0Cut");
  ElectronPlots* electrons_IsoCut_all     = new ElectronPlots("electrons_IsoCut_all");
  ElectronPlots* electrons_IsoCut_barrel  = new ElectronPlots("electrons_IsoCut_barrel");
  ElectronPlots* electrons_IsoCut_endcap  = new ElectronPlots("electrons_IsoCut_endcap");
  ElectronPlots* electrons_IdCut_all      = new ElectronPlots("electrons_IdCut_all");
  ElectronPlots* electrons_IdCut_barrel   = new ElectronPlots("electrons_IdCut_barrel");
  ElectronPlots* electrons_IdCut_endcap   = new ElectronPlots("electrons_IdCut_endcap");
  ElectronPlots* electrons_ConversionCut  = new ElectronPlots("electrons_ConversionCut");
  
  
  MuonPlots*     muons_noCut         = new MuonPlots("muons_noCut");
  MuonPlots*     muons_PtEtaCut      = new MuonPlots("muons_PtEtaCut");
  MuonPlots*     muons_d0Cut         = new MuonPlots("muons_d0Cut");
  MuonPlots*     muons_IsoCut        = new MuonPlots("muons_IsoCut");
  MuonPlots*     muons_IdCut         = new MuonPlots("muons_IdCut");
  
  
  LeptonPairPlots*  pair_noCut_ee       = new LeptonPairPlots("noCut_ee");
  LeptonPairPlots*  pair_noCut_mm       = new LeptonPairPlots("noCut_mm");
  LeptonPairPlots*  pair_noCut_em       = new LeptonPairPlots("noCut_em");
  LeptonPairPlots*  pair_noCut_me       = new LeptonPairPlots("noCut_me");
  LeptonPairPlots*  pair_noCut_mixed    = new LeptonPairPlots("noCut_ee");
  LeptonPairPlots*  pair_noCut_all      = new LeptonPairPlots("noCut_all");
  
  LeptonPairPlots*  pair_ptEtaCut_ee       = new LeptonPairPlots("ptEtaCut_ee");
  LeptonPairPlots*  pair_ptEtaCut_mm       = new LeptonPairPlots("ptEtaCut_mm");
  LeptonPairPlots*  pair_ptEtaCut_em       = new LeptonPairPlots("ptEtaCut_em");
  LeptonPairPlots*  pair_ptEtaCut_me       = new LeptonPairPlots("ptEtaCut_me");
  LeptonPairPlots*  pair_ptEtaCut_mixed    = new LeptonPairPlots("ptEtaCut_ee");
  LeptonPairPlots*  pair_ptEtaCut_all      = new LeptonPairPlots("ptEtaCut_all");
  
  LeptonPairPlots*  pair_d0Cut_ee       = new LeptonPairPlots("d0Cut_ee");
  LeptonPairPlots*  pair_d0Cut_mm       = new LeptonPairPlots("d0Cut_mm");
  LeptonPairPlots*  pair_d0Cut_em       = new LeptonPairPlots("d0Cut_em");
  LeptonPairPlots*  pair_d0Cut_me       = new LeptonPairPlots("d0Cut_me");
  LeptonPairPlots*  pair_d0Cut_mixed    = new LeptonPairPlots("d0Cut_ee");
  LeptonPairPlots*  pair_d0Cut_all      = new LeptonPairPlots("d0Cut_all");
  
  LeptonPairPlots*  pair_IsoCut_ee       = new LeptonPairPlots("IsoCut_ee");
  LeptonPairPlots*  pair_IsoCut_mm       = new LeptonPairPlots("IsoCut_mm");
  LeptonPairPlots*  pair_IsoCut_em       = new LeptonPairPlots("IsoCut_em");
  LeptonPairPlots*  pair_IsoCut_me       = new LeptonPairPlots("IsoCut_me");
  LeptonPairPlots*  pair_IsoCut_mixed    = new LeptonPairPlots("IsoCut_ee");
  LeptonPairPlots*  pair_IsoCut_all      = new LeptonPairPlots("IsoCut_all");

  LeptonPairPlots*  pair_IdCut_ee       = new LeptonPairPlots("IdCut_ee");
  LeptonPairPlots*  pair_IdCut_mm       = new LeptonPairPlots("IdCut_mm");
  LeptonPairPlots*  pair_IdCut_em       = new LeptonPairPlots("IdCut_em");
  LeptonPairPlots*  pair_IdCut_me       = new LeptonPairPlots("IdCut_me");
  LeptonPairPlots*  pair_IdCut_mixed    = new LeptonPairPlots("IdCut_ee");
  LeptonPairPlots*  pair_IdCut_all      = new LeptonPairPlots("IdCut_all");

  LeptonPairPlots*  pair_ConvCut_ee       = new LeptonPairPlots("ConvCut_ee");
  LeptonPairPlots*  pair_ConvCut_mm       = new LeptonPairPlots("ConvCut_mm");
  LeptonPairPlots*  pair_ConvCut_em       = new LeptonPairPlots("ConvCut_em");
  LeptonPairPlots*  pair_ConvCut_me       = new LeptonPairPlots("ConvCut_me");
  LeptonPairPlots*  pair_ConvCut_mixed    = new LeptonPairPlots("ConvCut_ee");
  LeptonPairPlots*  pair_ConvCut_all      = new LeptonPairPlots("ConvCut_all");

  
   
  
  GenLeptonPairPlots*  genpair_ee_nocut       = new GenLeptonPairPlots("genpair_ee_nocut");
  GenLeptonPairPlots*  genpair_mm_nocut       = new GenLeptonPairPlots("genpair_mm_nocut");
  GenLeptonPairPlots*  genpair_em_nocut       = new GenLeptonPairPlots("genpair_em_nocut");
  GenLeptonPairPlots*  genpair_me_nocut       = new GenLeptonPairPlots("genpair_me_nocut");
  GenLeptonPairPlots*  genpair_mixed_nocut    = new GenLeptonPairPlots("genpair_mixed_nocut");
  GenLeptonPairPlots*  genpair_all_nocut      = new GenLeptonPairPlots("genpair_all_nocut");
  
  GenLeptonPairPlots*  genpair_ee_nofromtau_nocut       = new GenLeptonPairPlots("genpair_ee_nofromtau_nocut");
  GenLeptonPairPlots*  genpair_mm_nofromtau_nocut       = new GenLeptonPairPlots("genpair_mm_nofromtau_nocut");
  GenLeptonPairPlots*  genpair_em_nofromtau_nocut       = new GenLeptonPairPlots("genpair_em_nofromtau_nocut");
  GenLeptonPairPlots*  genpair_me_nofromtau_nocut       = new GenLeptonPairPlots("genpair_me_nofromtau_nocut");
  GenLeptonPairPlots*  genpair_mixed_nofromtau_nocut    = new GenLeptonPairPlots("genpair_mixed_nofromtau_nocut");
  GenLeptonPairPlots*  genpair_all_nofromtau_nocut      = new GenLeptonPairPlots("genpair_all_nofromtau_nocut");
  
  GenLeptonPairPlots*  genpair_ee_fromtau_nocut       = new GenLeptonPairPlots("genpair_ee_fromtau_nocut");
  GenLeptonPairPlots*  genpair_mm_fromtau_nocut       = new GenLeptonPairPlots("genpair_mm_fromtau_nocut");
  GenLeptonPairPlots*  genpair_em_fromtau_nocut       = new GenLeptonPairPlots("genpair_em_fromtau_nocut");
  GenLeptonPairPlots*  genpair_me_fromtau_nocut       = new GenLeptonPairPlots("genpair_me_fromtau_nocut");
  GenLeptonPairPlots*  genpair_mixed_fromtau_nocut    = new GenLeptonPairPlots("genpair_mixed_fromtau_nocut");
  GenLeptonPairPlots*  genpair_all_fromtau_nocut      = new GenLeptonPairPlots("genpair_all_fromtau_nocut");  
  
  GenLeptonPairPlots*  genpair_ee_pteta       = new GenLeptonPairPlots("genpair_ee_pteta");
  GenLeptonPairPlots*  genpair_mm_pteta       = new GenLeptonPairPlots("genpair_mm_pteta");
  GenLeptonPairPlots*  genpair_em_pteta       = new GenLeptonPairPlots("genpair_em_pteta");
  GenLeptonPairPlots*  genpair_me_pteta       = new GenLeptonPairPlots("genpair_me_pteta");
  GenLeptonPairPlots*  genpair_mixed_pteta    = new GenLeptonPairPlots("genpair_mixed_pteta");
  GenLeptonPairPlots*  genpair_all_pteta      = new GenLeptonPairPlots("genpair_all_pteta");
  
  GenLeptonPairPlots*  genpair_ee_nofromtau_pteta       = new GenLeptonPairPlots("genpair_ee_nofromtau_pteta");
  GenLeptonPairPlots*  genpair_mm_nofromtau_pteta       = new GenLeptonPairPlots("genpair_mm_nofromtau_pteta");
  GenLeptonPairPlots*  genpair_em_nofromtau_pteta       = new GenLeptonPairPlots("genpair_em_nofromtau_pteta");
  GenLeptonPairPlots*  genpair_me_nofromtau_pteta       = new GenLeptonPairPlots("genpair_me_nofromtau_pteta");
  GenLeptonPairPlots*  genpair_mixed_nofromtau_pteta    = new GenLeptonPairPlots("genpair_mixed_nofromtau_pteta");
  GenLeptonPairPlots*  genpair_all_nofromtau_pteta      = new GenLeptonPairPlots("genpair_all_nofromtau_pteta");
  
  GenLeptonPairPlots*  genpair_ee_fromtau_pteta       = new GenLeptonPairPlots("genpair_ee_fromtau_pteta");
  GenLeptonPairPlots*  genpair_mm_fromtau_pteta       = new GenLeptonPairPlots("genpair_mm_fromtau_pteta");
  GenLeptonPairPlots*  genpair_em_fromtau_pteta       = new GenLeptonPairPlots("genpair_em_fromtau_pteta");
  GenLeptonPairPlots*  genpair_me_fromtau_pteta       = new GenLeptonPairPlots("genpair_me_fromtau_pteta");
  GenLeptonPairPlots*  genpair_mixed_fromtau_pteta    = new GenLeptonPairPlots("genpair_mixed_fromtau_pteta");
  GenLeptonPairPlots*  genpair_all_fromtau_pteta      = new GenLeptonPairPlots("genpair_all_fromtau_pteta");  

  int nf=0;
  string filename;
  while(ConfigFile>>filename && filename!="EOF"){
     
    cout<<"Reading "<<filename<<endl;
    TFile *file=TFile::Open(filename.c_str());
    TTree* rootTree=new TTree;
    rootTree = (TTree*)file->Get("tree");
    int nev = int(rootTree->GetEntries());
    cout<<"number of entries is : "<<nev<<endl;
    
      MyEvtId            *evtid                    = NULL ;
      MyL1Trig           *l1trig                   = NULL ;
      MyHLTrig           *hltrig                   = NULL ;
      MyGenKin           *genkin                   = NULL ;
      vector<MyVertex>   *vertex                   = NULL;
    
      vector<MyGenPart>  *genpart                  = NULL ;
      vector<MyGenPart>  *genelec                  = NULL ;
      vector<MyGenPart>  *genmu                    = NULL ;
  //  vector<MyGenPart>  *gennu                    = NULL ;
  //  vector<MyJet>      *ak5calojets              = NULL ;
      vector<MyJet>      *ak5pfjets                = NULL ;
  //  vector<MyJet>      *ak5trackjets             = NULL ;
  //  vector<MyJet>      *iterativecone5calojets   = NULL ;
  //  vector<MyJet>      *iterativecone5pfjets     = NULL ;
  //  vector<MyJet>      *iterativecone5trackjets  = NULL ;
  //  vector<MyJet>      *siscone5calojets         = NULL ;
  //  vector<MyJet>      *siscone5pfjets           = NULL ;
  //  vector<MyJet>      *siscone5trackjets        = NULL ;
      vector<MyElectron> *electrons_raw            = NULL;
      vector<MyMuon>     *muons_raw                = NULL ;
   // vector<MyMET>      *calomet                  = NULL ;
      vector<MyMET>      *tcmet                    = NULL ;
  //  vector<MyMET>      *pfmet                    = NULL ;
      vector<MyGenMET>   *genmet                   = NULL ;
   

      rootTree         -> SetBranchAddress("offlinePrimaryVertices",&vertex);
      rootTree         -> SetBranchAddress("EvtId",&evtid);
      rootTree         -> SetBranchAddress("L1Trig",&l1trig);
      rootTree         -> SetBranchAddress("HLTrig",&hltrig);
      rootTree         -> SetBranchAddress("GenKin",&genkin);
      rootTree         -> SetBranchAddress("GenPart",&genpart);
      rootTree         -> SetBranchAddress("GenElec",&genelec);
      rootTree         -> SetBranchAddress("GenMu",&genmu);
 //   rootTree         -> SetBranchAddress("GenNu",&gennu);
 //   rootTree         -> SetBranchAddress("ak5CaloJets",&ak5calojets);
      rootTree         -> SetBranchAddress("ak5PFJets",&ak5pfjets);
 //   rootTree         -> SetBranchAddress("ak5TrackJets",&ak5trackjets);
 //   rootTree         -> SetBranchAddress("iterativeCone5CaloJets",&iterativecone5calojets);
 //   rootTree         -> SetBranchAddress("iterativeCone5PFJets",&iterativecone5pfjets);
 //   rootTree         -> SetBranchAddress("iterativeCone5TrackJets",&iterativecone5trackjets);
 //   rootTree         -> SetBranchAddress("sisCone5CaloJets",&siscone5calojets);
 //   rootTree         -> SetBranchAddress("sisCone5PFJets",&siscone5pfjets);
 //   rootTree         -> SetBranchAddress("sisCone5TrackJets",&siscone5trackjets);
     rootTree         -> SetBranchAddress("gsfElectrons",&electrons_raw);
     rootTree         -> SetBranchAddress("muons",&muons_raw);
 //   rootTree         -> SetBranchAddress("met",&calomet);
     rootTree         -> SetBranchAddress("tcMet",&tcmet);
 //   rootTree	     -> SetBranchAddress("pfMet",&pfmet);
     rootTree	     -> SetBranchAddress("genMetTrue",&genmet);
    
    
    
   
    for(int i = 0; i < nev; i++){
      
      
      if(ntot%20000==0)cout<<"event number "<<ntot<<endl;
      ntot++;
      
      rootTree->GetEvent(i);  
    
   //   if(ApplyPreselectionBeforeHLT) PreselectionMarker = evtid  -> PreselMarker;
      
    //  if(ApplyKfactor=="YES")        kfactor            = genkin -> kfactor;
      weight=kfactor;
      weight*=DataSampleWeight;    //have to run once to get this
      nevanalyzed += weight;
      
      bool leptonic = false;   
      string fs;
      int ne =0;
      int nm =0;
      int nt =0;
      
        /*
       cout<<"name      : "<<itgen->name    <<endl;
       cout<<"pdgID     : "<<itgen->pdgId   <<endl;
       cout<<"status    : "<<itgen->status    <<endl;
       cout<<"uniqueId  : "<<itgen->fUniqueID <<endl;
       cout<<"mother1   : "<<itgen->mo1     <<endl;
       cout<<"mother2   : "<<itgen->mo2   <<endl;
       cout<<"daughter1 : "<<itgen->da1   <<endl;
       cout<<"daughter2 : "<<itgen->da2   <<endl;
       cout<<"mass      : "<<itgen->m       <<endl;
       cout<<"eta       : "<<itgen->eta     <<endl;
       cout<<"y         : "<<Y              <<endl;
       cout<<"pt        : "<<itgen->pt      <<endl;
       cout<<"e         : "<<itgen->e       <<endl;
       cout<<"p         : "<<P              <<endl;
       cout<<"px        : "<<itgen->px      <<endl;
       cout<<"py        : "<<itgen->py      <<endl;
       cout<<"pz        : "<<itgen->pz      <<endl;
       cout<<"                            "<<endl;
       cout<<" ---------------------------"<<endl;
       cout<<"                            "<<endl;*/
    
   //    vector<MyGenPart*> *genmuons_I             = new vector<MyGenPart*>();
   //    vector<MyGenPart*> *genelectrons_I         = new vector<MyGenPart*>();
    
    
       for(vector<MyGenPart>::iterator itgen=genpart->begin();itgen!=genpart->end();itgen++){
         
	 
	 if(fabs(itgen->pdgId) == 11) ne++;
         if(fabs(itgen->pdgId) == 13) nm++;
         if(fabs(itgen->pdgId) == 15) nt++;
	 }
	
       
       if( ne == 2 )                  {fs="ee";leptonic = true;}
       if( nm == 2 )                  {fs="mm";leptonic = true;}
       if( nt == 2 )                  {fs="tt";leptonic = true;}
       if( ne == 1 && nm ==1 )        {fs="em";leptonic = true;}
       if( ne == 1 && nt ==1 )        {fs="et";leptonic = true;}
       if( nm == 1 && nt ==1 )        {fs="mt";leptonic = true;}
       if( !leptonic ) fs="nl"; 
    //   cout << ne << " " <<nm<<" "<<nt<< " leptonic "<<leptonic<<endl;
      
      
      
      
      
       // ------------ GenMet definition --------------------------  
	  
	double genMet=0;
	double genMetPhi=0;
	double genMetx=0;
	double genMety=0;
	for(vector<MyGenMET>::iterator itmet=genmet->begin();itmet!=genmet->end();itmet++){
	   genMet=itmet->pt;
	   genMetPhi=itmet->phi;
	   genMetx=itmet->pt * cos(itmet->phi);
	   genMety=itmet->pt * sin(itmet->phi);
	   }
      
      
      /// ----------------   Make Gen LeptonPairs ----------------------------
   //   if(fs=="ee"){
   //   cout<<"-------------------------------------------"<<endl;
  //    cout<<" electron vector size "<<genelec->size()<<endl;
      
      vector<GenLeptonPair*> *genLeptonPair_nocut       = new vector<GenLeptonPair*>;
      vector<GenLeptonPair*> *genLeptonPair_pteta       = new vector<GenLeptonPair*>;
      
      vector<MyGenPart*> *genmuons_nocut             = new vector<MyGenPart*>();
      vector<MyGenPart*> *genmuons_pteta             = new vector<MyGenPart*>();
      
      vector<MyGenPart*> *genelectrons_nocut         = new vector<MyGenPart*>();
      vector<MyGenPart*> *genelectrons_pteta         = new vector<MyGenPart*>();
      
      *genmuons_nocut           = GenPartFilter(*genmu,true,false,13,10,2.4);
      *genmuons_pteta           = GenPartFilter(*genmu,true,true ,13,10,2.4);
      
      *genelectrons_nocut       = GenPartFilter(*genelec,true,false,11,10,2.5);
      *genelectrons_pteta       = GenPartFilter(*genelec,true,true ,11,10,2.5);
      
      genLeptonPair_nocut        = MakeGenLeptonPairVector(*genelectrons_nocut,*genmuons_nocut,fs);
      genLeptonPair_pteta        = MakeGenLeptonPairVector(*genelectrons_pteta,*genmuons_pteta,fs);
      
       
      GenLeptonPair *bestGenPair_nocut = new GenLeptonPair;
      GenLeptonPair *bestGenPair_pteta = new GenLeptonPair;
      
      
       bestGenPair_nocut = findBestGenPair(*genLeptonPair_nocut);
       bestGenPair_pteta = findBestGenPair(*genLeptonPair_pteta);
   
   
   
       if( bestGenPair_nocut->type =="ee" && leptonic)   genpair_ee_nocut     -> fill(*bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="mm" && leptonic)   genpair_mm_nocut     -> fill(*bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="em" && leptonic)   genpair_em_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="me" && leptonic)   genpair_me_nocut     -> fill(*bestGenPair_nocut,genMet,genMetPhi,weight );
      if((bestGenPair_nocut->type =="em" ||  
          bestGenPair_nocut->type =="me") && leptonic)  genpair_mixed_nocut  -> fill(*bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type !="none" && leptonic) genpair_all_nocut    -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight);
    
      
      if( bestGenPair_nocut->type =="ee" && (fs=="tt" || fs=="et" || fs=="mt") )   genpair_ee_fromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="mm" && (fs=="tt" || fs=="et" || fs=="mt") )   genpair_mm_fromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="em" && (fs=="tt" || fs=="et" || fs=="mt") )   genpair_em_fromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="me" && (fs=="tt" || fs=="et" || fs=="mt") )   genpair_me_fromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if((bestGenPair_nocut->type =="em" ||  bestGenPair_nocut->type =="me") 
       && (fs=="tt" || fs=="et" || fs=="mt"))                                      genpair_mixed_fromtau_nocut  -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type !="none" &&  leptonic && (fs=="tt" || fs=="et" || fs=="mt") )   genpair_all_fromtau_nocut   -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
   
      
      
      if( bestGenPair_nocut->type =="ee" && !(fs=="tt" || fs=="et" || fs=="mt") && leptonic)    genpair_ee_nofromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="mm" && !(fs=="tt" || fs=="et" || fs=="mt") && leptonic )   genpair_mm_nofromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="em" && !(fs=="tt" || fs=="et" || fs=="mt") )               genpair_em_nofromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type =="me" && !(fs=="tt" || fs=="et" || fs=="mt") )               genpair_me_nofromtau_nocut     -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if((bestGenPair_nocut->type =="em" || bestGenPair_nocut->type =="me") 
       && !(fs=="tt" || fs=="et" || fs=="mt") && leptonic)                                      genpair_mixed_nofromtau_nocut  -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
      if( bestGenPair_nocut->type !="none" && leptonic && !(fs=="tt" || fs=="et" || fs=="mt") )                                     genpair_all_nofromtau_nocut   -> fill( *bestGenPair_nocut,genMet,genMetPhi,weight );
   
  
      if( bestGenPair_pteta->type =="ee" && leptonic)                                           genpair_ee_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="mm" && leptonic)                                           genpair_mm_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="em" && leptonic)                                           genpair_em_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="me" && leptonic)                                           genpair_me_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if((bestGenPair_pteta->type =="em" ||  
          bestGenPair_pteta->type =="me") && leptonic)                                          genpair_mixed_pteta  -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if(  bestGenPair_pteta->type !="none" && leptonic)                                        genpair_all_pteta    -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
    
      
      if( bestGenPair_pteta->type =="ee" && (fs=="tt" || fs=="et" || fs=="mt") )                 genpair_ee_fromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="mm" && (fs=="tt" || fs=="et" || fs=="mt") )                 genpair_mm_fromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="em" && (fs=="tt" || fs=="et" || fs=="mt") )                 genpair_em_fromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="me" && (fs=="tt" || fs=="et" || fs=="mt") )                 genpair_me_fromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if((bestGenPair_pteta->type =="em" ||  bestGenPair_pteta->type =="me") 
       && (fs=="tt" || fs=="et" || fs=="mt"))                                                    genpair_mixed_fromtau_pteta  -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type !="none" && leptonic && (fs=="tt" || fs=="et" || fs=="mt") )                                       genpair_all_fromtau_pteta    -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
   
      
      
      if( bestGenPair_pteta->type =="ee" && !(fs=="tt" || fs=="et" || fs=="mt") && leptonic)     genpair_ee_nofromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="mm" && !(fs=="tt" || fs=="et" || fs=="mt") && leptonic )    genpair_mm_nofromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="em" && !(fs=="tt" || fs=="et" || fs=="mt") )                genpair_em_nofromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type =="me" && !(fs=="tt" || fs=="et" || fs=="mt") )                genpair_me_nofromtau_pteta     -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if((bestGenPair_pteta->type =="em" || bestGenPair_pteta->type =="me") 
       && !(fs=="tt" || fs=="et" || fs=="mt") && leptonic)                                       genpair_mixed_nofromtau_pteta  -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
      if( bestGenPair_pteta->type !="none" && leptonic && !(fs=="tt" || fs=="et" || fs=="mt") )  genpair_all_nofromtau_pteta    -> fill( *bestGenPair_pteta,genMet,genMetPhi,weight );
   
 
      
      
      // ------vector<MyMuon*> *muons       = new vector<MyMuon*>();------- DATA  ------Event Selection ------------------
        
       int vtxId = getBestVertex(vertex);
    
       
       
       // -------- Trigger Count ------------------------
       
       if(hltrig->HLTmap["HLT_L1MuOpen"])          HLT_L1MuOpen+=weight;
       if(hltrig->HLTmap["HLT_L1Mu"])              HLT_L1Mu+=weight;
       if(hltrig->HLTmap["HLT_Mu5"])               HLT_Mu5+=weight;
       if(hltrig->HLTmap["HLT_Mu9"])               HLT_Mu9+=weight;
       if(hltrig->HLTmap["HLT_L1DoubleMuOpen"])    HLT_L1DoubleMuOpen+=weight;
       if(hltrig->HLTmap["HLT_DoubleMu0"])         HLT_DoubleMu0+=weight;
       if(hltrig->HLTmap["HLT_DoubleMu3"])         HLT_DoubleMu3+=weight;
       if(hltrig->HLTmap["HLT_L1SingleEG5"])       HLT_L1SingleEG5+=weight;
    //   if(hltrig->HLTmap["HLT_Ele15_SW_EleId_L1R"])HLT_Ele15_SW_EleId_L1R+=weight;
       if(hltrig->HLTmap["HLT_Ele15_LW_L1R"])      HLT_Ele15_LW_L1R+=weight;
       if(hltrig->HLTmap["HLT_Ele15_SiStrip_L1R"]) HLT_Ele15_SiStrip_L1R +=weight;
       
       
       if(l1trig->L1map["L1_SingleMuOpen"]) L1_SingleMuOpen+=weight;
       if(l1trig->L1map["L1_SingleMu0*muons_ptEta = MuonFilter(*muons,vtxId, true, false, false, false);"])    L1_SingleMu0+=weight;
       if(l1trig->L1map["L1_SingleMu3"])    L1_SingleMu3+=weight;
       if(l1trig->L1map["L1_SingleMu7"])    L1_SingleMu7+=weight;
       if(l1trig->L1map["L1_SingleMu20"])   L1_SingleMu20+=weight;
       if(l1trig->L1map["L1_DoubleMu3"])    L1_DoubleMu3+=weight;
       if(l1trig->L1map["L1_DoubleMuOpen"]) L1_DoubleMuOpen+=weight;
       if(l1trig->L1map["L1_SingleEG1"])    L1_SingleEG1+=weight;
       if(l1trig->L1map["L1_SingleEG2"])    L1_SingleEG2+=weight;
       if(l1trig->L1map["L1_SingleEG5"])    L1_SingleEG5+=weight;
       if(l1trig->L1map["L1_SingleEG8"])    L1_SingleEG8+=weight;
       if(l1trig->L1map["L1_SingleEG20"])   L1_SingleEG20+=weight;
       if(l1trig->L1map["L1_DoubleEG5"])    L1_DoubleEG5+=weight;
       
       // ---------- Make lepton preselection collection --------------------
       
       
       vector<MyMuon*> *muons_pt5                      = new vector<MyMuon*>();
       vector<MyMuon*> *muons_pt10                     = new vector<MyMuon*>();
       vector<MyElectron*> *electrons_bfmcl_pt5        = new vector<MyElectron*>();
       vector<MyElectron*> *electrons_bfmcl_pt10       = new vector<MyElectron*>();
	       
       *muons_pt5                  = MuonFilter(*muons_raw,vtxId, true , false, false, false,5);
       *muons_pt10                 = MuonFilter(*muons_raw,vtxId, true , false, false, false,10);
       *electrons_bfmcl_pt5        = ElectronFilter(*electrons_raw,vtxId, true , false, false, false, false,0,5);
       *electrons_bfmcl_pt10       = ElectronFilter(*electrons_raw,vtxId, true , false, false, false, false,0,10);
	      
       vector<LeptonPair*> *pair_pt5   = new vector<LeptonPair*>;
       vector<LeptonPair*> *pair_pt10  = new vector<LeptonPair*>;
         
       pair_pt5   = MakeLeptonPairVector(*electrons_bfmcl_pt5, *muons_pt5);
       pair_pt10  = MakeLeptonPairVector(*electrons_bfmcl_pt10,*muons_pt10);
         
       if( muons_pt5            -> size() > 0) nmu5     += weight;
       if( muons_pt10           -> size() > 0) nmu10    += weight;
       if( electrons_bfmcl_pt5  -> size() > 0) nel5     += weight;
       if( electrons_bfmcl_pt10 -> size() > 0) nel10    += weight;
       if( pair_pt5             -> size() > 0) npair5   += weight;
       if( pair_pt10            -> size() > 0) npair10  += weight;
       
       
       
       // --------  Trigger Requirements ---------------------------
       
       bool hltok=false;
       
       if(hltrig->HLTmap["HLT_Mu9"] || hltrig->HLTmap["HLT_Ele15_LW_L1R"])hltok=true;   //loose HLT for now ...
      
          if(hltok){
	    hltpassed += weight;
       
            // ----------Make Muon Collection ---------------
            
	    vector<MyMuon*> *muons       = new vector<MyMuon*>();
	    vector<MyMuon*> *muons_ptEta = new vector<MyMuon*>();
            vector<MyMuon*> *muons_d0    = new vector<MyMuon*>();
            vector<MyMuon*> *muons_iso   = new vector<MyMuon*>();
            vector<MyMuon*> *muons_id    = new vector<MyMuon*>();
        
            
	    *muons       = MuonFilter(*muons_raw,vtxId, false, false, false, false);
	    *muons_ptEta = MuonFilter(*muons,vtxId, true, false, false, false);
            *muons_d0    = MuonFilter(*muons,vtxId, true, true, false, false);
            *muons_iso   = MuonFilter(*muons,vtxId, true, true, true, false);
            *muons_id    = MuonFilter(*muons,vtxId, true, true, true, true);
         
	 
	 
	 
	   
       
            //------------- Make Electrons collections ------------------------
       
            vector<MyElectron*> *electrons_bfmcl            = new vector<MyElectron*>();
	    vector<MyElectron*> *electrons_ptEta_bfmcl      = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_d0_bfmcl         = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_iso_all_bfmcl    = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_iso_barrel_bfmcl = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_iso_endcap_bfmcl = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_id_all_bfmcl     = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_id_barrel_bfmcl  = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_id_endcap_bfmcl  = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_conversion_bfmcl = new vector<MyElectron*>();
            
	    *electrons_bfmcl            = ElectronFilter(*electrons_raw,vtxId, false, false, false, false, false,0);
	    *electrons_ptEta_bfmcl      = ElectronFilter(*electrons_raw,vtxId, true, false, false, false, false,0);
            *electrons_d0_bfmcl         = ElectronFilter(*electrons_raw,vtxId, true, true, false, false, false,0);
            *electrons_iso_all_bfmcl    = ElectronFilter(*electrons_raw,vtxId, true, true, true, false, false,0);
            *electrons_iso_barrel_bfmcl = ElectronFilter(*electrons_raw,vtxId, true, true, true, false, false,1);
            *electrons_iso_endcap_bfmcl = ElectronFilter(*electrons_raw,vtxId, true, true, true, false, false,2);
            *electrons_id_all_bfmcl     = ElectronFilter(*electrons_raw,vtxId, true, true, true, true, false,0);
            *electrons_id_barrel_bfmcl  = ElectronFilter(*electrons_raw,vtxId, true, true, true, true, false,1);
            *electrons_id_endcap_bfmcl  = ElectronFilter(*electrons_raw,vtxId, true, true, true, true, false,2);
            *electrons_conversion_bfmcl = ElectronFilter(*electrons_raw,vtxId, true, true, true, true, true,0);
          
	    // ---------- Remove Muon Overlap -------------------
	    
	    vector<MyElectron*> *electrons            = new vector<MyElectron*>();
	    vector<MyElectron*> *electrons_ptEta      = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_d0         = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_iso_all    = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_iso_barrel = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_iso_endcap = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_id_all     = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_id_barrel  = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_id_endcap  = new vector<MyElectron*>();
            vector<MyElectron*> *electrons_conversion = new vector<MyElectron*>();
       
	    
	    *electrons              = ElectronsCleaning(*electrons_bfmcl           , *muons);
	    *electrons_ptEta        = ElectronsCleaning(*electrons_ptEta_bfmcl     , *muons_ptEta);
            *electrons_d0           = ElectronsCleaning(*electrons_d0_bfmcl        , *muons_d0);
            *electrons_iso_all      = ElectronsCleaning(*electrons_iso_all_bfmcl   , *muons_iso);
            *electrons_iso_barrel   = ElectronsCleaning(*electrons_iso_barrel_bfmcl, *muons_iso);
            *electrons_iso_endcap   = ElectronsCleaning(*electrons_iso_endcap_bfmcl, *muons_iso);
            *electrons_id_all       = ElectronsCleaning(*electrons_id_all_bfmcl    , *muons_id);
            *electrons_id_barrel    = ElectronsCleaning(*electrons_id_barrel_bfmcl , *muons_id);
            *electrons_id_endcap    = ElectronsCleaning(*electrons_id_endcap_bfmcl , *muons_id);
            *electrons_conversion   = ElectronsCleaning(*electrons_conversion_bfmcl, *muons_id);
	    
	    
	    
	    //------------- Make Electrons Control Plots ------------------------
       
           
       
             electrons_noCut      -> fill(*electrons, weight, vtxId);
             electrons_PtEtaCut   -> fill(*electrons_ptEta, weight, vtxId);
             electrons_d0Cut      -> fill(*electrons_d0, weight, vtxId);
             electrons_IsoCut_all   -> fill(*electrons_iso_all, weight, vtxId);
             electrons_IsoCut_barrel   -> fill(*electrons_iso_barrel, weight, vtxId);
             electrons_IsoCut_endcap   -> fill(*electrons_iso_endcap, weight, vtxId);
             electrons_IdCut_all       -> fill(*electrons_id_all, weight, vtxId);
             electrons_IdCut_barrel   -> fill(*electrons_id_barrel, weight, vtxId);
             electrons_IdCut_endcap   -> fill(*electrons_id_endcap, weight, vtxId);
             electrons_ConversionCut   -> fill(*electrons_conversion, weight, vtxId);
     
            
           //------------- Make Muon Control Plots ------------------------
       
          
            muons_noCut    -> fill(*muons,weight,vtxId);
            muons_PtEtaCut -> fill(*muons_ptEta, weight, vtxId);
            muons_d0Cut    -> fill(*muons_d0, weight, vtxId);
            muons_IsoCut   -> fill(*muons_iso, weight, vtxId);
            muons_IdCut    -> fill(*muons_id, weight, vtxId);
       
      
          
	   // ------Lepton Pairs Creations --------------------------
      
      
       
          vector<LeptonPair*> *pair_noCut = new vector<LeptonPair*>;
          vector<LeptonPair*> *pair_ptEta = new vector<LeptonPair*>;
          vector<LeptonPair*> *pair_d0    = new vector<LeptonPair*>;
          vector<LeptonPair*> *pair_iso   = new vector<LeptonPair*>;
          vector<LeptonPair*> *pair_id    = new vector<LeptonPair*>;
          vector<LeptonPair*> *pair_conv  = new vector<LeptonPair*>;
      
         
          pair_noCut = MakeLeptonPairVector(*electrons_bfmcl, *muons);
          pair_ptEta = MakeLeptonPairVector(*electrons_ptEta_bfmcl, *muons_ptEta);
          pair_d0    = MakeLeptonPairVector(*electrons_d0_bfmcl , *muons_d0);
          pair_iso   = MakeLeptonPairVector(*electrons_iso_all_bfmcl , *muons_iso);
          pair_id    = MakeLeptonPairVector(*electrons_id_all_bfmcl , *muons_id);
          pair_conv  = MakeLeptonPairVector(*electrons_conversion_bfmcl , *muons_id);
      
          vector<LeptonPair*> *pair_mll1 = new vector<LeptonPair*>;
	  vector<LeptonPair*> *pair_mll2 = new vector<LeptonPair*>;
	  vector<LeptonPair*> *pair_pmet = new vector<LeptonPair*>;
	  
	   
	  vector<MyMuon*>     *extrasoftmuons_ee = new vector<MyMuon*>;
	  vector<MyMuon*>     *extrasoftmuons_mm = new vector<MyMuon*>;
	  vector<MyMuon*>     *extrasoftmuons_em = new vector<MyMuon*>;
	  vector<MyMuon*>     *extrasoftmuons_me = new vector<MyMuon*>;
	   
	  vector<MyMuon*>     *extramuons_ee      = new vector<MyMuon*>();
	  vector<MyMuon*>     *extramuons_mm      = new vector<MyMuon*>();
	  vector<MyMuon*>     *extramuons_em      = new vector<MyMuon*>();
	  vector<MyMuon*>     *extramuons_me      = new vector<MyMuon*>();
	   
	  vector<MyElectron*> *extraelectrons_ee   = new vector<MyElectron*>();
	  vector<MyElectron*> *extraelectrons_mm   = new vector<MyElectron*>();
	  vector<MyElectron*> *extraelectrons_em   = new vector<MyElectron*>();
	  vector<MyElectron*> *extraelectrons_me   = new vector<MyElectron*>();
	  
		  
	// ------------ Met definition --------------------------  
	  
	   double tcMet=0;
	   double tcMetPhi=0;
	   double tcMetx=0;
	   double tcMety=0;
	   for(vector<MyMET>::iterator itmet=tcmet->begin();itmet!=tcmet->end();itmet++){
	      tcMet=itmet->pt;
	      tcMetPhi=itmet->phi;
	      tcMetx=itmet->pt * cos(itmet->phi);
	      tcMety=itmet->pt * sin(itmet->phi);
	      }
	  
	  
	  
	  // ------- LeptonPair Plots ------------------------  
	  
	  
	  LeptonPair *bestPair_nocut = new LeptonPair;
          LeptonPair *bestPair_pteta = new LeptonPair;
          LeptonPair *bestPair_d0    = new LeptonPair;
          LeptonPair *bestPair_iso   = new LeptonPair;
          LeptonPair *bestPair_id    = new LeptonPair;
          LeptonPair *bestPair_conv  = new LeptonPair;
         
	  bestPair_nocut   = findBestPair(*pair_noCut);
          bestPair_pteta   = findBestPair(*pair_ptEta);
          bestPair_d0      = findBestPair(*pair_d0);
          bestPair_iso     = findBestPair(*pair_iso);
          bestPair_id      = findBestPair(*pair_id);
          bestPair_conv    = findBestPair(*pair_conv);
          
	  
	  if( bestPair_nocut->type =="ee" )   pair_noCut_ee     -> fill( *bestPair_nocut,tcMet,tcMetPhi,weight );
          if( bestPair_nocut->type =="em" )   pair_noCut_em     -> fill( *bestPair_nocut,tcMet,tcMetPhi,weight );
          if( bestPair_nocut->type =="me" )   pair_noCut_me     -> fill( *bestPair_nocut,tcMet,tcMetPhi,weight );
          if( bestPair_nocut->type =="mm" )   pair_noCut_mm     -> fill( *bestPair_nocut,tcMet,tcMetPhi,weight );
          if( bestPair_nocut->type =="em" 
	   || bestPair_nocut->type =="me" )   pair_noCut_mixed  -> fill( *bestPair_nocut,tcMet,tcMetPhi,weight );
          if( bestPair_nocut->type !="none" )   pair_noCut_all     -> fill( *bestPair_nocut,tcMet,tcMetPhi,weight );
          
	  
	  if( bestPair_pteta->type =="ee" )   pair_ptEtaCut_ee     -> fill( *bestPair_pteta,tcMet,tcMetPhi,weight );
          if( bestPair_pteta->type =="em" )   pair_ptEtaCut_em     -> fill( *bestPair_pteta,tcMet,tcMetPhi,weight );
          if( bestPair_pteta->type =="me" )   pair_ptEtaCut_me     -> fill( *bestPair_pteta,tcMet,tcMetPhi,weight );
          if( bestPair_pteta->type =="mm" )   pair_ptEtaCut_mm     -> fill( *bestPair_pteta,tcMet,tcMetPhi,weight );
          if( bestPair_pteta->type =="em" 
	   || bestPair_pteta->type =="me" )   pair_ptEtaCut_mixed  -> fill( *bestPair_pteta,tcMet,tcMetPhi,weight );
          if( bestPair_pteta->type !="none" ) pair_ptEtaCut_all    -> fill( *bestPair_pteta,tcMet,tcMetPhi,weight );
          
	  
	  if( bestPair_d0->type =="ee" )   pair_d0Cut_ee     -> fill( *bestPair_d0,tcMet,tcMetPhi,weight );
          if( bestPair_d0->type =="em" )   pair_d0Cut_em     -> fill( *bestPair_d0,tcMet,tcMetPhi,weight );
          if( bestPair_d0->type =="me" )   pair_d0Cut_me     -> fill( *bestPair_d0,tcMet,tcMetPhi,weight );
          if( bestPair_d0->type =="mm" )   pair_d0Cut_mm     -> fill( *bestPair_d0,tcMet,tcMetPhi,weight );
          if( bestPair_d0->type =="em" 
	   || bestPair_d0->type =="me" )   pair_d0Cut_mixed  -> fill( *bestPair_d0,tcMet,tcMetPhi,weight );
          if( bestPair_d0->type !="none" ) pair_d0Cut_all    -> fill( *bestPair_d0,tcMet,tcMetPhi,weight );
          
	  
	  
	  if( bestPair_iso->type =="ee" )   pair_IsoCut_ee     -> fill( *bestPair_iso,tcMet,tcMetPhi,weight );
          if( bestPair_iso->type =="em" )   pair_IsoCut_em     -> fill( *bestPair_iso,tcMet,tcMetPhi,weight );
          if( bestPair_iso->type =="me" )   pair_IsoCut_me     -> fill( *bestPair_iso,tcMet,tcMetPhi,weight );
          if( bestPair_iso->type =="mm" )   pair_IsoCut_mm     -> fill( *bestPair_iso,tcMet,tcMetPhi,weight );
          if( bestPair_iso->type =="em" 
	   || bestPair_iso->type =="me" )   pair_IsoCut_mixed  -> fill( *bestPair_iso,tcMet,tcMetPhi,weight );
          if( bestPair_iso->type !="none" ) pair_IsoCut_all    -> fill( *bestPair_iso,tcMet,tcMetPhi,weight );
          
	  
	  if( bestPair_id->type =="ee" )   pair_IdCut_ee     -> fill( *bestPair_id,tcMet,tcMetPhi,weight );
          if( bestPair_id->type =="em" )   pair_IdCut_em     -> fill( *bestPair_id,tcMet,tcMetPhi,weight );
          if( bestPair_id->type =="me" )   pair_IdCut_me     -> fill( *bestPair_id,tcMet,tcMetPhi,weight );
          if( bestPair_id->type =="mm" )   pair_IdCut_mm     -> fill( *bestPair_id,tcMet,tcMetPhi,weight );
          if( bestPair_id->type =="em" 
	   || bestPair_id->type =="me" )   pair_IdCut_mixed  -> fill( *bestPair_id,tcMet,tcMetPhi,weight );
          if( bestPair_id->type !="none" ) pair_IdCut_all    -> fill( *bestPair_id,tcMet,tcMetPhi,weight );
         
	  
	  
	  if( bestPair_conv->type =="ee" )   pair_ConvCut_ee     -> fill( *bestPair_conv,tcMet,tcMetPhi,weight );
          if( bestPair_conv->type =="em" )   pair_ConvCut_em     -> fill( *bestPair_conv,tcMet,tcMetPhi,weight );
          if( bestPair_conv->type =="me" )   pair_ConvCut_me     -> fill( *bestPair_conv,tcMet,tcMetPhi,weight );
          if( bestPair_conv->type =="mm" )   pair_ConvCut_mm     -> fill( *bestPair_conv,tcMet,tcMetPhi,weight );
          if( bestPair_conv->type =="em" 
	   || bestPair_conv->type =="me" )   pair_ConvCut_mixed  -> fill( *bestPair_conv,tcMet,tcMetPhi,weight );
          if( bestPair_id->type !="none" )   pair_ConvCut_all    -> fill( *bestPair_conv,tcMet,tcMetPhi,weight );
         
	
	
	
	
	
	  
	  //-------------- Prepare Jet Collection------------------------------
	  
	  vector<MyJet*> *jetsCleaned = new vector<MyJet*>();
	  *jetsCleaned = makeJetCleaning(*ak5pfjets,*electrons_conversion_bfmcl,*muons_id, 20, 3, 0.3);
	
	  
	  
	  
	  // ------ Pt, Eta, Opposite charge requirement ------------------
      
          if( pair_ptEta->size() > 0 ){
              
	      pteta_passed_all += weight;
	      if( find(*pair_ptEta,"ee") )                           pteta_passed_ee += weight;
	      if( find(*pair_ptEta,"mm") )                           pteta_passed_mm += weight;
	      if( find(*pair_ptEta,"em") )                           pteta_passed_em += weight;
	      if( find(*pair_ptEta,"me") )                           pteta_passed_me += weight;
	      if( find(*pair_ptEta,"em") || find(*pair_ptEta,"me") ) pteta_passed_mixed += weight;
	      
	      // ------ d0 requirement ------------------
      
              if( pair_d0->size() > 0 ){
              
	         d0_passed_all += weight;
	         if( find(*pair_d0,"ee") )                         d0_passed_ee += weight;
	         if( find(*pair_d0,"mm") )                         d0_passed_mm += weight;
	         if( find(*pair_d0,"em") )                         d0_passed_em += weight;
	         if( find(*pair_d0,"me") )                         d0_passed_me += weight;
	         if( find(*pair_d0,"em") || find(*pair_d0,"me") )  d0_passed_mixed += weight;  
	     
	         // ------ iso requirement ------------------
      
                 if( pair_iso->size() > 0 ){
              
	            iso_passed_all += weight;
	            if( find(*pair_iso,"ee") )                          iso_passed_ee += weight;
          	    if( find(*pair_iso,"mm") )                          iso_passed_mm += weight;
	            if( find(*pair_iso,"em") )                          iso_passed_em += weight;
	            if( find(*pair_iso,"me") )                          iso_passed_me += weight;
	            if( find(*pair_iso,"em") || find(*pair_iso,"me") )  iso_passed_mixed += weight;  
	     
	            // ------ id requirement ------------------
      
                    if( pair_id->size() > 0 ){
              
	               id_passed_all += weight;
	               if( find(*pair_id,"ee") )                          id_passed_ee += weight;
	               if( find(*pair_id,"mm") )                          id_passed_mm += weight;
	               if( find(*pair_id,"em") )                          id_passed_em += weight;
	               if( find(*pair_id,"me") )                          id_passed_me += weight;
	               if( find(*pair_id,"em") || find(*pair_id,"me") )   id_passed_mixed += weight;  
	     
	               // ------ conv requirement ------------------
      
                       if( pair_conv->size() > 0 ){
              
	                  conv_passed_all += weight;
	                  if( find(*pair_conv,"ee") )                            conv_passed_ee += weight;
	                  if( find(*pair_conv,"mm") )                            conv_passed_mm += weight;
	                  if( find(*pair_conv,"em") )                            conv_passed_em += weight;
	                  if( find(*pair_conv,"me") )                            conv_passed_me += weight;
	                  if( find(*pair_conv,"em") || find(*pair_conv,"me") )   conv_passed_mixed += weight;  
	     
	                 
			  // ------------ MEt cut -------------------
			 
			 
			  if ( tcMet > 20 ){
			      
			      met_passed_all += weight;
	                      if( find(*pair_conv,"ee") )                            met_passed_ee += weight;
	                      if( find(*pair_conv,"mm") )                            met_passed_mm += weight;
	                      if( find(*pair_conv,"em") )                            met_passed_em += weight;
	                      if( find(*pair_conv,"me") )                            met_passed_me += weight;
	                      if( find(*pair_conv,"em") || find(*pair_conv,"me") )   met_passed_mixed += weight;  
			 
			     
			      *pair_mll1 = makeMllCut1(*pair_conv);
			 
			     
			      // ------- Mll cut # -------------------------------------
			     
			      if ( pair_mll1->size() > 0  ){
			          
				  mll1_passed_all += weight;
	                          if( find(*pair_mll1,"ee") )                            mll1_passed_ee += weight;
	                          if( find(*pair_mll1,"mm") )                            mll1_passed_mm += weight;
	                          if( find(*pair_mll1,"em") )                            mll1_passed_em += weight;
	                          if( find(*pair_mll1,"me") )                            mll1_passed_me += weight;
	                          if( find(*pair_mll1,"em") || find(*pair_mll1,"me") )   mll1_passed_mixed += weight;  
			      
			          
			          *pair_mll2 = makeMllCut2(*pair_mll1);
			      
			          // -------------- Mll cut-------------------------
				
				
				  if ( pair_mll2->size() > 0  ){
			          
				     mll2_passed_all += weight;
	                             if( find(*pair_mll2,"ee") )                            mll2_passed_ee    += weight;
	                             if( find(*pair_mll2,"mm") )                            mll2_passed_mm    += weight;
	                             if( find(*pair_mll2,"em") )                            mll2_passed_em    += weight;
	                             if( find(*pair_mll2,"me") )                            mll2_passed_me    += weight;
	                             if( find(*pair_mll2,"em") || find(*pair_mll2,"me") )   mll2_passed_mixed += weight;  
				      
				     
			             *pair_pmet = makeProjectedMetCut(*pair_mll2,tcMet,tcMetPhi);
				     
			            
				    // ----------------- Projected Met cut ----------------------------
				    
				     if ( pair_pmet->size() > 0  ){
			          
				        pmet_passed_all += weight;
	                                if( find(*pair_pmet,"ee") )                            pmet_passed_ee    += weight;
	                                if( find(*pair_pmet,"mm") )                            pmet_passed_mm    += weight;
	                                if( find(*pair_pmet,"em") )                            pmet_passed_em    += weight;
	                                if( find(*pair_pmet,"me") )                            pmet_passed_me    += weight;
	                                if( find(*pair_pmet,"em") || find(*pair_pmet,"me") )   pmet_passed_mixed += weight;  
			            
				    
				    
				        // ---------------- Jet Veto -------------------------------
				        
					 
					 if ( jetsCleaned -> size() ==0 ) {
                
					   jetveto_passed_all += weight;
	                                   if( find(*pair_pmet,"ee") )                               jetveto_passed_ee    += weight;
	                                   if( find(*pair_pmet,"mm") )                               jetveto_passed_mm    += weight;
	                                   if( find(*pair_pmet,"em") )                               jetveto_passed_em    += weight;
	                                   if( find(*pair_pmet,"me") )                               jetveto_passed_me    += weight;
	                                   if( find(*pair_pmet,"em") || find(*pair_pmet,"me") )      jetveto_passed_mixed += weight;  
					   
		 
					   
					   // -------------Soft Muon Veto --------------------------------
				           
					   
					   *extrasoftmuons_ee = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"ee");
					   *extrasoftmuons_mm = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"mm"); 
					   *extrasoftmuons_em = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"em"); 
					   *extrasoftmuons_me = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"me"); 
					 
 /* 
                                           if( (extrasoftmuons_em -> size() >0)  &&  find(*pair_pmet,"em")  ) {
				                 cout << " ===================== ExtraSofKilled ====================== " << endl;
                                                    cout << "pair_pmet size  = " <<   pair_pmet->size() << endl ;
                                                    for ( vector<LeptonPair*>::iterator itp = pair_pmet->begin() ; itp != pair_pmet->end() ; ++itp){ 
                                                       (*itp)->PrintPair(vtxId);
                                                    } 
                                                    cout << "extrasoft size =  " <<   extrasoftmuons_em->size() << endl ;
                                                    for(vector<MyMuon*>::iterator itm = extrasoftmuons_em->begin() ; itm != extrasoftmuons_em->end() ; ++itm){ 
                                                      cout << " Pt " <<  (*itm)->pt << endl; 
                                                      PrintRecoMuon(*itm ,vtxId );
                                                    }
                                            } 
*/
                                              
 
					    if((extrasoftmuons_ee -> size() ==0) || (extrasoftmuons_mm -> size() ==0) || (extrasoftmuons_em -> size() ==0) || (extrasoftmuons_me -> size() ==0) ){
					      
					      softmuons_passed_all += weight;
	                                      if(  (extrasoftmuons_ee -> size() ==0)  &&  find(*pair_pmet,"ee")  )           softmuons_passed_ee    += weight;
	                                      if(  (extrasoftmuons_mm -> size() ==0)  &&  find(*pair_pmet,"mm")  )           softmuons_passed_mm    += weight;
	                                      if(  (extrasoftmuons_em -> size() ==0)  &&  find(*pair_pmet,"em")  )          {softmuons_passed_em += weight; softmuons_passed_mixed += weight;}
	                                      if(  (extrasoftmuons_me -> size() ==0)  &&  find(*pair_pmet,"me")  )          {softmuons_passed_me += weight; softmuons_passed_mixed += weight;}
	                                    

					   
					     // ------------ extra lepton veto -------------------------
					     
					     
					    
		 			     *extramuons_ee           = ExtraMuons(*muons, *pair_pmet,vtxId,"ee");
					     *extramuons_mm           = ExtraMuons(*muons, *pair_pmet,vtxId,"mm");
					     *extramuons_em           = ExtraMuons(*muons, *pair_pmet,vtxId,"em");
					     *extramuons_me           = ExtraMuons(*muons, *pair_pmet,vtxId,"me");
					     
					     *extraelectrons_ee       = ExtraElectrons(*electrons,*pair_pmet, vtxId,"ee");
					     *extraelectrons_mm       = ExtraElectrons(*electrons,*pair_pmet, vtxId,"mm");
					     *extraelectrons_em       = ExtraElectrons(*electrons,*pair_pmet, vtxId,"em");
					     *extraelectrons_me       = ExtraElectrons(*electrons,*pair_pmet, vtxId,"me");
					     
					
					     if (   (extramuons_ee->size() == 0 && extraelectrons_ee->size() == 0) 
					         || (extramuons_mm->size() == 0 && extraelectrons_mm->size() == 0)
					         || (extramuons_em->size() == 0 && extraelectrons_em->size() == 0)
					         || (extramuons_me->size() == 0 && extraelectrons_me->size() == 0) )
					     
					        {
					     
					        extraleptons_passed_all += weight; D_all = weight*weight;
	                                        if( find(*pair_pmet,"ee") && (extramuons_ee->size() == 0 && extraelectrons_ee->size() == 0))   {extraleptons_passed_ee    += weight; D_ee += weight*weight;}
	                                        if( find(*pair_pmet,"mm") && (extramuons_mm->size() == 0 && extraelectrons_mm->size() == 0))   {extraleptons_passed_mm    += weight; D_mm += weight*weight;}
	                                        if( find(*pair_pmet,"em") && (extramuons_em->size() == 0 && extraelectrons_em->size() == 0))   {extraleptons_passed_em    += weight; D_em += weight*weight;}
	                                        if( find(*pair_pmet,"me") && (extramuons_me->size() == 0 && extraelectrons_me->size() == 0))   {extraleptons_passed_me    += weight; D_me += weight*weight;}
	                                        if( (find(*pair_pmet,"em") && (extramuons_em->size() == 0 && extraelectrons_em->size() == 0))
						  ||(find(*pair_pmet,"me") && (extramuons_me->size() == 0 && extraelectrons_me->size() == 0)) ){extraleptons_passed_mixed += weight; D_mixed += weight*weight;}   
						
						} // extra lepton veto
					     } // extra soft muon veto
					  } // jet veto  
				       }  // projected met cut
				    } // mll cut #2 
			         }  // mll cut #1
			     } // met cut 
			  }  // conversion requirment
	               } // id requirement
	            } // iso requirement 
	        }   // d0 requirement
	     }  // pt, eta , opposite charge cut
	  
	  
	  
	  
	  delete electrons;
	  delete electrons_ptEta;
          delete electrons_d0;
          delete electrons_iso_all;
          delete electrons_iso_barrel;
          delete electrons_iso_endcap;
          delete electrons_id_all;
          delete electrons_id_barrel;
          delete electrons_id_endcap;
          delete electrons_conversion;
          delete electrons_bfmcl;
          delete electrons_ptEta_bfmcl;
          delete electrons_d0_bfmcl;
          delete electrons_iso_all_bfmcl;
          delete electrons_iso_barrel_bfmcl;
          delete electrons_iso_endcap_bfmcl;
          delete electrons_id_all_bfmcl;
          delete electrons_id_barrel_bfmcl;
          delete electrons_id_endcap_bfmcl;
          delete electrons_conversion_bfmcl;
	  delete muons;
	  delete muons_ptEta;
          delete muons_d0;
          delete muons_iso;
          delete muons_id;
          delete pair_noCut;
          delete pair_ptEta;
          delete pair_d0;
          delete pair_iso;
          delete pair_id;
          delete pair_conv;
          delete jetsCleaned;
          delete pair_mll1;
          delete pair_mll2;
          delete pair_pmet;
          delete extrasoftmuons_ee;
          delete extrasoftmuons_mm;
	  delete extrasoftmuons_em;
	  delete extrasoftmuons_me;
	  delete extramuons_ee;
	  delete extramuons_mm;
	  delete extramuons_em;
	  delete extramuons_me;
	  delete extraelectrons_em;
	  delete extraelectrons_me;
	  delete extraelectrons_ee;
	  delete extraelectrons_mm;
	  delete bestPair_nocut ;
          delete bestPair_pteta ;
          delete bestPair_d0    ;
          delete bestPair_iso   ;
          delete bestPair_id    ;
          delete bestPair_conv  ;
         
	 
	  } // HLT requirement
      
      delete genLeptonPair_pteta;
      delete bestGenPair_pteta;
      
      delete muons_pt5;
      delete muons_pt10;
      delete electrons_bfmcl_pt5;
      delete electrons_bfmcl_pt10;
      delete pair_pt5;
      delete pair_pt10;
          
      
      }  //end event-loop
  
      
    delete rootTree;
    delete file;
   
   }  // close file
   
   nf++;
   
   TFile analysisfile(OutputRootFile.c_str(),"RECREATE");
   
   electrons_noCut           -> write();
   electrons_PtEtaCut        -> write();
   electrons_d0Cut           -> write();
   electrons_IsoCut_all      -> write();
   electrons_IsoCut_barrel   -> write();
   electrons_IsoCut_endcap   -> write();
   electrons_IdCut_all           -> write();
   electrons_IdCut_barrel        -> write();
   electrons_IdCut_endcap        -> write();
   electrons_ConversionCut  -> write();
   muons_noCut             -> write();
   muons_PtEtaCut          -> write();
   muons_d0Cut             -> write();
   muons_IsoCut            -> write();
   muons_IdCut             -> write();
   
  // pair_noCut_ee        ->write();
 //  pair_ptEtaCut_ee     ->write(); 
   
   genpair_ee_nocut ->write();
   genpair_mm_nocut ->write();
   genpair_em_nocut ->write();
   genpair_me_nocut ->write();
   genpair_mixed_nocut ->write();
   genpair_all_nocut ->write();
   genpair_ee_fromtau_nocut ->write();
   genpair_mm_fromtau_nocut ->write();
   genpair_em_fromtau_nocut ->write();
   genpair_me_fromtau_nocut ->write();
   genpair_mixed_fromtau_nocut ->write();
   genpair_all_fromtau_nocut ->write();
   genpair_ee_nofromtau_nocut ->write();
   genpair_mm_nofromtau_nocut ->write();
   genpair_em_nofromtau_nocut ->write();
   genpair_me_nofromtau_nocut ->write();
   genpair_mixed_nofromtau_nocut ->write();
   genpair_all_nofromtau_nocut ->write();
 
 
   genpair_ee_pteta ->write();
   genpair_mm_pteta ->write();
   genpair_em_pteta ->write();
   genpair_me_pteta ->write();
   genpair_mixed_pteta ->write();
   genpair_all_pteta ->write();
   genpair_ee_fromtau_pteta ->write();
   genpair_mm_fromtau_pteta ->write();
   genpair_em_fromtau_pteta ->write();
   genpair_me_fromtau_pteta ->write();
   genpair_mixed_fromtau_pteta ->write();
   genpair_all_fromtau_pteta ->write();
   genpair_ee_nofromtau_pteta ->write();
   genpair_mm_nofromtau_pteta ->write();
   genpair_em_nofromtau_pteta ->write();
   genpair_me_nofromtau_pteta ->write();
   genpair_mixed_nofromtau_pteta ->write();
   genpair_all_nofromtau_pteta ->write();
 


   pair_noCut_ee      -> write();
   pair_noCut_mm       -> write();
   pair_noCut_em       -> write();
   pair_noCut_me       -> write();
   pair_noCut_mixed    -> write();
   pair_noCut_all      -> write();
  
   pair_ptEtaCut_ee       -> write();
   pair_ptEtaCut_mm       -> write();
   pair_ptEtaCut_em       -> write();
   pair_ptEtaCut_me       -> write();
   pair_ptEtaCut_mixed    -> write();
   pair_ptEtaCut_all      -> write();
  
   pair_d0Cut_ee       -> write();
   pair_d0Cut_mm       -> write();
   pair_d0Cut_em       -> write();
   pair_d0Cut_me       -> write();
   pair_d0Cut_mixed    -> write();
   pair_d0Cut_all      -> write();
  
   pair_IsoCut_ee       -> write();
   pair_IsoCut_mm       -> write();
   pair_IsoCut_em       -> write();
   pair_IsoCut_me       -> write();
   pair_IsoCut_mixed    -> write();
   pair_IsoCut_all      -> write();

   pair_IdCut_ee       -> write();
   pair_IdCut_mm       -> write();
   pair_IdCut_em       -> write();
   pair_IdCut_me       -> write();
   pair_IdCut_mixed    -> write();
   pair_IdCut_all      -> write();

   pair_ConvCut_ee       -> write();
   pair_ConvCut_mm       -> write();
   pair_ConvCut_em       -> write();
   pair_ConvCut_me       -> write();
   pair_ConvCut_mixed    -> write();
   pair_ConvCut_all      -> write();











   delete electrons_noCut         ;
   delete electrons_PtEtaCut      ;
   delete electrons_d0Cut         ;
   delete electrons_IsoCut_all    ;
   delete electrons_IsoCut_barrel ;
   delete electrons_IsoCut_endcap ;
   delete electrons_IdCut_all     ;
   delete electrons_IdCut_barrel  ;
   delete electrons_IdCut_endcap  ;
   delete electrons_ConversionCut ;
   delete muons_noCut             ;
   delete muons_PtEtaCut          ;
   delete muons_d0Cut             ;
   delete muons_IsoCut            ;
   delete muons_IdCut            ;
   
  // delete pair_noCut_ee ;  
    

 
 
 
 
 
 
 
 
    
    cout << " ------------- Trigger efficiencies ------------------------"   << endl;
    cout << "  "   << endl;
    cout << "          L1    "   << endl;
    cout << "  "   << endl;
   
   
    cout<< " L1_SingleMuOpen=        "<<L1_SingleMuOpen/nevanalyzed    <<endl;
    cout<< " L1_SingleMu0=           "<<L1_SingleMu0/nevanalyzed    <<endl;
    cout<< " L1_SingleMu7=           "<<L1_SingleMu7/nevanalyzed    <<endl;
    cout<< " L1_DoubleMu3=           "<<L1_DoubleMu3/nevanalyzed    <<endl;
    cout<< " L1_SingleMu20=          "<<L1_SingleMu20/nevanalyzed    <<endl;
    cout<< " L1_SingleMu3=           "<<L1_SingleMu3/nevanalyzed    <<endl;
    cout<< " L1_DoubleMuOpen=        "<<L1_DoubleMuOpen/nevanalyzed    <<endl;
    cout<< " L1_SingleEG1=           "<<L1_SingleEG1/nevanalyzed    <<endl;
    cout<< " L1_SingleEG2=           "<<L1_SingleEG2/nevanalyzed    <<endl;
    cout<< " L1_SingleEG5=           "<<L1_SingleEG5/nevanalyzed    <<endl;
    cout<< " L1_SingleEG8=           "<<L1_SingleEG8/nevanalyzed    <<endl;
    cout<< " L1_SingleEG20=          "<<L1_SingleEG20/nevanalyzed    <<endl;
    cout<< " L1_DoubleEG5=           "<<L1_DoubleEG5/nevanalyzed    <<endl;

    cout << "  "   << endl;
    cout << "          HLT    "   << endl;
    cout << "  "   << endl;
   
   
    cout<< " HLT_L1MuOpen=           "<<HLT_L1MuOpen/nevanalyzed    <<endl;
    cout<< " HLT_L1Mu=               "<<HLT_L1Mu/nevanalyzed    <<endl;
    cout<< " HLT_Mu5=                "<<HLT_Mu5/nevanalyzed    <<endl;
    cout<< " HLT_Mu9=                "<<HLT_Mu9/nevanalyzed    <<endl;
    cout<< " HLT_L1DoubleMuOpen=     "<<HLT_L1DoubleMuOpen/nevanalyzed    <<endl;
    cout<< " HLT_DoubleMu0=          "<<HLT_DoubleMu0/nevanalyzed    <<endl;
    cout<< " HLT_DoubleMu3=          "<<HLT_DoubleMu3/nevanalyzed    <<endl;
    cout<< " HLT_L1SingleEG5=        "<<HLT_L1SingleEG5/nevanalyzed    <<endl;
 //   cout<< " HLT_Ele15_SW_EleId_L1R= "<<HLT_Ele15_SW_EleId_L1R/nevanalyzed    <<endl;
    cout<< " HLT_Ele15_LW_L1R=       "<<HLT_Ele15_LW_L1R/nevanalyzed    <<endl;
    cout<< " HLT_Ele15_SiStrip_L1R=  "<<HLT_Ele15_SiStrip_L1R/nevanalyzed    <<endl;
       
    
    cout <<" ------------------  Preselection for leptons ---------------------- " << endl;
    
    cout <<" electrons  5 GeV  :" << nel5/nevanalyzed <<endl;
    cout <<" muons      5 GeV  :" << nmu5/nevanalyzed <<endl;
    cout <<" electrons 10 GeV  :" << nel10/nevanalyzed <<endl;
    cout <<" muons     10 GeV  :" << nmu10/nevanalyzed <<endl;
    cout <<" ============================" << endl;
    cout <<" pairs      5 GeV  :" << npair5/nevanalyzed <<endl;
    cout <<" pairs     10 GeV  :" << npair10/nevanalyzed <<endl;
   
    
    
    
    
    cout<<"                                        "<<endl;
    cout<<"                                        "<<endl;
    cout<<"                                        "<<endl;
    cout<<"                                        "<<endl;
    cout<<" =============================          "<<endl;
    cout<<"                                        "<<endl;
    cout<<"(READ THIS FIRST ROUND ONLY !!)  Data Sample Weight for "<<Luminosity<<" pb-1 (sigma x Lumi)/(number of an. events): "<<CrossSection*Luminosity/nevanalyzed<<endl;
    cout<<"                                        "<<endl;
    cout<<"Total number of events analyzed                        : "<<nevanalyzed<<endl;
   
  
    cout<<"============== Event Selection for all final states ============"<<endl;
    double eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    cout<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_all)/hltpassed;
    cout<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_all<<endl;
    eff=0;
    if(pteta_passed_all>0.)eff=double(d0_passed_all)/pteta_passed_all;
    cout<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_all<<endl;
    eff=0;
    if(d0_passed_all>0.)eff=double(iso_passed_all)/d0_passed_all;
    cout<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_all<<endl;
    eff=0;
    if(iso_passed_all>0.)eff=double(id_passed_all)/iso_passed_all;
    cout<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_all<<endl;
    eff=0;
    if(id_passed_all>0.)eff=double(conv_passed_all)/id_passed_all;
    cout<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_all <<endl;
    eff=0; 
    if(conv_passed_all>0.)eff=double(met_passed_all)/conv_passed_all;
    cout<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_all <<endl;
    eff=0;
    if(met_passed_all>0.)eff=double(mll1_passed_all)/met_passed_all;
    cout<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_all <<endl;
    eff=0; 
    if(mll1_passed_all>0.)eff=double(mll2_passed_all)/mll1_passed_all;
    cout<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_all <<endl;
    eff=0;
    if(mll2_passed_all>0.)eff=double(pmet_passed_all)/mll2_passed_all;
    cout<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_all<<endl;
    eff=0;
    if(pmet_passed_all>0.)eff=double(jetveto_passed_all)/pmet_passed_all;
    cout<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_all <<endl;
    eff=0;
    if(jetveto_passed_all>0.)eff=double(softmuons_passed_all)/jetveto_passed_all;
    cout<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_all<<endl;
    eff=0;          
    if(softmuons_passed_all>0.)eff=double(extraleptons_passed_all)/softmuons_passed_all;
    cout<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_all<<endl;
    eff=0;     
    
    cout<<"==========================================="<<endl;
    cout<<"Total efficiency                      : "<<extraleptons_passed_all/nevanalyzed<<" +/- "<<sqrt(D_all)/nevanalyzed<<endl;
    cout<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_all/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_all)/nevanalyzed*Luminosity<<endl;
    cout<<"==========================================="<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
  
  
   cout<<"============== Event Selection for ee final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    cout<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_ee)/hltpassed;
    cout<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_ee<<endl;
    eff=0;
    if(pteta_passed_ee>0.)eff=double(d0_passed_ee)/pteta_passed_ee;
    cout<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_ee<<endl;
    eff=0;
    if(d0_passed_ee>0.)eff=double(iso_passed_ee)/d0_passed_ee;
    cout<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_ee<<endl;
    eff=0;
    if(iso_passed_ee>0.)eff=double(id_passed_ee)/iso_passed_ee;
    cout<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_ee<<endl;
    eff=0;
    if(id_passed_ee>0.)eff=double(conv_passed_ee)/id_passed_ee;
    cout<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_ee <<endl;
    eff=0; 
    if(conv_passed_ee>0.)eff=double(met_passed_ee)/conv_passed_ee;
    cout<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_ee <<endl;
    eff=0;
    if(met_passed_ee>0.)eff=double(mll1_passed_ee)/met_passed_ee;
    cout<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_ee <<endl;
    eff=0; 
    if(mll1_passed_ee>0.)eff=double(mll2_passed_ee)/mll1_passed_ee;
    cout<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_ee <<endl;
    eff=0;
    if(mll2_passed_ee>0.)eff=double(pmet_passed_ee)/mll2_passed_ee;
    cout<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_ee<<endl;
    eff=0;
    if(pmet_passed_ee>0.)eff=double(jetveto_passed_ee)/pmet_passed_ee;
    cout<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_ee <<endl;
    eff=0;
    if(jetveto_passed_ee>0.)eff=double(softmuons_passed_ee)/jetveto_passed_ee;
    cout<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_ee<<endl;
    eff=0;          
    if(softmuons_passed_ee>0.)eff=double(extraleptons_passed_ee)/softmuons_passed_ee;
    cout<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_ee<<endl;
    eff=0;     
    
    cout<<"==========================================="<<endl;
    cout<<"Total efficiency                      : "<<extraleptons_passed_ee/nevanalyzed<<" +/- "<<sqrt(D_ee)/nevanalyzed<<endl;
    cout<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_ee/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_ee)/nevanalyzed*Luminosity<<endl;
    cout<<"==========================================="<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    
    
    cout<<"============== Event Selection for mm final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    cout<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_mm)/hltpassed;
    cout<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_mm<<endl;
    eff=0;
    if(pteta_passed_mm>0.)eff=double(d0_passed_mm)/pteta_passed_mm;
    cout<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_mm<<endl;
    eff=0;
    if(d0_passed_mm>0.)eff=double(iso_passed_mm)/d0_passed_mm;
    cout<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_mm<<endl;
    eff=0;
    if(iso_passed_mm>0.)eff=double(id_passed_mm)/iso_passed_mm;
    cout<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_mm<<endl;
    eff=0;
    if(id_passed_mm>0.)eff=double(conv_passed_mm)/id_passed_mm;
    cout<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_mm <<endl;
    eff=0; 
    if(conv_passed_mm>0.)eff=double(met_passed_mm)/conv_passed_mm;
    cout<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_mm <<endl;
    eff=0;
    if(met_passed_mm>0.)eff=double(mll1_passed_mm)/met_passed_mm;
    cout<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_mm <<endl;
    eff=0; 
    if(mll1_passed_mm>0.)eff=double(mll2_passed_mm)/mll1_passed_mm;
    cout<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_mm <<endl;
    eff=0;
    if(mll2_passed_mm>0.)eff=double(pmet_passed_mm)/mll2_passed_mm;
    cout<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_mm<<endl;
    eff=0;
    if(pmet_passed_mm>0.)eff=double(jetveto_passed_mm)/pmet_passed_mm;
    cout<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_mm <<endl;
    eff=0;
    if(jetveto_passed_mm>0.)eff=double(softmuons_passed_mm)/jetveto_passed_mm;
    cout<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_mm<<endl;
    eff=0;          
    if(softmuons_passed_mm>0.)eff=double(extraleptons_passed_mm)/softmuons_passed_mm;
    cout<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_mm<<endl;
    eff=0;     
    
    cout<<"==========================================="<<endl;
    cout<<"Total efficiency                      : "<<extraleptons_passed_mm/nevanalyzed<<" +/- "<<sqrt(D_mm)/nevanalyzed<<endl;
    cout<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_mm/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_mm)/nevanalyzed*Luminosity<<endl;
    cout<<"==========================================="<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    
    
    
    cout<<"============== Event Selection for em final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    cout<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_em)/hltpassed;
    cout<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_em<<endl;
    eff=0;
    if(pteta_passed_em>0.)eff=double(d0_passed_em)/pteta_passed_em;
    cout<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_em<<endl;
    eff=0;
    if(d0_passed_em>0.)eff=double(iso_passed_em)/d0_passed_em;
    cout<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_em<<endl;
    eff=0;
    if(iso_passed_em>0.)eff=double(id_passed_em)/iso_passed_em;
    cout<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_em<<endl;
    eff=0;
    if(id_passed_em>0.)eff=double(conv_passed_em)/id_passed_em;
    cout<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_em <<endl;
    eff=0; 
    if(conv_passed_em>0.)eff=double(met_passed_em)/conv_passed_em;
    cout<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_em <<endl;
    eff=0;
    if(met_passed_em>0.)eff=double(mll1_passed_em)/met_passed_em;
    cout<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_em <<endl;
    eff=0; 
    if(mll1_passed_em>0.)eff=double(mll2_passed_em)/mll1_passed_em;
    cout<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_em <<endl;
    eff=0;
    if(mll2_passed_em>0.)eff=double(pmet_passed_em)/mll2_passed_em;
    cout<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_em<<endl;
    eff=0;
    if(pmet_passed_em>0.)eff=double(jetveto_passed_em)/pmet_passed_em;
    cout<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_em <<endl;
    eff=0;
    if(jetveto_passed_em>0.)eff=double(softmuons_passed_em)/jetveto_passed_em;
    cout<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_em<<endl;
    eff=0;          
    if(softmuons_passed_em>0.)eff=double(extraleptons_passed_em)/softmuons_passed_em;
    cout<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_em<<endl;
    eff=0;     
    
    cout<<"==========================================="<<endl;
    cout<<"Total efficiency                      : "<<extraleptons_passed_em/nevanalyzed<<" +/- "<<sqrt(D_em)/nevanalyzed<<endl;
    cout<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_em/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_em)/nevanalyzed*Luminosity<<endl;
    cout<<"==========================================="<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    
    
    cout<<"============== Event Selection for me final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    cout<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_me)/hltpassed;
    cout<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_me<<endl;
    eff=0;
    if(pteta_passed_me>0.)eff=double(d0_passed_me)/pteta_passed_me;
    cout<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_me<<endl;
    eff=0;
    if(d0_passed_me>0.)eff=double(iso_passed_me)/d0_passed_me;
    cout<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_me<<endl;
    eff=0;
    if(iso_passed_me>0.)eff=double(id_passed_me)/iso_passed_me;
    cout<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_me<<endl;
    eff=0;
    if(id_passed_me>0.)eff=double(conv_passed_me)/id_passed_me;
    cout<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_me <<endl;
    eff=0; 
    if(conv_passed_me>0.)eff=double(met_passed_me)/conv_passed_me;
    cout<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_me <<endl;
    eff=0;
    if(met_passed_me>0.)eff=double(mll1_passed_me)/met_passed_me;
    cout<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_me <<endl;
    eff=0; 
    if(mll1_passed_me>0.)eff=double(mll2_passed_me)/mll1_passed_me;
    cout<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_me <<endl;
    eff=0;
    if(mll2_passed_me>0.)eff=double(pmet_passed_me)/mll2_passed_me;
    cout<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_me<<endl;
    eff=0;
    if(pmet_passed_me>0.)eff=double(jetveto_passed_me)/pmet_passed_me;
    cout<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_me <<endl;
    eff=0;
    if(jetveto_passed_me>0.)eff=double(softmuons_passed_me)/jetveto_passed_me;
    cout<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_me<<endl;
    eff=0;          
    if(softmuons_passed_me>0.)eff=double(extraleptons_passed_me)/softmuons_passed_me;
    cout<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_me<<endl;
    eff=0;     
    
    cout<<"==========================================="<<endl;
    cout<<"Total efficiency                      : "<<extraleptons_passed_me/nevanalyzed<<" +/- "<<sqrt(D_me)/nevanalyzed<<endl;
    cout<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_me/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_me)/nevanalyzed*Luminosity<<endl;
    cout<<"==========================================="<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    
    
    cout<<"============== Event Selection for mixed final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    cout<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_mixed)/hltpassed;
    cout<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_mixed<<endl;
    eff=0;
    if(pteta_passed_mixed>0.)eff=double(d0_passed_mixed)/pteta_passed_mixed;
    cout<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_mixed<<endl;
    eff=0;
    if(d0_passed_mixed>0.)eff=double(iso_passed_mixed)/d0_passed_mixed;
    cout<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_mixed<<endl;
    eff=0;
    if(iso_passed_mixed>0.)eff=double(id_passed_mixed)/iso_passed_mixed;
    cout<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_mixed<<endl;
    eff=0;
    if(id_passed_mixed>0.)eff=double(conv_passed_mixed)/id_passed_mixed;
    cout<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_mixed <<endl;
    eff=0; 
    if(conv_passed_mixed>0.)eff=double(met_passed_mixed)/conv_passed_mixed;
    cout<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_mixed <<endl;
    eff=0;
    if(met_passed_mixed>0.)eff=double(mll1_passed_mixed)/met_passed_mixed;
    cout<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_mixed <<endl;
    eff=0; 
    if(mll1_passed_mixed>0.)eff=double(mll2_passed_mixed)/mll1_passed_mixed;
    cout<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_mixed <<endl;
    eff=0;
    if(mll2_passed_mixed>0.)eff=double(pmet_passed_mixed)/mll2_passed_mixed;
    cout<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_mixed<<endl;
    eff=0;
    if(pmet_passed_mixed>0.)eff=double(jetveto_passed_mixed)/pmet_passed_mixed;
    cout<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_mixed <<endl;
    eff=0;
    if(jetveto_passed_mixed>0.)eff=double(softmuons_passed_mixed)/jetveto_passed_mixed;
    cout<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_mixed<<endl;
    eff=0;          
    if(softmuons_passed_mixed>0.)eff=double(extraleptons_passed_mixed)/softmuons_passed_mixed;
    cout<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_mixed<<endl;
    eff=0;     
    
    cout<<"==========================================="<<endl;
    cout<<"Total efficiency                      : "<<extraleptons_passed_mixed/nevanalyzed<<" +/- "<<sqrt(D_mixed)/nevanalyzed<<endl;
    cout<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_mixed/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_mixed)/nevanalyzed*Luminosity<<endl;
    cout<<"==========================================="<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" "<<endl;
   
   
   
   
   
   
   
   
   
   
   
   
   ofstream results;
   results.open(OutputTextFile.c_str());
   
   
    results<<"============== Event Selection for all final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    results<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_all)/hltpassed;
    results<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_all<<endl;
    eff=0;
    if(pteta_passed_all>0.)eff=double(d0_passed_all)/pteta_passed_all;
    results<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_all<<endl;
    eff=0;
    if(d0_passed_all>0.)eff=double(iso_passed_all)/d0_passed_all;
    results<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_all<<endl;
    eff=0;
    if(iso_passed_all>0.)eff=double(id_passed_all)/iso_passed_all;
    results<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_all<<endl;
    eff=0;
    if(id_passed_all>0.)eff=double(conv_passed_all)/id_passed_all;
    results<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_all <<endl;
    eff=0; 
    if(conv_passed_all>0.)eff=double(met_passed_all)/conv_passed_all;
    results<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_all <<endl;
    eff=0;
    if(met_passed_all>0.)eff=double(mll1_passed_all)/met_passed_all;
    results<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_all <<endl;
    eff=0; 
    if(mll1_passed_all>0.)eff=double(mll2_passed_all)/mll1_passed_all;
    results<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_all <<endl;
    eff=0;
    if(mll2_passed_all>0.)eff=double(pmet_passed_all)/mll2_passed_all;
    results<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_all<<endl;
    eff=0;
    if(pmet_passed_all>0.)eff=double(jetveto_passed_all)/pmet_passed_all;
    results<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_all <<endl;
    eff=0;
    if(jetveto_passed_all>0.)eff=double(softmuons_passed_all)/jetveto_passed_all;
    results<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_all<<endl;
    eff=0;          
    if(softmuons_passed_all>0.)eff=double(extraleptons_passed_all)/softmuons_passed_all;
    results<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_all<<endl;
    eff=0;     
    
    results<<"==========================================="<<endl;
    results<<"Total efficiency                      : "<<extraleptons_passed_all/nevanalyzed<<" +/- "<<sqrt(D_all)/nevanalyzed<<endl;
    results<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_all/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_all)/nevanalyzed*Luminosity<<endl;
    results<<"==========================================="<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
  
    
    
      
   results<<"============== Event Selection for ee final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    results<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_ee)/hltpassed;
    results<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_ee<<endl;
    eff=0;
    if(pteta_passed_ee>0.)eff=double(d0_passed_ee)/pteta_passed_ee;
    results<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_ee<<endl;
    eff=0;
    if(d0_passed_ee>0.)eff=double(iso_passed_ee)/d0_passed_ee;
    results<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_ee<<endl;
    eff=0;
    if(iso_passed_ee>0.)eff=double(id_passed_ee)/iso_passed_ee;
    results<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_ee<<endl;
    eff=0;
    if(id_passed_ee>0.)eff=double(conv_passed_ee)/id_passed_ee;
    results<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_ee <<endl;
    eff=0; 
    if(conv_passed_ee>0.)eff=double(met_passed_ee)/conv_passed_ee;
    results<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_ee <<endl;
    eff=0;
    if(met_passed_ee>0.)eff=double(mll1_passed_ee)/met_passed_ee;
    results<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_ee <<endl;
    eff=0; 
    if(mll1_passed_ee>0.)eff=double(mll2_passed_ee)/mll1_passed_ee;
    results<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_ee <<endl;
    eff=0;
    if(mll2_passed_ee>0.)eff=double(pmet_passed_ee)/mll2_passed_ee;
    results<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_ee<<endl;
    eff=0;
    if(pmet_passed_ee>0.)eff=double(jetveto_passed_ee)/pmet_passed_ee;
    results<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_ee <<endl;
    eff=0;
    if(jetveto_passed_ee>0.)eff=double(softmuons_passed_ee)/jetveto_passed_ee;
    results<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_ee<<endl;
    eff=0;          
    if(softmuons_passed_ee>0.)eff=double(extraleptons_passed_ee)/softmuons_passed_ee;
    results<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_ee<<endl;
    eff=0;     
    
    results<<"==========================================="<<endl;
    results<<"Total efficiency                      : "<<extraleptons_passed_ee/nevanalyzed<<" +/- "<<sqrt(D_ee)/nevanalyzed<<endl;
    results<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_ee/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_ee)/nevanalyzed*Luminosity<<endl;
    results<<"==========================================="<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    
    
    results<<"============== Event Selection for mm final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    results<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_mm)/hltpassed;
    results<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_mm<<endl;
    eff=0;
    if(pteta_passed_mm>0.)eff=double(d0_passed_mm)/pteta_passed_mm;
    results<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_mm<<endl;
    eff=0;
    if(d0_passed_mm>0.)eff=double(iso_passed_mm)/d0_passed_mm;
    results<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_mm<<endl;
    eff=0;
    if(iso_passed_mm>0.)eff=double(id_passed_mm)/iso_passed_mm;
    results<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_mm<<endl;
    eff=0;
    if(id_passed_mm>0.)eff=double(conv_passed_mm)/id_passed_mm;
    results<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_mm <<endl;
    eff=0; 
    if(conv_passed_mm>0.)eff=double(met_passed_mm)/conv_passed_mm;
    results<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_mm <<endl;
    eff=0;
    if(met_passed_mm>0.)eff=double(mll1_passed_mm)/met_passed_mm;
    results<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_mm <<endl;
    eff=0; 
    if(mll1_passed_mm>0.)eff=double(mll2_passed_mm)/mll1_passed_mm;
    results<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_mm <<endl;
    eff=0;
    if(mll2_passed_mm>0.)eff=double(pmet_passed_mm)/mll2_passed_mm;
    results<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_mm<<endl;
    eff=0;
    if(pmet_passed_mm>0.)eff=double(jetveto_passed_mm)/pmet_passed_mm;
    results<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_mm <<endl;
    eff=0;
    if(jetveto_passed_mm>0.)eff=double(softmuons_passed_mm)/jetveto_passed_mm;
    results<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_mm<<endl;
    eff=0;          
    if(softmuons_passed_mm>0.)eff=double(extraleptons_passed_mm)/softmuons_passed_mm;
    results<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_mm<<endl;
    eff=0;     
    
    results<<"==========================================="<<endl;
    results<<"Total efficiency                      : "<<extraleptons_passed_mm/nevanalyzed<<" +/- "<<sqrt(D_mm)/nevanalyzed<<endl;
    results<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_mm/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_mm)/nevanalyzed*Luminosity<<endl;
    results<<"==========================================="<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    
    
    
    results<<"============== Event Selection for em final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    results<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_em)/hltpassed;
    results<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_em<<endl;
    eff=0;
    if(pteta_passed_em>0.)eff=double(d0_passed_em)/pteta_passed_em;
    results<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_em<<endl;
    eff=0;
    if(d0_passed_em>0.)eff=double(iso_passed_em)/d0_passed_em;
    results<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_em<<endl;
    eff=0;
    if(iso_passed_em>0.)eff=double(id_passed_em)/iso_passed_em;
    results<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_em<<endl;
    eff=0;
    if(id_passed_em>0.)eff=double(conv_passed_em)/id_passed_em;
    results<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_em <<endl;
    eff=0; 
    if(conv_passed_em>0.)eff=double(met_passed_em)/conv_passed_em;
    results<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_em <<endl;
    eff=0;
    if(met_passed_em>0.)eff=double(mll1_passed_em)/met_passed_em;
    results<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_em <<endl;
    eff=0; 
    if(mll1_passed_em>0.)eff=double(mll2_passed_em)/mll1_passed_em;
    results<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_em <<endl;
    eff=0;
    if(mll2_passed_em>0.)eff=double(pmet_passed_em)/mll2_passed_em;
    results<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_em<<endl;
    eff=0;
    if(pmet_passed_em>0.)eff=double(jetveto_passed_em)/pmet_passed_em;
    results<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_em <<endl;
    eff=0;
    if(jetveto_passed_em>0.)eff=double(softmuons_passed_em)/jetveto_passed_em;
    results<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_em<<endl;
    eff=0;          
    if(softmuons_passed_em>0.)eff=double(extraleptons_passed_em)/softmuons_passed_em;
    results<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_em<<endl;
    eff=0;     
    
    results<<"==========================================="<<endl;
    results<<"Total efficiency                      : "<<extraleptons_passed_em/nevanalyzed<<" +/- "<<sqrt(D_em)/nevanalyzed<<endl;
    results<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_em/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_em)/nevanalyzed*Luminosity<<endl;
    results<<"==========================================="<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    
    
    results<<"============== Event Selection for me final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    results<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_me)/hltpassed;
    results<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_me<<endl;
    eff=0;
    if(pteta_passed_me>0.)eff=double(d0_passed_me)/pteta_passed_me;
    results<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_me<<endl;
    eff=0;
    if(d0_passed_me>0.)eff=double(iso_passed_me)/d0_passed_me;
    results<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_me<<endl;
    eff=0;
    if(iso_passed_me>0.)eff=double(id_passed_me)/iso_passed_me;
    results<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_me<<endl;
    eff=0;
    if(id_passed_me>0.)eff=double(conv_passed_me)/id_passed_me;
    results<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_me <<endl;
    eff=0; 
    if(conv_passed_me>0.)eff=double(met_passed_me)/conv_passed_me;
    results<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_me <<endl;
    eff=0;
    if(met_passed_me>0.)eff=double(mll1_passed_me)/met_passed_me;
    results<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_me <<endl;
    eff=0; 
    if(mll1_passed_me>0.)eff=double(mll2_passed_me)/mll1_passed_me;
    results<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_me <<endl;
    eff=0;
    if(mll2_passed_me>0.)eff=double(pmet_passed_me)/mll2_passed_me;
    results<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_me<<endl;
    eff=0;
    if(pmet_passed_me>0.)eff=double(jetveto_passed_me)/pmet_passed_me;
    results<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_me <<endl;
    eff=0;
    if(jetveto_passed_me>0.)eff=double(softmuons_passed_me)/jetveto_passed_me;
    results<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_me<<endl;
    eff=0;          
    if(softmuons_passed_me>0.)eff=double(extraleptons_passed_me)/softmuons_passed_me;
    results<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_me<<endl;
    eff=0;     
    
    results<<"==========================================="<<endl;
    results<<"Total efficiency                      : "<<extraleptons_passed_me/nevanalyzed<<" +/- "<<sqrt(D_me)/nevanalyzed<<endl;
    results<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_me/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_me)/nevanalyzed*Luminosity<<endl;
    results<<"==========================================="<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    
    
    results<<"============== Event Selection for mixed final states ============"<<endl;
    eff=0;
    if(nevanalyzed>0.)eff=double(hltpassed)/nevanalyzed;
    results<<"0) Pass HLT                                      : "<<eff<<" , "<<hltpassed<<endl;
    eff=0;
    if(hltpassed>0.)eff=double(pteta_passed_mixed)/hltpassed;
    results<<"1) Pt, Eta cut                                   : "<<eff<<" , "<<pteta_passed_mixed<<endl;
    eff=0;
    if(pteta_passed_mixed>0.)eff=double(d0_passed_mixed)/pteta_passed_mixed;
    results<<"2) d0 cut (vertex)                               : "<<eff<<" , "<<d0_passed_mixed<<endl;
    eff=0;
    if(d0_passed_mixed>0.)eff=double(iso_passed_mixed)/d0_passed_mixed;
    results<<"3) Isolation cuts                                : "<<eff<<" , "<<iso_passed_mixed<<endl;
    eff=0;
    if(iso_passed_mixed>0.)eff=double(id_passed_mixed)/iso_passed_mixed;
    results<<"4) Id cuts                                       : "<<eff<<" , "<< id_passed_mixed<<endl;
    eff=0;
    if(id_passed_mixed>0.)eff=double(conv_passed_mixed)/id_passed_mixed;
    results<<"5) Conversion rej.                               : "<<eff<<" , "<<conv_passed_mixed <<endl;
    eff=0; 
    if(conv_passed_mixed>0.)eff=double(met_passed_mixed)/conv_passed_mixed;
    results<<"6) MET cut                                       : "<<eff<<" , "<<met_passed_mixed <<endl;
    eff=0;
    if(met_passed_mixed>0.)eff=double(mll1_passed_mixed)/met_passed_mixed;
    results<<"7) Mll cut #1                                    : "<<eff<<" , "<<mll1_passed_mixed <<endl;
    eff=0; 
    if(mll1_passed_mixed>0.)eff=double(mll2_passed_mixed)/mll1_passed_mixed;
    results<<"8) Mll cut #2                                    : "<<eff<<" , "<<mll2_passed_mixed <<endl;
    eff=0;
    if(mll2_passed_mixed>0.)eff=double(pmet_passed_mixed)/mll2_passed_mixed;
    results<<"9)  rojected MET cut                             : "<<eff<<" , "<< pmet_passed_mixed<<endl;
    eff=0;
    if(pmet_passed_mixed>0.)eff=double(jetveto_passed_mixed)/pmet_passed_mixed;
    results<<"10) Jet Veto                                     : "<<eff<<" , "<<jetveto_passed_mixed <<endl;
    eff=0;
    if(jetveto_passed_mixed>0.)eff=double(softmuons_passed_mixed)/jetveto_passed_mixed;
    results<<"11) Soft Muon rejection                          : "<<eff<<" , "<< softmuons_passed_mixed<<endl;
    eff=0;          
    if(softmuons_passed_mixed>0.)eff=double(extraleptons_passed_mixed)/softmuons_passed_mixed;
    results<<"12) Extralepton Rejection                        : "<<eff<<" , "<< extraleptons_passed_mixed<<endl;
    eff=0;     
    
    results<<"==========================================="<<endl;
    results<<"Total efficiency                      : "<<extraleptons_passed_mixed/nevanalyzed<<" +/- "<<sqrt(D_mixed)/nevanalyzed<<endl;
    results<<"Remaining number of events at "<<Luminosity<<" pb-1 : "<<CrossSection*extraleptons_passed_mixed/nevanalyzed*Luminosity<<" +/- "<<CrossSection*sqrt(D_mixed)/nevanalyzed*Luminosity<<endl;
    results<<"==========================================="<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    results<<" "<<endl;
    
    
    
  
  return 0;
} //main
