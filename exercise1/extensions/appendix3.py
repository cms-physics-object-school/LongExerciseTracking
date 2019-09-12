from DataFormats.FWLite import Handle, Events
import ROOT

events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
tracks = Handle("std::vector<reco::Track>")
beamspot = Handle("reco::BeamSpot")

dxy_vs_phi_000 = ROOT.TProfile("dxy_vs_phi_000", "dxy_vs_phi_000", 100, -3.14, 3.14) 
dxy_vs_phi_beamspot = ROOT.TProfile("dxy_vs_phi_beamspot", "dxy_vs_phi_beamspot", 100, -3.14, 3.14) 

i = 0
events.toBegin()
for event in events:
    event.getByLabel("generalTracks", tracks)
    event.getByLabel("offlineBeamSpot", beamspot)
    j = 0
    for track in tracks.product():
        if i == 0 and j == 0:
            print "Dxy at 0,0,0:",track.dxy(ROOT.math.XYZPoint(0, 0, 0))
            print "Dxy at beamspot:",track.dxy(beamspot.product())
        dxy_vs_phi_000.Fill(track.phi(), track.dxy(ROOT.math.XYZPoint(0, 0, 0)))
        dxy_vs_phi_beamspot.Fill(track.phi(), track.dxy(beamspot.product()))

dxy_vs_phi_000.SetAxisRange(-0.2, 0.2, "Y")
dxy_vs_phi_beamspot.SetAxisRange(-0.2, 0.2, "Y")

dxy_vs_phi_000.Draw()
dxy_vs_phi_beamspot.Draw()
