void makeTopEff()
{

   TFile * f = TFile::Open("./global_PUS_all.root");

   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   PUSregime.push_back("4300_nopus");
   PUSregime.push_back("5400_donut");
   PUSregime.push_back("4300_donut");
   PUSregime.push_back("5400_global");
   PUSregime.push_back("4300_global");
   PUSregime.push_back("gct");
   std::vector<TString> algo;
   std::vector<TString> jetnum;
   jetnum.push_back("x1");
   jetnum.push_back("x2");
   jetnum.push_back("x3");
   jetnum.push_back("x4");

   TFile *top = new TFile("top_eff.root","recreate");
   //TH1D * matchedhist_global_global =  (f->Get("demo/ak4_global_pus/col2_matched_global_alljet_pt"));
   //TH1D * matchedhist_local_global =  (f->Get("demo/ak4_global_pus/col2_matched_local_alljet_pt"));
   //for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
   {      
      //TDirectory * dir = top->mkdir((*iPUS).Data());
      //dir->cd();

      TH1D * denom = f->Get("demo/global_histograms/mean_top");
      denom->Rebin(10);
      denom->Sumw2();
      for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
      {
	 TH1D * num = f->Get(("demo/global_histograms/Efficiency_"+*iJet).Data());
	 num->Rebin(10);
	 num->Sumw2();
	 TGraphAsymmErrors * result=(effDiv(num,denom));
	 result->Write(("Eff"+*iJet));
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
