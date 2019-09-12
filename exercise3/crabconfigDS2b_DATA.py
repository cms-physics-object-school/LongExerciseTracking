
from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'DSp_ZB16runBv3_2b'
config.General.workArea = 'crab_projects_skim'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'demoanalyzerDS2b_DATA.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.priority = 10;

config.Data.inputDataset = '/ZeroBias/Run2016B-23Sep2016-v3/AOD'
config.Data.inputDBS = 'global'
config.Data.splitting='EventAwareLumiBased'
config.Data.unitsPerJob= 800000
config.Data.publication = False
config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"

config.Site.storageSite = "T2_IT_Pisa"



