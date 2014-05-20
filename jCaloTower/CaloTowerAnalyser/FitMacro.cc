FitMacro(){

  TFile* file = new TFile("output/fulloutput_ttbar.root");

  std::vector<TString> etabins;
  std::vector<TString> ptbins;

  etabins.push_back("eta_bin1");
  etabins.push_back("eta_bin2");
  etabins.push_back("eta_bin3");
  etabins.push_back("eta_bin4");

  ptbins.push_back("pt_0to20");
  ptbins.push_back("pt_20to40"); 
  ptbins.push_back("pt_40to60"); 
  ptbins.push_back("pt_60to80"); 
  ptbins.push_back("pt_80to100"); 
  ptbins.push_back("pt_100to120"); 
  ptbins.push_back("pt_120to140"); 
  ptbins.push_back("pt_140to160"); 
  ptbins.push_back("pt_160to180"); 
  ptbins.push_back("pt_180to200"); 

  //Fill an array of pT for each eta bin
  double p0[4][10];
  double p0err[4][10];
  double p1[4][10];
  double p1err[4][10];
  double ptarr[10]={20,40,60,80,100,120,140,160,180,200};

  int i=0;
  for(std::vector<TString>::const_iterator eta=etabins.begin(); eta!=etabins.end();eta++){
    int j=0;
    for(std::vector<TString>::const_iterator pt=ptbins.begin(); pt!=ptbins.end();pt++){

      file->cd((TString("demo/pus_histograms/Size_4/")+*eta+"/"+*pt+"/nint").Data());

      TProfile * profile = nint_4_out1_middle2->ProfileX();
      //nint_4_out1_middle2_profile->Fit("pol1","","",30,50);
      profile->Fit("pol1","","",30,50);
      //TF1* fit = nint_4_out1_middle2_profile->GetFunction("pol1");
      TF1* fit = profile->GetFunction("pol1");
      //nint_4_strip1_profile->Fit("pol1","","",30,50);
      //TF1* fit = nint_4_strip1_profile->GetFunction("pol1");
      p0[i][j]=fit->GetParameter(0);
      p0err[i][j]=fit->GetParError(0);
      p1[i][j]=fit->GetParameter(1);
      p1err[i][j]=fit->GetParError(1);

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

  TFile* outfile = new TFile("output/fitplots.root","RECREATE");

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

