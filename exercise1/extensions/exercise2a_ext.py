from DataFormats.FWLite import Handle, Events
import ROOT
from math import sqrt
events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
tracks = Handle("std::vector<reco::Track>")

px_histogram = ROOT.TH1F("px", "px", 100, -1000, 1000)
py_histogram = ROOT.TH1F("py", "py", 100, -1000, 1000)
pz_histogram = ROOT.TH1F("pz", "pz", 100, -1000, 1000)
mass_histogram = ROOT.TH1F("mass", "mass", 100, 0, 5)
mass_histogram2 = ROOT.TH1F("mass2", "mass2", 100, 6, 11)


i = 0
print 'Printing only first events tracks, skipping events with only 1 track'
print 'Track pt, p, px, py, pz'
for event in events:
    event.getByLabel("globalMuons", tracks)
    numTotal = tracks.product().size()
    numLoose = 0
    numTight = 0
    numHighPurity = 0
    total_px = 0
    total_py = 0
    total_pz = 0
    for track in tracks.product():
        if(i < 1): print track.pt(), track.p(), track.px(), track.py(), track.pz()
        total_px += track.px()
        total_py += track.py()
        total_pz += track.pz()
    px_histogram.Fill(total_px)
    py_histogram.Fill(total_py)
    pz_histogram.Fill(total_pz)

    if len(tracks.product()) < 2: continue
    one = tracks.product()[0]
    two = tracks.product()[1]
    energy = sqrt(0.106**2 + one.p()**2) + sqrt(0.106**2 + two.p()**2)
    px = one.px() + two.px()
    py = one.py() + two.py()
    pz = one.pz() + two.pz()
    mass = sqrt(energy**2 - px**2 - py**2 - pz**2)
    mass_histogram.Fill(mass)
    mass_histogram2.Fill(mass)

    i = i + 1
    #if i > 100: break

cx = ROOT.TCanvas ( "cx" , "cx" , 800, 800 )
cx.cd()
px_histogram.Draw()
cx.Print("px_histogram.png")
cy = ROOT.TCanvas ( "cy" , "cy" , 800, 800 )
cy.cd()
py_histogram.Draw()
cy.Print("py_histogram.png")
cz = ROOT.TCanvas ( "cz" , "cz" , 800, 800 )
cz.cd()
pz_histogram.Draw()
cz.Print("pz_histogram.png")
c = ROOT.TCanvas ( "c" , "c" , 800, 800 )
c.cd()
mass_histogram.Draw()
c.Print("mass.png")

cc = ROOT.TCanvas ( "cc" , "cc" , 800, 800 )
cc.cd()
mass_histogram2.Draw()
cc.Print("mass2.png")
