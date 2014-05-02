import ROOT as r

ofile = r.TFile("ofile.root","RECREATE")
file = r.TFile("histograms-ttbar_13TeV_PU40_25ns_test_skimmed_v2.root", "READ")
canvas1 = r.TCanvas("profile_Eta1GenL1Response_30_35", "profile_Eta1GenL1Response_30_35", 500,500)

hist = file.Get("demo/global_histograms/Eta1GenL1Response_30_35")

prof = hist.ProfileX()

ofile.cd()
prof.Write()
ofile.Close()
