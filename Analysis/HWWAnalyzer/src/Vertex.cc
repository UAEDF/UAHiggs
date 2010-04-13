#include "Analysis/HWWAnalyzer/interface/HWWAnalyzer.h"
void HWWAnalyzer::DoVertexAnalysis(const edm::Event& iEvent){
  (m->Vertex).clear();
  Handle<VertexCollection> vertexHandle;
  iEvent.getByLabel("offlinePrimaryVertices",vertexHandle);
  const reco::VertexCollection vertexCollection = *(vertexHandle.product());
  VertexCollection::const_iterator iVertex;
  cout<<"================"<<endl;
  for(iVertex = vertexCollection.begin();iVertex!= vertexCollection.end(); iVertex++){
    cout << "vertex x,y,z " << iVertex->x() << " "
	 << iVertex->y() << " "
	 << iVertex->z() << endl;
    myobject vo;
    vo.px=iVertex->x();
    vo.py=iVertex->y();
    vo.pz=iVertex->z();
    (m->Vertex).push_back(vo);
  }
}

