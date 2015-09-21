#ifndef MESON_CXX
#define MESON_CXX

#include "Meson.h"
void Meson::SetParams()
{
  TFile* f = new TFile("PiNtuple.root");
  TTree *np = (TTree*)f->Get("np");
  const int kMaxParticles = 10000;
  Int_t npizero;
  Float_t neutral_mom[kMaxParticles];
  np->SetBranchAddress("npizero",&npizero);
  np->SetBranchAddress("neutral_mom",&neutral_mom);

  TFile* fout = TFile::Open("Woburn.root","RECREATE");
  TTree l("l","");
  int mesons;
  float mid,mx,my,mz,me,mnew,mass;
  l.Branch("mesons",&mesons,"mesons/I");
  l.Branch("mid",&mid,"mid/F"); // meson id
  l.Branch("mx",&mx,"mx/F"); //x-momentum
  l.Branch("my",&my,"my/F");
  l.Branch("mz",&mz,"mz/F");
  l.Branch("me",&me,"me/F"); // energy
  l.Branch("mnew",&mnew,"mnew/F"); //3-momentum
  l.Branch("mass",&mass,"mass/F"); //meson mass
  TH1F *x = new TH1F("x","P_{x}",200,-1,1);
  TH1F *y = new TH1F("y","P_{y}",200,-1,1);
  TH1F *z = new TH1F("z","P_{z}",800,0,8); 
  TH1F *e = new TH1F("e","Energy",800,0,8);
  TH1F *m = new TH1F("m","Mass",1100,0,1.1);
  TH2F *n = new TH2F("n","P_{old} vs. P_{new}",1000,0,10,1000,0,10);
  TH1F *d = new TH1F("d","Particle ID",5,1,6);
  TH2F *ie = new TH2F("ie","Particle ID vs. Energy",5,1,6,1000,0,10);
  TH2F *msen = new TH2F("msen","Mass vs. Energy",600,0.5,1.1,800,0,8);
  TH2F *momoe = new TH2F("momoe","P_{old} vs. Energy",800,0,8,800,0,8);
  TH2F *momne = new TH2F("momne","P_{new} vs. Energy",800,0,8,800,0,8);
  TH2F *etmome = new TH2F("etamome","P_{eta} vs. Energy_{eta}",800,0,8,800,0,8);
  TH2F *ommome = new TH2F("ommome","P_{#omega} vs. Energy_{#omega}",800,0,8,800,0,8);
  TH2F *rhomome = new TH2F("rhomome","P_{#rho} vs. Energy_{#rho}",800,0,8,800,0,8);
  TH2F *etpmome = new TH2F("etpmome","P_{#eta'} vs. Energy_{#eta'}",800,0,8,800,0,8);
  TH2F *phimome = new TH2F("phimome","P_{#phi} vs. Energy_{#phi}",800,0,8,800,0,8);
  TH2F *opxpz = new TH2F("opxpz"," Old P_{x} vs. Old P_{z} ",200,-1,1,800,0,8);
  TH2F *npxpz = new TH2F("npxpz"," New P_{x} vs. New P_{z} ",200,-1,1,800,0,8);
  TH2F *opypz = new TH2F("opypz"," Old P_{y} vs. Old P_{z} ",200,-1,1,800,0,8);
  TH2F *npypz = new TH2F("npypz"," New P_{y} vs. New P_{z} ",200,-1,1,800,0,8);
  TH2F *etpxpz = new TH2F("etpxpz", "P_{x_{#eta}} vs. P_{z_{#eta}}",200,-1,1,800,0,8);
  TH2F *etpypz = new TH2F("etpypz", "P_{y_{#eta}} vs. P_{z_{#eta}}",200,-1,1,800,0,8);
  TH2F *ompxpz = new TH2F("ompxpz", "P_{x_{#omega}} vs. P_{z_{#omega}}",200,-1,1,800,0,8);
  TH2F *ompypz = new TH2F("ompypz", "P_{y_{#omega}} vs. P_{z_{#omega}}",200,-1,1,800,0,8);
  TH2F *rhopxpz = new TH2F("rhopxpz", "P_{x_{#rho}} vs. P_{z_{#rho}}",200,-1,1,800,0,8);
  TH2F *rhopypz = new TH2F("rhopypz", "P_{y_{#rho}} vs. P_{z_{#rho}}",200,-1,1,800,0,8);
  TH2F *etappxpz = new TH2F("etappxpz", "P_{x_{#eta'}} vs. P_{z_{#eta'}}",200,-1,1,800,0,8);
  TH2F *etappypz = new TH2F("etappypz", "P_{y_{#eta'}} vs. P_{y_{#eta'}}",200,-1,1,800,0,8);
  TH2F *phipxpz = new TH2F("phipxpz", "P_{x_{#phi}} vs. P_{z_{#phi}}", 200,-1,1,800,0,8);
  TH2F *phipypz = new TH2F("phipypz", "P_{y_{#phi}} vs. P_{z_{#phi}}", 200,-1,1,800,0,8);
  TH1F *inveta = new TH1F("inveta","#eta Invariant Mass",1100,0,1.1);
  TH1F *invetap = new TH1F("invetap","#eta' Invariant Mass",1100,0,1.1);
  TH1F *invrho = new TH1F("invrho","#rho Invariant Mass",1100,0,1.1);
  TH1F *invomega = new TH1F("invomega","#omega Invariant Mass",1100,0,1.1);
  TH1F *invphi = new TH1F("invphi","#phi Invariant Mass",1100,0,1.1);
  TH2F *minv = new TH2F("minv","Invariant Mass vs. Mass",600,.5,1.1,600,.5,1.1);
  TH2F *oinvninv = new TH2F("oinvninv","Old I.M. vs. New I.M.",1000,.1,1.1,600,.5,1.1);
  int ctr = 0;
  Int_t nentries = (Int_t)np->GetEntries();
  for(Int_t i=0; i<nentries; i++)
    {
      np->GetEntry(i);
      for(Int_t j=0; j<npizero; j++)
      {
	float fakeMass[5] = {0.54785,0.77526,0.78265,0.95778,1.019461};
	for(const auto& fM : fakeMass)
	  {
	    // pi0 3-momentum
	    float mM = sqrt(neutral_mom[0]*neutral_mom[0]+
			    neutral_mom[1]*neutral_mom[1]+
			    neutral_mom[2]*neutral_mom[2]);
	    // pi0 (inferred) energy
	    float iE = sqrt(0.139*0.139+mM*mM);
	    // proceed if the inferred energy is greater than
	    // the mass of the "new" meson
	    if(iE-fM>0)
	      {
		float fakeE = iE-fM; // meson energy
		float fakePnew = sqrt(fakeE*fakeE+fM*fM); // meson 3-momentum
		// assign meson component momentum (e.g. px, py, pz)
		//in a similar ratio as original pi0 component momentum
		float fakePx = (fakePnew*neutral_mom[0])/mM; 
		float fakePy = (fakePnew*neutral_mom[1])/mM;
		float fakePz = (fakePnew*neutral_mom[2])/mM;
		mx = fakePx;
		my = fakePy;
		mz = fakePz;
		me = fakeE;
		mnew = fakePnew;
		float id; // meson id
		if (fM == fakeMass[0]){ id = 1; }
		if (fM == fakeMass[1]){ id = 2; }
		if (fM == fakeMass[2]){ id = 3; }
		if (fM == fakeMass[3]){ id = 4; }
		if (fM == fakeMass[4]){ id = 5; }
		if(id == 1)
		  { etmome->Fill(fakePnew,fakeE);
		    etpxpz->Fill(fakePx,fakePz);
		    etpypz->Fill(fakePy,fakePz);
		    inveta->Fill(sqrt(std::abs(me*me-mnew*mnew)));}
		if(id == 2)
		  { invomega->Fill(sqrt(std::abs(me*me-mnew*mnew)));
		    ommome->Fill(fakePnew,fakeE);
		    ompxpz->Fill(fakePx,fakePz);
		    ompypz->Fill(fakePy,fakePz);}
		if(id == 3)
		  { invrho->Fill(sqrt(std::abs(me*me-mnew*mnew)));
		    rhomome->Fill(fakePnew,fakeE);
		    rhopxpz->Fill(fakePx,fakePz);
		    rhopypz->Fill(fakePy,fakePz);}
		if(id == 4)
		  { invetap->Fill(sqrt(std::abs(me*me-mnew*mnew)));
		    etpmome->Fill(fakePnew,fakeE);
		    etappxpz->Fill(fakePx,fakePz);
		    etappypz->Fill(fakePy,fakePz);}
		if(id == 5)
		  { invphi->Fill(sqrt(std::abs(me*me-mnew*mnew)));
		    phimome->Fill(fakePnew,fakeE);
		    phipxpz->Fill(fakePx,fakePz);
		    phipypz->Fill(fakePy,fakePz);}
		minv->Fill(fM,sqrt(std::abs(me*me-mnew*mnew)));
		oinvninv->Fill(sqrt(std::abs(iE*iE-mM*mM)),sqrt(std::abs(me*me-mnew*mnew)));
		mass = fM;
		mid = id;
		x->Fill(fakePx);
		y->Fill(fakePy);
		z->Fill(fakePz);
		e->Fill(fakeE);
		m->Fill(fM);
		n->Fill(mM,fakePnew);
		d->Fill(id);
		ie->Fill(id,fakeE);
		msen->Fill(fM,fakeE);
		momoe->Fill(mM,iE);
		momne->Fill(fakePnew,fakeE);
		opxpz->Fill(neutral_mom[0],neutral_mom[2]);
		npxpz->Fill(fakePx,fakePz);
		opypz->Fill(neutral_mom[1],neutral_mom[2]);
		npypz->Fill(fakePy,fakePz);
		ctr++;
		} // <-- end if
	  } // <-- end fakeMass loop 
	} // <-- end j loop
      //} // end i loop
  if(ctr>0)
      {
	mesons = ctr; // total number of mesons populated in tree
        l.Fill(); // fill the tree
      }
    } // <-- end i loop 
  f->Close(); 
  fout->Write(); 
} // <-- end void

#endif
