void makeNewRate()
{
  TFile * f = TFile::Open("neutrino_skim_run.root");
  TFile * f_out = new TFile("neutrino_rate.root","recreate");
  TTree * tree = (TTree *) f->Get("demo/L1Tree;1"); 
  int mNPV;
  f_out->cd();
  std::vector<float> * donutpt; 
  std::vector<float> * globalpt; 
  tree->SetBranchAddress("jetPt_5400_calib_global",&globalpt);
  tree->SetBranchAddress("jetPt_5450_calib_donut",&donutpt);

  TH1D * donutjetpt = new TH1D ("donutjetpt_rate",";pt;",1000,-0.5,999.5);
  TH1D * globaljetpt = new TH1D ("globaljetpt_rate",";pt;",1000,-0.5,999.5);


    int nevent = tree->GetEntries();
    for (int k =30; k <200; k++)
    {
      double counterdo = 0;
      double counterglo = 0;
      double countergen = 0;

      for (int i = 0; i < nevent;i++)
      {

	tree->GetEvent(i);
	//	  for (int  j = 0; j < l1pt->size(); j++)
	if(donutpt->size()>0 && donutpt->at(0)>k)
	{
	  counterdo+=1;
	} 
	if(globalpt->size()>0 && globalpt->at(0)>k)
	{
	  counterglo+=1;
	} 
      }
      globaljetpt->SetBinContent(k,counterglo/nevent);//counter/nevent);
      donutjetpt->SetBinContent(k,counterdo/nevent);//counter/nevent);
    }
    globaljetpt->SetLineColor(4);
    donutjetpt->SetLineColor(2);

    globaljetpt->Write();
    donutjetpt->Write();
    f_out->Close();
}
