from DataFormats.FWLite import Handle, Events
import inspect
events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
tracks = Handle("std::vector<reco::Track>")
i = 0
print "Printing 5 events"
for event in events:
    print "Event", i
    print "Track q*pT, Dxy, Dz, chi2, ndof, N valid hits, Algo"
    event.getByLabel("generalTracks", tracks)
    j = 0
    for track in tracks.product():
        #if j > 24: continue
        print "    Track", j, track.charge()/track.pt(), track.dxy(), track.dz(), track.chi2(), track.ndof(), track.numberOfValidHits(), track.algoName()
        j += 1
    i += 1
    if i >= 5: break
