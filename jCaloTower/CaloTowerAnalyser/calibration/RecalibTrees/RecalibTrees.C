#define RecalibTrees_cxx
#include "RecalibTrees.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "calibration_params.hh"

void RecalibTrees::Loop(int firstEntry, int lastEntry)
{
//   In a ROOT session, you can do:
//      Root > .L RecalibTrees.C
//      Root > RecalibTrees t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   if(lastEntry>nentries){
    lastEntry = nentries;
    std::cout << "Last entry > nentries, just going to nentries" << std::endl;
   }
   

   //nentries = 10000;

   outFile->cd();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=firstEntry; jentry<lastEntry;jentry++) {
     //Long64_t ientry = LoadTree(jentry);
     //if (ientry < 0) break;
     //nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     //

     //Get the relevant entry to start work
     GetEntry(jentry); 

     jetPt_5400_calib_donut->clear();
     jetPt_5400_calib_global->clear();
     jetPt_5400_calib_nopus->clear();
     jetPt_5450_calib_donut ->clear();
     jetPt_5450_calib_global->clear();
     jetPt_5450_calib_nopus->clear();
     //jetPt_5450_calib_2_strips->clear();
     //jetPt_5450_calib_3_strips->clear();

     *jetPt_5400_calib_donut = calibrateL1Jets(*jetPt_5400_donut, *jetEta_5400_donut,0,10.,999.);
     *jetPt_5400_calib_global = calibrateL1Jets(*jetPt_5400_global, *jetEta_5400_global,1,10.,999.);
     *jetPt_5400_calib_nopus = calibrateL1Jets(*jetPt_5400_nopus, *jetEta_5400_nopus,2,10.,999.);
     *jetPt_5450_calib_donut = calibrateL1Jets(*jetPt_5450_donut, *jetEta_5450_donut,3,10.,999.);
     *jetPt_5450_calib_global = calibrateL1Jets(*jetPt_5450_global, *jetEta_5450_global,5,10.,999.);
     *jetPt_5450_calib_nopus = calibrateL1Jets(*jetPt_5450_nopus, *jetEta_5450_nopus,4,10.,999.);
     //*jetPt_5450_calib_2_strips = calibrateL1Jets(*jetPt_5450_2_strips, *jetEta_5450_2_strips,6,10.,999.);
     //*jetPt_5450_calib_3_strips = calibrateL1Jets(*jetPt_5450_3_strips, *jetEta_5450_3_strips,7,10.,999.);


     friendTree->Fill();

     if(jentry%100==0) std::cout << "Done: " << jentry << std::endl;
   }

   friendTree->Write();

   outFile->Close();
}
