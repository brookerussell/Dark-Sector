import sys
from ROOT import *

#a=TChain("np","")
#a.AddFile("PiNtuple.root")

#b=Meson()
#b.SetParams()

c=TChain("l","")
c.AddFile("Woburn.root");

d=VB()
d.PseudoscalarMeson()

#e=TChain("k","")
#e.AddFile("Stoneham.root")

#f=Decay()
#f.Detector()

#g=TChain("np","")
#g.AddFile("PiNtuple.root")

#h=LeptophobicMC()
#h.Run()

#sys.exit(0)
