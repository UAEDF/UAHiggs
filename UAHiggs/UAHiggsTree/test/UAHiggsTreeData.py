# Import configurations
import FWCore.ParameterSet.Config as cms

#from Configuration.StandardSequences.Generator_cff import *
#from RecoJets.Configuration.RecoGenJets_cff import *
#from RecoJets.Configuration.GenJetParticles_cff import *

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
#process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
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
fileNames = cms.untracked.vstring(
#'dcap:///pnfs/iihe/cms/store/user/xjanssen/data/CMSSW_3_9_7/DataCopy_397/__Electron__Run2010B-Dec22ReReco_v1__RECO/DataCopy_397__CMSSW_3_9_7__Electron__Run2010B-Dec22ReReco_v1__RECO_1_1_Cru.root',				  
#'file:/user/selvaggi/step2_RAW2DIGI_L1Reco_RECO_9_4_HKd.root'			 
#'file:/user/selvaggi/BA62B277-02E4-DF11-941B-001EC9ED7E8F.root',				 
#'file:/user/selvaggi/7EFE3196-04E4-DF11-B926-00266CF25F34.root'
#'dcap:///pnfs/iihe/cms/store/user/xjanssen/data/CMSSW_3_9_7/DataCopy_397/__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__GEN-SIM-RECO/DataCopy_397__CMSSW_3_9_7__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__GEN-SIM-RECO_1_1_RJI.root')					 
#'dcap:///pnfs/iihe/cms/store/user/xjanssen/data/CMSSW_3_9_7/DataCopy_397/__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__AODSIM/DataCopy_397__CMSSW_3_9_7__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__AODSIM_1_2_auo.root'				 )
#'file:/user/selvaggi/'file:/user/selvaggi/test_H160_Spring11.root')
#'file:/user/selvaggi/'file:/user/selvaggi/test_DoubleMu.root'
#'file:/user/selvaggi/test_2011data/0C4C6809-EC53-E011-B373-003048F118AA.root',
#'file:/user/selvaggi/test_2011data/10BEBABB-AE52-E011-BC0E-0030487C7392.root',
#'file:/user/selvaggi/test_2011data/14717021-5453-E011-BFA3-001D09F29146.root',
#'file:/user/selvaggi/test_2011data/1C5B9D31-8D54-E011-85EE-0030487CD7B4.root',
#'file:/user/selvaggi/test_2011data/1E542106-9454-E011-940B-0030487CD14E.root',
#'file:/user/selvaggi/test_2011data/2AE3BC0B-9954-E011-86CB-003048F11C5C.root',
#'file:/user/selvaggi/test_2011data/2C4072F5-8B54-E011-9481-0030487CD7E0.root',
#'file:/user/selvaggi/test_2011data/2EFC0B8D-1554-E011-AD06-0030487CBD0A.root',
#'file:/user/selvaggi/test_2011data/34346E5D-6854-E011-9353-000423D987E0.root',
#'file:/user/selvaggi/test_2011data/367129C0-D453-E011-9BE9-0030487CD6F2.root',
#'file:/user/selvaggi/test_2011data/40A4ED22-0C54-E011-98C2-001617DBD5AC.root',
#'file:/user/selvaggi/test_2011data/40D5C869-1854-E011-AEF7-0030487C8E00.root',
#'file:/user/selvaggi/test_2011data/44DDA8D2-4554-E011-8524-000423D33970.root',
#'file:/user/selvaggi/test_2011data/54623440-0C55-E011-894C-001D09F2906A.root',
#'file:/user/selvaggi/test_2011data/5696FE52-8753-E011-A826-0030487CD6E8.root',
#'file:/user/selvaggi/test_2011data/5A2F688C-C354-E011-AF51-0030487C608C.root',
#'file:/user/selvaggi/test_2011data/5ADB6543-EB53-E011-AD21-003048F110BE.root',
#'file:/user/selvaggi/test_2011data/5CB739D0-9452-E011-BEF7-001D09F2924F.root',
#'file:/user/selvaggi/test_2011data/6056C9A5-3554-E011-B033-001D09F253C0.root',
#'file:/user/selvaggi/test_2011data/64FA48EE-9754-E011-B022-000423D996C8.root',
#'file:/user/selvaggi/test_2011data/68438EE0-4054-E011-AB93-003048CFB40C.root',
#'file:/user/selvaggi/test_2011data/82CAF258-8654-E011-890A-003048F1BF68.root',
#'file:/user/selvaggi/test_2011data/82D09EAF-1355-E011-8683-001D09F2841C.root',
#'file:/user/selvaggi/test_2011data/963910BD-5E54-E011-97C7-000423D9890C.root',
#'file:/user/selvaggi/test_2011data/9C908216-A954-E011-A230-003048CFB40C.root',
#'file:/user/selvaggi/test_2011data/9E483420-8A53-E011-8AF7-001D09F24FBA.root',
#'file:/user/selvaggi/test_2011data/A47B0830-9053-E011-ADAE-0030487CD13A.root',
#'file:/user/selvaggi/test_2011data/AA4AFBD2-F753-E011-8640-003048F024E0.root',
#'file:/user/selvaggi/test_2011data/AC7C51CA-F853-E011-B24F-001617E30D4A.root',
#'file:/user/selvaggi/test_2011data/B0613FDA-1555-E011-9778-003048F118D2.root',
#'file:/user/selvaggi/test_2011data/B289BC36-AE54-E011-B242-001D09F24498.root',
#'file:/user/selvaggi/test_2011data/B6CE0D8F-CB53-E011-A605-003048F118AC.root',
#'file:/user/selvaggi/test_2011data/C2B9928F-FD54-E011-B0CC-001D09F23A84.root',
#'file:/user/selvaggi/test_2011data/C45F1631-4054-E011-9DFF-001D09F291D7.root',
#'file:/user/selvaggi/test_2011data/C487B619-EE54-E011-BD7C-0030487CD178.root',
#'file:/user/selvaggi/test_2011data/C80C856D-8A53-E011-9C96-001617C3B6CC.root',
#'file:/user/selvaggi/test_2011data/C8B7E91D-F154-E011-B7BA-001617E30F50.root',
#'file:/user/selvaggi/test_2011data/D21DCE6D-5F51-E011-A17D-0030487C7828.root',
#'file:/user/selvaggi/test_2011data/D236C873-8751-E011-8FF5-0030487A18D8.root',
#'file:/user/selvaggi/test_2011data/E2F8B39E-0955-E011-8157-001D09F23944.root',
#'file:/user/selvaggi/test_2011data/F28C7DA0-0454-E011-98A9-003048D2C0F2.root',
#'file:/user/selvaggi/test_2011data/F430BC90-E453-E011-86FB-001D09F23944.root',
#'file:/user/selvaggi/test_2011data/F8799441-3B54-E011-A426-001D09F2A690.root',
#'file:/user/selvaggi/test_2011data/F88D52FF-F054-E011-AA2E-001D09F24DDA.root')
'dcap://maite.iihe.ac.be/pnfs/iihe/cms/ph/sc4/store/data/Run2011A/DoubleMu/AOD/PromptReco-v2/000/162/803/009F5D68-9A69-E011-AFAA-003048F1182E.root')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

# L1 extra --------------------------------------------------------------------------
#process.load("L1Trigger.L1ExtraFromDigis.l1extra_cff")
#process.load("EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi")
#process.l1GtUnpack.DaqGtInputTag = 'source'http://hari.b-rail.be/HAFAS/bin/query.exe/fn?seqnr=3&ident=g6.02642811.1298043529&REQ0HafasScrollDir=1
#process.load("L1Trigger.L1ExtraFromDigis.l1extraParticles_cff")


# gen particles printouts -----------------------------------------------------------
#process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
#process.ak5PFL2Relative.useCondDB = False
#process.ak5PFL3Absolute.useCondDB = False
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

#process.GlobalTag.globaltag = 'START38_V12::All'
#process.GlobalTag.globaltag = 'START39_V8::All'
#process.GlobalTag.globaltag = 'START311_V1G1::All'
#process.GlobalTag.globaltag = 'GR_P_V14::All'
process.GlobalTag.globaltag = 'GR_P_V17::All'

# ------ Jet Enenergy Corrections ----------
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.load('RecoJets.Configuration.RecoPFJets_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionServices_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff')


process.ak5PFResidual.era = cms.string('JEC10V1')

# ------ Calculate jet area A
#process.load('RecoJets.JetProducers.ak5PFJets_cfi')
process.ak5PFJets.doAreaFastjet = True
#process.ak5PFJets.Rho_EtaMax = cms.double(4.5)

process.ak5PFJetsEta = process.ak5PFJets.clone()
process.ak5PFJetsEta.doAreaFastjet = True
#process.ak5PFJetsEta.Rho_EtaMax = cms.double(4.5)
#process.ak5PFJetsEta.Ghost_EtaMax= cms.double(7.5)
#process.ak5PFJetsEta.GhostArea = cms.double(0.005)


#------- Calculate event rho
#process.load('RecoJets.JetProducers.kt4PFJets_cfi')
#process.kt6PFJets = process.kt4PFJets.clone( rParam = 0.6, doRhoFastjet = True, doAreaFastjet = True, Rho_EtaMax= cms.double(4.4) )
process.kt6PFJets.doRhoFastjet = True
process.kt6PFJets.Rho_EtaMax= cms.double(4.5)
process.kt6PFJets.Ghost_EtaMax = cms.double(5.0)

process.kt6PFJetsIso = process.kt6PFJets.clone()
process.kt6PFJetsIso.doRhoFastjet = True
process.kt6PFJetsIso.Rho_EtaMax= cms.double(2.5)


process.kt6PFJetsEta = process.kt6PFJets.clone()
process.kt6PFJetsEta.doRhoFastjet = True
process.kt6PFJetsEta.Rho_EtaMax= cms.double(5.0)
#process.kt6PFJetsEta.Rho_EtaMax= cms.double(5)
process.kt6PFJetsEta.doFastJetNonUniform = cms.bool(True)
process.kt6PFJetsEta.Ghost_EtaMax= cms.double(7.5)
#process.kt6PFJetsEta.puCenters = cms.vdouble( -5,-4, -3, -2, -1, 0, 1, 2, 3, 4,5)
process.kt6PFJetsEta.puCenters = cms.vdouble(-5.0,0.0,5.0)
process.kt6PFJetsEta.nExclude = cms.uint32(0)
#process.kt6PFJetsEta.GhostArea = cms.double(0.005)
#process.kt6PFJetsEta.puWidth = cms.double(1)
process.kt6PFJetsEta.puWidth   = cms.double(2.5)

process.ak5PFJetsL1FastEta  =  cms.EDProducer('HiL1Subtractor',
src    = cms.InputTag('ak5PFJetsEta'),
jetType    = cms.string('PFJet'),
rhoTag    = cms.string('kt6PFJetsEta'),
doUniform = cms.bool(False)
)

process.ak5PFJetsL1Hyb  =  cms.EDProducer('L1HybridSubtractor',
src    = cms.InputTag('ak5PFJets'),
jetType    = cms.string('PFJet'),
rhoTag    = cms.string('kt6PFJets'),
corrFile  = cms.string('CondFormats/JetMETObjects/data/Fall10_L1Hybrid_AK5PF_v1.txt')
)

process.ak5PFJetsNoPuL1Area  =  cms.EDProducer('HiL1Subtractor',
src        = cms.InputTag('ak5PFJetsNoPu'),
jetType    = cms.string('PFJet'),
rhoTag     = cms.string('kt6PFJetsNoPu'),
doUniform  = cms.bool(True)
)

#------- Configure Jet Energy Correction Producer
#process.load('JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff')
#process.L1Fastjet.algorithm = cms.string('AK5Calo') #DUMMY needs to read an existing file
#process.L1Fastjet.era = 'Spring10'                  #DUMMY needs to read an existing file
#process.L1Fastjet.level = cms.string('L2Relative') #DUMMY needs to read an existing file
#process.L1Fastjet.useCondDB = cms.untracked.bool(False)
#process.L1Fastjet.srcMedianPt = cms.InputTag('kt6PFJets','rho') 

#process.ak5PFJetsL1Fastjet = process.ak5PFL1Fastjet.clone( srcMedianPt = cms.InputTag('kt6PFJets','rho') )

#process.ak5PFJetsL1Area = cms.Sequence( process.ak5PFJets * process.kt6PFJets * process.ak5PFJetsL1FastJet )




#process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionProducers_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff')

process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False
process.ak5PFResidual.era = cms.string('Jec10V1')

process.ak5PFL1Offset.useCondDB = False
process.ak5PFL1Fastjet.useCondDB  = False

process.ak5PFJetsL1Offset   = process.ak5PFJetsL2L3.clone(correctors = ['ak5PFL1Offset'])
process.ak5PFJetsL1Area     = process.ak5PFJetsL2L3.clone(correctors = ['ak5PFL1Fastjet'])

process.ak5PFJetsL1FastJet  = cms.Sequence(process.kt6PFJets* process.ak5PFJets * process.ak5PFJetsL1Area)
process.ak5PFJetsL1FastJetEta  = cms.Sequence(process.kt6PFJetsEta * process.ak5PFJetsEta * process.ak5PFJetsL1FastEta)

process.ak5PFJetsL2L3 = process.ak5PFJetsL2L3Residual.clone()
process.ak5PFJetsL1FastL2L3 = process.ak5PFJetsL1FastL2L3Residual.clone()

process.ak5PFJetsL1OffsetL2L3  = process.ak5PFJetsL1L2L3Residual.clone()
process.ak5PFJetsL1FastJetL2L3 = cms.Sequence(process.kt6PFJets *process.ak5PFJets *  process.ak5PFJetsL1FastL2L3)

process.ak5PFJetsL1FastEtaL2L3 = process.ak5PFJetsL2L3Residual.clone(src = 'ak5PFJetsL1FastEta')
process.ak5PFJetsL1FastJetEtaL2L3 = cms.Sequence(process.kt6PFJetsEta *process.ak5PFJetsEta *  process.ak5PFJetsL1FastEtaL2L3)

process.ak5PFJetsL1HybL2L3  = process.ak5PFJetsL2L3Residual.clone(src = 'ak5PFJetsL1Hyb')
process.ak5PFJetsL1HybridL2L3 = cms.Sequence(process.kt6PFJets *process.ak5PFJets *  process.ak5PFJetsL1HybL2L3)





#------------------------------- PFnoPU jets ----------------------

from PhysicsTools.PatAlgos.tools.jetTools import *

process.load("PhysicsTools.PFCandProducer.pfNoPileUp_cff")  
process.pfPileUp.Enable = True    
process.pfPileUp.Vertices = "goodOfflinePrimaryVerticesDA"

process.ak5PFJetsNoPu = process.ak5PFJets.clone(src = "pfNoPileUp")  
process.kt6PFJetsNoPu = process.kt6PFJets.clone(src = "pfNoPileUp")

process.ak5PFJetsNoPuL1FastJet      = cms.Sequence(process.kt6PFJetsNoPu * process.ak5PFJetsNoPu *  process.ak5PFJetsNoPuL1Area)
process.ak5PFJetsNoPuL1FastL2L3     = process.ak5PFJetsL2L3.clone(src = 'ak5PFJetsNoPuL1Area')
process.ak5PFJetsNoPuL1FastJetL2L3  = cms.Sequence(process.kt6PFJetsNoPu  *process.ak5PFJetsNoPu *  process.ak5PFJetsNoPuL1FastL2L3)



# ---- With DA Vertex -------

process.ak5CaloL1OffsetDA = cms.ESSource(
    'L1OffsetCorrectionService',
    era = cms.string('Jec10V1'),
    level = cms.string('L1Offset'),
    section   = cms.string(''),
    algorithm = cms.string('AK5Calo'),
    useCondDB = cms.untracked.bool(False),
    vertexCollection = cms.string('offlinePrimaryVerticesDA'),
    minVtxNdof = cms.int32(4)
    )

process.ak5PFL1OffsetDA = process.ak5CaloL1OffsetDA.clone(algorithm = 'AK5PF')


process.ak5PFL1DAL2L3 = cms.ESSource(
    'JetCorrectionServiceChain',
    correctors = cms.vstring('ak5PFL1OffsetDA','ak5PFL2Relative','ak5PFL3Absolute','ak5PFResidual')
    )

process.ak5PFJetsL1OffsetDA       = process.ak5PFJetsL2L3.clone(correctors = ['ak5PFL1OffsetDA'])
process.ak5PFJetsL1OffsetDAL2L3   = process.ak5PFJetsL2L3.clone(correctors = ['ak5PFL1DAL2L3']) 



#--------------- b- tagging ------------

# b-tagging general configuration
from RecoJets.JetAssociationProducers.ic5JetTracksAssociatorAtVertex_cfi import *
from RecoBTag.Configuration.RecoBTag_cff import *

# create a new jets and tracks association
process.JTAVak5PFJets = ic5JetTracksAssociatorAtVertex.clone()
process.JTAVak5PFJets.jets   = "ak5PFJets"
process.JTAVak5PFJets.tracks = "generalTracks"

process.IPTIak5PFJets = impactParameterTagInfos.clone()
process.IPTIak5PFJets.jetTracks = "JTAVak5PFJets"
process.IPTIak5PFJets.primaryVertex = "offlinePrimaryVerticesDA"

process.JTAVak5PFJetsL1OffsetDAL2L3 = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsL1OffsetDAL2L3")
process.JTAVak5PFJetsL1OffsetL2L3   = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsL1OffsetL2L3")
process.JTAVak5PFJetsL1FastL2L3     = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsL1FastL2L3")
process.JTAVak5PFJetsL1FastEtaL2L3  = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsL1FastEtaL2L3")
process.JTAVak5PFJetsL2L3           = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsL2L3")
process.JTAVak5PFJetsL1HybL2L3      = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsL1HybL2L3")
process.JTAVak5PFJetsNoPuL1FastL2L3 = process.JTAVak5PFJets.clone(jets   = "ak5PFJetsNoPuL1FastL2L3")

process.IPTIak5PFJetsL1OffsetDAL2L3  = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsL1OffsetDAL2L3")
process.IPTIak5PFJetsL1OffsetL2L3    = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsL1OffsetL2L3")
process.IPTIak5PFJetsL1FastL2L3      = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsL1FastL2L3")
process.IPTIak5PFJetsL1FastEtaL2L3   = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsL1FastEtaL2L3")
process.IPTIak5PFJetsL2L3            = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsL2L3")
process.IPTIak5PFJetsL1HybL2L3       = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsL1HybL2L3")
process.IPTIak5PFJetsNoPuL1FastL2L3  = process.impactParameterTagInfos.clone(jetTracks = "JTAVak5PFJetsNoPuL1FastL2L3")

process.TCHEak5PFJets                  = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJets")))
process.TCHEak5PFJetsL1OffsetDAL2L3    = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsL1OffsetDAL2L3")))
process.TCHEak5PFJetsL1OffsetL2L3      = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsL1OffsetL2L3")))
process.TCHEak5PFJetsL1FastL2L3        = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsL1FastL2L3")))
process.TCHEak5PFJetsL1FastEtaL2L3     = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsL1FastEtaL2L3")))
process.TCHEak5PFJetsL2L3              = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsL2L3")))
process.TCHEak5PFJetsL1HybL2L3         = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsL1HybL2L3")))
process.TCHEak5PFJetsNoPuL1FastL2L3    = trackCountingHighEffBJetTags.clone(tagInfos = cms.VInputTag(cms.InputTag("IPTIak5PFJetsNoPuL1FastL2L3")))


process.JetBtaggingIP = cms.Sequence(
    process.JTAVak5PFJets*
    process.JTAVak5PFJetsL1OffsetDAL2L3*
    process.JTAVak5PFJetsL1OffsetL2L3*
    process.JTAVak5PFJetsL1FastL2L3*
    process.JTAVak5PFJetsL1FastEtaL2L3*
    process.JTAVak5PFJetsL2L3*
    process.JTAVak5PFJetsL1HybL2L3*
    process.JTAVak5PFJetsNoPuL1FastL2L3*
    
    process.IPTIak5PFJets* 
    process.IPTIak5PFJetsL1OffsetDAL2L3* 
    process.IPTIak5PFJetsL1OffsetL2L3* 
    process.IPTIak5PFJetsL1FastL2L3* 
    process.IPTIak5PFJetsL1FastEtaL2L3* 
    process.IPTIak5PFJetsL2L3* 
    process.IPTIak5PFJetsL1HybL2L3* 
    process.IPTIak5PFJetsNoPuL1FastL2L3* 
    
    process.TCHEak5PFJets*
    process.TCHEak5PFJetsL1OffsetDAL2L3*
    process.TCHEak5PFJetsL1OffsetL2L3*
    process.TCHEak5PFJetsL1FastL2L3* 
    process.TCHEak5PFJetsL1FastEtaL2L3* 
    process.TCHEak5PFJetsL2L3*
    process.TCHEak5PFJetsL1HybL2L3*
    process.TCHEak5PFJetsNoPuL1FastL2L3 
     





)   

#------ Create GenJet collections -------------

process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff") 
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")
process.load('RecoJets.JetProducers.ak5GenJets_cfi')
process.produceAk5GenJets = cms.Sequence(process.genParticlesForJets*process.ak5GenJets)




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


#----------------- Likelihood Electron Id --------------------------

process.load("RecoEgamma.ElectronIdentification.electronIdLikelihoodExt_cfi")
process.electronIDLH = process.eidLikelihoodExt.clone()





# Track Jets (>3_4_2)--------------------------------------------------------------

process.load("RecoJets.Configuration.RecoTrackJets_cff")


# TransientTrack + 3D ID Boris stuff -----------------------------------------------

process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")





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

# Modules to execute
  , StoreGenPart     = cms.bool(False)
  , StoreGenKine     = cms.bool(False)
  , doJetVertexAlpha = cms.bool(False)


# Preselection

  , doSingleLeptonPreselection = cms.bool(True)
  , doLeptonPairPreselection   = cms.bool(True)
  , doRandomPreskim            = cms.bool(False)
  
  , singleLeptonPtCut          = cms.double(20)
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

  , requested_genjets      = cms.vstring('ak5GenJets')#'sisCone5GenJets')
  , requested_calojets     = cms.vstring('ak5CaloJets')
  , requested_pfjets       = cms.vstring('ak5PFJets',
                                         #'ak5PFJetsL1Offset',
                                         #'ak5PFJetsL1Area',
                                        # 'ak5PFJetsL1Hyb',
                                         'ak5PFJetsL1HybL2L3',
                                         'ak5PFJetsL2L3',
                                         'ak5PFJetsL1OffsetL2L3',
                                         'ak5PFJetsL1FastL2L3',
                                         'ak5PFJetsL1FastEtaL2L3',
                                        # 'ak5PFJetsL1OffsetDA',
					 'ak5PFJetsL1OffsetDAL2L3',
					# 'ak5PFJetsL1FastEta',
					# 'ak5PFJetsNoPuL1Area',
					 'ak5PFJetsNoPuL1FastL2L3'
                                         )#'kt6PFJetsL2L3','kt6PFJetsPUL2L3',)
                                         
  , requested_trackjets    = cms.vstring('ak5TrackJets')

  , requested_hlt_bits     = cms.vstring('HLT_DoubleMu7_v',
					'HLT_Mu24_v',
					'HLT_IsoMu17_v',
					'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v',
					'HLT_Mu17_Ele8_CaloIdL_v',
					'HLT_Mu8_Ele17_CaloIdL_v',
					)
  , requested_L1_bits      = cms.vstring('L1_DoubleMu0',
                                         'L1_DoubleMu3',
					 'L1_SingleEG12',
					 'L1_SingleMu7',
					 'L1_Mu3_EG5' )

  , requested_vertexs      = cms.vstring('offlinePrimaryVertices','offlinePrimaryVerticesDA')#,'offlinePrimaryVerticesWithBS')
  , requested_tracks       = cms.vstring('generalTracks')#,'pixelTracks')
  , requested_neutrals     = cms.vstring('particleFlow')


)


# Charged MET producer from Boris et al. --------------------------------------------
process.load("WWAnalysis.Tools.chargedMetProducer_cfi")
process.chargedMetProducer.vertexTag = "offlinePrimaryVerticesDA"
process.chargedMetProducer.collectionTag = "particleFlow"
process.chargedPlusNeutralMetProducer = process.chargedMetProducer.clone()
process.chargedPlusNeutralMetProducer.addNeutrals = True


# DA vertex -------------------------------------------------------------------------

from RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi import *

#process.load("Alignment.CommonAlignmentProducer.FakeAlignmentSource_cfi")
#process.preferFakeAlign = cms.ESPrefer("FakeAlignmentSource") 


process.offlinePrimaryVerticesDA = cms.EDProducer("PrimaryVertexProducer",
    verbose = cms.untracked.bool(False),
    algorithm = cms.string('AdaptiveVertexFitter'),
    TrackLabel = cms.InputTag("generalTracks"),
    useBeamConstraint = cms.bool(True),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    minNdof  = cms.double(0.0),
    PVSelParameters = cms.PSet(
        maxDistanceToBeam = cms.double(2.0)
    ),
    TkFilterParameters = cms.PSet(
        algorithm=cms.string('filter'),
        maxNormalizedChi2 = cms.double(5.0),
        minPixelLayersWithHits=cms.int32(2),
        minSiliconLayersWithHits = cms.int32(5),
        maxD0Significance = cms.double(5.0), 
        minPt = cms.double(0.0),
        trackQuality = cms.string("any")
    ),

    TkClusParameters = cms.PSet(
        algorithm   = cms.string("DA"),
        TkDAClusParameters = cms.PSet( 
            coolingFactor = cms.double(0.8),  #  rather slow annealing for now
            Tmin = cms.double(4.),            #  end of annealing
            vertexSize = cms.double(0.01)     #  ~ resolution
        )
    )
)



from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector

process.goodOfflinePrimaryVerticesDA = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(7.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlinePrimaryVerticesDA')
    )






# Data output ----------------------------------------------------------------------- 
#process.out = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string('cmsdata.root')
#)


# PAth (what to do) ------------------------------------------------------------------
process.path = cms.Path( process.hltPhysicsDeclared*
                         process.noscraping*			 
		       #  process.FakeAlignmentSource*
		       #  process.GenPartDecay * 
                       #  process.GenPartTree *
                       #  process.GenPartList *  
#                        process.KFactorProducer *
#        	         process.higgsToWW2LeptonsPreselectionSequence *
#                         process.recoAllTrackJets *
#                         process.produceAk5GenJets*
                         process.offlinePrimaryVerticesDA*		        
                         process.chargedMetProducer*
                         process.chargedPlusNeutralMetProducer*
			 process.goodOfflinePrimaryVerticesDA*		        
			 process.pfNoPileUpSequence*
			 process.electronIDLH*
			 process.kt6PFJetsIso*
			 process.ak5PFJetsNoPuL1FastJet*      
                         process.ak5PFJetsL1OffsetDA*
                         process.ak5PFJetsL1FastJetEta*
			 process.ak5PFJetsL1Offset*
		         process.ak5PFJetsL1FastJet*
			 process.ak5PFJetsL1Hyb*
			 process.ak5PFJetsL2L3*
                         process.ak5PFJetsL1OffsetL2L3*
			 process.ak5PFJetsL1OffsetDAL2L3*
			 process.ak5PFJetsL1FastJetL2L3*
                         process.ak5PFJetsL1FastJetEtaL2L3*
                         process.ak5PFJetsL1HybridL2L3*
			 process.ak5PFJetsNoPuL1FastJetL2L3*
                         process.JetBtaggingIP*
		         process.UAHiggsTree
			  
			  
			     )

# EndPath (what to store) ------------------------------------------------------------
#process.outpath = cms.EndPath(process.out)


