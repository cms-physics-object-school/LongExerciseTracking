{

  gROOT->Reset();
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1,0);
  gStyle->SetTitleX(0.5); //title X location 
  gStyle->SetTitleY(0.96); //title Y location 
  gStyle->SetPaintTextFormat(".2f");

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(true);
  tdrStyle->SetGridColor(1);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistFillColor(63);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  tdrStyle->SetErrorX(0.);

gSystem->Load("libRooFit") ;
using namespace RooFit ;

// --- Observable ---
RooRealVar deltaM("deltaM","diff (GeV)", 0.14,0.16) ;
  
// --- Parameters ---
RooRealVar sigma("sigma","width of gaussian",0.0006, 0.0003, 0.001) ;
RooRealVar mean("mean","mean of gaussian",0.1454, 0.14, 0.16) ;

RooRealVar sigma2("sigma2","width of gaussian",0.0006, 0.0004, 0.0015) ;
   
// --- Build Gaussian PDF ---
RooGaussian sign("sign","signal PDF",deltaM,mean,sigma) ;
RooGaussian sign2("sign2","signal PDF",deltaM,mean,sigma2) ;
RooRealVar fr("fr","width of gaussian",0.5, 0., 1) ;
RooAddPdf sig("sig", "g1+g2", RooArgSet(sign, sign2),fr);

RooRealVar m0("m0", "m0", 0.1396);
RooRealVar p0("p0","p0",0.003,0.0002,0.0042);
RooRealVar p1("p1","p1",4, 0., 7.);
RooRealVar p2("p2","p2",6,0.,8.);
RooGenericPdf bkg("bkg","(1-exp(-(deltaM-m0)/p0))*(deltaM/m0)^p1 + p2*(deltaM/m0 - 1)",RooArgSet(m0,deltaM,p0,p1,p2));

RooRealVar nsig("nsig","#signal events",8000,0,150000) ;
RooRealVar nbkg("nbkg","#background events",15000,0,2000000) ;
RooAddPdf model("model","g+a",RooArgList(sig,bkg),RooArgList(nsig,nbkg)) ;

TFile *f00 = new TFile(""); //type here the name of your root file
TString name = ""; // type here the name of the plot you want to fit
TH1F *da= (TH1F*) f00->Get(name);

TH1F *da1=(TH1F*)da->Clone();

da1->Sumw2();

da1->Rebin(4);

RooDataHist *data = new RooDataHist("data","diff mass",deltaM,da1);
RooFitResult* r = model.fitTo(*data,Save()) ;
r->Print("") ;

TCanvas *c = new TCanvas;
TImage *img = TImage::Create();

RooPlot* mesframe = deltaM.frame() ;
data->plotOn(mesframe) ;
model.plotOn(mesframe) ;
model.plotOn(mesframe,Components(bkg),LineStyle(kDashed)) ;
mesframe->GetXaxis()->SetTitle("M(k#pi#pi_{s}) - M(k#pi) [GeV/c^{2}]");
mesframe->SetTitle("");
mesframe->Draw()  ;

TLatex latexLabel2;
latexLabel2.SetTextSize(0.04);
latexLabel2.SetTextFont(32);
latexLabel2.SetNDC();
latexLabel2.DrawLatex(0.3, 0.93, " CMS Preliminary at #sqrt{s} = 13 TeV, 2016");

img->FromPad(c);
img->WriteImage(name+"_2b.png");

}


