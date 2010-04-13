echo "If you want to run crab also, please execute this script as ./CreateCMSSWCfgs.sh RunCrab"
for file in TT;do # WW WJ WZ ZZ4l ZZ2l2n STs STt STtW H130 H150 H160 H170 H200 H500;do 
echo "====================================="
    [ $file == 'TT' ] && dataset=/TTJets-madgraph/Fall08_IDEAL_V11_redigi_v10/GEN-SIM-RECO
    [ $file == 'ZJ' ] && dataset=/ZJets-madgraph/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
    [ $file == 'WW' ] && dataset=/WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
    [ $file == 'WJ' ] && dataset=/WJets-madgraph/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
    [ $file == 'WZ' ] && dataset=/WZ_incl/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
    [ $file == 'ZZ4l' ] && dataset=/ZZ_4l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
    [ $file == 'ZZ2l2n' ] && dataset=/ZZ_2l2n/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
    [ $file == 'STs' ] && dataset=/SingleTop_sChannel/Summer08_IDEAL_V11_redigi_v3/GEN-SIM-RECO
    [ $file == 'STt' ] && dataset=/SingleTop_tChannel/Summer08_IDEAL_V11_redigi_v3/GEN-SIM-RECO
    [ $file == 'STtW' ] && dataset=/SingleTop_tWChannel/Summer08_IDEAL_V11_redigi_v3/GEN-SIM-RECO

    TemplateFile='TemplateCMSSW.py'

    if [ $file == 'H130' ];then 
	dataset=/H130_WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
	TemplateFile='TemplateCMSSWHiggs.py'
	mass=130
    fi
    if [ $file == 'H150' ];then 
	dataset=/H150_WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
	TemplateFile='TemplateCMSSWHiggs.py'
	mass=150
    fi
    if [ $file == 'H160' ];then 
	dataset=/H160_WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
	TemplateFile='TemplateCMSSWHiggs.py'
	mass=160
    fi
    if [ $file == 'H170' ];then 
	dataset=/H170_WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
	TemplateFile='TemplateCMSSWHiggs.py'
	mass=170
    fi
    if [ $file == 'H200' ];then 
	dataset=/H200_WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
	TemplateFile='TemplateCMSSWHiggs.py'
	mass=200
    fi
    if [ $file == 'H500' ];then 
	dataset=/H500_WW_2l/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
	TemplateFile='TemplateCMSSWHiggs.py'
	mass=500
    fi
    


    cat $TemplateFile | sed -e "s@H160WW@$file@g" \
	-e "s@160@$mass@g" > ${file}22X.py 

    if [ $file == 'STs' ]; then
	cat $TemplateFile | sed -e "s@H160WW@$file@g" \
                                -e "s@OnReco@@g" > ${file}22X.py
    fi
    if [ $file == 'STt' ]; then
	cat $TemplateFile | sed -e "s@H160WW@$file@g" \
                                -e "s@OnReco@@g" > ${file}22X.py
    fi
    if [ $file == 'STtW' ]; then
	cat $TemplateFile | sed -e "s@H160WW@$file@g" \
                                -e "s@OnReco@@g" > ${file}22X.py
    fi

    cat TemplateCrab.cfg | sed -e "s@H160@$file@g" \
	-e "s@datasetpath=@datasetpath=$dataset@g" > crab${file}22X.cfg

    [ $file == 'WZ' ] && echo "CE_white_list=.wisc.edu" >> crab${file}22X.cfg 
    [ $file == 'TT' ] && echo "CE_white_list=.wisc.edu" >> crab${file}22X.cfg 
    [ $file == 'ZJ' ] && echo "CE_white_list=.wisc.edu" >> crab${file}22X.cfg 
    [ $file == 'WW' ] && echo "CE_white_list=.ucsd.edu" >> crab${file}22X.cfg 
    [ $file == 'WJ' ] && echo "CE_white_list=.ucsd.edu" >> crab${file}22X.cfg 
    [ $file == 'ZZ4l' ] && echo "CE_white_list=.wisc.edu" >> crab${file}22X.cfg 
    [ $file == 'ZZ2l2n' ] && echo "CE_white_list=.ucsd.edu" >> crab${file}22X.cfg 
    [ $file == 'STs' ] && echo "CE_white_list=.mit.edu" >> crab${file}22X.cfg 
    [ $file == 'STt' ] && echo "CE_white_list=.ifca.es" >> crab${file}22X.cfg 
    [ $file == 'STtW' ] && echo "CE_white_list=.ifca.es" >> crab${file}22X.cfg 
    [ $file == 'H130' ] && echo "CE_white_list=.infn.it" >> crab${file}22X.cfg 
    [ $file == 'H150' ] && echo "CE_white_list=.infn.it" >> crab${file}22X.cfg 
    [ $file == 'H160' ] && echo "CE_white_list=.infn.it" >> crab${file}22X.cfg 
    [ $file == 'H170' ] && echo "CE_white_list=.infn.it" >> crab${file}22X.cfg 
    [ $file == 'H200' ] && echo "CE_white_list=.infn.it" >> crab${file}22X.cfg 
    [ $file == 'H500' ] && echo "CE_white_list=.ifca.es" >> crab${file}22X.cfg 

    if [ $1 ];then 
	if [ $1 == 'RunCrab' ];then
	    echo Will also run crab using crab${file}22X.cfg
	    crab -create -cfg crab${file}22X.cfg 
	    crab -submit -c ~/${file}22X
	fi
    fi
done
