#include "TVector3.h"
#include "../include/MyGenPart.h"
#include "../include/MyMuon.h"
#include "../include/MyElectron.h"

double deltaR(double , double , double , double );

bool isMatched ( MyGenPart *gp1 , MyGenPart *gp2 , double dRCut = 0.1 ) {
  double dR = deltaR( gp1->eta , gp2->eta , gp1->phi , gp2->phi  ) ;
  if ( dR <= dRCut ) return true;
  return false;
} 

bool isMatched ( MyGenPart *gp , MyElectron *ele , double dRCut = 0.1 ) {
  double dR = deltaR( gp->eta , ele->eta , gp->phi , ele->phi  ) ;
  if ( dR <= dRCut ) return true;
  return false;
} 

bool isMatched ( MyGenPart *gp , MyMuon *muo , double dRCut = 0.1 ) {
  double dR = deltaR( gp->eta , muo->eta , gp->phi , muo->phi  ) ;
  if ( dR <= dRCut ) return true;
  return false;
} 

bool isMatched ( TVector3 vp ,  TVector3 vr , double dRCut = 0.1 ) {
  double dR = deltaR( vp.Eta() , vr.Eta() , vp.Phi() , vr.Phi()  ) ;
  if ( dR <= dRCut ) return true;
  return false;
} 



double GenPartMatch( vector<MyGenPart*> vgpref , vector<MyGenPart*> vgppro ) {

  double mindR = 999. ;

  for(vector<MyGenPart*>::iterator itr = vgpref.begin() ; itr != vgpref.end() ; ++itr){
     for(vector<MyGenPart*>::iterator itp = vgppro.begin() ; itp != vgppro.end() ; ++itp){
        double dR = deltaR( (*itr)->eta , (*itp)->eta , (*itr)->phi , (*itp)->phi  ) ;
        if ( fabs(dR) <  fabs(mindR) )  mindR = dR ;
     }
  }
  return mindR;

}

double RecoElectronMatch( vector<MyGenPart*> vgpref , vector<MyElectron*> velepro ) {

  double mindR = 999. ;

  for(vector<MyGenPart*>::iterator itr = vgpref.begin() ; itr != vgpref.end() ; ++itr){
    for(vector<MyElectron*>::iterator itp = velepro.begin() ; itp != velepro.end() ; ++itp){
        double dR = deltaR( (*itr)->eta , (*itp)->eta , (*itr)->phi , (*itp)->phi  ) ;
        if ( fabs(dR) <  fabs(mindR) )  mindR = dR ;
    }
  }
  return mindR;

}

double RecoMuonMatch( vector<MyGenPart*> vgpref , vector<MyMuon*> velepro ) {

  double mindR = 999. ;

  for(vector<MyGenPart*>::iterator itr = vgpref.begin() ; itr != vgpref.end() ; ++itr){
    for(vector<MyMuon*>::iterator itp = velepro.begin() ; itp != velepro.end() ; ++itp){
        double dR = deltaR( (*itr)->eta , (*itp)->eta , (*itr)->phi , (*itp)->phi  ) ;
        if ( fabs(dR) <  fabs(mindR) )  mindR = dR ;
    }
  }
  return mindR;

}

