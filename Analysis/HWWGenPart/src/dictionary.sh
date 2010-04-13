#!/bin/bash
rootcint -f eventdict.cc -c -I${PWD}/../../.. \
         -p \
	    Analysis/HWWGenPart/interface/MyEvtId.h \
	    Analysis/HWWGenPart/interface/MyL1Trig.h \
	    Analysis/HWWGenPart/interface/MyPart.h \
 	    Analysis/HWWGenPart/interface/MyGenKin.h \
            Analysis/HWWGenPart/interface/MyGenPart.h \
	    Analysis/HWWGenPart/interface/MyGenJet.h \
	    Analysis/HWWGenPart/interface/MyBeamSpot.h \
	    Analysis/HWWGenPart/interface/MyVertex.h \
	    Analysis/HWWGenPart/interface/MyTracks.h \
	    Analysis/HWWGenPart/interface/MyElectron.h \
	    Analysis/HWWGenPart/interface/MyMuon.h \
            Analysis/HWWGenPart/interface/LinkDef.h
