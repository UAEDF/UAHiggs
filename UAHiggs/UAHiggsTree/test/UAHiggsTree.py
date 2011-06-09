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
#'file:/user/selvaggi/step2_RAW2DIGI_L1Reco_RECO_9_1_XqK.root'
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_100_1_5mB.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_101_1_0lI.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_10_1_jLy.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_102_1_QSr.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_103_1_eKQ.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_104_1_C1L.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_105_1_CxP.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_106_1_YiG.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_107_1_JGk.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_108_1_RjO.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_109_1_5Bb.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_11_2_qLm.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_1_1_uau.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_12_1_wBD.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_13_1_cCv.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_14_1_coy.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_15_1_tvK.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_16_1_1JP.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_17_1_ywv.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_18_1_GOS.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_19_1_zmN.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_20_1_Dcy.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_21_1_gCI.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_2_1_Pmm.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_22_1_BN4.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_23_1_rIa.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_24_1_8rf.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_25_1_NP6.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_26_1_cg7.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_27_1_Iqv.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_28_1_zXu.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_29_1_wEC.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_30_1_qTT.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_31_1_Dt1.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_3_1_9on.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_32_1_Efl.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_33_1_ysN.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_34_1_W4Z.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_35_1_1cf.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_36_1_Udr.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_37_1_LGq.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_38_1_9dQ.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_39_1_VRo.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_40_1_qSn.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_41_1_IlM.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_4_1_wQ4.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_42_2_nfj.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_43_1_5UF.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_44_1_K8K.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_45_1_mZD.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_46_1_XC7.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_47_1_Cdj.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_48_1_Dzq.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_49_1_YkG.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_50_1_Sxq.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_51_1_q1q.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_5_1_R6Z.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_52_1_gEr.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_53_1_Uw2.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_54_1_jPj.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_55_1_0Gf.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_56_1_vri.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_57_1_Jap.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_58_1_8BX.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_59_1_1y7.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_60_1_b5R.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_61_1_7XI.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_6_1_ZW3.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_62_1_PC9.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_63_1_xiS.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_64_1_qW0.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_65_1_F3d.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_66_1_uA2.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_67_3_LPj.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_68_1_m5m.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_69_1_UTb.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_70_1_2Os.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_71_1_JrB.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_7_1_b5A.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_72_1_pHC.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_73_1_Hj8.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_74_1_EK1.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_75_1_GW0.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_76_1_82g.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_77_1_VEE.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_78_1_CG5.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_79_1_w7D.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_80_1_AoM.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_81_1_42c.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_8_1_cMS.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_82_1_nTR.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_83_1_qJZ.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_84_1_N1n.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_85_1_agY.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_86_1_bCr.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_87_1_4yh.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_88_2_CGi.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_89_1_LIa.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_90_1_k2U.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_91_1_08M.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_9_1_ICb.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_92_1_grD.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_93_1_gvv.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_94_1_U2r.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_95_1_fgv.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_96_1_nya.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_97_1_pag.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_98_1_yCq.root',
#'file:/user/selvaggi/datasets/387/step2_RAW2DIGI_L1Reco_RECO_99_1_Ozl.root'
#'file:/user/selvaggi/step2_RAW2DIGI_L1Reco_RECO_9_4_HKd.root'			 
#'file:/user/selvaggi/BA62B277-02E4-DF11-941B-001EC9ED7E8F.root',				 
#'file:/user/selvaggi/7EFE3196-04E4-DF11-B926-00266CF25F34.root'
#'dcap:///pnfs/iihe/cms/store/user/xjanssen/data/CMSSW_3_9_7/DataCopy_397/__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__GEN-SIM-RECO/DataCopy_397__CMSSW_3_9_7__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__GEN-SIM-RECO_1_1_RJI.root')					 
#'dcap:///pnfs/iihe/cms/store/user/xjanssen/data/CMSSW_3_9_7/DataCopy_397/__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__AODSIM/DataCopy_397__CMSSW_3_9_7__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__AODSIM_1_2_auo.root'				 )
'file:/user/selvaggi/test_H160_Spring11.root')
#'dcap:///pnfs/iihe/cms/ph/sc4/store/mc/Spring11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S1_START311_V1G1-v1/0000/00BACB8D-114E-E011-A14C-485B39800C04.root')
#'file:/user/selvaggi/test_MuEG.root')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


# Data output ----------------------------------------------------------------------- 
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('cmsdata.root'),
    outputCommands  = cms.untracked.vstring('keep *')
)


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
process.GlobalTag.globaltag = 'START311_V1G1::All'
#process.GlobalTag.globaltag = 'GR_H_V15::All'

# ------ Jet Enenergy Corrections ----------
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.load('RecoJets.Configuration.RecoPFJets_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionServices_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff')


# ------ Calculate jet area A
#process.load('RecoJets.JetProducers.ak5PFJets_cfi')
process.ak5PFJets.doAreaFastjet = True
#process.ak5PFJets.Rho_EtaMax = cms.double(5.0)

process.ak5PFJetsEta = process.ak5PFJets.clone()
process.ak5PFJetsEta.doAreaFastjet = True
#process.ak5PFJetsEta.Rho_EtaMax = cms.double(5.0)
#process.ak5PFJetsEta.Ghost_EtaMax= cms.double(5.0)
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


process.ak5PFJetsNoPuL1Area  =  cms.EDProducer('HiL1Subtractor',
src        = cms.InputTag('ak5PFJetsNoPu'),
jetType    = cms.string('PFJet'),
rhoTag     = cms.string('kt6PFJetsNoPu'),
doUniform  = cms.bool(True)
)


process.ak5PFJetsL1Hyb  =  cms.EDProducer('L1HybridSubtractor',
src    = cms.InputTag('ak5PFJets'),
jetType    = cms.string('PFJet'),
rhoTag    = cms.string('kt6PFJets'),
corrFile  = cms.string('src/CondFormats/JetMETObjects/data/Fall10_L1Hybrid_AK5PF_v1.txt')
)


#------------------------------- PFnoPU jets ----------------------

from PhysicsTools.PatAlgos.tools.jetTools import *

process.load("PhysicsTools.PFCandProducer.pfNoPileUp_cff")  
process.pfPileUp.Enable = True    
process.pfPileUp.Vertices = "goodOfflinePrimaryVerticesDA"


# pat sequence
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

# Configure PAT to use PF2PAT instead of AOD sources
# this function will modify the PAT sequences. It is currently 
# not possible to run PF2PAT+PAT and standart PAT at the same time
#from PhysicsTools.PatAlgos.tools.pfTools import *
#postfix = "PFlow"

#usePF2PAT(process,runPF2PAT=True, jetAlgo='AK5', runOnMC=False, postfix=postfix)
#process.pfPileUpPFlow.Enable = True
#process.pfPileUpPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpPFlow.Vertices = cms.InputTag('goodOfflinePrimaryVerticesDA')
#process.pfJetsPFlow.doAreaFastjet = True
#process.pfJetsPFlow.doRhoFastjet = False

# Compute the mean pt per unit area (rho) from the
# PFchs inputs
#from RecoJets.JetProducers.kt4PFJets_cfi import kt4PFJets
#process.kt6PFJetsPFlow = kt4PFJets.clone(
#    rParam = cms.double(0.6),
#    src = cms.InputTag('pfNoElectron'+postfix),
#    doAreaFastjet = cms.bool(True),
#    doRhoFastjet = cms.bool(True),
#    voronoiRfact = cms.double(0.9)
#    )
#process.patJetCorrFactorsPFlow.rho = cms.InputTag("kt6PFJetsPFlow", "rho")
#process.patJetCorrFactorsPFlow.levels = ['L1FastJet','L2Relative','L3Absolute']

# Add the PV selector and KT6 producer to the sequence
##getattr(process,"patPF2PATSequence"+postfix).replace(
#    getattr(process,"pfNoElectron"+postfix),
#    getattr(process,"pfNoElectron"+postfix)*process.kt6PFJetsPFlow )

#process.patseq = cms.Sequence(    
#    process.goodOfflinePrimaryVerticesDA*
#    getattr(process,"patPF2PATSequence"+postfix)
#    )

# Adjust the event content
#process.out.outputCommands += [
#    'keep *_selectedPat*_*_*',
#    'keep *_goodOfflinePrimaryVerticesDA*_*_*',    
#    'keep double_*PFlow*_*_PAT'
#]











process.ak5PFJetsNoPu = process.ak5PFJets.clone(src = "pfNoPileUp")  
process.kt6PFJetsNoPu = process.kt6PFJets.clone(src = "pfNoPileUp")

process.ak5PFJetsNoPuL1FastJet      = cms.Sequence(process.kt6PFJetsNoPu * process.ak5PFJetsNoPu *  process.ak5PFJetsNoPuL1Area)
process.ak5PFJetsNoPuL1FastL2L3     = process.ak5PFJetsL2L3.clone(src = 'ak5PFJetsNoPuL1Area')
process.ak5PFJetsNoPuL1FastJetL2L3  = cms.Sequence(process.kt6PFJetsNoPu  *process.ak5PFJetsNoPu *  process.ak5PFJetsNoPuL1FastL2L3)


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

#process.ak5PFL2Relative.useCondDB = False
#process.ak5PFL3Absolute.useCondDB = False
#process.ak5PFResidual.useCondDB = False
#process.ak5PFL1Offset.useCondDB = False
#process.ak5PFL1FastJet.useCondDB = False

process.ak5PFL1Offset.useCondDB = False
process.ak5PFL1Fastjet.useCondDB  = False

process.ak5PFJetsL1Offset   = process.ak5PFJetsL2L3.clone(correctors = ['ak5PFL1Offset'])
process.ak5PFJetsL1Area     = process.ak5PFJetsL2L3.clone(correctors = ['ak5PFL1Fastjet'])


process.ak5PFJetsL1FastJet     = cms.Sequence(process.kt6PFJets    * process.ak5PFJets * process.ak5PFJetsL1Area)
process.ak5PFJetsL1FastJetEta  = cms.Sequence(process.kt6PFJetsEta * process.ak5PFJetsEta * process.ak5PFJetsL1FastEta)

process.ak5PFJetsL1OffsetL2L3  = process.ak5PFJetsL1L2L3.clone()
process.ak5PFJetsL1FastJetL2L3 = cms.Sequence(process.kt6PFJets *process.ak5PFJets *  process.ak5PFJetsL1FastL2L3)

process.ak5PFJetsL1FastEtaL2L3    = process.ak5PFJetsL2L3.clone(src = 'ak5PFJetsL1FastEta')
process.ak5PFJetsL1FastJetEtaL2L3 = cms.Sequence(process.kt6PFJetsEta *process.ak5PFJetsEta *  process.ak5PFJetsL1FastEtaL2L3)


process.ak5PFJetsL1HybL2L3  = process.ak5PFJetsL2L3.clone(src = 'ak5PFJetsL1Hyb')
process.ak5PFJetsL1HybridL2L3 = cms.Sequence(process.kt6PFJets *process.ak5PFJets *  process.ak5PFJetsL1HybL2L3)









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
    correctors = cms.vstring('ak5PFL1OffsetDA','ak5PFL2Relative','ak5PFL3Absolute')
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

process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWKFactorProducer_cfi")
process.KFactorProducer.inputFilename = cms.untracked.string('HiggsAnalysis/HiggsToWW2Leptons/data/scalefactor.mh160.dat')

#HLT filter from PreSelection 

#process.higgsToWW2LeptonsHLTFilter.HLTPaths = ['HLT_L1MuOpen','HLT_L1Mu','HLT_Mu5','HLT_Mu9','HLT_L1DoubleMuOpen','HLT_DoubleMu0','HLT_DoubleMu3','HLT_L1SingleEG5','HLT_Ele15_SW_EleId_L1R','HLT_Ele15_SiStrip_L1R']

# UAHiggsTree Code ------------------------------------------------------------------
process.UAHiggsTree = cms.EDAnalyzer('UAHiggsTree'

  , fileName = cms.untracked.string('UAHiggsTree.root')

# Modules to execute
  , StoreGenPart     = cms.bool(True)
  , StoreGenKine     = cms.bool(True)
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

  , requested_hlt_bits     = cms.vstring('HLT_DoubleMu5_v',
                                         'HLT_Mu21_v',
                                         'HLT_IsoMu17_v',
					 'HLT_Mu5_Ele17_v',
					 'HLT_Mu11_Ele8_v',
                                         'HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v'
                                         )
  , requested_L1_bits      = cms.vstring('L1_SingleMuOpen','L1_SingleMu0','L1_SingleMu7','L1_DoubleMu3','L1_SingleMu20','L1_SingleMu3','L1_DoubleMuOpen','L1_SingleEG1','L1_SingleEG2','L1_SingleEG5','L1_SingleEG8','L1_SingleEG20','L1_DoubleEG5')

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




# PAth (what to do) ------------------------------------------------------------------
process.path = cms.Path( process.hltPhysicsDeclared*
                         process.noscraping*			 
		       #  process.FakeAlignmentSource*
		       #  process.GenPartDecay * 
                       #  process.GenPartTree *
                       #  process.GenPartList *  
                         process.KFactorProducer *
#        	         process.higgsToWW2LeptonsPreselectionSequence *
#                         process.recoAllTrackJets *
#                         process.produceAk5GenJets*
                         process.offlinePrimaryVerticesDA*		        
                         process.chargedMetProducer*
                         process.chargedPlusNeutralMetProducer*
		         process.goodOfflinePrimaryVerticesDA*		        
		#	 process.patseq*
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


