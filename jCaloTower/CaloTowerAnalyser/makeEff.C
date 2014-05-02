void makeEff()
{

TFile *f = TFile::Open("./matchingeff.root");
TH1D * allhist =  (f->Get("demo/gen_l1trigger/col2_alljet_pt"));
TH1D * matchedhist_global =  (f->Get("demo/gen_l1trigger/col2_matched_global_alljet_pt"));
TH1D * matchedhist_local =  (f->Get("demo/gen_l1trigger/col2_matched_local_alljet_pt"));

allhist->Rebin(10);

matchedhist_local->Rebin(10);
matchedhist_global->Rebin(10);
matchedhist_local->Sumw2();
matchedhist_global->Sumw2();
allhist->Sumw2();

//TH1D matcheff = ((*matchedhist).Divide(allhist));
//matchedhist->Divide(allhist);
//matchedhist->Draw();
TGraphAsymmErrors * matchCurvelocal = effDiv(matchedhist_local,allhist);
TGraphAsymmErrors * matchCurveglobal = effDiv(matchedhist_global,allhist);
matchCurvelocal->SetLineColor(2);
matchCurvelocal->Draw("alp");
matchCurveglobal->Draw("same");
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
