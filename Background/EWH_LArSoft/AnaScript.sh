#!/bin/bash

echo "Script to loop over lots of different prodgenie files"

for (( i=0; i<=199; i++ ))
do
    #echo "Copying file number $i"
    #cp /uboone/data/uboonepro/reco2D/v1_00_04_ub01/prodgenie_bnb_nu_3window_uboone/15368701_${i}/prodgenie_bnb_nu_3window_uboone_15318999_${i}_gen_15335565_${i}_g4_15342655_${i}_detsim_tpc_15368701_${i}_reco2D.root .

    #The following changes the filename in the fcl file for dark photon ana module
    echo "services.TFileService.fileName: \"MCC5_v03_BNB_Hist__$i.root\"" >> /uboone/app/users/ehimwich/v03_04_00/srcs/larexamples/DarkPhotonAna/darkphoton.fcl
    echo "Running larsoft job to create Histogram number $i"
    #lar -c darkphoton.fcl prodgenie_bnb_nu_3window_uboone_15318999_${i}_gen_15335565_${i}_g4_15342655_${i}_detsim_tpc_15368701_${i}_reco2D.root

    ##COMMAND FOR RUNNING WITH BNB AND COSMICS
    #lar -c darkphoton.fcl prodgenie_bnb_nu_cosmic_uboone_53048_${i}_gen_53056_${i}_g4.root
    ##COMMAND FOR RUNNING WITH BNB
    lar -c /uboone/app/users/ehimwich/v03_04_00/srcs/larexamples/DarkPhotonAna/darkphoton.fcl prodgenie_bnb_nu_uboone_53047_${i}_gen_53053_${i}_g4.root
    ##COMMAND FOR RUNNING WITH COSMICS
    #lar -c darkphoton.fcl prodcosmics_uboone_75703_${i}_gen_75704_${i}_g4.root



    #lar -c darkphoton.fcl /uboone/data/users/ehimwich/prodgenie_bnb_nu_3window_uboone_15318999_${i}_gen_15335565_${i}_g4_15342655_${i}_detsim_tpc_15368701_${i}_reco2D.root

    echo "DONE WITH LARSOFT JOB!!!"

done
