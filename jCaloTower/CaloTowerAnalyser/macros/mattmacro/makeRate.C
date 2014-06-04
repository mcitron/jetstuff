void makeRate()
{

//   TFile * f = TFile::Open("./neutrino_skim_run.root");
 // TFile * f = TFile::Open("./batch/neutrino5/neutrino_out.root");

   //TFile * f = TFile::Open("./global_PUS_TEST.root");
   TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140603/neutrino_out.root");
   //TFile * f = TFile::Open("/afs/cern.ch/work/m/mcitron/public/TTBAR/140603/ttbar_output.root");
   std::vector<TString> PUSregime;
   PUSregime.push_back("5400_nopus");
   //PUSregime.push_back("5450_nopus");
  // PUSregime.push_back("5400_donut");
   //PUSregime.push_back("5450_donut");
   //PUSregime.push_back("5400_global");
/*   PUSregime.push_back("4300_nopus");
   PUSregime.push_back("4300_donut");
   PUSregime.push_back("4300_global");
   PUSregime.push_back("gct");*/
   std::vector<TString> jetnum;
   jetnum.push_back("alljet");
   jetnum.push_back("jet1");
   jetnum.push_back("jet2");
   jetnum.push_back("jet3");
   jetnum.push_back("jet4");


   TFile *top = new TFile("ratePlots_n.root","recreate");
   for (auto iPUS = PUSregime.begin(); iPUS!=PUSregime.end(); iPUS++)
   {      
      TDirectory * dir = top->mkdir((*iPUS).Data());
      dir->cd();
      for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
      {
	 //TH1D * origplot = f->Get(("demo/"+*iPUS+"_gen/col1_"+*iJet+"_pt").Data());
	 //std::cout << "demo/"+*iPUS+"_gen/seed/col1_seed_"+*iJet+";1" << std::endl;
	 TH1D * origplot = f->Get(("demo/"+*iPUS+"_gen/seed/col1_seed_"+*iJet).Data());
//	 TH1D * origplot = f->Get(("demo/"+*iPUS+"_gen/superseed/col1_rings_0_1_"+*iJet).Data());
//	 TH1D * origplot = f->Get(("demo/"+*iPUS+"_gen/other/col1_"+*iJet+"_pt").Data());
	 TH1D * cumuplot = makeCumu(origplot);
	 cumuplot->Write();
      }
   }

   top->Write();

}

TH1D * makeCumu(TH1D * input)
{
   TH1D * output = new TH1D();
   output=input;
   int norm = input->GetEntries();
   //output->SetBinContent(0,1.);
   int dummy = 0;
   for (int bins = 0; bins != input->GetNbinsX()-1; bins++)
   {
      dummy += input->GetBinContent(bins);
      output->SetBinContent(bins,1-(double)dummy/norm);
   } 
   return output;
}
