from ROOT import *
from math import sqrt
from DataFormats.FWLite import Handle, Events
events = Events("output.root")
secondaryVertices = Handle("std::vector<reco::VertexCompositeCandidate>")
mass_histogram = TH1F("mass", "mass", 100, 0.4, 0.6)
dxy_histogram = TH1F("dxy","dxy",100,0,50)
rho_z_histogram = TH2F("rho_z", "rho_z", 100, 0, 30, 100, 0, 10)
deltaz_histogram = TH1F("deltaz", "deltaz", 1000, -20, 20)

i = 0
events.toBegin()
for event in events:
    print "Event:", i
    event.getByLabel("SecondaryVerticesFromLooseTracks", "Kshort", secondaryVertices)
    j = 0
    sv = secondaryVertices.product()
    for vertex in sv:
        print "    Vertex:", j, vertex.vx(), vertex.vy(), vertex.vz()
        mass_histogram.Fill(vertex.mass())
        dxy_histogram.Fill(sqrt(vertex.vx()**2 + vertex.vy()**2))
        rho_z_histogram.Fill(abs(vertex.vz()), sqrt(vertex.vx()**2 + vertex.vy()**2))
        for k in range(j+1, len(sv)):
            deltaz_histogram.Fill(sv[k].vz() - sv[j].vz())
        j += 1


    i += 1
c = TCanvas ( "c" , "c" , 800, 800 )
mass_histogram.Draw()
c.SaveAs("sec_vert_mass.png")

c2 = TCanvas("c2","c2",800,800)
dxy_histogram.Draw()
c2.SaveAs("sec_vert_dxy.png")

c3 = TCanvas("c3","c3",800,800)
rho_z_histogram.Draw("colz")
c3.SaveAs("sec_vert_rhoz.png")

c4 = TCanvas("c4","c4",800,800)
deltaz_histogram.Draw()
c4.SaveAs("sec_vert_dz.png")
