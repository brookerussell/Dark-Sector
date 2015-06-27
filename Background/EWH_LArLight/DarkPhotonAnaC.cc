// This code does the analysis on photons in an event. \n
// It is wrapped in dark_photon_ana.py

// It was originally designed to work with MCC4 files \n
// and several of the distinctions made in the various histograms \n
// are based on the MCC4 definition of "primary," which was \n
// changed in MCC5 and is no longer useful. 

// For the April APS, Histogram Case "B" was used. 

// Before using, make sure to link relevant classes, defined in LArLight:
// LineDist, MinaTestEvent, MinaTestParticle


#ifndef DARKPHOTONANAC_CC
#define DARKPHOTONANAC_CC

#include "DarkPhotonAnaC.hh"
#include "LineDist.hh"

struct PhotonPair{ 
  MinaTestParticle part1;
  MinaTestParticle part2;
  double dist;
};

double DarkPhotonAnaC::RunPOTLoop(TTree* tree)
{
  std::cout << "In POT loop" << std::endl;
  
  //Check whether pot branch exists
  if(!(tree->GetBranch("Toy_POT_branch"))) {

    std::cerr
      << "\033[93m" 
      << "Input TTree has no branch called \"Toy_POT_branch\"!" 
      << "\033[00m" << std::endl;
    return 0.;
  }

  double pot = 0;
  
  tree->SetBranchAddress("Toy_POT_branch",&pot);
  
  double TotalPOT = 0.;

   for(size_t i=0; i<tree->GetEntries(); ++i) {
     
     std::cout << "Entry Number " << i << std::endl;
     std::cout << tree->GetEntry(i) << std::endl;
     std::cout << pot << std::endl;
     

     
     TotalPOT += pot;
     
   }
   return TotalPOT;
}
//struct PhotonGroup : std::vector<MinaTestParticle> {};

void DarkPhotonAnaC::RunEventLoop(TTree* tree)
{
  //
  // This function runs an event loop on input TTree and attempts to read MinaTestEvent data product
  //

  std::cout.precision(4);
  std::cout << "In event loop" << std::endl;
 
  // Step 1) check if MinaTestEvent branch exists
  if(!(tree->GetBranch("Toy_event_branch"))) {

    std::cerr
      << "\033[93m" 
      << "Input TTree has no branch called \"Toy_event_branch\"!" 
      << "\033[00m" << std::endl;
    return;
  }
  
  // Step 2) add a handle to read-out data
  MinaTestEvent* mina_test_event = new MinaTestEvent;
  tree->SetBranchAddress("Toy_event_branch",&mina_test_event);
 
  // Definition of output TTree!
  TFile* fout = TFile::Open("MCC5Analyzed_BNB_Cosmics_v03_143_APS_Cuts_Dist_03cm_N.root", "RECREATE");
  //TH1D* fPDGCodeHist = new TH1D("pdgcodes",";PDG Code;", 5000, -2500, 2500);
  //Histograms for ALL particles in the events we're looking at.
  TH1D* fPhotonCountHist = new TH1D("fphotoncount",";Number of Photons;", 50, 0, 50);
  TH1D* fElectronCountHist = new TH1D("felectroncount", ";Number of Electrons;", 10, 0, 10);
  TH1D* fEnergyHist = new TH1D("fphotonenergy",";Photon Energy (MeV);",1000,0,1000);
  TH1D* fMultiPhotonHist = new TH1D("fphotongroup","Number of Photons in Area Groups", 50, 0, 50);
  TH1D* fPhotonDistHist = new TH1D("fphotondist",";Distances between Photons (cm);",5000,0,500);
  //TH1D* fPhoton_ElectronHist = new TH1D("fphotonsWelectron","# of Photons with One Electron", 50, 0, 50);
  TH1D* fPhotonMotherHist = new TH1D("fphotonmotherTID",";TrackID of Photon Mother;",500,0,500);
  TH1D* fMotherPDGHist = new TH1D("fphotonmotherPDG",";PDG of Photon Mother;",5000, -2500, 2500);
  TH1D* fTrackLengthHist = new TH1D("fphotontracklength",";Photon Track Length (cm);", 500, 0, 500);

  //Histogram for different cases.
  TH1D* fCaseHist = new TH1D("fCaseHist",";Number of Different Cases;",12,0,6);

  //Histograms made for the different cases
  //CASE A: 3 or more photons with at least one photon being primary
  TH1D* A_Dist = new TH1D("Adist","All Photon Distance (cm) CASE A", 5000,0,500);
  TH1D* A_MPDG = new TH1D("AmotherPDG","All Photon Mother PDG CASE A", 5000, -2500, 2500);
  TH1D* A_Energy = new TH1D("Aenergy", "All Photon Energy (MeV) CASE A", 1000, 0, 1000);
  TH1D* A_Count = new TH1D("Acount", "Total Photons in Event CASE A", 50, 0, 50);
  TH1D* A_Primary = new TH1D("Aprimary", "Number of Primary Photons CASE A", 50, 0, 50);

  //CASE B: Number of primary photons with Pi0 as Mother
  //This is the case that we used for the APS
  
  TH1D* B_Dist_Total = new TH1D("BdistTotal","All Photon Distance (cm) CASE B", 5000,0,500);
  TH1D* B_Dist_Pi0Photons = new TH1D("BdistPi0Photons","Photon with Pi0 as Mother Distance (cm) CASE B", 5000,0,500);
  TH1D* B_Dist_OtherPhotons = new TH1D("BdistOtherPhotons","Other Photon Distance (cm) CASE B", 5000,0,500);
  TH1D* B_MPDG = new TH1D("BmotherPDG","Photon Mother PDG CASE B", 5000, -2500, 2500);
  TH1D* B_Energy_Pi0Photons = new TH1D("BenergyPi0Photons", "Photon Energy (MeV) with Pi0 as Mother CASE B", 1000, 0, 1000);
  TH1D* B_Energy_OtherPhotons = new TH1D("BenergyOtherPhotons", "Other Photon Energy (MeV) CASE B", 1000, 0, 1000);
  TH1D* B_Count = new TH1D("Bcount", "Total Photons CASE B", 50, 0, 50);
  TH1D* B_pi0 = new TH1D("Bpi0", "Number of Photons with Pi0 as Mother CASE B", 50, 0, 50);

  TH1D* C_Dist = new TH1D("Cdist","Photon Distance (cm) CASE C", 5000,0,500);
  TH1D* C_MPDG = new TH1D("CmotherPDG","Photon Mother PDG CASE C", 5000, -2500, 2500);
  TH1D* C_Energy = new TH1D("Cenergy", "Photon Energy (MeV) CASE C", 1000, 0, 1000);
  TH1D* C_Count = new TH1D("Ccount", "Total Photons CASE C", 50, 0, 50);

  TH1D* N_Dist = new TH1D("Ndist","Pure Nuclear Scattering Photon Distance (cm)", 5000,0,500);
  TH1D* N_MPDG = new TH1D("NmotherPDG","Pure Nuclear Scattering Photon Mother PDG", 5000, -2500, 2500);
  TH1D* N_Energy = new TH1D("Nenergy", "Pure Nuclear Scattering Photon Energy (MeV)", 1000, 0, 1000);
  TH1D* N_Count = new TH1D("Ncount", "Total Photons in Pure Nuclear Scattering Events", 50, 0, 50);
  
  //CASE D: Dalitz Decay
  TH1D* D_Energy = new TH1D("DmotherPi0Energy","Pi0 Energy in Dalitz Decay Events (MeV)", 1000, 0, 1000);
  TH1D* D_Count = new TH1D("Dpi0Count", "Number of Pi0 in Dalitz Decay Events", 50, 0, 50);


  // Step 3) start event loop

  int ThreeOrMore = 0;
  int ExactlyThree = 0;
  int ThreePrimary = 0;
  int EnergyPiCut = 0;
  int EnergyPiCut3 = 0;
  int EnergyNCut = 0;


  //KLUDGE FOR MAKING ENERGY / DISTANCE CUTS

  std::array<int, 23> Cuts = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 5000};
  std::array<int, 23> Pi0EventsAboveCut;
  std::array<int, 23> Pi0EventsAboveCut_TwoPi0;

  //  std::array<int, 7> Dist_Cuts = {1, 2, 5, 10, 50, 100, 1000};
  //  std::array<int, 7> Pi0EventsBelowDistCut;
  int Pi0EventsBelowDistCut = 0;
  double Dist_Cut = 0.3;

  for ( int i = 0; i < Cuts.size(); i = i + 1) {
      Pi0EventsAboveCut[i] = 0;
      Pi0EventsAboveCut_TwoPi0[i] = 0;
    }

  //  for ( int i = 0; i < Dist_Cuts.size(); i = i + 1) {
  //      Pi0EventsBelowDistCut[i] = 0;
  //    }

  //END KLUDGE
  
  int TotalEvents = 0;
  int ThreeWithTwo = 0; //Number of events with >= 3 photons, >=2 from the SAME Pi0
  int NoPi0Mother = 0; //Number of events with No Pi0 AS A MOTHER
  int NoPi0 = 0; //Number of events with No Pi0 AT ALL

  int ThreeShowers = 0; //Number of events with >= 3 SHOWERS of either photons or electrons
  int ThreeShowersPi0 = 0; //Number of events with >= 3 showers from Pi0
  int ThreeShowersNoPi0 = 0; //Number of events with >= showers and NO Pi0

  for(size_t i=0; i<tree->GetEntries(); ++i) {

    //std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    //std::cout << "TTree entry: " << i << std::endl;
    tree->GetEntry(i);

    //std::cout << "  Found " << mina_test_event->size() << " particles!" << std::endl;
    //std::cout << "  Listing PDG ID of particles..." << std::flush;

    //std::cout << " " << std::endl;
    
    int photon_count = 0;
    int e_count = 0;
    int e_pi0_mother_count = 0;
    int pos_count = 0;
    int pos_pi0_mother_count = 0;
    int primary_count = 0;
    int pi0_mother_count = 0;
    int non_nuclear_count = 0;
    int energy_pi_count = 0;
    int energy_n_count = 0;
    int pi0_count = 0;

    std::array<int, 23> photons_above_cut;
    std::array<int, 23> photons_above_cut_Pi0;
    //std::array<int, 7> photons_above_dist_cut;

    for ( int i = 0; i < photons_above_cut.size(); i = i + 1) {
      photons_above_cut[i] = 0;
      photons_above_cut_Pi0[i] = 0;
    }

    //for ( int i = 0; i < photons_above_dist_cut.size(); i = i + 1) {
    //  photons_above_dist_cut[i] = 0;
    //}

    //std::cout << "New Loop" << std::endl;

    std::vector<MinaTestParticle> Pho_;
    Pho_.clear();
    std::vector<int> MotherTID_;
    
    MotherTID_.clear();

    for(auto const& mina_test_particle : *mina_test_event) {
      
//      std::cout << mina_test_particle.fPDG() << " ";
      if (mina_test_particle.fPDG() == 22 && mina_test_particle.fEnergy() >= 5) { 
	++photon_count; //Count the number of photons in the event
	fEnergyHist->Fill(mina_test_particle.fEnergy());
//	std::cout << "Photon Track ID: " << mina_test_particle.fTrackId() << std::endl;
//	std::cout << "Photon Energy (MeV): " << std::fixed << mina_test_particle.fEnergy() << std::endl;
//	std::cout << 3.14159 << std::endl;
//	std::cout << "Photon Mother Track ID: " << mina_test_particle.fMotherTID() << std::endl;
//	std::cout << "Photon Mother PDG: " << mina_test_particle.fMotherPDG() << std::endl;
//	std::cout << "Photon Initial Position X: " << mina_test_particle.fStartXYZT()[0] << std::endl;
	fMotherPDGHist->Fill(mina_test_particle.fMotherPDG());
	fPhotonMotherHist->Fill(mina_test_particle.fMotherTID());
	fTrackLengthHist->Fill(mina_test_particle.fTrackLength());
	Pho_.push_back(mina_test_particle);
	if (mina_test_particle.fMotherPDG() == 111) 
	  ++pi0_mother_count;

	//KLUDGE: ALSO ACCOUNT FOR BEAM "PRIMARIES" WITH PHOTONS NOT FROM PRIMARY COSMIC PARTICLE OR FROM NEUTRINO-NUCLEUS INTERACTION
	if (mina_test_particle.fMotherPDG() == 0)
	  ++primary_count;
	//if (mina_test_particle.fMotherPDG() 
	//END KLUDGE
	if (mina_test_particle.fMotherPDG() == 22){
	  //std::cout << "!!!!!!!!FOUND PHOTON WITH PHOTON AS MOTHER!!!!!!!!" << std::endl;
	  //std::cout << "Particle Track ID: " << mina_test_particle.fTrackId() << std::endl;
	  //std::cout << "Particle Mother Track ID: " << mina_test_particle.fMotherTID() << std::endl;
	}
	if (mina_test_particle.fMotherPDG() != 2112 
	    && mina_test_particle.fMotherPDG() != 2212 
	    && mina_test_particle.fMotherPDG() != 13 
	    && mina_test_particle.fMotherPDG() != 211
	    && mina_test_particle.fMotherPDG() != -211)
	  ++non_nuclear_count;
      }
      if (mina_test_particle.fPDG() == 11) {
	++e_count;
	if (mina_test_particle.fMotherPDG() == 111){
	  ++e_pi0_mother_count;
	  MotherTID_.push_back(mina_test_particle.fMotherTID());
	}
	
      }
      if (mina_test_particle.fPDG() == -11){
	++pos_count;
	if(mina_test_particle.fMotherPDG() == 111){
	  ++pos_pi0_mother_count;
	  MotherTID_.push_back(mina_test_particle.fMotherTID());
	}
      }
      if (mina_test_particle.fPDG() == 111)
	++pi0_count;
    }

//    std::cout << "photon count" << photon_count << std::endl;
//    std::cout << "electron count" << e_count << std::endl;

    //SORT BASED ON THE THREE CASES, A, B, and C. 
    //Fill all the histograms except the distance ones (which will be filled later)
    //CASE A: 3 or more photons, with one or more of the photons as primary
    bool filled = false;
    if (photon_count >= 3 && primary_count != 0 && pi0_mother_count == 0){
      fCaseHist->Fill(1);
      filled = true;
      A_Primary->Fill(primary_count);
      A_Count->Fill(photon_count);
      for (auto const& A_particle : *mina_test_event){
	if (A_particle.fPDG() == 22){
	  A_MPDG->Fill(A_particle.fMotherPDG());
	  A_Energy->Fill(A_particle.fEnergy());
	}
      }
    }
    ///USED TO HAVE primary_count == 0
    if (photon_count >= 3 && pi0_mother_count >= 2){ // && primary_count == 0){
      std::cout << "NEW EVENT" << std::endl;
      fCaseHist->Fill(2);
      filled = true;
      B_Count->Fill(photon_count);
      B_pi0->Fill(pi0_mother_count);
      for (auto const& B_particle : *mina_test_event){
	if (B_particle.fPDG() == 22){
	  B_MPDG->Fill(B_particle.fMotherPDG());
	  if (B_particle.fEnergy() >= 10)
	    ++energy_pi_count;
	  for (int i = 0; i < Cuts.size(); i = i + 1){
	      if (B_particle.fEnergy() >= Cuts[i]){
		//std::cout << "Photon Energy " << B_particle.fEnergy() << std::endl;
		//std::cout << "Energy Cut " << Cuts[i] << std::endl;
		photons_above_cut[i] = photons_above_cut[i] + 1;
	      }
	      //std::cout << "Photons above cut: " << photons_above_cut[i] << std::endl;
	    }
	  if (B_particle.fMotherPDG() == 111) {//ONLY includes energy and number of particles with pi0 mother
	    B_Energy_Pi0Photons->Fill(B_particle.fEnergy());
	    for (int i = 0; i < Cuts.size(); i = i +1){
	      if (B_particle.fEnergy() >= Cuts[i]){
	    	photons_above_cut_Pi0[i] = photons_above_cut_Pi0[i] + 1;
	    	std::cout << "In photon cut loop" << std::endl;
	      }
	    }
	    //std::cout << "New Iteration" << std::endl;
	  }
	  else 
	    B_Energy_OtherPhotons->Fill(B_particle.fEnergy());
	}
      }
    }
    if (e_count == 1){
//      fCaseHist->Fill(3);
//      filled = true;
      C_Count->Fill(photon_count);
      for (auto const& C_particle : *mina_test_event){
	if (C_particle.fPDG() == 22){
	  C_MPDG->Fill(C_particle.fMotherPDG());
	  C_Energy->Fill(C_particle.fEnergy());
	}
      }
    }
    //CASE N: PURE NUCLEAR SCATTERING.
    if (photon_count >= 3 && pi0_mother_count == 0 && non_nuclear_count == 0){
      fCaseHist->Fill(4);
      filled = true;
      N_Count->Fill(photon_count);
      for (auto const& N_particle : *mina_test_event){
	if (N_particle.fPDG() == 22){
	  N_MPDG->Fill(N_particle.fMotherPDG());
	  N_Energy->Fill(N_particle.fEnergy());
	  if (N_particle.fEnergy() >= 10)
	    ++energy_n_count;
	}
      }
    }
    //CASE D: DALITZ DECAY WITH GAMMA, e+, AND e-
    if (photon_count >= 3 && pi0_mother_count >= 1 && e_pi0_mother_count >= 1 && pos_pi0_mother_count >= 1){
      fCaseHist->Fill(5);
      //std::cout << "FOUND POSSIBLE DALITZ DECAY" << std::cout;
      //std::cout << "================================================" << std::endl;
      //      filled = true;
      int D_pi0_count = 0;
      for (auto const& D_particle: *mina_test_event){
	if (D_particle.fPDG() == 111){
	  ++D_pi0_count;
	  //std::cout << "FOUND POSSIBLE DALITZ DECAY PI0" << std::endl;
	  //std::cout << "====================================================" << std::endl;
	  //std::cout << D_particle.fEnergy() << std::endl;
	  D_Energy->Fill(D_particle.fEnergy());
	}
      }
      D_Count->Fill(D_pi0_count);
    }
    //CASE D2: DALITZ DECAY WITH TWO GAMMA
    if (photon_count >=3 && pi0_mother_count >= 2){
      ////
      int TwoDaughters = 0;
      for(std::vector<MinaTestParticle>::iterator p1 = Pho_.begin(); p1 != Pho_.end()-1; ++p1) {
	//loop over all but the last particle in the loop
	
	if (p1 == Pho_.end()-1){
	  break;
	}
	
	for(std::vector<MinaTestParticle>::iterator p2 = p1+1; p2 != Pho_.end(); ++p2) {
	    if( ((*p1).fMotherTID() == (*p2).fMotherTID()) && ((*p2).fMotherPDG() == 111)){
	      bool ThirdDaughter = false;
	      for (std::vector<MinaTestParticle>::iterator p3 = p2+1; p3 != Pho_.end(); ++p3){
		if ( (*p3).fMotherTID() == (*p2).fMotherTID())
		  ThirdDaughter = true;
	      }
	      if (!ThirdDaughter)
		++TwoDaughters;
	    }
	      
	}
      }
      ////      
      if (TwoDaughters > 0){
	fCaseHist->Fill(5.5);
	//std::cout << "FOUND POSSIBLE DALITZ DECAY TYPE 2" << std::cout;
	//std::cout << "================================================" << std::endl;
      }
    }

    if (filled == false && photon_count < 3)
      fCaseHist->Fill(0);
    if (filled == false && photon_count >= 3)
      fCaseHist->Fill(0.5);
    

    if (photon_count >= 3)
      ++ThreeOrMore;
    if (photon_count == 3)
      ++ExactlyThree;
    if (primary_count == 3)
      ++ThreePrimary;
    if (energy_pi_count >= 3)
      ++EnergyPiCut;
    if (energy_pi_count == 3)
      ++EnergyPiCut3;
    if (energy_n_count >= 3)
      ++EnergyNCut;

    //LOOP FOR ENERGY CUT
    if (photon_count >= 3 && pi0_mother_count >= 2){
      for (int i = 0; i < Cuts.size(); i = i+1){
	if (photons_above_cut[i] >= 3)
	  Pi0EventsAboveCut[i] = Pi0EventsAboveCut[i] + 1;
	if (photons_above_cut[i] >= 3 && photons_above_cut_Pi0[i] >= 2)
	  Pi0EventsAboveCut_TwoPi0[i] = Pi0EventsAboveCut_TwoPi0[i] + 1;
      }
    }
    //END LOOP FOR ENERGY CUT

    ++TotalEvents;

    bool SamePhotonMotherPi0 = false;
    bool three_showers_pi0_present = false;
    for(std::vector<MinaTestParticle>::iterator p1 = Pho_.begin(); p1 != Pho_.end()-1; ++p1) {
      //loop over all but the last particle in the loop
      int TotalDaughters = 0;

      if (p1 == Pho_.end()-1){
	break;
      }

      for(int a : MotherTID_) {
	    if (a == (*p1).fMotherTID())
	      ++TotalDaughters;
      }
      
      for(std::vector<MinaTestParticle>::iterator p2 = p1+1; p2 != Pho_.end(); ++p2) {
	if( (*p1).fMotherTID() == (*p2).fMotherTID() && (*p2).fMotherPDG() == 111){
	    SamePhotonMotherPi0 = true;
	    ++TotalDaughters;
	}
	
      }
      if (TotalDaughters >= 3)
	three_showers_pi0_present = true;
    }
    
    if (SamePhotonMotherPi0 == true && photon_count >= 3 && pi0_mother_count >= 2)
      ++ThreeWithTwo;
    if (pi0_mother_count == 0 && photon_count >= 3)
      ++NoPi0Mother;
    if (pi0_count == 0)
      ++NoPi0;
    if (photon_count + e_count + pos_count >= 3)
      ++ThreeShowers;
    if (three_showers_pi0_present == true)
      ++ThreeShowersPi0;
    if ((photon_count + e_count + pos_count >= 3) && (pi0_mother_count == 0) && (e_pi0_mother_count == 0) && (pos_pi0_mother_count == 0))
      ++ThreeShowersNoPi0;


    fPhotonCountHist->Fill(photon_count);
    fElectronCountHist->Fill(e_count);

    //if (e_count == 1)
    //fPhoton_ElectronHist->Fill(photon_count);
   
    std::vector<PhotonPair> Distance_;
    Distance_.clear();
    
    //kludgey initialization of TempPair
    PhotonPair TempPair;
    TempPair.dist = 0.;
    TempPair.part1.clear();
    TempPair.part2.clear();

    //Assign the distances between particles, if they're close enough 
    //This makes Distance_ an ORDERED list of pairs. (lower, higher)

    LineDist Dist;

    //    std::cout << "size Pho_ " << Pho_.size() << std::endl;

    if (!Pho_.empty()){
      for(std::vector<MinaTestParticle>::iterator p1 = Pho_.begin(); p1 != Pho_.end()-1; ++p1) {
	//loop over all but the last particle in the loop
	
	if (p1 == Pho_.end()-1){
	  break;
	}
	
	for(std::vector<MinaTestParticle>::iterator p2 = p1+1; p2 != Pho_.end(); ++p2) {
	  fPhotonDistHist->Fill(Dist.Calc(*p1,*p2));
	  //write to distance histograms for particles in certain events
	  if (photon_count >= 3 && primary_count != 0)
	    A_Dist->Fill(Dist.Calc(*p1,*p2));
	  if (photon_count >= 3 && pi0_mother_count >= 2){
	    B_Dist_Total->Fill(Dist.Calc(*p1,*p2));

	    //DISTANCE CUTS APPLIED HERE
	    //	    for (int i = 0; i < Dist_Cuts.size(); i = i + 1){
	    //	      if (Dist.Calc(*p1,*p2) > Dist_Cuts[i]){
	    //		//std::cout << "Photon Dist " << Dist.Calc(*p1,*p2) << std::endl;
	    //		//std::cout << "Dist Cut " << Dist_Cuts[i] << std::endl;
	    //		photons_above_dist_cut[i] = 1;
	    //	      }
	    //	      //std::cout << "Photons above cut: " << photons_above_dist_cut[i] << std::endl;
	    //	    }
	    //END APPLICATION OF DISTANCE CUTS  

	    if ((*p1).fMotherPDG() == 111 && (*p2).fMotherPDG() == 111){
	      B_Dist_Pi0Photons->Fill(Dist.Calc(*p1,*p2));
	      //std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	      //std::cout << "Writing Distance between Pi0 Photons " << Dist.Calc(*p1,*p2) << std::endl;
	      //std::cout << "Photon 1 Location: " <<  (*p1).fEndXYZT()[0] << " " <<  (*p1).fEndXYZT()[1] << " " <<  (*p1).fEndXYZT()[2] << std::endl;
	      //std::cout << "Photon 2 Location: " <<  (*p2).fEndXYZT()[0] << " " <<  (*p2).fEndXYZT()[1] << " " <<  (*p2).fEndXYZT()[2] << std::endl;
	    }
	    else if ((*p1).fMotherPDG() != 111 && (*p2).fMotherPDG() != 111)
	      B_Dist_OtherPhotons->Fill(Dist.Calc(*p1,*p2));
	  }
	  if (photon_count >=3 && primary_count == 0 && pi0_mother_count == 0 && non_nuclear_count == 0)
	    N_Dist->Fill(Dist.Calc(*p1,*p2));
	  if (e_count == 1)
	    C_Dist->Fill(Dist.Calc(*p1,*p2));
	  //end writing to histograms for particles in certain types of events
	  //std::cout << "DISTANCE BETWEEN PHOTONS: " << Dist.Calc(*p1,*p2) << std::endl;
	  if (Dist.Calc(*p1,*p2) <= Dist_Cut){
	    TempPair.dist = Dist.Calc(*p1,*p2);
	    TempPair.part1 = *p1;
	    TempPair.part2 = *p2;
	    Distance_.push_back(TempPair);
	  }
	}
	
	
      }
    } //end of if !Pho_.empty()

//    std::cout << "Size of Distance_" << Distance_.size() << std::endl;
			      

    //Merge the relevant distances into retraceable groups
    //Again a kludgey clearing.  
    std::vector<std::vector<MinaTestParticle> > Pgroups_;
    Pgroups_.clear();

    if (!Distance_.empty()){

      for(std::vector<PhotonPair>::iterator pair1 = Distance_.begin(); pair1 != Distance_.end()-1; ++pair1 ) {
	
	//	if (Distance_.size() < 20)
	  //std::cout << "In pair 1 loop" << std::endl;
	//If pair1 is already in a group, continue (we have already picked it up below)
	if (!Pgroups_.empty()){
	  bool found1 = false;
	  for (std::vector<MinaTestParticle>  const& g : Pgroups_){
	    if (found1 == true)
	      break;
	    for (MinaTestParticle const& part : g){
	      if ((*pair1).part1.fTrackId() == part.fTrackId() || (*pair1).part2.fTrackId() == part.fTrackId()){
		found1 = true;
		break;
	      }
	    }
	  }      
	  if (found1 == true)     
	    continue; //Continue the OUTER loop
	}
	
	  
	if (pair1 != Distance_.end()-1){
	//Loop over all of the other pairs
	  for(std::vector<PhotonPair>::iterator pair2 = pair1+1; pair2 != Distance_.end(); ++pair2){

//	    if (Distance_.size() < 20) {
//	      std::cout << "In pair 2 loop" << std::endl;
//	      std::cout << "Pair 1: " << (*pair1).part1.fTrackId() << " " << (*pair1).part2.fTrackId() << std::endl;
//	      std::cout << "Pair 2: " << (*pair2).part1.fTrackId() << " " << (*pair2).part2.fTrackId() << std::endl;
//	    }
	    
	  
	  //first check whether any groups already exist; if not, make the first one where relevant.
	    if (Pgroups_.empty()){
//	      std::cout << "EMPTY" << std::endl;
	      if ( (*pair1).part1.fTrackId() == (*pair2).part1.fTrackId() || (*pair1).part2.fTrackId() == (*pair2).part1.fTrackId() ) {
		std::vector<MinaTestParticle> group = {(*pair1).part1, (*pair1).part2, (*pair2).part2};
		Pgroups_.push_back(group);
//		std::cout << "Creating group" << std::endl;
	      }
	      //the first of these cases should never happen due to ordering; maybe check at some point
	      else if ((*pair1).part1.fTrackId() == (*pair2).part2.fTrackId() || (*pair1).part2.fTrackId() == (*pair2).part2.fTrackId() ) {
		std::vector<MinaTestParticle> group = {(*pair1).part1, (*pair1).part2, (*pair2).part1};
		Pgroups_.push_back(group);
//		std::cout << "Creating group" << std::endl;
	      }
	    }
	  
	  //If groups already exist, merge the pair into an existing group where relevant
	    else {
	      bool found2 = false;
//	      if (Distance_.size() < 20){
//		std::cout << "In OUTER else loop" << std::endl;
//		std::cout << "PGROUP SIZE " << Pgroups_.size() << std::endl;
//	      }
	      for (std::vector<MinaTestParticle>  &g : Pgroups_){
		if (found2 == true)
		  break;
//		if (Distance_.size() < 20)
//		  std::cout << "In inner else loop, size g: " << g.size() << std::endl;			  
		for (MinaTestParticle const &part : g){
		  if ((*pair2).part1.fTrackId() == part.fTrackId()){
		    bool p2found = false;
		    //std::cout << "Particle ID to match " << part.fTrackId() << std::endl;
		    for (MinaTestParticle const &p : g){
		      if ((*pair2).part2.fTrackId() == p.fTrackId())
			p2found = true;
		    }
		    if (!p2found){
		      g.push_back((*pair2).part2);
//		      std::cout << "Adding particle ID " << (*pair2).part2.fTrackId() << std::endl;
		    }
		    found2 = true;
		    break;
		  }	
		  else if ((*pair2).part2.fTrackId() == part.fTrackId()){
		    bool p1found = false;
		    for (MinaTestParticle const &p : g){
		      if ((*pair2).part1.fTrackId() == p.fTrackId())
			p1found = true;
		    }
		    if (!p1found){
		      g.push_back((*pair2).part1);
//		      std::cout << "Adding particle ID " << (*pair2).part1.fTrackId() << std::endl;
		    }
		    found2 = true;
		    
		    break;
		  }
		} //End loop over particles in group     

	      } //End loop over groups

	      //CREATE A NEW GROUP IF IT WASN'T FOUND IN AN OLD GROUP
	      if (found2 == false){
		if ( (*pair1).part1.fTrackId() == (*pair2).part1.fTrackId() || (*pair1).part2.fTrackId() == (*pair2).part1.fTrackId() ) {
		  std::vector<MinaTestParticle> group = {(*pair1).part1, (*pair1).part2, (*pair2).part2};
		  Pgroups_.push_back(group);
		  //std::cout << "Creating another group" << std::endl;
		}
		//the first of these cases should never happen due to ordering; maybe check at some point
		else if ((*pair1).part1.fTrackId() == (*pair2).part2.fTrackId() || (*pair1).part2.fTrackId() == (*pair2).part2.fTrackId() ) {
		  std::vector<MinaTestParticle> group = {(*pair1).part1, (*pair1).part2, (*pair2).part1};
		  Pgroups_.push_back(group);
		  //std::cout << "Creating another group" << std::endl;
		}
		
	      }
	      
	    } //End else statment 
	    
	  } //End loop over second pair
	  
	} //End check for whether second pair is empty
	
      } //End loop over all pairs

    } //End check for whether distance is empty

    //std::cout << "Pgroup size" << Pgroups_.size() << std::endl;
    
    //Now analyze each group by mother particle.
    for (std::vector<MinaTestParticle> const& g : Pgroups_){
      //std::cout << "NEW GROUP!!!!!" << std::endl;
      //std::cout << "Total photons in event: " << photon_count << std::endl;
      //std::cout << "Total photons in group: " << g.size() << std::endl;
      fMultiPhotonHist->Fill(g.size());
    }

//    std::cout << std::endl;
//    std::cout << "done with entry " << i << std::endl;
//    std::cout << std::endl;

    int Pi0_daughters = 0; 
    //LOOP FOR DISTANCE CUT
    if (photon_count >= 3 && pi0_mother_count >= 2){
      //      for (int i = 0; i < Dist_Cuts.size(); i = i+1){
      //	if (photons_above_dist_cut[i] == 0)
      //	  Pi0EventsBelowDistCut[i] = Pi0EventsBelowDistCut[i] + 1;
      //      }
      int GroupsWithTwoDaughters = 0;
      for (std::vector<MinaTestParticle> const& g : Pgroups_){
	//std::cout << "NEW GROUP!!!!!" << std::endl;
	//std::cout << "Total photons in event: " << photon_count << std::endl;
	std::cout << "Total photons in group: " << g.size() << std::endl;
	fMultiPhotonHist->Fill(g.size());
	Pi0_daughters = 0;
	for (auto const& group_particle : g){
	  if (group_particle.fMotherPDG() == 111){
	    Pi0_daughters = Pi0_daughters + 1;
	  }
	}
	if (Pi0_daughters >= 2)
	  GroupsWithTwoDaughters = GroupsWithTwoDaughters + 1;
      }
      if (GroupsWithTwoDaughters != 0)
	Pi0EventsBelowDistCut = Pi0EventsBelowDistCut + 1;
    }
    //END LOOP FOR DISTANCE CUT

  } 

  std::cout << "EVENTS with 3 or more photons: " << ThreeOrMore << std::endl;
  std::cout << "EVENTS with exactly 3 photons: " << ExactlyThree << std::endl;
  std::cout << "EVENTS with exactly 3 primary photons: " << ThreePrimary << std::endl;
  std::cout << "Pi0 EVENTS with photon energy over 10 MeV: " << EnergyPiCut << std::endl;
  std::cout << "Pi0 EVENTS with photon energy over 10 MeV AND three photons: " << EnergyPiCut3 << std::endl;
  std::cout << "Nuclear scattering EVENTS with energy over 10 MeV: " << EnergyNCut << std::endl;

  std::cout << "TOTAL EVENTS: " << TotalEvents << std::endl;
  std::cout << "EVENTS with 3 or more photons, at least 2 from the SAME Pi0: " << ThreeWithTwo << std::endl;
  std::cout << "EVENTS with NO Pi0 as Mother: " << NoPi0Mother << std::endl;
  std::cout << "EVENTS with NO Pi0 AT ALL: " << NoPi0 << std::endl;
  std::cout << "EVENTS with 3 or more SHOWERS (photons, electrons, positrons): " << ThreeShowers << std::endl;
  std::cout << "EVENTS with 3 or more SHOWERS from Pi0: " << ThreeShowersPi0 << std::endl;
  std::cout << "EVENTS with 3 or more SHOWERS, NO Pi0: " << ThreeShowersNoPi0 << std::endl;

  for (int i = 0; i < Cuts.size(); i = i+1){
    std::cout << "Energy Cut: " << Cuts[i] << " MeV" << std::endl;
    std::cout << "Number of Pi0 Events: " << Pi0EventsAboveCut[i] << std::endl;
    std::cout << "Number of Pi0 Events with two Pi0 photons: " <<  Pi0EventsAboveCut_TwoPi0[i] << std::endl;
  }

  std::cout << "Distance Cut: " << Dist_Cut << " cm" << std::endl;
  std::cout << "Number of Pi0 Events Below Cut: " << Pi0EventsBelowDistCut << std::endl;

  //  for (int i = 0; i < Dist_Cuts.size(); i = i+1){
  //  std::cout << "Distance Cut: " << Dist_Cuts[i] << " cm" << std::endl;
  //  std::cout << "Number of Pi0 Events: " << Pi0EventsBelowDistCut[i] << std::endl;
  //  }
  
  //std::cout << "Check 3" << std::endl;
  fPhotonCountHist->Write();
  fElectronCountHist->Write(); 
  fEnergyHist->Write();
  fMultiPhotonHist->Write();
  fPhotonDistHist->Write();
  //fPhoton_ElectronHist->Write();
  fPhotonMotherHist->Write();
  fTrackLengthHist->Write();
  fMotherPDGHist->Write();
  fCaseHist->Write();

  A_Dist->Write();
  A_MPDG->Write();
  A_Energy->Write();
  A_Count->Write();
  A_Primary->Write();

  B_Dist_Total->Write();
  B_Dist_Pi0Photons->Write();
  B_Dist_OtherPhotons->Write();
  B_MPDG->Write();
  B_Energy_Pi0Photons->Write();
  B_Energy_OtherPhotons->Write();
  B_Count->Write();
  B_pi0->Write();

  C_Dist->Write();
  C_MPDG->Write();
  C_Energy->Write();
  C_Count->Write();

  N_Dist->Write();
  N_MPDG->Write();
  N_Energy->Write();
  N_Count->Write();

  D_Energy->Write();
  D_Count->Write();

  fout->Close();
  
}


#endif
