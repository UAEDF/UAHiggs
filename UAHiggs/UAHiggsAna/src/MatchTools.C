
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


