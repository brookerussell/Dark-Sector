import sys


from ROOT import gSystem
gSystem.Load("libDarkSector_SignalMC")
from ROOT import test
from ROOT import TFile, TTree, TBranch
from ROOT import gDirectory

try:

    print "PyROOT recognized your class %s" % str(test)

except NameError:

    print "Failed importing SignalMC..."

# open the file    
#myfile = TFile( 'TestOutput.root ' )
fin = TFile.Open("ChgdPionPlotter.root","READ")

# retrieve the ntuple of interest
mytuple = fin.Get("t1")
#incorporate the next line to follow
#mytuple.MesonMaker()

#entries = mytuple.GetEntriesFast()

#mytuple.Ship("trial.root")

#momX = float(mytuple.px)
#print momX

#for a in range (0, entries):
#    print momX


#tr = f.Get("t")

#for event in tr:
#    print tr.px

sys.exit(0)

