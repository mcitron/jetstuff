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
#    'file:../../TriggerTowers_MinBias2012D.root'
    'file:../../TriggerTowers_SingleMu2012D.root'
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_14_1_8Aa.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_12_1_vAl.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_9_1_Gsd.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_6_1_89o.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_3_1_iwX.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_11_1_qd4.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_2_1_58V.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_13_1_SRi.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_4_1_xBo.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_10_1_NNL.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_8_1_dsP.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_7_1_JY2.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_5_1_AvR.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_15_1_WKi.root',
#     '/store/user/jad/NeutrinoGun140PU_18Jun001/output-all_1_1_UVi.root'
    )
)

process.demo = cms.EDAnalyzer('CaloTowerAnalyser'
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histograms-singlemu.root')
                                   )

process.p = cms.Path(process.demo)
