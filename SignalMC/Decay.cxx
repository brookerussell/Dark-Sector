#ifndef DECAY_CXX
#define DECAY_CXX

#include "Decay.h"

void Decay::Detector()
{
  TFile* y = new TFile("Stoneham.root");
  TTree *k = (TTree*)y->Get("k");
  int vbosons;
  float vx,vy,vz,ve,vmass,px,py,pz,pe;
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

  TFile* fout = TFile::Open("Melrose.root","RECREATE");
  TTree d("d","");
  int vb,detector;
  float dx,dy,dz,de,pw,prob,gb,exprob,mx,my,mz,me,ph1x,ph1y,ph1z,ph1e,ph2x,ph2y,ph2z,ph2e,minv,p1inv,p2inv;
  d.Branch("vb",&vb,"vb/I");
  d.Branch("dx",&dx,"dx/F");
  d.Branch("dy",&dy,"dy/F");
  d.Branch("dz",&dz,"dz/F");
  d.Branch("de",&de,"de/F");
  d.Branch("pw",&pw,"pw/F"); // partial width
  d.Branch("prob",&prob,"prob/F"); // probability
  d.Branch("detector",&detector,"detector/I"); 
  d.Branch("gb",&gb,"gb/F"); // coupling
  d.Branch("exprob",&exprob,"exprob/F"); // extrapolated probability
  d.Branch("mx",&mx,"mx/F");
  d.Branch("my",&my,"my/F");
  d.Branch("mz",&mz,"mz/F");
  d.Branch("me",&me,"me/F");
  d.Branch("minv",&minv,"minv/F");
  d.Branch("ph1x",&ph1x,"ph1x/F");
  d.Branch("ph1y",&ph1y,"ph1y/F");
  d.Branch("ph1z",&ph1z,"ph1z/F");
  d.Branch("ph1e",&ph1e,"ph1e/F");
  d.Branch("p1inv",&p1inv,"p1inv/F");
  d.Branch("ph2x",&ph2x,"ph2x/F");
  d.Branch("ph2y",&ph2y,"ph2y/F");
  d.Branch("ph2z",&ph2z,"ph2z/F");
  d.Branch("ph2e",&ph2e,"ph2e/F");
  d.Branch("p2inv",&p2inv,"p2inv/F");
  /*d.Branch("sb",&sb,"sb/F"); // SBND events
  d.Branch("mi",&mi,"mi/F"); // MicroBooNE events
  d.Branch("ic",&ic,"ic/F"); // Icarus events*/
  
  TH1F *g = new TH1F("g","",8,log10(0.000000001),log10(0.1));
  TH1F *proj = new TH1F("proj","",1000,0,1);
  TH1F *sb = new TH1F("sb","",1000,0,1);
  TH1F *mi = new TH1F("mi","",1000,0,1);
  TH1F *ic = new TH1F("ic","",1000,0,1);
  TH2F *ssb = new TH2F("ssb","",48,.140,.620,8,log10(0.00000001),log10(0.1));
  TH2F *smi = new TH2F("smi","",48,.140,.620,8,log10(0.00000001),log10(0.1));
  TH2F *sic = new TH2F("sic","",48,.140,.620,8,log10(0.00000001),log10(0.1));
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
      float alpha_EM = 7.29735257*pow(10.0,-3.0);
      float pi = 3.141592653589;
      float f_pion = 0.093;
      float mass_pion = 0.139570;

      //for(const auto* fe : frontend)
      //      for(float k=0.1; k>0.000000001; k*=.1) // a proxy for alpha_B
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
		      g->Fill(gb);
		      proj->Fill(exprob);
		      if(detector == 0) {sb->Fill(exprob);ssb->Fill(vmass,k,prob);}
		      if(detector == 1) {mi->Fill(exprob);smi->Fill(vmass,k,prob);}
		      if(detector == 2) {ic->Fill(exprob);sic->Fill(vmass,k,prob);}
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
		      minv = piinv;
		      float ph1inv = Photon1.Mag();
		      p1inv = ph1inv;
		      float ph2inv = Photon2.Mag();
		      p2inv = ph2inv;
		      mx = PiZero[0];
		      my = PiZero[1];
		      mz = PiZero[2];
		      me = PiZero[3];
		      ph1x = Photon1[0];
		      ph1y = Photon1[1];
		      ph1z = Photon1[2];
		      ph1e = Photon1[3];
		      ph2x = Photon2[0];
		      ph2y = Photon2[1];
		      ph2z = Photon2[2];
		      ph2e = Photon2[3];
		      d.Fill();
		      ctr++;
		    } // <-- end vy if
		  else
		    {continue;}
		} // <-- end vx if
	      else
		{continue;}
	    } // <-- end j loop/end frontend loop
	  
	} // <-- end k loop
    }
  fout->Append(g); fout->Append(proj); fout->Append(sb); fout->Append(mi); fout->Append(ic); fout->Append(ssb); fout->Append(smi); fout->Append(sic);
  y->Close();
  fout->Write();  
} // <-- end void
#endif
