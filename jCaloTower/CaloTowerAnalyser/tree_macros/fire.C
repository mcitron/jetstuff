int N_50NS_BUNCHES=1368;
int N_25NS_BUNCHES=2508;
int LHC_FREQUENCY=11246;

int ZB_XSECTION=LHC_FREQUENCY*N_50NS_BUNCHES;
void rates(){
TFile * f_ttbar= new TFile("neutrino-output-2014-06-22.root");
TFile * f_out= new TFile("./rateTest.root","recreate");
TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree;6");
std::vector<TString> jetType;
jetType.push_back("5400_calib_nopus");
jetType.push_back("5450_calib_nopus");
jetType.push_back("5450_calib_donut");
jetType.push_back("5400_calib_donut");
jetType.push_back("5400_calib_global");
jetType.push_back("gct_calib_gen");
TString bins = "(1000,0,1000)";

  for (iType = jetType.begin();iType != jetType.end(); iType++)
  {

    TCut matchedcut = "jetMatchedPt_"+*iType+"["+*iNum+"]!=-1";


    tree_ttbar->Draw("jetPt_"+*iType+"["+*iNum+"]>>"+*iType+"_"+*iNum+bins,"");
    TH1F *test = (TH1F*)gPad->GetPrimitive(*iType+"_"+*iNum);
    test->Write();
    test->SetName(*iType+"_"+*iNum+"_"+"Rate");

    TH1F* cumuplot = makeCumu(test,overallNorm);
    cumuplot->Write();
  }
f_out->Close();
return;
}
