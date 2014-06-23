void ratesNVTX(){
TFile * f_neutrino= new TFile("neutrino_output.root");
TFile * f_out= new TFile("./rateTestNVTX.root","recreate");
TTree * tree_neutrino = f_neutrino->Get("demo/L1Tree;1");
int cut = 30;
std::vector<TString> jetnum;
jetnum.push_back("0");
jetnum.push_back("1");
jetnum.push_back("2");
jetnum.push_back("3");
std::vector<TString> jetType;
jetType.push_back("5400_calib_nopus");
jetType.push_back("5450_calib_nopus");
//jetType.push_back("5450_calib_donut");
//jetType.push_back("5400_calib_donut");
//jetType.push_back("5400_calib_global");
//jetType.push_back("calib_gct");
TString bins = "(1000,0,1000)";
TString bins2 = "(10,0,100,1000,0,1000)";
double xpoints[50];
double ypoints[50];
for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
{
  TDirectory * jnum = f_out->mkdir("jetNumber_"+*iNum);
  jnum->cd();
  for (iType = jetType.begin();iType != jetType.end(); iType++)
  {

    tree_neutrino->Draw("jetPt_"+*iType+"["+*iNum+"]:mNPV>>"+*iType+"_"+*iNum+bins2,"","colz");
    TH2F *fullL1NVTX = (TH2F*)gPad->GetPrimitive(*iType+"_"+*iNum);
fullL1NVTX->Write();
    int i =0;
/*
    for(int nvtx=1; nvtx < fullL1NVTX->GetNbinsX(); nvtx+=1){
      //std::cout << fullL1NVTX->GetXaxis()->GetBinCenter(nvtx)<< std::endl;
      char buffer[1000];
      sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+1);
      TH1D * dummyplot = fullL1NVTX->ProjectionY("temp"+*iType+*iNum,nvtx,nvtx+1);
      //dummyplot->Write();
      if(dummyplot->GetEntries() != 0){
	double factor = (double) dummyplot->GetEntries()/fullL1NVTX->GetEntries();
	TH1D * cumuplot=makeCumu(dummyplot,1);
	cumuplot->SetTitle(buffer);
	cumuplot->Write();
	ypoints[i]=cumuplot->GetBinContent(cumuplot->FindBin(100));
	std::cout << ypoints[i]<< std::endl;
      }
      else
      {
	ypoints[i]=0.;
      }
      xpoints[i]=nvtx;
      i++;
    }

    TGraph *rate_nvtx_bin_graph = new TGraph(fullL1NVTX->GetNbinsX()-1,&xpoints[0],&ypoints[0]);
    //TGraph *rate_nvtx_bin_graph = new TGraph(dummyplot->GetNbinsX(),&xpoints[0],&ypoints[0]);

    rate_nvtx_bin_graph->SetTitle("ptCut"+*iType+*iNum);
    rate_nvtx_bin_graph->GetXaxis()->SetTitle("nvtx");
    rate_nvtx_bin_graph->GetYaxis()->SetTitle("Rate");
    rate_nvtx_bin_graph->SetName("ptCut"+*iType+*iNum);
    rate_nvtx_bin_graph->SetMarkerStyle(5);
    //  rate_nvtx_bin_graph->SetLineStyle(0);
    rate_nvtx_bin_graph->GetYaxis()->SetRangeUser(0,1);
    rate_nvtx_bin_graph->Write();
*/
  }
}
f_out->Close();
return;
}

TH1D * makeCumu(TH1D * input, double overallNorm){

  TH1D * output = new TH1D(*input);
  //output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int nYbins = input->GetNbinsY();
  int dummy = input->GetBinContent(nXbins+1);
  for (int xbins = 0; xbins <= nXbins; xbins++)
  {
    dummy += input->GetBinContent(nXbins-xbins);
    output->SetBinContent((nXbins-xbins),((double)dummy)/overallNorm);
  }

  return output;
}
