from DataFormats.FWLite import Handle, Events
import ROOT
events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")
tracks = Handle("std::vector<reco::Track>")

histogram = ROOT.TH1F("histogram", "histogram", 100, 0, 10)
#histogram2 = ROOT.TH1F("histogram2","histogram2",100,0,10)
#histogram3 = ROOT.TH1F("histogram3","histogram3",50,0,50)

i = 0
for event in events:
    event.getByLabel("generalTracks", tracks)
    for track in tracks.product():
	histogram.Fill(track.normalizedChi2())
        #if(tracks.numberOfValidHits()>3): histogram2.Fill(track.normalizedChi2())
        #histogram3.Fill(track.numberOfValidHits())
    i += 1
    #if i > 1000: break

c = ROOT.TCanvas ( "c" , "c" , 800, 800 )
c.cd()
histogram.Draw()

