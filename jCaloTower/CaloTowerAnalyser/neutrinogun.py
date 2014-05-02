import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'WARNING'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
        )
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
                                                                    
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_NeutrinoGun_13TeV_PU40_25ns_skimmed_v2.root'
    'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_NeutrinoGun_13TeV_PU40_50ns_1-10_skimmed_v3.root'
    ),
    skipEvents = cms.untracked.uint32(0)
)

process.demo = cms.EDAnalyzer('CaloTowerAnalyser'
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histograms-neutrinogun_13TeV_PU40_50ns_1-10_skimmed_v3_allevents.root')
                                   )

process.p = cms.Path(process.demo)
