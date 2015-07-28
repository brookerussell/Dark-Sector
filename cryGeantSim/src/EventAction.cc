//
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
/// \file muonDet/crySim/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
// $Id$
// --------------------------------------------------------------
//

#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
//#include "G4TrajectoryContainer.hh"
//#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"


//#include "barDetectorHit.hh"

EventAction::EventAction(DSEvent *dsEventData,TTree* the_tree)
{
DSEventData = dsEventData;
_tree = the_tree;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  std::cout << "Begin of Event" << std::endl;
}

void EventAction::EndOfEventAction(const G4Event* evt)
{

  std::cout << "End of Event Action" << std::endl;

//  //----------Taken from EventAction()--------------------
//  G4String colName;
//  G4SDManager* SDman = G4SDManager::GetSDMpointer();
//  fBDHCID0 = SDman->GetCollectionID(colName="CryoDetector/barDetectorColl");
//  fVerboseLevel = 1;
//  //-----------------------------------------------------
//  
//  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
//  barDetectorHitsCollection* BDHC0 = 0;
//  
//  BDHC0 = (barDetectorHitsCollection*)(HCE->GetHC(fBDHCID0));
//
//  // Diagnostics
//  if (fVerboseLevel==0 || evt->GetEventID() % fVerboseLevel != 0) return;
//  G4PrimaryParticle* primary = evt->GetPrimaryVertex(0)->GetPrimary(0);
////  G4cout /*<< G4endl */
////          << ">>> Event " << evt->GetEventID() << " >>> Simulation truth : "
////          << primary->GetG4code()->GetParticleName()
////          << " " << primary->GetMomentum() << G4endl;
//
//  // Histos and ntuples
//  G4double eDepDet0 = 0.;
//
//  G4double MomentumX = 0.;
//  G4double MomentumY = 0.;
//  G4double MomentumZ = 0.;
//  G4int PDGCode = 0;
//  
//  G4double eDepLast = 0.;
//
//  if((BDHC0->entries())!= 0)
//  {
//    int iHit = 0;
////    double totalE = 0.;
//    for(G4int j = 0; j < (BDHC0->entries());j++)
//    {  
//      barDetectorHit* aHit = (*BDHC0)[j];
//      double eDep = aHit->GetEdep();
//      if(eDep>0.)
//      {
//        iHit++;
//        eDepDet0 += eDep;
////         G4cout << "aHit->GetPos(): " << aHit->GetPos() << G4endl;
//      }
//    }
//    G4cout << "CryoDetector has " << iHit << " hits. Total Edep is "
//           << eDepDet0/MeV << " (MeV)" << G4endl;
//  }
//

  DSEventData->SetEventNum(evt->GetEventID());
  _tree->Fill();
 
  DSEventData->clear();

}