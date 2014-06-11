import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/1EB67544-9074-E311-B8F7-0025905A6132.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/26DC1D3C-6D74-E311-B1C9-002618FDA28E.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/38CAEE4B-AA74-E311-948B-0025905822B6.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/3AC210F6-8474-E311-9CF0-00304867918A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/4010585C-7E74-E311-B03B-0026189437F5.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/40443F65-9D77-E311-A0C9-00261894387A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/409BA958-8C74-E311-8B3D-003048679236.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/50C962C3-7F74-E311-BAF9-002618943935.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/5C6C9C8C-8774-E311-A056-002618943811.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/66308B67-8674-E311-A1B7-0026189438A5.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/862D0CF9-8D74-E311-934F-0025905A60B2.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/901DCA88-A074-E311-8510-0025905A60B0.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/94B6452E-6074-E311-B70E-0025905A60B6.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/A09DB8C3-7374-E311-963C-003048679248.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/A8737069-8374-E311-B8E4-0026189438DE.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/AC700628-7974-E311-8C5E-00261894388A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/B896C387-EB76-E311-90FB-00261894382D.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/B8D4AC9C-8974-E311-BB5C-003048FFD71E.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/BC10527F-6774-E311-ADD1-002618943882.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/C2DF7978-8A74-E311-BFCC-00304867920C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/D0470AB6-6E74-E311-BFF2-0030486792A8.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/D435CC8F-6374-E311-9BC3-0025905A48EC.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/D44B3496-7A74-E311-BF04-00261894393C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/D61E9CD8-CD74-E311-9450-0025905A60D0.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/E2B06A5B-8474-E311-B96F-003048D15DB6.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/EA630382-7874-E311-813C-003048678BC6.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/EABA346D-A074-E311-BFB8-003048FFCB8C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/ECA45D91-8074-E311-AAC6-00304867BF18.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/F21F2E7A-6974-E311-85C1-0025905A497A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/00000/FC5599CC-7F74-E311-8D98-0025905A60A6.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/005457EE-4874-E311-AE73-002618943831.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/00907F03-5274-E311-A718-003048FFCB74.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/069A6378-7074-E311-820C-002618943974.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/0A972EED-4374-E311-B49C-0025905A6084.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/0E86A25A-3D74-E311-AF3C-002618FDA248.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/1409CFD9-3975-E311-835E-00261894386B.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/166D6830-3574-E311-B656-003048678A6C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/169CB7D0-5774-E311-9E48-002618943953.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/184288EF-6074-E311-82F5-002590596484.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/1AD1FB53-3E74-E311-9EB6-002618943836.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/2ABB4D19-4174-E311-AE99-00304867C04E.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/36EEDDBC-7077-E311-9D9F-003048FFCC0A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/387C4AB2-6374-E311-9003-0025905AA9F0.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/3A4BD024-3674-E311-8BA4-002618943905.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/3A6CA9B7-4474-E311-9965-003048FFD754.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/3CD0E145-3B74-E311-B617-0025905964C4.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/40058D8A-4E74-E311-91DC-0025905A612C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/40DA9ABB-1076-E311-84D0-003048D15D22.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/48DF0551-4B74-E311-A245-00261894389D.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/5022B673-3C74-E311-8B43-003048D3C010.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/5844D9D0-5A74-E311-AB43-003048FFD732.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/5C68514C-6C74-E311-BF96-0025905964BE.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/5E206FA6-6774-E311-87CC-002354EF3BE6.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/666D10D8-4E74-E311-BC2E-0025905A60EE.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/6CF3DF84-4674-E311-BACA-003048D3C010.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/7010B200-4B74-E311-8817-00304867902E.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/74EFD515-3974-E311-8417-00261894393E.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/7625D635-5E74-E311-BBA1-002590596498.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/7E511977-5574-E311-B1DE-0025905A497A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/7E83D077-5774-E311-8021-0025905A497A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/84906FF9-5074-E311-80D0-00261894389A.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/8602443F-4074-E311-94A3-0025905A60DA.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/8A71CC93-4F74-E311-9BA6-0025905964C4.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/98FAF817-3A74-E311-B8E3-0025905AA9F0.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/9E4EF9CF-3B74-E311-945A-003048678F74.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/A0DC1797-4874-E311-9570-00261894398C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/A2EAB3A3-5374-E311-B8D8-002618943930.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/A6081C85-3874-E311-B583-002354EF3BCE.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/B26CD563-3A74-E311-B8CE-003048678EE2.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/B6995419-4D74-E311-8138-0025905A6070.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/BC93A1E5-4774-E311-BDE1-0025905A6122.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/BE9534AE-3D74-E311-872A-0026189438D5.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/CC0AA753-5C74-E311-9274-003048FFD756.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/CE1AF047-3F74-E311-85BC-0026189438D7.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/CE41D648-4574-E311-9CD3-002618943831.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/D00018EA-4B74-E311-B100-002618943935.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/D4D4A8D7-4574-E311-A451-003048678FE0.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/D8FE85D4-4274-E311-9596-002618943960.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/E2D169DB-5274-E311-BF7D-0025905A48D8.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/E89ADCE3-4974-E311-B27A-003048679162.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/EAC381FD-4174-E311-8D61-0026189438AD.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/EED1F28D-4274-E311-B665-003048678B36.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/FA4F7229-4D74-E311-B236-00261894390C.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/FE104A42-3874-E311-9A03-0025905964C0.root',
       '/store/mc/Fall13dr/QCD_Pt-15to30_Tune4C_13TeV_pythia8/AODSIM/castor_tsg_PU1bx50_POSTLS162_V1-v1/20000/FE61779D-5974-E311-BF0D-002618943918.root' ] );


secFiles.extend( [
               ] )
