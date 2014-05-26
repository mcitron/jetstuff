void makeRate2D()
{

   //   TFile * f = TFile::Open("./neutrino_skim_run.root");
   TFile * f = TFile::Open("./batch/neutrino5/neutrino_out.root");

   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   //PUSregime.push_back("4300_nopus");
   PUSregime.push_back("5400_donut");
   //PUSregime.push_back("4300_donut");
   PUSregime.push_back("5400_global");
   //PUSregime.push_back("4300_global");
   PUSregime.push_back("gct");
   std::vector<TString> jetnum;
   //  jetnum.push_back("alljet");
   jetnum.push_back("jet1");
   // jetnum.push_back("jet2");
   // jetnum.push_back("jet3");
   //jetnum.push_back("jet4");


   TFile *top = new TFile("ratePlots.root","recreate");
   for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
   {      
      TDirectory * dir = top->mkdir((*iPUS).Data());
      dir->cd();
      for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
      {
	 TH2D * origplot = f->Get(("demo/"+*iPUS+"_gen/col1_"+*iJet+"_pt_NPV").Data());
	 origplot->RebinAxis(10,origplot->GetXaxis());//->Rebin(10);
	 TH1D * cumuplot = makeCumu(origplot,20);
	 cumuplot->SetTitle(*iPUS+*iJet);
	 cumuplot->Write(*iPUS+*iJet);
	 //delete cumuplot;
      }
   }

   top->Write();

}

TH1D * makeCumu(TH2D * input,double ptcut)
{
   TH1D * output = new TH1D("rate",";NPV;",100,-0.5,99.5);
   //output=input;
   //int norm = input->GetEntries();

   //   output->SetBinContent(0,1.);
   double nbinspt=input->GetXaxis()->FindBin(ptcut);
   for (int binsx = 0; binsx != input->GetNbinsX(); binsx++)
   {
      double dummy1 = 0.;
      double dummy2 = 0.;
      for (int binsy = 0; binsy != input->GetNbinsY();binsy++)
      {
	 dummy1 += input->GetBinContent(binsx,binsy);
	 if (binsy > nbinspt)
	 {
	    dummy2+=input->GetBinContent(binsx,binsy);
	 }
      } 
      double rate = (dummy1==0) ? 0:dummy2/dummy1;// std::cout << (double) dummy2/dummy1 << std::endl;
      output->SetBinContent(binsx,rate);
   } 
   return output;
}
