#include "TCut.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2.h"
#include "TProfile.h"
#include <iostream>

namespace{

  int N_50NS_BUNCHES=1368;
  int N_25NS_BUNCHES=2508;
  int LHC_FREQUENCY=11246;

  int ZB_XSECTION=LHC_FREQUENCY*N_50NS_BUNCHES;

}

void makeJetPlots()
{
  TFile * fout = new TFile("jetPlots.root","recreate");

  TFile * finNeutrino = new TFile("ngun_jetTree.root");
  TTree * treeNeut = (TTree *)finNeutrino->Get("jetTree");
  treeNeut->AddFriend("demo/L1Tree",
      "/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140710/neutrino_output.root");

  TFile * finTtbar = new TFile("ttbar_jetTree.root");
  TTree * treeTtbar = (TTree *)finTtbar->Get("jetTree");
  treeTtbar->AddFriend("demo/L1Tree",
      "/afs/cern.ch/work/m/mcitron/public/TTBAR/140710/ttbar_output.root");

  std::vector<TString> jetTypes;
  jetTypes.push_back("s0_nopus");
  jetTypes.push_back("s0_donut");
 /* jetTypes.push_back("s0_global");
  jetTypes.push_back("s0_chunky");
  jetTypes.push_back("s0_tsup1");
  jetTypes.push_back("s0_tsup2");
  jetTypes.push_back("s0_tsup3");
  jetTypes.push_back("s5_nopus");
  jetTypes.push_back("s5_donut");
  jetTypes.push_back("s5_global");
  jetTypes.push_back("s5_chunky");
  jetTypes.push_back("s5_tsup1");
  jetTypes.push_back("s5_tsup2");
  jetTypes.push_back("s5_tsup3");
*/
  std::vector<TString> jetnum;
  jetnum.push_back("0");
  jetnum.push_back("3");

  //Cuts for turnons
  std::vector<TString> genPtCuts;
  genPtCuts.push_back("50.");
  genPtCuts.push_back("100.");
  genPtCuts.push_back("150.");

  for(std::vector<TString>::const_iterator iType=jetTypes.begin();
      iType!=jetTypes.end(); iType++){

    //Make a directory for each of the jet types
    TDirectory* jetDir = fout->mkdir(*iType);

    TDirectory* effDir = jetDir->mkdir("efficiency");
    TDirectory* rateDir = jetDir->mkdir("rate");
    TDirectory* rateEffDir = jetDir->mkdir("rate_eff");
    TDirectory* sumsDir = jetDir->mkdir("sums");
    TDirectory* turnonDir = jetDir->mkdir("turnons");

    for(std::vector<TString>::const_iterator iNum=jetnum.begin();
        iNum!=jetnum.end(); iNum++){

      /*
      TH1F* eff = makeEfficiency(treeTtbar, effDir, *iType, *iNum);
      TH1F* rate = makeRate(treeNeut, rateDir, *iType, *iNum);
      makeSums(treeTtbar, sumsDir, *iType, "ttbar");
      makeSums(treeNeut, sumsDir, *iType, "ngun");
      makeRateEff(rateEffDir, rate, eff, *iNum);
      */
      makeTurnon(treeTtbar, turnonDir, *iType, *iNum, genPtCuts);

    }

    std::cout << "Done " << iType->Data() << std::endl;

  }

}

void makeTurnon(TTree *tree, TDirectory* dir, TString jetType, TString jetNum,
    const std::vector<TString>& genptcut){

  dir->cd();
  tree->Draw("jetMatchedPt_"+jetType+"["+jetNum+"]>>denom_"+jetNum+"(1000,0.,1000.)",
      "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1");
  TH1F *denom = (TH1F*)gDirectory->Get("denom_"+jetNum);
  denom->Write();
  denom->Rebin(10);
  denom->Sumw2();
  for (std::vector<TString>::const_iterator iPt = genptcut.begin(); 
      iPt!=genptcut.end(); iPt++){

    tree->Draw("jetMatchedPt_"+jetType+"["+jetNum+"]>>num_"+jetNum+"_"+*iPt+"(1000.,0.,1000.)",
        "jetPt_"+jetType+"["+jetNum+"]>"+*iPt+"&&jetMatchedPt_"+jetType+"["+jetNum+"]!=-1");
    TH1F *num = (TH1F*)gDirectory->Get("num_"+jetNum+"_"+*iPt);
    num->Write();
    num->Rebin(10);
    num->Sumw2();
    TGraphAsymmErrors * result=(effDiv(num,denom));
    result->Write((jetNum+"_"+*iPt));
  } 

}

void makeRateEff(TDirectory* dir, TH1F* rate, TH1F* efficiency, TString jetNum){

  dir->cd();
  if(rate->GetNbinsX() != efficiency->GetNbinsX()) 
    std::cout << "Different binning between rate and efficiency\n";
  else{

    TGraph * rate_efficiency =
      new TGraph(rate->GetNbinsX());
    rate_efficiency->SetName("rate_efficiency_jet"+jetNum);
    rate_efficiency->SetTitle(";Efficiency (ttbar normalised rate);Rate (0 bias normalised rate)");

    for(unsigned bin=0; bin<rate->GetNbinsX(); bin++){

      rate_efficiency->SetPoint(bin, 
          efficiency->GetBinContent(bin), rate->GetBinContent(bin));

    }

    rate_efficiency->RemovePoint(rate_efficiency->GetN());
    rate_efficiency->Write();
  }

}

void makeSums(TTree *tree, TDirectory* dir, TString jetType, TString dataset){

  dir->cd();
  tree->Draw("ht_"+jetType+">>ht_"+jetType+"dataset(400,0.,4000.)");
  TH1F* test = (TH1F*) gDirectory->Get("ht_"+jetType+"dataset");
  test->Write();
  tree->Draw("mhtX_"+jetType+">>mhtX_"+jetType+"dataset(400,-2000.,2000.)");
  TH1F* test = (TH1F*) gDirectory->Get("mhtX_"+jetType+"dataset");
  test->Write();
  tree->Draw("mhtY_"+jetType+">>mhtY_"+jetType+"dataset(400,-2000.,2000.)");
  TH1F* test = (TH1F*) gDirectory->Get("mhtY_"+jetType+"dataset");
  test->Write();

}

TH1F* makeEfficiency(TTree *tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  TCut genptcut = "jetPt_ak4_gen["+jetNum+"]>50";
  tree->Draw("jetPt_ak4_gen["+jetNum+"]>>overall_"+jetNum,genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall_"+jetNum);
  double overallNorm = overall->GetEntries();

  TCut matchedcut = "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1";


  tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(1000,0.,1000.)",
      genptcut&&matchedcut,"");
  TH1F *test = (TH1F*)gDirectory->Get(jetType+"_"+jetNum);
  test->Write();
  test->SetName(jetType+"_"+jetNum+"_"+"Efficiency");

  TH1F* cumuplot = makeEfficiencyCumu(test,overallNorm);
  cumuplot->Write();

  return cumuplot;

}

TH1F* makeRate(TTree *tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(1000,-0.5,999.5)");
  TH1F *test = (TH1F*)gDirectory->Get(jetType+"_"+jetNum);
  test->Write();
  test->SetName(jetType+"_"+jetNum+"_"+"Rate");
  TH1F* cumuplot = makeRateCumu(test,tree->GetEntries());
  cumuplot->Write();

  return cumuplot;

}

TH1F * makeEfficiencyCumu(TH1F * input, double overallNorm){

  TH1F * output = new TH1F(*input);
  //output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int nYbins = input->GetNbinsY();
  int dummy = input->GetBinContent(nXbins+1);
  for (int xbins = 0; xbins <= nXbins; xbins++)
  {
    dummy += input->GetBinContent(nXbins-xbins);
    output->SetBinContent((nXbins-xbins),((double)dummy)/overallNorm);
  }

  return output;
}

TH1F * makeRateCumu(TH1F * input, double overallNorm){

  TH1F * output = new TH1F(*input);
  //output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int nYbins = input->GetNbinsY();
  int dummy = 0;
  for (int xbins = 0; xbins <= nXbins+1; xbins++)
  {
    dummy += input->GetBinContent(nXbins+1-xbins);
    output->SetBinContent((nXbins+1-xbins),ZB_XSECTION*((double)dummy)/overallNorm);
  }

  return output;
}

TGraphAsymmErrors * effDiv(TH1F * matchedhist, TH1F * allhist)
{
  TGraphAsymmErrors* matchCurve = new TGraphAsymmErrors();
  matchCurve->SetName("matchCurve");

  //TH1D matcheff = ((*matchedhist).Divide(allhist));
  //matchedhist->Divide(allhist);
  //matchedhist->Draw();

  matchCurve->Divide(matchedhist,allhist);
  return matchCurve;
}
