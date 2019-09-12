from math import sqrt
from DataFormats.FWLite import Handle, Events
import ROOT

events = Events("output.root")
primaryVertices = Handle("std::vector<reco::Vertex>")
secondaryVertices = Handle("std::vector<reco::VertexCompositeCandidate>")

cosAngle_histogram = ROOT.TH1F("cosAngle","cosAngle",100,-1,1)
cosAngle_zoom_histogram = ROOT.TH1F("cosAngle_zoom","cosAngle_zoom",100,0.99,1)
mass_histogram = ROOT.TH1F("mass","mass",100,0.4,0.6)
mass_goodCosAngle = ROOT.TH1F("mass_goodCosAngle","mass_goodCosAngle",100,0.4,0.6)

i = 0
events.toBegin()
for event in events:
    event.getByLabel("offlinePrimaryVertices",primaryVertices)
    event.getByLabel("SecondaryVerticesFromLooseTracks","Kshort",secondaryVertices)
    for secondary in secondaryVertices.product():
        px = secondary.px()
        py = secondary.py()
        pz = secondary.pz()
        p = secondary.p()
        bestCosAngle = -1
        for primary in primaryVertices.product():
            dx = secondary.vx() - primary.x()
            dy = secondary.vy() - primary.y()
            dz = secondary.vz() - primary.z()
            dl = sqrt(dx**2 + dy**2 + dz**2)
            if (i < 20): print "Normalized momentum:",px/p,py/p,pz/p,"Normalized displacement:",dx/dl,dy/dl,dz/dl

            dotProduct = px*dx + py*dy + pz*dz
            cosAngle = dotProduct/p/dl
            if cosAngle > bestCosAngle:
                bestCosAngle = cosAngle
        cosAngle_histogram.Fill(bestCosAngle)
        cosAngle_zoom_histogram.Fill(bestCosAngle)
        mass_histogram.Fill(secondary.mass())
        if bestCosAngle > 0.99: mass_goodCosAngle.Fill(secondary.mass())

    i += 1

c1 = ROOT.TCanvas("c1","c1",800,800)
c1.cd()
cosAngle_histogram.Draw()
c1.Print("cosAngle.png")

c2 = ROOT.TCanvas("c2","c2",800,800)
c2.cd()
cosAngle_zoom_histogram.Draw()
c2.Print("cosAngle_zoom.png")

c3 = ROOT.TCanvas("c3","c3",800,800)
c3.cd()
mass_goodCosAngle.Draw()
c3.Print("mass_improved.png")
