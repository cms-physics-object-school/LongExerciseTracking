import os 
from array import array

file_list = os.listdir("results")

Effi = array('d') 
Err_Eff = array('d')

for f in file_list:
    file = open("results/"+f)
    righe = file.readlines()

    def approximate(text):
        return round(float(text))
    
    print "Processing ", f.split(".")[0]

    for riga in righe:
        
        split = riga.split(" ")
        if split[0] == "N2b_data":
            n2bdata = approximate(split[1])
            err_n2bdata = approximate(split[2])
        elif split[0] == "N4b_data":
            n4bdata = approximate(split[1])
            err_n4bdata = approximate(split[2])
        elif split[0] == "N2b_MC":
            n2bmc = approximate(split[1])
            err_n2bmc = approximate(split[2])
        elif split[0] == "N4b_MC":
            n4bmc = approximate(split[1])
            err_n4bmc = approximate(split[2])
    print "N 2b data: ", n2bdata, " +/- ", err_n2bdata
    print "N 4b data: ", n4bdata, " +/- ", err_n4bdata
    print "N 2b MC: ", n2bmc, " +/- ", err_n2bmc
    print "N 4b MC: ", n4bmc, " +/- ", err_n4bmc
    TOT1 = 58317010
    TOT2 = 9301883
    R_PDG = 2.08
    err_R_PDG = 0.05
    effi1 = n2bmc/TOT1
    effi2 = n4bmc/TOT2
    err_effi1 = (1/TOT1) * ((err_n2bmc)**(2) + ((n2bmc)**(2))/TOT1 )**(0.5) 
    err_effi2 = (1/TOT2) * ((err_n4bmc)**(2) + ((n4bmc)**(2))/TOT2 )**(0.5) 

    err_ratio_effi_squared = (1/effi2**2)*(err_effi1**2 + ((effi1**2)/(effi2**2))*(err_effi2**2)) 
    err_ratio_N_squared = (1/n2bdata**2)*(err_n4bdata**2 + ((n4bdata**2)/(n2bdata**2))*(err_n2bdata**2))  

    R = (n4bdata/n2bdata)*(effi1/effi2)
    err_R = (((n4bdata**2)/(n2bdata**2))*err_ratio_effi_squared + (((effi1**2)/(effi2**2))*err_ratio_N_squared ))**(0.5)

    rel_effi = (R/R_PDG)**(0.5)
    err_rel_effi = ((1./4)*(1./(R_PDG*R))*(err_R**2) + (1./4)*(R/R_PDG**3)*(0.05**2)  )**(0.5)

    Effi.append(rel_effi)
    Err_Eff.append(err_rel_effi)

    print "R = ", R, " +/- ", err_R
    print "rel effi = ", rel_effi, " +/- ", err_rel_effi 
    print "-----------------------------------------------"
    file.close()

print Effi
print Err_Eff

import ROOT

c1 = ROOT.TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
gr = ROOT.TGraphErrors(len(Effi), array('d', [5,6]), Effi, array('d', [0.,0.]), Err_Eff )
line = ROOT.TLine(4,1,7,1)
line.SetLineColor(ROOT.kRed)

gr.Draw("AP")
line.Draw("same")
c1.Update()

c1.SaveAs("test.png")
raw_input("Press enter to continue...")
