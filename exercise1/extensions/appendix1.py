from ROOT import *
from math import sqrt
from DataFormats.FWLite import Handle, Events
events = Events("output.root")
secondaryVertices = Handle("std::vector<reco::VertexCompositeCandidate>")
mass_loose = TH1F("mass_loose", "mass_loose", 100, 0.4, 0.6)
mass_tight = TH1F("mass_tight", "mass_tight", 100, 0.4, 0.6)
mass_highpurity = TH1F("mass_highpurity", "mass_highpurity", 100, 0.4, 0.6)

i = 0
events.toBegin()
for event in events:
    print "Event:", i
    event.getByLabel("SecondaryVerticesFromLooseTracks", "Kshort", secondaryVertices)
    for vertex in secondaryVertices.product():
        mass_loose.Fill(vertex.mass())
    event.getByLabel("SecondaryVerticesFromTightTracks", "Kshort", secondaryVertices)
    for vertex in secondaryVertices.product():
        mass_tight.Fill(vertex.mass())
    event.getByLabel("SecondaryVerticesFromHighPurityTracks", "Kshort", secondaryVertices)
    for vertex in secondaryVertices.product():
        mass_highpurity.Fill(vertex.mass())


mass_loose.SetLineColor(kBlack)
mass_tight.SetLineColor(kBlue)
mass_highpurity.SetLineColor(kRed)

c = TCanvas("c","c",800,600)
c.cd()
mass_loose.Draw()
mass_tight.Draw("same")
mass_highpurity.Draw("same")
c.Print("mass_3levels.png")

mass_loose.SetMinimum(0)

peak = ROOT.TF1("peak", "[0]*exp(-(x - [1])**2/2./[2]**2)/sqrt(6.28)/[2] + [3]", 0.44, 0.56)
peak.SetParameter(0, 3.)
peak.SetParameter(1, 0.5)
peak.SetParameter(2, 0.004)
peak.SetParameter(3, 30.)

mass_loose.Fit(peak)
parameters_loose = {"signal": mass_loose.GetFunction("peak").GetParameter(0) * 60 / (0.56 - 0.44),
                    "background": mass_loose.GetFunction("peak").GetParameter(3) * 60,
                    }

mass_tight.Fit(peak)
parameters_tight = {"signal": mass_tight.GetFunction("peak").GetParameter(0) * 60 / (0.56 - 0.44),
                    "background": mass_tight.GetFunction("peak").GetParameter(3) * 60,
                    }

mass_highpurity.Fit(peak)
parameters_highPurity = {"signal": mass_highpurity.GetFunction("peak").GetParameter(0) * 60 / (0.56 - 0.44),
                    "background": mass_highpurity.GetFunction("peak").GetParameter(3) * 60,
                    }

compare_signal = ROOT.TH1F("compare_signal", "", 3, 0.5, 3.5)
compare_signal.SetBinContent(1, parameters_loose["signal"])
compare_signal.SetBinContent(2, parameters_tight["signal"])
compare_signal.SetBinContent(3, parameters_highPurity["signal"])
compare_signal.SetStats(False)
compare_signal.GetXaxis().SetBinLabel(1, "loose")
compare_signal.GetXaxis().SetBinLabel(2, "tight")
compare_signal.GetXaxis().SetBinLabel(3, "highPurity")

compare_background = ROOT.TH1F("compare_background", "", 3, 0.5, 3.5)
compare_background.SetBinContent(1, parameters_loose["background"])
compare_background.SetBinContent(2, parameters_tight["background"])
compare_background.SetBinContent(3, parameters_highPurity["background"])
compare_background.SetLineStyle(2)
compare_background.SetLineColor(ROOT.kRed)

tlegend = ROOT.TLegend(0.55, 0.85, 0.95, 0.95)
tlegend.SetFillColor(ROOT.kWhite)
tlegend.AddEntry(compare_signal, "Signal yield", "l")
tlegend.AddEntry(compare_background, "Background yield", "l")

compare_signal.SetAxisRange(0, 11000, "Y")

compare_signal.Draw()
compare_background.Draw("same")
tlegend.Draw()

c.Print("mass_fitted.png")
