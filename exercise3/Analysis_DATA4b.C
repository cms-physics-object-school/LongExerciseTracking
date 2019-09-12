
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

void Analysis_DATA4b(){

char *file_DATA=(char *)"/home/common/LongExercises/Dstar/ntuples/DS4b_DATA2016_ZeroBias_skim_total.root";
TFile *DATA  =new TFile (file_DATA);

TTree *a_ = (TTree*)DATA->Get("demo/Analysis");

// Booking Variables here
double pi_mass = 0.13957018;
double K_mass = 0.493677;
double D0_mass = 1.864841;


// get branches here


// set addredd here


// your histo declaration here


int tot = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i % 100000 == 0){
  cout << i << " events analyzed on " << tot << endl;
 }



//your selection cuts 

}//for entries

TFile *f = new TFile("DS_4b_data2016.root", "RECREATE");

//write your histos here

f->Write();
f->Close();

}
