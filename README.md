jetstuff
========

Latest Version of the Jet Maker code as initiated by Jad  


Most of the work is done in jCaloTower/ . The other packages are there for data formats.  


Workflow is as follows:  


1. Make a slim of the variables you want (see makeL1Skim.py). Keeps most L1 stuff including the towers etc..  


2. Produce a tree of jet candidates and other variables relevant to PUS with CaloTowerAnalyser. Configs in batch, e.g. 
batch_executable_filelist.sh. This is used to split up and run one job per input file.  

3. hadd the output of the trees to get a tree of jet candidates per data sample  


4. Give this tree as an input to JetMaker which is a MakeClass style thing to produce a tree of PUS jet candidates. New PUS
methods can be added here provided the variables required are included in the tree made in step 2.  


5. To calibrate all these jet types, run calibrationPlots.C in calibration/ to make the plots required for calibration. Then 
run getCalibrationJETMET.cpp followed by getReCalibJETMET.C to calculate LUTs for calibration.  

6. Put the LUTS into calibrationLUTS.hh in RecalibTrees and run RecalibTrees with the tree from step (2) and the tree from 
step (3) to calibrate all the jets output from (3).  

6. Go to AN and run the plot making macros to get all relevant plots for the analysis notes over the tree in (2) and (6).  


