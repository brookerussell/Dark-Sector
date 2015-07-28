// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: SteppingAction.cc,v 1.15 2006/06/29 17:49:13 gunter Exp $
// GEANT4 tag $Name: geant4-08-01-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
//#include "DSParticle.hh"

#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4Step.hh"

#include "G4FieldManager.hh"
#include "G4VProcess.hh"
#include "G4ProcessManager.hh"

//#include "G4RunManager.hh"
//#include "G4DecayTable.hh"
//#include "G4MuonDecayChannelWithSpin.hh"
//#include "G4MuonMinusCaptureAtRest.hh"

#include <iostream>
#include <fstream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DSEvent *aDSEvent)
{
  DSEventData = aDSEvent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Physical numbers to evaluate
G4double PathLengthTPC;
G4double PathLengthActive;
G4double EnergyDepositTPC;
G4double EnergyDepositActive;
G4double HitEnergyTPC;
G4ThreeVector HitMomentumTPC;
G4ThreeVector DecayMomentumTPC;
G4ThreeVector DecayMomentumActive;


G4double DecayEnergyDeposit;
G4double DecayPathLength;
G4double DecayElectEnergy;
G4ThreeVector DecayElectMomentum;

// Counts
//G4int HitNumberTPC = 0;
//G4int HitNumberActive = 0;
//G4int DecayNumberTPC = 0;
//G4int DecayNumberActive = 0;
int EventNumber = 0;
//G4int i=0;
//G4int DecayEventNumber;

// Set Flags
G4int HitFlagActive = false;
G4int DecayFlag =false;
G4int StorageFlag = false;
G4int DecayStoreFlag = false;
G4int DecayWriteFlag = false;

//Names
G4String HitParticleName;
G4String DecayParticleName;
// G4String ProcessName;

// Temporary
G4int DeltaRayID;

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{  

  //std::cout << "In stepping action" << std::endl;

  // Get step information
  int TrackID = aStep->GetTrack()->GetTrackID();
  G4int StepNumber = aStep->GetTrack()->GetCurrentStepNumber();
  G4String StepVolumeName  = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
  G4String VertexVolumeName = aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
  G4String ParticleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
  G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();
  
  //std::cout << "Before ProcessName" << std::endl;

  std::string ProcessName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

  //std::cout << "After ProcessName" << std::endl;
  
  
  if (TrackID == 1 && StepVolumeName == "volTPCActive_PV" && ProcessName != "Transportation") 
    G4cout << EventNumber << " " << ParticleName << " " << ProcessName << " " << aStep->GetPreStepPoint()->GetTotalEnergy()-aStep->GetPostStepPoint()->GetTotalEnergy() << G4endl;
  
  
  if( StepNumber == 1 )
  {
    //std::cout << "We reached the assignment point" << std::endl;

    DSParticle aDSParticle;
    int PDG = aStep->GetTrack()->GetDynamicParticle()->GetPDGcode();
    double Energy = aStep->GetTrack()->GetTotalEnergy();
    int MotherTrackID = aStep->GetTrack()->GetParentID();
    int MotherPDG = 0;

    //std::cout << "\n~~~~~~~\n";
    //std::cout << "My PDG is...";
    //std::cout << PDG << "\n";
    //std::cout << "My track ID is...";
    //std::cout << TrackID << "\n";
    //std::cout << "My process is...";
    //std::cout << ProcessName << "\n";
    //std::cout << "My mother track ID is...";
    //std::cout << MotherTrackID << "\n" << std::endl;
    
    // if(p)  {
    //  std::cout << "!!!!!!!!!!\n";
    //  std::cout << "I found my Primary PDGcode...";
    //  std::cout << p->GetPDGcode();
    //  std::cout << "\n~~~~~~~\n";
    // }

    std::vector<double> StartXYZ;
    StartXYZ.push_back(aStep->GetTrack()->GetPosition()[0]);
    StartXYZ.push_back(aStep->GetTrack()->GetPosition()[1]);
    StartXYZ.push_back(aStep->GetTrack()->GetPosition()[2]);

    std::vector<double> StartMomXYZ; 
    StartMomXYZ.push_back(aStep->GetTrack()->GetMomentum()[0]);
    StartMomXYZ.push_back(aStep->GetTrack()->GetMomentum()[1]);
    StartMomXYZ.push_back(aStep->GetTrack()->GetMomentum()[2]);

    std::vector<double> StartMomDirXYZ; 
    StartMomDirXYZ.push_back(aStep->GetTrack()->GetMomentumDirection()[0]);
    StartMomDirXYZ.push_back(aStep->GetTrack()->GetMomentumDirection()[1]);
    StartMomDirXYZ.push_back(aStep->GetTrack()->GetMomentumDirection()[2]);

    std::vector<double> VertexXYZ;
    VertexXYZ.push_back(aStep->GetTrack()->GetVertexPosition()[0]);
    VertexXYZ.push_back(aStep->GetTrack()->GetVertexPosition()[1]);
    VertexXYZ.push_back(aStep->GetTrack()->GetVertexPosition()[2]);

    std::vector<double> VertexMomDirXYZ;
    VertexMomDirXYZ.push_back(aStep->GetTrack()->GetVertexMomentumDirection()[0]);
    VertexMomDirXYZ.push_back(aStep->GetTrack()->GetVertexMomentumDirection()[1]);
    VertexMomDirXYZ.push_back(aStep->GetTrack()->GetVertexMomentumDirection()[2]);
    
    aDSParticle.SetParticle(EventNumber, TrackID, PDG, Energy, StartXYZ, StartMomXYZ, StartMomDirXYZ, VertexXYZ, VertexMomDirXYZ, ProcessName, MotherTrackID, MotherPDG);
    
    DSEventData->push_back(aDSParticle);

    EventNumber++;
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......