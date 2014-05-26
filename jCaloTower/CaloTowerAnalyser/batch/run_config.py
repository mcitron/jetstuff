import subprocess
import make_config
#import sys
import os

num = str(int(os.environ['LSB_JOBINDEX'])-1)

totevents = 70000
#totevents = sys.argv[0]
Nruns = 10
#Nruns = sys.argv[1]
#outputdir = sys.argv[2]
#input = sys.argv[3]
outputdir="/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/neutrino5"
#rundir="/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/"
#input='file:/afs/cern.ch/work/m/mcitron/public/TriggerTowers_NeutrinoGun_13TeV_PU40_50ns_1-10_skimmed_v3.root'    
#input = "file:/afs/cern.ch/work/a/aelwood/public/TriggerTowers_TTbar_13TeV_PU40_50ns_1-10_skimmed_v3.root"
input = "file:/afs/cern.ch/work/m/mcitron/public/output_run4.root"
print totevents,Nruns,outputdir,input 
arg_array=[]
for i in range(0,Nruns):
 arg_array.append([str(int(totevents*1./Nruns)),input,str(i*int(totevents*1./Nruns)+1),os.path.join(outputdir,"output"+"_run"+str(i)+".root")])

#define file names
configinput=make_config.make_config_input(arg_array[int(num)][0],arg_array[int(num)][1],arg_array[int(num)][2],arg_array[int(num)][3])
if not os.path.exists(outputdir):
    os.makedirs(outputdir)

os.chdir(outputdir)

f = open('config_'+num+'.py','w')
f.write(configinput)

with open("cmssw_"+num+".log",'w') as f:
 subprocess.call(["cmsRun", "config_"+num+".py"],stdout=f)

os.remove('config_'+num+'.py')
