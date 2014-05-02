import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'WARNING'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
        )
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_RelValTTbar_withPU.root',
    'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_RelValTTbar_withPU_2.root',
    'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_RelValTTbar_withPU_3.root'
    )
)

process.demo = cms.EDAnalyzer('CaloTowerAnalyser'
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histograms-relvalttbar_test.root')
                                   )

process.p = cms.Path(process.demo)
