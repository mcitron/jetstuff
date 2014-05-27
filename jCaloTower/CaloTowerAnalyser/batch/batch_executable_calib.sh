cd /afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/
eval `scramv1 runtime -sh` 
#python run_calib.py
python run_config.py 70000 10 '/afs/cern.ch/work/m/mcitron/public/test/' 'file:/afs/cern.ch/work/m/mcitron/public/output_run4.root'
#USAGE run_config.py <tot num> <split> <outputdir> <input>
