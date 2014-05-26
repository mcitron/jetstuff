cd /afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/
eval `scramv1 runtime -sh` 
for i in {53..59}
do
 export LSB_JOBINDEX=$i
 echo $LSB_JOBINDEX
# python run_skim.py
done
