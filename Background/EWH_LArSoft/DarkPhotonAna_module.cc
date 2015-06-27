////////////////////////////////////////////////////////////////////////
// Class:       DarkPhotonAna
// Module Type: analyzer
// File:        DarkPhotonAna_module.cc
//
// Generated at Thu Jul 10 11:49:46 2014 by Elizabeth Himwich using artmod
// from cetpkgsupport v1_05_04.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"

// ART includes

#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Optional/TFileService.h"

// C++ Includes
#include <cmath>
#include <iostream>
#include <vector>

// LArSoft Includes
#include "SimulationBase/MCParticle.h"
#include "Geometry/Geometry.h"
#include "SimpleTypesAndConstants/geo_types.h"
#include "SummaryData/POTSummary.h"

// ROOT includes
#include "TTree.h"
#include "TStopwatch.h"

// I include
#include "MinaTestPhoton.hh"
#include "MinaTestParticle.hh"
#include "MinaTestEvent.hh"

struct PhotonTime{
  
  int TrackID;
  double Time;

};

class DarkPhotonAna;

class DarkPhotonAna : public art::EDAnalyzer {
public:

  //Constructor
  explicit DarkPhotonAna(fhicl::ParameterSet const & p);

  //Destuctor
  virtual ~DarkPhotonAna();

  // Analyze function, executed for every event (range-based for loop)
  void analyze(art::Event const & e) override;

  // Begin job, executed at beginning of job
  void beginJob();

  //Begin sub run, executed at the beginning of the subRun??
  void beginSubRun(const art::SubRun&);

private:

  //TTree pointer...
  TTree* _outTree;
  TTree* _outTreePOT;

  // Data product to save event-wise data
  MinaTestEvent Evt;

  // Variables for exclusion
  double detHeight;
  double detWidth;
  double detectorLength;

  /// LArG4 producer process name
  std::string _g4_module_label;

  //Protons on target information (added 09/2014)
  Double_t pot;
  std::string _POT_module_label;

  //STOPWATCH
  TStopwatch stopwatch;

};


DarkPhotonAna::DarkPhotonAna(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p)  // ,
{
  _outTree = nullptr;
  _g4_module_label = p.get<std::string>("G4ModuleLabel");
  _POT_module_label = p.get<std::string>("POTModuleLabel"); // 09/2014

 // More initializers here.
}

DarkPhotonAna::~DarkPhotonAna()
{
  // Clean up dynamic memory and other resources here.
}


void DarkPhotonAna::beginJob()
{
  //Create TTree
  art::ServiceHandle<art::TFileService> tfs;
  art::ServiceHandle<geo::Geometry> fGeometry;
  
  _outTree = tfs->make<TTree>("Toy_tree","");
  _outTreePOT = tfs->make<TTree>("Toy_POT_tree","");

  // Attach MinaTest
  _outTree->Branch("Toy_event_branch", "MinaTestEvent",&Evt);
  _outTreePOT->Branch("Toy_POT_branch", &pot, "pot/D");

  // Get geometry properties
  detectorLength = fGeometry->DetLength(); 
  detWidth  = fGeometry->DetHalfWidth()  * 2.;
  detHeight = fGeometry->DetHalfHeight() * 2.;

  //std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;
  //std::cout << fGeometry->GDMLFile() << std::endl;

}

void DarkPhotonAna::beginSubRun(const art::SubRun &sr){

  art::Handle< sumdata::POTSummary > potListHandle;

  if(sr.getByLabel(_POT_module_label,potListHandle))
    pot=potListHandle->totpot;
  else 
    pot=0.;
  
  _outTreePOT->Fill();
}

void DarkPhotonAna::analyze(art::Event const & e)
{ 
  stopwatch.Start();
  
  
  
  //std::cout << "ANALYSIS LOOP!!" << std::endl;
  // Access Data
  art::Handle<std::vector<simb::MCParticle> > partArray;
  e.getByLabel(_g4_module_label,partArray);

    // Check if there is any MCParticle
  if(!partArray.isValid()) {

    std::cerr << "\033[93m" << "Did not find any MCParticle! Skipping..." << "\033[00m" << std::endl;
    return;

  }

  //Initialize MinaTest event
  Evt.clear();

  // Set event number
  Evt.SetEvent(e.id().event(),e.run());


  //In this particle loop particles are only excluded for VOLUME and DIRECTION

  
  std::vector<int> excludedTrackID_;
  std::vector<PhotonTime> includedPhoton_;


  for ( auto const& particle : *partArray )
    {
      
      //std::cout << "MeV >= 10" << std::endl;
      bool exclude = false;
      double magnitude = std::sqrt(std::pow(particle.Momentum(0)[0],2.) + std::pow(particle.Momentum(0)[1],2.) + std::pow(particle.Momentum(0)[2],2.));
      
      //Exclude particles pointed outside the detector
      if ( particle.Position(0)[0] <= (20.) )
	{
	  double theta = std::acos(particle.Momentum(0)[0]/magnitude);
	  if ( theta >= 3.1415927*(3/4) )
	    exclude = true;
	}
      else if ( particle.Position(0)[0] >= (detWidth -20.) )
	{
	  double theta = std::acos(particle.Momentum(0)[0]/magnitude);
	  if ( theta <= 3.1415927*(1/4) )
	    exclude = true;
	} 
      
      //Exclude in the z direction
      if ( particle.Position(0)[2] <= (20.) )
	{
	  double theta = std::acos(particle.Momentum(0)[2]/magnitude);
	  if ( theta >= 3.1415927*(3/4) )
	    exclude = true;
	}
      else if ( particle.Position(0)[2] >= (detWidth -20.) )
	{
	  double theta = std::acos(particle.Momentum(0)[2]/magnitude);
	  if ( theta <= 3.1415927*(1/4) )
	    exclude = true;
	} 
      
      //Exclude in the y direction
      if ( particle.Position(0)[1] <= (-(detHeight/2.) + 10.) )
	{
	  double theta = std::acos(particle.Momentum(0)[1]/magnitude);
	  if ( theta >= 3.1415927*(3/4) )
	    exclude = true;
	}
      else if ( particle.Position(0)[1] >= (detHeight/2. -10.) )
	{
	  double theta = std::acos(particle.Momentum(0)[1]/magnitude);
	  if ( theta <= 3.1415927*(1/4) )
	    exclude = true;
	} 
      
      if (particle.Position(0)[0] >= detWidth && std::abs(particle.Position(0)[1]) >= detHeight/2.
	  && particle.Position(0)[2] >= detectorLength)
	exclude = true;
      
	//      //std::cout << fPDG << " " << fSelectedPDG << std::endl;
	//      if (particle.PdgCode() == 22  && exclude == false)
	//	{
	//	  //std::cout << "Found Photon!" << std::endl;
	//	  //std::cout << "Event: " << e.id().event() << std::endl;
//	  int i;
//	  //std::cout << "Position and Momentum" << std:: endl;
//	  for (i = 0; i <= 2; ++i)
//	    {
//	      //std::cout << " " << particle.Position(0)[i] << std::endl;
//	      //std::cout << " " << particle.Momentum(0)[i] << std::endl;
//	    }
//	}
      if (exclude == true) //&& it's outside the range
	excludedTrackID_.push_back(particle.TrackId()); //then it should be excluded.
      
    } //end particle loop (exclusion)
  

  // ANALYSIS LOOP ONCE PARTICLES ARE EXCLUDED
  for (auto const& part : *partArray) {
    
    MinaTestPhoton Pho_;
    Pho_.clear();
    
    
    //decide whether particle is included or excluded
    bool exclude = false;
    for (std::vector<int>::iterator i = excludedTrackID_.begin(); i != excludedTrackID_.end(); ++i)
      {
	if (part.TrackId() == *i)
	  exclude = true;
      }
    
    //
    for (std::vector<PhotonTime>::iterator i = includedPhoton_.begin(); i != includedPhoton_.end(); ++i)
      {
	if (part.TrackId() == (*i).TrackID)
	  std::cout << "Found duplicate Track ID!!!!!" << std::endl;
	if (part.TrackId() == (*i).TrackID && part.Position(0)[3] > (*i).Time){
	  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	  std::cout << "Excluded particle based on time" << std::endl;
	  exclude = true;
	}
      }
      
    //If it's not excluded, add it to the event
    if (exclude == false)
      {
	
	if (part.PdgCode() == 22)
	  {
	    
	    size_t numberTrajectoryPoints = part.NumberTrajectoryPoints();
	    // For trajectories, as for vectors and arrays, the
	    // first point is #0, not #1.
	    int last = numberTrajectoryPoints - 1;
	    
	    std::vector<double> sXYZT = { part.Position(0)[0], part.Position(0)[1], part.Position(0)[2], part.Position(0)[3] };
	    std::vector<double> eXYZT = { part.Position(last)[0], part.Position(last)[1], part.Position(last)[2], part.Position(last)[3] };
	    
	    //Distance added
	    
	    int MotherPDG = 0.;
	    for (auto const& p : *partArray) {
	      if (p.TrackId() == part.Mother())
		MotherPDG = p.PdgCode();
	    }
	    
	    double trackLength = std::sqrt( std::pow(eXYZT[0] - sXYZT[0],2) + std::pow(eXYZT[1] - sXYZT[1],2) + std::pow(eXYZT[2] - sXYZT[2],2) );
	    
	    //std::cout << "PHOTON ENERGY (PRESUMED): " << part.E()*1000 << std::endl;
	    
	    Pho_.SetPhoton(part.E()*1000, sXYZT, eXYZT, part.Mother(), MotherPDG, trackLength);
	    PhotonTime temp;
	    temp.TrackID = part.TrackId();
	    temp.Time = part.Position(0)[3];
	    includedPhoton_.push_back(temp);
	    
	  }
	
	MinaTestParticle tmp;
	tmp.SetParticle(part.TrackId(), part.PdgCode(), Pho_);
	
	Evt.push_back(tmp);
      } // end exclusion loop
    
  } // end particle loop 
    // Fill TTree
  _outTree->Fill();
  
  excludedTrackID_.clear();

  std::cout << "This time is " << stopwatch.RealTime() << std::endl;

  stopwatch.Continue();
  
} //end analyze loop

DEFINE_ART_MODULE(DarkPhotonAna)

