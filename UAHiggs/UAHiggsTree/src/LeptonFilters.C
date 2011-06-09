// system include files
#include <memory>
#include <string>
#include <iostream>
// Muon Includes
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
// Gsf Electron
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronIsoCollection.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronIsoNumCollection.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/ClusterShape.h"
#include "DataFormats/EgammaReco/interface/BasicClusterShapeAssociation.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/Common/interface/ValueMap.h"


// UAHiggsTree UAHiggs class declaration
#include "UAHiggs/UAHiggsTree/interface/UAHiggsTree.h"
#include "TRandom.h"


bool UAHiggsTree::PassLeptonFilter(vector<MyElectron> allElectrons[5],vector<MyMuon> allMuons[5], double ptCut ){
    bool keep = false;
        for(vector<MyElectron>::iterator it_ele = allElectrons[0].begin() ; it_ele != allElectrons[0].end() ; ++it_ele){
            if(it_ele->pt >= ptCut) keep = true; 
    	 //   cout<<"ele: "<<it_ele->pt<<","<<it_ele->Part.charge<<endl;
	//    cout<<keep<<endl;
	}     
        for(vector<MyMuon>::iterator it_mu = allMuons[0].begin() ; it_mu != allMuons[0].end() ; ++it_mu){
            if(it_mu->pt >= ptCut) keep = true; 
    	 //   cout<<"mu: "<<it_mu->pt<<","<<it_mu->Part.charge<<endl;
         //   cout<<keep<<endl;
        } 
  //  cout<<"keep inside func: "<<keep<<endl;
    return keep;




}

bool UAHiggsTree::PassLeptonPairFilter(vector<MyElectron> allElectrons[5],vector<MyMuon> allMuons[5], double ptCut ){

  int  nLeptonPlus = 0 ;
  int  nLeptonMin  = 0 ;

  for(vector<MyElectron>::iterator itele = allElectrons[0].begin() ; itele != allElectrons[0].end() ; ++itele){
    if( itele->pt >= ptCut) {
    //  cout<<"ele: "<<itele->pt<<","<<itele->Part.charge<<endl;
      if( itele->Part.charge > 0 ) { ++nLeptonPlus ; }
      else                         { ++nLeptonMin  ; }
    }
  }

  for(vector<MyMuon>::iterator itmu = allMuons[0].begin() ; itmu != allMuons[0].end() ; ++itmu){
    if( itmu->pt >= ptCut) {
    //  cout<<"mu: "<<itmu->pt<<","<<itmu->Part.charge<<endl;
      if( itmu->Part.charge > 0 ) { ++nLeptonPlus ; }
      else                        { ++nLeptonMin  ; }
    }
  }
//  cout<<nLeptonPlus<<","<<nLeptonMin<<endl;
  if (  nLeptonPlus > 0 && nLeptonMin > 0 ) return true ;
  return false ;

}
    
/*  
   //  ------make electron-electron pairs ---------
  int i=0;
  int j=0;
  for(vector<MyElectron>::iterator itele1 = allElectrons[0].begin() ; itele1 != allElectrons[0].end() ; ++itele1){
     i++;j=0;
     for(vector<MyElectron>::iterator itele2 = allElectrons[0].begin() ; itele2 != allElectrons[0].end() ; ++itele2){
         j++;
	 if(i<j){
	    if( itele1->Part.charge == - itele2->Part.charge){
	       if( (itele1->pt >= ptCut) && (itele2->pt >= ptCut) ) keep = true; break;
	        } 
	    }
         }
    }
   //  ------make muon-muon pairs ---------
   i=0;j=0;
   for(vector<MyMuon>::iterator itmu1 = allMuons[0].begin() ; itmu1 != allMuons[0].end() ; ++itmu1){
     i++;j=0;
     for(vector<MyMuon>::iterator itmu2 = allMuons[0].begin() ; itmu2 != allMuons[0].end() ; ++itmu2){
         j++;
	 if(i<j){
	    if( itmu1->Part.charge == - itmu2->Part.charge){
	       if( (itmu1->pt >= ptCut) && (itmu2->pt >= ptCut) ) keep = true; break;
	       }
	    } 
	 }
      }
  
  //  ------make electron-muon  and muon-electron pairs ---------
  
   for(vector<MyElectron>::iterator itele = allElectrons[0].begin() ; itele!= allElectrons[0].end() ; ++itele){
      for(vector<MyMuon>::iterator itmu = allMuons[0].begin() ; itmu != allMuons[0].end() ; ++itmu){
         if( itele->Part.charge == - itmu->Part.charge){
	        if( (itele->pt >= ptCut) && (itmu->pt >= ptCut) ) keep = true; break;
	        }
	    } 
	 }
  
   return keep;
  
  
  }
*/
