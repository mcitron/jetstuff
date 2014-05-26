#ifndef L1JETPRODUCER_H
#define L1JETPRODUCER_H


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

#include "jCaloTower/L1JetProducer/interface/jad_jet_class.hh"
#include "jCaloTower/L1JetProducer/interface/matching_algo.hh"

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include <fastjet/PseudoJet.hh>

class L1JetProducer{
  public:
    explicit L1JetProducer(const edm::ParameterSet&);
    ~L1JetProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    void getJets(std::vector < fastjet::PseudoJet > &constits,std::vector < fastjet::PseudoJet > &jets);
    std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int phisize, int etasize, int vetophisize, int vetoetasize, int seedthresh1, int seedthresh2);
    std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int jetsize, int vetowindowsize, int seedthresh1, int seedthresh2); 
    void compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName);

  private:

};
//
#endif
