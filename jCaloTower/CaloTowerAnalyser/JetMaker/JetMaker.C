#define JetMaker_cxx
#include "JetMaker.h"
#include "MatchingAlgo.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

namespace{

  void getESums(const std::vector<TLorentzVector>& jets, 
      double& ht, double& mhtX, double& mhtY){

    ht=0;
    TLorentzVector mht;

    for(unsigned i=0; i<jets.size(); i++){
      if(jets[i].Pt()>20.){
        ht+=jets[i].Pt();
        mht+=jets[i];
      }
    }
    mhtX=-1.0*mht.Px();
    mhtY=-1.0*mht.Py();
  }

  bool sortbypt(const TLorentzVector &a, const TLorentzVector &b) { return a.Pt() > b.Pt(); } 

}

void JetMaker::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();

  //nentries=2900000;

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
    for(std::vector<TString>::const_iterator it=jetTypes.begin();
        it!=jetTypes.end();it++){
      jetObjects[*it].reserve(20);
    }

    std::vector<TLorentzVector> genJetObjects;
    genJetObjects.reserve(20);

    //Pull the nopus jets into a TLorentzVector
    //Apply the types of PUS

    //For Gen
    if(!doNGun){
      for(unsigned i=0; i<jetPt_ak4_gen->size(); i++){
        TLorentzVector jet;
        jet.SetPtEtaPhiM(jetPt_ak4_gen->at(i),jetEta_ak4_gen->at(i),
            jetPhi_ak4_gen->at(i),0.);
        genJetObjects.push_back(jet);
      }
    }
    //For L1

    //Define the jetObjects
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

      //Same with chunky seed 10
      if((jetRingSumsEnergy_0_L1_for_Nick->at(i)+jetRingSumsEnergy_1_L1_for_Nick->at(i))>10){
        jetObjects["c10_nopus"].push_back(jet);
        if(globalPt>0.) jetObjects["c10_global"].push_back(globalJet);
        if(donutPt>0.) jetObjects["c10_donut"].push_back(donutJet);
        if(chunkyPt>0.) jetObjects["c10_chunky"].push_back(chunkyJet);
        if(tsup1Pt>0.) jetObjects["c10_tsup1"].push_back(tsup1Jet);
        if(tsup2Pt>0.) jetObjects["c10_tsup2"].push_back(tsup2Jet);
        if(tsup3Pt>0.) jetObjects["c10_tsup3"].push_back(tsup3Jet);
      }
    }

    //Fill the tree variables from the jetObjects
    //Loop over PUS types

    for(std::vector<TString>::const_iterator it=jetTypes.begin(); it!=jetTypes.end(); it++){

      //Sort the jets by pt
      std::sort(jetObjects[*it].begin(),jetObjects[*it].end(),sortbypt);

      //Match the jets to gen

      std::vector<int> l1_matched_index_algo1;
      if(!doNGun){
        //Make all possible pairs of jets
        std::vector<pair_info> pairs = make_pairs(genJetObjects, jetObjects[*it]);

        //Find the index of the gen jet that is matched to L1
        l1_matched_index_algo1 
          = analyse_pairs_local(pairs, jetObjects[*it].size(),0.49);
      }

      //Fill the tree variables
      //int j=0;
      //for(std::vector<TLorentzVector>::const_iterator iJet=jetObjects[*it].begin(); 
      //    iJet!=jetObjects[*it].end(); iJet++)

      for(unsigned j=0; j<jetObjects[*it].size(); j++){

        //Note the conversion to GeV
        double newPt = 0.5*jetObjects[*it][j].Pt();
        jetPt[*it]->push_back(newPt);
        jetEta[*it]->push_back(jetObjects[*it][j].Eta());
        jetPhi[*it]->push_back(jetObjects[*it][j].Phi());

        if(!doNGun){
          //Fill for the matched
          if (l1_matched_index_algo1[j]!=-1)
          {
            jetMatchedPt[*it]->push_back(genJetObjects.at(l1_matched_index_algo1.at(j)).Pt());

            //Fill the histograms for the correlation
            for(unsigned e=0; e<etaBins.size(); e++){
              double etaLow = e*0.75-3.0;
              double etaHigh = e*0.75-2.25;
              if((jetObjects[*it][j].Eta() > etaLow) && (jetObjects[*it][j].Eta() <= etaHigh)){

                corrHists[*it+etaBins[e]]->Fill(genJetObjects.at(l1_matched_index_algo1.at(j)).Pt(),newPt);
                ratioHists[*it+etaBins[e]]->Fill(genJetObjects.at(l1_matched_index_algo1.at(j)).Pt(),
                    newPt/genJetObjects.at(l1_matched_index_algo1.at(j)).Pt());
                break;

              }
            }
          }
          else
          {
            jetMatchedPt[*it]->push_back(-1.);
          }
        }

        //j++;
      }

      //Calculate the energy sums
      getESums(jetObjects[*it],ht[*it],mhtX[*it],mhtY[*it]);

    }

    jetTree->Fill();
    if(jentry%10000==0) std::cout << "Done: " << jentry << std::endl;
  }

  //Write the output

  jetTree->Write();

  for(std::vector<TString>::const_iterator it=jetTypes.begin(); 
      it!=jetTypes.end(); it++){

    TDirectory* dir = outFile->mkdir(*it);
    dir->cd();

    for(std::vector<TString>::const_iterator eBins = etaBins.begin();
        eBins != etaBins.end(); eBins++){

      corrHists[*it+*eBins]->Write();
      ratioHists[*it+*eBins]->Write();
    }
  }

  outFile->Close(); 

}
