import FWCore.ParameterSet.Config as cms

process = cms.Process("TracksAndVertices")

# get the data from the Double-Mu triggered sample, a randomly selected file from Run2012A (must be accessible on your system)
process.source = cms.Source("PoolSource",
    skipEvents=cms.untracked.uint32(6000),
    fileNames = cms.untracked.vstring("root://eoscms.cern.ch//store/data/Run2017C/DoubleMuon/AOD/PromptReco-v1/000/299/370/00000/0E5CDA9A-C96D-E711-B810-02163E014736.root","/store/data/Run2017C/DoubleMuon/AOD/PromptReco-v1/000/299/370/00000/0EE732AA-C26D-E711-BE95-02163E011EE2.root"))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))  # get the first 1e4 events

# ignore any messages except ERROR level and higher
process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring("cout"),
    cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))

# don't exclude any events

# output to tracks_and_vertices.root
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *",   # exclude all but a few chosen data products
                                           
                                           # tracks of all kinds
                                           "keep *_generalTracks_*_*",
                                           "keep *_globalMuons_*_*",
                                           "keep *_ckfInOutTracksFromConversions_*_*",
                                           "keep *_ckfOutInTracksFromConversions_*_*",
                                           "keep *_conversionStepTracks_*_*",
                                           "keep *_uncleanedOnlyCkfInOutTracksFromConversions_*_*",
                                           "keep *_uncleanedOnlyCkfOutInTracksFromConversions_*_*",
					   "keep *_cosmicMuons_*_*",
					   "keep *_cosmicMuons1Leg_*_*",
					   "keep *_displacedGlobalMuons_*_*",
					   "keep *_displacedStandAloneMuons_*_*",
					   "keep *_displacedTracks_*_*",
					   "keep *_refittedStandAloneMuons_*_*",
					   "keep *_standAloneMuons_*_*",
					   "keep *_tevMuons_*_*",
					   "keep *_impactParameterTagInfosEI_*_*",
                                           
                                           # the beamspot and primary vertices
                                           "keep *_offlineBeamSpot_*_*",
                                           "keep *_offlinePrimaryVertices_*_*",
                                           "keep *_offlinePrimaryVerticesWithBS_*_*",
					   "keep *_inclusiveSecondaryVertices_*_*",

					   #keep a few other things
					   "keep *_generalV0Candidates_*_*",

                                           # event-level information that we *might* use
                                           "keep *_logErrorHarvester_*_*",
                                           "keep *_l1L1GtObjectMap_*_*",
                                           "keep *_TriggerResults_*_HLT",
                                           "keep *_hltTriggerSummaryAOD_*_*",
                                           "keep *_clusterSummaryProducer_*_*",
                                           ),
    fileName = cms.untracked.string("tracks_and_vertices_DoubleMuon2017C_299370.root"))

process.endpath = cms.EndPath(process.output)
