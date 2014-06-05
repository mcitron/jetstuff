void makeRateNvtx()
{

  int nvtxBin=10;
  int nvtxMin=20;
  int nvtxMax=70;
  int cut =30;
  //   TFile * f = TFile::Open("./neutrino_skim_run.root");
  // TFile * f = TFile::Open("./batch/neutrino5/neutrino_out.root");

  //   TFile * f = TFile::Open("./neutrino_skim_run.root");
  TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140604/neutrino_output.root");
//  TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/TTBAR/140603/ttbar_output.root");
  std::vector<TString> PUSregime;
  PUSregime.push_back("5400_nopus");
  PUSregime.push_back("5400_global");
  PUSregime.push_back("5400_donut");
  PUSregime.push_back("5450_nopus");
  PUSregime.push_back("5450_donut");
  //PUSregime.push_back("5400_calib_nopus");
  //PUSregime.push_back("5450_nopus");
  //PUSregime.push_back("5450_calib_nopus");


  //PUSregime.push_back("gct");
  //PUSregime.push_back("gct_calib");

  std::vector<TString> jetnum;
  //  jetnum.push_back("alljet");
  jetnum.push_back("jet1");
  jetnum.push_back("jet2");
  jetnum.push_back("jet3");
  jetnum.push_back("jet4");

  double xpoints[50];
  double ypoints[50];

  TH2D * dummy_nvtx_plot=f->Get("demo/5400_nopus_gen/other/col1_jet1_pt_NPV");
  TFile *top = new TFile("ratePlots_Nvtx_tt.root","recreate");
  for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
  {      
    TDirectory * dir = top->mkdir((*iPUS).Data());
    dir->cd();
    for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
    {
      //TH1D * origplot = f->Get(("demo/"+*iPUS+"_gen/col1_"+*iJet+"_pt").Data());
      TH2D * rate_nvtx_plot=f->Get(("demo/"+*iPUS+"_gen/other/col1_"+*iJet+"_pt_NPV").Data());
      int i=0;
      for(int nvtx=nvtxMin; nvtx <= nvtxMax; nvtx+=nvtxBin){
	char buffer[100];
	sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+nvtxBin);
	TH1D * origplot = rate_nvtx_plot->ProjectionY(*iPUS+"_"+*iJet+"_"+TString(buffer),nvtx,nvtx+nvtxBin);

	TH1D * dummyplot = dummy_nvtx_plot->ProjectionY("temp",nvtx,nvtx+nvtxBin);
	double numen = dummyplot->GetEntries();

	makeCumu(origplot,numen);
	ypoints[i]=origplot->GetBinContent(origplot->FindBin(cut));
	//std::cout << ypoints[i] << std::endl;

	origplot->Write();
	xpoints[i]=nvtx;
	i++;
      }

      //TGraph *rate_nvtx_bin_graph = new TGraph(6,&xpoints[0],&ypoints[0]);
      TGraph *rate_nvtx_bin_graph = new TGraph((nvtxMax-nvtxMin)/nvtxBin,&xpoints[0],&ypoints[0]);

      rate_nvtx_bin_graph->SetTitle("ptCut"+*iJet);
      rate_nvtx_bin_graph->GetXaxis()->SetTitle("nvtx");
      rate_nvtx_bin_graph->GetYaxis()->SetTitle("Rate");
      rate_nvtx_bin_graph->SetName("ptCut"+*iJet);
      rate_nvtx_bin_graph->SetMarkerStyle(5);
      //  rate_nvtx_bin_graph->SetLineStyle(0);
      rate_nvtx_bin_graph->GetYaxis()->SetRangeUser(0,1);
      rate_nvtx_bin_graph->Write();
    }
  }

  top->Close();

}
/*
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
*/
TH1D * makeCumu(TH1D * input, int totalOverall)
{
  TH1D * output = new TH1D();
  output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  std::cout << norm <<"  "<<totalOverall << std::endl;
  int dummy = 0;
  for (int bins = 0; bins < input->GetNbinsX(); bins++)
  {
    dummy += input->GetBinContent(bins);
    if (norm!=0) output->SetBinContent(bins,(1-(double)dummy/norm)*norm/totalOverall);
    else output->SetBinContent(bins,0.);
  } 
  return output;
}
