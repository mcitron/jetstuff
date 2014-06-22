#ifndef HISTOGRAM_FUNCTIONS_HH
#define HISTOGRAM_FUNCTIONS_HH

void CaloTowerAnalyser::MakeJetTree(const std::vector<jJet> & col1, const std::vector<jJet> & col2, TString folderName, bool isgct) {
if (col1.size()!=0)
{
  if(!pMade[folderName+"_jet"])
  {
    std::cout << folderName+"_jet" <<std::endl;
    jetPt_[folderName+"_jet"] = new std::vector<Float_t>();
    jetArea_[folderName+"_jet"] = new std::vector<Float_t>();
    jetRms_[folderName+"_jet"] = new std::vector<Float_t>();
    jetPhi_[folderName+"_jet"] = new std::vector<Float_t>();
    jetEta_[folderName+"_jet"] = new std::vector<Float_t>();
    jetDonut_[folderName+"_jet"] = new std::vector<Float_t>();
    jetMatchedPt_[folderName+"_jet"] = new std::vector<Float_t>();
    jetMinDR_[folderName+"_jet"] = new std::vector<Float_t>();
    tree->Branch("jetPt_"+TString(folderName), "std::vector<float>", &jetPt_[folderName+"_jet"]);
    tree->Branch("jetArea_"+TString(folderName), "std::vector<float>", &jetArea_[folderName+"_jet"]);
    tree->Branch("jetRms_"+TString(folderName), "std::vector<float>", &jetRms_[folderName+"_jet"]);
    tree->Branch("jetPhi_"+TString(folderName), "std::vector<float>", &jetPhi_[folderName+"_jet"]);
    tree->Branch("jetEta_"+TString(folderName), "std::vector<float>", &jetEta_[folderName+"_jet"]);
    tree->Branch("jetDonut_"+TString(folderName), "std::vector<float>", &jetDonut_[folderName+"_jet"]);
    tree->Branch("jetMatchedPt_"+TString(folderName), "std::vector<float>", &jetMatchedPt_[folderName+"_jet"]);
    tree->Branch("jetMinDR_"+TString(folderName), "std::vector<float>", &jetMinDR_[folderName+"_jet"]);
    pMade[folderName+"_jet"]=true;
    for (unsigned int i = 0; i  != col1.at(0).getOuterStrips().size(); i++)
    {
      std::string s = std::to_string(i);
      jetOuterStripsArea_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      jetOuterStripsEnergy_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      tree->Branch("jetOuterStripsEnergy_"+s+"_"+TString(folderName), "std::vector<float>", &jetOuterStripsEnergy_[folderName+"_jet_"+s]);
      tree->Branch("jetOuterStripsArea_"+s+"_"+TString(folderName), "std::vector<float>", &jetOuterStripsArea_[folderName+"_jet_"+s]);
    } 
    for (unsigned int i = 0; i  != col1.at(0).ringSums().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsArea_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      jetRingSumsEnergy_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      jetRingSumsHighest_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      tree->Branch("jetRingSumsEnergy_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsEnergy_[folderName+"_jet_"+s]);
      tree->Branch("jetRingSumsHighest_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsHighest_[folderName+"_jet_"+s]);
      tree->Branch("jetRingSumsArea_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsArea_[folderName+"_jet_"+s]);
    } 
  }
  std::vector<jJet> test = col1;
  pairs = (isgct) ? make_gct_pairs(col2,col1) : make_pairs(col2, col1);
  std::vector<int> col1_matched_index_algo1 = analyse_pairs_local(pairs, col1.size(), 33);
  //std::cout << col1_matched_index_algo1.at(0) << std::endl;
  jetPt_[folderName+"_jet"]->clear();
  jetArea_[folderName+"_jet"]->clear();
  jetRms_[folderName+"_jet"]->clear();
  jetPhi_[folderName+"_jet"]->clear();
  jetEta_[folderName+"_jet"]->clear();
  jetDonut_[folderName+"_jet"]->clear();
  jetMatchedPt_[folderName+"_jet"]->clear();
  jetMinDR_[folderName+"_jet"]->clear();

  for (unsigned int i = 0; i  != col1.at(0).getOuterStrips().size(); i++)
  {
    std::string s = std::to_string(i);
    jetOuterStripsEnergy_[folderName+"_jet_"+s]->clear();
    jetOuterStripsArea_[folderName+"_jet_"+s]->clear();
  }
  for (unsigned int i = 0; i  != col1.at(0).ringSums().size(); i++)
  {
    std::string s = std::to_string(i);
    jetRingSumsEnergy_[folderName+"_jet_"+s]->clear();
    jetRingSumsHighest_[folderName+"_jet_"+s]->clear();
    jetRingSumsArea_[folderName+"_jet_"+s]->clear();
  }
  //  std::vector <Float_t> * jetPhi_[folderName+"_jet"] = new std::vector<Float_t>();
  //  std::vector <Float_t> *  jetEta_[folderName+"_jet"] = new std::vector<Float_t>();
  int i=0;
  for (auto jet = col1.begin(); jet != col1.end(); jet++)
  {
    jetPt_[folderName+"_jet"]->push_back(jet->pt());
    if(!isgct)
    {
      jetPhi_[folderName+"_jet"]->push_back(g.phi(jet->iPhi()));
      jetEta_[folderName+"_jet"]->push_back(g.eta(jet->iEta()));
    } 
    jetDonut_[folderName+"_jet"]->push_back(jet->getOuterSum());
    jetArea_[folderName+"_jet"]->push_back(jet->area());
    jetRms_[folderName+"_jet"]->push_back(jet->rms());

    jetMinDR_[folderName+"_jet"]->push_back(test.at(i).minDeltaR2(col1));
    for (unsigned int j = 0; j  != jet->getOuterStrips().size(); j++)
    {
      std::string s = std::to_string(j);
      jetOuterStripsArea_[folderName+"_jet_"+s]->push_back(jet->getOuterStrips().at(j).second);
      jetOuterStripsEnergy_[folderName+"_jet_"+s]->push_back(jet->getOuterStrips().at(j).first);
    }
    for (unsigned int j = 0; j  != jet->ringSums().size(); j++)
    {
      std::string s = std::to_string(j);
      jetRingSumsArea_[folderName+"_jet_"+s]->push_back(jet->ringAreas().at(j));
      jetRingSumsEnergy_[folderName+"_jet_"+s]->push_back(jet->ringSums().at(j));
      jetRingSumsHighest_[folderName+"_jet_"+s]->push_back(jet->ringMax().at(j));
    }

    if (col1_matched_index_algo1[i]!=-1)
    {
      jetMatchedPt_[folderName+"_jet"]->push_back(col2.at(col1_matched_index_algo1.at(i)).pt());
    }
    else
    {
      jetMatchedPt_[folderName+"_jet"]->push_back(-1);
    }
    i+=1;
  }

}
  return;
}

void CaloTowerAnalyser::MakeMatchTree(const std::vector<jJet> & col1,const std::vector<jJet> & col2, TString folderName,bool isgct) {

if (col1.size()!=0){

  if(!pMade[folderName+"_match"])
  {
    std::cout << folderName+"_match" <<std::endl;
    genJetMatchAlgo1_[folderName+"_match"] = new std::vector<Int_t>();
    genJetMatchAlgo2_[folderName+"_match"] = new std::vector<Int_t>();
    tree->Branch("genJetMatchAlgo1_"+TString(folderName), "std::vector<int>", &genJetMatchAlgo1_[folderName+"_match"]);
    tree->Branch("genJetMatchAlgo2_"+TString(folderName), "std::vector<int>", &genJetMatchAlgo2_[folderName+"_match"]);
    pMade[folderName+"_match"]=true;
  }

  genJetMatchAlgo1_[folderName+"_match"]->clear();
  genJetMatchAlgo2_[folderName+"_match"]->clear();

  pairs = (isgct) ? make_gct_pairs(col1,col2) : make_pairs(col1, col2);
  std::vector<int> col2_matched_index_algo1 = analyse_pairs_local(pairs, col2.size(), 33);
  std::vector<int> col2_matched_index_algo2 = analyse_pairs_global(pairs, col2.size(), 33);


  for (unsigned int i = 0; i < col2.size(); i++)
  {
    genJetMatchAlgo1_[folderName+"_match"]->push_back(col2_matched_index_algo1[i]);
    genJetMatchAlgo2_[folderName+"_match"]->push_back(col2_matched_index_algo2[i]);
  }

}
  return;
}

void CaloTowerAnalyser::MakeSumTree(const std::vector<jJet> & col1,TString folderName,bool isgct, bool iscalibgct) {
if (col1.size()!=0){

  if(!pMade[folderName+"_sum"])
  {
    std::cout << folderName+"_sum" <<std::endl;
    sums_[folderName+"_sum"] = new std::vector<Float_t>();
    tree->Branch("sums_"+TString(folderName+"_sum"), "std::vector<float>", &sums_[folderName+"_sum"]);
    pMade[folderName+"_sum"]=true;
  }

  sums_[folderName+"_sum"]->clear();

  //  std::vector <Float_t> * jetPhi_[folderName+"_sum"] = new std::vector<Float_t>();
  //  std::vector <Float_t> *  jetEta_[folderName+"_sum"] = new std::vector<Float_t>();
  double HTcol1;
  double MHTcol1;
  double MHTcol1_x;
  double MHTcol1_y;
  if (!isgct)
  {
    HTcol1=calculateHT(col1,20);
    MHTcol1_x=calculateMHT(col1,20)[0];
    MHTcol1_y=calculateMHT(col1,20)[1];
    MHTcol1=calculateMHT(col1,20)[2];
  }
  else if(iscalibgct)
  {
    HTcol1=mGctHtCalib;
    MHTcol1=mGctHtMissCalib;
    MHTcol1_x=0;
    MHTcol1_y=0;
  }
  else
  {
    HTcol1=mGctHtUncalib;
    MHTcol1=mGctHtMissUncalib;
    MHTcol1_x=0;
    MHTcol1_y=0;
  }
  sums_[folderName+"_sum"]->push_back(HTcol1);
  sums_[folderName+"_sum"]->push_back(MHTcol1);
  sums_[folderName+"_sum"]->push_back(MHTcol1_x);
  sums_[folderName+"_sum"]->push_back(MHTcol1_y);
}
  return;
}

#endif
