makeFit(){

   //TFile* file = new TFile("global_PUS_all.root");
   //TFile * file = TFile::Open("./batch/ttbar2/ttbar_out.root");
   TFile * f = TFile::Open("./batch/qcd_test/qcd_calib.root");
   //TFile * file = TFile::Open("./batch/ttbar2/ttbar_out.root");
   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   PUSregime.push_back("5400_calib_nopus");
   PUSregime.push_back("4300_nopus");
   PUSregime.push_back("5400_calib_donut");
   PUSregime.push_back("5400_donut");
   //PUSregime.push_back("6550_nopus");
   PUSregime.push_back("4300_donut");
   PUSregime.push_back("5400_calib_global");
   PUSregime.push_back("5400_global");
   PUSregime.push_back("4300_global");
   PUSregime.push_back("gct");

   TString njetsType = "alljet";

   std::vector<TString> etabins;
   std::vector<TString> ptbins;

   etabins.push_back("eta_-28to-14");
   etabins.push_back("eta_-14to0");
   etabins.push_back("eta_0to14");
   etabins.push_back("eta_14to28");

   ptbins.push_back("pt_0to20");
   ptbins.push_back("pt_20to40");
   ptbins.push_back("pt_40to60");
   ptbins.push_back("pt_60to80");
   ptbins.push_back("pt_80to100");
   ptbins.push_back("pt_100to120");

   std::vector<double> ptarr;//,60,100,140,180,220};
   ptarr.push_back(10);
   ptarr.push_back(30);
   ptarr.push_back(50);
   ptarr.push_back(70);
   ptarr.push_back(90);
   ptarr.push_back(110);
   int i = 0;
   TFile* top = new TFile((njetsType+"_fitplots.root").Data(),"RECREATE");
   for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
{      
   TDirectory * dir = top->mkdir((*iPUS).Data());
   dir->cd();
   for(std::vector<TString>::const_iterator eta=etabins.begin(); eta!=etabins.end();eta++){
      std::vector<double> p0;
      std::vector<double> p0err;
      std::vector<double> p1;
      std::vector<double> p1err;
      bool make_plot=true;
      for(std::vector<TString>::const_iterator pt=ptbins.begin(); pt!=ptbins.end();pt++){
	 TProfile * profile_plot=file->Get(("demo/"+*iPUS+"_gen/"+*eta+"/"+*pt+"/pt_ratio_nvts_algo1_"+njetsType+"_profile").Data());
	 i = profile_plot->Fit("pol1","","",30,50);
	 if (i!=0)
	 {
	    make_plot=false;
	    break;
	 }
	 TF1* fit_plot = profile_plot->GetFunction("pol1");

	 p0.push_back(fit_plot->GetParameter(0));
	 p0err.push_back(fit_plot->GetParError(0));
	 p1.push_back(fit_plot->GetParameter(1));
	 p1err.push_back(fit_plot->GetParError(1));
      }
      if(make_plot)
      {
	 TGraphErrors *p0plot = new TGraphErrors(ptarr.size(), &(ptarr[0]), &(p0[0]), 0, &(p0err[0]) );
	 p0plot->SetName("p0"+*eta); 
	 p0plot->SetTitle("p0"+*eta+";PT;p0"); 

	 TGraphErrors *p1plot = new TGraphErrors(ptarr.size(), &(ptarr[0]), &(p1[0]), 0, &(p1err[0]) );
	 p1plot->SetName("p1"+*eta); 
	 p1plot->SetTitle("p1"+*eta+";PT;p1"); 

	 p0plot->Write();
	 p1plot->Write();
      }
   }
}
top->Write();
}

