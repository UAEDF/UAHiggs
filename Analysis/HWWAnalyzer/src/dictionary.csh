#!/bin/csh

#eval `scramv1 runtime -csh`
rootcint -f eventdict.cc -c -I${PWD}/../../.. \
         -p Analysis/HWWAnalyzer/interface/mytrack.h \
            Analysis/HWWAnalyzer/interface/myobject.h \
            Analysis/HWWAnalyzer/interface/myevent.h \
            Analysis/HWWAnalyzer/interface/LinkDef.h
