void newMakeRateEff()
{

  TFile * f_ttbar = TFile::Open("/afs/cern.ch/work/m/mcitron/public/TTBAR/140603/ttbar_output.root");
  TFile * f_neutrino = TFile::Open("/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140603/neutrino_out.root");
  //TFile * f_neutrino = TFile::Open("../../neutrino_gun_out/neutrinogun_30May014.root");
  //TFile * f_neutrino = TFile::Open("matts_neutrino_fullrun.root");
  //TFile * f_ttbar = TFile::Open("matts_ttbar_fullrun.root");

  std::vector<TString> PUSregime;
  PUSregime.push_back("5400_nopus");
  PUSregime.push_back("5400_calib_nopus");
  PUSregime.push_back("5450_nopus");
  PUSregime.push_back("5450_calib_nopus");
  PUSregime.push_back("5400_global");
  PUSregime.push_back("5400_calib_global");
  PUSregime.push_back("5450_global");
  PUSregime.push_back("5400_donut");
  PUSregime.push_back("5400_calib_donut");
  PUSregime.push_back("5450_donut");
  PUSregime.push_back("5450_calib_donut");
  //PUSregime.push_back("gct");
  std::vector<TString> jetnum;
  jetnum.push_back("alljet");
  jetnum.push_back("jet1");
  jetnum.push_back("jet2");
  jetnum.push_back("jet3");
  jetnum.push_back("jet4");


  TFile *top = new TFile("ratePlots.root","recreate");
  //TH1D * matchedhist_global_global =  (f->Get("demo/ak4_global_pus/col2_matched_global_alljet_pt"));
  //TH1D * matchedhist_local_global =  (f->Get("demo/ak4_global_pus/col2_matched_local_alljet_pt"));
  for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
  {      
    TDirectory * dir = top->mkdir((*iPUS).Data());
    dir->cd();
    for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
    {
      //std::cout << "demo/"+*iPUS+"_gen/col2_"+*iJet+"_pt" << std::endl;
      TH1D * origplot_ttbar = f_ttbar->Get(("demo/"+*iPUS+"_gen/other/col1_"+*iJet+"_pt").Data());
      TH1D * origplot_neutrino = f_neutrino->Get(("demo/"+*iPUS+"_gen/other/col1_"+*iJet+"_pt").Data());
      //TH1D * origplot_ttbar = f_ttbar->Get(("demo/"+*iPUS+"_gen/col1_seed_"+*iJet).Data());
      //TH1D * origplot_neutrino = f_neutrino->Get(("demo/"+*iPUS+"_gen/col1_seed_"+*iJet).Data());

      TH1D* dummyplot = f_ttbar->Get("demo/5400_nopus_gen/other/col1_jet1_pt");
      int nTtbar = dummyplot->GetEntries();
      TH1D* dummyplot2 = f_neutrino->Get("demo/5400_nopus_gen/other/col1_jet1_pt");
      int nNeutrinoGun = dummyplot2->GetEntries();
      //Make the rates
      TH1D * cumuplot_ttbar = makeCumu(origplot_ttbar, nTtbar);
      cumuplot_ttbar->SetName("ttbar_col1_"+*iJet+"_pt");
      TH1D * cumuplot_neutrino = makeCumu(origplot_neutrino, nNeutrinoGun);
      cumuplot_neutrino->SetName("neutrino_col1_"+*iJet+"_pt");

      //Plot the rates for different bins against one another
      if(cumuplot_ttbar->GetNbinsX() != cumuplot_neutrino->GetNbinsX()) std::cout << "Different binning between rate and efficiency\n";
      else{

	TGraph * rate_efficiency = 
	  new TGraph(cumuplot_ttbar->GetNbinsX());
	rate_efficiency->SetName("rate_efficiency_"+*iJet);
	rate_efficiency->SetTitle(";Efficiency (ttbar normalised rate);Rate (0 bias normalised rate)");

	for(unsigned bin=0; bin<cumuplot_ttbar->GetNbinsX(); bin++){
	  rate_efficiency->SetPoint(bin, cumuplot_ttbar->GetBinContent(bin), cumuplot_neutrino->GetBinContent(bin));
	}

	rate_efficiency->Write();
      }


      cumuplot_neutrino->Write();
      cumuplot_ttbar->Write();
    }
  }

  top->Write();

}

TH1D * makeCumu(TH1D * input, int totalOverall)
{
  TH1D * output = new TH1D();
  output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int dummy = 0;
  for (int bins = 0; bins < input->GetNbinsX(); bins++)
  {
    dummy += input->GetBinContent(bins);
    if (norm!=0) output->SetBinContent(bins,(1-(double)dummy/norm)*norm/totalOverall);
    else output->SetBinContent(bins,0.);
  } 
  return output;
}
