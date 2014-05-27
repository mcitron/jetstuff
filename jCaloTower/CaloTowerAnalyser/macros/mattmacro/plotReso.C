plotReso(){

   //TFile* file = new TFile("global_PUS_all.root");
   TFile * file = TFile::Open("./batch/ttbar5/ttbar_out.root");
   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   //PUSregime.push_back("4300_nopus");
   PUSregime.push_back("5400_donut");
   //PUSregime.push_back("6550_nopus");
   //PUSregime.push_back("4300_donut");
   PUSregime.push_back("5400_global");
   //PUSregime.push_back("4300_global");
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
   for(std::vector<TString>::const_iterator eta=etabins.begin(); eta!=etabins.end();eta++){
      std::vector<double> p0;
      std::vector<double> p0err;
      std::vector<double> p1;
      std::vector<double> p1err;
      bool make_plot=true;
      for(std::vector<TString>::const_iterator pt=ptbins.begin(); pt!=ptbins.end();pt++){
	 std::cout << "demo/5400_nopus_gen/"+*eta+"/"+*pt+"/pt_ratio_nvts_algo1_"+njetsType+"_profile" << std::endl;
	 TProfile * nopus=file->Get(("demo/5400_nopus_gen/"+*eta+"/"+*pt+"/pt_ratio_nvts_algo1_"+njetsType+"_profile").Data());
	 TProfile * global=file->Get(("demo/5400_global_gen/"+*eta+"/"+*pt+"/pt_ratio_nvts_algo1_"+njetsType+"_profile").Data());
	 TProfile * donut=file->Get(("demo/5400_donut_gen/"+*eta+"/"+*pt+"/pt_ratio_nvts_algo1_"+njetsType+"_profile").Data());

	 TLegend* leg = new TLegend(0.2,0.2,0.48,0.5);
	 leg->SetFillColor(0);
	 leg->AddEntry(nopus,"No PUS","lep");
	 leg->AddEntry(donut,"Donut Sub","lep");
	 leg->AddEntry(global,"Global Sub","lep");

	 TCanvas * c = new TCanvas("c","",600,600);

	 c->cd();
	 gStyle->SetOptStat(0);
	 nopus->SetLineColor(1);
	 nopus->GetYaxis()->SetTitle("");
	 nopus->GetXaxis()->SetTitle("");

	 nopus->Draw();

	 donut->SetLineColor(2);
	 donut->GetYaxis()->SetTitle("");
	 donut->GetXaxis()->SetTitle("");
	 donut->Draw("same");

	 global->SetLineColor(4);
	 global->GetYaxis()->SetTitle("");
	 global->GetXaxis()->SetTitle("");
	 global->Draw("same");


	 //	 leg->Draw();


	 c->SaveAs("output/resolution_"+*pt+"_"+*eta+".png");
      }
   }
}

