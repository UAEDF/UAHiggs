/********************************************************************
* eventdict.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error eventdict.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#define G__PRIVATE_GVALUE
#include "cint/G__ci.h"
extern "C" {
extern void G__cpp_setup_tagtableeventdict();
extern void G__cpp_setup_inheritanceeventdict();
extern void G__cpp_setup_typetableeventdict();
extern void G__cpp_setup_memvareventdict();
extern void G__cpp_setup_globaleventdict();
extern void G__cpp_setup_memfunceventdict();
extern void G__cpp_setup_funceventdict();
extern void G__set_cpp_environmenteventdict();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "Analysis/HWWGenPart/interface/MyEvtId.h"
#include "Analysis/HWWGenPart/interface/MyL1Trig.h"
#include "Analysis/HWWGenPart/interface/MyPart.h"
#include "Analysis/HWWGenPart/interface/MyGenKin.h"
#include "Analysis/HWWGenPart/interface/MyGenPart.h"
#include "Analysis/HWWGenPart/interface/MyGenJet.h"
#include "Analysis/HWWGenPart/interface/MyBeamSpot.h"
#include "Analysis/HWWGenPart/interface/MyVertex.h"
#include "Analysis/HWWGenPart/interface/MyTracks.h"
#include "Analysis/HWWGenPart/interface/MyElectron.h"
#include "Analysis/HWWGenPart/interface/MyMuon.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__eventdictLN_TClass;
extern G__linked_taginfo G__eventdictLN_TBuffer;
extern G__linked_taginfo G__eventdictLN_TMemberInspector;
extern G__linked_taginfo G__eventdictLN_TObject;
extern G__linked_taginfo G__eventdictLN_vectorlEdoublecOallocatorlEdoublegRsPgR;
extern G__linked_taginfo G__eventdictLN_string;
extern G__linked_taginfo G__eventdictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_MyEvtId;
extern G__linked_taginfo G__eventdictLN_MyL1Trig;
extern G__linked_taginfo G__eventdictLN_TMatrixTBaselEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTBaselEdoublegR;
extern G__linked_taginfo G__eventdictLN_TVectorTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TVectorTlEdoublegR;
extern G__linked_taginfo G__eventdictLN_TElementActionTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TElementPosActionTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTRow_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTRowlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTDiag_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTColumn_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTFlat_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSub_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseRow_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseDiag_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTColumnlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTDiaglEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTFlatlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSublEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseRowlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseDiaglEfloatgR;
extern G__linked_taginfo G__eventdictLN_TLorentzVector;
extern G__linked_taginfo G__eventdictLN_MyPart;
extern G__linked_taginfo G__eventdictLN_MyGenKin;
extern G__linked_taginfo G__eventdictLN_MyGenPart;
extern G__linked_taginfo G__eventdictLN_MyGenJet;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenPartcOallocatorlEMyGenPartgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenPartcOallocatorlEMyGenPartgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyGenPartcOallocatorlEMyGenPartgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_MyBeamSpot;
extern G__linked_taginfo G__eventdictLN_MyVertex;
extern G__linked_taginfo G__eventdictLN_MyTracks;
extern G__linked_taginfo G__eventdictLN_vectorlEintcOallocatorlEintgRsPgR;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEintcOallocatorlEintgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_MyElectron;
extern G__linked_taginfo G__eventdictLN_MyMuon;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenJetcOallocatorlEMyGenJetgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenJetcOallocatorlEMyGenJetgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyGenJetcOallocatorlEMyGenJetgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyVertexcOallocatorlEMyVertexgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyVertexcOallocatorlEMyVertexgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyVertexcOallocatorlEMyVertexgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyTrackscOallocatorlEMyTracksgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyTrackscOallocatorlEMyTracksgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyTrackscOallocatorlEMyTracksgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyElectroncOallocatorlEMyElectrongRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyElectroncOallocatorlEMyElectrongRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyElectroncOallocatorlEMyElectrongRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyMuoncOallocatorlEMyMuongRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyMuoncOallocatorlEMyMuongRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyMuoncOallocatorlEMyMuongRsPgRcLcLiteratorgR;

/* STUB derived class for protected member access */
typedef vector<MyGenPart,allocator<MyGenPart> > G__vectorlEMyGenPartcOallocatorlEMyGenPartgRsPgR;
typedef vector<MyGenJet,allocator<MyGenJet> > G__vectorlEMyGenJetcOallocatorlEMyGenJetgRsPgR;
typedef vector<MyVertex,allocator<MyVertex> > G__vectorlEMyVertexcOallocatorlEMyVertexgRsPgR;
typedef vector<MyTracks,allocator<MyTracks> > G__vectorlEMyTrackscOallocatorlEMyTracksgRsPgR;
typedef vector<MyElectron,allocator<MyElectron> > G__vectorlEMyElectroncOallocatorlEMyElectrongRsPgR;
typedef vector<MyMuon,allocator<MyMuon> > G__vectorlEMyMuoncOallocatorlEMyMuongRsPgR;
