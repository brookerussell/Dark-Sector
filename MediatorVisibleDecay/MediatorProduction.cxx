#ifndef MEDIATORPRODUCTION_CXX
#define MEDIATORPRODUCTION_CXX

#include "MediatorProduction.h"

// ##########################################################################  
// ###  This code takes in the mesons from NeutralMesonProduction.h/cxx   ###  
// ###     and then produces the vector boson mediator and a photon       ###
// ###                                                                    ###
// ###           OUTPUT: the kinematic information for the                ###  
// ###                     vector boson mediator                          ###  
// ##########################################################################

void MediatorProduction::MP()
{  
  TFile* f = new TFile("NeutralMesonProduction_output.root");
  TTree *nmp = (TTree*)f->Get("nmp");
  
  // Instantiating variables to read the meson ntuple
  int uniquePi0,Pi0Meson,nMesons;
  float mesonID,mesonMass;
  double mesonPx,mesonPy,mesonPz,mesonE;  

  // Grabbing the branches from TFile f for the meson
  nmp->SetBranchAddress("uniquePi0",&uniquePi0);
  nmp->SetBranchAddress("Pi0Meson",&Pi0Meson);
  nmp->SetBranchAddress("nMesons",&nMesons);
  nmp->SetBranchAddress("mesonID",&mesonID);
  nmp->SetBranchAddress("mesonPx",&mesonPx);
  nmp->SetBranchAddress("mesonPy",&mesonPy);
  nmp->SetBranchAddress("mesonPz",&mesonPz);
  nmp->SetBranchAddress("mesonE",&mesonE);
  nmp->SetBranchAddress("mesonMass",&mesonMass);

  TFile* fout = TFile::Open("MediatorProduction_output.root","RECREATE");
  TTree mp("mp","");

  int uniqueVB,nVbosons;
  int mesonMotherID,Pi0_identifier,Pi0Meson_identifier,Pi0VB_identifier; 
  double omass,VB_mass;
  double VB_Px,VB_Py,VB_Pz,VB_E;
  TLorentzVector meson_lf,VectorBoson,Photon;
  
  mp.Branch("uniqueVB",&uniqueVB,"uniqueVB/I");
  mp.Branch("nVbosons",&nVbosons,"nVbosons/I"); // # of newly created mediators
  mp.Branch("mesonMotherID",&mesonMotherID,"mesonMotherID/I");
  mp.Branch("Pi0_identifier",&Pi0_identifier,"Pi0_identifier/I");
  mp.Branch("Pi0Meson_identifier",&Pi0Meson_identifier,"Pi0Meson_identifier/I");
  mp.Branch("Pi0VB_identifier",&Pi0VB_identifier,"Pi0VB_identifier/I");
  mp.Branch("omass",&omass,"omass/D"); // Meson mother mass 
  mp.Branch("meson_lf",&meson_lf); // meson 4-vector
  mp.Branch("VectorBoson",&VectorBoson); // VB 4-vector
  mp.Branch("Photon",&Photon); // Photon 4-vector 
  mp.Branch("VB_Px",&VB_Px,"VB_Px/D"); // VB Px (GeV)
  mp.Branch("VB_Py",&VB_Py,"VB_Py/D"); // VB Py (GeV)
  mp.Branch("VB_Pz",&VB_Pz,"VB_Pz/D"); // VB Pz (GeV)
  mp.Branch("VB_E",&VB_E,"VB_E/D"); // VB energy (GeV)
  mp.Branch("VB_mass",&VB_mass,"VB_mass/D"); //VB mass

  Int_t mentries = (Int_t)nmp->GetEntries(); // Grabbing the # of events (POT)
  
  int ctr = 0; //Instantiate counter for unique vector boson
  double VB_P;

  std::cout << "Making the mediator from neutral mesons. " << std::endl;

  //for(Int_t i=0; i<mentries; i++) // Looping over all events
  for(Int_t i=0; i<10; i++)
    {
      //if(i % 1000 == 0){std::cout<<"Event = "<<i<<std::endl;} 
     
      nmp->GetEntry(i);
  
      meson_lf.SetPxPyPzE(mesonPx,
			  mesonPy,
			  mesonPz,
			  mesonE);
      
      // Decay in flight if the meson is 
      // an eta (ID == 1) or eta prime (ID == 4)
      if (mesonID == 1 || mesonID == 4)
	{
	  TGenPhaseSpace event_k;
	   
	  // Looping over mass ranges in 10 MeV steps 
	  for(float m = 0.140; m<0.630; m+=0.010)
	    {
	      double masses[2] = {m,0.0};
	          
	      // If the mass of the meson is greater than the mass
	      // of the vector boson, allow the vector voson decay      
	      if(mesonMass > m)
		{  
		  // Set the decay of the meson 
		  event_k.SetDecay(meson_lf,2,masses);
		  
		  event_k.Generate(); // Decay the particle
		  
		  TLorentzVector *vectorBoson = event_k.GetDecay(0);
		  TLorentzVector *photonInitial = event_k.GetDecay(1);
		  VectorBoson = *vectorBoson;
		  Photon = *photonInitial;

		  float VBinvMassAfter = sqrt( (VectorBoson[3]*VectorBoson[3]) - 
					       ( (VectorBoson[0]*VectorBoson[0]) +
						 (VectorBoson[1]*VectorBoson[1]) +
						 (VectorBoson[2]*VectorBoson[2]) ) );
		      
		  // Setting the output file branches
		  VB_Px = VectorBoson[0];
		  VB_Py = VectorBoson[1];
		  VB_Pz = VectorBoson[2];
		  VB_E  = VectorBoson[3];

		  VB_mass = VBinvMassAfter;

		  
		  omass = mesonMass;
		  mesonMotherID = mesonID;

		  Pi0_identifier = uniquePi0;
		  Pi0Meson_identifier = Pi0Meson;
		  Pi0VB_identifier = uniquePi0;

		  ctr++;
		  uniqueVB = ctr;
		  
		  mp.Fill();

		  //Clear all 4-momenta, otherwise a segfault will result
		  meson_lf.Clear();
		  VectorBoson.Clear();
		  Photon.Clear();
		} // <-- end if
	    } // <-- end m for loop
	} // <-- end eta/eta' if
      if(mesonID == 2 || mesonID == 3 || mesonID == 5)
	{
	  // Looping over mass ranges in 10 MeV steps
	  for(float n = 0.140; n < 0.630; n+=0.010)
	    {
	      double mesonP = sqrt(mesonPx*mesonPx +
				   mesonPy*mesonPy +
				   mesonPz*mesonPz);

	      // Inferred meson energy
	      float iE = sqrt((n*n)+(mesonP*mesonP)); 

	      if((iE*iE)>(n*n))
		{
		  // 3-momentum of the new vector boson; 
		  // p = sqrt(E^2 - m^2) ###
		  VB_P = sqrt((iE*iE)-(n*n));
		   
		  // Energy of the new vector boson;
		  // E =  sqrt(P^2 - m^2) ###
		  VB_E = sqrt((VB_P*VB_P)+(n*n));
		   
		  // Assigning vector boson component moment in a similar
		  // ratio as the original meson component momentum 
		  VB_Px = (VB_P*mesonPx)/mesonP;
		  VB_Py = (VB_P*mesonPy)/mesonP;
		  VB_Pz = (VB_P*mesonPz)/mesonP;
		   
		  float invMass = sqrt ( (VB_E*VB_E) -
					 ( (VB_Px*VB_Px) +
					   (VB_Py*VB_Py) +
					   (VB_Pz*VB_Pz) ) );
		  
		  VectorBoson.SetPxPyPzE(VB_Px,
					 VB_Py,
					 VB_Pz,
					 VB_E);
		  VB_mass = invMass;
		  omass = mesonMass;
		  mesonMotherID = mesonID;

		  Pi0_identifier = uniquePi0;
                  Pi0Meson_identifier = Pi0Meson;
                  Pi0VB_identifier = uniquePi0;

		  ctr++;
                  uniqueVB = ctr;
		  		    
		  mp.Fill();
		} // <-- if energy^2 is greater than mesonMass^2
	    } // <-- end n loop 
	} // <-- end if meson #2,3,5
      

} // <-- end i loop 
  f->Close();
  fout->Write();
}


#endif
