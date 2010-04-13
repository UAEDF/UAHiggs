//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec 15 11:44:42 2009 by ROOT version 5.22/00a
// from TTree tree/tree
// found on file: HWWGenPart.root
//////////////////////////////////////////////////////////

#ifndef Test_h
#define Test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMax = 13;

class Test {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //MyEvtId         *EvtId;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          Run;
   UInt_t          Evt;
   UInt_t          LumiSect;
   ULong64_t       Time;
   Bool_t          IsData;
   UInt_t          ExpType;
   Int_t           Bunch;
   Int_t           Orbit;
   Int_t           GenPart_;
   UInt_t          GenPart_fUniqueID[kMax];   //[_]
   UInt_t          GenPart_fBits[kMax];   //[_]
   Double_t        GenPart_pt[kMax];   //[_]
   Double_t        GenPart_eta[kMax];   //[_]
   Double_t        GenPart_phi[kMax];   //[_]
   Double_t        GenPart_charge[kMax];   //[_]
   Double_t        GenPart_e[kMax];   //[_]
   Double_t        GenPart_px[kMax];   //[_]
   Double_t        GenPart_py[kMax];   //[_]
   Double_t        GenPart_pz[kMax];   //[_]
   Double_t        GenPart_m[kMax];   //[_]
   UInt_t          GenPart_v_fUniqueID[kMax];   //[_]
   UInt_t          GenPart_v_fBits[kMax];   //[_]
   UInt_t          GenPart_v_fP_fUniqueID[kMax];   //[_]
   UInt_t          GenPart_v_fP_fBits[kMax];   //[_]
   Double_t        GenPart_v_fP_fX[kMax];   //[_]
   Double_t        GenPart_v_fP_fY[kMax];   //[_]
   Double_t        GenPart_v_fP_fZ[kMax];   //[_]
   Double_t        GenPart_v_fE[kMax];   //[_]
   Int_t           GenPart_pdgId[kMax];   //[_]
   Int_t           GenPart_status[kMax];   //[_]
   Int_t           GenPart_mo1[kMax];   //[_]
   Int_t           GenPart_mo2[kMax];   //[_]
   Int_t           GenPart_da1[kMax];   //[_]
   Int_t           GenPart_da2[kMax];   //[_]
   string          GenPart_name[kMax];

   // List of branches
   TBranch        *b_EvtId_fUniqueID;   //!
   TBranch        *b_EvtId_fBits;   //!
   TBranch        *b_EvtId_Run;   //!
   TBranch        *b_EvtId_Evt;   //!
   TBranch        *b_EvtId_LumiSect;   //!
   TBranch        *b_EvtId_Time;   //!
   TBranch        *b_EvtId_IsData;   //!
   TBranch        *b_EvtId_ExpType;   //!
   TBranch        *b_EvtId_Bunch;   //!
   TBranch        *b_EvtId_Orbit;   //!
   TBranch        *b__;   //!
   TBranch        *b_GenPart_fUniqueID;   //!
   TBranch        *b_GenPart_fBits;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_charge;   //!
   TBranch        *b_GenPart_e;   //!
   TBranch        *b_GenPart_px;   //!
   TBranch        *b_GenPart_py;   //!
   TBranch        *b_GenPart_pz;   //!
   TBranch        *b_GenPart_m;   //!
   TBranch        *b_GenPart_v_fUniqueID;   //!
   TBranch        *b_GenPart_v_fBits;   //!
   TBranch        *b_GenPart_v_fP_fUniqueID;   //!
   TBranch        *b_GenPart_v_fP_fBits;   //!
   TBranch        *b_GenPart_v_fP_fX;   //!
   TBranch        *b_GenPart_v_fP_fY;   //!
   TBranch        *b_GenPart_v_fP_fZ;   //!
   TBranch        *b_GenPart_v_fE;   //!
   TBranch        *b_GenPart_pdgId;   //!
   TBranch        *b_GenPart_status;   //!
   TBranch        *b_GenPart_mo1;   //!
   TBranch        *b_GenPart_mo2;   //!
   TBranch        *b_GenPart_da1;   //!
   TBranch        *b_GenPart_da2;   //!
   TBranch        *b_GenPart_name;   //!

   Test(TTree *tree=0);
   virtual ~Test();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Test_cxx
Test::Test(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("HWWGenPart.root");
      if (!f) {
         f = new TFile("HWWGenPart.root");
      }
      tree = (TTree*)gDirectory->Get("tree");

   }
   Init(tree);
}

Test::~Test()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Test::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Test::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Test::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_EvtId_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_EvtId_fBits);
   fChain->SetBranchAddress("Run", &Run, &b_EvtId_Run);
   fChain->SetBranchAddress("Evt", &Evt, &b_EvtId_Evt);
   fChain->SetBranchAddress("LumiSect", &LumiSect, &b_EvtId_LumiSect);
   fChain->SetBranchAddress("Time", &Time, &b_EvtId_Time);
   fChain->SetBranchAddress("IsData", &IsData, &b_EvtId_IsData);
   fChain->SetBranchAddress("ExpType", &ExpType, &b_EvtId_ExpType);
   fChain->SetBranchAddress("Bunch", &Bunch, &b_EvtId_Bunch);
   fChain->SetBranchAddress("Orbit", &Orbit, &b_EvtId_Orbit);
   fChain->SetBranchAddress("GenPart", &GenPart_, &b__);
   fChain->SetBranchAddress("GenPart.fUniqueID", GenPart_fUniqueID, &b_GenPart_fUniqueID);
   fChain->SetBranchAddress("GenPart.fBits", GenPart_fBits, &b_GenPart_fBits);
   fChain->SetBranchAddress("GenPart.pt", GenPart_pt, &b_GenPart_pt);
   fChain->SetBranchAddress("GenPart.eta", GenPart_eta, &b_GenPart_eta);
   fChain->SetBranchAddress("GenPart.phi", GenPart_phi, &b_GenPart_phi);
   fChain->SetBranchAddress("GenPart.charge", GenPart_charge, &b_GenPart_charge);
   fChain->SetBranchAddress("GenPart.e", GenPart_e, &b_GenPart_e);
   fChain->SetBranchAddress("GenPart.px", GenPart_px, &b_GenPart_px);
   fChain->SetBranchAddress("GenPart.py", GenPart_py, &b_GenPart_py);
   fChain->SetBranchAddress("GenPart.pz", GenPart_pz, &b_GenPart_pz);
   fChain->SetBranchAddress("GenPart.m", GenPart_m, &b_GenPart_m);
   fChain->SetBranchAddress("GenPart.v.fUniqueID", GenPart_v_fUniqueID, &b_GenPart_v_fUniqueID);
   fChain->SetBranchAddress("GenPart.v.fBits", GenPart_v_fBits, &b_GenPart_v_fBits);
   fChain->SetBranchAddress("GenPart.v.fP.fUniqueID", GenPart_v_fP_fUniqueID, &b_GenPart_v_fP_fUniqueID);
   fChain->SetBranchAddress("GenPart.v.fP.fBits", GenPart_v_fP_fBits, &b_GenPart_v_fP_fBits);
   fChain->SetBranchAddress("GenPart.v.fP.fX", GenPart_v_fP_fX, &b_GenPart_v_fP_fX);
   fChain->SetBranchAddress("GenPart.v.fP.fY", GenPart_v_fP_fY, &b_GenPart_v_fP_fY);
   fChain->SetBranchAddress("GenPart.v.fP.fZ", GenPart_v_fP_fZ, &b_GenPart_v_fP_fZ);
   fChain->SetBranchAddress("GenPart.v.fE", GenPart_v_fE, &b_GenPart_v_fE);
   fChain->SetBranchAddress("GenPart.pdgId", GenPart_pdgId, &b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart.status", GenPart_status, &b_GenPart_status);
   fChain->SetBranchAddress("GenPart.mo1", GenPart_mo1, &b_GenPart_mo1);
   fChain->SetBranchAddress("GenPart.mo2", GenPart_mo2, &b_GenPart_mo2);
   fChain->SetBranchAddress("GenPart.da1", GenPart_da1, &b_GenPart_da1);
   fChain->SetBranchAddress("GenPart.da2", GenPart_da2, &b_GenPart_da2);
   fChain->SetBranchAddress("GenPart.name", GenPart_name, &b_GenPart_name);
   Notify();
}

Bool_t Test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Test::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Test::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Test_cxx
