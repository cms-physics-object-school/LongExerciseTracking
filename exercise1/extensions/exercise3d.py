from math import sqrt
from DataFormats.FWLite import Handle, Events
import ROOT

events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
primaryVertices = Handle("std::vector<reco::Vertex>")
tracks = Handle("std::vector<reco::Track>")
beamspot = Handle("reco::Beamspot")

ntrksvsnvtx_histogram = ROOT.TH2F("ntrksvsnvtx", "Ntracks vs NVtx", 30,0,29,100,0,2000)

sumz = 0
N = 0

events.toBegin()
for event in events:
    event.getByLabel("offlinePrimaryVertices", primaryVertices)
    event.getByLabel("generalTracks",tracks)
    event.getByLabel("offlineBeamSpot",beamspot)
    print "Pile-up:", primaryVertices.product().size()

    for vertex in primaryVertices.product():
        N += 1
        sumz += vertex.z()
        if(i < 10): print "N tracks:",vertex.nTracks(),", tracks size:",vertex.trackSize()
    
    ntrksvsnvtx_histogram.Fill(primaryVertices.product().size(),tracks.product().size())
    mean = sumz/N
    if N % 100 == 0:
        print "Mean of primary vertices:",mean,"Beamspot:",beamspot.product().z0()

    i += 1

c = ROOT.TCanvas ( "c" , "c" , 800, 800 )
c.cd()
ntrksvsnvtx_histogram.Draw("colz")
c.Print("ntrks_vs_nvtx.png")

