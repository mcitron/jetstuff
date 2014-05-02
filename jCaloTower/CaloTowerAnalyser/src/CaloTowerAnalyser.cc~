// -*- C++ -*-
//
// Package:    CaloTowerAnalyser
// Class:      CaloTowerAnalyser
// 
/**\class CaloTowerAnalyser CaloTowerAnalyser.cc jCaloTower/CaloTowerAnalyser/src/CaloTowerAnalyser.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jad Marrouche
//         Created:  Fri Jun 21 08:28:06 BST 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimDataFormats/SLHC/interface/L1CaloTower.h"
#include "SimDataFormats/SLHC/interface/L1CaloTowerFwd.h"

#include "SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"

#include "jCaloTower/CaloTowerAnalyser/interface/jad_jet_class.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/matching_algo.hh"

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include <fastjet/PseudoJet.hh>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TString.h"
#include "TH2.h"
#include "TROOT.h"
#include "TCanvas.h"

//Switches
//#define COMPARE_JET_COLLECTIONS
//
//
// class declaration
//

class CaloTowerAnalyser : public edm::EDAnalyzer {
  public:
    explicit CaloTowerAnalyser(const edm::ParameterSet&);
    ~CaloTowerAnalyser();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    void getJets(std::vector < fastjet::PseudoJet > &constits,std::vector < fastjet::PseudoJet > &jets);
    std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int phisize, int etasize, int vetophisize, int vetoetasize, int seedthresh1, int seedthresh2);
    std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int jetsize, int vetowindowsize, int seedthresh1, int seedthresh2); 
    void compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName);
    void printOneEvent(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const std::vector<jJet> & L1jets, const std::vector<fastjet::PseudoJet> & ak4ttjets, const reco::GenJetCollection * ak4genjets, std::vector<fastjet::PseudoJet> & ak4genjetsp);
    void printOneEvent(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const std::map <TString,std::vector<jJet> > & L1jets, const std::map<TString,std::vector<fastjet::PseudoJet>> & ak4jets,std::map<TString,const reco::GenJetCollection *> ak4genjets);
    std::vector<int> closestJetDistance(const std::vector<jJet> & jJets);
    void SetNPV(int NPV);
    int GetNPV();
    void setL1Sizes(std::vector<TString> l1Sizes);
    void setL1PusVars(std::vector<TString> l1Vars);
    void setGlobalPusVars(std::vector<TString> globalVars);
    void bookPusHists(TString folderName);

  private:
    bool mPrintMe=false;
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;

    //void Make2DMap(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const edm::Handle<CaloTowerCollection> calotowers, const int eventNumber);

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    //virtual void endRun(edm::Run const&, edm::EventSetup const&);
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

    // ----------member data ---------------------------
    int mEventNumber;
    int mNPV;
    std::vector<pair_info> pairs;
    TH1D * num_tops_per_event;
    TH1D * median_energy_per_event;

    std::map<TString, TH1F*> pusHists1d_;
    std::map<TString, TH2F*> pusHists2d_;
    std::vector<TString> globalPusVars_;
    std::vector<TString> l1Sizes_;
    std::vector<TString> l1PusVars_;

    TH1D * genjet_pt;
    TH2D * ntowers_vs_npv;

    TH2D * r4_vs_npv_eta1_pt3050;
    TH2D * r4_vs_npv_eta2_pt3050;
    TH2D * r4_vs_npv_eta3_pt3050;
    TH2D * r4_vs_npv_eta1_pt80100;
    TH2D * r4_vs_npv_eta2_pt80100;
    TH2D * r4_vs_npv_eta3_pt80100;

    TH2D * deltaGenL1_pT3050_eta1_v1;
    TH2D * deltaGenL1_v2;
    TH2D * deltaGenL1_v3;
    TH2D * deltaGenL1_pT3050_eta1_v4;
    TH2D * deltaGenL1_pT3050_eta2_v1;
    TH2D * deltaGenL1_pT3050_eta2_v4;
    TH2D * deltaGenL1_pT3050_eta3_v1;
    TH2D * deltaGenL1_pT3050_eta3_v4;
    TH2D * deltaGenL1_ntowers;
    TH2D * deltaGenL1_R1;
    TH2D * deltaGenL1_R2;
    TH2D * deltaGenL1_R3;
    TH2D * deltaGenL1_R4;


    TriggerTowerGeometry g; //to run the constructor -- could also make this static

    std::map<std::string, TH1D * > col1_jet1_eta;
    std::map<std::string, TH1D * > col1_jet2_eta;
    std::map<std::string, TH1D * > col1_jet3_eta;
    std::map<std::string, TH1D * > col1_jet4_eta;
    std::map<std::string, TH1D * > col2_jet1_eta;
    std::map<std::string, TH1D * > col2_jet2_eta;
    std::map<std::string, TH1D * > col2_jet3_eta;
    std::map<std::string, TH1D * > col2_jet4_eta;
    std::map<std::string, TH1D * > col1_jet1_pt;
    std::map<std::string, TH1D * > col1_jet2_pt;
    std::map<std::string, TH1D * > col1_jet3_pt;
    std::map<std::string, TH1D * > col1_jet4_pt;
    std::map<std::string, TH1D * > col2_jet1_pt;
    std::map<std::string, TH1D * > col2_jet2_pt;
    std::map<std::string, TH1D * > col2_jet3_pt;
    std::map<std::string, TH1D * > col2_jet4_pt;
    std::map<std::string, TH1D * > col1_alljet_pt;
    std::map<std::string, TH1D * > col2_alljet_pt;
    std::map<std::string, TH1D * > col1_alljet_eta;
    std::map<std::string, TH1D * > col2_alljet_eta;
    std::map<std::string, TH1D * > col2_matched_local_alljet_pt;
    std::map<std::string, TH1D * > col2_matched_local_alljet_eta;
    std::map<std::string, TH2D * > col2_matched_local_ptcorr;
    std::map<std::string, TH2D * > col2_matched_local_jet1_ptcorr;
    std::map<std::string, TH2D * > col2_matched_local_jet2_ptcorr;
    std::map<std::string, TH2D * > col2_matched_local_jet3_ptcorr;
    std::map<std::string, TH2D * > col2_matched_local_jet4_ptcorr;
    std::map<std::string, TH2D * > col2_matched_local_ptres;
    std::map<std::string, TH1D * > col2_matched_local_jet1_pt;
    std::map<std::string, TH1D * > col2_matched_local_jet2_pt;
    std::map<std::string, TH1D * > col2_matched_local_jet3_pt;
    std::map<std::string, TH1D * > col2_matched_local_jet4_pt;
    std::map<std::string, TH1D * > col2_matched_local_jet1_eta;
    std::map<std::string, TH1D * > col2_matched_local_jet2_eta;
    std::map<std::string, TH1D * > col2_matched_local_jet3_eta;
    std::map<std::string, TH1D * > col2_matched_local_jet4_eta;

    std::map<std::string, TH1D * > col2_matched_global_alljet_pt;
    std::map<std::string, TH1D * > col2_matched_global_alljet_eta;
    std::map<std::string, TH2D * > col2_matched_global_ptcorr;
    std::map<std::string, TH2D * > col2_matched_global_jet1_ptcorr;
    std::map<std::string, TH2D * > col2_matched_global_jet2_ptcorr;
    std::map<std::string, TH2D * > col2_matched_global_jet3_ptcorr;
    std::map<std::string, TH2D * > col2_matched_global_jet4_ptcorr;
    std::map<std::string, TH2D * > col2_matched_global_ptres;
    std::map<std::string, TH1D * > col2_matched_global_jet1_pt;
    std::map<std::string, TH1D * > col2_matched_global_jet2_pt;
    std::map<std::string, TH1D * > col2_matched_global_jet3_pt;
    std::map<std::string, TH1D * > col2_matched_global_jet4_pt;
    std::map<std::string, TH1D * > col2_matched_global_jet1_eta;
    std::map<std::string, TH1D * > col2_matched_global_jet2_eta;
    std::map<std::string, TH1D * > col2_matched_global_jet3_eta;
    std::map<std::string, TH1D * > col2_matched_global_jet4_eta;

};

void CaloTowerAnalyser::SetNPV(int npv) { mNPV = npv; }
int CaloTowerAnalyser::GetNPV() { return mNPV; }

void CaloTowerAnalyser::setL1Sizes(std::vector<TString> l1Sizes){
  l1Sizes_=l1Sizes;
}
void CaloTowerAnalyser::setL1PusVars(std::vector<TString> l1Vars){
  l1PusVars_=l1Vars;
}
void CaloTowerAnalyser::setGlobalPusVars(std::vector<TString> globalVars){
  globalPusVars_=globalVars;
}

void CaloTowerAnalyser::bookPusHists(TString folderName){

  edm::Service<TFileService> fs;
  TFileDirectory dir = fs->mkdir(folderName.Data());

  for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){
    pusHists1d_[*gVIt] = dir.make<TH1F>(*gVIt,";"+*gVIt,70,-0.5,69.5);
    for(std::vector<TString>::const_iterator gVIt2=gVIt+1; gVIt2!=globalPusVars_.end(); gVIt2++){
      pusHists2d_[*gVIt+"_"+*gVIt2] = dir.make<TH2F>(*gVIt+"_"+*gVIt2,";"+*gVIt+";"+*gVIt2,70,-0.5,69.5,70,-0.5,69.5);
    }
  }
  for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){
    TFileDirectory subdir = dir.mkdir(((TString)"Size_"+*l1SIt).Data());
    for(std::vector<TString>::const_iterator l1VIt=l1PusVars_.begin(); l1VIt!=l1PusVars_.end(); l1VIt++){
      pusHists1d_[*l1SIt+"_"+*l1VIt] = subdir.make<TH1F>(*l1SIt+"_"+*l1VIt,"Size "+*l1SIt+" energy "+*l1VIt, 20,-0.5,19.5);
      for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){
        TFileDirectory subsubdir = subdir.mkdir(gVIt->Data());
        pusHists2d_[*gVIt+"_"+*l1SIt+"_"+*l1VIt] = subsubdir.make<TH2F>(*gVIt+"_"+*l1SIt+"_"+*l1VIt,";"+*gVIt+";"+*l1SIt+"_"+*l1VIt,
            70,-0.5,69.5,20,-0.5,19.5);
      }
    }  
  }
}
void CaloTowerAnalyser::compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName) {

  edm::Service<TFileService> fs;
  TFileDirectory dir = fs->mkdir(folderName);

  //check initialised via means of mMapping, e.g.
  if(col1_jet1_eta.count(folderName) == 0) { col1_jet1_eta[folderName] = dir.make<TH1D>("col1_jet1_eta",";eta jet1;",57, -0.5, 56.5); }
  if(col1_jet2_eta.count(folderName) == 0) { col1_jet2_eta[folderName] = dir.make<TH1D>("col1_jet2_eta",";eta jet2;",57, -0.5, 56.5); }
  if(col1_jet3_eta.count(folderName) == 0) { col1_jet3_eta[folderName] = dir.make<TH1D>("col1_jet3_eta",";eta jet3;",57, -0.5, 56.5); }
  if(col1_jet4_eta.count(folderName) == 0) { col1_jet4_eta[folderName] = dir.make<TH1D>("col1_jet4_eta",";eta jet4;",57, -0.5, 56.5); }
  if(col2_jet1_eta.count(folderName) == 0) { col2_jet1_eta[folderName] = dir.make<TH1D>("col2_jet1_eta",";eta jet1;",57, -0.5, 56.5); }
  if(col2_jet2_eta.count(folderName) == 0) { col2_jet2_eta[folderName] = dir.make<TH1D>("col2_jet2_eta",";eta jet2;",57, -0.5, 56.5); }
  if(col2_jet3_eta.count(folderName) == 0) { col2_jet3_eta[folderName] = dir.make<TH1D>("col2_jet3_eta",";eta jet3;",57, -0.5, 56.5); }
  if(col2_jet4_eta.count(folderName) == 0) { col2_jet4_eta[folderName] = dir.make<TH1D>("col2_jet4_eta",";eta jet4;",57, -0.5, 56.5); }
  if(col1_jet1_pt.count(folderName) == 0) { col1_jet1_pt[folderName] = dir.make<TH1D>("col1_jet1_pt",";p_{T} jet1;",1000, -0.5, 999.5); }
  if(col1_jet2_pt.count(folderName) == 0) { col1_jet2_pt[folderName] = dir.make<TH1D>("col1_jet2_pt",";p_{T} jet2;",1000, -0.5, 999.5); }
  if(col1_jet3_pt.count(folderName) == 0) { col1_jet3_pt[folderName] = dir.make<TH1D>("col1_jet3_pt",";p_{T} jet3;",1000, -0.5, 999.5); }
  if(col1_jet4_pt.count(folderName) == 0) { col1_jet4_pt[folderName] = dir.make<TH1D>("col1_jet4_pt",";p_{T} jet4;",1000, -0.5, 999.5); }
  if(col2_jet1_pt.count(folderName) == 0) { col2_jet1_pt[folderName] = dir.make<TH1D>("col2_jet1_pt",";p_{T} jet1;",1000, -0.5, 999.5); }
  if(col2_jet2_pt.count(folderName) == 0) { col2_jet2_pt[folderName] = dir.make<TH1D>("col2_jet2_pt",";p_{T} jet2;",1000, -0.5, 999.5); }
  if(col2_jet3_pt.count(folderName) == 0) { col2_jet3_pt[folderName] = dir.make<TH1D>("col2_jet3_pt",";p_{T} jet3;",1000, -0.5, 999.5); }
  if(col2_jet4_pt.count(folderName) == 0) { col2_jet4_pt[folderName] = dir.make<TH1D>("col2_jet4_pt",";p_{T} jet4;",1000, -0.5, 999.5); }
  if(col1_alljet_pt.count(folderName) == 0) { col1_alljet_pt[folderName] = dir.make<TH1D>("col1_alljet_pt",";p_{T} all jets;",1000, -0.5, 999.5); }
  if(col2_alljet_pt.count(folderName) == 0) { col2_alljet_pt[folderName] = dir.make<TH1D>("col2_alljet_pt",";p_{T} all jets;",1000, -0.5, 999.5); }
  if(col1_alljet_eta.count(folderName) == 0) { col1_alljet_eta[folderName] = dir.make<TH1D>("col1_alljet_eta",";eta all jets;",57, -0.5, 56.5); }
  if(col2_alljet_eta.count(folderName) == 0) { col2_alljet_eta[folderName] = dir.make<TH1D>("col2_alljet_eta",";eta all jets;",57, -0.5, 56.5);}
  if(col2_matched_local_alljet_pt.count(folderName) == 0) { col2_matched_local_alljet_pt[folderName] = dir.make<TH1D>("col2_matched_local_alljet_pt",";p_{T} all jets matched;",1000, -0.5, 999.5); }
  if(col2_matched_local_alljet_eta.count(folderName) == 0) { col2_matched_local_alljet_eta[folderName] = dir.make<TH1D>("col2_matched_local_alljet_eta",";eta all jets matched;",57, -0.5, 56.5); }
  if(col2_matched_local_ptcorr.count(folderName) == 0) { col2_matched_local_ptcorr[folderName] = dir.make<TH2D>("col2_matched_local_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_local_ptres.count(folderName) == 0) { col2_matched_local_ptres[folderName] = dir.make<TH2D>("col2_matched_local_ptres", ";col1 pT; (col2 - col1) / col1 pT", 1000, -0.5, 999.5, 200, -10.05, 10.95); }
  if(col2_matched_local_jet1_pt.count(folderName) == 0) { col2_matched_local_jet1_pt[folderName] = dir.make<TH1D>("col2_matched_local_jet1_pt",";p_{T} jet1 matched;",1000, -0.5, 999.5); }
  if(col2_matched_local_jet2_pt.count(folderName) == 0) { col2_matched_local_jet2_pt[folderName] = dir.make<TH1D>("col2_matched_local_jet2_pt",";p_{T} jet2 matched;",1000, -0.5, 999.5); }
  if(col2_matched_local_jet3_pt.count(folderName) == 0) { col2_matched_local_jet3_pt[folderName] = dir.make<TH1D>("col2_matched_local_jet3_pt",";p_{T} jet3 matched;",1000, -0.5, 999.5); }
  if(col2_matched_local_jet4_pt.count(folderName) == 0) { col2_matched_local_jet4_pt[folderName] = dir.make<TH1D>("col2_matched_local_jet4_pt",";p_{T} jet4 matched;",1000, -0.5, 999.5); }
  if(col2_matched_local_jet1_eta.count(folderName) == 0) { col2_matched_local_jet1_eta[folderName] = dir.make<TH1D>("col2_matched_local_jet1_eta",";eta jet1 matched;",57, -0.5, 56.5); }
  if(col2_matched_local_jet2_eta.count(folderName) == 0) { col2_matched_local_jet2_eta[folderName] = dir.make<TH1D>("col2_matched_local_jet2_eta",";eta jet2 matched;",57, -0.5, 56.5); }
  if(col2_matched_local_jet3_eta.count(folderName) == 0) { col2_matched_local_jet3_eta[folderName] = dir.make<TH1D>("col2_matched_local_jet3_eta",";eta jet3 matched;",57, -0.5, 56.5); }
  if(col2_matched_local_jet4_eta.count(folderName) == 0) { col2_matched_local_jet4_eta[folderName] = dir.make<TH1D>("col2_matched_local_jet4_eta",";eta jet4 matched;",57, -0.5, 56.5); }
  if(col2_matched_local_jet1_ptcorr.count(folderName) == 0) { col2_matched_local_jet1_ptcorr[folderName] = dir.make<TH2D>("col2_matched_local_jet1_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_local_jet2_ptcorr.count(folderName) == 0) { col2_matched_local_jet2_ptcorr[folderName] = dir.make<TH2D>("col2_matched_local_jet2_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_local_jet3_ptcorr.count(folderName) == 0) { col2_matched_local_jet3_ptcorr[folderName] = dir.make<TH2D>("col2_matched_local_jet3_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_local_jet4_ptcorr.count(folderName) == 0) { col2_matched_local_jet4_ptcorr[folderName] = dir.make<TH2D>("col2_matched_local_jet4_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

  if(col2_matched_global_alljet_pt.count(folderName) == 0) { col2_matched_global_alljet_pt[folderName] = dir.make<TH1D>("col2_matched_global_alljet_pt",";p_{T} all jets matched;",1000, -0.5, 999.5); }
  if(col2_matched_global_alljet_eta.count(folderName) == 0) { col2_matched_global_alljet_eta[folderName] = dir.make<TH1D>("col2_matched_global_alljet_eta",";eta all jets matched;",57, -0.5, 56.5); }
  if(col2_matched_global_ptcorr.count(folderName) == 0) { col2_matched_global_ptcorr[folderName] = dir.make<TH2D>("col2_matched_global_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_global_ptres.count(folderName) == 0) { col2_matched_global_ptres[folderName] = dir.make<TH2D>("col2_matched_global_ptres", ";col1 pT; (col2 - col1) / col1 pT", 1000, -0.5, 999.5, 200, -10.05, 10.95); }
  if(col2_matched_global_jet1_pt.count(folderName) == 0) { col2_matched_global_jet1_pt[folderName] = dir.make<TH1D>("col2_matched_global_jet1_pt",";p_{T} jet1 matched;",1000, -0.5, 999.5); }
  if(col2_matched_global_jet2_pt.count(folderName) == 0) { col2_matched_global_jet2_pt[folderName] = dir.make<TH1D>("col2_matched_global_jet2_pt",";p_{T} jet2 matched;",1000, -0.5, 999.5); }
  if(col2_matched_global_jet3_pt.count(folderName) == 0) { col2_matched_global_jet3_pt[folderName] = dir.make<TH1D>("col2_matched_global_jet3_pt",";p_{T} jet3 matched;",1000, -0.5, 999.5); }
  if(col2_matched_global_jet4_pt.count(folderName) == 0) { col2_matched_global_jet4_pt[folderName] = dir.make<TH1D>("col2_matched_global_jet4_pt",";p_{T} jet4 matched;",1000, -0.5, 999.5); }
  if(col2_matched_global_jet1_eta.count(folderName) == 0) { col2_matched_global_jet1_eta[folderName] = dir.make<TH1D>("col2_matched_global_jet1_eta",";eta jet1 matched;",57, -0.5, 56.5); }
  if(col2_matched_global_jet2_eta.count(folderName) == 0) { col2_matched_global_jet2_eta[folderName] = dir.make<TH1D>("col2_matched_global_jet2_eta",";eta jet2 matched;",57, -0.5, 56.5); }
  if(col2_matched_global_jet3_eta.count(folderName) == 0) { col2_matched_global_jet3_eta[folderName] = dir.make<TH1D>("col2_matched_global_jet3_eta",";eta jet3 matched;",57, -0.5, 56.5); }
  if(col2_matched_global_jet4_eta.count(folderName) == 0) { col2_matched_global_jet4_eta[folderName] = dir.make<TH1D>("col2_matched_global_jet4_eta",";eta jet4 matched;",57, -0.5, 56.5); }
  if(col2_matched_global_jet1_ptcorr.count(folderName) == 0) { col2_matched_global_jet1_ptcorr[folderName] = dir.make<TH2D>("col2_matched_global_jet1_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_global_jet2_ptcorr.count(folderName) == 0) { col2_matched_global_jet2_ptcorr[folderName] = dir.make<TH2D>("col2_matched_global_jet2_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_global_jet3_ptcorr.count(folderName) == 0) { col2_matched_global_jet3_ptcorr[folderName] = dir.make<TH2D>("col2_matched_global_jet3_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
  if(col2_matched_global_jet4_ptcorr.count(folderName) == 0) { col2_matched_global_jet4_ptcorr[folderName] = dir.make<TH2D>("col2_matched_global_jet4_ptcorr", ";col1 pT;col2 pT", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

  for(unsigned int i=0; i<col1.size(); i++) {
    col1_alljet_pt[folderName]->Fill(col1[i].pt());
    col1_alljet_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));
    if(i == 0) { col1_jet1_pt[folderName]->Fill(col1[i].pt()); col1_jet1_eta[folderName]->Fill(g.new_iEta(col1[i].iEta())); }
    if(i == 1) { col1_jet2_pt[folderName]->Fill(col1[i].pt()); col1_jet2_eta[folderName]->Fill(g.new_iEta(col1[i].iEta())); }
    if(i == 2) { col1_jet3_pt[folderName]->Fill(col1[i].pt()); col1_jet3_eta[folderName]->Fill(g.new_iEta(col1[i].iEta())); }
    if(i == 3) { col1_jet4_pt[folderName]->Fill(col1[i].pt()); col1_jet4_eta[folderName]->Fill(g.new_iEta(col1[i].iEta())); }
  }
  for(unsigned int i=0; i<col2.size(); i++) {
    col2_alljet_pt[folderName]->Fill(col2[i].pt());
    col2_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
    if(i == 0) { col2_jet1_pt[folderName]->Fill(col2[i].pt()); col2_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 1) { col2_jet2_pt[folderName]->Fill(col2[i].pt()); col2_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 2) { col2_jet3_pt[folderName]->Fill(col2[i].pt()); col2_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
    if(i == 3) { col2_jet4_pt[folderName]->Fill(col2[i].pt()); col2_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
  }

  pairs = make_pairs(col1, col2);
  std::vector<int> col2_matched_index_local = analyse_pairs_local(pairs, col2.size(), 26);
  std::vector<int> col2_matched_index_global = analyse_pairs_global(pairs, col2.size(), 26);
  // std::vector<int> col2_matched_index_local = analyse_pairs_global(pairs, col2.size(), 25);
  for(unsigned int i=0; i<col2_matched_index_local.size(); i++) {
    //std::cout << "ak4genjetp with index " << i << " is matched to ak4ttjet with index " << ak4tt_matched_index[i] << std::endl;
    if(col2_matched_index_local[i] != -1) {
      col2_matched_local_alljet_pt[folderName]->Fill(col2[i].pt());
      col2_matched_local_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
      col2_matched_local_ptcorr[folderName]->Fill(col1[col2_matched_index_local[i]].pt(), col2[i].pt());
      if(col2[i].pt() > 0.0) {
        col2_matched_local_ptres[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index_local[i]].pt() / col2[i].pt()) - 1.0 );
      }

      if(i == 0) { col2_matched_local_jet1_pt[folderName]->Fill(col2[i].pt()); col2_matched_local_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_local_jet1_ptcorr[folderName]->Fill(col1[col2_matched_index_local[i]].pt(), col2[i].pt()); }
      if(i == 1) { col2_matched_local_jet2_pt[folderName]->Fill(col2[i].pt()); col2_matched_local_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_local_jet2_ptcorr[folderName]->Fill(col1[col2_matched_index_local[i]].pt(), col2[i].pt()); }
      if(i == 2) { col2_matched_local_jet3_pt[folderName]->Fill(col2[i].pt()); col2_matched_local_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_local_jet3_ptcorr[folderName]->Fill(col1[col2_matched_index_local[i]].pt(), col2[i].pt()); }
      if(i == 3) { col2_matched_local_jet4_pt[folderName]->Fill(col2[i].pt()); col2_matched_local_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_local_jet4_ptcorr[folderName]->Fill(col1[col2_matched_index_local[i]].pt(), col2[i].pt()); }

    } 
    //  else{
    //    if (col2[i].pt() > 200. && folderName =="gen_l1trigger" ) {this->mPrintMe = true; std::cout << mPrintMe << std::endl;}
    // }

  }
  for(unsigned int i=0; i<col2_matched_index_global.size(); i++) {
    //std::cout << "ak4genjetp with index " << i << " is matched to ak4ttjet with index " << ak4tt_matched_index[i] << std::endl;
    if(col2_matched_index_global[i] != -1) {
      col2_matched_global_alljet_pt[folderName]->Fill(col2[i].pt());
      col2_matched_global_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
      col2_matched_global_ptcorr[folderName]->Fill(col1[col2_matched_index_global[i]].pt(), col2[i].pt());
      if(col2[i].pt() > 0.0) {
        col2_matched_global_ptres[folderName]->Fill(col2[i].pt(), (col1[col2_matched_index_global[i]].pt() / col2[i].pt()) - 1.0 );
      }

      if(i == 0) { col2_matched_global_jet1_pt[folderName]->Fill(col2[i].pt()); col2_matched_global_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_global_jet1_ptcorr[folderName]->Fill(col1[col2_matched_index_global[i]].pt(), col2[i].pt()); }
      if(i == 1) { col2_matched_global_jet2_pt[folderName]->Fill(col2[i].pt()); col2_matched_global_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_global_jet2_ptcorr[folderName]->Fill(col1[col2_matched_index_global[i]].pt(), col2[i].pt()); }
      if(i == 2) { col2_matched_global_jet3_pt[folderName]->Fill(col2[i].pt()); col2_matched_global_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_global_jet3_ptcorr[folderName]->Fill(col1[col2_matched_index_global[i]].pt(), col2[i].pt()); }
      if(i == 3) { col2_matched_global_jet4_pt[folderName]->Fill(col2[i].pt()); col2_matched_global_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); col2_matched_global_jet4_ptcorr[folderName]->Fill(col1[col2_matched_index_global[i]].pt(), col2[i].pt()); }

    } 
    else{
      if (col2[i].pt() > 0. && folderName =="gen_l1trigger" ) {this->mPrintMe = true;}
    }

  }

  return;

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
void CaloTowerAnalyser::getJets(std::vector < fastjet::PseudoJet > &constits,std::vector < fastjet::PseudoJet > &jets) { 

  double rParam = 0.4;
  fastjet::JetDefinition jetDef(fastjet::antikt_algorithm, rParam);    
  int activeAreaRepeats = 1;
  double ghostArea = 0.01;
  double ghostEtaMax = 7.0;
  fastjet::GhostedAreaSpec fjActiveArea(ghostEtaMax,activeAreaRepeats,ghostArea);
  fastjet::AreaDefinition fjAreaDefinition( fastjet::active_area, fjActiveArea );
  fastjet::ClusterSequenceArea* thisClustering_ = new fastjet::ClusterSequenceArea(constits, jetDef, fjAreaDefinition);
  std::vector<fastjet::PseudoJet> out_jets = sorted_by_pt(thisClustering_->inclusive_jets(5.0));
  for(unsigned int i0 = 0; i0 < out_jets.size(); i0++) jets.push_back(out_jets[i0]);

  return;
}


std::vector<jJet> CaloTowerAnalyser::getL1Jets(const std::vector< std::vector<int> > & input, int jetsize, int vetowindowsize, int seedthresh1, int seedthresh2) {

  //seedthresh1 is the seedthreshold on the central tower
  //seedthresh2 is the threshold on all towers a la zero suppression
  //jetsize is the +/- number to span i.e. +/- 1 = 3x3
  //vetowindowsize is the +/- number window to look at to potentially veto the central tower

  std::vector<jJet> L1_jJets;
  TriggerTowerGeometry g;


  //std::cout << input.size() << ", " << input[0].size() << std::endl;

  for ( int i = 0; i < (int)input.size(); i++) {
    for ( int j = 0; j < (int)input[i].size(); j++) {
      //std::cout << "new: (" << i << ", " << j << ", " << input[i][j] << ")" << std::endl;
      int numtowersaboveme=0;
      int numtowersabovethresh=0;

      std::vector<int> localsums(jetsize+1,0); //to hold the ring sums (+1 for centre)
      std::vector<int> areas(jetsize+1,0); //to hold the ring areas (i.e. when we get up against the boundaries)
      std::vector<int> outerstrips(4,0); //to hold the energies in the 4 surrounding outer strips (excluding corners)

      for(int k=(i-jetsize); k<=(i+jetsize); k++) {
        for(int l=(j-jetsize); l<=(j+jetsize); l++) {
          if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
          //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;

          //make a co-ordinate transform at the phi boundary
          int newl;
          if(l < 0) { newl = l+72; } 
          else if (l > 71) { newl = l-72; } 
          else { newl = l; }

          if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }

          //to decide which ring to assign energy to
          for( int m=0; m<jetsize+1;m++) { //+1 for centre of jet
            if((abs(i-k) == m && abs(j-l) <= m) || (abs(i-k) <= m && abs(j-l) == m)) { 
              //i.e. we are now in ring m
              localsums[m] += input[k][newl]; 
              areas[m] += 1;

              if(m == jetsize) { //i.e. we are in the outer ring and want to parameterise PU
                if( (k-i) == m && abs(j-l) <= (m-1) ) { outerstrips[0] += input[k][newl]; }
                if( (i-k) == m && abs(j-l) <= (m-1) ) { outerstrips[1] += input[k][newl]; }
                if( (l-j) == m && abs(i-k) <= (m-1) ) { outerstrips[2] += input[k][newl]; }
                if( (j-l) == m && abs(i-k) <= (m-1) ) { outerstrips[3] += input[k][newl]; }
              }

              if(m > 0 && m <= vetowindowsize) { //i.e. don't compare the central tower or towers outside vetowindowsize

                if((k+l) > (i+j) ) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } }
                else if( ((k+l) == (i+j)) && (k-i) > (l-j)) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } } //this line is to break the degeneracy along the diagonal treating top left different to bottom right
                else { if(input[k][newl] >= input[i][j]) { numtowersaboveme++; } }

              }
              break; //no point continuining since can only be a member of one ring
            }
          }

        }
      }

      //now we have a jet candidate centred at i,j, with the ring energies and areas defined

      //now we have the L1 jet candidate:
      if(numtowersaboveme == 0 && input[i][j] > seedthresh1) {
        double totalenergy=0.0;
        //std::cout << "iEta: " << g.old_iEta(i) << ", iPhi: " << g.old_iPhi(j) << ", r0: " << localsums[0] <<  ", r1: " << localsums[1] << ", r2: " << localsums[2] << ", r3: " << localsums[3] << ", r4: " << localsums[4] << std::endl;
        for(int ring=0; ring < (int)localsums.size(); ring++) { totalenergy += localsums[ring]; }
        //this is with PUS:
        //for(int ring=0; ring < (int)localsums.size()-1; ring++) { totalenergy += localsums[ring]; }
        //std::sort(outerstrips.begin(),outerstrips.end());
        //totalenergy = totalenergy - (3.5 * (outerstrips[1] + outerstrips[2]));

        //this means we have a viable candidate
        if(totalenergy > 0.0) {
          L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips));
        }

      }

    }
  }

  //sort by highest pT before ending
  std::sort(L1_jJets.begin(), L1_jJets.end(), sortbypt);  

  return L1_jJets;

}

std::vector<jJet> CaloTowerAnalyser::getL1Jets(const std::vector< std::vector<int> > & input, int phisize, int etasize, int vetophisize, int vetoetasize, int seedthresh1, int seedthresh2) {

  //seedthresh1 is the seedthreshold on the central tower
  //seedthresh2 is the threshold on all towers a la zero suppression
  //jetsize is the +/- number to span i.e. +/- 1 = 3x3
  //vetowindowsize is the +/- number window to look at to potentially veto the central tower

  std::vector<jJet> L1_jJets;
  TriggerTowerGeometry g;


  //std::cout << input.size() << ", " << input[0].size() << std::endl;

  for ( int i = 0; i < (int)input.size(); i++) {
    for ( int j = 0; j < (int)input[i].size(); j++) {
      //std::cout << "new: (" << i << ", " << j << ", " << input[i][j] << ")" << std::endl;
      int numtowersaboveme=0;
      int numtowersabovethresh=0;
      int jetsize=4;
      std::vector<int> localsums(jetsize+1,0); //to hold the ring sums (+1 for centre)
      std::vector<int> areas(jetsize+1,0); //to hold the ring areas (i.e. when we get up against the boundaries)
      std::vector<int> outerstrips(4,0); //to hold the energies in the 4 surrounding outer strips (excluding corners)

      for(int k=(i-phisize); k<=(i+phisize); k++) {
        for(int l=(j-etasize); l<=(j+etasize); l++) {
          if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
          //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;

          //make a co-ordinate transform at the phi boundary
          int newl;
          if(l < 0) { newl = l+72; } 
          else if (l > 71) { newl = l-72; } 
          else { newl = l; }

          if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }

          //to decide which ring to assign energy to

          jetsize = (phisize > etasize) ? phisize:etasize;

          for( int m=0; m<jetsize+1;m++) { //+1 for centre of jet
            if((abs(i-k) == m && abs(j-l) <= m) || (abs(i-k) <= m && abs(j-l) == m)) { 
              //i.e. we are now in ring m
              localsums[m] += input[k][newl]; 
              areas[m] += 1;

              //Outer Rings
              if( (k-i) == phisize && abs(j-l) <= (etasize-1) ) { outerstrips[0] += input[k][newl]; }
              if( (i-k) == phisize && abs(j-l) <= (etasize-1) ) { outerstrips[1] += input[k][newl]; }
              if( (l-j) == etasize && abs(i-k) <= (phisize-1) ) { outerstrips[2] += input[k][newl]; }
              if( (j-l) == etasize && abs(i-k) <= (phisize-1) ) { outerstrips[3] += input[k][newl]; }

              if(m > 0 && abs(l-j) <= vetoetasize && abs(i-k) <= vetophisize) { //i.e. don't compare the central tower or towers outside vetowindowsize

                if((k+l) > (i+j) ) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } }
                else if( ((k+l) == (i+j)) && (k-i) > (l-j)) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } } //this line is to break the degeneracy along the diagonal treating top left different to bottom right
                else { if(input[k][newl] >= input[i][j]) { numtowersaboveme++; } }

              }
              break; //no point continuining since can only be a member of one ring
            }
          }

        }
      }

      //now we have a jet candidate centred at i,j, with the ring energies and areas defined

      //now we have the L1 jet candidate:
      if(numtowersaboveme == 0 && input[i][j] > seedthresh1) {
        double totalenergy=0.0;
        //std::cout << "iEta: " << g.old_iEta(i) << ", iPhi: " << g.old_iPhi(j) << ", r0: " << localsums[0] <<  ", r1: " << localsums[1] << ", r2: " << localsums[2] << ", r3: " << localsums[3] << ", r4: " << localsums[4] << std::endl;
        for(int ring=0; ring < (int)localsums.size(); ring++) { totalenergy += localsums[ring]; }
        //this is with PUS:
        //for(int ring=0; ring < (int)localsums.size()-1; ring++) { totalenergy += localsums[ring]; }
        //std::sort(outerstrips.begin(),outerstrips.end());
        //totalenergy = totalenergy - (3.5 * (outerstrips[1] + outerstrips[2]));

        //this means we have a viable candidate
        if(totalenergy > 0.0) {
          L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips));
        }

      }

    }
  }

  //sort by highest pT before ending
  std::sort(L1_jJets.begin(), L1_jJets.end(), sortbypt);  

  return L1_jJets;

}

std::vector<int> CaloTowerAnalyser::closestJetDistance(const std::vector<jJet> & jJets) {

  std::vector<int> distances(jJets.size(),-1);

  bool summary=false;

  //std::cout << "event size: " << jJets.size() << std::endl;

  if(jJets.size() > 0) { //will get distance =999 for closest distance if only 1 jet
    for(int i=0; i<(int)jJets.size(); i++) {
      int closestDR2 = 999;

      //std::cout << i << " closest to " << distances[i] << std::endl;

      for(int j=0; j<(int)jJets.size(); j++) {
        if(i!=j && jJets[i].DeltaR2(jJets[j]) < closestDR2) { closestDR2 = jJets[i].DeltaR2(jJets[j]); }
      }
      distances[i] = closestDR2;
      //std::cout << i << " closest distance " << closestDR2 << std::endl;

    }

  } else { std::cout << "no jets in collection" << std::endl; throw 1; }

  if(summary) {
    for(unsigned int i=0; i< distances.size(); i++) {
      std::cout << "jet " << i << " (" << jJets[i].pt() << ", " << jJets[i].iEta() << ", " << jJets[i].iPhi() << ") closest = " << distances[i] << std::endl; 
    }

  }

  return distances;
}

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

  // std::string folderName = "Event_";
  // std::stringstream caseNumber;
  // caseNumber << eventNumber;
  // folderName.append(caseNumber.str());
  TFileDirectory dir = fs->mkdir("global_histograms");

  TriggerTowerGeometry g; //to run the constructor -- could also make this static

  genjet_pt = dir.make<TH1D>("genjet_pt",";p_{T};",1000, -0.5, 999.5);
  //genjet_pt_nomunu_far = dir.make<TH1D>("genjet_pt_nomunu_far",";p_{T};",1000, -0.5, 999.5);
  //genjet_pt_nomunu_far_match_L1 = dir.make<TH1D>("genjet_pt_nomunu_far_match_L1",";p_{T};",1000, -0.5, 999.5);
  median_energy_per_event = dir.make<TH1D>("median_energy_per_event",";median energy per event;",100, -0.5, 99.5);
  num_tops_per_event = dir.make<TH1D>("Number of tops",";median energy per event;",100, -0.5, 99.5);

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
  mEventNumber=1;

  std::vector<TString> l1Sizes;
  l1Sizes.push_back("3");
  l1Sizes.push_back("4");
  this->setL1Sizes(l1Sizes);

  std::vector<TString> globalVars;
  globalVars.push_back("rhott");
  globalVars.push_back("rhogen");
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

  //Make the necessary histograms
  this->bookPusHists("pus_histograms");


}


CaloTowerAnalyser::~CaloTowerAnalyser()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}



//
// member functions
//

// ------------ method called for each event  ------------
  void
CaloTowerAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if (mEventNumber % 100 == 0) { std::cout << "starting event " << mEventNumber << std::endl; }


  /*
     std::cout << "at event " << mEventNumber << std::endl;

  // Get GCT jets (uncalib) collection
  edm::Handle<L1GctJetCandCollection> GctUncalibCenJets;
  edm::InputTag gctUncalibCenJets("valGctDigis","cenJets","jadtest");
  iEvent.getByLabel(gctUncalibCenJets, GctUncalibCenJets);

  for(unsigned int i=0; i<GctUncalibCenJets->size(); i++) {
  std::cout << GctUncalibCenJets->at(i).rank() << ", " << GctUncalibCenJets->at(i).regionId().ieta() << ", " << GctUncalibCenJets->at(i).regionId().iphi() << std::endl;
  }

  // Get GCT jets (uncalib) collection
  edm::Handle<L1GctJetCandCollection> GctCalibCenJets;
  edm::InputTag gctCalibCenJets("gctDigis","cenJets","jadtest");
  iEvent.getByLabel(gctCalibCenJets, GctCalibCenJets);

  for(unsigned int i=0; i<GctCalibCenJets->size(); i++) {
  std::cout << GctCalibCenJets->at(i).rank() << ", " << GctCalibCenJets->at(i).regionId().ieta() << ", " << GctCalibCenJets->at(i).regionId().iphi() << std::endl;
  }
  */


  edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers;
  iEvent.getByLabel("L1CaloTowerProducer", triggertowers);

  // Get gen jet collection
  edm::Handle<reco::GenJetCollection> hGenJetProduct;
  edm::InputTag genjetselector("ak4GenJets","","jadtest");
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

  for(unsigned int i = 0; i < genphandle->size(); i++) {
    const reco::GenParticle* p = &((*genphandle)[i]);
    if ( (p->status() == 1) && p->pt() > 0.0 && abs(p->pdgId()) != 12 && abs(p->pdgId()) != 13 && abs(p->pdgId()) != 14 && abs(p->pdgId()) != 16 && abs(p->eta()) < 3.0) {
      //std::cout << p->pdgId() << ", " << p->pt() << ", " << g.iEta(p->eta()) << ", " << g.iPhi(p->phi()) << std::endl;
      fastjet::PseudoJet curPseudoJet;
      curPseudoJet.reset_PtYPhiM( p->pt(), p->eta(), p->phi(), 0.0); //last argument is mass
      pseudoak4genjetsp.push_back(curPseudoJet);
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

  int ntowersinevent=0; //this is a container to calculate the number of non-zero towers in an event (correlation with NPV)
  std::vector<int> energies_per_event; //this is a container to calculate the median tower energy in an event
  for(l1slhc::L1CaloTowerCollection::const_iterator j=triggertowers->begin(); j!=triggertowers->end(); j++) {

    if ( abs((*j).iEta()) > 28 ) { continue; } //i.e. |eta| < 3 only

    energies_per_event.push_back((*j).E() + (*j).H()); //for median calculation
    if((*j).E() + (*j).H() > 0) { ntowersinevent++; } //to look at correlation with NPV

    myarray[g.new_iEta((*j).iEta())][g.new_iPhi((*j).iPhi())] = ((*j).E() + (*j).H());

    //so now myarray is on the scale ieta 0-56, iphi 0-71
    //std::cout << "old: (" << (*j).iEta() << ", " << (*j).iPhi() << ", " << (*j).E() + (*j).H() << ")" << std::endl;
    //std::cout << "size = " << triggertowers->size() << std::endl;

    //make ak4TT:
    fastjet::PseudoJet curPseudoJet;
    curPseudoJet.reset_PtYPhiM( ((*j).E() + (*j).H()) , g.eta((*j).iEta()), g.phi((*j).iPhi()), 0.0); //last argument is mass
    pseudoak4ttjets.push_back(curPseudoJet);
  }

  ntowers_vs_npv->Fill(ntowersinevent, this->GetNPV()); //ntowers > 0 in an event

  //now sort and calculate median of energies
  if(energies_per_event.size() > 0) {
    std::sort(energies_per_event.begin(), energies_per_event.end()); //sort the vector
    if(energies_per_event.size() % 2 == 0 ) {
      int index1 = energies_per_event.size() / 2;
      median_energy_per_event->Fill((double)(energies_per_event[index1] + energies_per_event[index1+1]) / 2.0);
    } else {
      int index1 = (int)energies_per_event.size() / 2;
      median_energy_per_event->Fill(energies_per_event[index1]);
    }
  }


  //now make the genjetsp collection (clustered based on eta<3 deposits and no muons and neutrinos)
  this->getJets(pseudoak4genjetsp, ak4genjetsp);
  //now make the ak4tt collection
  this->getJets(pseudoak4ttjets, ak4ttjets);

  fastjet::GridMedianBackgroundEstimator lGrid(5.0,0.8);
  lGrid.set_particles(pseudoak4ttjets);
  double rhoTt=lGrid.rho();

  lGrid=fastjet::GridMedianBackgroundEstimator(5.0,0.8);
  lGrid.set_particles(pseudoak4genjetsp);
  double rhoGen=lGrid.rho();


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

  /*
  //an example on how to use the closestJetDistance function
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

  this->compareJetCollections(ak4tt_jJet, ak4genjetsp_jJet, "ak4tt_ak4genjetsp");

  std::map<TString,double> globalPusVarsMap;
  globalPusVarsMap["rhott"] = rhoTt;
  globalPusVarsMap["rhogen"] = rhoGen;
  globalPusVarsMap["nint"] = mNPV;
  
  //make a container for the L1 jets
  std::vector<jJet> L1_4300_jJet = getL1Jets(myarray, 4, 3, 0, 0);
  std::vector<jJet> L1_4350_jJet = getL1Jets(myarray, 4, 3, 5, 0);
  std::vector<jJet> L1_4400_jJet = getL1Jets(myarray, 4, 4, 0, 0);
  std::vector<jJet> L1_rect_jJet = getL1Jets(myarray, 4, 4,4,4, 0, 0);
  std::vector<jJet> L1_4300donut_jJet;
  std::vector<jJet> L1_4350donut_jJet;
  std::map<TString, std::vector<jJet> > L1_jJet_map;

  //Fill the map with the sizes
  for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){
    L1_jJet_map[*l1SIt+"_out1"] = getL1Jets(myarray, atoi(l1SIt->Data())+1,atoi(l1SIt->Data()),0,0);
    L1_jJet_map[*l1SIt+"_out2"] = getL1Jets(myarray, atoi(l1SIt->Data())+2,atoi(l1SIt->Data()),0,0);
  }
  this->mPrintMe = false;
  this->compareJetCollections(L1_4400_jJet, ak4genjetsp_jJet, "gen_l1trigger");
  //std::cout << mPrintMe << std::endl;

  std::map <TString,std::vector<jJet> > jJetMap;
  std::map <TString,std::vector<fastjet::PseudoJet> > ak4Map;
  std::map <TString,const reco::GenJetCollection * > genMap;

  jJetMap["L1_4400"] = L1_4400_jJet;

  ak4Map["ak4tt"] = ak4ttjets; 
  ak4Map["ak4gen"] = ak4genjetsp; 

  genMap["genp"] = genJetCol; 

  if(this->mPrintMe)
  {
    std::cout << "Event Printed" << std::endl;
    //printOneEvent(triggertowers, L1_4400_jJet,ak4ttjets, genJetCol, ak4genjetsp);
    printOneEvent(triggertowers, jJetMap,ak4Map,genMap);
  }
  this->mPrintMe = false;
  for(unsigned int i=0; i<L1_4300_jJet.size(); i++) {
    double newenergy=L1_4300_jJet[i].eatDonut();
    if(newenergy > 0.0) { L1_4300donut_jJet.push_back(jJet(newenergy, L1_4300_jJet[i].iEta(), L1_4300_jJet[i].iPhi())); }
  }
  for(unsigned int i=0; i<L1_4350_jJet.size(); i++) {
    double newenergy=L1_4350_jJet[i].eatDonut();
    if(newenergy > 0.0) { L1_4350donut_jJet.push_back(jJet(newenergy, L1_4350_jJet[i].iEta(), L1_4350_jJet[i].iPhi())); }
  }

  this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet, "L14300_ak4genjetsp");
  this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet, "L14300donut_ak4genjetsp");
  this->compareJetCollections(L1_4350_jJet, ak4genjetsp_jJet, "L14350_ak4genjetsp");
  this->compareJetCollections(L1_4350donut_jJet, ak4genjetsp_jJet, "L14350donut_ak4genjetsp");
  this->compareJetCollections(L1_4400_jJet, ak4genjetsp_jJet, "L14400_ak4genjetsp");

  if(this->GetNPV() > 30 && this->GetNPV() <=35) { 
    this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet, "L14300_ak4genjetsp_npv3035"); 
    this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet, "L14300donut_ak4genjetsp_npv3035");
    this->compareJetCollections(L1_4350_jJet, ak4genjetsp_jJet, "L14350_ak4genjetsp_npv3035"); 
    this->compareJetCollections(L1_4350donut_jJet, ak4genjetsp_jJet, "L14350donut_ak4genjetsp_npv3035");
  } else if(this->GetNPV() > 35 && this->GetNPV() <=40) { 
    this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet, "L14300_ak4genjetsp_npv3540"); 
    this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet, "L14300donut_ak4genjetsp_npv3540");
    this->compareJetCollections(L1_4350_jJet, ak4genjetsp_jJet, "L14350_ak4genjetsp_npv3540"); 
    this->compareJetCollections(L1_4350donut_jJet, ak4genjetsp_jJet, "L14350donut_ak4genjetsp_npv3540");
  } else if(this->GetNPV() > 40 && this->GetNPV() <=45) { 
    this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet, "L14300_ak4genjetsp_npv4045"); 
    this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet, "L14300donut_ak4genjetsp_npv4045"); 
    this->compareJetCollections(L1_4350_jJet, ak4genjetsp_jJet, "L14350_ak4genjetsp_npv4045"); 
    this->compareJetCollections(L1_4350donut_jJet, ak4genjetsp_jJet, "L14350donut_ak4genjetsp_npv4045");
  } else if(this->GetNPV() > 45 && this->GetNPV() <=50) { 
    this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet, "L14300_ak4genjetsp_npv4550"); 
    this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet, "L14300donut_ak4genjetsp_npv4550");
    this->compareJetCollections(L1_4350_jJet, ak4genjetsp_jJet, "L14350_ak4genjetsp_npv4550"); 
    this->compareJetCollections(L1_4350donut_jJet, ak4genjetsp_jJet, "L14350donut_ak4genjetsp_npv4550");
  }

 for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){
    pusHists1d_[*gVIt]->Fill(globalPusVarsMap[*gVIt]);
    for(std::vector<TString>::const_iterator gVIt2=gVIt+1; gVIt2!=globalPusVars_.end(); gVIt2++){
      pusHists2d_[*gVIt+"_"+*gVIt2]->Fill(globalPusVarsMap[*gVIt],globalPusVarsMap[*gVIt2]);
    }
  }

  for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){
    for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out1"].size(); i++){
      pusHists1d_[*l1SIt+"_strip1"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0]);
      pusHists1d_[*l1SIt+"_strip2"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1]);
      pusHists1d_[*l1SIt+"_strip3"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2]);
      pusHists1d_[*l1SIt+"_strip4"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3]);
      pusHists1d_[*l1SIt+"_out1_middle2"]->Fill(L1_jJet_map[*l1SIt+"_out1"][i].PUE());
    }
    for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out2"].size(); i++){
      pusHists1d_[*l1SIt+"_strip5"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0]);
      pusHists1d_[*l1SIt+"_strip6"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1]);
      pusHists1d_[*l1SIt+"_strip7"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2]);
      pusHists1d_[*l1SIt+"_strip8"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3]);
      pusHists1d_[*l1SIt+"_out2_middle2"]->Fill(L1_jJet_map[*l1SIt+"_out2"][i].PUE());
    }
  }

  for(std::vector<TString>::const_iterator gVIt=globalPusVars_.begin(); gVIt!=globalPusVars_.end(); gVIt++){
    for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){

      for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out1"].size(); i++){
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip1"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[0]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[1]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip3"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[2]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip4"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].getOuterStrips()[3]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_out1_middle2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out1"][i].PUE());
      }
      for(unsigned i=0; i<L1_jJet_map[*l1SIt+"_out2"].size(); i++){
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip5"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[0]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip6"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[1]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip7"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[2]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_strip8"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].getOuterStrips()[3]);
        pusHists2d_[*gVIt+"_"+*l1SIt+"_out2_middle2"]->Fill(globalPusVarsMap[*gVIt],L1_jJet_map[*l1SIt+"_out2"][i].PUE());
      }
    }
  }



  this->compareJetCollections(L1_4300_jJet, ak4tt_jJet, "L14300_ak4tt");
  this->compareJetCollections(L1_4300donut_jJet, ak4tt_jJet, "L14300donut_ak4tt");
  this->compareJetCollections(L1_4400_jJet, ak4tt_jJet, "L14400_ak4tt");
  //  printOneEvent(triggertowers, L1_jJet, ak4ttjets, genJetCol, ak4genjetsp); 

  /* 
     pairs = make_pairs(L1_jJet, ak4genjetsp_jJet);
     std::sort(pairs.begin(), pairs.end(), sortDR);
     std::vector<int> ak4genjetsp_L1_matched_index = analyse_pairs(pairs, ak4genjetsp_jJet.size(), 16);

  //think about improving analyse_pairs to somehow be able to return pair 1 <--> pair2 i.e. both matched lists
  //double scale=0.5;

  for(unsigned int i=0; i<ak4genjetsp_L1_matched_index.size(); i++) {
  if(ak4genjetsp_L1_matched_index[i] != -1) {
  genjet_pt_nomunu_match_L1->Fill(ak4genjetsp_jJet[i].pt());
  genjet_eta_nomunu_match_L1->Fill(ak4genjetsp_jJet[i].iEta());
  if(i == 0) { jet1_genjet_pt_nomunu_match_L1->Fill(ak4genjetsp_jJet[i].pt()); }
  if(i == 1) { jet2_genjet_pt_nomunu_match_L1->Fill(ak4genjetsp_jJet[i].pt()); }
  if(i == 2) { jet3_genjet_pt_nomunu_match_L1->Fill(ak4genjetsp_jJet[i].pt()); }
  if(i == 3) { jet4_genjet_pt_nomunu_match_L1->Fill(ak4genjetsp_jJet[i].pt()); }

  L1_vs_genjetpt->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].pt(), ak4genjetsp_jJet[i].pt());       
  if(ak4genjetsp_jJet[i].pt() > 30.0 && ak4genjetsp_jJet[i].pt() < 50.0) {
  if(abs(ak4genjetsp_jJet[i].iEta()) < 10 && abs(ak4genjetsp_jJet[i].iEta()) >= 0) {
  deltaGenL1_pT3050_eta1_v1->Fill((ak4genjetsp_jJet[i].pt() - L1_jJet[ak4genjetsp_L1_matched_index[i]].pt()) / ak4genjetsp_jJet[i].pt(), NPV);
  } else if(abs(ak4genjetsp_jJet[i].iEta()) < 20 && abs(ak4genjetsp_jJet[i].iEta()) >= 10) {
  deltaGenL1_pT3050_eta2_v1->Fill((ak4genjetsp_jJet[i].pt() - L1_jJet[ak4genjetsp_L1_matched_index[i]].pt()) / ak4genjetsp_jJet[i].pt(), NPV);
  } else if(abs(ak4genjetsp_jJet[i].iEta()) < 30 && abs(ak4genjetsp_jJet[i].iEta()) >= 20) {
  deltaGenL1_pT3050_eta3_v1->Fill((ak4genjetsp_jJet[i].pt() - L1_jJet[ak4genjetsp_L1_matched_index[i]].pt()) / ak4genjetsp_jJet[i].pt(), NPV);
  }
  }

  if(minDR2genp[i] > 35) {
  genjet_pt_nomunu_far_match_L1->Fill(ak4genjetsp_jJet[i].pt());
  }

  if(ak4genjetsp_jJet[i].pt() < 100.0 && ak4genjetsp_jJet[i].pt() > 80.0) {
  if(abs(ak4genjetsp_jJet[i].iEta()) >= 0 && abs(ak4genjetsp_jJet[i].iEta()) < 10) { r4_vs_npv_eta1_pt80100->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].PUE(), NPV); }
  if(abs(ak4genjetsp_jJet[i].iEta()) >= 10 && abs(ak4genjetsp_jJet[i].iEta()) < 20) { r4_vs_npv_eta2_pt80100->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].PUE(), NPV); }
  if(abs(ak4genjetsp_jJet[i].iEta()) >= 20 && abs(ak4genjetsp_jJet[i].iEta()) < 30) { r4_vs_npv_eta3_pt80100->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].PUE(), NPV); }
  }
  if(ak4genjetsp_jJet[i].pt() < 50.0 && ak4genjetsp_jJet[i].pt() > 30.0) {
  if(abs(ak4genjetsp_jJet[i].iEta()) >= 0 && abs(ak4genjetsp_jJet[i].iEta()) < 10) { r4_vs_npv_eta1_pt3050->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].PUE(), NPV); }
  if(abs(ak4genjetsp_jJet[i].iEta()) >= 10 && abs(ak4genjetsp_jJet[i].iEta()) < 20) { r4_vs_npv_eta2_pt3050->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].PUE(), NPV); }
  if(abs(ak4genjetsp_jJet[i].iEta()) >= 20 && abs(ak4genjetsp_jJet[i].iEta()) < 30) { r4_vs_npv_eta3_pt3050->Fill(L1_jJet[ak4genjetsp_L1_matched_index[i]].PUE(), NPV); }
  }

  } else {
  //else , we have genjets not matched
  //check energy of genjet that's not matched. if above threshold, plot event and let's investigate
  //if(ak4genjetsp_jJet[i].pt() > 50.0 && minDR2genp[i] > 35) {
  //  std::cout << "triggered at event " << mEventNumber << ", pT " << ak4genjetsp_jJet[i].pt() << std::endl;
  //         printOneEvent(triggertowers, L1_jJet, ak4ttjets, genJetCol, ak4genjetsp);
  //}
  }
  }

  //now do the same for the L1donut jets -- PUsub can kill some jets potentially...
  pairs = make_pairs(L1donut_jJet, ak4genjetsp_jJet);
  std::sort(pairs.begin(), pairs.end(), sortDR);
  std::vector<int> ak4genjetsp_L1donut_matched_index = analyse_pairs(pairs, ak4genjetsp_jJet.size(), 16);

  for(unsigned int i=0; i<ak4genjetsp_L1donut_matched_index.size(); i++) {
  if(ak4genjetsp_L1donut_matched_index[i] != -1) {
  genjet_pt_nomunu_match_L1donut->Fill(ak4genjetsp_jJet[i].pt());
  L1donut_vs_genjetpt->Fill(L1donut_jJet[ak4genjetsp_L1donut_matched_index[i]].pt(), ak4genjetsp_jJet[i].pt()); //we can do this because we have a guarantee that L1_jJet & L1donut_jJet are the same size/position
  if(ak4genjetsp_jJet[i].pt() > 30.0 && ak4genjetsp_jJet[i].pt() < 50.0) {
  if(abs(ak4genjetsp_jJet[i].iEta()) < 10 && abs(ak4genjetsp_jJet[i].iEta()) >= 0) {
  deltaGenL1_pT3050_eta1_v4->Fill((ak4genjetsp_jJet[i].pt() - L1donut_jJet[ak4genjetsp_L1donut_matched_index[i]].pt()) / ak4genjetsp_jJet[i].pt(), NPV);
  } else if(abs(ak4genjetsp_jJet[i].iEta()) < 20 && abs(ak4genjetsp_jJet[i].iEta()) >= 10) {
  deltaGenL1_pT3050_eta2_v4->Fill((ak4genjetsp_jJet[i].pt() - L1donut_jJet[ak4genjetsp_L1donut_matched_index[i]].pt()) / ak4genjetsp_jJet[i].pt(), NPV);
  } else if(abs(ak4genjetsp_jJet[i].iEta()) < 30 && abs(ak4genjetsp_jJet[i].iEta()) >= 20) {
  deltaGenL1_pT3050_eta3_v4->Fill((ak4genjetsp_jJet[i].pt() - L1donut_jJet[ak4genjetsp_L1donut_matched_index[i]].pt()) / ak4genjetsp_jJet[i].pt(), NPV);
  }
  }

} //else , we have genjets not matched
}   
*/

//if(mEventNumber == 18 || mEventNumber == 80 || mEventNumber == 94) { printOneEvent(triggertowers, L1_4400_jJet, ak4ttjets, genJetCol, ak4genjetsp); }
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
