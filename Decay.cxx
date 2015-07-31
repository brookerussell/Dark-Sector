#ifndef DECAY_CXX
#define DECAY_CXX

#include "Decay.h"

void Decay::Detector()
{
  TFile* y = new TFile("Stoneham.root");
  TTree *k = (TTree*)y->Get("k");
  int vbosons;
  double vx,vy,vz,ve,vmass,px,py,pz,pe,omass;
  k->SetBranchAddress("vbosons",&vbosons);
  k->SetBranchAddress("vx",&vx);
  k->SetBranchAddress("vy",&vy);
  k->SetBranchAddress("vz",&vz);
  k->SetBranchAddress("ve",&ve);
  k->SetBranchAddress("vmass",&vmass);
  k->SetBranchAddress("px",&px);
  k->SetBranchAddress("py",&py);
  k->SetBranchAddress("pz",&pz);
  k->SetBranchAddress("pe",&pe);
  k->SetBranchAddress("omass",&omass);

  TFile* fout = TFile::Open("Melrose.root","RECREATE");
  TTree d("d","");
  int vb,detector;
  float dx,dy,dz,de,pw,prob,gb,exprob,mx,my,mz,me,ph1x,ph1y,ph1z,ph1e,ph2x,ph2y,ph2z,ph2e,minv,p1inv,p2inv;
  d.Branch("vb",&vb,"vb/I"); // number of vector bosons
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
  
  TH1F *g = new TH1F("g","#alpha_{B} (baryonic gauge coupling constant)",8,log10(0.000000001),log10(0.1));
  TH1F *proj = new TH1F("proj","Probability Scaled to POT",1000,0,1);
  TH1F *sb = new TH1F("sb","",1000,0,1);
  TH1F *mi = new TH1F("mi","",1000,0,1);
  TH1F *ic = new TH1F("ic","",1000,0,1);
  TH2F *ssb = new TH2F("ssb","Reach at SBND",48,.140,.620,8,log10(0.00000001),log10(0.1));
  TH2F *smi = new TH2F("smi","Reach at MicroBooNE",48,.140,.620,8,log10(0.00000001),log10(0.1));
  TH2F *sic = new TH2F("sic","Reach at Icarus",48,.140,.620,8,log10(0.00000001),log10(0.1));
  TH1F *medrf = new TH1F("medrf","Mediator Invariant Mass (rest frame)",1100,0,1.1);
  TH1F *medlf = new TH1F("medlf","Mediator Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *pirf = new TH1F("pirf","#pi^{0} Invariant Mass (rest frame)",1100,0,1.1);
  TH1F *ph1rf = new TH1F("ph1rf","#gamma1 Invariant Mass (rest frame)",1100,0,1.1);
  TH1F *ph2rf = new TH1F("ph2rf","#gamma2 Invariant Mass (rest frame)",1100,0,1.1);
  TH1F *pilf = new TH1F("pilf","#pi^{0} Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *ph1lf = new TH1F("ph1lf","#gamma1 Invariant Mass (lab frame)",1100,0,1.1);
  TH1F *ph2lf = new TH1F("ph2lf","#gamma2 Invariant Mass (lab frame)",1100,0,1.1);
  int ctr = 0;
  Int_t dentries = (Int_t)k->GetEntries();
  //for(Int_t i=0; i<dentries; i++)
  for(int i=0; i < 800; i++)
  {
      k->GetEntry(i);

      if(vx<0) {vx = vx*-1;}
      if(vy<0) {vy = vy*-1;}
      if(vz<0) {vz = vz*-1;}

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
	      if(vx/vz < xdist[j]/frontend[j])
		{
		  if(vy/vz < ydist[j]/frontend[j])
		    {
		      float Partial_width = k*alpha_EM*pow(vmass,3.0)
			*pow(96.0,-1.0)*pow(pi,-3.0)*pow(f_pion,-2.0)
			*pow(1-(pow(mass_pion,2.0)*pow(vmass,-2.0)),3.0);
		      float Tau = pow(Partial_width,-1.0);
		      TLorentzVector Ephemeral;
		      Ephemeral.SetPxPyPzE(vx,vy,vz,ve);
		      float boost_mag = Ephemeral.Beta();
		      float lbar = boost_mag*c*Tau;
		      float P_decay = exp(-frontend[j]*pow(lbar,-1.0))
			-exp(-backend[j]*pow(lbar,-1.0));
		      dx = vx;
		      dy = vy;
		      dz = vz;
		      de = ve;
		      pw = Partial_width;
		      prob = P_decay;
		      exprob = P_decay*66000000000000;
		      detector = j;
		      gb = k;
		      g->Fill(k);
		      proj->Fill(exprob);
		      if(j == 0) {sb->Fill(exprob);ssb->Fill(vmass,k,exprob);}
		      if(j == 1) {mi->Fill(exprob);smi->Fill(vmass,k,exprob);}
		      if(j == 2) {ic->Fill(exprob);sic->Fill(vmass,k,exprob);}
		      float mlf = Ephemeral.Mag();
		      medlf->Fill(mlf);
		      
		      // boost mediator to its rest frame
		      Ephemeral.Boost(-Ephemeral.Px()/Ephemeral.E(),
				      -Ephemeral.Py()/Ephemeral.E(),
				      -Ephemeral.Pz()/Ephemeral.E());
		      float mrf = Ephemeral.Mag();
		      medrf->Fill(mrf);
		      TGenPhaseSpace event_d;
		      double masses_d[3] = {0.139,0.0,0.0};
		      event_d.SetDecay(Ephemeral,3,masses_d);
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
		      PiZero.Boost(PiZero.BoostVector());
		      Photon1.Boost(Photon1.BoostVector());
		      Photon2.Boost(Photon2.BoostVector());
		      TLorentzVector PiZero_lf;
		      PiZero_lf.SetPxPyPzE(PiZero[0],
					   PiZero[1],
					   PiZero[2],
					   PiZero[3]);
		      TLorentzVector Photon1_lf;
		      Photon1_lf.SetPxPyPzE(Photon1[0],
					    Photon1[1],
					    Photon1[2],
					    Photon1[3]);
		      TLorentzVector Photon2_lf;
		      Photon2_lf.SetPxPyPzE(Photon2[0],
					    Photon2[1],
					    Photon2[2],
					    Photon2[3]);
		      float piinvlf = PiZero_lf.Mag();
		      pilf->Fill(piinvlf);
		      float ph1invlf = Photon1_lf.Mag();
		      ph1lf->Fill(ph1invlf);
		      float ph2invlf = Photon2_lf.Mag();
		      ph2lf->Fill(ph2invlf);
		      mx = PiZero_lf.Px();
		      my = PiZero_lf.Py();
		      mz = PiZero_lf.Pz();
		      me = PiZero_lf.E();
		      ph1x = Photon1_lf.Px();
		      ph1y = Photon1_lf.Py();
		      ph1z = Photon1_lf.Pz();
		      ph1e = Photon1_lf.E();
		      ph2x = Photon2_lf.Px();
		      ph2y = Photon2_lf.Py();
		      ph2z = Photon2_lf.Pz();
		      ph2e = Photon2_lf.E();
		      d.Fill();
		      ctr++;
		    } // <-- end vy if
		} // <-- end vx if
	    } // <-- end j loop/end frontend loop	  
	} // <-- end k loop
    }
  y->Close();
  fout->Write();  
} // <-- end void
#endif
