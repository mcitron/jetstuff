void makeplot() {


  TFile * file = new TFile("histograms-2.root", "READ");

  TH1D * histE1 = (TH1D*)file->Get("demo/resE_00_05");
  TH1D * histE2 = (TH1D*)file->Get("demo/resE_05_10");
  TH1D * histE3 = (TH1D*)file->Get("demo/resE_10_15");
  TH1D * histE4 = (TH1D*)file->Get("demo/resE_15_20");
  TH1D * histE5 = (TH1D*)file->Get("demo/resE_20_25");
  TH1D * histE6 = (TH1D*)file->Get("demo/resE_25_30");

  TH1D * histH1 = (TH1D*)file->Get("demo/resH_00_05");
  TH1D * histH2 = (TH1D*)file->Get("demo/resH_05_10");
  TH1D * histH3 = (TH1D*)file->Get("demo/resH_10_15");
  TH1D * histH4 = (TH1D*)file->Get("demo/resH_15_20");
  TH1D * histH5 = (TH1D*)file->Get("demo/resH_20_25");
  TH1D * histH6 = (TH1D*)file->Get("demo/resH_25_30");

  TH1D * resE = new TH1D("resE",";eta;res",8, 0., 4.);
  TH1D * resH = new TH1D("resH",";eta;res",8, 0., 4.);

  resE->SetBinContent(1, histE1->GetMean());
  resE->SetBinError(1, histE1->GetRMS());
  resE->SetBinContent(2, histE2->GetMean());
  resE->SetBinError(2, histE2->GetRMS());
  resE->SetBinContent(3, histE3->GetMean());
  resE->SetBinError(3, histE3->GetRMS());
  resE->SetBinContent(4, histE4->GetMean());
  resE->SetBinError(4, histE4->GetRMS());
  resE->SetBinContent(5, histE5->GetMean());
  resE->SetBinError(5, histE5->GetRMS());
  resE->SetBinContent(6, histE6->GetMean());
  resE->SetBinError(6, histE6->GetRMS());

  resE->SetLineColor(kRed);
  resE->Draw();


  resH->SetBinContent(1, histH1->GetMean());
  resH->SetBinError(1, histH1->GetRMS());
  resH->SetBinContent(2, histH2->GetMean());
  resH->SetBinError(2, histH2->GetRMS());
  resH->SetBinContent(3, histH3->GetMean());
  resH->SetBinError(3, histH3->GetRMS());
  resH->SetBinContent(4, histH4->GetMean());
  resH->SetBinError(4, histH4->GetRMS());
  resH->SetBinContent(5, histH5->GetMean());
  resH->SetBinError(5, histH5->GetRMS());
  resH->SetBinContent(6, histH6->GetMean());
  resH->SetBinError(6, histH6->GetRMS());

  resH->SetLineColor(kBlack);
  resH->Draw("same");


  //cout << hist1->GetMean() << endl;
  
  return;
}
