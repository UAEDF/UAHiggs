import FWCore.ParameterSet.Config as cms

process = cms.Process("H2WW2emu")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")

process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")

process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWPreselectionSequence_cff")
process.load("HiggsAnalysis.HiggsToWW2Leptons.HWWKFactorProducer_cfi")
process.load("RecoEcal.EgammaClusterProducers.ecalClusteringSequence_cff")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.MessageLogger = cms.Service("MessageLogger")

process.jetvertexalpha = cms.EDFilter("JetVertexAssociation",
    JV_deltaZ = cms.double(0.3),
    TRACK_ALGO = cms.string('generalTracks'),
    JV_alpha_threshold = cms.double(0.0),
    JET_ALGO = cms.string('iterativeCone5CaloJets'),
    JV_type_Algo = cms.int32(1),
    JV_cone_size = cms.double(0.5),
    VERTEX_ALGO = cms.string('offlinePrimaryVertices'),
    JV_cutType = cms.string('delta'),
    JV_sigmaZ = cms.double(9.5)
)

process.myanalysis = cms.EDAnalyzer("HWWAnalyzer",

    CheckMCTruth = cms.string('OnReco'),
    StoreTracks = cms.bool(False),
    HistOutFile = cms.untracked.string('outH16021X.root'),
    ItIsASoup = cms.bool(False),

    EleHcalIsolationParameters = cms.PSet(
        IsoConeSizeOut = cms.double(0.4),
        IsoConeSizeIn = cms.double(0.1),
        IsoPtMin = cms.double(0.0)
    ),

    EleEcalIsolationParameters = cms.PSet(
        IsoConeSizeOut = cms.double(0.4),
        IsoConeSizeIn = cms.double(0.1),
        IsoPtMin = cms.double(0.0)
    ),

    BarrelClusters = cms.InputTag("hybridSuperClusters:hybridShapeAssoc"),
#    EndCapClusters = cms.InputTag("islandBasicClusters:islandEndcapShapeAssoc"),
    EndCapClusters = cms.InputTag("multi5x5BasicClusters:multi5x5EndcapShapeAssoc"),
    towers = cms.InputTag("towerMaker"),
    met = cms.InputTag("muonCorrectedMET"),
    PFmet = cms.InputTag("pfMet"),
    tracks = cms.InputTag("generalTracks"),
    bjets = cms.InputTag("trackCountingHighPurBJetTags"),
    jets = cms.InputTag("iterativeCone5CaloJets"),
    PFjetsIC5 = cms.InputTag("iterativeCone5PFJets"),
    PFjetsSC5 = cms.InputTag("sisCone5PFJets"),
    preselectedelectrons = cms.InputTag("isolatedElectronsRef"),
    preselectedmuons = cms.InputTag("isolatedMuons"),
    channels = cms.vstring('all'),
    requested_hlt_bits = cms.vstring('HLT_IsoEle15_L1I','HLT_IsoEle18_L1R','HLT_IsoEle15_LW_L1I','HLT_LooseIsoEle15_LW_L1R','HLT_Ele10_SW_L1R','HLT_Ele15_SW_L1R','HLT_Ele15_LW_L1R','HLT_IsoMu9', 'HLT_IsoMu11','HLT_IsoMu13', 'HLT_IsoMu15','HLT_Mu3','HLT_Mu5','HLT_Mu7','HLT_Mu9','HLT_Mu11','HLT_Mu13','HLT_Mu15'),
    PrintHLTNames = cms.bool(False),                                 
    TrackIsolationLabel = cms.string("eleIsoDepositTk"),
    EcalJurassicIsolationLabel = cms.string("eleIsoFromDepsEcalFromHits"),
    WhichElectronID = cms.string("eidTight"),
    KFactorLabel = cms.string("kf160"),    
    Process_ID = cms.string('')
)

process.load('RecoEgamma.EgammaIsolationAlgos.eleIsoFromDepsModules_cff')

import HiggsAnalysis.HiggsToWW2Leptons.HWWKFactorProducer_cfi as mykf
process.kf160 = mykf.KFactorProducer.clone(
    inputFilename = cms.untracked.string('HiggsAnalysis/HiggsToWW2Leptons/data/160_10TeV.dat'),
    Debug =cms.untracked.bool(False)
)    
process.p = cms.Path(process.kf160*process.higgsToWW2LeptonsPreselectionSequence*process.jetvertexalpha*process.eleIsoFromDepsEcalFromHits*process.myanalysis)
