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
  int eventNum,uniqueVB,mesonTOvb,pi0TOvb,mesonMotherID;
  double omass,VB_mass;
  double VB_Px,VB_Py,VB_Pz,VB_E;

  mp->SetBranchAddress("eventNum",&eventNum); // Event number
  mp->SetBranchAddress("uniqueVB",&uniqueVB); // # to track VB
  mp->SetBranchAddress("mesonTOvb",&mesonTOvb); // Links meson to VB
  mp->SetBranchAddress("pi0TOvb",&pi0TOvb); // Links Pi0 to VB
  mp->SetBranchAddress("mesonMotherID",&mesonMotherID);
  mp->SetBranchAddress("omass",&omass); // Meson mother mass
  mp->SetBranchAddress("VB_mass",&VB_mass); // VB mass (GeV)
  mp->SetBranchAddress("VB_Px",&VB_Px); // VB Px (GeV)
  mp->SetBranchAddress("VB_Py",&VB_Py); // VB Py (GeV)
  mp->SetBranchAddress("VB_Pz",&VB_Pz); // VB Pz (GeV)
  mp->SetBranchAddress("VB_E",&VB_E); // VB energy (GeV)

  TFile* fout = TFile::Open("MediatorSelection_output.root","RECREATE");
  TTree ms("ms","");

  int eventNUM,UniqueVB,MesonToVB,Pi0ToVB,mesonMother_id;
  double VB_PX,VB_PY,VB_PZ,VB_ENERGY,VB_MASS;
  TLorentzVector VB;
  ms.Branch("eventNUM",&eventNUM,"eventNUM/I"); // Event number
  ms.Branch("UniqueVB",&UniqueVB,"UniqueVB/I"); // # to track VB
  ms.Branch("MesonToVB",&MesonToVB,"MesonToVB/I"); // Links meson to VB
  ms.Branch("Pi0ToVB",&Pi0ToVB,"Pi0ToVB/I"); // Links Pi0 to VB
  ms.Branch("mesonMother_id",&mesonMother_id,"mesonMother_id/I"); 
  ms.Branch("VB_PX",&VB_PX,"VB_PX/D"); // VB Px (GeV)
  ms.Branch("VB_PY",&VB_PY,"VB_PY/D"); // VB Py (GeV)
  ms.Branch("VB_PZ",&VB_PZ,"VB_PZ/D"); // VB Pz (GeV)
  ms.Branch("VB_ENERGY",&VB_ENERGY,"VB_ENERGY/D"); // VB energy (GeV)
  ms.Branch("VB_MASS",&VB_MASS,"VB_MASS/D"); // VB mass (GeV)
  ms.Branch("VB",&VB); // VB 4-vector



  Int_t entries = (Int_t)mp->GetEntries(); // Grabbing the # of events (POT)

  int a = 0;
  int ctr = 0;
  std::vector<int> temp;
  std::map<int,std::vector<int>> interim;
  std::map<int,int> provisional;

  std::cout << "START mediator selection"<<std::endl;

  for(Int_t i=0; i<entries; i++) // Loop over all events
    {
      mp->GetEntry(i);

      // If the Pi0 mother has changed sinced the last entry
      if(a != pi0TOvb)
	{
	  interim[a]=temp;
	  temp.clear();
	} // <-- end if statement

	  // Save to vector the unique VB ID #
	  temp.push_back(uniqueVB);
	  
	  a = pi0TOvb;
    } // <-- end i loop
  
  // The code in this for loop comes from
  // http://www.cppsamples.com/common-tasks/choose-random-element.html
  // "Choose a random element" from a vector  
  for(auto const &entity : interim)
    {
      //      std::cout<<"\n Number of vector bosons belonging to one Pi0 mother: "<<entity.second.size()
      //       <<"\n Pi0 identifier #: "<< entity.first <<std::endl;

      std::vector<int> makeshift = entity.second;
     
      if(makeshift.size() == 0) continue;
      
      std::random_device random_device; 
      std::mt19937 engine{random_device()};
      std::uniform_int_distribution<int> dist(0,makeshift.size() - 1);
      int random_element = makeshift[dist(engine)];
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
	      // Assign TBranches
	      VB_PX = VB_Px;
	      VB_PY = VB_Py;
	      VB_PZ = VB_Pz;
	      VB_ENERGY = VB_E;
	      VB_MASS = VB_mass;
	      VB.SetPxPyPzE(VB_Px,
			    VB_Py,
			    VB_Pz,
			    VB_E);
	      eventNUM = eventNum;
	      UniqueVB = uniqueVB;
	      MesonToVB = mesonTOvb;
	      Pi0ToVB = pi0TOvb;
	      mesonMother_id = mesonMotherID;
	      
	      ms.Fill();
	    } // <-- end if statement
	} // <-- end provisional loop
    } // <-- end j loop

  std::cout<<"RANDOMLY choosing one mediator from a Pi0 mother" << std::endl;                                

  f->Close();
  fout->Write();

}

#endif
