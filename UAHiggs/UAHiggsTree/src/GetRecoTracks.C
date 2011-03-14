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
#include "DataFormats/VertexReco/src/Vertex.cc"
#include "DataFormats/VertexReco/interface/VertexFwd.h"



// UAHiggsTree UAHiggs class decleration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"

//bool L1TrigDebug = false;

void UAHiggsTree::GetRecoTrack(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                               const string TrackCollection_ , vector<MyTracks>& TrackVector )
{
   using namespace std;
   using namespace edm;

   Double_t mpion = 139.57018;


   TrackVector.clear(); 

   MyTracks mytrack;

   Handle<TrackCollection> tracks;
   //iEvent.getByLabel(trackTags_,tracks);

//   iEvent.getByLabel("generalTracks",tracks);
   iEvent.getByLabel(TrackCollection_,tracks);

   for(TrackCollection::const_iterator tr = tracks->begin(); tr!=tracks->end(); ++tr)
   {
//   cout << tr->charge() << " " << tr->px() << " " << tr->py() << " " << tr->pz()   << endl;

     //mytrack.px = tr->px() ;
     //mytrack.py = tr->py() ;
     //mytrack.pz = tr->pz() ;
     //mytrack.eta= tr->eta() ;

     mytrack.Part.charge = tr->charge();
     mytrack.Part.v.SetPtEtaPhiM(tr->pt(),tr->eta(),tr->phi(), mpion );  

     mytrack.nhit  =  tr->hitPattern().numberOfValidHits();
     mytrack.chi2n =  tr->normalizedChi2();
     mytrack.dz    =  tr->dz();
     mytrack.d0    =  tr->d0();
     mytrack.edz   =  tr->dzError();
     mytrack.ed0   =  tr->d0Error();
     mytrack.ept   =  tr->ptError();

     mytrack.vx    =  tr->vertex().x();
     mytrack.vy    =  tr->vertex().y();
     mytrack.vz    =  tr->vertex().z();

     mytrack.quality[0] = tr->quality(reco::TrackBase::qualityByName("loose"));
     mytrack.quality[1] = tr->quality(reco::TrackBase::qualityByName("tight"));
     mytrack.quality[2] = tr->quality(reco::TrackBase::qualityByName("highPurity"));


     // BeamSpot (id=0) and Vertex (id>0) Links
     mytrack.vtxid.clear();
     mytrack.vtxdxy.clear();
     mytrack.vtxdz.clear();

     for ( int i = 0 ; i != vtxid ; i++ )
     {
        //cout << i << " " << vtxid_xyz[i] << endl;
        //cout << "dxy: " << tr->dxy( vtxid_xyz[i] ) << endl;  
        //cout << "dz : " << tr->dz( vtxid_xyz[i] ) << endl; 
        mytrack.vtxid.push_back( i ); 
        mytrack.vtxdxy.push_back( tr->dxy( vtxid_xyz[i] ) );
        mytrack.vtxdz.push_back(  tr->dz( vtxid_xyz[i] )  );
     }


 /* 
     cout << mytrack.Part.v.Px() << " "
          << mytrack.Part.v.Py() << " "
          << mytrack.Part.v.Pt() << endl;
*/

     TrackVector.push_back(mytrack);
   }


}



void UAHiggsTree::InitRecoTrack( vector<string> Tracks, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = Tracks.begin(); icoll!= Tracks.end();icoll++){
      tree->Branch( icoll->c_str(), &(allTracks[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllTracks( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> Tracks, vector<MyTracks> allTracks[5] )
{
  for (unsigned int i=0; i!= Tracks.size(); i++){
       GetRecoTrack(iEvent,iSetup,Tracks.at(i),allTracks[i]);
       }

}
