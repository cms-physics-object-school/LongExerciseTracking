import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v4'
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))
process.MessageLogger = cms.Service("MessageLogger")


process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
  '/store/data/Run2016C/ZeroBias/AOD/23Sep2016-v1/90000/002391CD-1783-E611-A733-24BE05CEACA1.root'     
)##,
)

process.demo = cms.EDAnalyzer('DATA13_2btree'
)


process.TFileService = cms.Service("TFileService",

  fileName = cms.string('DS2b.root')
)


process.p = cms.Path(process.demo)

