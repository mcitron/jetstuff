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
  // std::string folderName = "Event_";
  // std::stringstream caseNumber;
  // caseNumber << eventNumber;
  // folderName.append(caseNumber.str());
  TFileDirectory dir = fs->mkdir("global_histograms");

  TriggerTowerGeometry g; //to run the constructor -- could also make this static

  genjet_pt = dir.make<TH1D>("genjet_pt",";p_{T};",1000, -0.5, 999.5);

  tower_pt_real= dir.make<TH1D>("towers_real", ";pt;", 100, -0.5, 99.5);
  num_tower_pt_real= dir.make<TH1D>("num_towers_real", ";pt;", 100, -0.5, 99.5);
  tower_pt_real_jetpt= dir.make<TH2D>("towers_real_jet_pt", ";pt;jetpt", 100, -0.5, 99.5,100,-0.5,99.5);
  num_tower_pt_real_jetpt= dir.make<TH2D>("num_towers_real_jet_pt", ";pt;jetpt", 100, -0.5, 99.5,100,-0.5,99.5);

  tower_pt_pu= dir.make<TH1D>("towers_pu", ";pt;", 100, -0.5, 99.5);
  num_tower_pt_pu= dir.make<TH1D>("num_towers_pu", ";pt;", 100, -0.5, 99.5);
  tower_pt_pu_jetpt= dir.make<TH2D>("towers_pu_jet_pt", ";pt;jetpt", 100, -0.5, 99.5,100,-0.5,99.5);
  num_tower_pt_pu_jetpt= dir.make<TH2D>("num_towers_pu_jet_pt", ";pt;jetpt", 100, -0.5, 99.5,100,-0.5,99.5);

  //genjet_pt_nomunu_far = dir.make<TH1D>("genjet_pt_nomunu_far",";p_{T};",1000, -0.5, 999.5);
  //genjet_pt_nomunu_far_match_L1 = dir.make<TH1D>("genjet_pt_nomunu_far_match_L1",";p_{T};",1000, -0.5, 999.5);
  median_energy_per_event = dir.make<TH1D>("median_energy_per_event",";median energy per event;",100, -0.5, 99.5);
  median_jet_5400_energy_per_event = dir.make<TH1D>("median_jet_energy_per_event",";median energy per event;",100, -0.5, 99.5);
  median_rho_nvtx = dir.make<TH2D>("median_energy_jet_tower_per_event",";nvtx;median rho",100, -0.5, 99.5,1000,-0.5,999.5);


  num_tops_per_event = dir.make<TH1D>("Number_of_tops",";Num;",100, -0.5, 99.5);
  mean_top_pt_hist = dir.make<TH1D>("mean_top",";median_top;",1000, -0.5, 999.5);
  eff_over_x1_top = dir.make<TH1D>("Efficiency_x1",";Eff;",1000,-0.5,999.5); 
  eff_over_x2_top = dir.make<TH1D>("Efficiency_x2",";Eff;",1000,-0.5,999.5); 
  eff_over_x3_top = dir.make<TH1D>("Efficiency_x3",";Eff;",1000,-0.5,999.5); 
  eff_over_x4_top = dir.make<TH1D>("Efficiency_x4",";Eff;",1000,-0.5,999.5); 
  ntowers_vs_npv = dir.make<TH2D>("ntowers_vs_npv", ";ntowers;NPV", 500, -5, 4995, 100, -0.5, 99.5);

  r4_vs_npv_eta1_pt3050 = dir.make<TH2D>("r4_vs_npv_eta1_pt3050", ";r4;NPV", 100, -0.5, 99.5, 100, -0.5, 99.5);
  r4_vs_npv_eta2_pt3050 = dir.make<TH2D>("r4_vs_npv_eta2_pt3050", ";r4;NPV", 100, -0.5, 99.5, 100, -0.5, 99.5);
  r4_vs_npv_eta3_pt3050 = dir.make<TH2D>("r4_vs_npv_eta3_pt3050", ";r4;NPV", 100, -0.5, 99.5, 100, -0.5, 99.5);
  r4_vs_npv_eta1_pt80100 = dir.make<TH2D>("r4_vs_npv_eta1_pt80100", ";r4;NPV", 100, -0.5, 99.5, 100, -0.5, 99.5);
  r4_vs_npv_eta2_pt80100 = dir.make<TH2D>("r4_vs_npv_eta2_pt80100", ";r4;NPV", 100, -0.5, 99.5, 100, -0.5, 99.5);
  r4_vs_npv_eta3_pt80100 = dir.make<TH2D>("r4_vs_npv_eta3_pt80100", ";r4;NPV", 100, -0.5, 99.5, 100, -0.5, 99.5);


  deltaGenL1_pT3050_eta1_v1 = dir.make<TH2D>("deltaGenL1_pT3050_eta1_v1",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_v2 = dir.make<TH2D>("deltaGenL1_v2",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_v3 = dir.make<TH2D>("deltaGenL1_v3",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_pT3050_eta1_v4 = dir.make<TH2D>("deltaGenL1_pT3050_eta1_v4",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_pT3050_eta2_v1 = dir.make<TH2D>("deltaGenL1_pT3050_eta2_v1",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_pT3050_eta2_v4 = dir.make<TH2D>("deltaGenL1_pT3050_eta2_v4",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_pT3050_eta3_v1 = dir.make<TH2D>("deltaGenL1_pT3050_eta3_v1",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_pT3050_eta3_v4 = dir.make<TH2D>("deltaGenL1_pT3050_eta3_v4",";delta(Gen, L1);NPV", 100, -5.05, 4.95, 11, -2.5, 52.5);
  deltaGenL1_ntowers = dir.make<TH2D>("deltaGenL1_ntowers",";delta(Gen,L1);ntowers",100, -50.5, 49.5, 100, -0.5, 99.5);
  deltaGenL1_R1 = dir.make<TH2D>("deltaGenL1_R1",";delta(Gen,L1);R1",100, -50.5, 49.5, 100, -0.5, 99.5);
  deltaGenL1_R2 = dir.make<TH2D>("deltaGenL1_R2",";delta(Gen,L1);R2",100, -50.5, 49.5, 100, -0.5, 99.5);
  deltaGenL1_R3 = dir.make<TH2D>("deltaGenL1_R3",";delta(Gen,L1);R3",100, -50.5, 49.5, 100, -0.5, 99.5);
  deltaGenL1_R4 = dir.make<TH2D>("deltaGenL1_R4",";delta(Gen,L1);R4",100, -50.5, 49.5, 100, -0.5, 99.5);

  et_hist  = dir.make<TH1D>("et",";col2 H_{T};",3000,-0.5,2999.5);
  met_x_hist  = dir.make<TH1D>("met_x",";col2 MH_{T};",1000,-500.5,499.5);
  met_y_hist  = dir.make<TH1D>("met_y",";col2 MH_{T};",1000,-500.5,499.5);
  met_hist  = dir.make<TH1D>("met",";col2 MH_{T};",3000,-0.5,2999.5);

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
  this->bookPusHists("pus_histograms");


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
	//std::cout << GctHadTotal->at(i).et() << std::endl;
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
  const reco::GenJetCollection * genJetCol = 0;
  genJetCol = hGenJetProduct.product();

  for(unsigned int i=0; i < genJetCol->size(); i++) {
    genjet_pt->Fill((*genJetCol)[i].pt()); //note that there are no eta or ID requirements here (ie neutrinos etc)
  }

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
  num_tops_per_event->Fill(top_jJet.size());
  // Handle<l1slhc::L1CaloTowerCollection> offlinetriggertowers;
  // iEvent.getByLabel("L1OfflineCaloTowerProducer", offlinetriggertowers);
  // LogInfo("Demo") << "number of L1 offline trigger towers: " << offlinetriggertowers->size();

  // Handle<CaloTowerCollection> calotowers;
  // iEvent.getByLabel("towerMaker", calotowers); 
  // LogInfo("Demo") << "number of calotowers "<< calotowers->size();



  std::vector<fastjet::PseudoJet> pseudoak4ttjets;
  std::vector<fastjet::PseudoJet> ak4ttjets;

  std::vector< std::vector<int> > myarray(56, std::vector<int>(72, 0)); //this is just a container for the (E+H) per tower

  int ntowersinevent=0; //this is a container to calculate the number of non-zero towers in an event (correlation with NPV)
  std::vector<int> energies_per_event; //this is a container to calculate the median tower energy in an event
  double ET=0;
  double met_x=0;
  double met_y=0;
  for(l1slhc::L1CaloTowerCollection::const_iterator j=triggertowers->begin(); j!=triggertowers->end(); j++) {

    if ( abs((*j).iEta()) > 28 ) { continue; } //i.e. |eta| < 3 only

    energies_per_event.push_back((*j).E() + (*j).H()); //for median calculation
    if((*j).E() + (*j).H() > 0) { ntowersinevent++; } //to look at correlation with NPV

    myarray[g.new_iEta((*j).iEta())][g.new_iPhi((*j).iPhi())] = ((*j).E() + (*j).H());
    ET += (*j).E()+(*j).H();
    met_x -= cos(g.phi((*j).iPhi())) * ((*j).E() + (*j).H());
    met_y -= sin(g.phi((*j).iPhi())) * ((*j).E() + (*j).H());
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
  et_hist->Fill(mET);
  met_hist->Fill(mMET[2]);
  met_x_hist->Fill(mMET[0]);
  met_y_hist->Fill(mMET[1]);

  ntowers_vs_npv->Fill(ntowersinevent, this->GetNPV()); //ntowers > 0 in an event

  //now sort and calculate median of energies
  double median_tower = 0;
  if(energies_per_event.size() > 0) {
    std::sort(energies_per_event.begin(), energies_per_event.end()); //sort the vector
    if(energies_per_event.size() % 2 == 0 ) {
      int index1 = energies_per_event.size() / 2;
      //median_energy_per_event->Fill((double)(energies_per_event[index1] + energies_per_event[index1+1]) / 2.0);
      median_tower =(double)(energies_per_event[index1] + energies_per_event[index1+1]) / 2.0;
    } else {
      int index1 = (int)energies_per_event.size() / 2;
      //median_energy_per_event->Fill(energies_per_event[index1]);
      median_tower = energies_per_event[index1];
    }
  }
  median_energy_per_event->Fill(median_tower);

  //now make the genjetsp collection (clustered based on eta<3 deposits and no muons and neutrinos)
  this->getJets(pseudoak4genjetsp, ak4genjetsp);
  //now make the ak4tt collection
  this->getJets(pseudoak4ttjets, ak4ttjets);

  fastjet::GridMedianBackgroundEstimator lGrid(5.0,0.8);
  lGrid.set_particles(pseudoak4ttjets);
  //double rhoTt=lGrid.rho();


  lGrid=fastjet::GridMedianBackgroundEstimator(5.0,0.8);
  lGrid.set_particles(pseudoak4genjetsp);
  //double rhoGen=lGrid.rho();


  //so at this stage, we have ak4ttjets and ak4genjetsp (and genjets)

  //now, let's try to match the ak4tt jets with the ak4genjetsp and look at two things:
  //1. The energy correlation
  //2. The matching efficiency
  //we use jMatch as an algorithm

  //make std::vector<jJet> for ak4genjetsp and for ak4tt
  //std::cout << "ak4genjetsp:" << std::endl;
  std::vector<jJet> ak4genjetsp_jJet;
  for(unsigned int i=0; i<ak4genjetsp.size(); i++) {
    //std::cout << "(" << ak4genjetsp[i].pt() << ", " << g.iEta(ak4genjetsp[i].eta()) << ", " << g.iPhi(ak4genjetsp[i].phi()) << ")" << std::endl;
    ak4genjetsp_jJet.push_back(jJet(ak4genjetsp[i].pt(), g.iEta(ak4genjetsp[i].eta()), g.iPhi(ak4genjetsp[i].phi())));
  }


  //an example on how to use the closestJetDistance function
  /*  
      std::vector<int> minDR2genp;
      if(ak4genjetsp_jJet.size()>0) {
      minDR2genp = closestJetDistance(ak4genjetsp_jJet);
      for(unsigned int i=0; i<ak4genjetsp_jJet.size(); i++) {
      if(minDR2genp[i] > 35) {
      genjet_pt_nomunu_far->Fill(ak4genjetsp_jJet[i].pt());
      }
      }
      }
   */

  //std::cout << "ak4tt:" << std::endl;
  std::vector<jJet> ak4tt_jJet;
  for(unsigned int i=0; i<ak4ttjets.size(); i++) {
    //std::cout << "(" << ak4ttjets[i].pt() << ", " << g.iEta(ak4ttjets[i].eta()) << ", " << g.iPhi(ak4ttjets[i].phi()) << ")" << std::endl;
    ak4tt_jJet.push_back(jJet(ak4ttjets[i].pt(), g.iEta(ak4ttjets[i].eta()), g.iPhi(ak4ttjets[i].phi())));
  }



  //Testing discriminator
  std::vector<jJet> L1_5400_real_jJet;
  std::vector<jJet> L1_5400_pu_jJet;

  std::vector<jJet> L1_4300_real_jJet;
  std::vector<jJet> L1_4300_pu_jJet;

  //make a container for the L1 jets
  std::vector<jJet> L1_5400_jJet = getL1Jets(myarray, 5, 4, 0, 0);
  std::vector<jJet> L1_5450_jJet = getL1Jets(myarray, 5, 4, 5, 0);
  std::vector<jJet> L1_5420_jJet = getL1Jets(myarray, 5, 4, 2, 0);
  std::vector<jJet> L1_5430_jJet = getL1Jets(myarray, 5, 4, 3, 0);
  std::vector<jJet> L1_5440_jJet = getL1Jets(myarray, 5, 4, 4, 0);
  std::vector<jJet> L1_6550_jJet = getL1Jets(myarray, 6, 5, 5, 0);
  std::vector<jJet> L1_4300_jJet = getL1Jets(myarray, 4, 3, 0, 0);

  std::vector<jJet> L1_4300donut_jJet;
  std::vector<jJet> L1_4350donut_jJet;
  std::vector<jJet> L1_5400donut_jJet;
  std::vector<jJet> L1_5400global_jJet;
  std::vector<jJet> L1_5450donut_jJet;
  std::vector<jJet> L1_5450global_jJet;

  //std::vector<jJet> L1_4300donut_jJet;
  std::vector<jJet> L1_4300global_jJet;

  makePusHists(myarray, L1_4300_jJet, L1_5450_jJet);

  double median_jet_5400 = getMedian(L1_5400_jJet);
  double median_jet_5450 = getMedian(L1_5450_jJet);
  //double median_jet_4300 = getMedian(L1_4300_jJet);
  median_jet_5400_energy_per_event->Fill(median_jet_5400);
  median_rho_nvtx->Fill(mNPV,median_jet_5400);

  std::map <TString,std::vector<jJet> > jJetMap;
  std::map <TString,std::vector<fastjet::PseudoJet> > ak4Map;
  std::map <TString,const reco::GenJetCollection * > genMap;


  for(unsigned int i=0; i<L1_5400_jJet.size(); i++) {
    double newenergydonut5400=L1_5400_jJet[i].eatDonut();
    double newenergyglobal5400=L1_5400_jJet[i].eatGlobe(median_jet_5400);
    if(newenergydonut5400 >= 0.0) { 
      L1_5400donut_jJet.push_back(jJet(newenergydonut5400, L1_5400_jJet[i].iEta(), L1_5400_jJet[i].iPhi()));
      L1_5400_real_jJet.push_back(L1_5400_jJet[i]);
    }
    else
    {
      L1_5400_pu_jJet.push_back(L1_5400_jJet[i]);
    }
    if(newenergyglobal5400 >= 0.0) {
      L1_5400global_jJet.push_back(jJet(newenergyglobal5400, L1_5400_jJet[i].iEta(), L1_5400_jJet[i].iPhi())); 

    }
  }
  for(unsigned int i=0; i<L1_5450_jJet.size(); i++) {
    double newenergydonut5450=L1_5450_jJet[i].eatDonut();
    double newenergyglobal5450=L1_5450_jJet[i].eatGlobe(median_jet_5450);
    //Fill Real and pu jjet vectors
    if(newenergydonut5450 >= 0.0) { 
      L1_5450donut_jJet.push_back(jJet(newenergydonut5450, L1_5450_jJet[i].iEta(), L1_5450_jJet[i].iPhi()));
    }
    if(newenergyglobal5450 >= 0.0) {
      L1_5450global_jJet.push_back(jJet(newenergyglobal5450, L1_5450_jJet[i].iEta(), L1_5450_jJet[i].iPhi())); 

    }
  }

  for (auto jet = L1_5450_jJet.begin();jet != L1_5450_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5440_jJet.begin();jet != L1_5440_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5430_jJet.begin();jet != L1_5430_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5420_jJet.begin();jet != L1_5420_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5400_jJet.begin();jet != L1_5400_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5400donut_jJet.begin();jet != L1_5400donut_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5400global_jJet.begin();jet != L1_5400global_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5450donut_jJet.begin();jet != L1_5450donut_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);
  for (auto jet = L1_5450global_jJet.begin();jet != L1_5450global_jJet.end(); jet++) jet->setPt(jet->pt()*0.5);


  //Calibration
  //std::vector<jJet> calibrated_L1_5400_jJet = calibrateL1Jets(L1_5400_jJet,jetType::l15400nopus20,20,9999);
  std::vector<jJet> calibrated_L1_5400_jJet = calibrateL1Jets(L1_5400_jJet,jetType::l15400nopusGeV,8,9999);
  std::vector<jJet> calibrated_L1_5400global_jJet = calibrateL1Jets(L1_5400global_jJet,jetType::l15400globalGeV,8,9999);
  std::vector<jJet> calibrated_L1_5400donut_jJet = calibrateL1Jets(L1_5400donut_jJet,jetType::l15400donutGeV,8,9999);
  //std::vector<jJet> calibrated_L1_5450_jJet = calibrateL1Jets(L1_5450_jJet,jetType::l15450nopus40,40,9999);
  std::vector<jJet> calibrated_L1_5450_jJet = calibrateL1Jets(L1_5450_jJet,jetType::l15450nopusGeV,10,9999);
  //std::vector<jJet> calibrated_L1_5450donut_jJet = calibrateL1Jets(L1_5450donut_jJet,jetType::l15450donut30,30,9999);
  std::vector<jJet> calibrated_L1_5450donut_jJet = calibrateL1Jets(L1_5450donut_jJet,jetType::l15450donutGeV,10,9999);
  //this->mPrintMe = false;


  this->compareJetCollections(calibrated_L1_5400donut_jJet, ak4genjetsp_jJet,"5400_calib_donut_gen",false);
  this->compareJetCollections(calibrated_L1_5400_jJet, ak4genjetsp_jJet,"5400_calib_nopus_gen",false);
  /*  this->compareJetCollections(calibrated_L1_5400global_jJet, ak4genjetsp_jJet, "5400_calib_global_gen",false);

      this->compareJetCollections(calibrated_L1_5400donut_jJet, L1_5400donut_jJet,"5400_donut_calib_uncalib",false);
      this->compareJetCollections(calibrated_L1_5400_jJet, ak4genjetsp_jJet,"5400_nopus_calib_uncalib",false);
      this->compareJetCollections(calibrated_L1_5400global_jJet, ak4genjetsp_jJet, "5400_global_calib_uncalib",false);

      this->compareJetCollections(L1_5400donut_jJet, ak4genjetsp_jJet,"5400_donut_gen",false);
      this->compareJetCollections(L1_5400_jJet, ak4genjetsp_jJet,"5400_nopus_gen",false);
      this->compareJetCollections(L1_5400global_jJet, ak4genjetsp_jJet, "5400_global_gen",false);

      this->compareJetCollections(L1_5450donut_jJet, ak4genjetsp_jJet,"5450_donut_gen",false);
      this->compareJetCollections(L1_5450_jJet, ak4genjetsp_jJet,"5450_nopus_gen",false);
      this->compareJetCollections(L1_5450global_jJet, ak4genjetsp_jJet, "5450_global_gen",false);

      this->compareJetCollections(calibrated_L1_5450donut_jJet, ak4genjetsp_jJet,"5450_calib_donut_gen",false);
      this->compareJetCollections(calibrated_L1_5450_jJet, ak4genjetsp_jJet,"5450_calib_nopus_gen",false);
      if(mgct)
      {
      this->compareJetCollections(gct_jJet_calib, ak4genjetsp_jJet, "gct_calib_gen",true);
      this->compareJetCollections(gct_jJet_uncalib, ak4genjetsp_jJet, "gct_uncalib_gen",true);
      }
      this->compareJetCollections(L1_5420_jJet, ak4genjetsp_jJet,"5420_nopus_gen",false);
      this->compareJetCollections(L1_5430_jJet, ak4genjetsp_jJet,"5430_nopus_gen",false);
      this->compareJetCollections(L1_5440_jJet, ak4genjetsp_jJet,"5440_nopus_gen",false);
      */
  double mean_top_pt=0.;
  for (auto iTop = top_jJet.begin();iTop != top_jJet.end(); iTop++)
  {
    mean_top_pt += double(iTop->pt())/top_jJet.size();
  }
  //Means,xi, for i jets
  int x1 = 196;
  int x2 = 125;
  int x3 = 79;
  int x4 = 52;

  if (L1_5400donut_jJet.size() > 0 && L1_5400donut_jJet.at(0).pt() > x1) eff_over_x1_top->Fill(mean_top_pt);
  if (L1_5400donut_jJet.size() > 1 && L1_5400donut_jJet.at(1).pt() > x2) eff_over_x2_top->Fill(mean_top_pt);
  if (L1_5400donut_jJet.size() > 2 && L1_5400donut_jJet.at(2).pt() > x3) eff_over_x3_top->Fill(mean_top_pt);
  if (L1_5400donut_jJet.size() > 3 && L1_5400donut_jJet.at(3).pt() > x4) eff_over_x4_top->Fill(mean_top_pt);
  mean_top_pt_hist->Fill(mean_top_pt);
  //this->compareJetCollections(L1_5400donut_jJet, top_jJet,"5400_donut_top",false);
  //this->compareJetCollections(L1_5400_jJet, top_jJet,"5400_nopus_top",false);
  //this->compareJetCollections(L1_5400global_jJet, top_jJet,"5400_global_top",false);

  //this->compareJetCollections(top_jJet, L1_5400donut_jJet,"5400_top_donut",false);
  //this->compareJetCollections(top_jJet, L1_5400_jJet,"5400_top_nopus",false);
  //this->compareJetCollections(top_jJet, L1_5400global_jJet,"5400_top_global",false);

  //std::cout << mPrintMe << std::endl;
  jJetMap["L1_5400_Donut"] = L1_5400donut_jJet;
  ///   jJetMap["L1_5400_Donut_mask"] = L1_5400donut_jJet_mask;
  jJetMap["L1_4300_Donut"] = L1_4300donut_jJet;
  //  mPrintMe=true;
  if(this->mPrintMe)
  {
    std::cout << "Event Printed" << std::endl;
    printOneEvent(triggertowers, jJetMap,ak4Map,genMap);
  }
  this->mPrintMe = false;
  //CALIBRATE!!!


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
