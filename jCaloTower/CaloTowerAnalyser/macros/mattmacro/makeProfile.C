void makeProfile()
{
  TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140605/neutrino_output.root");
  //TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/TTBAR/140605/ttbar_output.root");
  std::vector<TString> PUSregime;
  PUSregime.push_back("seed");
  PUSregime.push_back("ring01");
  PUSregime.push_back("ring01norm");
  std::vector<TString> ETAregime;
  ETAregime.push_back("iEta_-28_to_-22");
  ETAregime.push_back("iEta_-21_to_-15");
  ETAregime.push_back("iEta_-14_to_-08");
  ETAregime.push_back("iEta_-07_to_-1");
  ETAregime.push_back("iEta_01_to_07");
  ETAregime.push_back("iEta_08_to_14");
  ETAregime.push_back("iEta_15_to_21");
  ETAregime.push_back("iEta_21_to_28");

  TFile *top = new TFile("ProfilePlotsn.root","recreate");
  for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
  {      
    TDirectory * dir = top->mkdir((*iPUS).Data());
    dir->cd();
    for (auto iEta = ETAregime.begin(); iEta!=ETAregime.end(); iEta++)
    {
      TH2D * origplot = f->Get(("demo/5400_nopus_gen/etaseedtests/col1_"+*iPUS+"_pt_corr_"+*iEta).Data());
      origplot->Sumw2();

      TProfile * profileplot = origplot->ProfileX("col1_"+*iPUS+"_pt_corr_"+*iEta, 0, -1); // where firstYbin = 0 and lastYbin = 9
      profileplot->Write();
    }
  }
  top->Close();

}

/*{
TFile * f = TFile::Open("./global_PUS.root");
TH2D * allhistDonut =  (f->Get("demo/donut_gen/pt_ratio_nvts_algo1"));
TH2D * allhistGlobal =  (f->Get("demo/global_gen/pt_ratio_nvts_algo1"));
TH2D * allhistNopus =  (f->Get("demo/nopus_gen/pt_ratio_nvts_algo1"));
allhistDonut->Sumw2();
TProfile *px = allhistGlobal->ProfileX("px", 0, -1); // where firstYbin = 0 and lastYbin = 9
TProfile *py = allhistDonut->ProfileX("py", 0, -1); // where firstYbin = 0 and lastYbin = 9
TProfile *pz = allhistNopus->ProfileX("pz", 0, -1); // where firstYbin = 0 and lastYbin = 9
//px->Draw();
//px->SetLineColor(1);
py->Draw("same");
py->SetLineColor(2);
pz->Draw("same");
pz->SetLineColor(3);
}
*/
