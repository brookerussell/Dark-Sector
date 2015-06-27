import sys
from ROOT import *

def main() :
       
    #Energy in Pi0 Decay Histogram
    print 'Here1'
    fin     = TFile.Open("MCC5Analyzed_BNB_Cosmics_v03_143_APS_Cuts_Dist_03cm_N.root","READ")

    Pi0DistanceHist = fin.Get("BdistPi0Photons")
        
    OtherDistanceHist = fin.Get("BdistOtherPhotons")

    Pi0DistanceHist.Scale(1/(Pi0DistanceHist.Integral()))
    OtherDistanceHist.Scale(1/(OtherDistanceHist.Integral()))

#    Pi0DistanceHist.Scale(1*17.9)
#    OtherDistanceHist.Scale(1*17.9)
    
    Pi0DistanceHist.SetLineColor(kBlue)
    OtherDistanceHist.SetTitle("Normalized Photon Distance Distribution in #pi^{0} Decay")
    
    OtherDistanceHist.SetLineColor(kBlack)

    print 'Here2'
    sys.stdin.readline()
    Canvas = TCanvas("PhotonDistance","Photon Distance")
    Canvas.cd()

    OtherDistanceHist.GetXaxis().SetTitle("Distance (cm)")
    
    print 'Here3'
    sys.stdin.readline()
    gStyle.SetOptStat(0)
    OtherDistanceHist.Draw()
    Canvas.Update();

    print 'Here4'
    sys.stdin.readline()
    gStyle.SetOptStat(0)
    Pi0DistanceHist.Draw("sames")
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
#    Canvas.SetLogy(1);


    print 'Here6'
    sys.stdin.readline()
    Canvas.Update();
    print 'Here7'
    sys.stdin.readline()    
    Canvas.Print("APS_Pi0Distance_Area4.gif")

    fin.Close()
    

print __name__
if __name__ == "__main__":
    main()
