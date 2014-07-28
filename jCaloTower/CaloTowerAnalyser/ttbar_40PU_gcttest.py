import FWCore.ParameterSet.Config as cms
import datetime
import os.path

doVer=True
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
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_25ns_12345_skimmed.root',
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_25ns_678910_skimmed.root'
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_25ns_1-10_skimmed_v2.root'
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_noPU_test2_v3.root'
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_50ns_1-10_skimmed_v3.root'    
      #'file:/afs/cern.ch/work/a/aelwood/public/TriggerTowers_TTbar_13TeV_PU40_50ns_1-10_skimmed_v3.root'
#      'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_noPU_skimmed_v2.root'
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_10_1_I2f.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_11_1_5ck.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_12_1_ux3.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_13_1_FG0.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_14_1_uiT.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_15_1_OlA.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_16_1_903.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_17_1_XRA.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_18_1_YtX.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_19_1_NYe.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_1_1_Ek8.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_20_1_5tJ.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_21_1_qW3.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_22_1_YpC.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_23_1_9nB.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_24_1_JOR.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_25_1_Hx8.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_26_1_P2d.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_27_1_0z8.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_28_1_tai.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_29_1_Wep.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_30_1_WYU.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_31_1_Wdl.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_32_1_l67.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_33_1_gc8.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_34_1_yOs.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_35_1_DWZ.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_36_1_rFj.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_37_1_nnM.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_38_1_8Dv.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_39_1_11g.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_40_1_EIP.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_41_1_Cxb.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_42_1_zrS.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_43_1_juC.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_44_1_qF0.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_45_1_TMe.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_5_1_Gs8.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_6_1_b1v.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_7_1_Zd9.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_8_1_zfB.root',
#'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_ttbar_PU40/L1SkimRun_9_1_QvH.root',
    ),
    skipEvents=cms.untracked.uint32(0)
)
now = datetime.datetime.now()
date = now.strftime("%Y-%m-%d")

process.demo = cms.EDAnalyzer('CaloTowerAnalyser',
skim_name=cms.string("jadtest"),
gctinfo=cms.bool(False)
)
fileName=('output/ttbar-output-PU40-'+date+'.root')
if(doVer):
 verNum = 1
 while (os.path.isfile(fileName)):
  fileName=('output/ttbar-output-PU40-'+date+'-rev'+str(verNum)+'.root')
  verNum+=1
print fileName
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(fileName),
                                   #fileName = cms.string('histograms-ttbar_13TeV_PU40_50ns_test_v3.root')
                                   )

process.p = cms.Path(process.demo)
