//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul  8 14:51:38 2014 by ROOT version 5.34/07
// from TTree L1Tree/L1Tree
// found on file: /home/adam/ttbar_output.root
//////////////////////////////////////////////////////////

#ifndef RecalibTrees_h
#define RecalibTrees_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <iostream>

// Fixed size dimensions of array or collections stored in the TTree if any.

class RecalibTrees {
  public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    //Add a new "friend" tree
    TFile* outFile;
    TTree* friendTree;

    //Add variablews for the friend tree
    vector<float> *jetPt_5400_calib_donut;
    vector<float> *jetPt_5400_calib_global;
    vector<float> *jetPt_5400_calib_nopus;
    vector<float> *jetPt_5450_calib_donut;
    vector<float> *jetPt_5450_calib_global;
    vector<float> *jetPt_5450_calib_nopus;
    //vector<float> *jetPt_5450_calib_2_strips;
    //vector<float> *jetPt_5450_calib_3_strips;

    //Add new branches
    TBranch *b_jetPt_5400_calib_donut;
    TBranch *b_jetPt_5400_calib_global;
    TBranch *b_jetPt_5400_calib_nopus;
    TBranch *b_jetPt_5450_calib_donut;
    TBranch *b_jetPt_5450_calib_global;
    TBranch *b_jetPt_5450_calib_nopus;


    // Declaration of leaf types
    vector<float> *jetPt_5400_donut;
    vector<float> *jetPt_5400_global;
    vector<float> *jetPt_5400_nopus;
    vector<float> *jetPt_5450_donut;
    vector<float> *jetPt_5450_global;
    vector<float> *jetPt_5450_nopus;
    vector<float> *jetEta_5400_donut;
    vector<float> *jetEta_5400_global;
    vector<float> *jetEta_5400_nopus;
    vector<float> *jetEta_5450_donut;
    vector<float> *jetEta_5450_global;
    vector<float> *jetEta_5450_nopus;

    // List of branches
    TBranch *b_jetPt_5400_donut;
    TBranch *b_jetPt_5400_global;
    TBranch *b_jetPt_5400_nopus;
    TBranch *b_jetPt_5450_donut;
    TBranch *b_jetPt_5450_global;
    TBranch *b_jetPt_5450_nopus;
    TBranch *b_jetEta_5400_donut;
    TBranch *b_jetEta_5400_global;
    TBranch *b_jetEta_5400_nopus;
    TBranch *b_jetEta_5450_donut;
    TBranch *b_jetEta_5450_global;
    TBranch *b_jetEta_5450_nopus;

    RecalibTrees(TTree *tree=0, int=0);
    virtual ~RecalibTrees();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop(int,int);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RecalibTrees_cxx
RecalibTrees::RecalibTrees(TTree *tree, int fileNumber) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/adam/ttbar_output.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("/home/adam/ttbar_output.root");
    }
    TDirectory * dir = (TDirectory*)f->Get("/home/adam/ttbar_output.root:/demo");
    dir->GetObject("L1Tree",tree);

  }
  Init(tree);

  //Initialise memory for the friend tree
  jetPt_5400_calib_donut = new std::vector<float>();
  jetPt_5400_calib_global = new std::vector<float>();
  jetPt_5400_calib_nopus  = new std::vector<float>();
  jetPt_5450_calib_donut  = new std::vector<float>();
  jetPt_5450_calib_global = new std::vector<float>();
  jetPt_5450_calib_nopus  = new std::vector<float>();
  //jetPt_5450_calib_2_strips = new std::vector<float>();
  //jetPt_5450_calib_3_strips = new std::vector<float>();


  //Set the branch addresses
  char fileName[16];
  sprintf(fileName,"friendTree%d.root",fileNumber);

  outFile = new TFile(fileName,"RECREATE");

  friendTree = new TTree("friendTree","friendTree");

  friendTree->Branch("jetPt_5400_calib_donut", "std::vector<float>", &jetPt_5400_calib_donut );
  friendTree->Branch("jetPt_5400_calib_nopus", "std::vector<float>", &jetPt_5400_calib_nopus );
  friendTree->Branch("jetPt_5400_calib_global", "std::vector<float>", &jetPt_5400_calib_global );
  friendTree->Branch("jetPt_5450_calib_donut", "std::vector<float>", &jetPt_5450_calib_donut );
  friendTree->Branch("jetPt_5450_calib_nopus", "std::vector<float>", &jetPt_5450_calib_nopus );
  friendTree->Branch("jetPt_5450_calib_global", "std::vector<float>", &jetPt_5450_calib_global );
  //friendTree->Branch("jetPt_5450_calib_2_strips", "std::vector<float>", &jetPt_5450_calib_2_strips );
  //friendTree->Branch("jetPt_5450_calib_3_strips", "std::vector<float>", &jetPt_5450_calib_3_strips );

  //fChain->SetBranchAddress("jetArea_ak4_gen", &jetArea_ak4_gen, &b_jetArea_ak4_gen);
  //friendTree->SetBranchAddress("jetPt_5400_calib_donut", &jetPt_5400_calib_donut, &b_jetPt_5400_calib_donut);
  //std::cout << "Got here" << std::endl;
  //friendTree->SetBranchAddress("jetPt_5400_calib_nopus", &jetPt_5400_calib_nopus, &b_jetPt_5400_calib_nopus);
  //friendTree->SetBranchAddress("jetPt_5400_calib_global", &jetPt_5400_calib_global, &b_jetPt_5400_calib_global);
  //friendTree->SetBranchAddress("jetPt_5450_calib_donut", &jetPt_5450_calib_donut, &b_jetPt_5450_calib_donut);
  //friendTree->SetBranchAddress("jetPt_5450_calib_nopus", &jetPt_5450_calib_nopus, &b_jetPt_5450_calib_nopus);
  //friendTree->SetBranchAddress("jetPt_5450_calib_global", &jetPt_5450_calib_global, &b_jetPt_5450_calib_global);

}

RecalibTrees::~RecalibTrees()
{

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  //  delete friendTree;
  delete jetPt_5400_calib_donut;
  delete jetPt_5400_calib_global;
  delete jetPt_5400_calib_nopus;
  delete jetPt_5450_calib_donut;
  delete jetPt_5450_calib_global;
  delete jetPt_5450_calib_nopus;

}

Int_t RecalibTrees::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t RecalibTrees::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void RecalibTrees::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  jetPt_5400_donut=0;
  jetPt_5400_global=0;
  jetPt_5400_nopus=0;
  jetPt_5450_donut=0;
  jetPt_5450_global=0;
  jetPt_5450_nopus=0;
  jetEta_5400_donut=0;
  jetEta_5400_global=0;
  jetEta_5400_nopus=0;
  jetEta_5450_donut=0;
  jetEta_5450_global=0;
  jetEta_5450_nopus=0;

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("jetPt_5400_donut", &jetPt_5400_donut, &b_jetPt_5400_donut);
  fChain->SetBranchAddress("jetPt_5400_global", &jetPt_5400_global, &b_jetPt_5400_global);
  fChain->SetBranchAddress("jetPt_5400_nopus", &jetPt_5400_nopus, &b_jetPt_5400_nopus);
  fChain->SetBranchAddress("jetPt_5450_donut", &jetPt_5450_donut, &b_jetPt_5450_donut);
  fChain->SetBranchAddress("jetPt_5450_global", &jetPt_5450_global, &b_jetPt_5450_global);
  fChain->SetBranchAddress("jetPt_5450_nopus", &jetPt_5450_nopus, &b_jetPt_5450_nopus);
  fChain->SetBranchAddress("jetEta_5400_donut", &jetEta_5400_donut, &b_jetEta_5400_donut);
  fChain->SetBranchAddress("jetEta_5400_global", &jetEta_5400_global, &b_jetEta_5400_global);
  fChain->SetBranchAddress("jetEta_5400_nopus", &jetEta_5400_nopus, &b_jetEta_5400_nopus);
  fChain->SetBranchAddress("jetEta_5450_donut", &jetEta_5450_donut, &b_jetEta_5450_donut);
  fChain->SetBranchAddress("jetEta_5450_global", &jetEta_5450_global, &b_jetEta_5450_global);
  fChain->SetBranchAddress("jetEta_5450_nopus", &jetEta_5450_nopus, &b_jetEta_5450_nopus);

  Notify();
}

Bool_t RecalibTrees::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void RecalibTrees::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t RecalibTrees::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef RecalibTrees_cxx
