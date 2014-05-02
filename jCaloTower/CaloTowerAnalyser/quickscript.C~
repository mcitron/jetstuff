void quickscript() {

  TFile * file = new TFile("histograms-ttbar_13TeV_PU40_25ns_test_skimmed_v2_5GeVseed_1000events.root","READ");

  TProfile * prof1 = ((TH2D*)file->Get("demo/global_histograms/deltaGenL1_pT3050_eta1_v1"))->ProfileY();
  TProfile * prof2 = ((TH2D*)file->Get("demo/global_histograms/deltaGenL1_pT3050_eta1_v4"))->ProfileY();
  TProfile * prof3 = ((TH2D*)file->Get("demo/global_histograms/deltaGenL1_pT3050_eta2_v1"))->ProfileY();
  TProfile * prof4 = ((TH2D*)file->Get("demo/global_histograms/deltaGenL1_pT3050_eta2_v4"))->ProfileY();
  TProfile * prof5 = ((TH2D*)file->Get("demo/global_histograms/deltaGenL1_pT3050_eta3_v1"))->ProfileY();
  TProfile * prof6 = ((TH2D*)file->Get("demo/global_histograms/deltaGenL1_pT3050_eta3_v4"))->ProfileY();

  TF1 *f1 = new TF1("f1", "pol1", 22.5, 52.5);
  bool doFit = false;

  TCanvas * eta1 = new TCanvas("eta1","eta1",600,600);
  prof1->GetYaxis()->SetRangeUser(0.0,1.0);
  prof1->SetStats(0);
  prof1->SetLineColor(kBlack);
  prof1->SetLineWidth(2);
  prof1->Draw();
  prof2->SetLineColor(kRed);
  prof2->SetLineWidth(2);
  prof2->Draw("same");

  TCanvas * eta2 = new TCanvas("eta2","eta2",600,600);
  prof3->GetYaxis()->SetRangeUser(0.0,1.0);
  prof3->SetStats(0);
  prof3->SetLineColor(kBlack);
  prof3->SetLineWidth(2);
  prof3->Draw();
  prof4->SetLineColor(kRed);
  prof4->SetLineWidth(2);
  prof4->Draw("same");

  TCanvas * eta3 = new TCanvas("eta3","eta3",600,600);
  prof5->GetYaxis()->SetRangeUser(0.0,1.0);
  prof5->SetStats(0);
  prof5->SetLineColor(kBlack);
  prof5->SetLineWidth(2);
  prof5->Draw();
  prof6->SetLineColor(kRed);
  prof6->SetLineWidth(2);
  prof6->Draw("same");

  if(doFit) {
    prof1->Fit("f1","R");
    //cout << f1->GetParameter(1) << endl;
    prof2->Fit("f1","R");
    prof3->Fit("f1","R");
    //cout << f1->GetParameter(1) << endl;
    prof4->Fit("f1","R");
    prof5->Fit("f1","R");
    //cout << f1->GetParameter(1) << endl;
    prof6->Fit("f1","R");
  }
  return;
}
