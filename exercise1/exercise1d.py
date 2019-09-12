from DataFormats.FWLite import Handle, Events
events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
tracks = Handle("std::vector<reco::Track>")

i = 0
for event in events:
    event.getByLabel("generalTracks", tracks)
    numTotal = tracks.product().size()
    numLoose = 0
    numTight = 0
    numHighPurity = 0
    for track in tracks.product():
	#print dir(track)
        if track.quality(track.qualityByName("loose")): numLoose += 1
        if track.quality(track.qualityByName("tight")): numTight += 1
        if track.quality(track.qualityByName("highPurity")): numHighPurity += 1
    print "numTotal", numTotal, "numLoose", numLoose, "numTight", numTight, "numHighPurity", numHighPurity 
    i += 1
    if i > 100: break
