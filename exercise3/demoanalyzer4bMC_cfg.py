import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))
process.MessageLogger = cms.Service("MessageLogger")


process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
  '/store/mc/RunIIFall15DR76/DStarToD0Pi_D0K3Pi_DStarFilter_TuneCUEP8M1_13TeV-pythia8-evtgen/AODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/30805EDF-6DD5-E511-9B58-00259074AE40.root'  

)##,
)

process.demo = cms.EDAnalyzer('MC13_4btree'
)


process.TFileService = cms.Service("TFileService",

  fileName = cms.string('MC4b.root')
)


process.p = cms.Path(process.demo)

