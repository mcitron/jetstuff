void makeEff()
{

   TFile * f = TFile::Open("./batch/qcd_test/qcd_calib.root");
// TFile * f = TFile::Open("./global_PUS_TEST.root");

   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   PUSregime.push_back("5400_calib_nopus");
   PUSregime.push_back("5450_nopus");
   //PUSregime.push_back("4300_nopus");
   PUSregime.push_back("5400_donut");
   PUSregime.push_back("5400_calib_donut");
   PUSregime.push_back("5450_donut");
  // PUSregime.push_back("4300_donut");
   PUSregime.push_back("5400_global");
   PUSregime.push_back("5400_calib_global");
   //PUSregime.push_back("4300_global");
   PUSregime.push_back("gct");
   std::vector<TString> algo;
   algo.push_back("algo1");
   algo.push_back("algo2");
   std::vector<TString> jetnum;
   //jetnum.push_back("alljet");
   jetnum.push_back("jet1");
   //jetnum.push_back("jet2");
   //jetnum.push_back("jet3");
   //jetnum.push_back("jet4");

   TFile *top = new TFile("ttbar_match.root","recreate");
   //TH1D * matchedhist_global_global =  (f->Get("demo/ak4_global_pus/col2_matched_global_alljet_pt"));
   //TH1D * matchedhist_local_global =  (f->Get("demo/ak4_global_pus/col2_matched_local_alljet_pt"));
   for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
   {      
      TDirectory * dir = top->mkdir((*iPUS).Data());
      dir->cd();
      for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
      {
	 TH1D * denom = f->Get(("demo/"+*iPUS+"_gen/col2_"+*iJet+"_pt").Data());
	 denom->Rebin(10);
	 denom->Sumw2();
	 for (auto iAlgo = algo.begin(); iAlgo!=algo.end(); iAlgo++)
	 {
	    TH1D *num=(f->Get(("demo/"+*iPUS+"_gen/col2_matched_"+*iAlgo+"_"+*iJet+"_pt").Data()));
	    num->Rebin(10);
	    num->Sumw2();
	    TGraphAsymmErrors * result=(effDiv(num,denom));
	    result->Write((*iJet+"_"+*iAlgo));
	 } 
      }
   }

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
