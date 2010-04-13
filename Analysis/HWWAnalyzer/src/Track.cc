#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"
void HWWAnalyzer::DoTrackAnalysis(const edm::Event& iEvent){
  (m->AllTracks).clear();  
  Handle<reco::TrackCollection> tracksHandle ;
  iEvent.getByLabel( TrackCollection_, tracksHandle ) ;
  //tracks defined in HWWAnalyzer.h as a public variable
  tracks = tracksHandle.product();
  
  TrackCollection::const_iterator track;
  for (track = tracks->begin(); track != tracks->end(); track++) {
    mytrack to;
    to.pt=track->pt();
    to.Vz=track->vz();
    to.Chi2=track->chi2();
    to.Ndof=track->ndof();
    to.VHits=track->numberOfValidHits();
    (m->AllTracks).push_back(to);   
  }
}

