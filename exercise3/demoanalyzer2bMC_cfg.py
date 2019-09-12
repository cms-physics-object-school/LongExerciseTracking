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
   '/store/mc/RunIIFall17DRPremix/DStarToD0Pi_D0K3Pi_DStarFilter_TuneCP5_13TeV-pythia8-evtgen/AODSIM/PU2017_94X_mc2017_realistic_v11-v1/60000/F2D9E1D9-60B9-E811-B926-14187763B811.root'
)
)

process.demo = cms.EDAnalyzer('MC13_2btree'
)


process.TFileService = cms.Service("TFileService",

  fileName = cms.string('MC2b.root')
)


process.p = cms.Path(process.demo)

