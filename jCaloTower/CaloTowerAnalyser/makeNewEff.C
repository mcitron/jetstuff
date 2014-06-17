void makeNewEff()
{
  TFile * f = new TFile("global_PUS_TEST.root");
  TFile * f_out = new TFile("ttbar_rate.root","recreate");
  TTree * tree = (TTree *) f->Get("demo/L1Tree"); 
  int mNPV;
  f_out->cd();

  std::vector<TString> PUSregime;
  //PUSregime.push_back("5400_calib_global");
  // PUSregime.push_back("5400_calib_nopus");
  // PUSregime.push_back("5450_calib_nopus");
  //PUSregime.push_back("5450_calib_donut");

  //tree->SetBranchAddress("mNPV",&mNPV);
  std::vector<float> * allgenpt; 
  std::vector<float> * donutpt; 
  std::vector<float> * globalpt; 
  std::vector<float> * donutmatchedpt; 
  std::vector<float> * globalmatchedpt; 
  std::vector<float> * genpt; 
  tree->SetBranchAddress("jetPt_ak4_gen",&allgenpt);
  tree->SetBranchAddress("jetPt_5400_calib_global",&globalpt);
  tree->SetBranchAddress("jetMatchedPt_5400_calib_global",&globalmatchedpt);
  tree->SetBranchAddress("jetPt_5450_calib_donut",&donutpt);
  tree->SetBranchAddress("jetMatchedPt_5450_calib_donut",&donutmatchedpt);

  TH1D * genjetpt = new TH1D ("genjetpt_eff",";pt;",1000,-0.5,999.5);
  TH1D * donutjetpt = new TH1D ("donutjetpt_eff",";pt;",1000,-0.5,999.5);
  TH1D * globaljetpt = new TH1D ("globaljetpt_eff",";pt;",1000,-0.5,999.5);


    int nevent = tree->GetEntries();
    for (int k =30; k <300; k++)
    {
      double counterdo = 0;
      double counterglo = 0;
      double countergen = 0;
      double counterdogen = 0;
      double counterglogen = 0;

      for (int i = 0; i < nevent;i++)
      {

	tree->GetEvent(i);
	//	  for (int  j = 0; j < l1pt->size(); j++)
	if(donutpt->size()>3 && donutmatchedpt->at(3) > 50)
	{
	  counterdogen +=1;
	  if(donutpt->at(3) > k)
	  {
	    counterdo+=1;
	  }
	} 
	if(globalpt->size()>3 &&  globalmatchedpt->at(3) > 50)
	{
	  counterglogen +=1;
	  if(globalpt->at(3) > k)
	  {
	    counterglo+=1;
	  }
	} /*
	if(allgenpt->size()>3 && allgenpt->at(3)>k )
	{
	  countergen+=1;
	}*/ 
      }
      donutjetpt->SetBinContent(k,counterdo/counterdogen);//counter/nevent);
      globaljetpt->SetBinContent(k,counterglo/counterglogen);//counter/nevent);
      //donutjetpt->SetBinContent(k,counterdo*5/nevent);//counter/nevent);
    }
    //genjetpt->SetLineColor(1);
    globaljetpt->SetLineColor(4);
    donutjetpt->SetLineColor(2);

    //genjetpt->Draw();
    globaljetpt->Write();
    donutjetpt->Write();
    f_out->Close();
}
/*
*//*
     if(donutpt->size()>3 && donutpt->at(3)>k && allgenpt->size()>3 && allgenpt->at(3)>k )
     {
     counterdo+=1;
     } 
     if(globalpt->size()>3 && globalpt->at(3)>k && allgenpt->size()>3 && allgenpt->at(3)>k )
     {
     counterglo+=1;
     } 
     if(allgenpt->size()>3 && allgenpt->at(3)>k )
     {
     countergen+=1;
     } */
