from math import sqrt
from DataFormats.FWLite import Handle, Events
import ROOT

events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
primaryVertices = Handle("std::vector<reco::Vertex>")


rho_z_histogram = ROOT.TH2F("rho_z", "rho_z", 100, 0, 30, 100, 0, 10)
deltaz_histogram = ROOT.TH1F("deltaz", "deltaz", 1000, -20, 20)

events.toBegin()
for event in events:
    event.getByLabel("offlinePrimaryVertices", primaryVertices)
    pv = primaryVertices.product()
    for i in xrange(0, pv.size()):
        rho_z_histogram.Fill(abs(pv[i].z()), sqrt(pv[i].x()**2 + pv[i].y()**2))
        for j in xrange(i + 1, pv.size()):
            deltaz_histogram.Fill(pv[i].z() - pv[j].z())

c = ROOT.TCanvas ( "c" , "c" , 800, 800 )
c.cd()
rho_z_histogram.Draw("colz")
c.Print("rho_z.png")
c.cd()

c2 = ROOT.TCanvas("c2","c2",800,800)
c2.cd()
deltaz_histogram.Draw()
c2.Print("deltaz.png")
