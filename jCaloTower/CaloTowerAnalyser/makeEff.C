void makeEff()
{

TFile * f = TFile::Open("./global_PUS.root");
TH1D * allhistDonut =  (f->Get("demo/ak4_donut_pus/col2_alljet_pt"));
TH1D * globalDonut = (f->Get("demo/ak4_donut_pus/col2_matched_global_alljet_pt"));
TH1D * localDonut =f->Get("demo/ak4_donut_pus/col2_matched_local_alljet_pt");

TH1D * allhistNopus =  (f->Get("demo/ak4_nopus_pus/col2_alljet_pt"));
TH1D * globalNopus = f->Get("demo/ak4_nopus_pus/col2_matched_global_alljet_pt");
TH1D * localNopus = f->Get("demo/ak4_nopus_pus/col2_matched_local_alljet_pt");

TH1D * allhistMedian =  (f->Get("demo/ak4_median_pus/col2_alljet_pt"));
TH1D * globalMedian = f->Get("demo/ak4_median_pus/col2_matched_global_alljet_pt");
TH1D * localMedian = f->Get("demo/ak4_median_pus/col2_matched_local_alljet_pt");

TFile *top = new TFile("matchingEff.root","recreate");
//TH1D * matchedhist_global_global =  (f->Get("demo/ak4_global_pus/col2_matched_global_alljet_pt"));
//TH1D * matchedhist_local_global =  (f->Get("demo/ak4_global_pus/col2_matched_local_alljet_pt"));

allhistDonut->Rebin(10);
allhistDonut->Sumw2();
allhistMedian->Rebin(10);
allhistMedian->Sumw2();
allhistNopus->Rebin(10);
allhistNopus->Sumw2();

globalNopus->Rebin(10);
localNopus->Rebin(10);
globalNopus->Sumw2();
localNopus->Sumw2();

globalDonut->Rebin(10);
localDonut->Rebin(10);
globalDonut->Sumw2();
localDonut->Sumw2();

globalMedian->Rebin(10);
localMedian->Rebin(10);
globalMedian->Sumw2();
localMedian->Sumw2();

//TH1D matcheff = ((*matchedhist).Divide(allhist));
//matchedhist->Divide(allhist);
//matchedhist->Draw();
TGraphAsymmErrors * matchCurvelocaldonut = effDiv(localDonut,allhistDonut);
TGraphAsymmErrors * matchCurveglobaldonut = effDiv(globalDonut,allhistDonut);

TGraphAsymmErrors * matchCurvelocalnopus = effDiv(localNopus,allhistNopus);
TGraphAsymmErrors * matchCurveglobalnopus = effDiv(globalNopus,allhistNopus);

TGraphAsymmErrors * matchCurvelocalmedian = effDiv(localMedian,allhistMedian);
TGraphAsymmErrors * matchCurveglobalmedian = effDiv(globalMedian,allhistMedian);

top->cd();
matchCurvelocaldonut->Write("local_donut");
matchCurveglobaldonut->Write("global_donut");
matchCurvelocalnopus->Write("local_nopus");
matchCurveglobalnopus->Write("global_nopus");
matchCurvelocalmedian->Write("local_median");
matchCurveglobalmedian->Write("global_median");
top->Write();
}

TGraphAsymmErrors * effDiv(TH1D * matchedhist, TH1D * allhist)
{
   TGraphAsymmErrors* matchCurve = new TGraphAsymmErrors();
   matchCurve->SetName("matchCurve");

   //TH1D matcheff = ((*matchedhist).Divide(allhist));
   //matchedhist->Divide(allhist);
   //matchedhist->Draw();

   matchCurve->Divide(matchedhist,allhist);
   return matchCurve;
}
