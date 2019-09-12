#include "LongExerciseTracking/exercise3/interface/MC13_2btree.h"


using namespace std;
using namespace edm;
using namespace reco;


class MC13_2btree : public edm::EDAnalyzer {
 public:
 explicit MC13_2btree(const edm::ParameterSet&);
 ~MC13_2btree();

 static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

 private:
 virtual void beginJob() ;
 virtual void analyze(const edm::Event&, const edm::EventSetup&);
 virtual void endJob() ;

 edm::InputTag assocTags_;

 std::map<std::string,TH1F*> histContainer_;

 std::map<std::string,TH2F*> histContainer2_;

 virtual void beginRun(edm::Run const&, edm::EventSetup const&);
 virtual void endRun(edm::Run const&, edm::EventSetup const&);
 virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
 virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
 int i;
  
 edm::EDGetToken tracks_;
 edm::EDGetToken hVtx_;
 edm::EDGetToken beamSpotHandle_;
 edm::EDGetToken genParticles_;
 edm::EDGetToken hPU_;
 
 //define a new tree for the reco quantities
 
 TTree *genTree;
 double Pis_pt_gen, Pis_eta_gen, Pis_phi_gen;
 double Pi_pt_gen, Pi_eta_gen, Pi_phi_gen;
 double K_pt_gen, K_eta_gen, K_phi_gen;
 double DS_pt_gen, DS_eta_gen, DS_phi_gen;
 double D0_pt_gen, D0_eta_gen, D0_phi_gen;

 // define here the variables you want to put inside the tree as done above for the gen variables

 // ----------member data ---------------------------
};

MC13_2btree::MC13_2btree(const edm::ParameterSet& iConfig)
{
 edm::Service<TFileService> fs;

 tracks_= consumes<reco::TrackCollection>(edm::InputTag("generalTracks"));
 hVtx_= consumes<std::vector<reco::Vertex>>(edm::InputTag("offlinePrimaryVertices"));
 beamSpotHandle_= consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"));
 genParticles_= consumes<edm::View<reco::GenParticle>>(edm::InputTag("genParticles"));
 hPU_ = consumes<std::vector<PileupSummaryInfo>>(edm::InputTag("addPileupInfo"));

 genTree = fs->make<TTree>("Gen", "Gen");

 genTree->Branch("Pis_pt_gen",&Pis_pt_gen,"Pis_pt_gen/D");
 genTree->Branch("Pis_eta_gen",&Pis_eta_gen,"Pis_eta_gen/D");
 genTree->Branch("Pis_phi_gen",&Pis_phi_gen,"Pis_phi_gen/D");

 genTree->Branch("Pi_pt_gen",&Pi_pt_gen,"Pi_pt_gen/D");
 genTree->Branch("Pi_eta_gen",&Pi_eta_gen,"Pi_eta_gen/D");
 genTree->Branch("Pi_phi_gen",&Pi_phi_gen,"Pi_phi_gen/D");

 genTree->Branch("K_pt_gen",&K_pt_gen,"K_pt_gen/D");
 genTree->Branch("K_eta_gen",&K_eta_gen,"K_eta_gen/D");
 genTree->Branch("K_phi_gen",&K_phi_gen,"K_phi_gen/D");
 
 genTree->Branch("D0_pt_gen",&D0_pt_gen,"D0_pt_gen/D");
 genTree->Branch("D0_eta_gen",&D0_eta_gen,"D0_eta_gen/D");
 genTree->Branch("D0_phi_gen",&D0_phi_gen,"D0_phi_gen/D");

 genTree->Branch("DS_pt_gen",&DS_pt_gen,"DS_pt_gen/D");
 genTree->Branch("DS_eta_gen",&DS_eta_gen,"DS_eta_gen/D");
 genTree->Branch("DS_phi_gen",&DS_phi_gen,"DS_phi_gen/D");

 // do the same for the reco tree, calling each branch you want to define
 
}

MC13_2btree::~MC13_2btree()
{
 

}


void
MC13_2btree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
 using namespace edm;

 edm::Handle<edm::View<reco::GenParticle> > genParticles;
 iEvent.getByToken(genParticles_, genParticles);
   
 edm::Handle<reco::TrackCollection> tracks;
 iEvent.getByToken(tracks_ , tracks );

 reco::BeamSpot beamSpot;
 edm::Handle<reco::BeamSpot> beamSpotHandle;
 iEvent.getByToken(beamSpotHandle_ , beamSpotHandle);

 edm::ESHandle<TransientTrackBuilder> theB;
 iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
  
 edm::ESHandle<TransientTrackBuilder> theB1;
 iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB1);

 int Dstar = 0, D0 = 0, Pislow = 0, Piplus = 0, Kminus = 0;
 double pi_mass = 0.13957018;
 double K_mass = 0.493677;
 double D0_mass = 1.864841;    
 int id = 0, n = 0, m= 0;
  
 TLorentzVector KvectorGen;
 TLorentzVector PivectorGen;
 TLorentzVector D0vectorGen;
 TLorentzVector PisvectorGen;
 TLorentzVector DSvectorGen;
 
		/*########### reconstruction of the chain at gen level ##########*/

 for(size_t i = 0; i < genParticles->size(); ++ i) {
  const GenParticle & p= (*genParticles)[i];
  id = p.pdgId();
  if (id == 413){Dstar ++;
   m = p.numberOfDaughters();
   if(m == 2){
    Pislow = 0;
    D0 = 0;   
    for(int i = 0; i < m; ++ i) {
     const Candidate * d = p.daughter( i );
     id = d->pdgId();
     if(id == 211){
      Pislow++;
      Pis_pt_gen = d->pt();
      Pis_eta_gen = d->eta();
      Pis_phi_gen = d->phi();
      PisvectorGen.SetPtEtaPhiM(Pis_pt_gen, Pis_eta_gen, Pis_phi_gen, pi_mass);
     }
     else if( id == 421 ){
      D0++;
      n = d->numberOfDaughters();
      if(n == 2){
       Piplus=0; Kminus=0; 
       for(int j = 0; j < n; ++ j) {
        const Candidate * e = d->daughter( j );
        int id2 = e->pdgId();
        if(id2 == 211) {
         Piplus++;
         Pi_pt_gen = e->pt();
         Pi_eta_gen = e->eta();
         Pi_phi_gen = e->phi();
         PivectorGen.SetPtEtaPhiM(Pi_pt_gen, Pi_eta_gen, Pi_phi_gen, pi_mass); 
        }
        if(id2 == -321) {
         Kminus++;
         K_pt_gen = e->pt();
         K_eta_gen = e->eta();
         K_phi_gen = e->phi();
         KvectorGen.SetPtEtaPhiM(K_pt_gen, K_eta_gen, K_phi_gen, K_mass);
        } 
       }//for su due corpi
      }//D0 in due corpi           
     }//id D0
    }//for decadim
   }//prodotti decad D*m
  }//D* meno 
 } //for genparticle

 if(Pislow == 1 && D0 == 1){
  if(Kminus == 1 && Piplus == 1){
   D0vectorGen = PivectorGen + KvectorGen;
   D0_pt_gen = D0vectorGen.Pt();
   DSvectorGen = D0vectorGen + PisvectorGen;
   DS_pt_gen = DSvectorGen.Pt();
   genTree->Fill();

		/*##### info vertices ######*/

   edm::Handle<std::vector<reco::Vertex> > hVtx;
   iEvent.getByToken(hVtx_ , hVtx);
   reco::Vertex primVertex;
   reco::Vertex primVertex_tmp;

   if(hVtx->size() > 0){ 

    /*##### beam spot definition ######*/

    double bsx = 0, bsy = 0, bsz = 0;
    if ( beamSpotHandle.isValid() ){ beamSpot = *beamSpotHandle;
     bsx = beamSpot.x0();
     bsy = beamSpot.y0();
     bsz = beamSpot.z0();
    }
    GlobalPoint BeamSpotGP(bsx, bsy, bsz);

    int sameVertex = 0, ntracks = 0, pttracks = 0;
    double inv_mass1 = 0, sigma_L = 0, CL = 0;
    bool goodtracks=false;
    float v_chi2 = 0;
    double deriv[3];
    double cov_sv[3][3];
    double cov_pv[3][3];
    double xprim = 0, yprim = 0, zprim = 0, xsec = 0, ysec = 0, zsec = 0, dx = 0, dy = 0, dz = 0, px = 0, py = 0, pz = 0, pi = 0, cosphi = 0, L = 0;
    bool goodvertex = false;

    for (unsigned int t = 0; t < hVtx->size(); t++){
     primVertex_tmp = hVtx->at(t);
     if(!primVertex_tmp.isFake()  && primVertex_tmp.isValid() && primVertex_tmp.ndof() > 4 && fabs(primVertex_tmp.z()-bsz) < 10 ){
      primVertex = primVertex_tmp;
      goodvertex = true;
      break;
      }
     }

    if(goodvertex){


				  //######### tracks preselection ##########

      			//############ combinatorial #############

                // D0 candidates selection

              // third track selection 

    }//good vertex
   }//#vertices > 0
  } //D0 
 }//D*
}

// ------------ method called once each job just before starting event loop  ------------
void 
MC13_2btree::beginJob()
{

edm::Service<TFileService> fs;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MC13_2btree::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MC13_2btree::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MC13_2btree::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MC13_2btree::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MC13_2btree::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MC13_2btree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MC13_2btree);
