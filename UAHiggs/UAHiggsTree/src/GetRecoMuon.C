// Package:     UAHiggsTree
// Class:       UAHiggsTree
// author:      Xavier Janssen
// Date:        22/03/2010 
//
// Description: Function to retrieve Gsf Muon 

// system include files
#include <memory>
#include <string>
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
//#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "DataFormats/VertexReco/src/Vertex.cc"
//#include "DataFormats/VertexReco/interface/VertexFwd.h"

// Muon Includes
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

// Boris 3D IP stuff's
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "WWAnalysis/Tools/interface/VertexReProducer.h"


// UAHiggsTree UAHiggs class declaration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"


void UAHiggsTree::GetRecoMuon(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                                       const string globalMuonCollection_, vector<MyMuon>& MuonVector )
{
   using namespace std;
   using namespace edm;
   using namespace reco;

   // BORIS 3D IP stuff: Declaration
   ESHandle<TransientTrackBuilder> theTTBuilder;
   iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theTTBuilder);


   MuonVector.clear();

   Handle<MuonCollection> muonsHandle;
   try {
     iEvent.getByLabel(globalMuonCollection_,muonsHandle);
   } catch ( cms::Exception& ex ) {
    printf("Error! can't get globalMuon collection\n");
   }
   const MuonCollection & muons = *(muonsHandle.product());

   for (reco::MuonCollection::const_iterator iMuon = muons.begin(); 
        iMuon != muons.end(); iMuon++) {

     MyMuon muon;     
     
     // Global Muon
   
     muon.pt  = iMuon->pt(); 
     muon.px  = iMuon->px(); 
     muon.py  = iMuon->py(); 
     muon.pz  = iMuon->pz(); 
     muon.e   = sqrt(iMuon->momentum().mag2()+MASS_MU*MASS_MU); 
     muon.eta = iMuon->eta(); 
     muon.phi = iMuon->phi(); 
     
     
     muon.Part.v.SetPxPyPzE(iMuon->px(),
                            iMuon->py(),
                            iMuon->pz(), 
                            sqrt(iMuon->momentum().mag2()+MASS_MU*MASS_MU));
     muon.Part.charge = iMuon->charge();

     // Global Properties

     muon.nChambers             = iMuon -> numberOfChambers();
     muon.nChambersMatched      = iMuon -> numberOfMatches();
     
     muon.AllGlobalMuons                          =  muon::isGoodMuon(*iMuon,muon::AllGlobalMuons);
     muon.AllStandAloneMuons                      =  muon::isGoodMuon(*iMuon,muon::AllStandAloneMuons);
     muon.AllTrackerMuons                         =  muon::isGoodMuon(*iMuon,muon::AllTrackerMuons);
     muon.TrackerMuonArbitrated                   =  muon::isGoodMuon(*iMuon,muon::TrackerMuonArbitrated);
     muon.AllArbitrated                           =  muon::isGoodMuon(*iMuon,muon::AllArbitrated);
     muon.GlobalMuonPromptTight                   =  muon::isGoodMuon(*iMuon,muon::GlobalMuonPromptTight);
     muon.TMLastStationLoose                      =  muon::isGoodMuon(*iMuon,muon::TMLastStationLoose);
     muon.TMLastStationTight                      =  muon::isGoodMuon(*iMuon,muon::TMLastStationTight);
     muon.TM2DCompatibilityLoose                  =  muon::isGoodMuon(*iMuon,muon::TM2DCompatibilityLoose);
     muon.TM2DCompatibilityTight                  =  muon::isGoodMuon(*iMuon,muon::TM2DCompatibilityTight);
     muon.TMOneStationLoose                       =  muon::isGoodMuon(*iMuon,muon::TMOneStationLoose);
     muon.TMOneStationTight                       =  muon::isGoodMuon(*iMuon,muon::TMOneStationTight);
     muon.TMLastStationOptimizedLowPtLoose        =  muon::isGoodMuon(*iMuon,muon::TMLastStationOptimizedLowPtLoose);
     muon.TMLastStationOptimizedLowPtTight        =  muon::isGoodMuon(*iMuon,muon::TMLastStationOptimizedLowPtTight);
     muon.GMTkChiCompatibility                    =  muon::isGoodMuon(*iMuon,muon::GMTkChiCompatibility);
     muon.GMStaChiCompatibility                   =  muon::isGoodMuon(*iMuon,muon::GMStaChiCompatibility);
     muon.GMTkKinkTight                           =  muon::isGoodMuon(*iMuon,muon::GMTkKinkTight);
     muon.TMLastStationAngLoose                   =  muon::isGoodMuon(*iMuon,muon::TMLastStationAngLoose);
     muon.TMLastStationAngTight                   =  muon::isGoodMuon(*iMuon,muon::TMLastStationAngTight);
     muon.TMOneStationAngLoose                    =  muon::isGoodMuon(*iMuon,muon::TMOneStationAngLoose);
     muon.TMOneStationAngTight                    =  muon::isGoodMuon(*iMuon,muon::TMOneStationAngTight);
     muon.TMLastStationOptimizedBarrelLowPtLoose  =  muon::isGoodMuon(*iMuon,muon::TMLastStationOptimizedBarrelLowPtLoose);
     muon.TMLastStationOptimizedBarrelLowPtTight  =  muon::isGoodMuon(*iMuon,muon::TMLastStationOptimizedBarrelLowPtTight);
     
 
     muon.isoR03sumPt   = iMuon->isolationR03().sumPt   ;
     muon.isoR03emEt    = iMuon->isolationR03().emEt    ;
     muon.isoR03hadEt   = iMuon->isolationR03().hadEt   ;
     muon.isoR03hoEt    = iMuon->isolationR03().hoEt    ;
     muon.isoR03nTracks = iMuon->isolationR03().nTracks ;
     muon.isoR03nJets   = iMuon->isolationR03().nJets   ;

     muon.isoR05sumPt   = iMuon->isolationR05().sumPt   ;
     muon.isoR05emEt    = iMuon->isolationR05().emEt    ;
     muon.isoR05hadEt   = iMuon->isolationR05().hadEt   ;
     muon.isoR05hoEt    = iMuon->isolationR05().hoEt    ;
     muon.isoR05nTracks = iMuon->isolationR05().nTracks ;
     muon.isoR05nJets   = iMuon->isolationR05().nJets   ;

     muon.calEnergyEm   = iMuon->calEnergy().em   ; 
     muon.calEnergyHad  = iMuon->calEnergy().had  ;
     muon.calEnergyHo   = iMuon->calEnergy().ho   ;
     muon.calEnergyEmS9 = iMuon->calEnergy().emS9 ;
     muon.calEnergyHadS9= iMuon->calEnergy().hadS9;
     muon.calEnergyHoS9 = iMuon->calEnergy().hoS9 ;

     muon.IsGlobalMuon      = iMuon->isGlobalMuon()     ;
     muon.IsTrackerMuon     = iMuon->isTrackerMuon()    ;
     muon.IsStandaloneMuon  = iMuon->isStandAloneMuon() ;
     muon.IsCaloMuon        = iMuon->isCaloMuon()       ;

     
     
 

     // Global Muon Track
   
   if(iMuon->globalTrack().isAvailable()){
    
    reco::TrackRef glTrack = iMuon->globalTrack();
   
    muon.globalTrack.Part.v.SetPxPyPzE(glTrack->momentum().x(),
                                         glTrack->momentum().y(),
                                         glTrack->momentum().z(),
                                         sqrt(glTrack->momentum().mag2()+MASS_MU*MASS_MU));

     muon.globalTrack.Part.charge = glTrack->charge();
     muon.globalTrack.numberOfValidTkHits    =  glTrack->hitPattern().numberOfValidTrackerHits();
     muon.globalTrack.numberOfValidMuonHits  =  glTrack->hitPattern().numberOfValidMuonHits();
     
   //  cout<<glTrack->hitPattern().numberOfValidTrackerHits()<<endl;
   //  cout<<glTrack->hitPattern().numberOfValidMuonHits()<<endl;
     
     
     muon.globalTrack.numberOfValidStripHits    =  glTrack->hitPattern().numberOfValidStripHits();
     muon.globalTrack.numberOfValidPixelHits    =  glTrack->hitPattern().numberOfValidPixelHits();
     muon.globalTrack.numberOfValidMuonRPCHits  =  glTrack->hitPattern().numberOfValidMuonRPCHits();
     muon.globalTrack.numberOfValidMuonCSCHits  =  glTrack->hitPattern().numberOfValidMuonCSCHits();
     muon.globalTrack.numberOfValidMuonDTHits   =  glTrack->hitPattern().numberOfValidMuonDTHits();
     
    
    
     muon.globalTrack.nhit  =  glTrack->hitPattern().numberOfValidHits();
     muon.globalTrack.chi2n =  glTrack->normalizedChi2();
     muon.globalTrack.dz    =  glTrack->dz();

     muon.globalTrack.d0    =  glTrack->d0();

     muon.globalTrack.edz   =  glTrack->dzError();
     muon.globalTrack.ed0   =  glTrack->d0Error();
     muon.globalTrack.ept   =  glTrack->ptError();

     muon.globalTrack.vx    =  glTrack->vertex().x();
     muon.globalTrack.vy    =  glTrack->vertex().y();
     muon.globalTrack.vz    =  glTrack->vertex().z();

     muon.globalTrack.quality[0] = glTrack->quality(reco::TrackBase::qualityByName("loose"));
     muon.globalTrack.quality[1] = glTrack->quality(reco::TrackBase::qualityByName("tight"));
     muon.globalTrack.quality[2] = glTrack->quality(reco::TrackBase::qualityByName("highPurity"));

     muon.globalTrack.vtxid.clear();
     muon.globalTrack.vtxdxy.clear();
     muon.globalTrack.vtxdz.clear();

     for ( int i = 0 ; i != vtxid ; i++ )
     {
        muon.globalTrack.vtxid.push_back( i );
        muon.globalTrack.vtxdxy.push_back( glTrack->dxy( vtxid_xyz[i] ) );
        muon.globalTrack.vtxdz.push_back(  glTrack->dz( vtxid_xyz[i] )  );
     }

    }
    
    else {
     
      muon.globalTrack.d0 = -999;
      for ( int i = 0 ; i != vtxid ; i++ )
       {
         
	  muon.globalTrack.vtxid.push_back( i );
          muon.globalTrack.vtxdxy.push_back( -999 );
          muon.globalTrack.vtxdz.push_back( -999 );
       }
     
    }
    
    
   
    
     // Inner Muon Track
     
   if(iMuon->innerTrack().isAvailable()){
     
     reco::TrackRef inTrack = iMuon->innerTrack();
     muon.innerTrack.Part.v.SetPxPyPzE(inTrack->momentum().x(),
                                         inTrack->momentum().y(),
                                         inTrack->momentum().z(),
                                         sqrt(inTrack->momentum().mag2()+MASS_MU*MASS_MU));
     muon.innerTrack.Part.charge = inTrack->charge();
     
     muon.innerTrack.numberOfValidTkHits    =  inTrack->hitPattern().numberOfValidTrackerHits();
     muon.innerTrack.numberOfValidMuonHits  =  inTrack->hitPattern().numberOfValidMuonHits();
    
     muon.innerTrack.numberOfValidStripHits    =  inTrack->hitPattern().numberOfValidStripHits();
     muon.innerTrack.numberOfValidPixelHits    =  inTrack->hitPattern().numberOfValidPixelHits();
     muon.innerTrack.numberOfValidMuonRPCHits  =  inTrack->hitPattern().numberOfValidMuonRPCHits();
     muon.innerTrack.numberOfValidMuonCSCHits  =  inTrack->hitPattern().numberOfValidMuonCSCHits();
     muon.innerTrack.numberOfValidMuonDTHits   =  inTrack->hitPattern().numberOfValidMuonDTHits();
     
     muon.innerTrack.nhit  =  inTrack->hitPattern().numberOfValidHits();
     muon.innerTrack.chi2n =  inTrack->normalizedChi2();
     muon.innerTrack.dz    =  inTrack->dz();
     muon.innerTrack.d0    =  inTrack->d0();
     muon.innerTrack.edz   =  inTrack->dzError();
     muon.innerTrack.ed0   =  inTrack->d0Error();
     muon.innerTrack.ept   =  inTrack->ptError();

     muon.innerTrack.vx    =  inTrack->vertex().x();
     muon.innerTrack.vy    =  inTrack->vertex().y();
     muon.innerTrack.vz    =  inTrack->vertex().z();

     muon.innerTrack.quality[0] = inTrack->quality(reco::TrackBase::qualityByName("loose"));
     muon.innerTrack.quality[1] = inTrack->quality(reco::TrackBase::qualityByName("tight"));
     muon.innerTrack.quality[2] = inTrack->quality(reco::TrackBase::qualityByName("highPurity"));

     muon.innerTrack.vtxid.clear();
     muon.innerTrack.vtxdxy.clear();
     muon.innerTrack.vtxdz.clear();

     for ( int i = 0 ; i != vtxid ; i++ )
     {
        muon.innerTrack.vtxid.push_back( i );
        muon.innerTrack.vtxdxy.push_back( inTrack->dxy( vtxid_xyz[i] ) );
        muon.innerTrack.vtxdz.push_back(  inTrack->dz( vtxid_xyz[i] )  );
     }

     // Boris 3D IP Stuff
     int iVtx = 0;
     muon.vtxid.clear();
     muon.tip.clear();
     muon.tipErr.clear();
     muon.ip.clear();
     muon.ipErr.clear();
     muon.tip2.clear();
     muon.tip2Err.clear();
     muon.ip2.clear();
     muon.ip2Err.clear();

     // ... redo muon trajectory
     reco::TransientTrack tt = theTTBuilder->build(iMuon->innerTrack());
     // ... get beamspot + first entry in IP respecting BS
     edm::Handle<reco::BeamSpot> bs;
     iEvent.getByLabel(edm::InputTag("offlineBeamSpot"),bs);
     reco::Vertex bsvtx = reco::Vertex(reco::Vertex::Point(bs->position().x(),bs->position().y(),bs->position().z()),reco::Vertex::Error());
          Measurement1D ip     = IPTools::absoluteTransverseImpactParameter(tt,bsvtx).second;
          Measurement1D ip3D   = IPTools::absoluteImpactParameter3D(tt,bsvtx).second;
          muon.vtxid.push_back( iVtx );
          ++iVtx;
          muon.tip.push_back(    ip.value()  );
          muon.tipErr.push_back( ip.error() );
          muon.ip.push_back(     ip3D.value() );
          muon.ipErr.push_back(  ip3D.error() );
          muon.tip2.push_back(    ip.value()  );
          muon.tip2Err.push_back( ip.error() );
          muon.ip2.push_back(     ip3D.value() );
          muon.ip2Err.push_back(  ip3D.error() );


     // ... Loop on vtx collections
     for (unsigned int ivc=0; ivc!= vertexs.size(); ivc++){

       // ... get vertex collection
       edm::Handle<reco::VertexCollection> vertices;
       iEvent.getByLabel(vertexs.at(ivc),vertices);
       //cout << vertexs.at(ivc) << " -> size = " << vertices->end()-vertices->begin() <<  endl;  

       // ... prepare refitting
       VertexReProducer revertex(vertices, iEvent); 
       Handle<reco::BeamSpot>        pvbeamspot; 
       iEvent.getByLabel(revertex.inputBeamSpot(), pvbeamspot);
   
         // ... Loop on vtx in curent collection
         for(VertexCollection::const_iterator pvtx=vertices->begin(); pvtx!= vertices->end() ; ++pvtx)
         {

           reco::Vertex vertexYesB;
           reco::Vertex vertexNoB;
           reco::TrackCollection newTkCollection;

           vertexYesB = *pvtx ;   

           // ... Remove lepton track
           bool foundMatch(false);
           for (reco::Vertex::trackRef_iterator itk = pvtx->tracks_begin(); itk!=pvtx->tracks_end(); ++itk) 
           {
              bool refMatching = (itk->get() == &*(iMuon->innerTrack()) );
              if(refMatching){
                foundMatch = true;
              }else{
                newTkCollection.push_back(*itk->get());
              }     
           }//track collection for vertexNoB is set

          //cout << "checking mu matching" << endl;
          if(!foundMatch) {
	    //cout << "WARNING: no muon matching found" << endl;
	    vertexNoB = vertexYesB;
          }else{      
            vector<TransientVertex> pvs = revertex.makeVertices(newTkCollection, *pvbeamspot, iSetup) ;
            //cout << pvs.size() << endl;
            if(pvs.empty()) {
                vertexNoB = reco::Vertex(reco::Vertex::Point(bs->position().x(),bs->position().y(),bs->position().z()),
                        reco::Vertex::Error());
            } else {
	      //vertexNoB = findClosestVertex<TransientVertex>(zPos,pvs);
	      vertexNoB = pvs.front(); //take the first in the list
            }
          }

          // ... Compute 3D IP
 
          Measurement1D ip     = IPTools::absoluteTransverseImpactParameter(tt,vertexYesB).second;
          Measurement1D ip3D   = IPTools::absoluteImpactParameter3D(tt,vertexYesB).second;
          Measurement1D ip_2   = IPTools::absoluteTransverseImpactParameter(tt,vertexNoB).second;
          Measurement1D ip3D_2 = IPTools::absoluteImpactParameter3D(tt,vertexNoB).second;

          muon.vtxid.push_back( iVtx );
          ++iVtx;
          muon.tip.push_back(    ip.value()  );
          muon.tipErr.push_back( ip.error() );
          muon.ip.push_back(     ip3D.value() );
          muon.ipErr.push_back(  ip3D.error() );
          muon.tip2.push_back(    ip_2.value()  );
          muon.tip2Err.push_back( ip_2.error() );
          muon.ip2.push_back(     ip3D_2.value() );
          muon.ip2Err.push_back(  ip3D_2.error() );
/*
          if (foundMatch){
            cout << ip3D.value() << " " << ip3D_2.value() << endl;
          } 
*/
         } // END ... Loop on vtx in curent collection

       } // END ... Loop on vtx collections

     } else {
     
      muon.innerTrack.d0 = -999;
      for ( int i = 0 ; i != vtxid ; i++ )
       {
          muon.innerTrack.vtxid.push_back( i );
          muon.innerTrack.vtxdxy.push_back( -999 ) ;
          muon.innerTrack.vtxdz.push_back( -999 );
          muon.vtxid.push_back( i ) ;
          muon.tip.push_back(    -999 ) ;
          muon.tipErr.push_back( -999 ) ;
          muon.ip.push_back(     -999 ) ;
          muon.ipErr.push_back(  -999 ) ;
          muon.tip2.push_back(   -999 ) ; 
          muon.tip2Err.push_back(-999 ) ; 
          muon.ip2.push_back(    -999 ) ; 
          muon.ip2Err.push_back( -999 ) ; 


       }
     
    }
     
     // Outer Muon Track
     
   if(iMuon->outerTrack().isAvailable()){
     
     reco::TrackRef outTrack = iMuon->outerTrack();
     muon.outerTrack.Part.v.SetPxPyPzE(outTrack->momentum().x(),
                                         outTrack->momentum().y(),
                                         outTrack->momentum().z(),
                                         sqrt(outTrack->momentum().mag2()+MASS_MU*MASS_MU));
     muon.outerTrack.Part.charge = outTrack->charge();
     muon.outerTrack.numberOfValidTkHits    =  outTrack->hitPattern().numberOfValidTrackerHits();
     muon.outerTrack.numberOfValidMuonHits  =  outTrack->hitPattern().numberOfValidMuonHits();
     
     muon.outerTrack.numberOfValidStripHits    =  outTrack->hitPattern().numberOfValidStripHits();
     muon.outerTrack.numberOfValidPixelHits    =  outTrack->hitPattern().numberOfValidPixelHits();
     muon.outerTrack.numberOfValidMuonRPCHits  =  outTrack->hitPattern().numberOfValidMuonRPCHits();
     muon.outerTrack.numberOfValidMuonCSCHits  =  outTrack->hitPattern().numberOfValidMuonCSCHits();
     muon.outerTrack.numberOfValidMuonDTHits   =  outTrack->hitPattern().numberOfValidMuonDTHits();
     
     
     
     muon.outerTrack.nhit  =  outTrack->hitPattern().numberOfValidHits();
     muon.outerTrack.chi2n =  outTrack->normalizedChi2();
     muon.outerTrack.dz    =  outTrack->dz();
     muon.outerTrack.d0    =  outTrack->d0();
     muon.outerTrack.edz   =  outTrack->dzError();
     muon.outerTrack.ed0   =  outTrack->d0Error();
     muon.outerTrack.ept   =  outTrack->ptError();

     muon.outerTrack.vx    =  outTrack->vertex().x();
     muon.outerTrack.vy    =  outTrack->vertex().y();
     muon.outerTrack.vz    =  outTrack->vertex().z();

     muon.outerTrack.quality[0] = outTrack->quality(reco::TrackBase::qualityByName("loose"));
     muon.outerTrack.quality[1] = outTrack->quality(reco::TrackBase::qualityByName("tight"));
     muon.outerTrack.quality[2] = outTrack->quality(reco::TrackBase::qualityByName("highPurity"));

     muon.outerTrack.vtxid.clear();
     muon.outerTrack.vtxdxy.clear();
     muon.outerTrack.vtxdz.clear();

     for ( int i = 0 ; i != vtxid ; i++ )
     {
        muon.outerTrack.vtxid.push_back( i );
        muon.outerTrack.vtxdxy.push_back( outTrack->dxy( vtxid_xyz[i] ) );
        muon.outerTrack.vtxdz.push_back(  outTrack->dz( vtxid_xyz[i] )  );
     }
    }

    else {
      
      muon.outerTrack.d0 = -999;
      for ( int i = 0 ; i != vtxid ; i++ )
       {
          muon.outerTrack.vtxid.push_back( i );
          muon.outerTrack.vtxdxy.push_back( -999 );
          muon.outerTrack.vtxdz.push_back( -999 );
       }
     
    }
     
     
     
     MuonVector.push_back(muon);

   } // end for MuonCollection 

}

void UAHiggsTree::InitRecoMuon( vector<string> muons, TTree* tree )
{
  int i=0;
  for (vector<string>::iterator icoll = muons.begin(); icoll!= muons.end();icoll++){
      tree->Branch( icoll->c_str(), &(allMuons[i]) );
      i++;
      }

}


void UAHiggsTree::GetAllMuons( const edm::Event& iEvent, const edm::EventSetup& iSetup, const vector<string> muons, vector<MyMuon> allMuons[5] )
{
  for (unsigned int i=0; i!= muons.size(); i++){
       GetRecoMuon(iEvent,iSetup,muons.at(i),allMuons[i]);
       }

}
