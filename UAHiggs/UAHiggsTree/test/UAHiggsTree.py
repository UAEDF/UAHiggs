# Import configurations
import FWCore.ParameterSet.Config as cms

#from Configuration.StandardSequences.Generator_cff import *

# set up process
process = cms.Process("GetGenPart")

# initialize MessageLogger and output report ----------------------------------------
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#Geometry --------------------------------------------------------------------------
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


# Data source -----------------------------------------------------------------------
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/user/selvaggi/DataCopy__CMSSW_3_2_6__H120_2W_2lnu_gluonfusion_10TeV__Summer09-MC_31X_V3-v1__GEN-SIM-RECO_1.root')
#    fileNames = cms.untracked.vstring('file:///user/xjanssen/outCopy/MYCOPY_1.root')
#   fileNames = cms.untracked.vstring('file:////user/xjanssen/data/CMSSW_3_2_6/DataCopy/__WW__Summer09-MC_31X_V3-v1__GEN-SIM-RECO/data/DataCopy__CMSSW_3_2_6__WW__Summer09-MC_31X_V3-v1__GEN-SIM-RECO_1.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

# L1 extra --------------------------------------------------------------------------
#process.load("L1Trigger.L1ExtraFromDigis.l1extra_cff")
#process.load("EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi")
#process.l1GtUnpack.DaqGtInputTag = 'source'
#process.load("L1Trigger.L1ExtraFromDigis.l1extraParticles_cff")


# gen particles printouts -----------------------------------------------------------

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.GenPartDecay = cms.EDAnalyzer("ParticleDecayDrawer",
    src = cms.InputTag('genParticles'),
    printP4 = cms.untracked.bool(False),
    printPtEtaPhi =  cms.untracked.bool(False),
    printVertex = cms.untracked.bool(False)    
)

process.GenPartTree = cms.EDAnalyzer("ParticleTreeDrawer",
    src = cms.InputTag('genParticles'),
    printP4 = cms.untracked.bool(False),
    printPtEtaPhi =  cms.untracked.bool(True),
    printVertex = cms.untracked.bool(False),
    printStatus = cms.untracked.bool(False),
    printIndex = cms.untracked.bool(False),
    status = cms.untracked.vint32( 3 )
)   

process.GenPartList = cms.EDAnalyzer("ParticleListDrawer",
    maxEventsToPrint = cms.untracked.int32(100),
    printVertex = cms.untracked.bool(False),
    src = cms.InputTag("genParticles")
)


#genParticlesForJets.ignoreParticleIDs += cms.vuint32( 12,14,16)


# configure modules via Global Tag --------------------------------------------------
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'MC_31X_V3::All'

# Electron Isolation collections ----( Majid )---------------------------------------

EleIsoEcalFromHitsExtractorBlock = cms.PSet(
    ComponentName = cms.string('EgammaRecHitExtractor'),
    DepositLabel = cms.untracked.string(''),
    isolationVariable = cms.string('et'),
    extRadius = cms.double(0.6),
    intRadius = cms.double(0.0),
    intStrip = cms.double(0.0),
    etMin = cms.double(0.0),
    energyMin = cms.double(0.08),
    subtractSuperClusterEnergy = cms.bool(False),
    tryBoth = cms.bool(True),
    vetoClustered = cms.bool(False),

    barrelEcalHits = cms.InputTag("reducedEcalRecHitsEB"),
    endcapEcalHits = cms.InputTag("reducedEcalRecHitsEE")

)

process.eleIsoDepositEcalFromHits = cms.EDProducer("CandIsoDepositProducer",
    src = cms.InputTag("gsfElectrons"),
    trackType = cms.string('candidate'),
    MultipleDepositsFlag = cms.bool(False),
    ExtractorPSet = cms.PSet(EleIsoEcalFromHitsExtractorBlock)
)


process.load("RecoEgamma.EgammaIsolationAlgos.eleIsoFromDepsModules_cff")
process.load("RecoEgamma.EgammaIsolationAlgos.eleIsoDepositTk_cff")

# HWW Preselection ------------------------------------------------------------------

process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWPreselectionSequence_cff")

# K-Factor Producer -----------------------------------------------------------------

process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWKFactorProducer_cfi")
process.KFactorProducer.inputFilename = cms.untracked.string('HiggsAnalysis/HiggsToWW2Leptons/data/160_7TeV.dat')

# UAHiggsTree Code ------------------------------------------------------------------
process.UAHiggsTree = cms.EDAnalyzer('UAHiggsTree'

  , fileName = cms.untracked.string('UAHiggsTree.root')

# Modules to execute
  , StoreGenPart = cms.bool(True)
  , StoreGenKine = cms.bool(True)

# Define DATA Collections
  , genPartColl   = cms.InputTag("genParticles") 
  , hepMCColl     = cms.InputTag("generator")
  , gsfelectrons  = cms.InputTag("gsfElectrons") 
  , hcalIsolation = cms.InputTag("egammaTowerIsolation")
  , trckIsolation = cms.InputTag("egammaElectronTkRelIsolation")
  , muons         = cms.InputTag("muons") 
)


# Data output ----------------------------------------------------------------------- 
process.out = cms.OutputModule("PoolOutputModule",
    verbose = cms.untracked.bool(False),
    fileName = cms.untracked.string('cmsdata.root')
)


# PAth (what to do) ------------------------------------------------------------------
process.path = cms.Path(
#                        process.l1GtUnpack *
#                        process.l1extraParticles *
#                        process.GenPartDecay * 
#                        process.GenPartTree *
#                        process.GenPartList *  
#                        process.genJetParticles*process.recoGenJets*
                         process.KFactorProducer *
		         process.higgsToWW2LeptonsPreselectionSequence *
                         process.eleIsoDepositEcalFromHits *
                         process.eleIsoFromDepsEcalFromHits *
                         process.eleIsoDepositTk  
#                        process.UAHiggsTree   
                       )

# EndPath (what to store) ------------------------------------------------------------
#process.outpath = cms.EndPath(process.out)

