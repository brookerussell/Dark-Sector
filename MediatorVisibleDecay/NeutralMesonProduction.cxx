#ifndef NEUTRALMESONPRODUCTION_CXX
#define NEUTRALMESONPRODUCTION_CXX

#include "NeutralMesonProduction.h"

// ##########################################################################
// ###  This code takes in the simulated Pi0 production from the BNB      ###
// ### code and then produces the heavier mesons which could have been    ###
// ###    created instead (e.g. eta, rho, omega, eta-prime, phi)          ###
// ###                                                                    ###
// ###      Once created, it then distributes the remaining energy and    ###
// ### momentum such that Px_initial / Ptot_inital = Px_final/ Ptot_final ###
// ###                                                                    ###
// ###           OUTPUT: the kinematic information for the                ###
// ###            created eta, rho, omega, eta prime, phi                 ###
// ##########################################################################

void NeutralMesonProduction::NMP()
{
  TFile* f = new TFile("PiNtuple.root");
  TTree *np = (TTree*)f->Get("np");

  // Instantiating variables to read the Pi0 ntuple
  const int kMaxParticles = 10000;
  Int_t npizero;
  Float_t neutral_mom[kMaxParticles];
  
  // Grabbing the branches from TFile f for the Pi0
  np->SetBranchAddress("npizero",&npizero); // Number of Pi0's in ntuple
  np->SetBranchAddress("neutral_mom",&neutral_mom);// Pi0 3-momentum

  TFile* fout = TFile::Open("NeutralMesonProduction_output.root","RECREATE");
  TTree nmp("nmp",""); 
  
  
  // Useful variables for storing the created mesons
  int uniquePi0,Pi0Meson,nMesons;
  float mesonID,mesonMass;
  double mesonPx,mesonPy,mesonPz,mesonE;
  TLorentzVector meson;
  nmp.Branch("uniquePi0",&uniquePi0,"uniquePi0/I"); // # to track Pi0 parent
  nmp.Branch("Pi0Meson",&Pi0Meson,"Pi0Meson/I"); // tracks meson from Pi0
  nmp.Branch("nMesons",&nMesons,"nMesons/I"); // # of newly created mesons
  nmp.Branch("mesonID",&mesonID,"mesonID/F"); // Meson ID
  nmp.Branch("mesonMass",&mesonMass,"mesonMass/F"); // Meson mass
  nmp.Branch("meson",&meson); // Meson 4-vector (E,P)
  nmp.Branch("mesonPx",&mesonPx,"mesonPx/D"); // Meson Px
  nmp.Branch("mesonPy",&mesonPy,"mesonPy/D"); // Meson Py
  nmp.Branch("mesonPz",&mesonPz,"mesonPz/D"); // Meson Pz
  nmp.Branch("mesonE",&mesonE,"mesonE/D"); // Meson E

  Int_t nentries = (Int_t)np->GetEntries(); // Grabbing the # of events (POT)
  
  uniquePi0 = 0; // Instantiate the Pi0 identifier #

  std::cout << "Make neutral mesons from Pi0s"<<std::endl;

  for(Int_t i=0; i<nentries; i++) // Looping over all events
    {
      //if(i % 10000 == 0){std::cout<<"Event = "<<i<<std::endl;}  

      np->GetEntry(i);

      for(Int_t j=0; j<npizero; j++) // Looping over total # Pi0's in event
        {
	  uniquePi0++;

	  // Setting a vector of mass's (in GeV) of the particles 
	  // that we are "faking" their creation; 
	  // Eta = 0.547 GeV, Omega = 0.775 GeV, Rho = 0.783 GeV, 
	  // Eta-prime = 0.958 GeV, Phi = 1.02 GeV   
	  float fakeMass[5] = {0.54785,0.77526,0.78265,0.95778,1.019461};
	  
	  for(const auto& fM : fakeMass) // looping over all the "fake" particles
	    {
	          
	      // Pi0 3-momentum 
	      float pi0Momentum = sqrt(neutral_mom[0]*neutral_mom[0]+
				       neutral_mom[1]*neutral_mom[1]+
				       neutral_mom[2]*neutral_mom[2]);
	      
	      // Inferred Pi0 energy
	      float iE = sqrt(0.139*0.139+pi0Momentum*pi0Momentum);
	         	         
	      if((iE*iE)>(fM*fM))
		{
		  // 3-momentum of the new meson; p = sqrt(E^2 - m^2)
		  float fakePnew = sqrt((iE*iE)-(fM*fM));
		  
		  // Energy of the new momentum; E =  sqrt (P^2 - m^2)
		  double fakeE = sqrt( (fakePnew*fakePnew) + (fM*fM) );
		  
		  // Assigning meson component momentum (e.g. px, py, pz)  
		  // in a similar ratio as original pi0 component momentum 
		  double fakePx = (fakePnew*neutral_mom[0])/pi0Momentum; 
		  double fakePy = (fakePnew*neutral_mom[1])/pi0Momentum;
		  double fakePz = (fakePnew*neutral_mom[2])/pi0Momentum;
		  
		  mesonPx = fakePx;
		  mesonPy = fakePy;
		  mesonPz = fakePz;
		  mesonE = fakeE;
		  meson.SetPxPyPzE(fakePx,
				   fakePy,
				   fakePz,
				   fakeE);


		  Pi0Meson = uniquePi0;

		  // Meson id variable definition
		  float id; // meson id
		  if (fM == fakeMass[0]){ id = 1; } // Eta
		  if (fM == fakeMass[1]){ id = 2; } // Omega
		  if (fM == fakeMass[2]){ id = 3; } // Rho
		  if (fM == fakeMass[3]){ id = 4; } // Eta prime
		  if (fM == fakeMass[4]){ id = 5; } // Rho

		  mesonMass = fM; // 		  
		  mesonID = id;

		  meson.Clear();
		  
		  nmp.Fill();
		} // <-- end if energy^2 > mass^2
	    } // <-- end fakeMass loop
	} // <-- end j loop       
    } // <-- end i loop 
  f->Close(); 
  fout->Write(); 
} // <-- end void


#endif
