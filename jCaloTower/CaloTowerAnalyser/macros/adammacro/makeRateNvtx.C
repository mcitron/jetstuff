void makeRateNvtx()
{

  int nvtxBin=10;

  //   TFile * f = TFile::Open("./neutrino_skim_run.root");
  // TFile * f = TFile::Open("./batch/neutrino5/neutrino_out.root");

  //   TFile * f = TFile::Open("./neutrino_skim_run.root");
  TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140602/output_run0.root");
  std::vector<TString> PUSregime;
  PUSregime.push_back("5400_nopus");
  //PUSregime.push_back("5400_calib_nopus");
  //PUSregime.push_back("5450_nopus");
  //PUSregime.push_back("5450_calib_nopus");
  

  //PUSregime.push_back("gct");
  //PUSregime.push_back("gct_calib");

  std::vector<TString> jetnum;
  jetnum.push_back("alljet");
  jetnum.push_back("jet1");
  jetnum.push_back("jet2");
  jetnum.push_back("jet3");
  jetnum.push_back("jet4");


  TFile *top = new TFile("ratePlots_Nvtx.root","recreate");
  for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
  {      
    TDirectory * dir = top->mkdir((*iPUS).Data());
    dir->cd();
    for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
    {
      //TH1D * origplot = f->Get(("demo/"+*iPUS+"_gen/col1_"+*iJet+"_pt").Data());
      TH2D * rate_nvtx_plot=f->Get(("demo/"+*iPUS+"_gen/seed/col1_seed_"+*iJet+";2").Data());

      for(int nvtx=20; nvtx<65; nvtx+=nvtxBin){
	std::cout << nvtx <<std::endl;
        char buffer[100];
        sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+nvtxBin);
        TH1D * origplot = rate_nvtx_plot->ProjectionY(*iPUS+"_"+*iJet+"_"+TString(buffer),nvtx,nvtx+nvtxBin);
        makeCumu(origplot);
        origplot->Write();
      }
    }
  }

  top->Close();

}

TH1D * makeCumu(TH1D * input)
{
  TH1D * output = new TH1D();
  output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,0.);
  int dummy = 0;
  for (int bins = 0; bins != input->GetNbinsX()-1; bins++)
  {
    dummy += input->GetBinContent(bins);
    output->SetBinContent(bins,1-(double)dummy/norm);
  } 
  return output;
}
