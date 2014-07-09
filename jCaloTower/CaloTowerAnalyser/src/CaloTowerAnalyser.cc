#include "jCaloTower/CaloTowerAnalyser/interface/CaloTowerAnalyser.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/jet_functions.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/histogram_functions.hh"


//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

CaloTowerAnalyser::CaloTowerAnalyser(const edm::ParameterSet& iConfig) {

  //edm::Service<TFileService> fs;
  edm::Service<TFileService> fs;
  mskim=iConfig.getParameter<std::string>("skim_name");
  mgct=iConfig.getParameter<bool>("gctinfo");

  tree = fs->make<TTree>("L1Tree","L1Tree");

  tree->Branch("mNPV", &mNPV, "mNPV/I");  
  tree->Branch("numHotTow", &numHotTow, "numHotTow/I");  
  tree->Branch("numHotTow12", &numHotTow12, "numHotTow12/I");  
  tree->Branch("medianRho", &medianRho, "medianRho/D");  
  //tree->Branch("Esums_", "std::vector<float>", &Esums_);
// std::string folderName = "Event_";
  // std::stringstream caseNumber;
  // caseNumber << eventNumber;
  // folderName.append(caseNumber.str());

  TriggerTowerGeometry g; //to run the constructor -- could also make this static



  mEventNumber=1;

  std::vector<TString> l1Sizes;
  l1Sizes.push_back("3");
  l1Sizes.push_back("4");
  this->setL1Sizes(l1Sizes);

  std::vector<TString> globalVars;
  //globalVars.push_back("rhott");
  //globalVars.push_back("rhogen");
  globalVars.push_back("nint");
  this->setGlobalPusVars(globalVars);

  std::vector<TString> l1Vars;
  l1Vars.push_back("strip1");
  l1Vars.push_back("strip2");
  l1Vars.push_back("strip3");
  l1Vars.push_back("strip4");
  l1Vars.push_back("strip5");
  l1Vars.push_back("strip6");
  l1Vars.push_back("strip7");
  l1Vars.push_back("strip8");
  /* l1Vars.push_back("middle6");
     l1Vars.push_back("middle4");*/
  l1Vars.push_back("out1_middle2");
  l1Vars.push_back("out2_middle2");
  this->setL1PusVars(l1Vars);

  std::map<TString,int> etaBins;
  etaBins["eta_bin1"] = -14;
  etaBins["eta_bin2"] = 0;
  etaBins["eta_bin3"] = 14;
  etaBins["eta_bin4"] = 28;
  this->setEtaBins(etaBins);

  std::map<TString,int> ptBins;
  ptBins["pt_0to20"] = 20; 
  ptBins["pt_20to40"] = 40; 
  ptBins["pt_40to60"] = 60; 
  ptBins["pt_60to80"] = 80; 
  ptBins["pt_80to100"] = 100; 
  ptBins["pt_100to120"] = 120; 
  ptBins["pt_120to140"] = 140; 
  ptBins["pt_140to160"] = 160; 
  ptBins["pt_160to180"] = 180; 
  ptBins["pt_180to200"] = 200; 
  this->setPtBins(ptBins);

  std::map<TString, int> nintBins;
  nintBins["nint_30to35"] = 35;
  nintBins["nint_35to40"] = 40;
  nintBins["nint_40to45"] = 45;
  nintBins["nint_45to50"] = 50;
  this->setNintBins(nintBins);

  //Make the necessary histograms


}


CaloTowerAnalyser::~CaloTowerAnalyser()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

double CaloTowerAnalyser::calculateHT(const std::vector<jJet> & jets, const int & thresh) {
  double ht=0.0;
  for(unsigned int i=0; i< jets.size(); i++) {
    if (jets[i].pt() > thresh)  ht += jets[i].pt();
  }
  return ht;
}

std::vector<double> CaloTowerAnalyser::calculateMHT(const std::vector<jJet> & jets, const int & thresh) {
  double mht_x=0.0;
  double mht_y=0.0;
  for(unsigned int i=0; i< jets.size(); i++) {
      if (jets[i].pt() > thresh)
      {
	mht_x -= cos(g.phi(jets[i].iPhi()))*jets[i].pt();
	mht_y -= sin(g.phi(jets[i].iPhi()))*jets[i].pt();
      }
    }
    std::vector<double> results;
    results.push_back(mht_x);
    results.push_back(mht_y);
    results.push_back(sqrt((mht_x*mht_x) + (mht_y*mht_y)));
    return results;
}
//
// member functions
//
// ------------ method called for each event  ------------
  void
CaloTowerAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //std::cout <<"EVENT " << mEventNumber << std::endl;
  if (mEventNumber % 100 == 0) { std::cout << "starting event " << mEventNumber << std::endl; }

  std::vector<jJet> gct_jJet_uncalib;
  std::vector<jJet> gct_jJet_calib;
  if (mgct)
  {

    //    std::cout << "at event " << mEventNumber << std::endl;

    // Get GCT jets (uncalib) collection
    edm::Handle<L1GctJetCandCollection> GctUncalibCenJets;
    edm::InputTag gctUncalibCenJets("valGctDigis","cenJets",mskim);
    iEvent.getByLabel(gctUncalibCenJets, GctUncalibCenJets);
    for(unsigned int i=0; i<GctUncalibCenJets->size(); i++) {
      if (GctUncalibCenJets->at(i).bx()==0)
      {
	//std::cout << GctUncalibCenJets->at(i).rank() << ", " << GctUncalibCenJets->at(i).regionId().ieta() << ", " << GctUncalibCenJets->at(i).regionId().iphi() << std::endl;
	gct_jJet_uncalib.push_back(jJet(GctUncalibCenJets->at(i).rank()*4,GctUncalibCenJets->at(i).regionId().ieta(),GctUncalibCenJets->at(i).regionId().iphi(),GctUncalibCenJets->at(i).bx()));
      } 
    }


    // Get GCT jets (calib) collection
    edm::Handle<L1GctJetCandCollection> GctCalibCenJets;
    edm::InputTag gctCalibCenJets("gctDigis","cenJets",mskim);
    iEvent.getByLabel(gctCalibCenJets, GctCalibCenJets);

    for(unsigned int i=0; i<GctCalibCenJets->size(); i++) {
      //std::cout << GctCalibCenJets->at(i).rank() << ", " << GctCalibCenJets->at(i).regionId().ieta() << ", " << GctCalibCenJets->at(i).regionId().iphi() << std::endl;
      if (GctUncalibCenJets->at(i).bx()==0)
      {
	//std::cout << GctUncalibCenJets->at(i).rank() << ", " << GctUncalibCenJets->at(i).regionId().ieta() << ", " << GctUncalibCenJets->at(i).regionId().iphi() << std::endl;
	gct_jJet_calib.push_back(jJet(GctCalibCenJets->at(i).rank()*4,GctCalibCenJets->at(i).regionId().ieta(),GctCalibCenJets->at(i).regionId().iphi(),GctCalibCenJets->at(i).bx()));
      } 
    }
    // Get GCT HT jets (calib) collection
    edm::Handle<L1GctEtHadCollection> GctHadTotal;
    edm::InputTag gctHadT("gctDigis","",mskim);
    iEvent.getByLabel(gctHadT, GctHadTotal);

    for(unsigned int i=0; i<GctHadTotal->size(); i++) {
      if (GctHadTotal->at(i).bx()==0)
      {
	mGctHtCalib=GctHadTotal->at(i).et();
      } 
    }
    edm::Handle<L1GctEtHadCollection> GctValHadTotal;
    edm::InputTag gctValHadT("valGctDigis","",mskim);
    iEvent.getByLabel(gctValHadT, GctValHadTotal);

    for(unsigned int i=0; i<GctValHadTotal->size(); i++) {
      if (GctValHadTotal->at(i).bx()==0)
      {
	mGctHtUncalib=GctValHadTotal->at(i).et();
      } 
    }
    edm::Handle<L1GctHtMissCollection> GctHtMiss;
    edm::InputTag gctMHT("gctDigis","",mskim);
    iEvent.getByLabel(gctMHT, GctHtMiss);

    for(unsigned int i=0; i<GctHtMiss->size(); i++) {
      if (GctHtMiss->at(i).bx()==0)
      {
	mGctHtMissCalib=GctHtMiss->at(i).et();
      } 
    }
    edm::Handle<L1GctHtMissCollection> GctValHtMiss;
    edm::InputTag gctValMHT("valGctDigis","",mskim);
    iEvent.getByLabel(gctValMHT, GctValHtMiss);
    for(unsigned int i=0; i<GctValHtMiss->size(); i++) {
      if (GctValHtMiss->at(i).bx()==0)
      {
	mGctHtMissUncalib=GctValHtMiss->at(i).et();
      } 
    }

  }

  edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers;
  iEvent.getByLabel("L1CaloTowerProducer", triggertowers);

  // Get gen jet collection
  edm::Handle<reco::GenJetCollection> hGenJetProduct;
  //edm::InputTag genjetselector("ak4GenJets","","skimrun");
  edm::InputTag genjetselector("ak4GenJets","",mskim);
  //iEvent.getByLabel("ak4GenJets", hGenJetProduct);
  iEvent.getByLabel(genjetselector, hGenJetProduct);


  //get nvertices from simulation
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  int NPV=-1;

  std::vector<PileupSummaryInfo>::const_iterator PVI;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
    int BX = PVI->getBunchCrossing();
    //std::cout << "bx = " << BX << std::endl;
    if(BX == 0) {
      NPV = PVI->getPU_NumInteractions();
      //std::cout << "NPV = " << NPV << std::endl;
      break;
    }
  }

  this->SetNPV(NPV);

  // Get genparticles:
  edm::Handle<reco::GenParticleCollection> genphandle;
  // For now, hard-code getByLabel
  iEvent.getByLabel("genParticles", genphandle);

  std::vector<fastjet::PseudoJet> pseudoak4genjetsp;
  std::vector<fastjet::PseudoJet> ak4genjetsp;

  std::vector<jJet> top_jJet;
  for(unsigned int i = 0; i < genphandle->size(); i++) {
    const reco::GenParticle* p = &((*genphandle)[i]);
    if ( (p->status() == 1) && p->pt() > 0.0 && abs(p->pdgId()) != 12 && abs(p->pdgId()) != 13 && abs(p->pdgId()) != 14 && abs(p->pdgId()) != 16 && abs(p->eta()) < 3.0) {
      //std::cout << p->pdgId() << ", " << p->pt() << ", " << g.iEta(p->eta()) << ", " << g.iPhi(p->phi()) << std::endl;
      fastjet::PseudoJet curPseudoJet;
      curPseudoJet.reset_PtYPhiM( p->pt(), p->eta(), p->phi(), 0.0); //last argument is mass
      pseudoak4genjetsp.push_back(curPseudoJet);
    }
    if ((p->pdgId() == 6 || p->pdgId() == -6) && p->status()==22)
    {
      top_jJet.push_back(jJet(p->pt(),g.iEta(p->eta()),g.iPhi(p->phi())));
    }
  }
  // Handle<l1slhc::L1CaloTowerCollection> offlinetriggertowers;
  // iEvent.getByLabel("L1OfflineCaloTowerProducer", offlinetriggertowers);
  // LogInfo("Demo") << "number of L1 offline trigger towers: " << offlinetriggertowers->size();

  // Handle<CaloTowerCollection> calotowers;
  // iEvent.getByLabel("towerMaker", calotowers); 
  // LogInfo("Demo") << "number of calotowers "<< calotowers->size();



  std::vector<fastjet::PseudoJet> pseudoak4ttjets;
  std::vector<fastjet::PseudoJet> ak4ttjets;

  std::vector< std::vector<int> > myarray(56, std::vector<int>(72, 0)); //this is just a container for the (E+H) per tower
  std::vector< std::vector<int> > myarrayECAL(56, std::vector<int>(72, 0)); //this is just a container for the (E+H) per tower
  std::vector< std::vector<int> > myarrayHCAL(56, std::vector<int>(72, 0)); //this is just a container for the (E+H) per tower

  int ntowersinevent=0; //this is a container to calculate the number of non-zero towers in an event (correlation with NPV)
  std::vector<int> energies_per_event; //this is a container to calculate the median tower energy in an event

  double ET=0.;
  double met_x=0.;
  double met_y=0.;
  numHotTow = 0;
  numHotTow12 = 0;
  for(l1slhc::L1CaloTowerCollection::const_iterator j=triggertowers->begin(); j!=triggertowers->end(); j++) {

    if ( abs((*j).iEta()) > 28 ) { continue; } //i.e. |eta| < 3 only

    energies_per_event.push_back((*j).E() + (*j).H()); //for median calculation
    if((*j).E() + (*j).H() > 0) { ntowersinevent++; } //to look at correlation with NPV

    myarray[g.new_iEta((*j).iEta())][g.new_iPhi((*j).iPhi())] = ((*j).E() + (*j).H());
    myarrayECAL[g.new_iEta((*j).iEta())][g.new_iPhi((*j).iPhi())] = ((*j).E());
    myarrayHCAL[g.new_iEta((*j).iEta())][g.new_iPhi((*j).iPhi())] = ((*j).H());
    ET += (*j).E()+(*j).H();
    met_x -= cos(g.phi((*j).iPhi())) * ((*j).E() + (*j).H());
    met_y -= sin(g.phi((*j).iPhi())) * ((*j).E() + (*j).H());
    if (abs((*j).iEta()) <= 12 && ((*j).E() + (*j).H()) > 0.1) { numHotTow12++; }
    if (((*j).E() + (*j).H()) > 0.1) { numHotTow++; }
    //so now myarray is on the scale ieta 0-56, iphi 0-71
    //std::cout << "old: (" << (*j).iEta() << ", " << (*j).iPhi() << ", " << (*j).E() + (*j).H() << ")" << std::endl;
    //std::cout << "size = " << triggertowers->size() << std::endl;

    //make ak4TT:
    fastjet::PseudoJet curPseudoJet;
    curPseudoJet.reset_PtYPhiM( ((*j).E() + (*j).H()) , g.eta((*j).iEta()), g.phi((*j).iPhi()), 0.0); //last argument is mass
    pseudoak4ttjets.push_back(curPseudoJet);
  }

  mET=ET;
  mMET.clear();
  mMET.push_back(met_x);
  mMET.push_back(met_y);
  mMET.push_back(sqrt(met_x*met_x+met_y*met_y));
  /*Esums_->clear();
  Esums_->push_back(ET);
  Esums_->push_back(sqrt(met_x*met_x+met_y*met_y));
  Esums_->push_back(met_x);
  Esums_->push_back(met_y);*/

  //now make the genjetsp collection (clustered based on eta<3 deposits and no muons and neutrinos)
  this->getJets(pseudoak4genjetsp, ak4genjetsp);
  //now make the ak4tt collection
  this->getJets(pseudoak4ttjets, ak4ttjets);

  fastjet::GridMedianBackgroundEstimator lGrid(5.0,0.8);
  lGrid.set_particles(pseudoak4ttjets);


  lGrid=fastjet::GridMedianBackgroundEstimator(5.0,0.8);
  lGrid.set_particles(pseudoak4genjetsp);


  //so at this stage, we have ak4ttjets and ak4genjetsp (and genjets)

  //now, let's try to match the ak4tt jets with the ak4genjetsp and look at two things:
  //1. The energy correlation
  //2. The matching efficiency
  //we use jMatch as an algorithm

  //make std::vector<jJet> for ak4genjetsp and for ak4tt
  //std::cout << "ak4genjetsp:" << std::endl;
  std::vector<jJet> ak4genjetsp_jJet;
  for(unsigned int i=0; i<ak4genjetsp.size(); i++) {
    ak4genjetsp_jJet.push_back(jJet(ak4genjetsp[i].pt(), g.iEta(ak4genjetsp[i].eta()), g.iPhi(ak4genjetsp[i].phi())));
  }

  //std::cout << "ak4tt:" << std::endl;
  std::vector<jJet> ak4tt_jJet;
  for(unsigned int i=0; i<ak4ttjets.size(); i++) {
    //std::cout << "(" << ak4ttjets[i].pt() << ", " << g.iEta(ak4ttjets[i].eta()) << ", " << g.iPhi(ak4ttjets[i].phi()) << ")" << std::endl;
    ak4tt_jJet.push_back(jJet(ak4ttjets[i].pt(), g.iEta(ak4ttjets[i].eta()), g.iPhi(ak4ttjets[i].phi())));
  }



  //make a container for the L1 jets
  std::vector<jJet> L1_5400_3_chunky_jJet = getL1JetsMask(myarray, mask_square_9by9(), mask_chunky_donut_15by15(),4, 0, 0);
  std::vector<jJet> L1_5400_for_Nick = getL1JetsMask(myarray,myarrayECAL,myarrayHCAL, mask_square_9by9(),mask_donut_11by11(),4,0,0);

  this->MakeJetTree(ak4genjetsp_jJet,ak4genjetsp_jJet,"ak4_gen",false);
  this->MakeSumTree(ak4genjetsp_jJet,"ak4_gen",false);
  this->MakeMatchTree(ak4genjetsp_jJet,ak4genjetsp_jJet,"ak4_gen",false);

  std::map <TString,std::vector<jJet> > jJetComp;
  jJetComp["L1_for_Nick"]=L1_5400_for_Nick;
  jJetComp["5400_chunky"]=L1_5400_3_chunky_jJet;

  for (auto jet = jJetComp.begin();jet != jJetComp.end(); jet++)
  {
    this->MakeJetTree(jet->second,ak4genjetsp_jJet,jet->first,false);
    this->MakeMatchTree(jet->second,ak4genjetsp_jJet,jet->first,false);
    this->MakeSumTree(jet->second,jet->first,false);
  } 

  if(mgct)
  {
    this->MakeJetTree(gct_jJet_calib,ak4genjetsp_jJet, "gct_calib_gen",true);
    this->MakeMatchTree(gct_jJet_calib,ak4genjetsp_jJet,"gct_calib_gen",true);
    this->MakeSumTree(gct_jJet_calib,"gct_calib_gen",true,true);

    this->MakeJetTree(gct_jJet_uncalib,ak4genjetsp_jJet,  "gct_uncalib_gen",true);
    this->MakeMatchTree(gct_jJet_uncalib,ak4genjetsp_jJet,"gct_uncalib_gen",true);
    this->MakeSumTree(gct_jJet_uncalib,"gct_uncalib_gen",true,false);
  }

  tree->Fill();
  mEventNumber++;
  //std::cout << "reached end of event loop" << std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
  void 
CaloTowerAnalyser::beginJob()
{


}

// ------------ method called once each job just after ending the event loop  ------------
  void 
CaloTowerAnalyser::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
   void 
   CaloTowerAnalyser::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void 
   CaloTowerAnalyser::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void 
   CaloTowerAnalyser::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void 
   CaloTowerAnalyser::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CaloTowerAnalyser::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CaloTowerAnalyser);
