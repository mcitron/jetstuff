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
    std::vector<jJet> calibrateL1Jets(const std::vector<jJet>& inJets, const std::vector<double>& lut, double ptMin, double ptMax);
      std::vector<int> closestJetDistance(const std::vector<jJet> & jJets);
      void SetNPV(int NPV);
      int GetNPV();
      void setL1Sizes(std::vector<TString> l1Sizes);
      void setL1PusVars(std::vector<TString> l1Vars);
      void setGlobalPusVars(std::vector<TString> globalVars);
      void bookPusHists(TString folderName);
      double getMedian(const std::vector<jJet> & jets);

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

      TH1D * median_jet_5400_energy_per_event;
      TH2D * median_energy_5400_jet_tower_per_event;

      TH1D * median_jet_4300_energy_per_event;
      TH2D * median_energy_4300_jet_tower_per_event;

      std::map<TString, TH1F*> pusHists1d_;
      std::map<TString, TH2F*> pusHists2d_;
      std::vector<TString> globalPusVars_;
      std::vector<TString> l1Sizes_;
      std::vector<TString> l1PusVars_;

      TH1D * eff_over_x1_top;
      TH1D * eff_over_x2_top;
      TH1D * eff_over_x3_top;
      TH1D * eff_over_x4_top;
      TH1D * mean_top_pt_hist;


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
std::vector<jJet> CaloTowerAnalyser::calibrateL1Jets(const std::vector<jJet>& inJets, const std::vector<double>& lut, double ptMin, double ptMax){

  std::vector<jJet> outJets;

  for(auto iJet = inJets.begin(); iJet!=inJets.end(); iJet++){

    //If the pt of the jet is outside of the calibration range, add the jet to the calibrated jets and do nothing
    if(iJet->pt()<ptMin || iJet->pt()>ptMax){
      outJets.push_back(*iJet);
    }else{

      double p[6]; //These are the parameters of the fit
      double v[1]; //This is the pt value

      //Load the lut based on the correct eta bin
      if(iJet->iEta()>=-28 && iJet->iEta()<-17){
        p[0]=lut[0];
        p[1]=lut[1];
        p[2]=lut[2];
        p[3]=lut[3];
        p[4]=lut[4];
        p[5]=lut[5];
      }else if(iJet->iEta()>=-17 && iJet->iEta()<-6){
        p[0]=lut[6];
        p[1]=lut[7];
        p[2]=lut[8];
        p[3]=lut[9];
        p[4]=lut[10];
        p[5]=lut[11];
      }else if(iJet->iEta()>=-6 && iJet->iEta()<=6){
        p[0]=lut[12];
        p[1]=lut[13];
        p[2]=lut[14];
        p[3]=lut[15];
        p[4]=lut[16];
        p[5]=lut[17];
      }else if(iJet->iEta()>6 && iJet->iEta()<=17){
        p[0]=lut[18];
        p[1]=lut[19];
        p[2]=lut[20];
        p[3]=lut[21];
        p[4]=lut[22];
        p[5]=lut[23];
      }else if(iJet->iEta()>17 && iJet->iEta()<=28){
        p[0]=lut[24];
        p[1]=lut[25];
        p[2]=lut[26];
        p[3]=lut[27];
        p[4]=lut[28];
        p[5]=lut[29];
      }
      v[0]=iJet->pt();
      double correction=1.0*calibFit(v,p);

      jJet newJet=*iJet;
      newJet.setPt(correction*iJet->pt());

      outJets.push_back(newJet);

    }

  }
  return outJets;
}
void CaloTowerAnalyser::compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName, bool isgct) {
   std::map<TString,int> ptBins_;
   ptBins_["pt_0to20"] = 20;
   ptBins_["pt_20to40"] = 40;
   ptBins_["pt_40to60"] = 60;
   ptBins_["pt_60to80"] = 80;
   ptBins_["pt_80to100"] = 100;
   ptBins_["pt_100to120"] = 120;
   ptBins_["pt_above120"] = 999;

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

   if(col1_alljet_pt_NPV.count(folderName) == 0) { col1_alljet_pt_NPV[folderName] = dir.make<TH2D>("col1_alljet_pt_NPV",";NPV;p_{T} jet1",100,-0.5,99.5,1000, -0.5, 999.5); }
   if(col1_jet1_pt_NPV.count(folderName) == 0) { col1_jet1_pt_NPV[folderName] = dir.make<TH2D>("col1_jet1_pt_NPV",";NPV;p_{T} jet1",100,-0.5,99.5,1000, -0.5, 999.5); }
   if(col1_jet2_pt_NPV.count(folderName) == 0) { col1_jet2_pt_NPV[folderName] = dir.make<TH2D>("col1_jet2_pt_NPV",";NPV;p_{T} jet2",100,-0.5,99.5,1000, -0.5, 999.5); }
   if(col1_jet3_pt_NPV.count(folderName) == 0) { col1_jet3_pt_NPV[folderName] = dir.make<TH2D>("col1_jet3_pt_NPV",";NPV;p_{T} jet3",100,-0.5,99.5,1000, -0.5, 999.5); }
   if(col1_jet4_pt_NPV.count(folderName) == 0) { col1_jet4_pt_NPV[folderName] = dir.make<TH2D>("col1_jet4_pt_NPV",";NPV;p_{T} jet4",100,-0.5,99.5,1000, -0.5, 999.5); }

   if(col2_jet1_pt.count(folderName) == 0) { col2_jet1_pt[folderName] = dir.make<TH1D>("col2_jet1_pt",";p_{T} jet1;",1000, -0.5, 999.5); }
   if(col2_jet2_pt.count(folderName) == 0) { col2_jet2_pt[folderName] = dir.make<TH1D>("col2_jet2_pt",";p_{T} jet2;",1000, -0.5, 999.5); }
   if(col2_jet3_pt.count(folderName) == 0) { col2_jet3_pt[folderName] = dir.make<TH1D>("col2_jet3_pt",";p_{T} jet3;",1000, -0.5, 999.5); }
   if(col2_jet4_pt.count(folderName) == 0) { col2_jet4_pt[folderName] = dir.make<TH1D>("col2_jet4_pt",";p_{T} jet4;",1000, -0.5, 999.5); }

   if(col1_alljet_pt.count(folderName) == 0) { col1_alljet_pt[folderName] = dir.make<TH1D>("col1_alljet_pt",";p_{T} all jets;",1000, -0.5, 999.5); }
   if(col2_alljet_pt.count(folderName) == 0) { col2_alljet_pt[folderName] = dir.make<TH1D>("col2_alljet_pt",";p_{T} all jets;",1000, -0.5, 999.5); }
   if(col1_alljet_eta.count(folderName) == 0) { col1_alljet_eta[folderName] = dir.make<TH1D>("col1_alljet_eta",";eta all jets;",57, -0.5, 56.5); }
   if(col2_alljet_eta.count(folderName) == 0) { col2_alljet_eta[folderName] = dir.make<TH1D>("col2_alljet_eta",";eta all jets;",57, -0.5, 56.5);}

   if(col2_matched_algo1_alljet_pt.count(folderName) == 0) { col2_matched_algo1_alljet_pt[folderName] = dir.make<TH1D>("col2_matched_algo1_alljet_pt",";p_{T} all jets matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo1_alljet_eta.count(folderName) == 0) { col2_matched_algo1_alljet_eta[folderName] = dir.make<TH1D>("col2_matched_algo1_alljet_eta",";eta all jets matched;",57, -0.5, 56.5); }
   if(col2_matched_algo1_ptcorr.count(folderName) == 0) { col2_matched_algo1_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo1_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

   if(col2_matched_algo1_ptres_profile.count(folderName) == 0) { col2_matched_algo1_ptres_profile[folderName] = dir.make<TProfile>("col2_matched_algo1_ptres_profile", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5); }
   if(col2_matched_algo1_ptres.count(folderName) == 0) { col2_matched_algo1_ptres[folderName] = dir.make<TH2D>("col2_matched_algo1_ptres", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }

   if(col2_matched_algo1_ptratio.count(folderName) == 0) { col2_matched_algo1_ptratio[folderName] = dir.make<TH2D>("col2_matched_algo1_ptratio", ";col2 p_{T}; (col1) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }
   if(col2_matched_algo1_jet1_pt.count(folderName) == 0) { col2_matched_algo1_jet1_pt[folderName] = dir.make<TH1D>("col2_matched_algo1_jet1_pt",";p_{T} jet1 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet2_pt.count(folderName) == 0) { col2_matched_algo1_jet2_pt[folderName] = dir.make<TH1D>("col2_matched_algo1_jet2_pt",";p_{T} jet2 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet3_pt.count(folderName) == 0) { col2_matched_algo1_jet3_pt[folderName] = dir.make<TH1D>("col2_matched_algo1_jet3_pt",";p_{T} jet3 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet4_pt.count(folderName) == 0) { col2_matched_algo1_jet4_pt[folderName] = dir.make<TH1D>("col2_matched_algo1_jet4_pt",";p_{T} jet4 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet1_eta.count(folderName) == 0) { col2_matched_algo1_jet1_eta[folderName] = dir.make<TH1D>("col2_matched_algo1_jet1_eta",";eta jet1 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo1_jet2_eta.count(folderName) == 0) { col2_matched_algo1_jet2_eta[folderName] = dir.make<TH1D>("col2_matched_algo1_jet2_eta",";eta jet2 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo1_jet3_eta.count(folderName) == 0) { col2_matched_algo1_jet3_eta[folderName] = dir.make<TH1D>("col2_matched_algo1_jet3_eta",";eta jet3 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo1_jet4_eta.count(folderName) == 0) { col2_matched_algo1_jet4_eta[folderName] = dir.make<TH1D>("col2_matched_algo1_jet4_eta",";eta jet4 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo1_jet1_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet1_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo1_jet1_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet2_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet2_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo1_jet2_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet3_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet3_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo1_jet3_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo1_jet4_ptcorr.count(folderName) == 0) { col2_matched_algo1_jet4_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo1_jet4_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo2_alljet_pt.count(folderName) == 0) { col2_matched_algo2_alljet_pt[folderName] = dir.make<TH1D>("col2_matched_algo2_alljet_pt",";p_{T} all jets matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo2_alljet_eta.count(folderName) == 0) { col2_matched_algo2_alljet_eta[folderName] = dir.make<TH1D>("col2_matched_algo2_alljet_eta",";eta all jets matched;",57, -0.5, 56.5); }
   if(col2_matched_algo2_ptcorr.count(folderName) == 0) { col2_matched_algo2_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo2_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

   if(col2_matched_algo2_ptres_profile.count(folderName) == 0) { col2_matched_algo2_ptres_profile[folderName] = dir.make<TProfile>("col2_matched_algo2_ptres_profile", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5); }
   if(col2_matched_algo2_ptres.count(folderName) == 0) { col2_matched_algo2_ptres[folderName] = dir.make<TH2D>("col2_matched_algo2_ptres", ";col2 p_{T}; (col1 - col2) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }

   if(col2_matched_algo2_ptratio.count(folderName) == 0) { col2_matched_algo2_ptratio[folderName] = dir.make<TH2D>("col2_matched_algo2_ptratio", ";col2 p_{T}; (col1) / col2 p_{T}", 1000, -0.5, 999.5, 200, -10.05, 10.95); }
   if(col2_matched_algo2_jet1_pt.count(folderName) == 0) { col2_matched_algo2_jet1_pt[folderName] = dir.make<TH1D>("col2_matched_algo2_jet1_pt",";p_{T} jet1 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet2_pt.count(folderName) == 0) { col2_matched_algo2_jet2_pt[folderName] = dir.make<TH1D>("col2_matched_algo2_jet2_pt",";p_{T} jet2 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet3_pt.count(folderName) == 0) { col2_matched_algo2_jet3_pt[folderName] = dir.make<TH1D>("col2_matched_algo2_jet3_pt",";p_{T} jet3 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet4_pt.count(folderName) == 0) { col2_matched_algo2_jet4_pt[folderName] = dir.make<TH1D>("col2_matched_algo2_jet4_pt",";p_{T} jet4 matched;",1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet1_eta.count(folderName) == 0) { col2_matched_algo2_jet1_eta[folderName] = dir.make<TH1D>("col2_matched_algo2_jet1_eta",";eta jet1 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo2_jet2_eta.count(folderName) == 0) { col2_matched_algo2_jet2_eta[folderName] = dir.make<TH1D>("col2_matched_algo2_jet2_eta",";eta jet2 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo2_jet3_eta.count(folderName) == 0) { col2_matched_algo2_jet3_eta[folderName] = dir.make<TH1D>("col2_matched_algo2_jet3_eta",";eta jet3 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo2_jet4_eta.count(folderName) == 0) { col2_matched_algo2_jet4_eta[folderName] = dir.make<TH1D>("col2_matched_algo2_jet4_eta",";eta jet4 matched;",57, -0.5, 56.5); }
   if(col2_matched_algo2_jet1_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet1_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo2_jet1_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet2_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet2_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo2_jet2_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet3_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet3_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo2_jet3_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_matched_algo2_jet4_ptcorr.count(folderName) == 0) { col2_matched_algo2_jet4_ptcorr[folderName] = dir.make<TH2D>("col2_matched_algo2_jet4_ptcorr", ";col1 p_{T};col2 p_{T}", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }
   if(col2_saved_algo2.count(folderName) == 0) { col2_saved_algo2[folderName] = dir.make<TH2D>("col2_saved_algo2",";col2 p_{T};Max Matched p_{T};", 1000, -0.5, 999.5, 1000, -0.5, 999.5); }

   //Calibration Plots

   //New plots
   //Loop over Pt bins
   if(pMade.count(folderName) ==0)
   {
      TFileDirectory calibdir=dir.mkdir("calibration");

      //for(std::map<TString,std::pair<int,int> >::const_iterator etaBinIt=etaCalibBins_.begin(); etaBinIt!=etaCalibBins_.end(); etaBinIt++){
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
	 col2_matched_algo1_alljet_cut[TString(folderName)+ptCutIt->first]=dir.make<TH1D>("col2_matched_algo1_alljet_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
	 col2_matched_algo1_jet1_cut[TString(folderName)+ptCutIt->first]=dir.make<TH1D>("col2_matched_algo1_jet1_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
	 col2_matched_algo1_jet2_cut[TString(folderName)+ptCutIt->first]=dir.make<TH1D>("col2_matched_algo1_jet2_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
	 col2_matched_algo1_jet3_cut[TString(folderName)+ptCutIt->first]=dir.make<TH1D>("col2_matched_algo1_jet3_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);
	 col2_matched_algo1_jet4_cut[TString(folderName)+ptCutIt->first]=dir.make<TH1D>("col2_matched_algo1_jet4_cut_"+ptCutIt->first,";p_{T};",1000,-0.5,999.5);

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

   for(unsigned int i=0; i<col1.size(); i++) {
      col1_alljet_pt[folderName]->Fill(col1[i].pt());
      col1_alljet_pt_NPV[folderName]->Fill(mNPV,col1[i].pt());
      col1_alljet_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));
      if(i == 0) { col1_jet1_pt[folderName]->Fill(col1[i].pt()); col1_jet1_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet1_pt_NPV[folderName]->Fill(mNPV,col1[i].pt()); }
      if(i == 1) { col1_jet2_pt[folderName]->Fill(col1[i].pt()); col1_jet2_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet2_pt_NPV[folderName]->Fill(mNPV,col1[i].pt()); }
      if(i == 2) { col1_jet3_pt[folderName]->Fill(col1[i].pt()); col1_jet3_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet3_pt_NPV[folderName]->Fill(mNPV,col1[i].pt()); }
      if(i == 3) { col1_jet4_pt[folderName]->Fill(col1[i].pt()); col1_jet4_eta[folderName]->Fill(g.new_iEta(col1[i].iEta()));col1_jet4_pt_NPV[folderName]->Fill(mNPV,col1[i].pt()); }
   }
   for(unsigned int i=0; i<col2.size(); i++) {
      col2_alljet_pt[folderName]->Fill(col2[i].pt());
      col2_alljet_eta[folderName]->Fill(g.new_iEta(col2[i].iEta()));
      if(i == 0) { col2_jet1_pt[folderName]->Fill(col2[i].pt()); col2_jet1_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
      if(i == 1) { col2_jet2_pt[folderName]->Fill(col2[i].pt()); col2_jet2_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
      if(i == 2) { col2_jet3_pt[folderName]->Fill(col2[i].pt()); col2_jet3_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
      if(i == 3) { col2_jet4_pt[folderName]->Fill(col2[i].pt()); col2_jet4_eta[folderName]->Fill(g.new_iEta(col2[i].iEta())); }
   }
   pairs = (isgct) ? make_gct_pairs(col1,col2) : make_pairs(col1, col2);
   std::vector<int> col2_matched_index = analyse_pairs_local(pairs, col2.size(), 33);
   //std::vector<int> col1_matched_index_local = analyse_pairs_global(pairs, col2.size(), 25);
   for(unsigned int i=0; i<col2_matched_index.size(); i++) {
      //std::cout << "ak4genjetp with index " << i << " is matched to ak4ttjet with index " << ak4tt_matched_index[i] << std::endl;
      if(col2_matched_index[i] != -1) {
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
   delete thisClustering_;
   for(unsigned int i0 = 0; i0 < out_jets.size(); i0++) jets.push_back(out_jets[i0]);

   return;
}
double CaloTowerAnalyser::getMedian(const std::vector<jJet> & jets)
{
   //std::sort(jets.begin(),jets.end(),sortbyrho);
   std::vector<jJet> jetSort=jets;
   std::sort(jetSort.begin(),jetSort.end(), sortbyrho);  
   double median_energy=0.;
   if(jetSort.size() > 2) {
      if(jetSort.size() % 2 == 0 ) {
	 int index1 = jetSort.size() / 2;
	 median_energy=((double)((double)jetSort.at(index1).pt()/(double)jetSort.at(index1).area() + (double)jetSort.at(index1+1).pt()/(double)jetSort.at(index1+1).area()))/2.0;
      } else {
	 int index1 = (int)jetSort.size() / 2;
	 median_energy=((double)jetSort.at(index1).pt()/(double)jetSort.at(index1).area());
      }
   }
   return median_energy;

}
///MASK VERSION

std::vector<jJet> CaloTowerAnalyser::getL1JetsMask(const std::vector< std::vector<int> > & input, std::vector<std::vector< int > > mask, std::vector<std::vector< int > > mask_donut, int seedthresh1, int seedthresh2) {
   //seedthresh1 is the seedthreshold on the central tower
   //seedthresh2 is the threshold on all towers a la zero suppression
   //jetsize is the +/- number to span i.e. +/- 1 = 3x3
   /////vetowindowsize is the +/- number window to look at to potentially veto the central tower
   /////THIS MUST CHANGE
   std::vector<jJet> L1_jJets;
   TriggerTowerGeometry g;
   int etasize=(mask.size()-1)/2;
   int phisize=(mask.at(0).size()-1)/2;
   int nringsveto =etasize;

   int etasizedonut=(mask_donut.size()-1)/2;
   int phisizedonut=(mask_donut.at(0).size()-1)/2;
   int nstripsdonut =4;
   /////////////////
   //std::cout << input.size() << ", " << input[0].size() << std::endl;
   for ( int i = 0; i < (int)input.size(); i++) {
      for ( int j = 0; j < (int)input[i].size(); j++) {
	 std::vector<int> jetTower;
	 //std::cout << "new: (" << i << ", " << j << ", " << input[i][j] << ")" << std::endl;
	 int numtowersaboveme=0;
	 int numtowersabovethresh=0;

	 std::vector<int> localsums(nringsveto+1,0); //to hold the ring sums (+1 for centre)
	 std::vector<int> areas(nringsveto+1,0); //to hold the ring areas (i.e. when we get up against the boundaries)
	 std::vector<int> outerstrips(nstripsdonut,0); //to hold the energies in the 4 surrounding outer strips (excluding corners)
	 areas[0]=1;
	 int jetarea = 1;
	 int pusarea=0;
	 for(int l=(j-phisizedonut); l<=(j+phisizedonut); l++) {
	    for(int k=(i-etasizedonut); k<=(i+etasizedonut); k++) {
	       if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
	       //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;
	       unsigned int dk = k-i+etasizedonut;
	       unsigned int dl = l-j+phisizedonut;


		  //	       std::cout << dk << std::endl;
		  //	       std::cout << dl << std::endl;
		  //make a co-ordinate transform at the phi boundary
		  int newl;
	       if(l < 0) { newl = l+72; } 
	       else if (l > 71) { newl = l-72; } 
	       else { newl = l; }

	       if (l != j && k != i)
	       {
		  jetTower.push_back(input[k][newl]);
	       }
	       if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }
	       if(dl < mask_donut.size() && dk < mask_donut.at(0).size())
	       {
		  if(mask_donut[dl][dk] != 0)
		  {
		     outerstrips[mask_donut[dl][dk]-1]+=input[k][newl];
		     pusarea++;
	//	     std::cout << mask_donut[dl][dk];
		  }
	       }

	    }
	    //std::cout << std::endl;
	 }
	    //std::cout << std::endl;
	 for(int l=(j-phisize); l<=(j+phisize); l++) {
	    for(int k=(i-etasize); k<=(i+etasize); k++) {
	       unsigned int dk = k-i+etasize;
	       unsigned int dl = l-j+phisize;
	       if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
	       //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;
	       //	       std::cout << dk << std::endl;
	       //	       std::cout << dl << std::endl;
	       //make a co-ordinate transform at the phi boundary
	       int newl;
	       if(l < 0) { newl = l+72; } 
	       else if (l > 71) { newl = l-72; } 
	       else { newl = l; }

	       if (l != j && k != i)
	       {
		  jetTower.push_back(input[k][newl]);
	       }
	       if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }
	       if(dl < mask.size() && dk < mask.at(0).size())
	       {
		  if (mask[dl][dk] == 2){if(input[k][newl]>input[i][j]) {numtowersaboveme++;}}
		  else if (mask[dl][dk] == 1){if(input[k][newl]>=input[i][j]) {numtowersaboveme++;}}
		  /*
		     if((k+l) > (i+j) ) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } }
		     else if( ((k+l) == (i+j)) && (k-i) > (l-j)) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } } //this line is to break the degeneracy along the diagonal treating top left different to bottom right
		     else { if(input[k][newl] >= input[i][j]) { numtowersaboveme++; } }
		   */
		  for( int m=0; m<nringsveto+1;m++) { //+1 for centre of jet (n steps is n+1 rings!)
		     if((abs(i-k) == m && abs(j-l) <= m) || (abs(i-k) <= m && abs(j-l) == m)) { 
			//i.e. we are now in ring m
			localsums[m] += input[k][newl]; 
			if (mask[dl][dk] != 0) {areas[m] += 1; jetarea++;}
			break; //no point continuining since can only be a member of one ring
		     }
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
	    if(totalenergy > 0.0) {
//TEMP
	       areas.at(areas.size()-1)=pusarea;

//TEMP
	       L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips,jetTower,jetarea,pusarea));
	    }

	 }

      }
   }
   //sort by highest pT before ending
   std::sort(L1_jJets.begin(), L1_jJets.end(), sortbypt);  

   return L1_jJets;

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
	 std::vector<int> jetTower;
	 //std::cout << "new: (" << i << ", " << j << ", " << input[i][j] << ")" << std::endl;
	 int numtowersaboveme=0;
	 int numtowersabovethresh=0;

	 std::vector<int> localsums(jetsize+1,0); //to hold the ring sums (+1 for centre)
	 std::vector<int> areas(jetsize+1,0); //to hold the ring areas (i.e. when we get up against the boundaries)
	 std::vector<int> outerstrips(4,0); //to hold the energies in the 4 surrounding outer strips (excluding corners)
	 int jetarea = 1;
	 int pusarea = 0;
	 for(int k=(i-jetsize); k<=(i+jetsize); k++) {
	    for(int l=(j-jetsize); l<=(j+jetsize); l++) {
	       if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
	       //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;

	       //make a co-ordinate transform at the phi boundary
	       int newl;
	       if(l < 0) { newl = l+72; } 
	       else if (l > 71) { newl = l-72; } 
	       else { newl = l; }
	       if (l != j && k != i)
	       {
		  jetTower.push_back(input[k][newl]);
	       }
	       if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }

	       //to decide which ring to assign energy to
	       for( int m=0; m<jetsize+1;m++) { //+1 for centre of jet (n steps is n+1 rings!)
		  if((abs(i-k) == m && abs(j-l) <= m) || (abs(i-k) <= m && abs(j-l) == m)) { 
		     //i.e. we are now in ring m
		     if (m <= vetowindowsize) localsums[m] += input[k][newl]; 
		     areas[m]+=1;
		     if(m == jetsize) { //i.e. we are in the outer ring and want to parameterise PU
			if( (k-i) == m && abs(j-l) <= (m-1) ) { outerstrips[0] += input[k][newl];pusarea++; }
			if( (i-k) == m && abs(j-l) <= (m-1) ) { outerstrips[1] += input[k][newl];pusarea++; }
			if( (l-j) == m && abs(i-k) <= (m-1) ) { outerstrips[2] += input[k][newl];pusarea++; }
			if( (j-l) == m && abs(i-k) <= (m-1) ) { outerstrips[3] += input[k][newl];pusarea++; }
		     }

		     if(m > 0 && m <= vetowindowsize) { //i.e. don't compare the central tower or towers outside vetowindowsize
			jetarea++;
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
	       L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips,jetTower,jetarea,pusarea));
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
   median_energy_5400_jet_tower_per_event = dir.make<TH2D>("median_energy_jet_tower_per_event",";median tower;median jet",100, -0.5, 99.5,100,-0.5,99.5);

   median_jet_4300_energy_per_event = dir.make<TH1D>("median_jet_energy_per_event",";median energy per event;",100, -0.5, 99.5);
   median_energy_4300_jet_tower_per_event = dir.make<TH2D>("median_energy_jet_tower_per_event",";median tower;median jet",100, -0.5, 99.5,100,-0.5,99.5);

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
   //std::cout <<"EVENT " << mEventNumber << std::endl;
   if (mEventNumber % 100 == 0) { std::cout << "starting event " << mEventNumber << std::endl; }



   //    std::cout << "at event " << mEventNumber << std::endl;

   // Get GCT jets (uncalib) collection
   edm::Handle<L1GctJetCandCollection> GctUncalibCenJets;
   edm::InputTag gctUncalibCenJets("valGctDigis","cenJets","skimrun");
   //edm::InputTag gctUncalibCenJets("valGctDigis","cenJets","jadtest");
   iEvent.getByLabel(gctUncalibCenJets, GctUncalibCenJets);
   std::vector<jJet> gct_jJet;
   for(unsigned int i=0; i<GctUncalibCenJets->size(); i++) {
      if (GctUncalibCenJets->at(i).bx()==0)
      {
	 //std::cout << GctUncalibCenJets->at(i).rank() << ", " << GctUncalibCenJets->at(i).regionId().ieta() << ", " << GctUncalibCenJets->at(i).regionId().iphi() << std::endl;
	 gct_jJet.push_back(jJet(GctUncalibCenJets->at(i).rank()*8,GctUncalibCenJets->at(i).regionId().ieta(),GctUncalibCenJets->at(i).regionId().iphi(),GctUncalibCenJets->at(i).bx()));
      } 
   }

   /*
   // Get GCT jets (calib) collection
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
   edm::InputTag genjetselector("ak4GenJets","","skimrun");
   // edm::InputTag genjetselector("ak4GenJets","","jadtest");
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


   std::map<TString,double> globalPusVarsMap;
   globalPusVarsMap["rhott"] = rhoTt;
   globalPusVarsMap["rhogen"] = rhoGen;
   globalPusVarsMap["nint"] = mNPV;

   //Testing discriminator
   std::vector<jJet> L1_5400_real_jJet;
   std::vector<jJet> L1_5400_pu_jJet;

   std::vector<jJet> L1_4300_real_jJet;
   std::vector<jJet> L1_4300_pu_jJet;

   //make a container for the L1 jets
   //std::vector<jJet> L1_4300_jJet = getL1Jets(myarray, 4, 3, 0, 0);
   //std::vector<jJet> L1_4350_jJet = getL1Jets(myarray, 4, 3, 5, 0);
   std::vector<jJet> L1_5400_jJet = getL1Jets(myarray, 5, 4, 0, 0);
   std::vector<jJet> L1_5450_jJet = getL1Jets(myarray, 5, 4, 5, 0);
   std::vector<jJet> L1_6550_jJet = getL1Jets(myarray, 6, 5, 5, 0);
   std::vector<jJet> L1_4300_jJet = getL1Jets(myarray, 4, 3, 0, 0);

   //std::vector<std::vector<int> > mask=mask_square_9by9();
   //std::vector<std::vector<int> > mask_donut=mask_donut_11by11();

   //std::vector<jJet> L1_5400_jJet_mask = getL1JetsMask(myarray, mask, mask_donut, 0, 0);
   //std::vector<jJet> L1_5400donut_jJet_mask; 
   std::vector<jJet> L1_4300donut_jJet;
   std::vector<jJet> L1_4350donut_jJet;
   std::vector<jJet> L1_5400donut_jJet;
   std::vector<jJet> L1_5400global_jJet;
   std::vector<jJet> L1_5450donut_jJet;
   std::vector<jJet> L1_5450global_jJet;

   //std::vector<jJet> L1_4300donut_jJet;
   std::vector<jJet> L1_4300global_jJet;


   std::map<TString, std::vector<jJet> > L1_jJet_map;
   double median_jet_5400 = getMedian(L1_5400_jJet);
   double median_jet_5450 = getMedian(L1_5450_jJet);
   double median_jet_4300 = getMedian(L1_4300_jJet);
   median_jet_5400_energy_per_event->Fill(median_jet_5400);
   median_jet_4300_energy_per_event->Fill(median_jet_5400);
   median_energy_5400_jet_tower_per_event->Fill(median_tower,median_jet_5400);
   median_energy_4300_jet_tower_per_event->Fill(median_tower,median_jet_4300);

   //Fill the map with the sizes
   for(std::vector<TString>::const_iterator l1SIt=l1Sizes_.begin(); l1SIt!=l1Sizes_.end(); l1SIt++){
      L1_jJet_map[*l1SIt+"_out1"] = getL1Jets(myarray, atoi(l1SIt->Data())+1,atoi(l1SIt->Data()),0,0);
      L1_jJet_map[*l1SIt+"_out2"] = getL1Jets(myarray, atoi(l1SIt->Data())+2,atoi(l1SIt->Data()),0,0);
   }

   std::map <TString,std::vector<jJet> > jJetMap;
   std::map <TString,std::vector<fastjet::PseudoJet> > ak4Map;
   std::map <TString,const reco::GenJetCollection * > genMap;

   jJetMap["L1_5400"] = L1_5400_jJet;
   //jJetMap["L1_5400_mask"] = L1_5400_jJet_mask;

   ak4Map["ak4tt"] = ak4ttjets; 
   ak4Map["ak4gen"] = ak4genjetsp; 

   genMap["genp"] = genJetCol;

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
/*   for(unsigned int i=0; i<L1_5400_jJet_mask.size(); i++) {
      double newenergydonut5400=L1_5400_jJet_mask[i].eatDonut();

      if(newenergydonut5400 >= 0.0) { 
	 L1_5400donut_jJet_mask.push_back(jJet(newenergydonut5400, L1_5400_jJet_mask[i].iEta(), L1_5400_jJet_mask[i].iPhi()));
      }
   }*/
   for(unsigned int i=0; i<L1_4300_jJet.size(); i++) {
      double newenergydonut4300=L1_4300_jJet[i].eatDonut();
      double newenergyglobal4300=L1_4300_jJet[i].eatGlobe(median_jet_4300);
      if(newenergydonut4300 >= 0.0) { 
	 L1_4300donut_jJet.push_back(jJet(newenergydonut4300, L1_4300_jJet[i].iEta(), L1_4300_jJet[i].iPhi()));
	 L1_4300_real_jJet.push_back(L1_4300_jJet[i]);
      }
      else
      {
	 L1_4300_pu_jJet.push_back(L1_4300_jJet[i]);
      }
      if(newenergyglobal4300 >= 0.0) {
	 L1_4300global_jJet.push_back(jJet(newenergyglobal4300, L1_4300_jJet[i].iEta(), L1_4300_jJet[i].iPhi())); 

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
   //Calibration
   std::vector<jJet> calibrated_L1_5400_jJet = calibrateL1Jets(L1_5400_jJet,getLut(jetType::nopus),0,9999);
   std::vector<jJet> calibrated_L1_5400global_jJet = calibrateL1Jets(L1_5400global_jJet,getLut(jetType::global),0,9999);
   std::vector<jJet> calibrated_L1_5400donut_jJet = calibrateL1Jets(L1_5400donut_jJet,getLut(jetType::donut),0,9999);
   //this->mPrintMe = false;
   
      this->compareJetCollections(L1_5400donut_jJet, ak4genjetsp_jJet,"5400_donut_gen",false);
      this->compareJetCollections(L1_5400_jJet, ak4genjetsp_jJet,"5400_nopus_gen",false);
      this->compareJetCollections(L1_5400global_jJet, ak4genjetsp_jJet, "5400_global_gen",false);

      this->compareJetCollections(calibrated_L1_5400donut_jJet, ak4genjetsp_jJet,"5400_calib_donut_gen",false);
      this->compareJetCollections(calibrated_L1_5400_jJet, ak4genjetsp_jJet,"5400_calib_nopus_gen",false);
      this->compareJetCollections(calibrated_L1_5400global_jJet, ak4genjetsp_jJet, "5400_calib_global_gen",false);

      this->compareJetCollections(calibrated_L1_5400donut_jJet, L1_5400donut_jJet,"5400_donut_calib_uncalib",false);
      this->compareJetCollections(calibrated_L1_5400_jJet, ak4genjetsp_jJet,"5400_nopus_calib_uncalib",false);
      this->compareJetCollections(calibrated_L1_5400global_jJet, ak4genjetsp_jJet, "5400_global_calib_uncalib",false);
/*
      this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet,"4300_donut_gen",false);
      this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet,"4300_nopus_gen",false);
      this->compareJetCollections(L1_4300global_jJet, ak4genjetsp_jJet, "4300_global_gen",false);

      this->compareJetCollections(L1_5450donut_jJet, ak4genjetsp_jJet,"5450_donut_gen",false);
      this->compareJetCollections(L1_5450_jJet, ak4genjetsp_jJet,"5450_nopus_gen",false);
      this->compareJetCollections(L1_5450global_jJet, ak4genjetsp_jJet, "5450_global_gen",false);

      this->compareJetCollections(L1_6550_jJet, ak4genjetsp_jJet,"6550_nopus_gen",false);

      this->compareJetCollections(top_jJet, ak4genjetsp_jJet, "top_gen",false);
      this->compareJetCollections(top_jJet, ak4tt_jJet, "top_tt_gen",false);


      this->compareJetCollections(gct_jJet, ak4genjetsp_jJet, "gct_gen",true);
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
      //printOneEvent(triggertowers, L1_5400_jJet,ak4ttjets, genJetCol, ak4genjetsp);
      printOneEvent(triggertowers, jJetMap,ak4Map,genMap);
   }
   this->mPrintMe = false;
   //CALIBRATE!!!



   int maxtower; 
   for (std::vector<jJet>::const_iterator jet = L1_5400_real_jJet.begin();jet!=L1_5400_real_jJet.end();++jet)
   {
      std::vector<int> towers=jet->getTowers();
      auto it = max_element(std::begin(towers), std::end(towers));
      maxtower = *it;
      int nbins = tower_pt_real->GetXaxis()->FindBin(maxtower);
      int nbinsy = tower_pt_real_jetpt->GetYaxis()->FindBin(jet->pt());
      //int nbinsx = tower_pt_real_jetpt->GetXaxis()->FindBin(maxtower);
      for (int bins = 0; bins < nbins; bins++)
      {
	 int numt = 0;
	 for (auto tower = towers.begin(); tower != towers.end(); tower++)
	 {
	    if (*tower >= (tower_pt_real->GetBinCenter(bins)))
	    {
	       numt++;
	    }
	 }
	 tower_pt_real->AddBinContent(bins,1);
	 num_tower_pt_real->AddBinContent(bins,numt);
	 tower_pt_real_jetpt->SetBinContent(bins,nbinsy,tower_pt_real_jetpt->GetBinContent(bins,nbinsy)+1);
	 num_tower_pt_real_jetpt->SetBinContent(bins,nbinsy,num_tower_pt_real_jetpt->GetBinContent(bins,nbinsy)+numt);
      }
   }
   for (std::vector<jJet>::const_iterator jet = L1_5400_pu_jJet.begin();jet!=L1_5400_pu_jJet.end();++jet)
   {
      std::vector<int> towers=jet->getTowers();
      auto it = max_element(std::begin(towers), std::end(towers));
      maxtower = *it;
      int nbins = tower_pt_pu->GetXaxis()->FindBin(maxtower);
      int nbinsy = tower_pt_pu_jetpt->GetYaxis()->FindBin(jet->pt());
      //int nbinsx = tower_pt_pu_jetpt->GetXaxis()->FindBin(maxtower);
      for (int bins = 0; bins < nbins; bins++)
      {
	 int numt = 0;
	 for (auto tower = towers.begin(); tower != towers.end(); tower++)
	 {
	    if (*tower >= (tower_pt_pu->GetBinCenter(bins)))
	    {
	       numt++;
	    }
	 }
	 tower_pt_pu->AddBinContent(bins,1);
	 num_tower_pt_pu->AddBinContent(bins,numt);
	 tower_pt_pu_jetpt->SetBinContent(bins,nbinsy,tower_pt_pu_jetpt->GetBinContent(bins,nbinsy)+1);
	 num_tower_pt_pu_jetpt->SetBinContent(bins,nbinsy,num_tower_pt_pu_jetpt->GetBinContent(bins,nbinsy)+numt);
      }
   }
   //Make histos for rates

   /*
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
    */
   /*
      this->compareJetCollections(L1_4300_jJet, ak4genjetsp_jJet, "L14300_ak4genjetsp");
      this->compareJetCollections(L1_4300donut_jJet, ak4genjetsp_jJet, "L14300donut_ak4genjetsp");
      this->compareJetCollections(L1_4350_jJet, ak4genjetsp_jJet, "L14350_ak4genjetsp");
      this->compareJetCollections(L1_4350donut_jJet, ak4genjetsp_jJet, "L14350donut_ak4genjetsp");
      this->compareJetCollections(L1_5400_jJet, ak4genjetsp_jJet, "L15400_ak4genjetsp");

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

      this->compareJetCollections(L1_4300_jJet, ak4tt_jJet, "L14300_ak4tt");
      this->compareJetCollections(L1_4300donut_jJet, ak4tt_jJet, "L14300donut_ak4tt");
      this->compareJetCollections(L1_5400_jJet, ak4tt_jJet, "L15400_ak4tt");
    */  
   //  printOneEvent(triggertowers, L1_jJet, ak4ttjets, genJetCol, ak4genjetsp); 





   //if(mEventNumber == 18 || mEventNumber == 80 || mEventNumber == 94) { printOneEvent(triggertowers, L1_5400_jJet, ak4ttjets, genJetCol, ak4genjetsp); }
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
