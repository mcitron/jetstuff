void check_rate_vs_nvtx() {

  TFile * file = new TFile("../histograms-neutrinogun_13TeV_PU40_50ns_1-10_skimmed_v3_allevents.root","READ");

  TH1D * hist1 = (TH1D*)((TH1D*)file->Get("demo/L14300_ak4genjetsp/col1_jet1_pt")->Clone());
  TH1D * hist2 = (TH1D*)((TH1D*)file->Get("demo/L14300donut_ak4genjetsp/col1_jet1_pt")->Clone());
  TH1D * hist3 = (TH1D*)((TH1D*)file->Get("demo/L14300_ak4genjetsp_npv3035/col1_jet1_pt")->Clone());
  TH1D * hist4 = (TH1D*)((TH1D*)file->Get("demo/L14300donut_ak4genjetsp_npv3035/col1_jet1_pt")->Clone());
  TH1D * hist5 = (TH1D*)((TH1D*)file->Get("demo/L14300_ak4genjetsp_npv3540/col1_jet1_pt")->Clone());
  TH1D * hist6 = (TH1D*)((TH1D*)file->Get("demo/L14300donut_ak4genjetsp_npv3540/col1_jet1_pt")->Clone());
  TH1D * hist7 = (TH1D*)((TH1D*)file->Get("demo/L14300_ak4genjetsp_npv4045/col1_jet1_pt")->Clone());
  TH1D * hist8 = (TH1D*)((TH1D*)file->Get("demo/L14300donut_ak4genjetsp_npv4045/col1_jet1_pt")->Clone());
  TH1D * hist9 = (TH1D*)((TH1D*)file->Get("demo/L14300_ak4genjetsp_npv4550/col1_jet1_pt")->Clone());
  TH1D * hist10 = (TH1D*)((TH1D*)file->Get("demo/L14300donut_ak4genjetsp_npv4550/col1_jet1_pt")->Clone());

  int thresh=25;

  //std::cout << "overall: " << hist1->Integral(thresh,500) / hist1->Integral() << " vs " << hist2->Integral(thresh,500) / hist2->Integral() << std::endl;
  std::cout << "npv 30-35 " << hist3->Integral(thresh,500) / hist3->Integral() << " vs " << hist4->Integral(thresh,500) / hist4->Integral() << std::endl;
  std::cout << "npv 35-40: " << hist5->Integral(thresh,500) / hist5->Integral() << " vs " << hist6->Integral(thresh,500) / hist6->Integral() << std::endl;
  std::cout << "npv 40-45: " << hist7->Integral(thresh,500) / hist7->Integral() << " vs " << hist8->Integral(thresh,500) / hist8->Integral() << std::endl;
  std::cout << "npv 45-50: " << hist9->Integral(thresh,500) / hist9->Integral() << " vs " << hist10->Integral(thresh,500) / hist10->Integral() << std::endl;

  return;

}
