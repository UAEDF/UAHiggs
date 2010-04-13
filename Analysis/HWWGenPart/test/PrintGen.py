# Import configurations
import FWCore.ParameterSet.Config as cms
# set up process
process = cms.Process("PrintGenPart")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:////user/xjanssen/outCopy/MYCOPY_1.root')
)
# copy 20 events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(100),
  printVertex = cms.untracked.bool(False),
  src = cms.InputTag("genParticles")
)


process.out = cms.OutputModule("PoolOutputModule",
    verbose = cms.untracked.bool(False),
    fileName = cms.untracked.string('cmsdata.root')
)

process.path = cms.Path(process.printTree)
#process.outpath = cms.EndPath(process.out)

