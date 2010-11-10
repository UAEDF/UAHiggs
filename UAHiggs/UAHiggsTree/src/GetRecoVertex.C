// Package:     UAHiggsTree
// Class:       UAHiggsTree
// author:      Xavier Janssen
// Date:        10/12/2009 
//
// Description: Function to retrieve Evt Id information

//  system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Genaral Tracks and Vertex
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "DataFormats/VertexReco/src/Vertex.cc"
#include "DataFormats/VertexReco/interface/VertexFwd.h"



// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"

bool RecoVtxDebug = false;

void UAHiggsTree::GetRecoVertex(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                               const string VertexCollection_ , vector<MyVertex>& VertexVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;

   VertexVector.clear();
   MyVertex myvertex;

   Handle<reco::VertexCollection> vtxcoll ;
   iEvent.getByLabel(VertexCollection_,vtxcoll);

   if (RecoVtxDebug) cout  << VertexCollection_ << " : Id  position "<< endl ;

   for(VertexCollection::const_iterator p=vtxcoll->begin(); p!= vtxcoll->end() ; ++p)
   {

      myvertex.id        = vtxid++;
      myvertex.x         = p->x()  ;
      myvertex.y         = p->y()  ;
      myvertex.z         = p->z()  ;
      myvertex.xerr      = p->xError()  ;
      myvertex.yerr      = p->yError()  ;
      myvertex.zerr      = p->zError()  ;
     
     
     
      if (RecoVtxDebug)
        cout << myvertex.id << " " << p->position() << endl;

      myvertex.ex        = p->xError()  ;
      myvertex.ey        = p->yError()  ;
      myvertex.ez        = p->zError()  ;
      myvertex.validity  = p->isValid() ;
      myvertex.fake      = p->isFake()  ;
      if ( ! myvertex.fake )
        myvertex.chi2n     = p->normalizedChi2() ;
      else
        myvertex.chi2n     = -99. ;
      myvertex.chi2        = p->ndof();
      myvertex.ndof        = p->chi2();
      myvertex.ntracks   = p->tracksSize() ;

      Double_t sumpt = 0;
  
      for (reco::Vertex::trackRef_iterator iTrack = p->tracks_begin(); iTrack!=p->tracks_end(); ++iTrack) {
           sumpt += (*iTrack)->pt();
         //  cout << sumpt  << endl;
      }
     
      myvertex.SumPtTracks   = sumpt ;
   
      
      
      
      VertexVector.push_back(myvertex);
      vtxid_xyz.push_back(p->position());
  
     
   
   }   

}


void UAHiggsTree::InitRecoVertex( vector<string> Vertexs, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = Vertexs.begin(); icoll!= Vertexs.end();icoll++){
      tree->Branch( icoll->c_str(), &(allVertexs[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllVertexs( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> Vertexs, vector<MyVertex> allVertexs[5] )
{
  for (unsigned int i=0; i!= Vertexs.size(); i++){
       GetRecoVertex(iEvent,iSetup,Vertexs.at(i),allVertexs[i]);
       }

}
