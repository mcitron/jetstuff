void makeTurnOn()
{
   TFile *top = new TFile("matchingEffcut.root","recreate");
   //TFile * f = TFile::Open("./batch/ttbar5/ttbar_out.root");//global_PUS_all.root");
   //`TFile * f = TFile::Open("./batch/qcd_test/output_run10.root");
   TFile * f = TFile::Open("./batch/qcd_test/output_120-170_qcd.root");
   //`TFile * f = TFile::Open("./batch/qcd_test/qcd_calib.root");
  // TFile * f = TFile::Open("global_PUS_TEST.root");//global_PUS_all.root");
   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   PUSregime.push_back("5400_calib_nopus");
   PUSregime.push_back("5450_nopus");
   PUSregime.push_back("4300_nopus");
   PUSregime.push_back("5400_donut");
   PUSregime.push_back("5400_calib_donut");
   PUSregime.push_back("5450_donut");
   PUSregime.push_back("4300_donut");
   PUSregime.push_back("5400_global");
   PUSregime.push_back("5400_calib_global");
   PUSregime.push_back("4300_global");
   PUSregime.push_back("gct");

   std::vector<TString> jetnum;
   jetnum.push_back("alljet");
   jetnum.push_back("jet1");
   jetnum.push_back("jet2");
   jetnum.push_back("jet3");
   jetnum.push_back("jet4");

   std::vector<TString> ptcut;
   ptcut.push_back("pt20");
   ptcut.push_back("pt40");
   ptcut.push_back("pt60");
   ptcut.push_back("pt80");

   top->cd();
   for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
   {      
      TDirectory * dir = top->mkdir((*iPUS).Data());
      dir->cd();
      for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
      {
	 std::cout << "demo/"+*iPUS+"_gen/col2_matched_algo1_"+*iJet+"_pt" << std::endl;
	 TH1D * denom = f->Get(("demo/"+*iPUS+"_gen/col2_matched_algo1_"+*iJet+"_pt").Data());
	 denom->Rebin(10);
	 denom->Sumw2();
	 for (auto iPt = ptcut.begin(); iPt!=ptcut.end(); iPt++)
	 {
//	    std::cout<<"here" << std::endl;
	    TH1D *num=(f->Get(("demo/"+*iPUS+"_gen/col2_matched_algo1_"+*iJet+"_cut_"+*iPt).Data()));
	    num->Rebin(10);
	    num->Sumw2();
	    TGraphAsymmErrors * result=(effDiv(num,denom));
	    result->Write((*iJet+*iPt));
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
