
#include "TBox.h"
#include "TArrow.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TLine.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;

void Analysis_MC2b(){

char *file_DATA=(char *)"/home/common/LongExercises/Dstar/ntuples/DS2b_MC.root";
TFile *DATA  =new TFile (file_DATA);

TTree *a_ = (TTree*)DATA->Get("demo/Analysis");
TTree *b_ = (TTree*)DATA->Get("demo/Gen");


// Booking Variables
double Pi_pt_gen, Pi_eta_gen, Pi_phi_gen;
double K_pt_gen, K_eta_gen, K_phi_gen;
double D0_pt_gen, D0_eta_gen, D0_phi_gen;
double Pis_pt_gen, Pis_eta_gen, Pis_phi_gen;
double DS_pt_gen, DS_eta_gen, DS_phi_gen;

double Pis_pt, Pis_eta, Pis_phi;
double Pi_pt, Pi_eta, Pi_phi;
double K_pt, K_eta, K_phi;
double DS_pt, DS_eta, DS_phi;
double D0_pt, D0_eta, D0_phi;
double CL_vertex, cos_phi;
int vertex_size;
double x_p, y_p, z_p;
double x_s, y_s, z_s;
double L_abs, L_sigma;
double pi_mass = 0.13957018;
double K_mass = 0.493677;
double D0_mass = 1.864841;
int num_tracks, ntracks, truePU;
bool passTrigger;

TBranch *b_Pi_pt_gen=b_->GetBranch("Pi_pt_gen");
TBranch *b_Pi_eta_gen=b_->GetBranch("Pi_eta_gen");
TBranch *b_Pi_phi_gen=b_->GetBranch("Pi_phi_gen");

TBranch *b_K_pt_gen=b_->GetBranch("K_pt_gen");
TBranch *b_K_eta_gen=b_->GetBranch("K_eta_gen");
TBranch *b_K_phi_gen=b_->GetBranch("K_phi_gen");

TBranch *b_Pis_pt_gen=b_->GetBranch("Pis_pt_gen");
TBranch *b_Pis_eta_gen=b_->GetBranch("Pis_eta_gen");
TBranch *b_Pis_phi_gen=b_->GetBranch("Pis_phi_gen");

TBranch *a_Pis_pt = a_->GetBranch("Pis_pt");
TBranch *a_Pis_eta=a_->GetBranch("Pis_eta");
TBranch *a_Pis_phi=a_->GetBranch("Pis_phi");

TBranch *a_Pi_pt=a_->GetBranch("Pi_pt");
TBranch *a_Pi_eta=a_->GetBranch("Pi_eta");
TBranch *a_Pi_phi=a_->GetBranch("Pi_phi");

TBranch *a_K_pt=a_->GetBranch("K_pt");
TBranch *a_K_eta=a_->GetBranch("K_eta");
TBranch *a_K_phi=a_->GetBranch("K_phi");

TBranch *a_DS_pt=a_->GetBranch("DS_pt");
TBranch *a_DS_eta=a_->GetBranch("DS_eta");
TBranch *a_DS_phi=a_->GetBranch("DS_phi");

TBranch *a_D0_pt=a_->GetBranch("D0_pt");
TBranch *a_D0_eta=a_->GetBranch("D0_eta");
TBranch *a_D0_phi=a_->GetBranch("D0_phi");

TBranch *a_L_sigma=a_->GetBranch("L_sigma");
TBranch *a_cosphi=a_->GetBranch("cos_phi");
TBranch *a_vertex_size=a_->GetBranch("vertex_size");
TBranch *a_num_tracks=a_->GetBranch("num_tracks");
TBranch *a_truePU= a_->GetBranch("truePU");
TBranch *a_trigger=a_->GetBranch("passTrigger");

b_Pi_pt_gen->SetAddress(&Pi_pt_gen);
b_Pi_eta_gen->SetAddress(&Pi_eta_gen);
b_Pi_phi_gen->SetAddress(&Pi_phi_gen);

b_K_pt_gen->SetAddress(&K_pt_gen);
b_K_eta_gen->SetAddress(&K_eta_gen);
b_K_phi_gen->SetAddress(&K_phi_gen);

b_Pis_pt_gen->SetAddress(&Pis_pt_gen);
b_Pis_eta_gen->SetAddress(&Pis_eta_gen);
b_Pis_phi_gen->SetAddress(&Pis_phi_gen);

a_Pis_pt->SetAddress(&Pis_pt);
a_Pis_eta->SetAddress(&Pis_eta);
a_Pis_phi->SetAddress(&Pis_phi);

a_Pi_pt->SetAddress(&Pi_pt);
a_Pi_eta->SetAddress(&Pi_eta);
a_Pi_phi->SetAddress(&Pi_phi);

a_K_pt->SetAddress(&K_pt);
a_K_eta->SetAddress(&K_eta);
a_K_phi->SetAddress(&K_phi);

a_DS_pt->SetAddress(&DS_pt);
a_DS_eta->SetAddress(&DS_eta);
a_DS_phi->SetAddress(&DS_phi);

a_D0_pt->SetAddress(&D0_pt);
a_D0_eta->SetAddress(&D0_eta);
a_D0_phi->SetAddress(&D0_phi);

a_L_sigma->SetAddress(&L_sigma);
a_cosphi->SetAddress(&cos_phi);
a_vertex_size->SetAddress(&vertex_size);
a_num_tracks->SetAddress(&num_tracks);

TLorentzVector Kvector;
TLorentzVector Pivector;
TLorentzVector D0vector;
TLorentzVector Pisvector;
TLorentzVector DSvector;
TLorentzVector Kvector_gen;
TLorentzVector Pivector_gen;
TLorentzVector Pisvector_gen;
TLorentzVector D0vector_gen;
TLorentzVector DSvector_gen;
double deltaM = 0;
float y=0;
TH1D * deltaMass = new TH1D ("deltaM", "deltaM", 400, 0.13, 0.17);
TH1D * tot_gen= new TH1D ("tot_gen", "tot_gen", 4, 0, 2);

int tot_gen_number = 0;
for (Int_t j=0;j<b_->GetEntries();j++) {
 b_->GetEntry(j);
 tot_gen_number = b_->GetEntries();
 if (j % 100000 == 0){
  cout << j << "gen events analyzed on " << tot_gen_number << endl;
 }
 Kvector_gen.SetPtEtaPhiM(K_pt_gen, K_eta_gen, K_phi_gen, K_mass);
 Pivector_gen.SetPtEtaPhiM(Pi_pt_gen, Pi_eta_gen, Pi_phi_gen, pi_mass);
 Pisvector_gen.SetPtEtaPhiM(Pis_pt_gen, Pis_eta_gen, Pis_phi_gen, pi_mass);
 D0vector_gen = Kvector_gen + Pivector_gen;
 DSvector_gen = Kvector_gen + Pivector_gen + Pisvector_gen;
 DS_pt_gen = DSvector_gen.Pt();
 tot_gen->Fill(1);
} 

int PU = 0, tot = 0;
for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i % 100000 == 0){
  cout << i << " reco events analyzed on " << tot << endl;
 }
 Kvector.SetPtEtaPhiM(K_pt, K_eta, K_phi, K_mass);
 Pivector.SetPtEtaPhiM(Pi_pt, Pi_eta, Pi_phi, pi_mass);
 D0vector = Kvector + Pivector;
 Pisvector.SetPtEtaPhiM(Pis_pt, Pis_eta, Pis_phi, pi_mass);
 DSvector = Kvector + Pivector + Pisvector;
 deltaM = fabs(DSvector.M() - D0vector.M());
 ntracks = num_tracks;
 PU = vertex_size;
 if(fabs(D0vector.M() - D0_mass) < 0.023){  
  if(cos_phi > 0.99){
   if(L_sigma > 3){
    if(D0_pt > 3){
     if(deltaM < 0.160){
      if(DS_pt > 5.5){
       deltaMass->Fill(deltaM);
      } 
     }//deltaM
    }//D0 pt
   }//Lsusigma
  }//cosphi
 }//if D0 mass
}//for entries

TFile *f = new TFile("DS_2b_MC.root", "RECREATE");
deltaMass->Write();
tot_gen->Write();

f->Write();
f->Close();

}
