void makeNewRate()
{
  TFile * f = TFile::Open("neutrino_skim_run.root");
  TFile * f_out = new TFile("neutrino_rate.root","recreate");
  TTree * tree = (TTree *) f->Get("demo/L1Tree;3"); 
  int mNPV;
  f_out->cd();
  std::vector<float> * donutpt; 
  std::vector<float> * donutseedpt; 
  std::vector<float> * globalpt; 
  std::vector<float> * nopuspt; 
  std::vector<float> * nopusseedpt; 
  int jetnum = 4;
  tree->SetBranchAddress("jetPt_5400_calib_global",&globalpt);
  tree->SetBranchAddress("jetPt_5450_calib_donut",&donutseedpt);
  tree->SetBranchAddress("jetPt_5400_calib_donut",&donutpt);
  tree->SetBranchAddress("jetPt_5400_calib_nopus",&nopuspt);
  tree->SetBranchAddress("jetPt_5450_calib_nopus",&nopusseedpt);

  TH1D * donutjetpt = new TH1D ("donutjetpt_rate",";pt;",1000,-0.5,999.5);
  TH1D * donutseedjetpt = new TH1D ("donutseedjetpt_rate",";pt;",1000,-0.5,999.5);
  TH1D * globaljetpt = new TH1D ("globaljetpt_rate",";pt;",1000,-0.5,999.5);
  TH1D * nopusjetpt = new TH1D ("nopusjetpt_rate",";pt;",1000,-0.5,999.5);
  TH1D * nopusseedjetpt = new TH1D ("nopusseedjetpt_rate",";pt;",1000,-0.5,999.5);


    int nevent = tree->GetEntries();
    for (int k =30; k <500; k++)
    {
      if (k%10 == 0) std::cout << k << std::endl;
      double counterdo = 0;
      double counterdoseed = 0;
      double counterglo = 0;
      double countergen = 0;
      double counternop = 0;
      double counternopseed = 0;

      for (int i = 0; i < nevent;i++)
      {

	tree->GetEvent(i);
	//	  for (int  j = 0; j < l1pt->size(); j++)
	if(donutpt->size()>jetnum && donutpt->at(jetnum)>k)
	{
	  counterdo+=1;
	} 
	if(donutseedpt->size()>jetnum && donutseedpt->at(jetnum)>k)
	{
	  counterdoseed+=1;
	} 
	if(globalpt->size()>jetnum && globalpt->at(jetnum)>k)
	{
	  counterglo+=1;
	} 
	if(nopuspt->size()>jetnum && nopuspt->at(jetnum)>k)
	{
	  counternop+=1;
	} 
	if(nopusseedpt->size()>jetnum && nopusseedpt->at(jetnum)>k)
	{
	  counternopseed+=1;
	} 
      }
      globaljetpt->SetBinContent(k,counterglo/nevent);//counter/nevent);
      donutjetpt->SetBinContent(k,counterdo/nevent);//counter/nevent);
      donutseedjetpt->SetBinContent(k,counterdoseed/nevent);//counter/nevent);
      nopusjetpt->SetBinContent(k,counternop/nevent);//counter/nevent);
      nopusseedjetpt->SetBinContent(k,counternopseed/nevent);//counter/nevent);
    }
    globaljetpt->SetLineColor(4);
    donutjetpt->SetLineColor(2);
    nopusjetpt->SetLineColor(1);
    nopusseedjetpt->SetLineStyle(2);

    globaljetpt->Write();
    donutjetpt->Write();
    donutseedjetpt->Write();
    nopusjetpt->Write();
    nopusseedjetpt->Write();
    f_out->Close();
}
