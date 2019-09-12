from DataFormats.FWLite import Handle, Events
events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
tracks = Handle("std::vector<reco::Track>")

i = 0
for event in events:
    print "Event", i
    event.getByLabel("generalTracks", tracks)
    j = 0
    for track in tracks.product():
        print "    Track", j, track.charge()/track.pt(), track.phi(), track.eta(), track.dxy(), track.dz()
        j += 1
    i += 1
    if i >= 5: break
