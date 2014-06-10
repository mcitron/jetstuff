cd /afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/
eval `scramv1 runtime -sh` 
#python run_calib.py
python python/run_ttbar_neutrino.py 70000 10 '/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140605/' '/afs/cern.ch/work/m/mcitron/public/TriggerTowers_NeutrinoGun_13TeV_PU40_50ns_1-10_skimmed_v3.root' 'jadtest'
#USAGE run_config.py <tot num> <split> <outputdir> <input>
