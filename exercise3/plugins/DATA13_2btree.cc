#include "LongExercises/CMSPOS2019/Tracking/interface/DATA13_2btree.h"

using pat::PATSingleVertexSelector;

using namespace std;
using namespace edm;
using namespace reco;

class DATA13_2btree : public edm::EDAnalyzer {
 public:
 explicit DATA13_2btree(const edm::ParameterSet&);
 ~DATA13_2btree();

 static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


 private:
 virtual void beginJob() ;
 virtual void analyze(const edm::Event&, const edm::EventSetup&);
 virtual void endJob() ;

 edm::InputTag assocTags_;
 std::map<std::string,TH1F*> histContainer_;

 std::map<std::string,TH2F*> histContainer2_;

 std::map<std::string,TProfile*> tprofile_;

 virtual void beginRun(edm::Run const&, edm::EventSetup const&);
 virtual void endRun(edm::Run const&, edm::EventSetup const&);
 virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
 virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
 int i;
 int run_number = 0, lumi = 0;
 edm::EDGetToken tracks_;
 edm::EDGetToken hVtx_;
 edm::EDGetToken beamSpotHandle_;
 edm::EDGetToken trigger;

 TTree *Tree;
 double Pis_pt, Pis_eta, Pis_phi;
 double Pi_pt, Pi_eta, Pi_phi;
 double K_pt, K_eta, K_phi;
 double DS_pt, DS_eta, DS_phi;
 double D0_pt, D0_eta, D0_phi;
 double CL_vertex, sum_ptVertex2, sum_ptVertex;
 double x_p, y_p, z_p; 
 double x_s, y_s, z_s; 
 double L_abs, L_sigma;
 double cos_phi;
 int vertex_size, num_tracks, pt_tracks;
 bool passTrigger;
      // ----------member data ---------------------------
};

DATA13_2btree::DATA13_2btree(const edm::ParameterSet& iConfig)
{
 edm::Service<TFileService> fs;
 Tree= fs->make<TTree>("Analysis","Analysis");

 Tree->Branch("run_number", &run_number, "run_number/I");
 Tree->Branch("lumi", &lumi, "lumi/I");

 Tree->Branch("Pis_pt",&Pis_pt,"Pis_pt/D");
 Tree->Branch("Pis_eta",&Pis_eta,"Pis_eta/D");
 Tree->Branch("Pis_phi",&Pis_phi,"Pis_phi/D");

 Tree->Branch("Pi_pt",&Pi_pt,"Pi_pt/D");
 Tree->Branch("Pi_eta",&Pi_eta,"Pi_eta/D");
 Tree->Branch("Pi_phi",&Pi_phi,"Pi_phi/D");

 Tree->Branch("K_pt",&K_pt,"K_pt/D");
 Tree->Branch("K_eta",&K_eta,"K_eta/D");
 Tree->Branch("K_phi",&K_phi,"K_phi/D");

 Tree->Branch("DS_pt",&DS_pt,"DS_pt/D");
 Tree->Branch("DS_eta",&DS_eta,"DS_eta/D");
 Tree->Branch("DS_phi",&DS_phi,"DS_phi/D");

 Tree->Branch("D0_pt",&D0_pt,"D0_pt/D");
 Tree->Branch("D0_eta",&D0_eta,"D0_eta/D");
 Tree->Branch("D0_phi",&D0_phi,"D0_phi/D");

 Tree->Branch("CL_vertex",&CL_vertex,"CL_vertex/D");
 
 Tree->Branch("x_p",&x_p,"x_p/D");
 Tree->Branch("y_p",&y_p,"y_p/D");
 Tree->Branch("z_p",&z_p,"z_p/D");
 
 Tree->Branch("x_s",&x_s,"x_s/D");
 Tree->Branch("y_s",&y_s,"y_s/D");
 Tree->Branch("z_s",&z_s,"z_s/D");
 
 Tree->Branch("L_abs",&L_abs,"L_abs/D");
 Tree->Branch("L_sigma",&L_sigma,"L_sigma/D");
 Tree->Branch("cos_phi",&cos_phi,"cos_phi/D");
 Tree->Branch("vertex_size",&vertex_size,"vertex_size/I");
 Tree->Branch("num_tracks",&num_tracks,"num_tracks/I");
 Tree->Branch("pt_tracks",&pt_tracks,"pt_tracks/D");
 Tree->Branch("sum_ptVertex",&sum_ptVertex,"sum_ptVertex/D");
 Tree->Branch("sum_ptVertex2",&sum_ptVertex2,"sum_ptVertex2/D");
 Tree->Branch("passTrigger", &passTrigger, "passTrigger/B");
 tracks_= consumes<reco::TrackCollection>(edm::InputTag("generalTracks"));
 hVtx_= consumes<std::vector<reco::Vertex>>(edm::InputTag("offlinePrimaryVertices"));
 beamSpotHandle_= consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"));
 trigger = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","","HLT"));
}

DATA13_2btree::~DATA13_2btree()
{
 

}


void
DATA13_2btree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 using namespace edm;

 edm::Handle<reco::TrackCollection> tracks;
 iEvent.getByToken(tracks_ , tracks );

 reco::BeamSpot beamSpot;
 edm::Handle<reco::BeamSpot> beamSpotHandle;
 iEvent.getByToken(beamSpotHandle_ , beamSpotHandle);

 edm::ESHandle<TransientTrackBuilder> theB;
 iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);

 edm::ESHandle<TransientTrackBuilder> theB1;
 iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB1);

 double pi_mass = 0.13957018;
 double K_mass = 0.493677;
 double D0_mass = 1.864841;

 edm::Handle<edm::TriggerResults> trigResults;
 iEvent.getByToken(trigger, trigResults);

 edm::Handle<std::vector<reco::Vertex>> hVtx;
 iEvent.getByToken(hVtx_ , hVtx); 
 reco::Vertex primVertex;

  //// try to write your code for the D*+ -> D0 pi+_slow -> k- pi+ pi+_slow selection


}

// ------------ method called once each job just before starting event loop  ------------
void 
DATA13_2btree::beginJob()
{

edm::Service<TFileService> fs;

//variabili vertice

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DATA13_2btree::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
DATA13_2btree::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
DATA13_2btree::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
DATA13_2btree::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
DATA13_2btree::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DATA13_2btree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DATA13_2btree);
