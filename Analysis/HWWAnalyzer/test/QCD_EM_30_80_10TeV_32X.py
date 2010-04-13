import FWCore.ParameterSet.Config as cms

process = cms.Process("H2WW2emu")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")

process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")

process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
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

    CheckMCTruth = cms.string(''),
    StoreTracks = cms.bool(False),
    HistOutFile = cms.untracked.string('outQCD_EM_30_80_10TeV_32X.root'),
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
    hep_mc = cms.InputTag("generator"),
    towers = cms.InputTag("towerMaker"),
    met = cms.InputTag("corMetGlobalMuons"),
    genmet = cms.InputTag("genMetTrue"),
    PFmet = cms.InputTag("pfMet"),
    tracks = cms.InputTag("generalTracks"),
    bjets = cms.InputTag("trackCountingHighPurBJetTags"),
    jets = cms.InputTag("iterativeCone5CaloJets"),
    PFjetsIC5 = cms.InputTag("iterativeCone5PFJets"),
    PFjetsSC5 = cms.InputTag("sisCone5PFJets"),
    gsfelectrons = cms.InputTag("gsfElectrons"),
    preselectedmuons = cms.InputTag("muons"),
    channels = cms.vstring('all'),
    requested_hlt_bits = cms.vstring('HLT_IsoEle15_L1I','HLT_IsoEle18_L1R','HLT_IsoEle15_LW_L1I','HLT_LooseIsoEle15_LW_L1R','HLT_Ele10_SW_L1R','HLT_Ele15_SW_L1R','HLT_Ele15_LW_L1R','HLT_IsoMu9', 'HLT_IsoMu11','HLT_IsoMu13', 'HLT_IsoMu15','HLT_Mu3','HLT_Mu5','HLT_Mu7','HLT_Mu9','HLT_Mu11','HLT_Mu13', 'HLT_Ele10_LW_EleId_L1R', 'HLT_Mu15' ,),
    PrintHLTNames = cms.bool(False),                                 
    TrackIsolationLabel = cms.string("eleIsoDepositTk"),
    EcalJurassicIsolationLabel = cms.string("eleIsoFromDepsEcalFromHits"),
    WhichElectronID = cms.string("eidTight"),
    KFactorLabel = cms.string("kf160"),    
    Process_ID = cms.string(''),
    
    
    
    do_pdf_analysis = cms.bool(False),
    first_incoming_particle = cms.int32(5),
    second_incoming_particle = cms.int32(6),
    first_outgoing_particle = cms.int32(7),
    second_outgoing_particle = cms.int32(8),
    PDFSetNameForReference1 = cms.string("cteq6m.LHpdf"),
    PDFSetNameForErrors1 = cms.string("cteq6.LHpdf"),
    PDFSetNameForReference2 = cms.string("cteq6m.LHpdf"),
    PDFSetNameForErrors2 = cms.string("cteq6.LHpdf"),
    PDFSetNameForReference_and_Errors1 = cms.string("cteq61.LHgrid"),
    PDFSetNameForReference_and_Errors2 = cms.string("cteq6mE.LHgrid"),
    PDFSetNameForReference_and_Errors3 = cms.string("cteq65.LHgrid"),
    PDFSetNameForReference_and_Errors4 = cms.string("cteq66.LHgrid"),
    NumberOfEventsToPrint = cms.int32(10),
   

)

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

process.p = cms.Path(process.jetvertexalpha*process.eleIsoDepositEcalFromHits*process.eleIsoFromDepsEcalFromHits*process.eleIsoDepositTk*process.myanalysis)
