import sys
from ROOT import *

def main() :
       
    #Energy in Pi0 Decay Histogram
    print 'Here1'
    fin     = TFile.Open("MCC5Analyzed_BNB_Cosmics_v03_143_Dalitz3_APS_PrimaryTest.root","READ")

    Pi0EnergyHist = fin.Get("BenergyPi0Photons")
        
    OtherEnergyHist = fin.Get("BenergyOtherPhotons")

    Pi0EnergyHist.Scale(1*17.9)
    OtherEnergyHist.Scale(1*17.9)
    
    Pi0EnergyHist.SetLineColor(kBlue)
    OtherEnergyHist.SetTitle("Photon Energy Distribution in #pi^{0} Decay")
    
    OtherEnergyHist.SetLineColor(kBlack)

    print 'Here2'
    sys.stdin.readline()
    Canvas = TCanvas("PhotonEnergy","Photon Energy")
    Canvas.cd()

    OtherEnergyHist.GetXaxis().SetTitle("Energy (MeV)")
    
    print 'Here3'
    sys.stdin.readline()
    gStyle.SetOptStat(0)
    OtherEnergyHist.Draw()
    Canvas.Update();

    print 'Here4'
    sys.stdin.readline()
    gStyle.SetOptStat(0)
    Pi0EnergyHist.Draw("sames")
    Canvas.Update();

#    Line = TLine(20,0,20,100000)
#    Line.SetLineColor(kRed)

#    Line.Draw("sames")


#    N_EnergyHist = fin.Get("Nenergy")
#    N_EnergyHist.SetLineColor(kBlack)
#    N_EnergyHist.SetTitle("Photon Energy Distribution in Nuclear Scattering")
#    N_EnergyHist.GetXaxis().SetTitle("Energy (MeV)")
#    gStyle.SetOptStat(0)
#
#    Canvas = TCanvas("PhotonEnergy","Photon Energy")
#    Canvas.cd() 
#
#    N_EnergyHist.Draw()
##
#    GroupHist = fin.Get("fphotongroup")
#    GroupHist.SetLineColor(kBlack)
#    GroupHist.SetTitle("Number of Photons in 1 cm Vertex Groups")
#    GroupHist.GetXaxis().SetTitle("Photons per Group")
#    gStyle.SetOptStat(0)
#
#    Canvas = TCanvas("PhotonEnergy","Photon Energy")
#    Canvas.cd() 
#
#    GroupHist.Draw()
#

    print 'Here5'
    sys.stdin.readline()
    Canvas.SetLogy(1);
    
    print 'Here6'
    sys.stdin.readline()
    Canvas.Update();

    # Here any changes that need to be made to the canvas by hand can \n
    # be added

    print 'Here7'
    sys.stdin.readline()    
    Canvas.Print("APS_Pi0Energy_Scaled.gif")

    fin.Close()
    

print __name__
if __name__ == "__main__":
    main()
