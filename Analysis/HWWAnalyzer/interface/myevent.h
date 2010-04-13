#ifndef __MYEVENT_HH__
#define __MYEVENT_HH__
#include "TObject.h"
using namespace std;
#include <vector>
#include <map>
#include <utility>
#include "mytrack.h"
#include "myobject.h"

class myevent : public TObject {
  
  public :
    myevent(){;}
  ~myevent(){;}

  vector<myobject> RecJets;
  vector<myobject> RecPFJetsIC5;
  vector<myobject> RecPFJetsSC5;
  vector<myobject> PreSelectedElectrons;
  vector<myobject> PreSelectedMuons;
  vector<myobject> RecMet;
  vector<myobject> RecPFMet;
  vector<myobject> GenMet;
  vector<myobject> GenJets;
  vector<myobject> MCBjets;
  vector<myobject> MCNus;
  vector<myobject> GenParticle;
  vector<myobject> Vertex; 
  vector<mytrack>  AllTracks;
  vector<double> PDF_weights1;
  vector<double> PDF_weights2;
  vector<double> PDF_weights3;
  vector<double> PDF_weights4;
  double product_central_1;
  double product_central_2;
  double product_central_3;
  double product_central_4;
  double x_1;
  double x_2;
  double Q_scale;
  int f1;
  int f2;
  double pdf_1;
  double pdf_2; 
  map<string,int> HLT;
  double weight;
  double KFactor;
  int ProcessId;
  double PtHat;
  bool PreselectionMarker;

  private :

  ClassDef (myevent,1)
};
#endif
