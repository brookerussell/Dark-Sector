#ifndef MESON_CXX
#define MESON_CXX

#include "Meson.h"

// ##########################################################################
// ###  This code takes in the simulated Pi0 production from the BNB      ###
// ### code and then produces the heavier mesons which could have been    ###
// ###    created instead (e.g. eta, rho, omega, eta-prime, phi)          ###
// ###                                                                    ###
// ###      Once created, it then distributes the remaining energy and    ###
// ### momentum such that Px_initial / Ptot_inital = Px_final/ Ptot_final ###
// ##########################################################################

void Meson::SetParams()
{
  // ####################################################
  // ### Opening the Pion Ntuple (note this file must ###
  // ###    match what is set in mac/default.py       ###
  // ####################################################
  TFile* f = new TFile("PiNtuple.root");
  TTree *np = (TTree*)f->Get("np");
  
  
  // ### Grabbing the variables for the Pi0 ###
  const int kMaxParticles = 10000;
  Int_t npizero;
  Float_t neutral_mom[kMaxParticles];
  
  // ### Grabbing the branches from TFile f for the Pi0 ###
  np->SetBranchAddress("npizero",&npizero); 		//<--- Number of Pi0's in ntuple
  np->SetBranchAddress("neutral_mom",&neutral_mom);	//<--- Pi0 3-momentum

  // #################################################################################
  // ###   Creating a file which will output the results of running this script    ###
  // ### Namely, the information about the created eta, rho, omega, eta-prime, phi ###
  // #################################################################################
  TFile* fout = TFile::Open("Woburn.root","RECREATE");
  TTree l("l",""); //<---Tree name "l"
  
  
  // ### Useful variables for storing the created ###
  int nMesons;
  float mesonID,mesonPx,mesonPy,mesonPz,mesonE,mesonPnew,mesonMass;
  
  // ### Number of newly created mesons ### 
  l.Branch("nMesons",&nMesons,"nMesons/I");
  
  // ### Meson ID: Eta == 1, Omega == 2, Rho == 3, Eta-prime == 4, Phi == 5 ###
  l.Branch("mesonID",&mesonID,"mesonID/F"); // meson id
  
  // ### Meson Px (GeV) ###
  l.Branch("mesonPx",&mesonPx,"mesonPx/F"); 
  
  // ### Meson Py (GeV) ###
  l.Branch("mesonPy",&mesonPy,"mesonPy/F");
  
  // ### Meson Pz (GeV) ###
  l.Branch("mesonPz",&mesonPz,"mesonPz/F");
  
  // ### Meson Energy (GeV) ###
  l.Branch("mesonE",&mesonE,"mesonE/F"); // energy
  
  // ### Meson new momentum P = E^2 - m^2 ###
  l.Branch("mesonPnew",&mesonPnew,"mesonPnew/F"); //3-momentum
  
  // ### Meson mesonMass (for the newly created particle ###
  l.Branch("mesonMass",&mesonMass,"mesonMass/F"); //meson mass
  
  // ########################
  // ### Histogram Checks ###
  // ########################
  TH1F *x = new TH1F("x","P_{x}",400,-2,2);
  TH1F *y = new TH1F("y","P_{y}",400,-2,2);
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
  
  
  // ### counter for mesons produced ###
  int ctr = 0;
  
  // ### Grabbing the number of events (POT) ###
  Int_t nentries = (Int_t)np->GetEntries();
  
  // ###############################
  // ### Looping over all events ###
  // ###############################
  for(Int_t i=0; i<nentries; i++)
    {
    
   // ### Printing Events ###
   if(i % 10000 == 0){std::cout<<"Event = "<<i<<std::endl;}  
      // ### Getting current entry for this event ###
      np->GetEntry(i);
      
      // ### Looping over the total number of Pi0's in the event ###
      for(Int_t j=0; j<npizero; j++)
        {
	// ###  Setting a vector of the mass's (in GeV) of the particles we are trying to "fake" their creation ###
	// ###     Eta = 0.547 GeV, Omega = 0.775 GeV, Rho = 0.783 GeV, Eta-prime = 0.958 GeV, Phi = 1.02 GeV   ###
	float fakeMass[5] = {0.54785,0.77526,0.78265,0.95778,1.019461};
	
	// ### Looping over all the "fake" particles we are trying to create
	for(const auto& fM : fakeMass)
	  {
	    
	    // ### Grabbing the Pi0 3-momentum ###
	    float pi0Momentum = sqrt(neutral_mom[0]*neutral_mom[0]+
			    neutral_mom[1]*neutral_mom[1]+
			    neutral_mom[2]*neutral_mom[2]);
	    // ### Calculating the Pi0 (inferred) energy ###
	    float iE = sqrt(0.139*0.139+pi0Momentum*pi0Momentum);
	    
	    
	    // ### Proceed if the inferred energy squared is greater than ###
	    // ###       the square of the mass of the "new" meson        ###
	    if((iE*iE)>(fM*fM))
	      {
		// ### The new 3-momentum of the meson is sqrt(E^2 - m^2)
		float fakePnew = sqrt((iE*iE)-(fM*fM)); // meson 3-momentum
		
		// ### The new energy given the new momentum sqrt (P^2 - m^2)
		float fakeE = sqrt( (fakePnew*fakePnew) + (fM*fM) ); // meson energy
		
		// ### Assigning meson component momentum (e.g. px, py, pz)  ###
		// ### in a similar ratio as original pi0 component momentum ###
		float fakePx = (fakePnew*neutral_mom[0])/pi0Momentum; 
		float fakePy = (fakePnew*neutral_mom[1])/pi0Momentum;
		float fakePz = (fakePnew*neutral_mom[2])/pi0Momentum;
		
		// ### Setting the branches ###
		mesonPx = fakePx;
		mesonPy = fakePy;
		mesonPz = fakePz;
		mesonE = fakeE;
		mesonPnew = fakePnew;
		
		// ### Defining the id variable for a given particle we are createing ###
		float id; // meson id
		if (fM == fakeMass[0]){ id = 1; } //<---Eta
		if (fM == fakeMass[1]){ id = 2; } //<---Omega
		if (fM == fakeMass[2]){ id = 3; } //<---Rho
		if (fM == fakeMass[3]){ id = 4; } //<---Eta-prime
		if (fM == fakeMass[4]){ id = 5; } //<---Rho
		
		// ### Making Eta Histograms ###
		if(id == 1)
		  { 
		  // ### Defining temp invariant mass ###
		  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
		  etmome->Fill(fakePnew,fakeE);
		  etpxpz->Fill(fakePx,fakePz);
		  etpypz->Fill(fakePy,fakePz);
		  inveta->Fill(tempInvMass);
		  }
		
		// ### Making Omega Histograms ###
		if(id == 2)
		  { 
		  // ### Defining temp invariant mass ###
		  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
		  invomega->Fill(tempInvMass);
		  ommome->Fill(fakePnew,fakeE);
		  ompxpz->Fill(fakePx,fakePz);
		  ompypz->Fill(fakePy,fakePz);
		  }
		
		// ### Making Eta Histograms ###
		if(id == 3)
		  {
		  // ### Defining temp invariant mass ###
		  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) ); 
		  invrho->Fill(tempInvMass);
		  rhomome->Fill(fakePnew,fakeE);
		  rhopxpz->Fill(fakePx,fakePz);
		  rhopypz->Fill(fakePy,fakePz);
		  }
		
		// ### Making Eta-prime Histograms ###
		if(id == 4)
		  { 
		  // ### Defining temp invariant mass ###
		  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
		  invetap->Fill(tempInvMass);
		  etpmome->Fill(fakePnew,fakeE);
		  etappxpz->Fill(fakePx,fakePz);
		  etappypz->Fill(fakePy,fakePz);
		  }
		
		// ### Making phi histograms ###
		if(id == 5)
		  { 
		  // ### Defining temp invariant mass ###
		  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
		  invphi->Fill(tempInvMass);
		  phimome->Fill(fakePnew,fakeE);
		  phipxpz->Fill(fakePx,fakePz);
		  phipypz->Fill(fakePy,fakePz);
		  }
		
		// ### Filling the TTree ###
		mesonMass = fM;
		mesonID = id;
		
		// ### Defining temp invariant mass ###
		float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
		
		// ### Checking the defined invariant mass versus the calculated invariant mass (sanity check) ###
		minv->Fill(fM,tempInvMass);
		
		// ### Pi0 invariant mass versus new invariant mass (sanity check) ###
		float tempPi0Mass = sqrt(iE*iE-pi0Momentum*pi0Momentum);
		oinvninv->Fill(tempPi0Mass,tempInvMass);
		
		// ### More simple sanity plots ###
		x->Fill(fakePx);
		y->Fill(fakePy);
		z->Fill(fakePz);
		e->Fill(fakeE);
		m->Fill(fM);
		n->Fill(pi0Momentum,fakePnew);
		d->Fill(id);
		ie->Fill(id,fakeE);
		msen->Fill(fM,fakeE);
		momoe->Fill(pi0Momentum,iE);
		momne->Fill(fakePnew,fakeE);
		opxpz->Fill(neutral_mom[0],neutral_mom[2]);
		npxpz->Fill(fakePx,fakePz);
		opypz->Fill(neutral_mom[1],neutral_mom[2]);
		npypz->Fill(fakePy,fakePz);
		
		// ### Iterate a counter if we made a new meson ###
		ctr++;
		
		} // <-- end if
	  } // <-- end fakeMass loop 
	} // <-- end j loop
      //} // end i loop
  
  // ### If we made a new meson go into this loop ###
  if(ctr>0)
      {
	nMesons = ctr; // total number of mesons populated in tree
        l.Fill(); // fill the tree
      }
    } // <-- end i loop 
  f->Close(); 
  fout->Write(); 
} // <-- end void

#endif
