# Import configurations
import FWCore.ParameterSet.Config as cms

#from Configuration.StandardSequences.Generator_cff import *

# set up process
process = cms.Process("UAHiggs")


process.options = cms.untracked.PSet(
     SkipEvent = cms.untracked.vstring('ProductNotFound')
 )


# initialize MessageLogger and output report ----------------------------------------

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000


#Geometry --------------------------------------------------------------------------
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


# Data source -----------------------------------------------------------------------
process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(' ')
 #    fileNames = cms.untracked.vstring('file:/user/selvaggi/DataCopy__CMSSW_3_2_6__H120_2W_2lnu_gluonfusion_10TeV__Summer09-MC_31X_V3-v1__GEN-SIM-RECO_1.root')
 #   fileNames = cms.untracked.vstring('file:/user/selvaggi/DataCopy__CMSSW_3_2_8__H160_2W_2lnu_gluonfusion_7TeV__Summer09-MC_31X_V3_156BxLumiPileUp-v1__GEN-SIM-RECO_1.root')
#    fileNames = cms.untracked.vstring('file:///user/xjanssen/outCopy/MYCOPY_1.root')
#   fileNames = cms.untracked.vstring('file:////user/xjanssen/data/CMSSW_3_2_6/DataCopy/__WW__Summer09-MC_31X_V3-v1__GEN-SIM-RECO/data/DataCopy__CMSSW_3_2_6__WW__Summer09-MC_31X_V3-v1__GEN-SIM-RECO_1.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

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
process.GlobalTag.globaltag = 'START3X_V26::All'

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

# Jet Vertex Alpha  ------------------------------------------------------------

## REMEMBER TO ADD NEW JV PRODUCER IF OTHER CALO JET COLLECTIONS ARE ADDED


process.jetvertexalpha = cms.EDFilter("JetVertexAssociation",
    JV_deltaZ = cms.double(0.3),
    TRACK_ALGO = cms.string('generalTracks'),
    JV_alpha_threshold = cms.double(0.0),
    JET_ALGO = cms.string(''),
    JV_type_Algo = cms.int32(0),
    JV_cone_size = cms.double(0.5),
    VERTEX_ALGO = cms.string('offlinePrimaryVertices'),
    JV_cutType = cms.string('delta'),
    JV_sigmaZ = cms.double(9.5)
)

process.JVAak5              = process.jetvertexalpha.clone()
process.JVAak5.JET_ALGO     = cms.string('ak5CaloJets')
process.JVAak5.JV_type_Algo = cms.int32(1)
process.JVBak5               = process.jetvertexalpha.clone()
process.JVBak5.JET_ALGO      = cms.string('ak5CaloJets')
process.JVBak5.JV_type_Algo  = cms.int32(2)

process.JVAak7              = process.jetvertexalpha.clone()
process.JVAak7.JET_ALGO     = cms.string('ak7CaloJets')
process.JVAak7.JV_type_Algo = cms.int32(1)
process.JVBak7               = process.jetvertexalpha.clone()
process.JVBak7.JET_ALGO      = cms.string('ak7CaloJets')
process.JVBak7.JV_type_Algo  = cms.int32(2)



process.JVAiterativeCone5              = process.jetvertexalpha.clone()
process.JVAiterativeCone5.JET_ALGO     = cms.string('iterativeCone5CaloJets')
process.JVAiterativeCone5.JV_type_Algo = cms.int32(1)
process.JVBiterativeCone5               = process.jetvertexalpha.clone()
process.JVBiterativeCone5.JET_ALGO      = cms.string('iterativeCone5CaloJets')
process.JVBiterativeCone5.JV_type_Algo  = cms.int32(2)

process.JVAsisCone5              = process.jetvertexalpha.clone()
process.JVAsisCone5.JET_ALGO     = cms.string('sisCone5CaloJets')
process.JVAsisCone5.JV_type_Algo = cms.int32(1)
process.JVBsisCone5               = process.jetvertexalpha.clone()
process.JVBsisCone5.JET_ALGO      = cms.string('sisCone5CaloJets')
process.JVBsisCone5.JV_type_Algo  = cms.int32(2)



process.jetvertexassociation = cms.Sequence(process.JVAak5        + process.JVBak5 +
			                    process.JVAiterativeCone5 + process.JVBiterativeCone5 +
                                            process.JVAsisCone5 + process.JVBsisCone5
                                            )


# Track Jets (>3_4_2)--------------------------------------------------------------

process.load("RecoJets.Configuration.RecoTrackJets_cff")


# HWW Preselection ------------------------------------------------------------------

process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWPreselectionSequence_cff")

# K-Factor Producer -----------------------------------------------------------------

process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWKFactorProducer_cfi")
process.KFactorProducer.inputFilename = cms.untracked.string('HiggsAnalysis/HiggsToWW2Leptons/data/160_7TeV.dat')

#HLT filter from PreSelection 

process.higgsToWW2LeptonsHLTFilter.HLTPaths = ['HLT_L1MuOpen','HLT_L1Mu','HLT_Mu5','HLT_Mu9','HLT_L1DoubleMuOpen','HLT_DoubleMu0','HLT_DoubleMu3','HLT_L1SingleEG5','HLT_Ele15_SW_EleId_L1R','HLT_Ele15_SiStrip_L1R']

# UAHiggsTree Code ------------------------------------------------------------------
process.UAHiggsTree = cms.EDAnalyzer('UAHiggsTree'

  , fileName = cms.untracked.string('UAHiggsTree.root')

# Modules to execute
  , StoreGenPart     = cms.bool(True)
  , StoreGenKine     = cms.bool(True)
  , doJetVertexAlpha = cms.bool(True)
# Define DATA Collections
  , genPartColl   = cms.InputTag("genParticles") 
  , hepMCColl     = cms.InputTag("generator")
  , hcalIsolation = cms.InputTag("egammaTowerIsolation")
  , trckIsolation = cms.InputTag("egammaElectronTkRelIsolation")
  , bjets         = cms.InputTag("trackCountingHighPurBJetTags")
 
 
# Data Collections --------------------

  , requested_gsfelectrons = cms.vstring('gsfElectrons')#),'isolatedElectrons','selectedElectrons')
  , requested_muons        = cms.vstring('muons')#,'isolatedMuons','selectedMuons')
  
  , requested_genmets      = cms.vstring('genMetTrue')
  , requested_calomets     = cms.vstring('met')
  , requested_pfmets       = cms.vstring('pfMet')
  , requested_tcmets       = cms.vstring('tcMet')

  , requested_genjets      = cms.vstring('iterativeCone5GenJets','sisCone5GenJets')
  , requested_calojets     = cms.vstring('iterativeCone5CaloJets','sisCone5CaloJets','ak5CaloJets')
  , requested_pfjets       = cms.vstring('iterativeCone5PFJets','sisCone5PFJets','ak5PFJets')
  , requested_trackjets    = cms.vstring('iterativeCone5TrackJets','sisCone5TrackJets','ak5TrackJets')

  , requested_hlt_bits     = cms.vstring('HLT_L1MuOpen','HLT_L1Mu','HLT_Mu5','HLT_Mu9','HLT_L1DoubleMuOpen','HLT_DoubleMu0','HLT_DoubleMu3','HLT_L1SingleEG5','HLT_Ele15_SW_EleId_L1R','HLT_Ele15_SiStrip_L1R')
  , requested_L1_bits      = cms.vstring('L1_SingleMuOpen','L1_SingleMu0','L1_SingleMu7','L1_DoubleMu3','L1_SingleMu20','L1_SingleMu3','L1_DoubleMuOpen','L1_SingleEG1','L1_SingleEG2','L1_SingleEG5','L1_SingleEG8','L1_SingleEG20','L1_DoubleEG5')

  , requested_vertexs      = cms.vstring('offlinePrimaryVertices')#,'pixelVertices')
  , requested_tracks       = cms.vstring('generalTracks')#,'pixelTracks')
 

)


# Data output ----------------------------------------------------------------------- 
#process.out = cms.OutputModule("PoolOutputModule",
#     verbose = cms.untracked.bool(False),
#    fileName = cms.untracked.string('cmsdata.root')
#)


# PAth (what to do) ------------------------------------------------------------------
process.path = cms.Path( 
#                        process.l1GtUnpack *
#                        process.l1extraParticles *
#                        process.GenPartDecay * 
#                        process.GenPartTree *
#                        process.GenPartList *  
#                        process.genJetParticles*
#			 process.recoGenJets*
#                         process.KFactorProducer *
#		         process.higgsToWW2LeptonsPreselectionSequence *
                         process.recoAllTrackJets *
			 process.jetvertexassociation *
#			 process.eleIsoDepositEcalFromHits *
#                         process.eleIsoFromDepsEcalFromHits *
#                         process.eleIsoDepositTk * 
                         process.UAHiggsTree   
                       )

# EndPath (what to store) ------------------------------------------------------------
#process.outpath = cms.EndPath(process.out)

