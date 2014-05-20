#ifndef CALOTOWERANALYSER_H
#define CALOTOWERANALYSER_H

// -*- C++ -*-
//
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

//Switches
//#define COMPARE_COLLECTIONS
#define PUS_HISTS

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
#include "TProfile.h"

//Switches
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
    //std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int phisize, int etasize, int vetophisize, int vetoetasize, int seedthresh1, int seedthresh2);
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
    void setEtaBins(std::map<TString,int> etaBins);
    void setPtBins(std::map<TString,int> ptBins);
    void setNintBins(std::map<TString,int> nintBins);
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
    std::map<TString, TProfile*> pusProfile_;
    std::vector<TString> globalPusVars_;
    std::vector<TString> l1Sizes_;
    std::vector<TString> l1PusVars_;
    std::map<TString, int> etaBins_;
    std::map<TString, int> ptBins_;
    std::map<TString, int> nintBins_;

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

#endif
