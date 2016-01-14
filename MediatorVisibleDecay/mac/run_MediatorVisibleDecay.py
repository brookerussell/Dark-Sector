import sys
from ROOT import *

a = TChain("np","")
a.AddFile("PiNtuple.root")

b = NeutralMesonProduction()
b.NMP()

c = TChain("nmp","")
c.AddFile("NeutralMesonProduction_output.root")

d = MediatorProduction()
d.MP()

e = TChain("mp","")
e.AddFile("MediatorProduction_output.root")

f = MediatorSelection()
f.MS()

g = TChain("ms","")
g.AddFile("MediatorSelection_outoput.root")

h = MediatorDetectorIntercept()
h.MDI()

i = TChain("mdi","")
i.AddFile("MediatorDetectorIntercept_output.root")

j = MediatorDecay()
j.MD()

h = TChain("md","")
h.AddFile("MediatorDecay_output.root")

z = SanityPlots()
z.Check()

sys.exit(0)
