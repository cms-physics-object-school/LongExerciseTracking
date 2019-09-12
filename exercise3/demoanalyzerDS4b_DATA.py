import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
##process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag.globaltag = '76X_dataRun2_v15'
#process.GlobalTag.globaltag = '80X_dataRun2_Prompt_ICHEP16JEC_v0'
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v4'
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))##-1
process.MessageLogger = cms.Service("MessageLogger")


process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
   '/store/data/Run2016C/ZeroBias/AOD/23Sep2016-v1/90000/002391CD-1783-E611-A733-24BE05CEACA1.root'
)##,
##skipEvents = cms.untracked.uint32(3800)
)

process.demo = cms.EDAnalyzer('DATA13_4btree'
)


process.TFileService = cms.Service("TFileService",

  fileName = cms.string('DS4b.root')
)


process.p = cms.Path(process.demo)

