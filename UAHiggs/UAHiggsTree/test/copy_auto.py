# Import configurations
import FWCore.ParameterSet.Config as cms
# set up process
process = cms.Process("copy")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(' ')
)
# copy 20 events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )


process.out = cms.OutputModule("PoolOutputModule",
    verbose = cms.untracked.bool(False),
    fileName = cms.untracked.string('cmsdata.root')
)

process.outpath = cms.EndPath(process.out)

