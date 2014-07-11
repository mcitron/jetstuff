#include "/afs/cern.ch/work/a/aelwood/trigger/jets/jadjet/CMSSW_6_2_0/src/SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"

calibrationPlots(){
  //Load files
  TFile* inFile = new TFile("/home/adam/ttbar_output.root");
  TTree* tree = inFile->Get("demo/L1Tree");

  TFile* outFile = new TFile("calibPlots.root","RECREATE");

  //Jet types
  std::vector<TString> jetType;
  jetType.push_back("5400_donut");
  jetType.push_back("5400_nopus");
  jetType.push_back("5400_global");
  jetType.push_back("5450_donut");
  jetType.push_back("5450_nopus");
  jetType.push_back("5450_global");

  //Eta cuts
  //  if(inJetEta[i]>=g.eta(-28) && inJetEta[i]<g.eta(-21));
  std::vector<TString> etaCutsLow;
  std::vector<TString> etaCutsHigh;
  std::vector<TString> etaCutsName;
  etaCutsLow.push_back(getEtaCut(-28,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-21,"<%f"));
  etaCutsName.push_back("Eta_m28_m21");
  etaCutsLow.push_back(getEtaCut(-21,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-14,"<%f"));
  etaCutsName.push_back("Eta_m21_m14");
  etaCutsLow.push_back(getEtaCut(-14,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-7,"<%f"));
  etaCutsName.push_back("Eta_m14_m7");
  etaCutsLow.push_back(getEtaCut(-7,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-1,"<=%f"));
  etaCutsName.push_back("Eta_m7_0");
  etaCutsLow.push_back(getEtaCut(1,">=%f"));
  etaCutsHigh.push_back(getEtaCut(7,"<=%f"));
  etaCutsName.push_back("Eta_0_7");
  etaCutsLow.push_back(getEtaCut(7,">%f"));
  etaCutsHigh.push_back(getEtaCut(14,"<=%f"));
  etaCutsName.push_back("Eta_7_14");
  etaCutsLow.push_back(getEtaCut(14,">%f"));
  etaCutsHigh.push_back(getEtaCut(21,"<=%f"));
  etaCutsName.push_back("Eta_14_21");
  etaCutsLow.push_back(getEtaCut(21,">%f"));
  etaCutsHigh.push_back(getEtaCut(28,"<=%f"));
  etaCutsName.push_back("Eta_21_28");

  TriggerTowerGeometry g;

  //Make plots

  outFile->cd();

  for(auto iJet=jetType.begin(); iJet!=jetType.end(); iJet++){

    for(int i=0; i<etaCutsName.size(); i++){

      tree->Draw("jetPt_"+*iJet+"/jetMatchedPt_"+*iJet+":jetMatchedPt_"+*iJet+">>ratio_"+*iJet+etaCutsName[i]+"(1000,-0.5,999.5,100,-1.,5.)",
          "jetMatchedPt_"+*iJet+"!=-1&&jetEta_"+*iJet+etaCutsLow[i]+"&&jetEta_"+*iJet+etaCutsHigh[i],"colz");
      TH2D* tmpHist = (TH2D*) gPad->GetPrimitive("ratio_"+*iJet+etaCutsName[i]);
      tmpHist->Write();

      tree->Draw("jetPt_"+*iJet+":jetMatchedPt_"+*iJet+">>corr_"+*iJet+etaCutsName[i]+"(1000,-0.5,999.5,1000,-0.5,999.5)",
          "jetMatchedPt_"+*iJet+"!=-1&&jetEta_"+*iJet+etaCutsLow[i]+"&&jetEta_"+*iJet+etaCutsHigh[i],"colz");
      TH2D* tmpHist = (TH2D*) gPad->GetPrimitive("corr_"+*iJet+etaCutsName[i]);
      tmpHist->Write();

    }
  }

  //Write out
}

TString getEtaCut(int x, char* lim){
  TriggerTowerGeometry g;
  double xReal = g.eta(x);
  char buffer[20];
  sprintf(buffer,lim,xReal);
  return TString(buffer);
}
