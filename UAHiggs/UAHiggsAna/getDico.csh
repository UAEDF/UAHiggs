#!/bin/bash

rm -fr LinkDef.C LinkDef.h tmp.h
rm -fr *.d *.so

wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyEvtId.h?view=co -O MyEvtId.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyGenKin.h?view=co -O MyGenKin.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyGenPart.h?view=co -O MyGenPart.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyL1Trig.h?view=co -O MyL1Trig.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyPart.h?view=co -O MyPart.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyTracks.h?view=co -O MyTracks.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyVertex.h?view=co -O MyVertex.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyBeamSpot.h?view=co -O MyBeamSpot.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MassParticles.h?view=co -O MassParticles.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyJet.h?view=co -O MyJet.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyGenJet.h?view=co -O MyGenJet.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyHLTrig.h?view=co -O MyHLTrig.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyElectron.h?view=co -O MyElectron.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyGenMET.h?view=co -O MyGenMET.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyMET.h?view=co -O MyMET.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/MyMuon.h?view=co -O MyMuon.h -o /dev/null
wget http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/UAHiggs/UAHiggs/UAHiggsTree/interface/LinkDef.h?view=co -O tmp.h -o /dev/null


sed "s:#endif::" < tmp.h > LinkDef.h
echo "#pragma link C++ class GenPartPlots+;">>LinkDef.h
echo "#pragma link C++ class ElectronPlots+;">>LinkDef.h
echo "#pragma link C++ class MuonPlots+;">>LinkDef.h
echo "#pragma link C++ class LeptonPair+;">>LinkDef.h
echo "#pragma link C++ class LeptonPairPlots+;">>LinkDef.h
echo "#pragma link C++ class vector<LeptonPair>+;">>LinkDef.h
echo "#endif">>LinkDef.h
rm -f tmp.h

