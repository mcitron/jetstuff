#ifndef CALOTOWERANALYSER_HH
#define CALOTOWERANALYSER_HH

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

//Switches
//#define COMPARE_COLLECTIONS

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
#include "jCaloTower/CaloTowerAnalyser/interface/mask.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/calibration_params.hh"

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
#include "TTree.h"
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
    std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int jetsize, int vetowindowsize, int seedthresh1, int seedthresh2); 
    std::vector<jJet> getL1JetsMask(const std::vector< std::vector<int> > & input, std::vector<std::vector <int> > mask, std::vector<std::vector <int > > donut_mask, int seedthresh1, int seedthresh2);
    //void compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName, bool isgct);
    void MakeJetTree(const std::vector<jJet> & col1,const std::vector<jJet> & col2,TString folderName, bool isgct);
    void MakeSumTree(const std::vector<jJet> & col1,TString folderName,bool isgct, bool iscalibgct=false);
    void MakeMatchTree(const std::vector<jJet> & col1,const std::vector<jJet> & col2,TString folderName,bool isgct);
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
    void makePusHists(const std::vector< std::vector<int> >& myarray,const std::vector<jJet>& L1_4300_jJet,const std::vector<jJet>& L1_5450_jJet);
    double getMedian(const std::vector<jJet> & jets);
    int getMedianSeed(const std::vector<jJet> & jets);
    double calculateHT(const std::vector<jJet> & jets,const int & thresh);
    std::vector<double> calculateMHT(const std::vector<jJet> & jets,const int & thresh);


  private:
    double mGctHtMissUncalib;
    double mGctHtMissCalib;
    double mGctHtCalib;
    double mGctHtUncalib;
    TTree* tree;
    std::map<TString, std::vector<Float_t> *> jetPt_;
    std::map<TString, std::vector<Float_t> *> jetPhi_;
    std::map<TString, std::vector<Float_t> *> jetEta_;
    std::map<TString, std::vector<Float_t> *> jetRing_;
    std::map<TString, std::vector<Float_t> *> jetMatchedPt_;
    std::map<TString, std::vector<Float_t> *> sums_;

    std::map<TString, std::vector<Int_t> *> genJetMatchAlgo1_;
    std::map<TString, std::vector<Int_t> *> genJetMatchAlgo2_;
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
    double mET=0;
    std::vector<double> mMET;
    std::vector<pair_info> pairs;
    TH1D * num_tops_per_event;
    TH1D * median_energy_per_event;

    TH1D * median_jet_5400_energy_per_event;
    TH1D * donut_jet_5450_energy_per_event;
    TH1D * donut_jet_iso_5450_energy_per_event;
    TH1D * number_jet_seed;
    TH1D * number_jet_median;
    TH2D * median_rho_nvtx;
    TH2D * median_rho_seed;


    std::map<TString, TH1F*> pusHists1d_;
    std::map<TString, TH2F*> pusHists2d_;
    std::map<TString, TProfile*> pusProfile_;
    std::vector<TString> globalPusVars_;
    std::vector<TString> l1Sizes_;
    std::vector<TString> l1PusVars_;
    std::map<TString, int> etaBins_;
    std::map<TString, int> ptBins_;
    std::map<TString, int> nintBins_;

    TH1D * eff_over_x1_top;
    TH1D * eff_over_x2_top;
    TH1D * eff_over_x3_top;
    TH1D * eff_over_x4_top;
    TH1D * mean_top_pt_hist;
    TH1D * met_hist;
    TH1D * et_hist;
    TH1D * met_x_hist;
    TH1D * met_y_hist;


    TH1D * genjet_pt;
    TH1D * tower_pt_real; 
    TH1D * num_tower_pt_real; 
    TH2D * tower_pt_real_jetpt; 
    TH2D * num_tower_pt_real_jetpt; 
    TH1D * tower_pt_pu; 
    TH1D * num_tower_pt_pu; 
    TH2D * tower_pt_pu_jetpt; 
    TH2D * num_tower_pt_pu_jetpt; 
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

    std::string mskim;
    bool mgct;
    TriggerTowerGeometry g; //to run the constructor -- could also make this static




    std::map<TString,bool> pMade;

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
void CaloTowerAnalyser::setEtaBins(std::map<TString,int> etaBins){
  etaBins_=etaBins;
}
void CaloTowerAnalyser::setPtBins(std::map<TString,int> ptBins){
  ptBins_=ptBins;
}
void CaloTowerAnalyser::setNintBins(std::map<TString,int> nintBins){
  nintBins_=nintBins;
}
#endif
