#define JetMaker_cxx
#include "JetMaker.h"
#include "MatchingAlgo.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

namespace{

  void getESums(const std::vector<TLorentzVector>& jets, 
      double& ht, double& mhtX, double& mhtY){

    ht=0;
    TLorentzVector mht;

    for(unsigned i=0; i<jets.size(); i++){
      ht+=jets[i].Pt();
      mht+=jets[i];
    }
    mhtX=-1.0*mht.Px();
    mhtY=-1.0*mht.Py();
  }

  bool sortbypt(const TLorentzVector &a, const TLorentzVector &b) { return a.Pt() > b.Pt(); } 

}

void JetMaker::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  outFile->cd();

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    GetEntry(jentry);

    //Clear the vectors
    for(std::vector<TString>::const_iterator it=jetTypes.begin(); it!=jetTypes.end(); it++){
      jetPt[*it]->clear();
      jetMatchedPt[*it]->clear();
      jetEta[*it]->clear();
      jetPhi[*it]->clear();
    }

    std::map< TString,std::vector<TLorentzVector> > jetObjects;
    std::vector<TLorentzVector> genJetObjects;

    //Pull the nopus jets into a TLorentzVector
    //Apply the types of PUS

    //For Gen
    for(unsigned i=0; i<jetPt_ak4_gen->size(); i++){
      TLorentzVector jet;
      jet.SetPtEtaPhiM(jetPt_ak4_gen->at(i),jetEta_ak4_gen->at(i),
          jetPhi_ak4_gen->at(i),0.);
      genJetObjects.push_back(jet);
    }

    //For L1

    //Define the jetObjects
    jetObjects["s0_nopus"] = std::vector<TLorentzVector>(); 
    jetObjects["s0_donut"] = std::vector<TLorentzVector>(); 
    jetObjects["s0_global"] = std::vector<TLorentzVector>(); 
    jetObjects["s0_chunky"] = std::vector<TLorentzVector>(); 
    jetObjects["s0_tsup1"] = std::vector<TLorentzVector>(); 
    jetObjects["s0_tsup2"] = std::vector<TLorentzVector>(); 
    jetObjects["s0_tsup3"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_nopus"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_donut"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_global"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_chunky"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_tsup1"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_tsup2"] = std::vector<TLorentzVector>(); 
    jetObjects["s5_tsup3"] = std::vector<TLorentzVector>(); 
    for(unsigned i=0; i<jetPt_L1_for_Nick->size(); i++){
      TLorentzVector jet;
      jet.SetPtEtaPhiM(jetPt_L1_for_Nick->at(i),jetEta_L1_for_Nick->at(i),
          jetPhi_L1_for_Nick->at(i),0.);
      //Nopus
      jetObjects["s0_nopus"].push_back(jet);

      //Global
      double globalPt = jet.Pt()-medianRho*jetArea_L1_for_Nick->at(i);

      TLorentzVector globalJet;
      if(globalPt>0.){
        globalJet.SetPtEtaPhiM(globalPt,jetEta_L1_for_Nick->at(i),
            jetPhi_L1_for_Nick->at(i),0.);
        jetObjects["s0_global"].push_back(globalJet);
      }

      //Donut
      double donutEnergy= 
        ((jetOuterStripsEnergy_1_L1_for_Nick->at(i)+jetOuterStripsEnergy_2_L1_for_Nick->at(i))/
         (jetOuterStripsArea_1_L1_for_Nick->at(i)+jetOuterStripsArea_2_L1_for_Nick->at(i)))*
        jetArea_L1_for_Nick->at(i);

      double donutPt = jet.Pt()-donutEnergy;

      TLorentzVector donutJet;
      if(donutPt>0.){ 
        donutJet.SetPtEtaPhiM(donutPt,jetEta_L1_for_Nick->at(i),
            jetPhi_L1_for_Nick->at(i),0.);
        jetObjects["s0_donut"].push_back(donutJet);
      }

      //Chunky
      double chunkyEnergy=
        ((jetOuterStripsEnergy_1_5400_chunky->at(i)+jetOuterStripsEnergy_2_5400_chunky->at(i))/
         (jetOuterStripsArea_1_5400_chunky->at(i)+jetOuterStripsArea_2_5400_chunky->at(i)))*
        jetArea_5400_chunky->at(i);

      double chunkyPt = jet.Pt()-chunkyEnergy;

      TLorentzVector chunkyJet;
      if(chunkyPt>0.){
        chunkyJet.SetPtEtaPhiM(chunkyPt,jetEta_L1_for_Nick->at(i),
            jetPhi_L1_for_Nick->at(i),0.);
        jetObjects["s0_chunky"].push_back(chunkyJet);
      }

      //TSup
      double tsup1Pt = jet.Pt()-jetTowerEnergyUp1_L1_for_Nick->at(i);
      double tsup2Pt = jet.Pt()-jetTowerEnergyUp2_L1_for_Nick->at(i);
      double tsup3Pt = jet.Pt()-jetTowerEnergyUp3_L1_for_Nick->at(i);

      TLorentzVector tsup1Jet;
      if(tsup1Pt>0.){ 
        tsup1Jet.SetPtEtaPhiM(tsup1Pt,jetEta_L1_for_Nick->at(i),
            jetPhi_L1_for_Nick->at(i),0.);
        jetObjects["s0_tsup1"].push_back(tsup1Jet);
      }

      TLorentzVector tsup2Jet;
      if(tsup2Pt>0.){ 
        tsup2Jet.SetPtEtaPhiM(tsup2Pt,jetEta_L1_for_Nick->at(i),
            jetPhi_L1_for_Nick->at(i),0.);
        jetObjects["s0_tsup2"].push_back(tsup2Jet);
      }

      TLorentzVector tsup3Jet;
      if(tsup3Pt>0.){
        tsup3Jet.SetPtEtaPhiM(tsup3Pt,jetEta_L1_for_Nick->at(i),
            jetPhi_L1_for_Nick->at(i),0.);
        jetObjects["s0_tsup3"].push_back(tsup3Jet);
      }

      //Same with seed 5
      if(jetRingSumsEnergy_0_L1_for_Nick->at(i)>5){
        jetObjects["s5_nopus"].push_back(jet);
        if(globalPt>0.) jetObjects["s5_global"].push_back(globalJet);
        if(donutPt>0.) jetObjects["s5_donut"].push_back(donutJet);
        if(chunkyPt>0.) jetObjects["s5_chunky"].push_back(chunkyJet);
        if(tsup1Pt>0.) jetObjects["s5_tsup1"].push_back(tsup1Jet);
        if(tsup2Pt>0.) jetObjects["s5_tsup2"].push_back(tsup2Jet);
        if(tsup3Pt>0.) jetObjects["s5_tsup3"].push_back(tsup3Jet);
      }
    }


    //Check that all the types of PUS have been done
    if(jetObjects.size() != jetTypes.size()){
      std::cout << "ERROR: all jetTypes PUS methods have not been implemented" << std::endl;
      break;
    }

    //Fill the tree variables from the jetObjects
    //Loop over PUS types

    for(std::vector<TString>::const_iterator it=jetTypes.begin(); it!=jetTypes.end(); it++){

      //Sort the jets by pt
      std::sort(jetObjects[*it].begin(),jetObjects[*it].end(),sortbypt);

      //Match the jets to gen

      //Make all possible pairs of jets
      std::vector<pair_info> pairs = make_pairs(genJetObjects, jetObjects[*it]);

      //Find the index of the gen jet that is matched to L1
      std::vector<int> l1_matched_index_algo1 
        = analyse_pairs_local(pairs, jetObjects[*it].size(),0.49);


      //Fill the tree variables
      int j=0;
      for(std::vector<TLorentzVector>::const_iterator iJet=jetObjects[*it].begin(); 
          iJet!=jetObjects[*it].end(); iJet++){

        //Note the conversion to GeV
        jetPt[*it]->push_back(0.5*iJet->Pt());
        jetEta[*it]->push_back(iJet->Eta());
        jetPhi[*it]->push_back(iJet->Phi());

        //Fill for the matched
        if (l1_matched_index_algo1[j]!=-1)
        {
          jetMatchedPt[*it]->push_back(genJetObjects.at(l1_matched_index_algo1.at(j)).Pt());
        }
        else
        {
          jetMatchedPt[*it]->push_back(-1);
        }

        j++;
      }

      //Calculate the energy sums
      getESums(jetObjects[*it],ht[*it],mhtX[*it],mhtY[*it]);

    }

    jetTree->Fill();
    if(jentry%500==0) std::cout << "Done: " << jentry << std::endl;
  }

  jetTree->Write();

  outFile->Close(); 

}
