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
    void compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName, bool isgct);
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
    double calculateHT(const std::vector<jJet> & jets,const int & thresh);
    std::vector<double> calculateMHT(const std::vector<jJet> & jets,const int & thresh);


  private:
    TTree* tree;
    std::map<TString, std::vector<Float_t> *> L1jetPt_;
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
    TH2D * median_rho_nvtx;


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

    std::map<std::string, TH1D * > col1_jet1_eta;
    std::map<std::string, TH1D * > col1_jet2_eta;
    std::map<std::string, TH1D * > col1_jet3_eta;
    std::map<std::string, TH1D * > col1_jet4_eta;
    std::map<std::string, TH1D * > col2_jet1_eta;
    std::map<std::string, TH1D * > col2_jet2_eta;
    std::map<std::string, TH1D * > col2_jet3_eta;
    std::map<std::string, TH1D * > col2_jet4_eta;
    std::map<std::string, TH1D * > col1_jet1_pt;
    std::map<std::string, TH1D * > col1_lead_seed;
    std::map<std::string, TH1D * > col1_jet2_pt;
    std::map<std::string, TH1D * > col1_jet3_pt;
    std::map<std::string, TH1D * > col1_jet4_pt;
    std::map<std::string, TH1D * > col1_jet5_pt;
    std::map<std::string, TH1D * > col1_jet6_pt;
    std::map<std::string, TH1D * > col1_jet7_pt;
    std::map<std::string, TH1D * > col1_jet8_pt;
    std::map<std::string, TH1D * > col1_jet9_pt;
    std::map<std::string, TH1D * > col1_jet10_pt;



    std::map<TString, TH1D * > col1_pt_eta_bins_alljet;
    std::map<TString, TH1D * > col1_pt_eta_bins_jet1;
    std::map<TString, TH1D * > col1_pt_eta_bins_jet2;
    std::map<TString, TH1D * > col1_pt_eta_bins_jet3;
    std::map<TString, TH1D * > col1_pt_eta_bins_jet4;





    std::map<std::string, TH1D * > col2_jet1_pt;
    std::map<std::string, TH1D * > col2_jet2_pt;
    std::map<std::string, TH1D * > col2_jet3_pt;
    std::map<std::string, TH1D * > col2_jet4_pt;
    std::map<std::string, TH1D * > col2_jet5_pt;
    std::map<std::string, TH1D * > col2_jet6_pt;
    std::map<std::string, TH1D * > col2_jet7_pt;
    std::map<std::string, TH1D * > col2_jet8_pt;
    std::map<std::string, TH1D * > col2_jet9_pt;
    std::map<std::string, TH1D * > col2_jet10_pt;
    std::map<std::string, TH1D * > col1_alljet_pt;
    std::map<std::string, TH1D * > col2_alljet_pt;
    std::map<std::string, TH1D * > col1_alljet_eta;
    std::map<std::string, TH1D * > col2_alljet_eta;
    std::map<std::string, TH1D * > col2_matched_algo1_alljet_pt;
    std::map<std::string, TH1D * > col2_matched_algo1_alljet_eta;
    std::map<std::string, TH2D * > col2_matched_algo1_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo1_jet1_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo1_jet2_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo1_jet3_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo1_jet4_ptcorr;
    std::map<std::string, TProfile * > col2_matched_algo1_ptres_profile;
    std::map<std::string, TH2D * > col2_matched_algo1_ptres;
    std::map<std::string, TH2D * > col2_matched_algo1_ptratio;
    std::map<std::string, TH1D * > col2_matched_algo1_jet1_pt;
    std::map<std::string, TH1D * > col2_matched_algo1_jet2_pt;
    std::map<std::string, TH1D * > col2_matched_algo1_jet3_pt;
    std::map<std::string, TH1D * > col2_matched_algo1_jet4_pt;
    std::map<std::string, TH1D * > col2_matched_algo1_jet1_eta;
    std::map<std::string, TH1D * > col2_matched_algo1_jet2_eta;
    std::map<std::string, TH1D * > col2_matched_algo1_jet3_eta;
    std::map<std::string, TH1D * > col2_matched_algo1_jet4_eta;

    std::map<std::string, TH1D * > col2_matched_algo2_alljet_pt;
    std::map<std::string, TH1D * > col2_matched_algo2_alljet_eta;
    std::map<std::string, TH2D * > col2_matched_algo2_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo2_jet1_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo2_jet2_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo2_jet3_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo2_jet4_ptcorr;
    std::map<std::string, TH2D * > col2_matched_algo2_ptres;
    std::map<std::string, TProfile * > col2_matched_algo2_ptres_profile;
    std::map<std::string, TH2D * > col2_matched_algo2_ptratio;
    std::map<std::string, TH1D * > col2_matched_algo2_jet1_pt;
    std::map<std::string, TH1D * > col2_matched_algo2_jet2_pt;
    std::map<std::string, TH1D * > col2_matched_algo2_jet3_pt;
    std::map<std::string, TH1D * > col2_matched_algo2_jet4_pt;
    std::map<std::string, TH1D * > col2_matched_algo2_jet1_eta;
    std::map<std::string, TH1D * > col2_matched_algo2_jet2_eta;
    std::map<std::string, TH1D * > col2_matched_algo2_jet3_eta;
    std::map<std::string, TH1D * > col2_matched_algo2_jet4_eta;
    //PLOTS FOR JAD
    std::map<std::string,TH2D * > col2_saved_algo2;
    std::map<std::string,TH2D * > index_matched;

    std::map<TString, TH2D * > pt_ratio_nvts_algo1_alljet;
    std::map<TString, TProfile * > pt_ratio_nvts_algo1_alljet_profile;

    std::map<TString, TH2D * > pt_ratio_nvts_algo1_jet1;
    std::map<TString, TProfile * > pt_ratio_nvts_algo1_jet1_profile;
    std::map<TString, TH2D * > pt_ratio_nvts_algo1_jet2;
    std::map<TString, TProfile * > pt_ratio_nvts_algo1_jet2_profile;
    std::map<TString, TH2D * > pt_ratio_nvts_algo1_jet3;
    std::map<TString, TProfile * > pt_ratio_nvts_algo1_jet3_profile;
    std::map<TString, TH2D * > pt_ratio_nvts_algo1_jet4;
    std::map<TString, TProfile * > pt_ratio_nvts_algo1_jet4_profile;
    std::map<TString,bool> pMade;
    //Turn ons
    std::map<TString,TH1D*> col2_matched_algo1_alljet_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet1_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet2_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet3_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet4_cut;

    std::map<TString,TH1D*> col2_matched_algo1_alljet_nvtx_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet1_nvtx_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet2_nvtx_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet3_nvtx_cut;
    std::map<TString,TH1D*> col2_matched_algo1_jet4_nvtx_cut;


    std::map<TString,TH2D*> col1_alljet_pt_NPV;
    std::map<TString,TH2D*> col1_jet1_pt_NPV;
    std::map<TString,TH2D*> col1_jet2_pt_NPV;
    std::map<TString,TH2D*> col1_jet3_pt_NPV;
    std::map<TString,TH2D*> col1_jet4_pt_NPV;
    //Calibration
    std::map<TString,TH2D*> col2_calib_ratio;
    std::map<TString,TProfile*> col2_calib_ratio_profile;
    std::map<TString,TH2D*> col2_calib_corr;
    std::map<TString,TProfile*> col2_calib_corr_profile;
    //Esums
    std::map<TString,TH1D*> col1_ht;
    std::map<TString,TH1D*> col2_ht;
    std::map<TString,TH1D*> col1_mht;
    std::map<TString,TH1D*> col2_mht;
    std::map<TString,TH1D*> col1_mht_x;
    std::map<TString,TH1D*> col2_mht_x;
    std::map<TString,TH1D*> col1_mht_y;
    std::map<TString,TH1D*> col2_mht_y;


    std::map<TString,TH2D*> col1_seed_pt_corr;
    std::map<TString,TH2D*> col1_ring01_pt_corr;
    std::map<TString,TH2D*> col1_ring01norm_pt_corr;

    std::map<TString,TH2D*> ht_resolution;
    std::map<TString,TH2D*> mht_x_resolution;
    std::map<TString,TH2D*> mht_y_resolution;
    std::map<TString,TH2D*> mht_resolution;

    std::map<TString,TH1D*> col2_ht_cut;
    std::map<TString,TH1D*> col2_mht_cut;
    std::map<TString,TH1D*> col1_et_cut;
    std::map<TString,TH1D*> col1_met_cut;
    std::map<TString,TH2D*> mht_ht_col2;
    std::map<TString,TH2D*> mht_ht_col1;
    std::map<TString,TH1D*> col1_seed_alljet;
    std::map<TString,TH1D*> col1_seed_jet1;
    std::map<TString,TH1D*> col1_seed_jet2;
    std::map<TString,TH1D*> col1_seed_jet3;
    std::map<TString,TH1D*> col1_seed_jet4;

    std::map<TString,TH2D*> col1_NPV_seed_alljet;
    std::map<TString,TH2D*> col1_NPV_seed_jet1;
    std::map<TString,TH2D*> col1_NPV_seed_jet2;
    std::map<TString,TH2D*> col1_NPV_seed_jet3;
    std::map<TString,TH2D*> col1_NPV_seed_jet4;

    std::map<TString,TH1D*> col1_rings_0_1_alljet;
    std::map<TString,TH1D*> col1_rings_0_1_jet1;
    std::map<TString,TH1D*> col1_rings_0_1_jet2;
    std::map<TString,TH1D*> col1_rings_0_1_jet3;
    std::map<TString,TH1D*> col1_rings_0_1_jet4;

    std::map<TString,TH2D*> col1_NPV_rings_0_1_alljet;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_jet1;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_jet2;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_jet3;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_jet4;

    std::map<TString,TH1D*> col1_rings_0_1_norm_alljet;
    std::map<TString,TH1D*> col1_rings_0_1_norm_jet1;
    std::map<TString,TH1D*> col1_rings_0_1_norm_jet2;
    std::map<TString,TH1D*> col1_rings_0_1_norm_jet3;
    std::map<TString,TH1D*> col1_rings_0_1_norm_jet4;

    std::map<TString,TH2D*> col1_NPV_rings_0_1_norm_alljet;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_norm_jet1;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_norm_jet2;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_norm_jet3;
    std::map<TString,TH2D*> col1_NPV_rings_0_1_norm_jet4;

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
