#Loop over histograms created in LArSoft. 
#NOTE: this assumes that the histograms are in the current folder.

import sys
from ROOT import *

print "_________________________________________________"
Toy_tree_ch=TChain("myana/Toy_tree","")
POT_tree_ch=TChain("myana/Toy_POT_tree","")

for i in range(0,143):
    Toy_tree_ch.AddFile("MCC5_v03_BNB_Cosmics_Hist__%s.root" %i)
    POT_tree_ch.AddFile("MCC5_v03_BNB_Cosmics_Hist__%s.root" %i)
    print "===========================File number %s opened========================" %i

#Toy_tree_ch.AddFile("TEMPORARY_MCC5.root")
#POT_tree_ch.AddFile("TEMPORARY_MCC5.root")

my_ana = DarkPhotonAnaC()

my_ana.RunEventLoop(Toy_tree_ch);

Total_POT=my_ana.RunPOTLoop(POT_tree_ch);

print Total_POT
