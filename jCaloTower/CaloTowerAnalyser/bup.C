FitMacro(){

  TFile* file = new TFile("global_PUS.root");

  std::vector<TString> etabins;
  std::vector<TString> ptbins;

  etabins.push_back("eta_-28to-14");
  etabins.push_back("eta_-14to0");
  etabins.push_back("eta_0to14");
  etabins.push_back("eta_14to28");

  ptbins.push_back("pt_0to40");
  ptbins.push_back("pt_40to80");
  ptbins.push_back("pt_80to120");
  ptbins.push_back("pt_120to160");
  ptbins.push_back("pt_160to200");
  ptbins.push_back("pt_200to240");

  //Fill an array of pT for each eta bin
  std::vector<double> p0vec;
  std::vector<double> p0errvec;
  std::vector<double> p1vec;
  std::vector<double> p1errvec;

  double p0[4][6];
  double p0err[4][6];
  double p1[4][6];
  double p1err[4][6];
  double ptarr[6]={20,60,100,140,180,220};

  int i=0;
  for(std::vector<TString>::const_iterator eta=etabins.begin(); eta!=etabins.end();eta++){
     int j=0;

     for(std::vector<TString>::const_iterator pt=ptbins.begin(); pt!=ptbins.end();pt++){

	file->cd((TString("demo/donut_gen/")+*eta+"/"+*pt+"/").Data());
	//std::cout << TString("demo/donut_gen/")+*eta+"/"+*pt+"/" << std::endl;
	//TProfile * alljet_donut=(TString("demo/donut_gen/")+*eta+"/"+*pt+"/"+"pt_ratio_nvts_algo1_alljet_profile")
	//TProfile * alljet_nopus=(TString("demo/nopus_gen/")+*eta+"/"+*pt+"/"+"pt_ratio_nvts_algo1_alljet_profile")
	pt_ratio_nvts_algo1_alljet_profile->Fit("pol1","","",30,50);
	TF1* fitdonut = pt_ratio_nvts_algo1_alljet_profile->GetFunction("pol1");
	//TF1* fitnopus = alljet_nopus->GetFunction("pol1");
	//p0[i][j]=fit->GetParameter(0);
	// p0err[i][j]=fit->GetParError(0);
	//p1[i][j]=fit->GetParameter(1);
	//p1err[i][j]=fit->GetParError(1);

	p0[i][j]=fitdonut->GetParameter(0);
	p0err[i][j]=fitdonut->GetParError(0);
	p1[i][j]=fitdonut->GetParameter(1);
	p1err[i][j]=fitdonut->GetParError(1);

	j++;
     }
     i++;
  }
  //Create graphs for all the bins
  TGraphErrors* p0eta1 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p0[0],0,p0err[0]);
  TGraphErrors* p0eta2 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p0[1],0,p0err[1]);
  TGraphErrors* p0eta3 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p0[2],0,p0err[2]);
  TGraphErrors* p0eta4 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p0[3],0,p0err[3]);
  TGraphErrors* p1eta1 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p1[0],0,p1err[0]);
  TGraphErrors* p1eta2 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p1[1],0,p1err[1]);
  TGraphErrors* p1eta3 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p1[2],0,p1err[2]);
  TGraphErrors* p1eta4 = new TGraphErrors(ptbins.size()-1,&ptarr[0],p1[3],0,p1err[3]);

  p0eta1->SetName("p0eta1"); 
  p0eta2->SetName("p0eta2"); 
  p0eta3->SetName("p0eta3"); 
  p0eta4->SetName("p0eta4"); 
  p1eta1->SetName("p1eta1"); 
  p1eta2->SetName("p1eta2"); 
  p1eta3->SetName("p1eta3"); 
  p1eta4->SetName("p1eta4"); 

  p0eta1->SetTitle("p0eta1;PT;p0"); 
  p0eta2->SetTitle("p0eta2;PT;p0"); 
  p0eta3->SetTitle("p0eta3;PT;p0"); 
  p0eta4->SetTitle("p0eta4;PT;p0"); 
  p1eta1->SetTitle("p1eta1;PT;p1"); 
  p1eta2->SetTitle("p1eta2;PT;p1"); 
  p1eta3->SetTitle("p1eta3;PT;p1"); 
  p1eta4->SetTitle("p1eta4;PT;p1"); 

  TFile* outfile = new TFile("fitplots.root","RECREATE");

  outfile->cd();

  p0eta1->Write();
  p0eta2->Write();
  p0eta3->Write();
  p0eta4->Write();
  p1eta1->Write();
  p1eta2->Write();
  p1eta3->Write();
  p1eta4->Write();

}

