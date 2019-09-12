#include "LongExerciseTracking/exercise3/interface/MC13_4btree.h"

using namespace std;
using namespace edm;
using namespace reco;


//
// class declaratio
//

class MC13_4btree : public edm::EDAnalyzer {
 public:
 explicit MC13_4btree(const edm::ParameterSet&);
 ~MC13_4btree();
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

 TTree *Tree;
 TTree *genTree;
 double Pis_pt_gen, Pis_eta_gen, Pis_phi_gen;
 double Pi1_pt_gen, Pi1_eta_gen, Pi1_phi_gen;
 double Pi2_pt_gen, Pi2_eta_gen, Pi2_phi_gen;
 double Pim_pt_gen, Pim_eta_gen, Pim_phi_gen;
 double K_pt_gen, K_eta_gen, K_phi_gen;
 double DS_pt_gen, DS_eta_gen, DS_phi_gen;
 double D0_pt_gen, D0_eta_gen, D0_phi_gen;
 double Pis_pt, Pis_eta, Pis_phi;
 double Pi1_pt, Pi1_eta, Pi1_phi;
 double Pi2_pt, Pi2_eta, Pi2_phi;
 double Pim_pt, Pim_eta, Pim_phi;
 double K_pt, K_eta, K_phi;
 double DS_pt, DS_eta, DS_phi;
 double D0_pt, D0_eta, D0_phi;
 double CL_vertex;
 double x_p, y_p, z_p;
 double x_s, y_s, z_s;
 double L_abs, L_sigma;
 double cos_phi;
 int vertex_size, num_tracks;

      // ----------member data ---------------------------
};

MC13_4btree::MC13_4btree(const edm::ParameterSet& iConfig)
{
 tracks_= consumes<reco::TrackCollection>(edm::InputTag("generalTracks"));
 hVtx_= consumes<std::vector<reco::Vertex>>(edm::InputTag("offlinePrimaryVertices"));
 beamSpotHandle_= consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"));
 genParticles_= consumes<edm::View<reco::GenParticle>>(edm::InputTag("genParticles"));

 edm::Service<TFileService> fs;

 genTree = fs->make<TTree>("Gen", "Gen");

 genTree->Branch("Pis_pt_gen",&Pis_pt_gen,"Pis_pt_gen/D");
 genTree->Branch("Pis_eta_gen",&Pis_eta_gen,"Pis_eta_gen/D");
 genTree->Branch("Pis_phi_gen",&Pis_phi_gen,"Pis_phi_gen/D");

 genTree->Branch("Pim_pt_gen",&Pim_pt_gen,"Pim_pt_gen/D");
 genTree->Branch("Pim_eta_gen",&Pim_eta_gen,"Pim_eta_gen/D");
 genTree->Branch("Pim_phi_gen",&Pim_phi_gen,"Pim_phi_gen/D");

 genTree->Branch("Pi1_pt_gen",&Pi1_pt_gen,"Pi1_pt_gen/D");
 genTree->Branch("Pi1_eta_gen",&Pi1_eta_gen,"Pi1_eta_gen/D");
 genTree->Branch("Pi1_phi_gen",&Pi1_phi_gen,"Pi1_phi_gen/D");

 genTree->Branch("Pi2_pt_gen",&Pi2_pt_gen,"Pi2_pt_gen/D");
 genTree->Branch("Pi2_eta_gen",&Pi2_eta_gen,"Pi2_eta_gen/D");
 genTree->Branch("Pi2_phi_gen",&Pi2_phi_gen,"Pi2_phi_gen/D");

 genTree->Branch("K_pt_gen",&K_pt_gen,"K_pt_gen/D");
 genTree->Branch("K_eta_gen",&K_eta_gen,"K_eta_gen/D");
 genTree->Branch("K_phi_gen",&K_phi_gen,"K_phi_gen/D");

 genTree->Branch("D0_pt_gen",&D0_pt_gen,"D0_pt_gen/D");
 genTree->Branch("D0_eta_gen",&D0_eta_gen,"D0_eta_gen/D");
 genTree->Branch("D0_phi_gen",&D0_phi_gen,"D0_phi_gen/D");

 genTree->Branch("DS_pt_gen",&DS_pt_gen,"DS_pt_gen/D");
 genTree->Branch("DS_eta_gen",&DS_eta_gen,"DS_eta_gen/D");
 genTree->Branch("DS_phi_gen",&DS_phi_gen,"DS_phi_gen/D");

 Tree= fs->make<TTree>("Analysis","Analysis");

 Tree->Branch("Pis_pt",&Pis_pt,"Pis_pt/D");
 Tree->Branch("Pis_eta",&Pis_eta,"Pis_eta/D");
 Tree->Branch("Pis_phi",&Pis_phi,"Pis_phi/D");

 Tree->Branch("Pi1_pt",&Pi1_pt,"Pi1_pt/D");
 Tree->Branch("Pi1_eta",&Pi1_eta,"Pi1_eta/D");
 Tree->Branch("Pi1_phi",&Pi1_phi,"Pi1_phi/D");

 Tree->Branch("Pi2_pt",&Pi2_pt,"Pi2_pt/D");
 Tree->Branch("Pi2_eta",&Pi2_eta,"Pi2_eta/D");
 Tree->Branch("Pi2_phi",&Pi2_phi,"Pi2_phi/D");

 Tree->Branch("Pim_pt",&Pim_pt,"Pim_pt/D");
 Tree->Branch("Pim_eta",&Pim_eta,"Pim_eta/D");
 Tree->Branch("Pim_phi",&Pim_phi,"Pim_phi/D");

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
}

MC13_4btree::~MC13_4btree()
{
 

}


void
MC13_4btree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 using namespace edm;

 edm::Handle<edm::View<reco::GenParticle> > genParticles;
 iEvent.getByToken(genParticles_, genParticles);
   
 edm::Handle<reco::TrackCollection> tracks;
 iEvent.getByToken(tracks_, tracks); 

 reco::BeamSpot beamSpot;
 edm::Handle<reco::BeamSpot> beamSpotHandle;
 iEvent.getByToken(beamSpotHandle_, beamSpotHandle);

 edm::ESHandle<TransientTrackBuilder> theB;
 iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
 
 edm::ESHandle<TransientTrackBuilder> theB1;
 iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB1); 
  
 int Dstar = 0, D0 = 0, Pislow = 0, Piplus = 0, Piplus1 = 0, Piplus2 = 0, Piminus = 0, Kminus = 0;
 double pi_mass = 0.13957018;
 double K_mass = 0.493677; 
 double D0_mass = 1.864841; 
 int id = 0, n = 0, m= 0;
 
 TLorentzVector KvectorGen;
 TLorentzVector Pi1vectorGen;
 TLorentzVector Pi2vectorGen;
 TLorentzVector PimvectorGen;
 TLorentzVector PisvectorGen;
 TLorentzVector D0vectorGen;
 TLorentzVector DSvectorGen;
 
 TLorentzVector KbarvectorGen;
 TLorentzVector Pi1barvectorGen;
 TLorentzVector Pi2barvectorGen;
 TLorentzVector PipbarvectorGen;
 TLorentzVector PisbarvectorGen;
 TLorentzVector D0barvectorGen;
 TLorentzVector DSbarvectorGen;

 /*########### reconstruction of the chain at gen level ##########*/

 int t = 0;

 for(size_t i = 0; i < genParticles->size(); ++ i) {
  const GenParticle & p= (*genParticles)[i];
  id = p.pdgId();
  if (id == 413){  Dstar ++;
   m = p.numberOfDaughters();
   if(m == 2){
    Pislow = 0;
    D0 = 0;
    for(int i = 0; i < m; ++ i) {
     const Candidate * d1 = p.daughter(i);
     id = d1->pdgId();
     if(id == 211){
      Pislow++;
      Pis_pt_gen = d1->pt();
      Pis_eta_gen = d1->eta();
      Pis_phi_gen= d1->phi();
      PisvectorGen.SetPtEtaPhiM( Pis_pt_gen, Pis_eta_gen,  Pis_phi_gen, pi_mass);
      }
     else if( id == 421 ){
      D0++;
      t = d1->numberOfDaughters();
      if(t == 4){
       Piplus = 0, Piplus1 = 0, Piplus2 = 0, Piminus = 0, Kminus = 0;
       for(int j = 0; j < t; ++ j) {
        const Candidate * e1 = d1->daughter( j );
        int id2 = e1->pdgId();
        if(id2 == 211) {
         Piplus++;
         if (Piplus == 1){
          Piplus1++;
          Pi1_pt_gen = e1->pt();
          Pi1_eta_gen = e1->eta();
          Pi1_phi_gen = e1->phi();
          Pi1vectorGen.SetPtEtaPhiM( Pi1_pt_gen, Pi1_eta_gen,  Pi1_phi_gen, pi_mass);
         }
         if (Piplus == 2){
          Piplus2++;
          Pi2_pt_gen = e1->pt();
          Pi2_eta_gen = e1->eta();
          Pi2_phi_gen = e1->phi();
          Pi2vectorGen.SetPtEtaPhiM( Pi2_pt_gen, Pi2_eta_gen, Pi2_phi_gen, pi_mass);
         }
        }
        if(id2 == -211) {
         Piminus++;
         Pim_pt_gen = e1->pt();
         Pim_eta_gen = e1->eta();
         Pim_phi_gen = e1->phi();
         PimvectorGen.SetPtEtaPhiM( Pim_pt_gen, Pim_eta_gen,  Pim_phi_gen, pi_mass);        
         }
        if(id2 == -321) {
         Kminus++;
         K_pt_gen = e1->pt();
         K_eta_gen = e1->eta();
         K_phi_gen = e1->phi();
         KvectorGen.SetPtEtaPhiM( K_pt_gen, K_eta_gen,  K_phi_gen, K_mass);
        } 
       }//for D0 decay
      }//if D0 decade in 4
     }//if D0 
    }//for D*decay
   }//if D* decay in 2
  }//if D*+
 } //for genparticle

 if(Pislow == 1 && D0 == 1){
  if(Kminus == 1 && Piplus1 == 1 && Piplus2 == 1 && Piminus ==1 ){
   D0vectorGen = KvectorGen + Pi1vectorGen + Pi2vectorGen + PimvectorGen;
   D0_pt_gen = D0vectorGen.Pt();
   DSvectorGen = D0vectorGen + PisvectorGen;
   DS_pt_gen = DSvectorGen.Pt();
   genTree->Fill();

   edm::Handle<std::vector<reco::Vertex> > hVtx;
   iEvent.getByToken(hVtx_, hVtx);
   reco::Vertex primaryVertex;
   reco::Vertex primaryVertex_tmp;

    // try to reconstruct the the decay chain:D*+ -> D0 pi+_slow-> k-pi+pi+pi- pi+_slow 

  }//if d0
 }//if D*
}

// ------------ method called once each job just before starting event loop  ------------
void 
MC13_4btree::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MC13_4btree::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MC13_4btree::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MC13_4btree::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MC13_4btree::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MC13_4btree::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MC13_4btree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MC13_4btree);
