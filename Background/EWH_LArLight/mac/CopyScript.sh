#!/bin/bash                                                                                                                                                                          

echo "Script to secure copy histograms from uboonegpvm05"

for (( i=101; i<=143; i++ ))
do
    echo "Copying file number $i"
    scp ehimwich@uboonegpvm02.fnal.gov:/uboone/data/users/ehimwich/MCC5_v03_BNB_Cosmics_Hist__${i}.root .
    #scp ehimwich@uboonegpvm02.fnal.gov:/uboone/app/users/ehimwich/MCTruthStudy4/srcs/larexamples/DarkPhotonAna/MCC5_BNB_Hist__${i}.root .
    #scp ehimwich@uboonegpvm05.fnal.gov:/uboone/app/users/ehimwich/MCTruthStudy4/srcs/larexamples/DarkPhotonAna/DarkPhotonCosmicHist__${i}.root .
    
done

