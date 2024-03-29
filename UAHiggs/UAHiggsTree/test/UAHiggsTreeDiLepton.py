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
process.MessageLogger.cerr.FwkReport.reportEvery = -1


#Geometry --------------------------------------------------------------------------
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


#process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')






# Data source -----------------------------------------------------------------------
process.source = cms.Source("PoolSource",
   #   fileNames = cms.untracked.vstring('file:/user/selvaggi/DataCopy__CMSSW_3_5_6__H160_2W_2lnu_gluonfusion_7TeV__Spring09-MC_31X_V26_S09-v1__GEN-SIM-RECO_1.root ')
  #fileNames = cms.untracked.vstring('store/mc/Spring10/WJets-madgraph/GEN-SIM-RECO/START3X_V26_S09-v1/0000/0250080D-FA44-DF11-B003-001D0967D5F8.root')
 #    fileNames = cms.untracked.vstring('file:/user/selvaggi/DataCopy__CMSSW_3_2_6__H120_2W_2lnu_gluonfusion_10TeV__Summer09-MC_31X_V3-v1__GEN-SIM-RECO_1.root')
 #   fileNames = cms.untracked.vstring('file:/user/selvaggi/DataCopy__CMSSW_3_2_8__H160_2W_2lnu_gluonfusion_7TeV__Summer09-MC_31X_V3_156BxLumiPileUp-v1__GEN-SIM-RECO_1.root')
#    fileNames = cms.untracked.vstring('file:///user/xjanssen/outCopy/MYCOPY_1.root')
#   fileNames = cms.untracked.vstring('file:////user/xjanssen/data/CMSSW_3_2_6/DataCopy/__WW__Summer09-MC_31X_V3-v1__GEN-SIM-RECO/data/DataCopy__CMSSW_3_2_6__WW__Summer09-MC_31X_V3-v1__GEN-SIM-RECO_1.root')

#   fileNames = cms.untracked.vstring('file:/user/xjanssen/data/CMSSW_3_8_3/DataCopy_38x/__EG__Run2010A-Sep17ReReco_v2__RECO/DataCopy_38x__CMSSW_3_8_3__EG__Run2010A-Sep17ReReco_v2__RECO_1_1_Okg.root')
#fileNames = cms.untracked.vstring('file:/user/xjanssen/data/CMSSW_3_8_4_patch2/DataCopy_384p2/__WWTo2L2Nu_TuneZ2_7TeV-pythia6__Fall10-START38_V12-v1__GEN-SIM-RECO/DataCopy_384p2__CMSSW_3_8_4_patch2__WWTo2L2Nu_TuneZ2_7TeV-pythia6__Fall10-START38_V12-v1__GEN-SIM-RECO_1_1_SMC.root')
#fileNames = cms.untracked.vstring('file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__EG__Run2010A-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__EG__Run2010A-Nov4ReReco_v1__RECO_1_2_A0r.root',
#                                  'file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__Electron__Run2010B-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__Electron__Run2010B-Nov4ReReco_v1__RECO_1_1_hLe.root') 
#				     )
fileNames = cms.untracked.vstring(
'file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__Mu__Run2010A-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__Mu__Run2010A-Nov4ReReco_v1__RECO_1_1_JCf.root',
'file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__Mu__Run2010B-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__Mu__Run2010B-Nov4ReReco_v1__RECO_1_2_4dK.root',
'file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__Mu__Run2010B-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__Mu__Run2010B-Nov4ReReco_v1__RECO_2_0_e1c.root',
'file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__Mu__Run2010B-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__Mu__Run2010B-Nov4ReReco_v1__RECO_3_0_bMl.root',
'file:/user/xjanssen/data/CMSSW_3_8_6/DataFetch_386_b/__Mu__Run2010B-Nov4ReReco_v1__RECO/DataFetch_386_b__CMSSW_3_8_6__Mu__Run2010B-Nov4ReReco_v1__RECO_4_0_qic.root'
))
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
#process.GlobalTag.globaltag = 'START3X_V26::All'
process.GlobalTag.globaltag = 'FT_R_38X_V14A::All'

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


process.jetvertexalpha = cms.EDProducer("JetVertexAssociation",
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
# ------ Jet Enenergy Corrections ----------

process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False




# ----- Trigger Selection --------------------

process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'
#process.mypath=cms.Path(process.hltPhysicsDeclared+<my_other_things_here>)


#---------------Beam scraping -------------------------


process.noscraping = cms.EDFilter("FilterOutScraping",
                                applyfilter = cms.untracked.bool(True),
                                debugOn = cms.untracked.bool(False),
                                numtrack = cms.untracked.uint32(10),
                                thresh = cms.untracked.double(0.25)
                                )





# Track Jets (>3_4_2)--------------------------------------------------------------

process.load("RecoJets.Configuration.RecoTrackJets_cff")

# -------------------Expected Hits Computer-------------------------------------




import HiggsAnalysis.HiggsToWW2Leptons.expectedHitsComputer_cfi

process.expectedHitsEle = HiggsAnalysis.HiggsToWW2Leptons.expectedHitsComputer_cfi.expectedHitsComputer.clone()
process.expectedHitsEle.inputColl   = cms.InputTag("gsfElectrons")
process.expectedHitsEle.useGsfTrack = cms.bool(True)

process.expectedHitsMu  = HiggsAnalysis.HiggsToWW2Leptons.expectedHitsComputer_cfi.expectedHitsComputer.clone()
process.expectedHitsMu.inputColl   = cms.InputTag("muons")
process.expectedHitsMu.useGsfTrack = cms.bool(False)

process.correctedExpectedHits = cms.Sequence(process.expectedHitsEle*process.expectedHitsMu)







# HWW Preselection ------------------------------------------------------------------

#process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWPreselectionSequence_cff")

# K-Factor Producer -----------------------------------------------------------------

#process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWKFactorProducer_cfi")
#process.KFactorProducer.inputFilename = cms.untracked.string('HiggsAnalysis/HiggsToWW2Leptons/data/160_7TeV.dat')

#HLT filter from PreSelection 

#process.higgsToWW2LeptonsHLTFilter.HLTPaths = ['HLT_L1MuOpen','HLT_L1Mu','HLT_Mu5','HLT_Mu9','HLT_L1DoubleMuOpen','HLT_DoubleMu0','HLT_DoubleMu3','HLT_L1SingleEG5','HLT_Ele15_SW_EleId_L1R','HLT_Ele15_SiStrip_L1R']

# UAHiggsTree Code ------------------------------------------------------------------
process.UAHiggsTree = cms.EDAnalyzer('UAHiggsTree'

  , fileName = cms.untracked.string('UAHiggsTree.root')
  # , fileName = cms.untracked.string('DataTreeEle.root')
   #, fileName = cms.untracked.string('DataTreeMu.root')
# Modules to execute
  , StoreGenPart     = cms.bool(False)
  , StoreGenKine     = cms.bool(False)
  , doJetVertexAlpha = cms.bool(False)


# Preselection

  , doSingleLeptonPreselection = cms.bool(False)
  , doLeptonPairPreselection   = cms.bool(True)
  , doRandomPreskim            = cms.bool(False)
  
  , singleLeptonPtCut          = cms.double(10)
  , leptonPairPtCut            = cms.double(10)
  , fractionOfEvents           = cms.double(1)   # insert number between 0 and 1


# Define DATA Collections
  , genPartColl   = cms.InputTag("genParticles") 
  , hepMCColl     = cms.InputTag("generator")
  , hcalIsolation = cms.InputTag("egammaTowerIsolation")
  , trckIsolation = cms.InputTag("egammaElectronTkRelIsolation")
  , bjets         = cms.InputTag("trackCountingHighEffBJetTags")
 
 
# Data Collections --------------------

  , requested_gsfelectrons = cms.vstring('gsfElectrons')#),'isolatedElectrons','selectedElectrons')
  , requested_muons        = cms.vstring('muons')#,'isolatedMuons','selectedMuons')
  
  , requested_genmets      = cms.vstring('genMetTrue')
  , requested_calomets     = cms.vstring('met')
  , requested_pfmets       = cms.vstring('pfMet')
  , requested_tcmets       = cms.vstring('tcMet')

  , requested_genjets      = cms.vstring('iterativeCone5GenJets')#'sisCone5GenJets')
  , requested_calojets     = cms.vstring('ak5CaloJets')
  , requested_pfjets       = cms.vstring('ak5PFJets','ak5PFJetsL2L3Residual')
  , requested_trackjets    = cms.vstring('ak5TrackJets')

  , requested_hlt_bits     = cms.vstring('HLT_L1MuOpen',
  					'HLT_L1Mu',
					'HLT_Mu5',
					'HLT_Mu9',
					'HLT_L1DoubleMuOpen',
					'HLT_DoubleMu0',
					'HLT_DoubleMu3',
					'HLT_Mu15_v1',
					'HLT_L1SingleEG5',
					'HLT_Ele10_LW_L1R',
					'HLT_Ele15_SW_L1R',
					'HLT_Ele15_SW_EleId_L1R',
					'HLT_Ele15_SiStrip_L1R',
					'HLT_Photon10_L1R',
					'HLT_Photon15_Cleaned_L1R',
					'HLT_Ele15_SW_CaloEleId_L1R',
					'HLT_Ele15_LW_L1R',
					'HLT_Ele17_SW_CaloEleId_L1R',
					'HLT_Ele17_SW_TightEleId_L1R',
					'HLT_Ele17_SW_TighterEleIdIsol_L1R_v2',
					'HLT_Ele17_SW_TighterEleIdIsol_L1R_v3'
					)
  , requested_L1_bits      = cms.vstring('L1_SingleMuOpen','L1_SingleMu0','L1_SingleMu7','L1_DoubleMu3','L1_SingleMu20','L1_SingleMu3','L1_DoubleMuOpen','L1_SingleEG1','L1_SingleEG2','L1_SingleEG5','L1_SingleEG8','L1_SingleEG20','L1_DoubleEG5')

  , requested_vertexs      = cms.vstring('offlinePrimaryVertices')
  , requested_tracks       = cms.vstring('generalTracks')#,'pixelTracks')


)


# Data output ----------------------------------------------------------------------- 
process.out = cms.OutputModule("PoolOutputModule",
    verbose = cms.untracked.bool(False),
    fileName = cms.untracked.string('cmsdata.root')
)


# PAth (what to do) ------------------------------------------------------------------
process.path = cms.Path( process.hltPhysicsDeclared*
                         process.noscraping*			 
#		         process.GenPartDecay * 
#                        process.GenPartTree *
#                        process.GenPartList *  
#                        process.KFactorProducer *
#        	         process.higgsToWW2LeptonsPreselectionSequence *
#                        process.recoAllTrackJets *

#			 process.jetvertexassociation *
#			 process.eleIsoDepositEcalFromHits *
#                        process.eleIsoFromDepsEcalFromHits *
#                        process.eleIsoDepositTk * 
                         process.correctedExpectedHits*
                         process.ak5PFJetsL2L3Residual*
			 process.UAHiggsTree
			    
                       )

# EndPath (what to store) ------------------------------------------------------------
process.outpath = cms.EndPath(process.out)


