#ifndef MEDIATORSELECTION_CXX
#define MEDIATORSELECTION_CXX

#include "MediatorSelection.h"
#include <random>
#include <vector>
#include <map>

// ########################################################################## 
// ###            This code takes in the vector bosons from               ###
// ###         MediatorProduction.h/cxx and then randomly selects         ###
// ###           one corresponding to a single Pi0 so as not to           ###
// ###                  overcount vector boson production                 ###
// ###                                                                    ###  
// ###           OUTPUT: the kinematic information for the                ###                                                                                
// ###                     vector boson mediator                          ###                                                                                
// ##########################################################################

void MediatorSelection::MS()
{
  TFile* f = new TFile("MediatorProduction_output.root");
  TTree *mp = (TTree*)f->Get("mp");
  
// Instantiating variables to read the vector boson ntuple
  int uniqueVB,nVbosons;
  int mesonMotherID,Pi0_identifier,Pi0Meson_identifier,Pi0VB_identifier;
  double VB_Px,VB_Py,VB_Pz,VB_E,VB_mass;

  mp->SetBranchAddress("uniqueVB",&uniqueVB);
  mp->SetBranchAddress("nVbosons",&nVbosons);
  mp->SetBranchAddress("mesonMotherID",&mesonMotherID);
  mp->SetBranchAddress("Pi0_identifier",&Pi0_identifier);
  mp->SetBranchAddress("Pi0Meson_identifier",&Pi0Meson_identifier);
  mp->SetBranchAddress("Pi0VB_identifier",&Pi0VB_identifier);
  mp->SetBranchAddress("VB_Px",&VB_Px);
  mp->SetBranchAddress("VB_Py",&VB_Py);
  mp->SetBranchAddress("VB_Pz",&VB_Pz);
  mp->SetBranchAddress("VB_E",&VB_E);
  mp->SetBranchAddress("VB_mass",&VB_mass);

  TFile* fout = TFile::Open("MediatorSelection_output.root","RECREATE");
  TTree ms("ms","");

  int nVB,mesonMother_id,Pi0_id;
  double VB_PX,VB_PY,VB_PZ,VB_ENERGY,VB_MASS;
  TLorentzVector VB;

  ms.Branch("nVB",&nVB,"nVB/I");
  ms.Branch("mesonMother_id",&mesonMother_id,"mesonMother_id/I");
  ms.Branch("Pi0_id",&Pi0_id,"Pi0_id/I");
  ms.Branch("VB_PX",&VB_PX,"VB_PX/D");
  ms.Branch("VB_PY",&VB_PY,"VB_PY/D");
  ms.Branch("VB_PZ",&VB_PZ,"VB_PZ/D");
  ms.Branch("VB_ENERGY",&VB_ENERGY,"VB_ENERGY/D");
  ms.Branch("VB_MASS",&VB_MASS,"VB_MASS/D");
  ms.Branch("VB",&VB); // VB 4-vector

  Int_t entries = (Int_t)mp->GetEntries(); // Grabbing the # of events (POT)

  int a = 0;
  int ctr = 0;
  std::vector<int> temp;
  std::map<int,std::vector<int>> interim;
  std::map<int,int> provisional;
  int random_element;

  std::cout << "Randomly choosing one mediator from a Pi0 mother" << std::endl;

  for(Int_t i=0; i<entries; i++) // Looping over all events
    {
      mp->GetEntry(i);

      // if the value of Pi0_identifier has changed,
      // then save the old Pi0_identifier info
      if(a != Pi0_identifier)
	{
	  interim[a]=temp;
	  temp.clear();
	} // <-- end if statement

      if(Pi0_identifier == Pi0VB_identifier)
	{
	  temp.push_back(uniqueVB);
	} // <-- end if statement

      a = Pi0_identifier;
    } // <-- end i loop
  
  for(auto const &entity : interim)
    {
      std::vector<int> makeshift = entity.second;
      // Choosing a random element from a vector
      std::random_device random_device;
      std::mt19937 engine{random_device()};
      std::uniform_int_distribution<int> dist(0,makeshift.size() - 1);
      random_element = makeshift[dist(engine)];
      makeshift.clear();
      ctr++;
      provisional[ctr]=random_element;
    } // <-- end interim loop

  for(Int_t j=0; j<entries; j++)
    {
      mp->GetEntry(j);
      for(auto const &other : provisional)
	{
	  if(uniqueVB == other.second)
	    {
	      VB_PX = VB_Px;
	      VB_PY = VB_Py;
	      VB_PZ = VB_Pz;
	      VB_ENERGY = VB_E;
	      VB_MASS = VB_mass;
	      VB.SetPxPyPzE(VB_Px,
			    VB_Py,
			    VB_Pz,
			    VB_E);

	      Pi0_id = Pi0_identifier;
	      mesonMother_id = mesonMotherID;
	      
	      ms.Fill();
	    } // <-- end if statement
	} // <-- end provisional loop
    } // <-- end j loop
  f->Close();
  fout->Write();

}

#endif