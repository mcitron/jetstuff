import FWCore.ParameterSet.Config as cms

process = cms.Process("skimrun")
process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger = cms.Service("MessageLogger",
threshold  = cms.untracked.string('ERROR')
####                     destinations       =  cms.untracked.vstring('/dev/null/file.txt'),
)



#process.source = cms.Source("PoolSource",
# fileNames = cms.untracked.vstring(

    #Neutrino13 PU40 50ns
 #  "/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/qcd1py/QCD_15-30_PU1.py"  
 #  ),

   # RAW files
  # secondaryFileNames = cms.untracked.vstring(
  # )
#)
process.load("/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/qcd1py/QCD_15-30_PU1.py" )


process.o1 = cms.OutputModule("PoolOutputModule",
  #fileName = cms.untracked.string('/afs/cern.ch/work/m/mcitron/public/TriggerTowers_NeutrinoGun_13TeV_PU40_50ns_1-10_skimmed_v3.root'),
  fileName = cms.untracked.string('file:/afs/cern.ch/work/m/mcitron/public/QCDPU1/output_run0.root'),
#   fileName = cms.untracked.string('output.root'),
    #SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('trigger_')),
    outputCommands = cms.untracked.vstring(
#    'keep *_*_*_*',
     'drop *_*_*_*',
#     'keep *_SLHCL1ExtraParticles_*_*',
#     'keep *_PUsubAK5CaloJetProducer_*_*',
#     # Test Pattern
#     'keep *_L1TestPatternCaloTowerProducer_*_*',

#     'keep *_hcalDigis_*_*',
     
     'keep *_valHcalTriggerPrimitiveDigis_*_*',
     'keep *_ecalDigis_EcalTriggerPrimitives_*',  
     'keep *_L1CaloTowerProducer_*_*',
     'keep *_ak4GenJets_*_*',
     'keep PileupSummaryInfos_*_*_*',
     'keep *_genParticles_*_*',
     'keep *_valGctDigis_*_*',
     'keep *_gctDigis_*_*'

#     'keep *_L1RingSubtractionProducer_*_*',
#     'keep *_L1TowerJetProducer_*_*',
#     'keep *_L1TowerJetCentralityFilter_*_*',
#     'keep *_L1TowerJetFilter1D_*_*',
#     'keep *_L1TowerJetPUEstimator_*_*',
#     'keep *_L1TowerJetPUSubtractedProducer_*_*',
#     'keep *_L1CalibFilterTowerJetProducer_*_*',
    
#     #kt6 jets for rho
#     'keep *_kt6CaloJets_*_RECO',
    
#     'keep *_ak5CaloJets_*_RECO',
#     'drop *_ak5CaloJets_rho_RECO',
#     'keep *_ak5CaloJets_rho_RCTofflineTEST',
#     'keep *_ak5PFJets_*_RECO',
#     'drop *_ak5PFJets_rho_RECO',
#     'keep *_ak5PFJets_rho_RCTofflineTEST',
#     'keep *_l1extraParticles_*_*',
#     'keep *_offlinePrimaryVertices_*_*',
#     'keep *_ak5JetID_*_*',
),
)


process.maxEvents = cms.untracked.PSet(
    # restrict number of events to 1000
    #input = cms.untracked.int32(10)
    # run over all events
    input = cms.untracked.int32(-1)
)

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

#process.GlobalTag.globaltag = 'POSTLS161_V12::All'
process.GlobalTag.globaltag = 'POSTLS162_V5::All'

process.load("Configuration.Geometry.GeometryIdeal_cff")

#switch line depending on data or simulation
#process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

#process.load("Configuration.StandardSequences.Reconstruction_Data_cff")
#process.load("RecoParticleFlow.PFProducer.particleFlow_cff") 
#process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
process.load("SLHCUpgradeSimulations.L1CaloTrigger.SLHCCaloTrigger_cff")
# process.load("L1Trigger.L1ExtraFromDigis.l1extraParticles_cfi")
# process.load("Configuration.StandardSequences.Services_cff")

process.load("Configuration.StandardSequences.L1HwVal_cff")

#import FWCore.ParameterSet.Config as cms
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.Configuration.RecoGenJets_cff')

process.ak4GenJets = process.ak5GenJets.clone(
        rParam = cms.double(0.4)
            )

process.antiktGenJets = cms.Sequence(process.genJetParticles*process.ak4GenJets)


process.load('L1TriggerConfig.GctConfigProducers.L1GctConfig_cff')
process.L1GctConfigProducers.CalibrationStyle = cms.string('None')

# #create collection of PU corrected AK5 Calo Jets
# process.PUsubAK5CaloJetProducer = cms.EDProducer('CalCaloProducer',
#                                    CaloJets = cms.InputTag("ak5CaloJets"),
#                                    JetCorrector = cms.string('ak5CaloL1FastL2L3Residual'), #jet corrections residual for data
# )

# from RecoJets.JetProducers.JetIDParams_cfi import *

# process.ak5JetID = cms.EDProducer('JetIDProducer', JetIDParams,
#         src = cms.InputTag('ak5CaloJets')

# )

# process.ak5PFJets.doRhoFastjet = cms.bool(True)

# process.ak5CaloJets.doRhoFastjet = cms.bool(True)


process.p1 = cms.Path(
    process.RawToDigi
    #+process.hcalDigis
    #+process.ecalDigis
    +process.valRctDigis
    +process.valGctDigis
    +process.SLHCCaloTrigger
    +process.antiktGenJets
#                       +process.ak5CaloJets
#                       +process.ak5PFJets
#                       +process.PUsubAK5CaloJetProducer
#                       +process.ak5JetID
)

process.p1.insert(1, process.valHcalTriggerPrimitiveDigis)
from SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff import HcalTPGCoderULUT
HcalTPGCoderULUT.LUTGenerationMode = cms.bool(True)
process.valRctDigis.hcalDigis             = cms.VInputTag(cms.InputTag('valHcalTriggerPrimitiveDigis'))
process.L1CaloTowerProducer.HCALDigis =  cms.InputTag("valHcalTriggerPrimitiveDigis")


process.outpath = cms.EndPath(process.o1)

# Make the job crash in case of missing product
#process.options = cms.untracked.PSet( Rethrow = cms.untracked.vstring('ProductNotFound') )
process.options = cms.untracked.PSet(

    SkipEvent = cms.untracked.vstring('ProductNotFound')
    # Make the job crash in case of missing product
    #Rethrow = cms.untracked.vstring('ProductNotFound')
    
)
