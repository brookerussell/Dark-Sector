import sys
from ROOT import *


# MAKE MESONS
a = TChain("np","")
a.AddFile("Pizero_input.root")

b = NeutralMesonProduction()
b.NMP()

c = TChain("nmp","")
c.AddFile("NeutralMesonProduction_output.root")

#z = SanityPlots()
#z.CheckNMP()

# -------------------------------------------------

# MAKE MEDIATOR
d = MediatorProduction()
d.MP()

e = TChain("mp","")
e.AddFile("MediatorProduction_output.root")

#z.CheckMP()

# -------------------------------------------------

# SELECT ONE MEDIATOR FROM PI0 
f = MediatorSelection()
f.MS()

g = TChain("ms","")
g.AddFile("MediatorSelection_outoput.root")

#z.CheckMS()
# --------------------------------------------------

# ONLY KEEP MEDIATOR WHICH TRAVERSE DETECTOR
h = MediatorDetectorIntercept()
h.MDI()

#i = TChain("mdi","")
#i.AddFile("MediatorDetectorIntercept_output.root")

#z.CheckMDI()
# -------------------------------------------------- 

# DECAY THE MEDIATOR TO SM PRODUCTS
#j = MediatorDecay()
#j.MD()

#h = TChain("md","")
#h.AddFile("MediatorDecay_output.root")

#z = SanityPlots()
#z.CheckMD()

sys.exit(0)
