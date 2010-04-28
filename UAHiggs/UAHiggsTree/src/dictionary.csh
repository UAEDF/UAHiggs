#write this in case of tcshell


rootcint -f eventdict.cc -c -I${PWD}/../../.. \
         -p \
	    UAHiggs/UAHiggsTree/interface/MyEvtId.h \
	    UAHiggs/UAHiggsTree/interface/MyL1Trig.h \
	    UAHiggs/UAHiggsTree/interface/MyHLTrig.h \
	    UAHiggs/UAHiggsTree/interface/MyPart.h \
 	    UAHiggs/UAHiggsTree/interface/MyGenKin.h \
            UAHiggs/UAHiggsTree/interface/MyGenPart.h \
	    UAHiggs/UAHiggsTree/interface/MyGenJet.h \
	    UAHiggs/UAHiggsTree/interface/MyBeamSpot.h \
	    UAHiggs/UAHiggsTree/interface/MyVertex.h \
	    UAHiggs/UAHiggsTree/interface/MyTracks.h \
	    UAHiggs/UAHiggsTree/interface/MyElectron.h \
	    UAHiggs/UAHiggsTree/interface/MyMuon.h \
            UAHiggs/UAHiggsTree/interface/MyJet.h \
	    UAHiggs/UAHiggsTree/interface/MyMET.h \
	    UAHiggs/UAHiggsTree/interface/MyGenMET.h \
	    UAHiggs/UAHiggsTree/interface/LinkDef.h
