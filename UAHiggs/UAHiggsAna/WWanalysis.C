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

#include "include/GenPartPlots.h"
#include "src/GenPartPlots.C"
#include "include/ElectronPlots.h"
#include "src/ElectronPlots.C"
#include "include/MuonPlots.h"
#include "src/MuonPlots.C"
#include "include/LeptonPair.h"
#include "src/LeptonPair.C"
#include "include/LeptonPairPlots.h"
#include "src/LeptonPairPlots.C"
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


  GenPartPlots* genlep_Iinc          = new GenPartPlots("genlep_Iinc"); 
  GenPartPlots* genlep_Iinc_emu      = new GenPartPlots("genlep_Iinc_emu"); 
  GenPartPlots* genlep_I_ee          = new GenPartPlots("genlep_I_ee"); 
  GenPartPlots* genlep_I_mumu        = new GenPartPlots("genlep_I_mumu"); 
  GenPartPlots* genlep_I_emu         = new GenPartPlots("genlep_I_emu"); 
  GenPartPlots* genlep_I_tautau      = new GenPartPlots("genlep_I_tautau"); 
  
  GenPartPlots* genlep_IIIinc         = new GenPartPlots("genlep_III"); 
  GenPartPlots* genlep_IIIinc_emu     = new GenPartPlots("genlep_IIIinc_emu"); 
  GenPartPlots* genlep_III_ee         = new GenPartPlots("genlep_III_ee"); 
  GenPartPlots* genlep_III_mumu       = new GenPartPlots("genlep_III_mumu"); 
  GenPartPlots* genlep_III_emu        = new GenPartPlots("genlep_III_emu"); 
  GenPartPlots* genlep_III_tautau     = new GenPartPlots("genlep_III_tautau"); 
  
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
  //  vector<MyGenMET>   *genmet                   = NULL ;
   

      rootTree         -> SetBranchAddress("offlinePrimaryVertices",&vertex);
      rootTree         -> SetBranchAddress("EvtId",&evtid);
      rootTree         -> SetBranchAddress("L1Trig",&l1trig);
      rootTree         -> SetBranchAddress("HLTrig",&hltrig);
 //     rootTree         -> SetBranchAddress("GenKin",&genkin);
  //    rootTree         -> SetBranchAddress("GenPart",&genpart);
 //     rootTree         -> SetBranchAddress("GenElec",&genelec);
 //     rootTree         -> SetBranchAddress("GenMu",&genmu);
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
 //   rootTree	     -> SetBranchAddress("genMetTrue",&genmet);
    
    
    
   
    for(int i = 0; i < nev; i++){
      
      
      if(ntot%20000==0)cout<<"event number "<<ntot<<endl;
      ntot++;
      
      rootTree->GetEvent(i);  
    
   //   if(ApplyPreselectionBeforeHLT) PreselectionMarker = evtid  -> PreselMarker;
      
    //  if(ApplyKfactor=="YES")        kfactor            = genkin -> kfactor;
      weight=kfactor;
      weight*=DataSampleWeight;    //have to run once to get this
      nevanalyzed += weight;
        //------------- Control Plots at Gen Level ------------------------
        
       vector<MyGenPart> *allGenLeptonsIinc        = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsIinc_emu    = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsI_ee        = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsI_mumu      = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsI_emu       = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsI_tautau    = new vector<MyGenPart>();
      
       vector<MyGenPart> *allGenLeptonsIIIinc      = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsIIIinc_emu  = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsIII_ee      = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsIII_mumu    = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsIII_emu     = new vector<MyGenPart>();
       vector<MyGenPart> *allGenLeptonsIII_tautau  = new vector<MyGenPart>();
      
        
      int n_e=0,n_mu=0,n_tau = 0;  
      int n_e_or_mu=0;
      
   /*   for(vector<MyGenPart>::iterator itgen=genpart->begin();itgen!=genpart->end();itgen++){
      if(itgen->name=="W+") {
	//  cout<<"name      : "<<itgen->name    <<endl;
       cout<<"pdgID     : "<<itgen->pdgId   <<endl;
       cout<<"status    : "<<itgen->status    <<endl;
       cout<<"uniqueId  : "<<itgen->fUniqueID <<endl;
       cout<<"mother1   : "<<itgen->mo1     <<endl;
       cout<<"mother2   : "<<itgen->mo2   <<endl;
       cout<<"daughter1 : "<<itgen->da1   <<endl;
       cout<<"daughter2 : "<<itgen->da2   <<endl;
       
       cout<<"mass      : "<<itgen->m       <<endl;
       cout<<"eta       : "<<itgen->eta     <<endl;
     //  cout<<"y         : "<<Y              <<endl;
       cout<<"pt        : "<<itgen->pt      <<endl;
       cout<<"e         : "<<itgen->e       <<endl;
      // cout<<"p         : "<<P              <<endl;
       cout<<"px        : "<<itgen->px      <<endl;
       cout<<"py        : "<<itgen->py      <<endl;
       cout<<"pz        : "<<itgen->pz      <<endl;
       cout<<"                            "<<endl;
       cout<<" ---------------------------"<<endl;
       cout<<"                            "<<endl;
	}
       }
	/*if(fabs(itgen->pdgId) == 11) {
           n_e++;
	   allGenLeptonsI_ee->push_back(*itgen);
           allGenLeptonsI_emu->push_back(*itgen);
	   }
	if(fabs(itgen->pdgId) == 13) {
           n_mu++;
	   allGenLeptonsI_mumu->push_back(*itgen);
           allGenLeptonsI_emu->push_back(*itgen);
	   }
        if(fabs(itgen->pdgId) == 15) {
	   n_tau++;
	   allGenLeptonsI_tautau->push_back(*itgen);
           }
        if(fabs(itgen->pdgId) == 11 || fabs(itgen->pdgId) == 13 ){
	   n_e_or_mu++;
	   allGenLeptonsIinc_emu->push_back(*itgen);
	   }
	if(fabs(itgen->pdgId) == 11 || fabs(itgen->pdgId) == 13 || fabs(itgen->pdgId) == 15) {
           allGenLeptonsIinc->push_back(*itgen);
           }
      
        }
	
	                              genlep_Iinc         -> fill(*allGenLeptonsIinc       ,weight);
	if(n_e_or_mu ==2)             genlep_Iinc_emu     -> fill(*allGenLeptonsIinc_emu   ,weight);
	if(n_e==1 && n_mu==1)         genlep_I_emu        -> fill(*allGenLeptonsI_emu      ,weight);
	if(n_e       ==2)             genlep_I_ee         -> fill(*allGenLeptonsI_ee       ,weight);
	if(n_mu      ==2)             genlep_I_mumu       -> fill(*allGenLeptonsI_mumu     ,weight);
	if(n_tau     ==2)             genlep_I_tautau     -> fill(*allGenLeptonsI_tautau   ,weight);
	 
	
        for(vector<MyGenPart>::iterator itgenelec=genelec->begin();itgenelec!=genelec->end();itgenelec++){
                               allGenLeptonsIIIinc            ->push_back(*itgenelec);
        if(n_e_or_mu==2)       allGenLeptonsIIIinc_emu        ->push_back(*itgenelec);
	if(n_e     ==2)        allGenLeptonsIII_ee            ->push_back(*itgenelec);
	if(n_mu    ==2)        allGenLeptonsIII_mumu          ->push_back(*itgenelec);
	if(n_e==1 && n_mu==1)  allGenLeptonsIII_emu           ->push_back(*itgenelec);
	if(n_tau==2)           allGenLeptonsIII_tautau        ->push_back(*itgenelec);
	  }
        
	for(vector<MyGenPart>::iterator itgenmu=genmu->begin();itgenmu!=genmu->end();itgenmu++){
                               allGenLeptonsIIIinc            ->push_back(*itgenmu);
        if(n_e_or_mu==2)       allGenLeptonsIIIinc_emu        ->push_back(*itgenmu);
	if(n_e     ==2)        allGenLeptonsIII_ee            ->push_back(*itgenmu);
	if(n_mu    ==2)        allGenLeptonsIII_mumu          ->push_back(*itgenmu);
	if(n_e==1 && n_mu==1)  allGenLeptonsIII_emu           ->push_back(*itgenmu);
	if(n_tau==2)           allGenLeptonsIII_tautau        ->push_back(*itgenmu);
	}
        
	                            genlep_IIIinc         -> fill(*allGenLeptonsIIIinc       ,weight);
	if(n_e_or_mu ==2)           genlep_IIIinc_emu     -> fill(*allGenLeptonsIIIinc_emu   ,weight);
	if(n_e==1 && n_mu==1)       genlep_III_emu        -> fill(*allGenLeptonsIII_emu      ,weight);
	if(n_e       ==2)           genlep_III_ee         -> fill(*allGenLeptonsIII_ee       ,weight);
	if(n_mu      ==2)           genlep_III_mumu       -> fill(*allGenLeptonsIII_mumu     ,weight);
	if(n_tau     ==2)           genlep_III_tautau     -> fill(*allGenLeptonsIII_tautau   ,weight);*/
	
 
 
 //    cout <<"-----------------------------------------------------"<<endl;
     
       delete  allGenLeptonsIinc         ;
       delete  allGenLeptonsIinc_emu     ;
       delete  allGenLeptonsI_ee         ; 
       delete  allGenLeptonsI_mumu       ;
       delete  allGenLeptonsI_emu        ;
       delete  allGenLeptonsI_tautau     ;
      
       delete  allGenLeptonsIIIinc       ;
       delete  allGenLeptonsIIIinc_emu   ;
       delete  allGenLeptonsIII_ee       ;
       delete  allGenLeptonsIII_mumu     ;
       delete  allGenLeptonsIII_emu      ;
       delete  allGenLeptonsIII_tautau   ;
      
      
      // ------------- DATA  ------Event Selection ------------------
        
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
       if(l1trig->L1map["L1_SingleMu0"])    L1_SingleMu0+=weight;
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
       
	    
	    *electrons              = ElectronsCleaning(*electrons_bfmcl            , *muons);
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
       
      
            //--------- Highest pt lepton --------------------
	   
	   
	   
	   
	   
	   
	   
	   // ------Lepton Pairs Creations --------------------------
      
      
          
    
    
            //"  "<< pair_noCut->at(0)->type <<endl;
          //  cout << "pteta cut size "<< pair_PtEta->size() <<endl;
           // cout<<"-----------------------"<<endl;
          //  << "  "<< pair_PtEta->at(0)->type <<endl;
          // cout << "d0 size        "<< pair_d0   ->size() << "  "<< pair_d0   ->at(0)->type << endl;
      
       
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
	  
		  
	  
	/*   if (electrons_ptEta->size() >1) {   
     
           cout << "ele vector size    "<< electrons_ptEta->size() << endl;
         //  cout << "muon vector size    "<< muons->size() << endl;
           
           for(vector<MyElectron*>::iterator it_ele = electrons_ptEta->begin() ; it_ele != electrons_ptEta->end() ; ++it_ele){
              cout<< (*it_ele)->GsfTrack.vtxdxy.at(vtxId)<<"         "<<(*it_ele)->pt<<endl;
              }
      
        //   for(vector<LeptonPair*>::iterator itpair = pair_ptEta->begin() ; itpair != pair_ptEta->end() ; ++itpair){
         //  cout << (*itpair)->type  <<"       "<< (*itpair)->getPtMax() <<"       "<< (*itpair)->getPtMin() <<endl;
         //  }
           //     sort(pair_noCut->begin(),pair_noCut->end(),order);
     
           cout<<"-------------------------"<<endl;
      
           cout << "ele d0 vector size    "<< electrons_d0->size() << endl;
           cout << "muon d0 vector size    "<< muons_d0->size() << endl;
      
        //   pair_ptEta = MakeLeptonPairVector(*electrons_ptEta, *muons_ptEta);
           
      
           for(vector<LeptonPair*>::iterator itpair = pair_d0->begin() ; itpair != pair_d0->end() ; ++itpair){
           cout << (*itpair)->type  <<"       "<< (*itpair)->getPtMax() <<"       "<< (*itpair)->getPtMin() <<endl;
           }
      
           }
	  
	  cout <<" =========================================="<<endl;*/
	  
	  
	  //-------------- Prepare Jet Collection------------------------------
	  
	  vector<MyJet*> *jetsCleaned = new vector<MyJet*>();
	  *jetsCleaned = makeJetCleaning(*ak5pfjets,*electrons_conversion_bfmcl,*muons_id, 20, 3, 0.3);
	
	  
	  vector<MyJet*> *jetsCleaned_ee  = new vector<MyJet*>();
	  vector<MyJet*> *jetsCleaned_mm  = new vector<MyJet*>();
	  vector<MyJet*> *jetsCleaned_em  = new vector<MyJet*>();
	  vector<MyJet*> *jetsCleaned_me  = new vector<MyJet*>();
	  vector<MyJet*> *jetsCleaned_all = new vector<MyJet*>();
	  
	  
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
			      
			          // -------------- Mll cuthttps://cms-mgt-conferences.web.cern.ch/cms-mgt-conferences/conferences/pres_display.aspx?cid=501&pid=2509 #2 -------------------------
				
				
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
				        
					/* vector<MyElectron*> *ee = new vector<MyElectron*>;
					 vector<MyMuon*> *mm = new vector<MyMuon*>;
					
					
					 *ee = KeepBestPairFromElectrons(*electrons,*pair_pmet,"ee");
					 *mm = KeepBestPairFromMuons(*muons,*pair_pmet,"ee");
       				         *jetsCleaned_ee = makeJetCleaning(*ak5pfjets,*ee,*mm, 20, 3, 0.3);
				         ee->clear();
				         mm->clear();
				        
					 *ee = KeepBestPairFromElectrons(*electrons,*pair_pmet,"mm");
					 *mm = KeepBestPairFromMuons(*muons,*pair_pmet,"mm");
       				         *jetsCleaned_mm = makeJetCleaning(*ak5pfjets,*ee,*mm, 20, 3, 0.3);
				         ee->clear();
				         mm->clear();
					 
					 *ee = KeepBestPairFromElectrons(*electrons,*pair_pmet,"me");
					 *mm = KeepBestPairFromMuons(*muons,*pair_pmet,"me");
       				         *jetsCleaned_me = makeJetCleaning(*ak5pfjets,*ee,*mm, 20, 3, 0.3);
				         ee->clear();
				         mm->clear();	  				
					
					 *ee = KeepBestPairFromElectrons(*electrons,*pair_pmet,"em");
					 *mm = KeepBestPairFromMuons(*muons,*pair_pmet,"em");
       				         *jetsCleaned_em = makeJetCleaning(*ak5pfjets,*ee,*mm, 20, 3, 0.3);
				         ee->clear();
				         mm->clear();
					
					 delete mm;
					 delete ee;
					  if( find(*pair_pmet,"ee") ){
					     cout<<"ak5 " <<jetsCleaned -> size()<<" ee "<<jetsCleaned_ee ->size()<<endl;
					     if  ( jetsCleaned -> size() ==0 && 
					        !( jetsCleaned_ee ->size()==0) ){
					    
					    cout<<"Run          : "<<evtid->Run<<endl;
					    cout<<"LumiSect     : "<<evtid->LumiSect<<endl;
					    cout<<"Event        : "<<evtid->Evt<<endl;
					    
					    for(vector<MyJet*>::iterator itj = jetsCleaned_ee->begin() ; itj != jetsCleaned_ee->end() ; ++itj){
					    cout<<"======= Jets ==================================================="<<endl;
					    cout<<" e                    "<<(*itj)->e <<endl;
					    cout<<" pt                   "<<(*itj)->pt <<endl;
					    cout<<" eta                  "<<(*itj)->eta <<endl;
					    cout<<" phi                  "<<(*itj)->phi <<endl;
					    cout<<" ChargedHadronEnergy  "<<(*itj)->ChargedHadronEnergy <<endl;
					    cout<<" NeutralHadronEnergy  "<<(*itj)->NeutralHadronEnergy <<endl;
					    cout<<" ChargedEmEnergy      "<<(*itj)->ChargedEmEnergy <<endl;
					    cout<<" ChargedMuEnergy      "<<(*itj)->ChargedMuEnergy <<endl;
					    cout<<" NeutralEmEnergy      "<<(*itj)->NeutralEmEnergy  <<endl;
					    cout<<" ChargedMultiplicity  "<<(*itj)->ChargedMultiplicity <<endl;
					    cout<<" NeutralMultiplicity  "<<(*itj)->NeutralMultiplicity <<endl;
					    cout<<" MuonMultiplicity     "<<(*itj)->MuonMultiplicity <<endl;
					    }
					    cout<<"======= electrons ==================================================="<<endl;
					    
					    
					    for(vector<MyElectron*>::iterator itele = electrons->begin() ; itele != electrons->end() ; ++itele){   	    
					    cout<<"-------------------------"<<endl;
					    cout<<" e                "<<(*itele)->e <<endl;
					    cout<<" pt               "<<(*itele)->pt <<endl;
					    cout<<" eta              "<<(*itele)->eta <<endl;
					    cout<<" phi              "<<(*itele)->phi <<endl;
					    cout<<" isoglobal        "<<((*itele)->TrackIsolationDr03+max(Double_t(0),(*itele)->EcalRecHitIsoDr03-1.0)+(*itele)->HcalTowerSumEtDr03)/(*itele)->pt <<endl;
					    cout<<" HoE              "<<(*itele)->HadronicOverEm <<endl;
					    cout<<" dPhi             "<<(*itele)->dPhiSupClusTrVtx <<endl;
					    cout<<" dEta             "<<(*itele)->dEtaSupClusTrVtx <<endl;
					    cout<<" Cov              "<<(*itele)->CoviEtaiEta <<endl;
					    cout<<" ConvDcot         "<<(*itele)->dcot_conv <<endl;
					    cout<<" ConvDist         "<<(*itele)->dist_conv <<endl;
					    
					    
					    }
					     
					     }
					     
					     }
					     
					     
					    
					    
					  */  
					    
					    
					    
					    
					    
					    // for(vector<MyJet*>::iterator itj = jet.begin() ; itj != jet.end() ; ++itj){
					    //     cout<<
					 	 
						 
						 
						// }
					    // for(vector<MyElectron*>::iterator itele = ele.begin() ; itele != ele.end() ; ++itele){   
					         
						// } 		
					 
					 if ( jetsCleaned -> size() ==0 ) {
        //                              if (       ak5pfjets -> size() ==0 ) {			
	           
					   jetveto_passed_all += weight;
	                                   if( find(*pair_pmet,"ee") )                               jetveto_passed_ee    += weight;
	                                   if( find(*pair_pmet,"mm") )                               jetveto_passed_mm    += weight;
	                                   if( find(*pair_pmet,"em") )                               jetveto_passed_em    += weight;
	                                   if( find(*pair_pmet,"me") )                               jetveto_passed_me    += weight;
	                                   if( find(*pair_pmet,"em") || find(*pair_pmet,"me") )      jetveto_passed_mixed += weight;  
					   
					/* 
				         if((jetsCleaned_ee -> size() ==0) || (jetsCleaned_mm -> size() ==0) || (jetsCleaned_em -> size() ==0) || (jetsCleaned_me -> size() ==0) ){
					   jetveto_passed_all += weight;
					   if ( jetsCleaned_ee -> size() ==0 && find(*pair_pmet,"ee") )jetveto_passed_ee    += weight;
					   if ( jetsCleaned_mm -> size() ==0 && find(*pair_pmet,"mm") )jetveto_passed_mm    += weight;
					   if ( jetsCleaned_em -> size() ==0 && find(*pair_pmet,"em") )jetveto_passed_em    += weight;
					   if ( jetsCleaned_me -> size() ==0 && find(*pair_pmet,"me") )jetveto_passed_me    += weight;
					   
					  */
					   	
	           
					   
					   // -------------Soft Muon Veto --------------------------------
				           
					   
					   *extrasoftmuons_ee = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"ee");
					   *extrasoftmuons_mm = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"mm"); 
					   *extrasoftmuons_em = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"em"); 
					   *extrasoftmuons_me = ExtraSoftMuons(*muons, *pair_pmet,vtxId,"me"); 
					   
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
          delete jetsCleaned_ee;
          delete jetsCleaned_mm;
          delete jetsCleaned_em;
          delete jetsCleaned_me;
          delete jetsCleaned_all;
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
	  
	 
	  } // HLT requirement
      }  //end event-loop
  
      
    delete rootTree;
    delete file;
   
   }  // close file
   
   nf++;
   
   TFile analysisfile(OutputRootFile.c_str(),"RECREATE");
   
   genlep_Iinc          -> write();
   genlep_Iinc_emu      -> write();
   genlep_I_emu         -> write();
   genlep_I_ee          -> write();
   genlep_I_mumu        -> write();
   genlep_I_tautau      -> write();
   genlep_IIIinc        -> write();
   genlep_IIIinc_emu    -> write();
   genlep_III_emu       -> write();
   genlep_III_ee        -> write();
   genlep_III_mumu      -> write();
   genlep_III_tautau    -> write();
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
   
    
   delete genlep_Iinc          ;
   delete genlep_Iinc_emu      ;
   delete genlep_I_emu         ;
   delete genlep_I_ee          ;
   delete genlep_I_mumu        ;
   delete genlep_I_tautau      ;
   delete genlep_IIIinc        ;
   delete genlep_IIIinc_emu    ;
   delete genlep_III_emu       ;
   delete genlep_III_ee        ;
   delete genlep_III_mumu      ;
   delete genlep_III_tautau    ;
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
   delete  muons_IdCut            ;
   
    
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
