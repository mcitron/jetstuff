cd /vols/cms04/mc3909/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/
source /vols/cms/grid/setup.sh
eval `scramv1 runtime -sh` 
#filelist='/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/qcd_PU140.txt'
filelist='/vols/cms04/mc3909/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/qcd_PU40.txt'
outputdir="/vols/cms04/mc3909/QCDPU40/"
python python/run_qcd.py $filelist $outputdir
