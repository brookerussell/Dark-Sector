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
#sys.exit(0)
