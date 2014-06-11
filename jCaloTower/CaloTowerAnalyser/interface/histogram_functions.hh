#ifndef HISTOGRAM_FUNCTIONS_HH
#define HISTOGRAM_FUNCTIONS_HH

void CaloTowerAnalyser::MakeL1Trees(const std::vector<jJet> & col1) {
  if(!pMade[folderName])
  {
    std::cout << folderName <<std::endl;
    L1jetPt_[folderName] = new std::vector<Float_t>();
    L1jetPhi_[folderName] = new std::vector<Float_t>();
    L1jetEta_[folderName] = new std::vector<Float_t>();
    L1jetRing_[folderName] = new std::vector<Float_t>();
    tree->Branch("L1jetPt_"+TString(folderName), "std::vector<float>", &L1jetPt_[folderName]);
    tree->Branch("L1jetPhi_"+TString(folderName), "std::vector<float>", &L1jetPhi_[folderName]);
    tree->Branch("L1jetEta_"+TString(folderName), "std::vector<float>", &L1jetEta_[folderName]);
    tree->Branch("L1jetRing_"+TString(folderName), "std::vector<float>", &L1jetRing_[folderName]);
    pMade[folderName]=true;
  }

  //  std::vector <Float_t> * L1jetPhi_[folderName] = new std::vector<Float_t>();
  //  std::vector <Float_t> *  L1jetEta_[folderName] = new std::vector<Float_t>();
  for (auto jet = col1.begin(); jet != col1.end(); jet++)
  {
    L1jetPt_[folderName]->push_back(jet->pt());
    L1jetPhi_[folderName]->push_back(jet->phi());
    L1jetEta_[folderName]->push_back(jet->eta());
    if (jet->ringSums().size()!=0)
    {
      L1jetRing_[folderName]->push_back(jet->ringSums().at(0));
    }
  }

  tree->Fill();
  L1jetPt_[folderName]->clear();
  L1jetPhi_[folderName]->clear();
  L1jetEta_[folderName]->clear();
  L1jetRing_[folderName]->clear();

  return;
}

void CaloTowerAnalyser::MakeGenTrees(const std::vector<jJet> & col1,const std::vector<jJet> & col2) {
  if(!pMade[folderName])
  {
    std::cout << folderName <<std::endl;
    GenjetPt_[folderName] = new std::vector<Float_t>();
    GenjetPhi_[folderName] = new std::vector<Float_t>();
    GenjetEta_[folderName] = new std::vector<Float_t>();
    GenjetRing_[folderName] = new std::vector<Float_t>();
    tree->Branch("GenjetPt_"+TString(folderName), "std::vector<float>", &GenjetPt_[folderName]);
    tree->Branch("GenjetPhi_"+TString(folderName), "std::vector<float>", &GenjetPhi_[folderName]);
    tree->Branch("GenjetEta_"+TString(folderName), "std::vector<float>", &GenjetEta_[folderName]);
    tree->Branch("GenjetRing_"+TString(folderName), "std::vector<float>", &GenjetRing_[folderName]);
    pMade[folderName]=true;
  }

  //  std::vector <Float_t> * GenjetPhi_[folderName] = new std::vector<Float_t>();
  //  std::vector <Float_t> *  GenjetEta_[folderName] = new std::vector<Float_t>();
  for (auto jet = col2.begin(); jet != col2.end(); jet++)
  {
    GenjetPt_[folderName]->push_back(jet->pt());
    GenjetPhi_[folderName]->push_back(jet->phi());
    GenjetEta_[folderName]->push_back(jet->eta());
    if (jet->ringSums().size()!=0)
    {
      GenjetRing_[folderName]->push_back(jet->ringSums().at(0));
    }
  }

  tree->Fill();
  GenjetPt_[folderName]->clear();
  GenjetPhi_[folderName]->clear();
  GenjetEta_[folderName]->clear();
  GenjetRing_[folderName]->clear();

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
