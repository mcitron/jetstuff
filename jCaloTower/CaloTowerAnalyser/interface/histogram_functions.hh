#ifndef HISTOGRAM_FUNCTIONS_HH
#define HISTOGRAM_FUNCTIONS_HH

void CaloTowerAnalyser::compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName, bool isgct) {
  std::map<TString,int> ptBins_;
  ptBins_["pt_0to20"] = 20;
  ptBins_["pt_20to40"] = 40;
  ptBins_["pt_40to60"] = 60;
  ptBins_["pt_60to80"] = 80;
  ptBins_["pt_80to100"] = 100;
  ptBins_["pt_100to120"] = 120;
  ptBins_["pt_above120"] = 999;

  std::map<TString,int> HTBins;
  HTBins["HT_100"] = 100;
  HTBins["HT_200"] = 200;

  std::map<TString,int> ETBins;
  ETBins["ET_100"] = 100;
  ETBins["ET_200"] = 200;

  std::map<TString,int> MHTBins;
  MHTBins["MHT_100"] = 100;
  MHTBins["MHT_200"] = 200;

  std::map<TString,int> METBins;
  METBins["MET_100"] = 100;
  METBins["MET_200"] = 200;

  std::map<TString,int> etaBins_;
  etaBins_["eta_-28to-14"] = -14;
  etaBins_["eta_-14to0"] = 0;
  etaBins_["eta_0to14"] = 14;
  etaBins_["eta_14to28"] = 28;

  std::map<TString,std::pair<int,int>> etaCalibBins_;
  etaCalibBins_["iEta_-28_to_-22"] = std::make_pair(-28,-21);
  etaCalibBins_["iEta_-21_to_-15"] = std::make_pair(-21,-14);
  etaCalibBins_["iEta_-14_to_-08"] = std::make_pair(-14,-7);
  etaCalibBins_["iEta_-07_to_-1"] = std::make_pair(-7,0);
  etaCalibBins_["iEta_01_to_07"] = std::make_pair(0,8);
  etaCalibBins_["iEta_08_to_14"] = std::make_pair(8,15);
  etaCalibBins_["iEta_15_to_21"] = std::make_pair(15,22);
  etaCalibBins_["iEta_21_to_28"] = std::make_pair(22,29);

  std::map<TString,int> ptCut;
  ptCut["pt20"] = 20;
  ptCut["pt40"] = 40;
  ptCut["pt60"] = 60;
  ptCut["pt80"] = 80;
  edm::Service<TFileService> fs;
  TFileDirectory dir = fs->mkdir(folderName);

  TFileDirectory otherdir=dir.mkdir("other");
  //check initialised via means of mMapping, e.g.
  if(col1_jet1_eta.count(folderName) == 0) { col1_jet1_eta[folderName] = otherdir.make<TH1D>("col1_jet1_eta",";eta jet1;",57, -0.5, 56.5); }
  if(col1_jet2_eta.count(folderName) == 0) { col1_jet2_eta[folderName] = otherdir.make<TH1D>("col1_jet2_eta",";eta jet2;",57, -0.5, 56.5); }
  if(col1_jet3_eta.count(folderName) == 0) { col1_jet3_eta[folderName] = otherdir.make<TH1D>("col1_jet3_eta",";eta jet3;",57, -0.5, 56.5); }
  if(col1_jet4_eta.count(folderName) == 0) { col1_jet4_eta[folderName] = otherdir.make<TH1D>("col1_jet4_eta",";eta jet4;",57, -0.5, 56.5); }

  if(col2_jet1_eta.count(folderName) == 0) { col2_jet1_eta[folderName] = otherdir.make<TH1D>("col2_jet1_eta",";eta jet1;",57, -0.5, 56.5); }
  if(col2_jet2_eta.count(folderName) == 0) { col2_jet2_eta[folderName] = otherdir.make<TH1D>("col2_jet2_eta",";eta jet2;",57, -0.5, 56.5); }
  if(col2_jet3_eta.count(folderName) == 0) { col2_jet3_eta[folderName] = otherdir.make<TH1D>("col2_jet3_eta",";eta jet3;",57, -0.5, 56.5); }
  if(col2_jet4_eta.count(folderName) == 0) { col2_jet4_eta[folderName] = otherdir.make<TH1D>("col2_jet4_eta",";eta jet4;",57, -0.5, 56.5); }

  if(col1_jet1_pt.count(folderName) == 0) { col1_jet1_pt[folderName] = otherdir.make<TH1D>("col1_jet1_pt",";p_{T} jet1;",1000, -0.5, 999.5); }
  if(col1_jet2_pt.count(folderName) == 0) { col1_jet2_pt[folderName] = otherdir.make<TH1D>("col1_jet2_pt",";p_{T} jet2;",1000, -0.5, 999.5); }
  if(col1_jet3_pt.count(folderName) == 0) { col1_jet3_pt[folderName] = otherdir.make<TH1D>("col1_jet3_pt",";p_{T} jet3;",1000, -0.5, 999.5); }
  if(col1_jet4_pt.count(folderName) == 0) { col1_jet4_pt[folderName] = otherdir.make<TH1D>("col1_jet4_pt",";p_{T} jet4;",1000, -0.5, 999.5); }
  if(col1_jet5_pt.count(folderName) == 0) { col1_jet5_pt[folderName] = otherdir.make<TH1D>("col1_jet5_pt",";p_{T} jet5;",1000, -0.5, 999.5); }
  if(col1_jet6_pt.count(folderName) == 0) { col1_jet6_pt[folderName] = otherdir.make<TH1D>("col1_jet6_pt",";p_{T} jet6;",1000, -0.5, 999.5); }
  if(col1_jet7_pt.count(folderName) == 0) { col1_jet7_pt[folderName] = otherdir.make<TH1D>("col1_jet7_pt",";p_{T} jet7;",1000, -0.5, 999.5); }
  if(col1_jet8_pt.count(folderName) == 0) { col1_jet8_pt[folderName] = otherdir.make<TH1D>("col1_jet8_pt",";p_{T} jet8;",1000, -0.5, 999.5); }
  if(col1_jet9_pt.count(folderName) == 0) { col1_jet9_pt[folderName] = otherdir.make<TH1D>("col1_jet9_pt",";p_{T} jet9;",1000, -0.5, 999.5); }
  if(col1_jet10_pt.count(folderName) == 0) { col1_jet10_pt[folderName] = otherdir.make<TH1D>("col1_jet10_pt",";p_{T} jet10;",1000, -0.5, 999.5); }

  if(col1_alljet_pt_NPV.count(folderName) == 0) { col1_alljet_pt_NPV[folderName] = otherdir.make<TH2D>("col1_alljet_pt_NPV",";NPV;p_{T} jet1",100,-0.5,99.5,1000, -0.5, 999.5); }
  if(col1_jet1_pt_NPV.count(folderName) == 0) { col1_jet1_pt_NPV[folderName] = otherdir.make<TH2D>("col1_jet1_pt_NPV",";NPV;p_{T} jet1",100,-0.5,99.5,1000, -0.5, 999.5); }
  if(col1_jet2_pt_NPV.count(folderName) == 0) { col1_jet2_pt_NPV[folderName] = otherdir.make<TH2D>("col1_jet2_pt_NPV",";NPV;p_{T} jet2",100,-0.5,99.5,1000, -0.5, 999.5); }
  if(col1_jet3_pt_NPV.count(folderName) == 0) { col1_jet3_pt_NPV[folderName] = otherdir.make<TH2D>("col1_jet3_pt_NPV",";NPV;p_{T} jet3",100,-0.5,99.5,1000, -0.5, 999.5); }
  if(col1_jet4_pt_NPV.count(folderName) == 0) { col1_jet4_pt_NPV[folderName] = otherdir.make<TH2D>("col1_jet4_pt_NPV",";NPV;p_{T} jet4",100,-0.5,99.5,1000, -0.5, 999.5); }

  if(col2_jet1_pt.count(folderName) == 0) { col2_jet1_pt[folderName] = otherdir.make<TH1D>("col2_jet1_pt",";p_{T} jet1;",1000, -0.5, 999.5); }
  if(col2_jet2_pt.count(folderName) == 0) { col2_jet2_pt[folderName] = otherdir.make<TH1D>("col2_jet2_pt",";p_{T} jet2;",1000, -0.5, 999.5); }
  if(col2_jet3_pt.count(folderName) == 0) { col2_jet3_pt[folderName] = otherdir.make<TH1D>("col2_jet3_pt",";p_{T} jet3;",1000, -0.5, 999.5); }
  if(col2_jet4_pt.count(folderName) == 0) { col2_jet4_pt[folderName] = otherdir.make<TH1D>("col2_jet4_pt",";p_{T} jet4;",1000, -0.5, 999.5); }
  if(col2_jet5_pt.count(folderName) == 0) { col2_jet5_pt[folderName] = otherdir.make<TH1D>("col2_jet5_pt",";p_{T} jet5;",1000, -0.5, 999.5); }
  if(col2_jet6_pt.count(folderName) == 0) { col2_jet6_pt[folderName] = otherdir.make<TH1D>("col2_jet6_pt",";p_{T} jet6;",1000, -0.5, 999.5); }
  if(col2_jet7_pt.count(folderName) == 0) { col2_jet7_pt[folderName] = otherdir.make<TH1D>("col2_jet7_pt",";p_{T} jet7;",1000, -0.5, 999.5); }
  if(col2_jet8_pt.count(folderName) == 0) { col2_jet8_pt[folderName] = otherdir.make<TH1D>("col2_jet8_pt",";p_{T} jet8;",1000, -0.5, 999.5); }
  if(col2_jet9_pt.count(folderName) == 0) { col2_jet9_pt[folderName] = otherdir.make<TH1D>("col2_jet9_pt",";p_{T} jet9;",1000, -0.5, 999.5); }
  if(col2_jet10_pt.count(folderName) == 0) { col2_jet10_pt[folderName] = otherdir.make<TH1D>("col2_jet10_pt",";p_{T} jet10;",1000, -0.5, 999.5); }

  if(col1_alljet_pt.count(folderName) == 0) { col1_alljet_pt[folderName] = otherdir.make<TH1D>("col1_alljet_pt",";p_{T} all jets;",1000, -0.5, 999.5); }
  if(col2_alljet_pt.count(folderName) == 0) { col2_alljet_pt[folderName] = otherdir.make<TH1D>("col2_alljet_pt",";p_{T} all jets;",1000, -0.5, 999.5); }
  if(col1_alljet_eta.count(folderName) == 0) { col1_alljet_eta[folderName] = otherdir.make<TH1D>("col1_alljet_eta",";eta all jets;",57, -0.5, 56.5); }
  if(col2_alljet_eta.count(folderName) == 0) { col2_alljet_eta[folderName] = otherdir.make<TH1D>("col2_alljet_eta",";eta all jets;",57, -0.5, 56.5);}

  if(col2_matched_algo1_alljet_pt.count(folderName) == 0) { col2_matched_algo1_alljet_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo1_alljet_pt",";p_{T} all jets matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo1_alljet_eta.count(folderName) == 0) { col2_matched_algo1_alljet_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo1_alljet_eta",";eta all jets matched;",57, -0.5, 56.5); }
  if(col2_matched_algo1_ptcorr.count(folderName) == 0) { col2_matched_algo1_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo1_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

  if(col2_matched_algo1_ptres_profile.count(folderName) == 0) { col2_matched_algo1_ptres_profile[folderName] = otherdir.make<TProfile>("col2_matched_algo1_ptres_profile", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5); }
  if(col2_matched_algo1_ptres.count(folderName) == 0) { col2_matched_algo1_ptres[folderName] = otherdir.make<TH2D>("col2_matched_algo1_ptres", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }

  if(col2_matched_algo1_ptratio.count(folderName) == 0) { col2_matched_algo1_ptratio[folderName] = otherdir.make<TH2D>("col2_matched_algo1_ptratio", ";col2 p_{T}; (col1) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }
  if(col2_matched_algo1_jet1_pt.count(folderName) == 0) { col2_matched_algo1_jet1_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet1_pt",";p_{T} jet1 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet2_pt.count(folderName) == 0) { col2_matched_algo1_jet2_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet2_pt",";p_{T} jet2 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet3_pt.count(folderName) == 0) { col2_matched_algo1_jet3_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet3_pt",";p_{T} jet3 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet4_pt.count(folderName) == 0) { col2_matched_algo1_jet4_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet4_pt",";p_{T} jet4 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet1_eta.count(folderName) == 0) { col2_matched_algo1_jet1_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet1_eta",";eta jet1 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo1_jet2_eta.count(folderName) == 0) { col2_matched_algo1_jet2_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet2_eta",";eta jet2 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo1_jet3_eta.count(folderName) == 0) { col2_matched_algo1_jet3_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet3_eta",";eta jet3 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo1_jet4_eta.count(folderName) == 0) { col2_matched_algo1_jet4_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo1_jet4_eta",";eta jet4 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo1_jet1_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet1_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo1_jet1_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet2_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet2_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo1_jet2_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet3_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet3_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo1_jet3_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo1_jet4_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet4_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo1_jet4_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo2_alljet_pt.count(folderName) == 0) { col2_matched_algo2_alljet_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo2_alljet_pt",";p_{T} all jets matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo2_alljet_eta.count(folderName) == 0) { col2_matched_algo2_alljet_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo2_alljet_eta",";eta all jets matched;",57, -0.5, 56.5); }
  if(col2_matched_algo2_ptcorr.count(folderName) == 0) { col2_matched_algo2_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo2_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

  if(col2_matched_algo2_ptres_profile.count(folderName) == 0) { col2_matched_algo2_ptres_profile[folderName] = otherdir.make<TProfile>("col2_matched_algo2_ptres_profile", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5); }
  if(col2_matched_algo2_ptres.count(folderName) == 0) { col2_matched_algo2_ptres[folderName] = otherdir.make<TH2D>("col2_matched_algo2_ptres", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }

  if(col2_matched_algo2_ptratio.count(folderName) == 0) { col2_matched_algo2_ptratio[folderName] = otherdir.make<TH2D>("col2_matched_algo2_ptratio", ";col2 p_{T}; (col1) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }
  if(col2_matched_algo2_jet1_pt.count(folderName) == 0) { col2_matched_algo2_jet1_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet1_pt",";p_{T} jet1 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet2_pt.count(folderName) == 0) { col2_matched_algo2_jet2_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet2_pt",";p_{T} jet2 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet3_pt.count(folderName) == 0) { col2_matched_algo2_jet3_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet3_pt",";p_{T} jet3 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet4_pt.count(folderName) == 0) { col2_matched_algo2_jet4_pt[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet4_pt",";p_{T} jet4 matched;",1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet1_eta.count(folderName) == 0) { col2_matched_algo2_jet1_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet1_eta",";eta jet1 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo2_jet2_eta.count(folderName) == 0) { col2_matched_algo2_jet2_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet2_eta",";eta jet2 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo2_jet3_eta.count(folderName) == 0) { col2_matched_algo2_jet3_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet3_eta",";eta jet3 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo2_jet4_eta.count(folderName) == 0) { col2_matched_algo2_jet4_eta[folderName] = otherdir.make<TH1D>("col2_matched_algo2_jet4_eta",";eta jet4 matched;",57, -0.5, 56.5); }
  if(col2_matched_algo2_jet1_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet1_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo2_jet1_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet2_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet2_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo2_jet2_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet3_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet3_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo2_jet3_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_algo2_jet4_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet4_ptcorr[folderName] = otherdir.make<TH2D>("col2_matched_algo2_jet4_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_saved_algo2.count(folderName) == 0) { col2_saved_algo2[folderName] = otherdir.make<TH2D>("col2_saved_algo2",";col2 p_{T};Max Matched p_{T};", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }


  //New plots
  //Loop over Pt bins
  if(pMade.count(folderName) ==0)
  {
    //SEED
    TFileDirectory seeddir=dir.mkdir("seed");
    col1_seed_alljet[folderName] = seeddir.make<TH1D>("col1_seed_alljet",";col1_seed p_{T};",500,-0.5,499.5);
    col1_seed_jet1[folderName] = seeddir.make<TH1D>("col1_seed_jet1",";col1_seed p_{T};",500,-0.5,499.5);
    col1_seed_jet2[folderName] = seeddir.make<TH1D>("col1_seed_jet2",";col1_seed p_{T};",500,-0.5,499.5);
    col1_seed_jet3[folderName] = seeddir.make<TH1D>("col1_seed_jet3",";col1_seed p_{T};",500,-0.5,499.5);
    col1_seed_jet4[folderName] = seeddir.make<TH1D>("col1_seed_jet4",";col1_seed p_{T};",500,-0.5,499.5);
    col1_NPV_seed_alljet[folderName] = seeddir.make<TH2D>("col1_NPV_seed_alljet",";NPV;col1_seed p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_seed_jet1[folderName] = seeddir.make<TH2D>("col1_NPV_seed_jet1",";NPV;col1_seed p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_seed_jet2[folderName] = seeddir.make<TH2D>("col1_NPV_seed_jet2",";NPV;col1_seed p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_seed_jet3[folderName] = seeddir.make<TH2D>("col1_NPV_seed_jet3",";NPV;col1_seed p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_seed_jet4[folderName] = seeddir.make<TH2D>("col1_NPV_seed_jet4",";NPV;col1_seed p_{T}",100,-0.5,99.5,500,-0.5,499.5);

    TFileDirectory superseeddir=dir.mkdir("superseed");
    col1_rings_0_1_alljet[folderName] = superseeddir.make<TH1D>("col1_rings_0_1_alljet",";col1_rings_0_1 p_{T};",500,-0.5,499.5);
    col1_rings_0_1_jet1[folderName] = superseeddir.make<TH1D>("col1_rings_0_1_jet1",";col1_rings_0_1 p_{T};",500,-0.5,499.5);
    col1_rings_0_1_jet2[folderName] = superseeddir.make<TH1D>("col1_rings_0_1_jet2",";col1_rings_0_1 p_{T};",500,-0.5,499.5);
    col1_rings_0_1_jet3[folderName] = superseeddir.make<TH1D>("col1_rings_0_1_jet3",";col1_rings_0_1 p_{T};",500,-0.5,499.5);
    col1_rings_0_1_jet4[folderName] = superseeddir.make<TH1D>("col1_rings_0_1_jet4",";col1_rings_0_1 p_{T};",500,-0.5,499.5);

    col1_NPV_rings_0_1_alljet[folderName] = superseeddir.make<TH2D>("col1_NPV_rings_0_1_alljet",";NPV;col1_rings_0_1 p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_jet1[folderName] = superseeddir.make<TH2D>("col1_NPV_rings_0_1_jet1",";NPV;col1_rings_0_1 p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_jet2[folderName] = superseeddir.make<TH2D>("col1_NPV_rings_0_1_jet2",";NPV;col1_rings_0_1 p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_jet3[folderName] = superseeddir.make<TH2D>("col1_NPV_rings_0_1_jet3",";NPV;col1_rings_0_1 p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_jet4[folderName] = superseeddir.make<TH2D>("col1_NPV_rings_0_1_jet4",";NPV;col1_rings_0_1 p_{T}",100,-0.5,99.5,500,-0.5,499.5);

    TFileDirectory superseednormdir=dir.mkdir("superseednorm");
    col1_rings_0_1_norm_alljet[folderName] = superseednormdir.make<TH1D>("col1_rings_0_1_norm_alljet",";col1_rings_0_1_norm p_{T};",500,-0.5,499.5);
    col1_rings_0_1_norm_jet1[folderName] = superseednormdir.make<TH1D>("col1_rings_0_1_norm_jet1",";col1_rings_0_1_norm p_{T};",500,-0.5,499.5);
    col1_rings_0_1_norm_jet2[folderName] = superseednormdir.make<TH1D>("col1_rings_0_1_norm_jet2",";col1_rings_0_1_norm p_{T};",500,-0.5,499.5);
    col1_rings_0_1_norm_jet3[folderName] = superseednormdir.make<TH1D>("col1_rings_0_1_norm_jet3",";col1_rings_0_1_norm p_{T};",500,-0.5,499.5);
    col1_rings_0_1_norm_jet4[folderName] = superseednormdir.make<TH1D>("col1_rings_0_1_norm_jet4",";col1_rings_0_1_norm p_{T};",500,-0.5,499.5);

    col1_NPV_rings_0_1_norm_alljet[folderName] = superseednormdir.make<TH2D>("col1_NPV_rings_0_1_norm_alljet",";NPV;col1_rings_0_1_norm p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_norm_jet1[folderName] = superseednormdir.make<TH2D>("col1_NPV_rings_0_1_norm_jet1",";NPV;col1_rings_0_1_norm p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_norm_jet2[folderName] = superseednormdir.make<TH2D>("col1_NPV_rings_0_1_norm_jet2",";NPV;col1_rings_0_1_norm p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_norm_jet3[folderName] = superseednormdir.make<TH2D>("col1_NPV_rings_0_1_norm_jet3",";NPV;col1_rings_0_1_norm p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    col1_NPV_rings_0_1_norm_jet4[folderName] = superseednormdir.make<TH2D>("col1_NPV_rings_0_1_norm_jet4",";NPV;col1_rings_0_1_norm p_{T}",100,-0.5,99.5,500,-0.5,499.5);
    //ESums (no cut)
    TFileDirectory esumsdir=dir.mkdir("esums");
    col2_ht[folderName]  = esumsdir.make<TH1D>("col2_ht",";col2 H_{T};",3000,-0.5,2999.5);
    col1_ht[folderName] = esumsdir.make<TH1D>("col1_ht",";col2 H_{T};",3000,-0.5,2999.5);

    col2_mht_x[folderName]  = esumsdir.make<TH1D>("col2_mht_x",";col2 MH_{T};",1000,-500.5,499.5);
    col1_mht_x[folderName]  = esumsdir.make<TH1D>("col1_mht_x",";col2 MH_{T};",1000,-500.5,499.5);

    col2_mht_y[folderName]  = esumsdir.make<TH1D>("col2_mht_y",";col2 MH_{T};",1000,-500.5,499.5);
    col1_mht_y[folderName]  = esumsdir.make<TH1D>("col1_mht_y",";col2 MH_{T};",1000,-500.5,499.5);

    col2_mht[folderName]  = esumsdir.make<TH1D>("col2_mht",";col2 mh_{t};",3000,-0.5,2999.5);
    col1_mht[folderName]  = esumsdir.make<TH1D>("col1_mht",";col2 mh_{t};",3000,-0.5,2999.5);

    ht_resolution[folderName]  = esumsdir.make<TH2D>("ht_resolution",";(col1_ht-col2_ht)/col2_ht;col2_ht",200,-10.5,9.5,3000,-0.5,2999.5);
    mht_x_resolution[folderName]  = esumsdir.make<TH2D>("mht_x_resolution",";(col1_mht_x-col2_mht_x)/col2_mht_x;col2_mht_x",200,-10.5,9.5,3000,-0.5,2999.5);
    mht_y_resolution[folderName]  = esumsdir.make<TH2D>("mht_y_resolution",";(col1_mht_y-col2_mht_y)/col2_mht_y;col2_mht_y",200,-10.5,9.5,3000,-0.5,2999.5);
    mht_resolution[folderName]  = esumsdir.make<TH2D>("mht_resolution",";(col1_mht-col2_mht)/col2_mht;col2_mht",200,-10.5,9.5,3000,-0.5,2999.5);

    mht_ht_col2[folderName]=esumsdir.make<TH2D>("col2_mht_ht",";col2_ht;col2_mht/col2_ht",3000,-0.5,2999.5,200,-1.005,0.995);
    mht_ht_col1[folderName]=esumsdir.make<TH2D>("col1_mht_ht",";col1_ht;col1_mht/col1_ht",3000,-0.5,2999.5,200,-1.005,0.995);
    index_matched[folderName]=otherdir.make<TH2D>("index_matched",";col2_i;col1_i",100,-0.5,99.5,100,-0.5,99.5);


    for(auto iHTBins=HTBins.begin(); iHTBins!=HTBins.end(); iHTBins++){
      col2_ht_cut[folderName+iHTBins->first] = esumsdir.make<TH1D>("col2_ht_col1_cut_"+iHTBins->first,";col2 H_{T};",3000,-0.5,2999.5);
    }
    for(auto iMHTBins=MHTBins.begin(); iMHTBins!=MHTBins.end(); iMHTBins++){
      col2_mht_cut[folderName+iMHTBins->first] = esumsdir.make<TH1D>("col2_mht_col1_cut_"+iMHTBins->first,";col2 H_{T};",3000,-0.5,2999.5);
    }

    for(auto iETBins=ETBins.begin(); iETBins!=ETBins.end(); iETBins++){
      col1_et_cut[folderName+iETBins->first] = esumsdir.make<TH1D>("col1_et_cut_"+iETBins->first,";col1 H_{T};",3000,-0.5,2999.5);
    }
    for(auto iMETBins=METBins.begin(); iMETBins!=METBins.end(); iMETBins++){
      col1_met_cut[folderName+iMETBins->first] = esumsdir.make<TH1D>("col1_met_cut_"+iMETBins->first,";col1 H_{T};",3000,-0.5,2999.5);
    }


    //Calibration Plots
    TFileDirectory calibdir=dir.mkdir("calibration");

    //for(std::map<TString,std::pair<int,int> >::const_iterator etaBinIt=etaCalibBins_.begin(); etaBinIt!=etaCalibBins_.end(); etaBinIt++)
    for(auto etaBinIt=etaCalibBins_.begin(); etaBinIt!=etaCalibBins_.end(); etaBinIt++){

      col2_calib_ratio[TString(folderName)+etaBinIt->first]=calibdir.make<TH2D>("col2_calib_ratio_"+etaBinIt->first,";col2 p_{T};col1 p_{T}/col2 p_{T}",1000,-0.5,999.5,200,-10.05,10.95);
      col2_calib_ratio_profile[TString(folderName)+etaBinIt->first]=calibdir.make<TProfile>("col2_calib_ratio_profile_"+etaBinIt->first,";col2 p_{T};col1 p_{T}/col2 p_{T}",1000,-0.5,999.5);

      col2_calib_corr[TString(folderName)+etaBinIt->first]=calibdir.make<TH2D>("col2_calib_corr_"+etaBinIt->first,";col2 p_{T};col1 p_{T}",1000,-0.5,999.5,1000,-0.5,999.5);
      col2_calib_corr_profile[TString(folderName)+etaBinIt->first]=calibdir.make<TProfile>("col2_calib_corr_profile_"+etaBinIt->first,";col2 p_{T};col1 p_{T}",1000,-0.5,999.5);

    }
    for(auto ptCutIt=ptCut.begin(); ptCutIt != ptCut.end(); ptCutIt++)
      //for(std::map<TString,std::pair<int,int> >::const_iterator ptCutIt=ptCut.begin(); ptCutIt != ptCut.end(); ptCutIt++)
    {
      std::cout << TString(folderName)+ptCutIt->first << std::endl;
      col2_matched_algo1_alljet_cut[TString(folderName)+ptCutIt->first]=otherdir.make<TH1D>("col2_matched_algo1_alljet_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
      col2_matched_algo1_jet1_cut[TString(folderName)+ptCutIt->first]=otherdir.make<TH1D>("col2_matched_algo1_jet1_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
      col2_matched_algo1_jet2_cut[TString(folderName)+ptCutIt->first]=otherdir.make<TH1D>("col2_matched_algo1_jet2_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
      col2_matched_algo1_jet3_cut[TString(folderName)+ptCutIt->first]=otherdir.make<TH1D>("col2_matched_algo1_jet3_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
      col2_matched_algo1_jet4_cut[TString(folderName)+ptCutIt->first]=otherdir.make<TH1D>("col2_matched_algo1_jet4_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);

    }
    std::cout << folderName << std::endl;
    pMade[folderName] = true;
    for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

      TFileDirectory etadir = dir.mkdir(etaBinIt->first.Data());

      //Loop over Pt bins
      for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){

	TFileDirectory ptdir = etadir.mkdir(ptBinIt->first.Data());

	pt_ratio_nvts_algo1_alljet[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TH2D>("pt_ratio_nvts_algo1_alljet", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5, 600, -3.005, 2.995); 
	pt_ratio_nvts_algo1_alljet_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TProfile>("pt_ratio_nvts_algo1_alljet_profile", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5); 
	pt_ratio_nvts_algo1_jet1[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TH2D>("pt_ratio_nvts_algo1_jet1", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5, 600, -3.005, 2.995); 
	pt_ratio_nvts_algo1_jet1_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TProfile>("pt_ratio_nvts_algo1_jet1_profile", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5); 
	pt_ratio_nvts_algo1_jet2[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TH2D>("pt_ratio_nvts_algo1_jet2", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5, 600, -3.005, 2.995); 
	pt_ratio_nvts_algo1_jet2_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TProfile>("pt_ratio_nvts_algo1_jet2_profile", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5); 
	pt_ratio_nvts_algo1_jet3[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TH2D>("pt_ratio_nvts_algo1_jet3", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5, 600, -3.005, 2.995); 
	pt_ratio_nvts_algo1_jet3_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TProfile>("pt_ratio_nvts_algo1_jet3_profile", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5); 
	pt_ratio_nvts_algo1_jet4[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TH2D>("pt_ratio_nvts_algo1_jet4", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5, 600, -3.005, 2.995); 
	pt_ratio_nvts_algo1_jet4_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first] = ptdir.make<TProfile>("pt_ratio_nvts_algo1_jet4_profile", ";NPV;(col1 pTgen-pTL1)/pTgen", 100, -0.5, 99.5); 
      }
    }
  }
  double HTcol1=calculateHT(col1,20);
  double HTcol2=calculateHT(col2,20);

  double MHTcol1_x=calculateMHT(col1,20)[0];
  double MHTcol2_x=calculateMHT(col2,20)[0];

  double MHTcol1_y=calculateMHT(col1,20)[1];
  double MHTcol2_y=calculateMHT(col2,20)[1];

  double MHTcol1=calculateMHT(col1,20)[2];
  double MHTcol2=calculateMHT(col2,20)[2];

  col2_ht[folderName]->Fill(HTcol2);
  col1_ht[folderName]->Fill(HTcol1);

  col1_mht[folderName]->Fill(MHTcol2);
  col2_mht[folderName]->Fill(MHTcol1);

  col1_mht_x[folderName]->Fill(MHTcol2_x);
  col2_mht_x[folderName]->Fill(MHTcol1_x);

  col1_mht_y[folderName]->Fill(MHTcol2_y);
  col2_mht_y[folderName]->Fill(MHTcol1_y);

  if(HTcol2 != 0) ht_resolution[folderName]->Fill(HTcol1/HTcol2-1,HTcol2);
  if(MHTcol2_x != 0) mht_x_resolution[folderName]->Fill(MHTcol1_x/MHTcol2_x-1,MHTcol2_x);
  if(MHTcol2_y != 0) mht_y_resolution[folderName]->Fill(MHTcol1_y/MHTcol2_y-1,MHTcol2_y);
  if(MHTcol2 != 0) mht_resolution[folderName]->Fill(MHTcol1/MHTcol2-1,MHTcol2);

  if(MHTcol2 != 0) mht_ht_col2[folderName]->Fill(HTcol2,MHTcol2/HTcol2);
  if(MHTcol1 != 0) mht_ht_col1[folderName]->Fill(HTcol1,MHTcol1/HTcol1);

  for(auto iHTBins=HTBins.begin(); iHTBins!=HTBins.end(); iHTBins++){
    if(HTcol1 > iHTBins->second)
    {
      col2_ht_cut[folderName+iHTBins->first]->Fill(HTcol2);
    }
  }

  for(auto iMHTBins=MHTBins.begin(); iMHTBins!=MHTBins.end(); iMHTBins++){
    if(MHTcol1 > iMHTBins->second)
    {
      col2_mht_cut[folderName+iMHTBins->first]->Fill(MHTcol2);
    }
  }

  for(auto iETBins=ETBins.begin(); iETBins!=ETBins.end(); iETBins++){
    if(mET > iETBins->second)
    {
      col1_et_cut[folderName+iETBins->first]->Fill(HTcol1);
    }
  }

  for(auto iMETBins=METBins.begin(); iMETBins!=METBins.end(); iMETBins++){
    if(mMET[2] > iMETBins->second)
    {
      col1_met_cut[folderName+iMETBins->first]->Fill(MHTcol1);
    }
  }

  for(unsigned int i=0; i<col1.size(); i++) {
    col1_alljet_pt[folderName]->Fill(col1[i].pt());
    if (col1[i].ringSums().size()!=0) 
    {
      col1_seed_alljet[folderName]->Fill(col1[i].ringSums().at(0));
      col1_rings_0_1_alljet[folderName]->Fill(col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
      col1_NPV_rings_0_1_alljet[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1));

      col1_rings_0_1_norm_alljet[folderName]->Fill(col1[i].ringSums().at(0)+(col1[i].ringSums().at(1))/8.);
      col1_NPV_rings_0_1_norm_alljet[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1)/8.);

      col1_NPV_seed_alljet[folderName]->Fill(mNPV,col1[i].ringSums().at(0));
    }
    col1_alljet_pt_NPV[folderName]->Fill(mNPV,col1[i].pt());
    col1_alljet_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));
    if(i == 0) { col1_jet1_pt[folderName]->Fill(col1[i].pt()); col1_jet1_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet1_pt_NPV[folderName]->Fill(mNPV,col1[i].pt());
      if (col1[i].ringSums().size()!=0) 
      {
	col1_seed_jet1[folderName]->Fill(col1[i].ringSums().at(0)); 
	col1_rings_0_1_jet1[folderName]->Fill(col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_rings_0_1_jet1[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_seed_jet1[folderName]->Fill(mNPV,col1[i].ringSums().at(0));
	col1_rings_0_1_norm_jet1[folderName]->Fill(col1[i].ringSums().at(0)+(col1[i].ringSums().at(1))/8.);
	col1_NPV_rings_0_1_norm_jet1[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1)/8.);
      }
    }
    if(i == 1) { col1_jet2_pt[folderName]->Fill(col1[i].pt()); col1_jet2_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet2_pt_NPV[folderName]->Fill(mNPV,col1[i].pt());
      if (col1[i].ringSums().size()!=0) 
      {
	col1_seed_jet2[folderName]->Fill(col1[i].ringSums().at(0)); 
	col1_rings_0_1_jet2[folderName]->Fill(col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_rings_0_1_jet2[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_seed_jet2[folderName]->Fill(mNPV,col1[i].ringSums().at(0));
	col1_rings_0_1_norm_jet2[folderName]->Fill(col1[i].ringSums().at(0)+(col1[i].ringSums().at(1))/8.);
	col1_NPV_rings_0_1_norm_jet2[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1)/8.);
      } 
    }
    if(i == 2) { col1_jet3_pt[folderName]->Fill(col1[i].pt()); col1_jet3_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet3_pt_NPV[folderName]->Fill(mNPV,col1[i].pt());
      if (col1[i].ringSums().size()!=0)
      {
	col1_seed_jet3[folderName]->Fill(col1[i].ringSums().at(0)); 
	col1_rings_0_1_jet3[folderName]->Fill(col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_rings_0_1_jet3[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_seed_jet3[folderName]->Fill(mNPV,col1[i].ringSums().at(0));
	col1_rings_0_1_norm_jet3[folderName]->Fill(col1[i].ringSums().at(0)+(col1[i].ringSums().at(1))/8.);
	col1_NPV_rings_0_1_norm_jet3[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1)/8.);
      }
    }
    if(i == 3) { col1_jet4_pt[folderName]->Fill(col1[i].pt()); col1_jet4_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet4_pt_NPV[folderName]->Fill(mNPV,col1[i].pt());
      if (col1[i].ringSums().size()!=0) 
      {
	col1_seed_jet4[folderName]->Fill(col1[i].ringSums().at(0)); 
	col1_rings_0_1_jet4[folderName]->Fill(col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_rings_0_1_jet4[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1));
	col1_NPV_seed_jet4[folderName]->Fill(mNPV,col1[i].ringSums().at(0));
	col1_rings_0_1_norm_jet4[folderName]->Fill(col1[i].ringSums().at(0)+(col1[i].ringSums().at(1))/8.);
	col1_NPV_rings_0_1_norm_jet4[folderName]->Fill(mNPV,col1[i].ringSums().at(0)+col1[i].ringSums().at(1)/8.);
      } 
    }
    if(i == 4) col1_jet5_pt[folderName]->Fill(col1[i].pt());
    if(i == 5) col1_jet6_pt[folderName]->Fill(col1[i].pt());
    if(i == 6) col1_jet7_pt[folderName]->Fill(col1[i].pt());
    if(i == 7) col1_jet8_pt[folderName]->Fill(col1[i].pt());
    if(i == 8) col1_jet9_pt[folderName]->Fill(col1[i].pt());
    if(i == 9) col1_jet10_pt[folderName]->Fill(col1[i].pt());
  }
  for(unsigned int i=0; i<col2.size(); i++) {
    col2_alljet_pt[folderName]->Fill(col2[i].pt());
    col2_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
    if(i == 0) { col2_jet1_pt[folderName]->Fill(col2[i].pt()); col2_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 1) { col2_jet2_pt[folderName]->Fill(col2[i].pt()); col2_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 2) { col2_jet3_pt[folderName]->Fill(col2[i].pt()); col2_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 3) { col2_jet4_pt[folderName]->Fill(col2[i].pt()); col2_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 4) { col2_jet5_pt[folderName]->Fill(col2[i].pt()); }
    if(i == 5) { col2_jet6_pt[folderName]->Fill(col2[i].pt()); }
    if(i == 6) { col2_jet7_pt[folderName]->Fill(col2[i].pt()); }
    if(i == 7) { col2_jet8_pt[folderName]->Fill(col2[i].pt()); }
    if(i == 8) { col2_jet9_pt[folderName]->Fill(col2[i].pt()); }
    if(i == 9) { col2_jet10_pt[folderName]->Fill(col2[i].pt()); }
  }
  pairs = (isgct) ? make_gct_pairs(col1,col2) : make_pairs(col1, col2);
  std::vector<int> col2_matched_index = analyse_pairs_local(pairs, col2.size(), 33);
  //std::vector<int> col1_matched_index_local = analyse_pairs_global(pairs, col2.size(), 25);

  for(unsigned int i=0; i<col2_matched_index.size(); i++) {
    //std::cout << "ak4genjetp with index " << i << " is matched to ak4ttjet with index " << ak4tt_matched_index[i] << std::endl;
    if(col2_matched_index[i] != -1) {
      index_matched[folderName]->Fill(i,col2_matched_index[i]);
      //New plots
      for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

	for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){
	  if (col2[i].pt() > ptBinIt->second && col2[i].iEta()< etaBinIt->second && col2[i].iEta() > etaBinIt->second-14)
	  {
	    pt_ratio_nvts_algo1_alljet[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	    pt_ratio_nvts_algo1_alljet_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	  }
	}
      }
      //Turn On Plots
      for(std::map<TString,int>::const_iterator ptCutIt=ptCut.begin(); ptCutIt!=ptCut.end(); ptCutIt++)
      {
	if (col1[col2_matched_index[i]].pt() > ptCutIt->second)
	{
	  col2_matched_algo1_alljet_cut[TString(folderName)+ptCutIt->first]->Fill(col2[i].pt());
	}
      }
      //std::cout << col2[i].pt() << std::endl;
      col2_matched_algo1_alljet_pt[folderName]->Fill(col2[i].pt());
      col2_matched_algo1_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
      col2_matched_algo1_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt());
      if(col2[i].pt() > 0.0) {
	col2_matched_algo1_ptres[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index[i]].pt() / col2[i].pt()) - 1.0 );
	col2_matched_algo1_ptres_profile[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index[i]].pt() / col2[i].pt()) - 1.0 );
	col2_matched_algo1_ptratio[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index[i]].pt() / col2[i].pt()));
      }
      //CALIB plots
      if(i < 4)
	for(auto etaBinIt=etaCalibBins_.begin(); etaBinIt!=etaCalibBins_.end(); etaBinIt++){
	  if (col2[i].iEta() >= etaBinIt->second.first && col2[i].iEta() < etaBinIt->second.second)
	  {
	    col2_calib_ratio[TString(folderName)+etaBinIt->first]->Fill(col2[i].pt(),col1[col2_matched_index[i]].pt()/col2[i].pt());
	    col2_calib_ratio_profile[TString(folderName)+etaBinIt->first]->Fill(col2[i].pt(),col1[col2_matched_index[i]].pt()/col2[i].pt());
	    col2_calib_corr[TString(folderName)+etaBinIt->first]->Fill(col2[i].pt(),col1[col2_matched_index[i]].pt());
	    col2_calib_corr_profile[TString(folderName)+etaBinIt->first]->Fill(col2[i].pt(),col1[col2_matched_index[i]].pt());
	  }
	}

      if(i == 0) { col2_matched_algo1_jet1_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo1_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); 
	col2_matched_algo1_jet1_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); 


	for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

	  for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){
	    if (col2[i].pt() > ptBinIt->second && col2[i].iEta()< etaBinIt->second && col2[i].iEta() > etaBinIt->second-14)
	    {
	      pt_ratio_nvts_algo1_jet1[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	      pt_ratio_nvts_algo1_jet1_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	    }
	  }
	}

	//Turn On Plots
	for(std::map<TString,int>::const_iterator ptCutIt=ptCut.begin(); ptCutIt!=ptCut.end(); ptCutIt++)
	{
	  if (col1[col2_matched_index[i]].pt() > ptCutIt->second)
	  {
	    col2_matched_algo1_jet1_cut[TString(folderName)+ptCutIt->first]->Fill(col2[i].pt());
	  }
	}

      }
      if(i == 1) { col2_matched_algo1_jet2_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo1_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo1_jet2_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); 

	for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

	  for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){
	    if (col2[i].pt() > ptBinIt->second && col2[i].iEta()< etaBinIt->second && col2[i].iEta() > etaBinIt->second-14)
	    {
	      pt_ratio_nvts_algo1_jet2[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	      pt_ratio_nvts_algo1_jet2_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	    }
	  }
	}
	//Turn On Plots
	for(std::map<TString,int>::const_iterator ptCutIt=ptCut.begin(); ptCutIt!=ptCut.end(); ptCutIt++)
	{
	  if (col1[col2_matched_index[i]].pt() > ptCutIt->second)
	  {
	    col2_matched_algo1_jet2_cut[TString(folderName)+ptCutIt->first]->Fill(col2[i].pt());
	  }
	}


      }

      //Turn On Plots

      if(i == 2) { col2_matched_algo1_jet3_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo1_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo1_jet3_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt());

	for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

	  for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){
	    if (col2[i].pt() > ptBinIt->second && col2[i].iEta()< etaBinIt->second && col2[i].iEta() > etaBinIt->second-14)
	    {
	      pt_ratio_nvts_algo1_jet3[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	      pt_ratio_nvts_algo1_jet3_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	    }
	  }
	}
	//Turn On Plots
	for(std::map<TString,int>::const_iterator ptCutIt=ptCut.begin(); ptCutIt!=ptCut.end(); ptCutIt++)
	{
	  if (col1[col2_matched_index[i]].pt() > ptCutIt->second)
	  {
	    col2_matched_algo1_jet3_cut[TString(folderName)+ptCutIt->first]->Fill(col2[i].pt());
	  }
	}



      }

      if(i == 3) { col2_matched_algo1_jet4_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo1_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo1_jet4_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); 

	for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

	  for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){
	    if (col2[i].pt() > ptBinIt->second && col2[i].iEta()< etaBinIt->second && col2[i].iEta() > etaBinIt->second-14)
	    {
	      pt_ratio_nvts_algo1_jet4[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	      pt_ratio_nvts_algo1_jet4_profile[TString(folderName)+ptBinIt->first+"_"+etaBinIt->first]->Fill(mNPV,(col2[i].pt()-col1[col2_matched_index[i]].pt())/col2[i].pt());
	    }
	  }
	}
	//Turn On Plots
	for(std::map<TString,int>::const_iterator ptCutIt=ptCut.begin(); ptCutIt!=ptCut.end(); ptCutIt++)
	{
	  if (col1[col2_matched_index[i]].pt() > ptCutIt->second)
	  {
	    col2_matched_algo1_jet4_cut[TString(folderName)+ptCutIt->first]->Fill(col2[i].pt());
	  }
	}


      }
    } 
  }
  //ALGO 2
  //pairs = (isgct) ? make_gct_pairs(col2,col1) : make_pairs(col2, col1);
  //std::cout << non0 << "\t";
  //Turn On Plots
  col2_matched_index = analyse_pairs_global(pairs, col2.size(), 33);

  for(unsigned int i=0; i<col2_matched_index.size(); i++) {
    //std::cout << "ak4genjetp with index " << i << " is matched to ak4ttjet with index " << ak4tt_matched_index[i] << std::endl;
    if(col2_matched_index[i] != -1) {
      col2_matched_algo2_alljet_pt[folderName]->Fill(col2[i].pt());
      col2_matched_algo2_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
      col2_matched_algo2_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt());
      if(col2[i].pt() > 0.0) {
	col2_matched_algo2_ptres[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index[i]].pt() / col2[i].pt()) - 1.0 );
	col2_matched_algo2_ptres_profile[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index[i]].pt() / col2[i].pt()) - 1.0 );
	col2_matched_algo2_ptratio[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index[i]].pt() / col2[i].pt()));
      }

      if(i == 0) { col2_matched_algo2_jet1_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo2_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo2_jet1_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); }
      if(i == 1) { col2_matched_algo2_jet2_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo2_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo2_jet2_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); }
      if(i == 2) { col2_matched_algo2_jet3_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo2_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo2_jet3_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); }
      if(i == 3) { col2_matched_algo2_jet4_pt[folderName]->Fill(col2[i].pt()); col2_matched_algo2_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_algo2_jet4_ptcorr[folderName]->Fill(col1[col2_matched_index[i]].pt(), col2[i].pt()); }

    } 
    //if (col1[col2_matched_index[i]].pt()/col2[i].pt() > 900. && folderName =="5400_donut_gen" ) {this->mPrintMe = true; std::cout << mPrintMe << std::endl;}
    //Turn On Plots
    /*      else
	    {
	    if (col2[i].pt()>200.) {
	    int max=0;
	    for (unsigned int j =0; j <col1.size();j++)
	    {
	    if (max < col1[j].pt()) max = col1[j].pt();
	    }
	    col2_saved_algo2[folderName]->Fill(col2[i].pt(),max);
	    if (max < col2[i].pt()) this->mPrintMe=true; std::cout << "PRINT "<<col2[i].pt() <<std::endl; 
    //	    break;
    }
    }
    */ 
  }

  return;

}

void CaloTowerAnalyser::bookPusHists(TString folderName){

  edm::Service<TFileService> fs;
  TFileDirectory dir = fs->mkdir(folderName.Data());

  for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){

    pusHists1d_[*gVIt] = dir.make<TH1F>(*gVIt,";"+*gVIt,80,-0.5,79.5);

    for(std::vector<TString>::const_iterator gVIt2=gVIt+1; gVIt2!=globalPusVars_.end(); gVIt2++){

      pusHists2d_[*gVIt+"_"+*gVIt2] = dir.make<TH2F>(*gVIt+"_"+*gVIt2,";"+*gVIt+";"+*gVIt2,40,-0.5,79.5,40,-0.5,79.5);
      pusProfile_[*gVIt+"_"+*gVIt2] = dir.make<TProfile>(*gVIt+"_"+*gVIt2+"_profile",";"+*gVIt+";"+*gVIt2,40,-0.5,79.5,-0.5,79.5);

    }
  }
  //Loop over sizes
  for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){

    TFileDirectory subdir = dir.mkdir(((TString)"Size_"+*l1SIt).Data());

    //Loop over the different strip permutations
    for(std::vector<TString>::const_iterator l1VIt=l1PusVars_.begin(); l1VIt!=l1PusVars_.end(); l1VIt++){

      pusHists1d_[*l1SIt+"_"+*l1VIt] = subdir.make<TH1F>(*l1SIt+"_"+*l1VIt,"Size "+*l1SIt+" energy "+*l1VIt, 60,-0.5,59.5);

      //Loop over the global 2D histograms
      for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){

	TFileDirectory subsubdir = subdir.mkdir(gVIt->Data());
	pusHists2d_[*gVIt+"_"+*l1SIt+"_"+*l1VIt] = subsubdir.make<TH2F>(*gVIt+"_"+*l1SIt+"_"+*l1VIt,";"+*gVIt+";"+*l1SIt+"_"+*l1VIt,
	    40,-0.5,79.5,60,-0.5,59.5);
	pusProfile_[*gVIt+"_"+*l1SIt+"_"+*l1VIt] = subsubdir.make<TProfile>(*gVIt+"_"+*l1SIt+"_"+*l1VIt+"_profile",";"+*gVIt+";"+*l1SIt+"_"+*l1VIt,
	    40,-0.5,79.5,-0.5,39.5);

      }
    }

    //Make histograms binned in pt and eta
    //Loop over eta bins
    for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){

      TFileDirectory etadir = subdir.mkdir(etaBinIt->first.Data());

      //Loop over Pt bins
      for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){

	TFileDirectory ptdir = etadir.mkdir(ptBinIt->first.Data());

	//Loop over the different strip permutations
	for(std::vector<TString>::const_iterator l1VIt=l1PusVars_.begin(); l1VIt!=l1PusVars_.end(); l1VIt++){

	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_"+*l1VIt] = 
	    ptdir.make<TH1F>(*l1SIt+"_"+*l1VIt,"Size "+*l1SIt+" energy "+*l1VIt, 60,-0.5,59.5);

	  //Loop over the global 2D histograms
	  for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){

	    TFileDirectory subptdir = ptdir.mkdir(gVIt->Data());
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_"+*l1VIt] = 
	      subptdir.make<TH2F>(*gVIt+"_"+*l1SIt+"_"+*l1VIt,";"+*gVIt+";"+*l1SIt+"_"+*l1VIt,40,-0.5,79.5,60,-0.5,59.5);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_"+*l1VIt] = 
	      subptdir.make<TProfile>(*gVIt+"_"+*l1SIt+"_"+*l1VIt+"_profile",";"+*gVIt+";"+*l1SIt+"_"+*l1VIt,40,-0.5,79.5,-0.5,39.5);

	  }
	}

      }
    }

  }

  //Make histograms in bins of Nint
  TFileDirectory dir2 = fs->mkdir("ring_comparisons");

  for(std::map<TString,int>::const_iterator nintBinIt=nintBins_.begin(); nintBinIt!=nintBins_.end(); nintBinIt++){
    TFileDirectory nintDir = dir2.mkdir((TString("4isolated/")+nintBinIt->first).Data());
    pusHists2d_[nintBinIt->first+"_ring0_total_4iso"] = nintDir.make<TH2F>("ring0_total",";ring0 (L1 units) (L1 units);total (L1 units)",100,0.,100.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring1_total_4iso"] = nintDir.make<TH2F>("ring1_total",";ring1 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring2_total_4iso"] = nintDir.make<TH2F>("ring2_total",";ring2 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring3_total_4iso"] = nintDir.make<TH2F>("ring3_total",";ring3 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring4_total_4iso"] = nintDir.make<TH2F>("ring4_total",";ring4 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring5_total_4iso"] = nintDir.make<TH2F>("ring5_total",";ring5 (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_donut_total_4iso"] = nintDir.make<TH2F>("donut_total",";donut (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_subtract_total_4iso"] = nintDir.make<TH2F>("subtract_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom3_total_4iso"] = nintDir.make<TH2F>("out1_bottom3_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom2_total_4iso"] = nintDir.make<TH2F>("out1_bottom2_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    nintDir = dir2.mkdir((TString("4/")+nintBinIt->first).Data());
    pusHists2d_[nintBinIt->first+"_ring0_total_4"] = nintDir.make<TH2F>("ring0_total",";ring0 (L1 units);total (L1 units)",100,0.,100.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring1_total_4"] = nintDir.make<TH2F>("ring1_total",";ring1 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring2_total_4"] = nintDir.make<TH2F>("ring2_total",";ring2 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring3_total_4"] = nintDir.make<TH2F>("ring3_total",";ring3 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring4_total_4"] = nintDir.make<TH2F>("ring4_total",";ring4 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring5_total_4"] = nintDir.make<TH2F>("ring5_total",";ring5 (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_donut_total_4"] = nintDir.make<TH2F>("donut_total",";donut (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_subtract_total_4"] = nintDir.make<TH2F>("subtract_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom3_total_4"] = nintDir.make<TH2F>("out1_bottom3_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom2_total_4"] = nintDir.make<TH2F>("out1_bottom2_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    nintDir = dir2.mkdir((TString("3isolated/")+nintBinIt->first).Data());
    pusHists2d_[nintBinIt->first+"_ring0_total_3iso"] = nintDir.make<TH2F>("ring0_total",";ring0 (L1 units);total (L1 units)",100,0.,100.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring1_total_3iso"] = nintDir.make<TH2F>("ring1_total",";ring1 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring2_total_3iso"] = nintDir.make<TH2F>("ring2_total",";ring2 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring3_total_3iso"] = nintDir.make<TH2F>("ring3_total",";ring3 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring4_total_3iso"] = nintDir.make<TH2F>("ring4_total",";ring4 (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_donut_total_3iso"] = nintDir.make<TH2F>("donut_total",";donut (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_subtract_total_3iso"] = nintDir.make<TH2F>("subtract_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom3_total_3iso"] = nintDir.make<TH2F>("out1_bottom3_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom2_total_3iso"] = nintDir.make<TH2F>("out1_bottom2_total",";donut (L1 units);total (L1 units)",200,0.,800.,200,0.,1000.);
    nintDir = dir2.mkdir((TString("3/")+nintBinIt->first).Data());
    pusHists2d_[nintBinIt->first+"_ring0_total_3"] = nintDir.make<TH2F>("ring0_total",";ring0 (L1 units);total (L1 units)",100,0.,100.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring1_total_3"] = nintDir.make<TH2F>("ring1_total",";ring1 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring2_total_3"] = nintDir.make<TH2F>("ring2_total",";ring2 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring3_total_3"] = nintDir.make<TH2F>("ring3_total",";ring3 (L1 units);total (L1 units)",200,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_ring4_total_3"] = nintDir.make<TH2F>("ring4_total",";ring4 (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_donut_total_3"] = nintDir.make<TH2F>("donut_total",";donut (L1 units);total (L1 units)",400,0.,50.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_subtract_total_3"] = nintDir.make<TH2F>("subtract_total",";donut (L1 units);total (L1 units)",200,0.,200.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom3_total_3"] = nintDir.make<TH2F>("out1_bottom3_total",";donut (L1 units);total (L1 units)",200,0.,200.,200,0.,1000.);
    pusHists2d_[nintBinIt->first+"_out1_bottom2_total_3"] = nintDir.make<TH2F>("out1_bottom2_total",";donut (L1 units);total (L1 units)",200,0.,200.,200,0.,1000.);
  }

}

void CaloTowerAnalyser::printOneEvent(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const std::vector<jJet> & L1jets, const std::vector<fastjet::PseudoJet> & ak4ttjets, const reco::GenJetCollection * ak4genjets, std::vector<fastjet::PseudoJet> & ak4genjetsp) {

  edm::Service<TFileService> fs;

  std::string folderName = "Event_";
  std::stringstream caseNumber;
  caseNumber << mEventNumber;
  folderName.append(caseNumber.str());
  TFileDirectory dir = fs->mkdir(folderName);

  TH2I * ttow = dir.make<TH2I>("ttow",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2I * ttowE = dir.make<TH2I>("ttowE",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2I * ttowH = dir.make<TH2I>("ttowH",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2I * L1jet = dir.make<TH2I>("L1jet",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2D * ak4tt = dir.make<TH2D>("ak4tt",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2D * ak4gen = dir.make<TH2D>("ak4gen",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2D * ak4genp = dir.make<TH2D>("ak4genp",";eta;phi",57, -28.5, 28.5, 72, 0.5, 72.5);

  for(l1slhc::L1CaloTowerCollection::const_iterator j=triggertowers->begin(); j!=triggertowers->end(); j++) {
    if ( abs((*j).iEta()) > 28 ) {
      continue;
    }
    ttow->Fill((*j).iEta(), (*j).iPhi(), ((*j).E() + (*j).H()));
    ttowE->Fill((*j).iEta(), (*j).iPhi(), (*j).E());
    ttowH->Fill((*j).iEta(), (*j).iPhi(), (*j).H());
  }

  for(unsigned int i=0; i<L1jets.size(); i++) {
    L1jet->Fill(L1jets[i].iEta(), L1jets[i].iPhi(), L1jets[i].pt());
  }
  for(unsigned int i=0; i < ak4genjets->size(); i++) {
    ak4gen->Fill(g.iEta((*ak4genjets)[i].eta()), g.iPhi((*ak4genjets)[i].phi()), (*ak4genjets)[i].pt());
    //std::cout << "(" << (*ak4genjets)[i].eta() << ", " << (*ak4genjets)[i].phi() << ") (" << g.iEta((*ak4genjets)[i].eta()) << ", " << g.iPhi((*ak4genjets)[i].phi()) << ")" << std::endl;
  }


  for(unsigned int i=0; i< ak4ttjets.size(); i++) {
    ak4tt->Fill(g.iEta(ak4ttjets[i].eta()), g.iPhi(ak4ttjets[i].phi()), ak4ttjets[i].pt());
  }

  for(unsigned int i=0; i < ak4genjetsp.size(); i++) {
    //std::cout << "(" << ak4genjetsp[i].eta() << " --> " << g.iEta(ak4genjetsp[i].eta()) << ")" << std::endl;
    ak4genp->Fill(g.iEta((ak4genjetsp)[i].eta()), g.iPhi((ak4genjetsp)[i].phi()), (ak4genjetsp)[i].pt());
  }  

  return;

}

void CaloTowerAnalyser::printOneEvent(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const std::map <TString,std::vector<jJet> > & L1jets, const std::map<TString,std::vector<fastjet::PseudoJet>> & ak4jets,std::map<TString,const reco::GenJetCollection *> ak4genjets) {

  edm::Service<TFileService> fs;

  std::string folderName = "Event_";
  std::stringstream caseNumber;
  caseNumber << mEventNumber;
  folderName.append(caseNumber.str());
  TFileDirectory dir = fs->mkdir(folderName);
  TH2I * ttow = dir.make<TH2I>("ttow",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2I * ttowE = dir.make<TH2I>("ttowE",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  TH2I * ttowH = dir.make<TH2I>("ttowH",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
  //TH2D * ak4tt = dir.make<TH2D>("ak4tt",";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);

  std::vector<TH2I*> hjJets;
  std::vector<TH2D*> hak4jets;

  for(l1slhc::L1CaloTowerCollection::const_iterator j=triggertowers->begin(); j!=triggertowers->end(); j++) {
    if ( abs((*j).iEta()) > 28 ) {
      continue;
    }
    ttow->Fill((*j).iEta(), (*j).iPhi(), ((*j).E() + (*j).H()));
    ttowE->Fill((*j).iEta(), (*j).iPhi(), (*j).E());
    ttowH->Fill((*j).iEta(), (*j).iPhi(), (*j).H());
  }
  for (std::map<TString,std::vector<jJet>>::const_iterator j = L1jets.begin();j != L1jets.end();j++)
  {
    TH2I* hjJet = dir.make<TH2I>((*j).first,";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
    for(std::vector<jJet>::const_iterator jet=(*j).second.begin(); jet!=(*j).second.end(); jet++) {
      hjJet->Fill(jet->iEta(), jet->iPhi(), jet->pt());
    }
    hjJets.push_back(hjJet);
  } 

  for (std::map<TString,std::vector<fastjet::PseudoJet>>::const_iterator j = ak4jets.begin();j != ak4jets.end();j++)
  {
    TH2D* hak4jet = dir.make<TH2D>((*j).first,";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
    for(std::vector<fastjet::PseudoJet>::const_iterator jet=(*j).second.begin(); jet!=(*j).second.end(); jet++) {
      hak4jet->Fill(g.iEta(jet->eta()), g.iPhi(jet->phi()), jet->pt());
    }
    hak4jets.push_back(hak4jet);
  }
  for (std::map<TString,const reco::GenJetCollection *>::const_iterator j = ak4genjets.begin();j != ak4genjets.end();j++)
  {
    const reco::GenJetCollection * ak4genjets = j->second;
    TH2D * ak4gen = dir.make<TH2D>(j->first,";eta;phi", 57,-28.5,28.5, 72, 0.5, 72.5);
    for(unsigned int i=0; i < ak4genjets->size(); i++) {
      ak4gen->Fill(g.iEta((*ak4genjets)[i].eta()), g.iPhi((*ak4genjets)[i].phi()), (*ak4genjets)[i].pt());
    }
  }
  return;
}

void CaloTowerAnalyser::makePusHists(const std::vector< std::vector<int> >& myarray,const std::vector<jJet>& L1_4300_jJet ,const std::vector<jJet>& L1_5450_jJet ){

  std::map<TString, std::vector<jJet> > L1_jJet_map;

  for(std::vector<jJet>::const_iterator L1_5450=L1_5450_jJet.begin(); L1_5450!=L1_5450_jJet.end(); L1_5450++){
    for(std::map<TString,int>::const_iterator nintIt = nintBins_.begin(); nintIt!=nintBins_.end(); nintIt++){
      if(mNPV<nintIt->second && mNPV>nintIt->second-5){

	//Check only isolated jets
	jJet thisjet = *L1_5450;
	//Get bottom 3 of the outer ring
	double out1_bottom3 = thisjet.getOuterStrips()[0].first+thisjet.getOuterStrips()[1].first+thisjet.getOuterStrips()[2].first;
	double out1_bottom2 = thisjet.getOuterStrips()[0].first+thisjet.getOuterStrips()[1].first;

	pusHists2d_[nintIt->first+"_ring0_total_4"]->Fill((double)L1_5450->ringSums().at(0)/L1_5450->ringAreas().at(0),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring1_total_4"]->Fill((double)L1_5450->ringSums().at(1)/L1_5450->ringAreas().at(1),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring2_total_4"]->Fill((double)L1_5450->ringSums().at(2)/L1_5450->ringAreas().at(2),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring3_total_4"]->Fill((double)L1_5450->ringSums().at(3)/L1_5450->ringAreas().at(3),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring4_total_4"]->Fill((double)L1_5450->ringSums().at(4)/L1_5450->ringAreas().at(4),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring5_total_4"]->Fill((double)L1_5450->getOuterSum()/L1_5450->ringAreas().at(5),L1_5450->pt());
	pusHists2d_[nintIt->first+"_donut_total_4"]->Fill((double)thisjet.PUE()/18.0,L1_5450->pt());
	pusHists2d_[nintIt->first+"_subtract_total_4"]->Fill((double)thisjet.PUE()*4.5,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom3_total_4"]->Fill((double)out1_bottom3*3.0,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom2_total_4"]->Fill((double)out1_bottom2*4.5,L1_5450->pt());
	if( !(thisjet.isolatedJet(L1_5450_jJet,81))) continue;
	pusHists2d_[nintIt->first+"_ring0_total_4iso"]->Fill((double)L1_5450->ringSums().at(0)/L1_5450->ringAreas().at(0),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring1_total_4iso"]->Fill((double)L1_5450->ringSums().at(1)/L1_5450->ringAreas().at(1),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring2_total_4iso"]->Fill((double)L1_5450->ringSums().at(2)/L1_5450->ringAreas().at(2),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring3_total_4iso"]->Fill((double)L1_5450->ringSums().at(3)/L1_5450->ringAreas().at(3),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring4_total_4iso"]->Fill((double)L1_5450->ringSums().at(4)/L1_5450->ringAreas().at(4),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring5_total_4iso"]->Fill((double)L1_5450->getOuterSum()/L1_5450->ringAreas().at(5),L1_5450->pt());
	pusHists2d_[nintIt->first+"_donut_total_4iso"]->Fill((double)thisjet.PUE()/18.0,L1_5450->pt());
	pusHists2d_[nintIt->first+"_subtract_total_4iso"]->Fill((double)thisjet.PUE()*4.5,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom3_total_4iso"]->Fill((double)out1_bottom3*3.0,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom2_total_4iso"]->Fill((double)out1_bottom2*4.5,L1_5450->pt());
      }
    }
  }

  for(std::vector<jJet>::const_iterator L1_5450=L1_4300_jJet.begin(); L1_5450!=L1_4300_jJet.end(); L1_5450++){
    for(std::map<TString,int>::const_iterator nintIt = nintBins_.begin(); nintIt!=nintBins_.end(); nintIt++){
      if(mNPV<nintIt->second && mNPV>nintIt->second-5){

	//Check only isolated jets
	jJet thisjet = *L1_5450;
	double out1_bottom3 = thisjet.getOuterStrips()[0].first+thisjet.getOuterStrips()[1].first+thisjet.getOuterStrips()[2].first;
	double out1_bottom2 = thisjet.getOuterStrips()[0].first+thisjet.getOuterStrips()[1].first;

	pusHists2d_[nintIt->first+"_ring0_total_3"]->Fill((double)L1_5450->ringSums().at(0)/L1_5450->ringAreas().at(0),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring1_total_3"]->Fill((double)L1_5450->ringSums().at(1)/L1_5450->ringAreas().at(1),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring2_total_3"]->Fill((double)L1_5450->ringSums().at(2)/L1_5450->ringAreas().at(2),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring3_total_3"]->Fill((double)L1_5450->ringSums().at(3)/L1_5450->ringAreas().at(3),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring4_total_3"]->Fill((double)L1_5450->getOuterSum()/L1_5450->ringAreas().at(4),L1_5450->pt());
	pusHists2d_[nintIt->first+"_donut_total_3"]->Fill((double)thisjet.PUE()/14.0,L1_5450->pt());
	pusHists2d_[nintIt->first+"_subtract_total_3"]->Fill((double)thisjet.PUE()*3.5,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom3_total_3"]->Fill((double)out1_bottom3*2.333,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom2_total_3"]->Fill((double)out1_bottom2*3.5,L1_5450->pt());
	if( !(thisjet.isolatedJet(L1_5450_jJet,81))) continue;
	pusHists2d_[nintIt->first+"_ring0_total_3iso"]->Fill((double)L1_5450->ringSums().at(0)/L1_5450->ringAreas().at(0),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring1_total_3iso"]->Fill((double)L1_5450->ringSums().at(1)/L1_5450->ringAreas().at(1),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring2_total_3iso"]->Fill((double)L1_5450->ringSums().at(2)/L1_5450->ringAreas().at(2),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring3_total_3iso"]->Fill((double)L1_5450->ringSums().at(3)/L1_5450->ringAreas().at(3),L1_5450->pt());
	pusHists2d_[nintIt->first+"_ring4_total_3iso"]->Fill((double)L1_5450->getOuterSum()/L1_5450->ringAreas().at(4),L1_5450->pt());
	pusHists2d_[nintIt->first+"_donut_total_3iso"]->Fill((double)thisjet.PUE()/14.0,L1_5450->pt());
	pusHists2d_[nintIt->first+"_subtract_total_3iso"]->Fill((double)thisjet.PUE()*3.5,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom3_total_3iso"]->Fill((double)out1_bottom3*2.333,L1_5450->pt());
	pusHists2d_[nintIt->first+"_out1_bottom2_total_3iso"]->Fill((double)out1_bottom2*3.5,L1_5450->pt());
      }
    }
  }

  //Fill the map with the sizes
  for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){
    L1_jJet_map[*l1SIt+"_out1"] = getL1Jets(myarray, atoi(l1SIt->Data())+1,atoi(l1SIt->Data()),5,0);
    L1_jJet_map[*l1SIt+"_out2"] = getL1Jets(myarray, atoi(l1SIt->Data())+2,atoi(l1SIt->Data()),5,0);
  }


  std::map<TString,double> globalPusVarsMap;
  globalPusVarsMap["nint"] = mNPV;


  //Fill the global hists
  for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){
    pusHists1d_[*gVIt]->Fill(globalPusVarsMap[*gVIt]);
    for(std::vector<TString>::const_iterator gVIt2=gVIt+1; gVIt2!=globalPusVars_.end(); gVIt2++){
      pusHists2d_[*gVIt+"_"+*gVIt2]->Fill(globalPusVarsMap[*gVIt],globalPusVarsMap[*gVIt2]);
      pusProfile_[*gVIt+"_"+*gVIt2]->Fill(globalPusVarsMap[*gVIt],globalPusVarsMap[*gVIt2]);
    }
  }

  //Only do it for well separated jets?
  bool isolatedOnly = false;
  double dR2Max=49.0;

  //Fill the all jets hists
  for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){
    for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out1"].size(); i++){
      if(isolatedOnly){
	if( !(L1_jJet_map[*l1SIt+"_out1"][i].isolatedJet(L1_jJet_map[*l1SIt+"_out1"],dR2Max))) continue;
      }
      pusHists1d_[*l1SIt+"_strip1"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0].first);
      pusHists1d_[*l1SIt+"_strip2"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1].first);
      pusHists1d_[*l1SIt+"_strip3"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2].first);
      pusHists1d_[*l1SIt+"_strip4"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3].first);
      pusHists1d_[*l1SIt+"_out1_middle2"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].PUE());
      //Fill the different binned hists
      for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){
	if(L1_jJet_map[*l1SIt+"_out1"][i].iEta() > etaBinIt->second || L1_jJet_map[*l1SIt+"_out1"][i].iEta() < etaBinIt->second-14)
	  continue; 
	for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){

	  if(L1_jJet_map[*l1SIt+"_out1"][i].pt() > ptBinIt->second || L1_jJet_map[*l1SIt+"_out1"][i].pt() < ptBinIt->second-20)
	    continue; 

	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip1"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip2"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip3"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip4"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_out1_middle2"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].PUE());


	}
      }

    }
    for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out2"].size(); i++){
      if(isolatedOnly){
	if( !(L1_jJet_map[*l1SIt+"_out2"][i].isolatedJet(L1_jJet_map[*l1SIt+"_out2"],dR2Max))) continue;
      }
      pusHists1d_[*l1SIt+"_strip5"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0].first);
      pusHists1d_[*l1SIt+"_strip6"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1].first);
      pusHists1d_[*l1SIt+"_strip7"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2].first);
      pusHists1d_[*l1SIt+"_strip8"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3].first);
      pusHists1d_[*l1SIt+"_out2_middle2"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].PUE());

      //Fill the different binned hists
      for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){
	if(L1_jJet_map[*l1SIt+"_out2"][i].iEta() > etaBinIt->second || L1_jJet_map[*l1SIt+"_out2"][i].iEta() < etaBinIt->second-14)
	  continue; 
	for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){

	  if(L1_jJet_map[*l1SIt+"_out2"][i].pt() > ptBinIt->second || L1_jJet_map[*l1SIt+"_out2"][i].pt() < ptBinIt->second-20)
	    continue; 

	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip5"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip6"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip7"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_strip8"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3].first);
	  pusHists1d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*l1SIt+"_out2_middle2"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].PUE());


	}
      }
    }
  }

  //Fill the 2d histograms for all hists
  for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){
    for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){

      for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out1"].size(); i++){
	if(isolatedOnly){
	  if( !(L1_jJet_map[*l1SIt+"_out1"][i].isolatedJet(L1_jJet_map[*l1SIt+"_out1"],dR2Max))) continue;
	}
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip1"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip3"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip4"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_out1_middle2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].PUE());

	pusProfile_[*gVIt+"_"+*l1SIt+"_strip1"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_strip2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_strip3"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_strip4"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_out1_middle2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].PUE());

	for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){
	  if(L1_jJet_map[*l1SIt+"_out1"][i].iEta() > etaBinIt->second || L1_jJet_map[*l1SIt+"_out1"][i].iEta() < etaBinIt->second-14)
	    continue; 
	  for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){

	    if(L1_jJet_map[*l1SIt+"_out1"][i].pt() > ptBinIt->second || L1_jJet_map[*l1SIt+"_out1"][i].pt() < ptBinIt->second-20)
	      continue; 

	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip1"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip2"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip3"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip4"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_out1_middle2"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].PUE());

	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip1"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip2"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip3"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip4"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_out1_middle2"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].PUE());

	  }
	}


      }
      for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out2"].size(); i++){
	if(isolatedOnly){
	  if( !(L1_jJet_map[*l1SIt+"_out2"][i].isolatedJet(L1_jJet_map[*l1SIt+"_out2"],dR2Max))) continue;
	}
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip5"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip6"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip7"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_strip8"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3].first);
	pusHists2d_[*gVIt+"_"+*l1SIt+"_out2_middle2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].PUE());

	pusProfile_[*gVIt+"_"+*l1SIt+"_strip5"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_strip6"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_strip7"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_strip8"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3].first);
	pusProfile_[*gVIt+"_"+*l1SIt+"_out2_middle2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].PUE());

	for(std::map<TString,int>::const_iterator etaBinIt=etaBins_.begin(); etaBinIt!=etaBins_.end(); etaBinIt++){
	  if(L1_jJet_map[*l1SIt+"_out1"][i].iEta() > etaBinIt->second || L1_jJet_map[*l1SIt+"_out1"][i].iEta() < etaBinIt->second-14)
	    continue; 
	  for(std::map<TString,int>::const_iterator ptBinIt=ptBins_.begin(); ptBinIt!=ptBins_.end(); ptBinIt++){

	    if(L1_jJet_map[*l1SIt+"_out1"][i].pt() > ptBinIt->second || L1_jJet_map[*l1SIt+"_out1"][i].pt() < ptBinIt->second-20)
	      continue; 

	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip5"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip6"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip7"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip8"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3].first);
	    pusHists2d_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_out2_middle2"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].PUE());

	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip5"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip6"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip7"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_strip8"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3].first);
	    pusProfile_[etaBinIt->first+"_"+ptBinIt->first+"_"+*gVIt+"_"+*l1SIt+"_out2_middle2"]->Fill(
		globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].PUE());

	  }
	}


      }
    }
  }
}

#endif
