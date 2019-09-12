import ROOT
from DataFormats.FWLite import Handle, Events
events = Events("root://cmseos.fnal.gov//store/user/cmsdas/2018/short_exercises/TrackingVertexing/tracks_and_vertices_DoubleMuon2017C_299370.root")

clusterSummary = Handle("ClusterSummary")

h = ROOT.TH2F("h", "h", 100, 0, 20000, 100, 0, 100000)

events.toBegin()
for event in events:
    event.getByLabel("clusterSummaryProducer", clusterSummary)
    cs = clusterSummary.product()
    try:
        h.Fill(cs.GetGenericVariable(cs.NMODULESPIXELS, cs.BPIX) + cs.GetGenericVariable(cs.NMODULESPIXELS, cs.FPIX), cs.GetGenericVariable(cs.NMODULES, cs.TRACKER))
    except TypeError:
        pass

h.Draw()
h.Fit("pol1")
