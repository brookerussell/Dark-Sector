#ifndef DECAY_CXX
#define DECAY_CXX

#include "Decay.h"

void Decay::Detector()
{
  TFile* y = new TFile("Stoneham.root");
  TTree *k = (TTree*)y->Get("k");
  int nVbosons;
  double VB_Px,VB_Py,VB_Pz,VB_E,VB_mass,photon_Px,photon_Py,photon_Pz,photon_E,omass;
  k->SetBranchAddress("nVbosons",&nVbosons);
  k->SetBranchAddress("VB_Px",&VB_Px);
  k->SetBranchAddress("VB_Py",&VB_Py);
  k->SetBranchAddress("VB_Pz",&VB_Pz);
  k->SetBranchAddress("VB_E",&VB_E);
  k->SetBranchAddress("VB_mass",&VB_mass);
  k->SetBranchAddress("photon_Px",&photon_Px);
  k->SetBranchAddress("photon_Py",&photon_Py);
  k->SetBranchAddress("photon_Pz",&photon_Pz);
  k->SetBranchAddress("photon_E",&photon_E);
  k->SetBranchAddress("omass",&omass);

  TFile* fout = TFile::Open("Melrose.root","RECREATE");
  TTree d("d","");
  int vb,detector;
  float dx,dy,dz,de,pw,prob,gb,exprob,mx,my,mz,me,ph1x,ph1y,ph1z,ph1e,ph2x,ph2y,ph2z,ph2e,minv,p1inv,p2inv;
  d.Branch("vb",&vb,"vb/I"); // # of vector bosons that intersect detectors
  d.Branch("dx",&dx,"dx/F"); // vector boson momentum component
  d.Branch("dy",&dy,"dy/F");
  d.Branch("dz",&dz,"dz/F");
  d.Branch("de",&de,"de/F"); // vector boson energy
  d.Branch("pw",&pw,"pw/F"); // partial width
  d.Branch("prob",&prob,"prob/F"); // probability
  d.Branch("detector",&detector,"detector/I"); 
  d.Branch("gb",&gb,"gb/F"); // coupling
  d.Branch("exprob",&exprob,"exprob/F"); // extrapolated probability
  d.Branch("mx",&mx,"mx/F"); // pi0 momentum component
  d.Branch("my",&my,"my/F");
  d.Branch("mz",&mz,"mz/F");
  d.Branch("me",&me,"me/F"); // pi0 energy
  d.Branch("minv",&minv,"minv/F");
  d.Branch("ph1x",&ph1x,"ph1x/F"); // photon1 momentum component
  d.Branch("ph1y",&ph1y,"ph1y/F");
  d.Branch("ph1z",&ph1z,"ph1z/F");
  d.Branch("ph1e",&ph1e,"ph1e/F"); // photon1 energy
  d.Branch("p1inv",&p1inv,"p1inv/F"); // photon1 invariant mass
  d.Branch("ph2x",&ph2x,"ph2x/F"); // photon2 momentum component
  d.Branch("ph2y",&ph2y,"ph2y/F");
  d.Branch("ph2z",&ph2z,"ph2z/F");
  d.Branch("ph2e",&ph2e,"ph2e/F"); // photon2 energy
  d.Branch("p2inv",&p2inv,"p2inv/F"); // photon2 invariant mass
  
  TH1F *g = new TH1F("g","#alpha_{B} (baryonic gauge coupling constant)",9,log10(0.000000001),log10(0.1));
  TH1F *proj = new TH1F("proj","Probability Scaled to POT",1000,0,1);
  TH1F *sb = new TH1F("sb","",1000,0,1);
  TH1F *mi = new TH1F("mi","",1000,0,1);
  TH1F *ic = new TH1F("ic","",1000,0,1);
  TH2F *ssb = new TH2F("ssb","Reach at SBND",48,.140,.620,9,log10(0.000000001),log10(0.1));
  TH2F *smi = new TH2F("smi","Reach at MicroBooNE",48,.140,.620,9,log10(0.000000001),log10(0.1));
  TH2F *sic = new TH2F("sic","Reach at Icarus",48,.140,.620,9,log10(0.000000001),log10(0.1));
  TH1F *medrf = new TH1F("medrf","Mediator Invariant Mass (rest frame)",1100,0,1.1);
  TH1F *medlf = new TH1F("medlf","Mediator Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *pirf = new TH1F("pirf","#pi^{0} Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *ph1rf = new TH1F("ph1rf","#gamma1 Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *ph2rf = new TH1F("ph2rf","#gamma2 Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *xpilf = new TH1F("xpilf","P_{x} (#pi^{0} lab frame)",400,-2,2);
  TH1F *ypilf = new TH1F("ypilf","P_{y} (#pi^{0} lab frame)",400,-2,2);
  TH1F *zpilf = new TH1F("zpilf","P_{z} (#pi^{0} lab frame)",400,-2,2);
  TH1F *epilf = new TH1F("epilf","#pi^0 Energy (lab frame)",1600,-8,8);
  TH1F *xph1lf = new TH1F("xph1lf","P_{x} (#gamma No. 1 lab frame)",400,-2,2);
  TH1F *yph1lf = new TH1F("yph1lf","P_{y} (#gamma No. 1 lab frame)",400,-2,2);
  TH1F *zph1lf = new TH1F("zph1lf","P_{z} (#gamma No. 1 lab frame)",400,-2,2);
  TH1F *eph1lf = new TH1F("eph1lf","#gamma No. 1 energy (lab frame)",1600,-8,8);
  TH1F *xph2lf = new TH1F("xph2lf","P_{x} (#gamma No. 2 lab frame)",400,-2,2);
  TH1F *yph2lf = new TH1F("yph2lf","P_{y} (#gamma No. 2 lab frame)",400,-2,2);
  TH1F *zph2lf = new TH1F("zph2lf","P_{z} (#gamma No. 2 lab frame)",400,-2,2);
  TH1F *eph2lf = new TH1F("eph2lf","#gamma No. 2 energy (lab frame)",1600,-8,8);
  int ctr = 0;
  Int_t dentries = (Int_t)k->GetEntries();
  for(Int_t i=0; i<dentries; i++)
  //for(int i=0; i < 800; i++)
  {
      k->GetEntry(i);

      if(VB_Px<0) {VB_Px = VB_Px*-1;}
      if(VB_Py<0) {VB_Py = VB_Py*-1;}
      if(VB_Pz<0) {VB_Pz = VB_Pz*-1;}

      float frontend [3] = {110.0,470.0,600.0}; 
      float backend [3] = {113.6,480.0,619.6};
      float xdist [3] = {2.0,1.25,3.6} ;
      float ydist [3] = {2.0,1.25,3.9};
      float c = 299792458; // speed of light
      float alpha_EM = 7.29735257*pow(10.0,-3.0); // fine structure constant
      float pi = 3.141592653589;
      float f_pion = 0.093;
      float mass_pion = 0.139570;
      for(float k=0.000000001; k<1; k*=10)
	{
	  for(int j=0; j<3; j++)
	    {
	      if(VB_Px/VB_Pz < xdist[j]/frontend[j])
		{
		  if(VB_Py/VB_Pz < ydist[j]/frontend[j])
		    {
		      float Partial_width = k*alpha_EM*pow(VB_mass,3.0)
			*pow(96.0,-1.0)*pow(pi,-3.0)*pow(f_pion,-2.0)
			*pow(1-(pow(mass_pion,2.0)*pow(VB_mass,-2.0)),3.0);
		      float Tau = pow(Partial_width,-1.0);
		      TLorentzVector Ephemeral;
		      Ephemeral.SetPxPyPzE(VB_Px,VB_Py,VB_Pz,VB_E);
		      float boost_mag = Ephemeral.Beta();
		      float lbar = boost_mag*c*Tau;
		      float P_decay = exp(-frontend[j]*pow(lbar,-1.0))
			-exp(-backend[j]*pow(lbar,-1.0));
		      dx = VB_Px;
		      dy = VB_Py;
		      dz = VB_Pz;
		      de = VB_E;
		      pw = Partial_width;
		      prob = P_decay;
		      exprob = P_decay*66000000000000;
		      detector = j;
		      gb = log10(k);
		      g->Fill(log10(k));
		      proj->Fill(exprob);
		      if(j == 0) {sb->Fill(exprob);ssb->Fill(VB_mass,log10(k),exprob);}
		      if(j == 1) {mi->Fill(exprob);smi->Fill(VB_mass,log10(k),exprob);}
		      if(j == 2) {ic->Fill(exprob);sic->Fill(VB_mass,log10(k),exprob);}
		      
		      // boost mediator to its rest frame
		      TLorentzVector Temp;
		      Temp.SetPxPyPzE(VB_Px,VB_Py,VB_Pz,VB_E);
		      float mlf = Temp.Mag();
		      medlf->Fill(std::abs(mlf));
		      Temp.Boost(-Temp.Px()/Temp.E(),
				      -Temp.Py()/Temp.E(),
				      -Temp.Pz()/Temp.E());
		      float mrf = Temp.Mag();
		      medrf->Fill(std::abs(mrf));
		      TGenPhaseSpace event_d;
		      double masses_d[3] = {0.139,0.0,0.0};
		      event_d.SetDecay(Temp,3,masses_d);
		      event_d.Generate();
		      TLorentzVector *pizero = event_d.GetDecay(0);
		      TLorentzVector *photon1 = event_d.GetDecay(1);
		      TLorentzVector *photon2 = event_d.GetDecay(2);
		      TLorentzVector PiZero = *pizero;
		      TLorentzVector Photon1 = *photon1;
		      TLorentzVector Photon2 = *photon2;
		      float piinv = PiZero.Mag();
		      pirf->Fill(piinv);
		      minv = piinv;
		      float ph1inv = Photon1.Mag();
		      ph1rf->Fill(ph1inv);
		      p1inv = ph1inv;
		      float ph2inv = Photon2.Mag();
		      ph2rf->Fill(ph2inv);
		      p2inv = ph2inv;
		      mx = PiZero.Px();
		      xpilf->Fill(mx);
		      my = PiZero.Py();
		      ypilf->Fill(my);
		      mz = PiZero.Pz();
		      zpilf->Fill(mz);
		      me = PiZero.E();
		      epilf->Fill(me);
		      ph1x = Photon1.Px();
		      xph1lf->Fill(ph1x);
		      ph1y = Photon1.Py();
		      yph1lf->Fill(ph1y);
		      ph1z = Photon1.Pz();
		      zph1lf->Fill(ph1z);
		      ph1e = Photon1.E();
		      eph1lf->Fill(ph1e);
		      ph2x = Photon2.Px();
		      xph2lf->Fill(ph2x);
		      ph2y = Photon2.Py();
		      yph2lf->Fill(ph2y);
		      ph2z = Photon2.Pz();
		      zph2lf->Fill(ph2z);
		      ph2e = Photon2.E();
		      eph2lf->Fill(ph2e);
		      ctr++;
		      Ephemeral.Clear();
		      Temp.Clear();
		      PiZero.Clear();
		      Photon1.Clear();
		      Photon2.Clear();
		    } // <-- end VB_Py if
		} // <-- end VB_Px if
	    } // <-- end j loop/end frontend loop	  
	} // <-- end k loop
      if(ctr>0)
	{
	  vb = ctr;
	  d.Fill();
	}
  }
  y->Close();
  fout->Write();  
} // <-- end void
#endif
