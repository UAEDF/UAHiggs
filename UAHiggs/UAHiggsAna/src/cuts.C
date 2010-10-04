

//----------------- GET THE BEST VERTEX ------------------

Double_t vtxz_cut = 15.;

int getBestVertex(vector<MyVertex>* vtxcoll){

  vector<MyVertex>::iterator goodVtx;
  int ntracks = -1;
  double chi2n=999;
  
  for(vector<MyVertex>::iterator itvtx=vtxcoll->begin();itvtx!=vtxcoll->end();++itvtx){
    if(itvtx->validity && fabs(itvtx->z)<vtxz_cut){
      if(itvtx->ntracks>ntracks){
        goodVtx  =  itvtx;
	ntracks  =  itvtx->ntracks;
	chi2n    =  itvtx->chi2n;
      }
      else if(itvtx->ntracks==ntracks){
        if(chi2n>itvtx->chi2n){
	  goodVtx  =  itvtx;
	  ntracks  =  itvtx->ntracks;
	  chi2n    =  itvtx->chi2n;
	}
      }
    }
  }
  
  if(ntracks<=0)
    return -1;
  
  return goodVtx->id;
}





//------------------------------ Electron Filter -----------------------------------------


Double_t etacut_ele = 2.5 ;
Double_t isoBarrelcut_ele = 0.07 ;
Double_t isoEndCapcut_ele = 0.03 ;
Double_t distconvcut = 0.02 ;
Double_t dcotconvcut = 0.02 ;



vector<MyElectron*> ElectronFilter(vector<MyElectron*> velec, 
                                                     int vtxId,
						     bool cutPtEta = true, 
						     bool cutd0 = true, 
						     bool cutIso = true, 
						     bool cutId = true, 
						     bool cutConv = true,
						     int  allOrBarrelOrEndcap =0,
						     Double_t ptcut_ele=20
						     )
						     {
 
  //Protecting code if no vertex were found
  if(vtxId==-1 && cutd0) velec.clear();   



  for(vector<MyElectron*>::iterator it_ele = velec.begin() ; it_ele != velec.end() ; ++it_ele){
   
     bool reject = false;
     
     
     // ------------------Pt, Eta cuts -----------------------
     
     if(cutPtEta){
        if( !( (*it_ele)->pt        > ptcut_ele)        )    reject = true; 
        if( !( fabs((*it_ele)->eta) < etacut_ele)       )    reject = true;}
      //---------------------Vertex Association ---------------
    
     if(cutd0){
       
       Double_t d0 = (*it_ele)->GsfTrack.vtxdxy.at(vtxId);
       if( !( fabs(d0) < 0.02 ) ) reject = true;
       
       }
     
     //-----------------Isolation-----------------------------
     
     if(cutIso){
       if ((*it_ele)->isBarrel){
	       if( !( ((*it_ele)->TrackIsolationDr03+max(Double_t(0),(*it_ele)->EcalRecHitIsoDr03-1.0)+(*it_ele)->HcalTowerSumEtDr03)/(*it_ele)->pt < isoBarrelcut_ele)  ) reject = true;
	       if( !((*it_ele)->TrackIsolationDr03/(*it_ele)->pt < 0.09) )reject = true;
	       if( !((*it_ele)->EcalRecHitIsoDr03/(*it_ele)->pt  < 0.07) )reject = true;
	       if( !((*it_ele)->HcalTowerSumEtDr03/(*it_ele)->pt < 0.10) )reject = true;
	    }
	      
	     
	   if ((*it_ele)->isEndCap){
	      if( !( ((*it_ele)->TrackIsolationDr03+(*it_ele)->EcalRecHitIsoDr03+(*it_ele)->HcalTowerSumEtDr03/(*it_ele)->pt) < isoEndCapcut_ele)  ) reject = true;   
              if( !((*it_ele)->TrackIsolationDr03/(*it_ele)->pt < 0.04) ) reject = true;
	      if( !((*it_ele)->EcalRecHitIsoDr03/(*it_ele)->pt  < 0.05) ) reject = true;
	      if( !((*it_ele)->HcalTowerSumEtDr03/(*it_ele)->pt < 0.025)) reject = true;}
	   }
	   
   
    
     //---------VBTF Id 80 cuts -----------------------------
      
     if(cutId){
           if ((*it_ele)->isBarrel){
            if( !((*it_ele)->CoviEtaiEta<0.01) )             reject = true;  
	    if( !(fabs((*it_ele)->dPhiSupClusTrVtx)<0.06 ) ) reject = true;
            if( !(fabs((*it_ele)->dEtaSupClusTrVtx)<0.004) ) reject = true; 
            if( !((*it_ele)->HadronicOverEm<0.04) )          reject = true;}
          if ((*it_ele)->isEndCap) {
            if( !((*it_ele)->CoviEtaiEta<0.03) )             reject = true;  
	    if( !(fabs((*it_ele)->dPhiSupClusTrVtx)<0.03 ) ) reject = true;
           // if( !(fabs((*it_ele)->dEtaSupClusTrVtx)<0.007) ) reject = true; 
            if( !((*it_ele)->HadronicOverEm<0.025)  )        reject = true;}
          }
     
      
    
     
     //-------Conversion-------------------------------------
     
     if(cutConv){
       if( (fabs((*it_ele)->dist_conv)<distconvcut) && (fabs((*it_ele)->dcot_conv)<dcotconvcut)  ) reject = true;}
  
     //------Barrel EndCap -----------------
     
     if(allOrBarrelOrEndcap==1){
        if((*it_ele)->isEndCap) reject=true;}
     if(allOrBarrelOrEndcap==2){
        if((*it_ele)->isBarrel) reject=true;}
     if(reject) velec.erase(it_ele--); 
   }
  
  return velec;
}



vector<MyElectron*> ElectronFilter(vector<MyElectron>& velec,
                                                       int vtxId,
						       bool cutPtEta = true, 
						       bool cutd0 = true, 
						       bool cutIso = true, 
						       bool cutId = true, 
						       bool cutConv = true,
						       int  allOrBarrelOrEndcap =0,
						       double ptcut_ele=20)
                                                       { 
    vector<MyElectron*>  *elec     = new vector<MyElectron*>;
    vector<MyElectron*>  *elec_out = new vector<MyElectron*>;
    
    for(vector<MyElectron>::iterator it_ele = velec.begin() ; it_ele != velec.end() ; ++it_ele){
        (*elec).push_back(&*it_ele);
    	}
    *elec_out = ElectronFilter(*elec,vtxId,cutPtEta,cutd0,cutIso,cutId,cutConv,allOrBarrelOrEndcap,ptcut_ele);
    return *elec_out;
    }


bool bigger(MyElectron*  i,MyElectron* j)  { 
      return (i->pt < j->pt); 
      }



MyElectron*  HighestPtElectron(vector<MyElectron*> velec){
             return *max_element(velec.begin(),velec.end(),bigger);
	       }


MyElectron*  HighestPtElectron(vector<MyElectron>& velec){
               vector<MyElectron*>  *elec     = new vector<MyElectron*>;
               MyElectron  *elec_out;
	       for(vector<MyElectron>::iterator it_ele = velec.begin() ; it_ele != velec.end() ; ++it_ele){
                  (*elec).push_back(&*it_ele);
    	          }
               elec_out = HighestPtElectron(*elec);
               return elec_out;
             }



//------------------------------ Muon Filter -----------------------------------------


Double_t etacut_mu = 2.4 ;
Double_t isocut_mu = 0.15 ;



vector<MyMuon*> MuonFilter(vector<MyMuon*> vmuon, 
                                         int vtxId,
					bool cutPtEta = true, 
					bool cutd0 = true, 
					bool cutIso = true, 
					bool cutId = true,
					double ptcut_mu=20) 
 {
  //Protecting code if no vertex were found
  if(vtxId==-1 && cutd0) vmuon.clear();   



  for(vector<MyMuon*>::iterator it_mu = vmuon.begin() ; it_mu != vmuon.end() ; ++it_mu){
     bool reject = false;
     
     
     // ------------------Pt, Eta cuts -----------------------
     
     if(cutPtEta){
        if( !((*it_mu)->pt        > ptcut_mu)        )    reject = true; 
        if( !(fabs((*it_mu)->eta) < etacut_mu)       )    reject = true;}
    
     //---------------------Vertex Association and NO STANDALONE Muon ---------------
    
     if(cutd0){
       Double_t d0 = (*it_mu)->globalTrack.vtxdxy.at(vtxId);
       if( !(fabs(d0) < 0.02) )            reject = true;
       if( !((*it_mu)->IsGlobalMuon) )     reject = true;
       if( !((*it_mu)->IsTrackerMuon) )    reject = true;
       }
     
     //-----------------Isolation-----------------------------
     
     if(cutIso){
        if( !( ((*it_mu)->isoR03sumPt + (*it_mu)->isoR03emEt + (*it_mu)->isoR03hadEt)/(*it_mu)->pt < isocut_mu)  ) reject = true;}
	 
     //---------VBTF Id 80 cuts -----------------------------
      
     if(cutId){
        if( !((*it_mu)->globalTrack.numberOfValidTkHits   >10)   )reject = true;   
        if( !((*it_mu)->globalTrack.numberOfValidMuonHits > 0)   )reject = true;  
        if( !((*it_mu)->globalTrack.chi2n                 <10)   )reject = true;  
          } 
       
     if(reject) vmuon.erase(it_mu--); 

  }
  
  return vmuon;
}


vector<MyMuon*> MuonFilter(vector<MyMuon>& vmuon,
                                                       int vtxId,
						       bool cutPtEta = true, 
						       bool cutd0 = true, 
						       bool cutIso = true, 
						       bool cutId = true ,
						       double ptcut_mu=20) 
						       
                                                       { 
    vector<MyMuon*>  *muo     = new vector<MyMuon*>;
    vector<MyMuon*>  *muo_out = new vector<MyMuon*>;
    
    for(vector<MyMuon>::iterator it_mu = vmuon.begin() ; it_mu != vmuon.end() ; ++it_mu){
        (*muo).push_back(&*it_mu);
    	}
    *muo_out = MuonFilter(*muo,vtxId,cutPtEta,cutd0,cutIso,cutId,ptcut_mu);
    return *muo_out;
    }










//--------------------------- Make Vector of Lepton Pairs ---------------------


bool order (LeptonPair*  i,LeptonPair* j)  { 
     
     if(i->getPtMax() >  j->getPtMax() )return true; 
     if(i->getPtMax() == j->getPtMax() )return i->getPtMin() > j->getPtMin(); 
     else return false;
     }





bool sameSign = false;

vector<LeptonPair*>* MakeLeptonPairVector(vector<MyElectron*>& velec, vector<MyMuon*>& vmuon){
  
  vector<LeptonPair*>  *pairvector     = new vector<LeptonPair*>;
  
  //  ------make electron-electron pairs ---------
  int i=0;
  int j=0;
  for(vector<MyElectron*>::iterator itele1 = velec.begin() ; itele1 != velec.end() ; ++itele1){
     i++;j=0;
     for(vector<MyElectron*>::iterator itele2 = velec.begin() ; itele2 != velec.end() ; ++itele2){
         j++;
	 if(i<j){
	    if( (*itele1)->Part.charge == - (*itele2)->Part.charge){
	       LeptonPair* pair = new LeptonPair();
	       if( (*itele1)->pt > (*itele2)->pt ) pair->fillLeptonPair(**itele1,**itele2);
	       else                                pair->fillLeptonPair(**itele2,**itele1);
	       pairvector->push_back(pair);
	       } 
	    }
         }
    }
   //  ------make muon-muon pairs ---------
   i=0;j=0;
   for(vector<MyMuon*>::iterator itmu1 = vmuon.begin() ; itmu1 != vmuon.end() ; ++itmu1){
     i++;j=0;
     for(vector<MyMuon*>::iterator itmu2 = vmuon.begin() ; itmu2 != vmuon.end() ; ++itmu2){
         j++;
	 if(i<j){
	    if( (*itmu1)->Part.charge == - (*itmu2)->Part.charge){
	       LeptonPair* pair = new LeptonPair();
	       if( (*itmu1)->pt > (*itmu2)->pt ) pair->fillLeptonPair(**itmu1,**itmu2);
	       else                              pair->fillLeptonPair(**itmu2,**itmu1);
	       pairvector->push_back(pair);
	      }
	    } 
	 }
      }
  
  //  ------make electron-muon  and muon-electron pairs ---------
  
   for(vector<MyElectron*>::iterator itele = velec.begin() ; itele!= velec.end() ; ++itele){
      for(vector<MyMuon*>::iterator itmu = vmuon.begin() ; itmu != vmuon.end() ; ++itmu){
         if( (*itele)->Part.charge == - (*itmu)->Part.charge){
	       LeptonPair* pair = new LeptonPair();
	       if( (*itele)->pt > (*itmu)->pt ) pair->fillLeptonPair(**itele,**itmu);
	       else                             pair->fillLeptonPair(**itmu,**itele);
	       pairvector->push_back(pair);
	       }
	    } 
	 }
  
  sort(pairvector->begin(), pairvector->end(),order); 
  return pairvector;
  
  }



 //---- overload the makepair function ---------------------

vector<LeptonPair*>* MakeLeptonPairVector(vector<MyElectron>& velec, vector<MyMuon>& vmuon){

    vector<MyElectron*>  *elec     = new vector<MyElectron*>;
    vector<MyMuon*>      *muon     = new vector<MyMuon    *>;
    
    vector<LeptonPair*>  *pairvector     = new vector<LeptonPair*>;
    
    
    for(vector<MyElectron>::iterator it_ele = velec.begin() ; it_ele != velec.end() ; ++it_ele){
        (*elec).push_back(&*it_ele);
    	}
    for(vector<MyMuon>::iterator it_mu = vmuon.begin() ; it_mu != vmuon.end() ; ++it_mu){
        (*muon).push_back(&*it_mu);
    	}
     
    pairvector = MakeLeptonPairVector(*elec,*muon);
    return pairvector;
    }  
    
    
    
// ----- Find type in a vector of Lepton Pairs ----------------------
   
   
   
bool find ( vector<LeptonPair*>& pair, string finalstate){
   bool found = false;
   for(vector<LeptonPair*>::iterator itpair = pair.begin() ; itpair != pair.end() ; ++itpair){
      if( (*itpair) -> type == finalstate) found = true;
      }
   return found;
   }


// -------- mll cut #1 -------------------------------

vector<LeptonPair*>   makeMllCut1 ( vector<LeptonPair*> pair ){
  for(vector<LeptonPair*>::iterator itpair = pair.begin() ; itpair != pair.end() ; ++itpair){
       if( (*itpair) -> getMll() <= 12 ) pair.erase(itpair--) ;
       }
   return pair;
   } 
    
 // -------- mll cut #2 -------------------------------

vector<LeptonPair*>   makeMllCut2 ( vector<LeptonPair*> pair ){
    for(vector<LeptonPair*>::iterator itpair = pair.begin() ; itpair != pair.end() ; ++itpair){
       if( fabs( (*itpair) -> getMll() - 91.1876 ) <= 15 ) pair.erase(itpair--);
       }
   return pair;
   } 
 
 
// -------- projected MET cut -------------------------------

vector<LeptonPair*>   makeProjectedMetCut ( vector<LeptonPair*> pair, double met, double phimet){
   
    bool reject=false;
    for(vector<LeptonPair*>::iterator itpair = pair.begin() ; itpair != pair.end() ; ++itpair){
       
       if(   ( ((*itpair)->getProjectedMet(met,phimet) < 35 )    &&  ((*itpair)->type == "ee"  ||  (*itpair)->type == "mm") )      
           ||( ((*itpair)->getProjectedMet(met,phimet) < 20 )    &&  ((*itpair)->type == "em"  ||  (*itpair)->type == "me") )  )   reject=true;  
       if(reject)pair.erase(itpair--) ;
       }
    return pair;
   
   }
    
    
    
// --------------- Jet Cleaning ---------------------------------    
     
double deltaR(double eta1, double eta2, double phi1, double phi2) 
{
  double dphi = fabs(phi1-phi2);
  if(dphi > M_PI) 
    {
      dphi = (2*M_PI - dphi);
    }
  double deta = fabs(eta1-eta2);
  return sqrt(dphi*dphi + deta*deta);
}


vector<MyJet*> makeJetCleaning(vector<MyJet*> jet, vector<MyElectron*>& ele, vector<MyMuon*>& muo, double ptmax, double eta, double dR){
     
     for(vector<MyJet*>::iterator itj = jet.begin() ; itj != jet.end() ; ++itj){
     	bool fakejet = false;
	bool reject;
	for(vector<MyElectron*>::iterator itele = ele.begin() ; itele != ele.end() ; ++itele){    
            if(deltaR((*itj)->eta,(*itele)->eta,(*itj)->phi,(*itele)->phi)< dR )fakejet=true;       
            }
	for(vector<MyMuon*>::iterator itmu = muo.begin() ; itmu != muo.end() ; ++itmu){    
            if(deltaR((*itj)->eta,(*itmu)->eta,(*itj)->phi,(*itmu)->phi)< dR )fakejet=true;       
            }
        if((*itj)->pt<ptmax || fabs( (*itj)->eta )>eta || (!fakejet))reject=true;
	
	if(reject) jet.erase(itj--); 
        }
  return jet;
  }  
    
    
vector<MyJet*> makeJetCleaning(vector<MyJet>& jet, 
			       vector<MyElectron*>& ele,
			       vector<MyMuon*>&muo,
			       double ptmax,
			       double eta,
			       double dR)
						       
                                                       { 
    vector<MyJet*>  *jetn     = new vector<MyJet*>;
    vector<MyJet*>  *jetout   = new vector<MyJet*>;
    
    for(vector<MyJet>::iterator itj = jet.begin() ; itj != jet.end() ; ++itj){
        (*jetn).push_back(&*itj);
    	}
    *jetout = makeJetCleaning(*jetn,ele,muo,ptmax,eta,dR);
    return *jetout;
    }
   

//------------ find best pair in vector of lepton pairs    -------------------------


LeptonPair* findBestPair(vector<LeptonPair*>& pair){
      LeptonPair* bestpair = new LeptonPair();
      if(pair.size()!=0)bestpair = pair.at(0);
      return bestpair;
     }


LeptonPair* findBestPair(vector<LeptonPair*>& pair, string type){
      bool found = false;
      LeptonPair* bestpair = new LeptonPair();
      for(vector<LeptonPair*>::iterator itpair = pair.begin() ; itpair != pair.end() ; ++itpair){
	  if( (*itpair) -> type == type ){
	    found = true;
	    bestpair = (*itpair);
	    break;          
            }
      }
     return bestpair;
     }






//----------  Soft Extra Muon Collection ----------    




vector<MyMuon*>  RemoveBestPairFromMuons(vector<MyMuon*>& muo ,vector<LeptonPair*>& pair, string type){ 
      bool reject=false;
      vector<MyMuon*> *muons = new vector<MyMuon*>();
      LeptonPair* bestpair = new LeptonPair();
      bestpair = findBestPair(pair,type);
      for(vector<MyMuon*>::iterator itm = muo.begin() ; itm != muo.end() ; ++itm){ 
         if( bestpair->isInside(**itm) )reject=true;
	 if(!reject) muons->push_back(*itm); 
	 }
      return *muons;
      }
 
 
 
 vector<MyMuon*>  ExtraSoftMuons(vector<MyMuon*>& muo ,vector<LeptonPair*>& pair, int vtxId, string type){ 
      vector<MyMuon*>* extrasoftmuons = new vector<MyMuon*>();
      *extrasoftmuons = RemoveBestPairFromMuons(muo,pair,type);
      for(vector<MyMuon*>::iterator itm = extrasoftmuons->begin() ; itm != extrasoftmuons->end() ; ++itm){ 
      //    bool foundinpair = false;
	  bool reject      = false;
	   if(    !( (*itm)->pt>3)
	      || !( (*itm)->IsTrackerMuon)
	      || !( (*itm)->TMOneStationAngTight)
	      || !( (*itm)->globalTrack.numberOfValidTkHits   >10)
	      || !( fabs( (*itm)->globalTrack.vtxdxy.at(vtxId))<0.2 )  ) reject = true;
               
          if(reject) extrasoftmuons->erase(itm--); 
      }
      
     return *extrasoftmuons;	   
     
  }     
	     




 vector<MyMuon*>  ExtraMuons(vector<MyMuon*>& muo ,vector<LeptonPair*>& pair, int vtxId, string type){ 
      vector<MyMuon*>* extramuons = new vector<MyMuon*>();
      *extramuons = RemoveBestPairFromMuons(muo,pair,type);
      *extramuons = MuonFilter(*extramuons,vtxId, true, true, true, true,10);
      return *extramuons;	   
     
  } 





//   -----------------Clean Electrons ---------------------------------------------	     
	     





vector<MyElectron*>  RemoveBestPairFromElectrons(vector<MyElectron*>& ele ,vector<LeptonPair*>& pair, string type){ 
      bool reject=false;
      vector<MyElectron*> *electrons = new vector<MyElectron*>();
      LeptonPair* bestpair = new LeptonPair();
      bestpair = findBestPair(pair,type);
      for(vector<MyElectron*>::iterator ite = ele.begin() ; ite != ele.end() ; ++ite){ 
         if( bestpair->isInside(**ite) )reject=true;
	 if(!reject) electrons->push_back(*ite); 
	 }
      return *electrons;
      }
 


vector<MyElectron*> ElectronsCleaning(vector<MyElectron*> velec, vector<MyMuon*> vmuon) {
  vector<MyElectron*> *electrons = new vector<MyElectron*>();
  for(vector<MyElectron*>::iterator it_ele = velec.begin() ; it_ele != velec.end() ; ++it_ele){
     bool reject = false;
     for(vector<MyMuon*>::iterator it_mu = vmuon.begin() ; it_mu != vmuon.end() ; ++it_mu){
        double dR = deltaR((*it_ele)->eta,(*it_mu)->eta,(*it_ele)->phi,(*it_mu)->phi);
	if(dR<0.1) reject = true; 
     }
    if(!reject) electrons->push_back(*it_ele); 
   }
  
  return *electrons;
}   
 






vector<MyElectron*>  ExtraElectrons(vector<MyElectron*>& ele ,  vector<LeptonPair*>& pair, int vtxId, string type){ 
      vector<MyElectron*>* extraelectrons = new vector<MyElectron*>();
        *extraelectrons = RemoveBestPairFromElectrons(ele,pair,type);
      *extraelectrons = ElectronFilter(*extraelectrons,vtxId, true, true, true, true,10);
      return *extraelectrons;	   
     } 





//--------------- substract collection from collection --------------


vector<MyElectron*> subs(vector<MyElectron*> ele1, vector<MyElectron*> ele2){
        for(vector<MyElectron*>::iterator it_ele2 = ele2.begin() ; it_ele2 != ele2.end() ; ++it_ele2){
           bool reject = false; 
	   for(vector<MyElectron*>::iterator it_ele1 = ele1.begin() ; it_ele1 != ele1.end() ; ++it_ele1){	          
	        if( *it_ele1 == *it_ele2)reject=true;     
		}    
           if(reject)ele2.erase(it_ele2--); 
           }
       return ele2;
       }
       
vector<MyMuon*> subs(vector<MyMuon*> mu1, vector<MyMuon*> mu2){
        for(vector<MyMuon*>::iterator it_mu2 = mu2.begin() ; it_mu2 != mu2.end() ; ++it_mu2){
           bool reject = false; 
	   for(vector<MyMuon*>::iterator it_mu1 = mu1.begin() ; it_mu1 != mu1.end() ; ++it_mu1){	          
	       if( *it_mu1 == *it_mu2)reject=true;     
	       }    
           if(reject)mu2.erase(it_mu2--); 
           }
	return mu2;		     
	}	     