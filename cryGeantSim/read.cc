/* ************************************************
 * GEANT4 GDML
 *
 * File:      read.cc
 *
 *
 * Date:      11/9/2012
 **************************************************/

// USER //
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
//#include "HistoManager.hh"
//#include "barDetector.hh"
//#include "barDetectorHit.hh"
#include "SteppingAction.hh"
#include "DSRun.h"
#include "DSParticle.h"

// GEANT4 //
#include "G4RunManager.hh"
#include "G4UImanager.hh"
//#include "G4UIterminal.hh"
//#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include <TSystem.h>
int main(int argc,char** argv)
{
  gSystem->Load("libMina_DStudy");
    G4RunManager* run_manager = new G4RunManager;

    G4VUserDetectorConstruction* detector_construction = new DetectorConstruction;

    G4VUserPhysicsList* physics_list = new PhysicsList;
    
    //HistoManager*  histo = new HistoManager();
    
    // UserAction classes
    //-------------------
    
    

    run_manager->SetUserInitialization(detector_construction);
    run_manager->SetUserInitialization(physics_list);
    run_manager->SetUserAction(new PrimaryGeneratorAction(""));


    DSEvent MyDSEvent;

    TFile* DSOutFile;
    TTree* DSMCTree;
    DSOutFile = new TFile("DS_uboone_mina.root","RECREATE");
    DSMCTree = new TTree("DSMCTree", "DSMC_output");
    DSMCTree->Branch("Test_DSEvent_Branch","DSEvent",&MyDSEvent);

    G4UserRunAction*      run_action = new RunAction();
    G4UserEventAction*    event_action = new EventAction(&MyDSEvent,DSMCTree);
    //G4UserSteppingAction* stepping_action = new SteppingAction(&MyDSEvent);
    //std::map<int,bool> moms_to_daughters;

    //G4UserSteppingAction* stepping_action = new SteppingAction(&MyDSEvent,&moms_to_daughters);
    G4UserSteppingAction* stepping_action = new SteppingAction(&MyDSEvent);

    run_manager->SetUserAction(stepping_action);
    run_manager->SetUserAction(run_action);
    run_manager->SetUserAction(event_action);
    //run_manager->SetUserAction(tracking_action);

        
    run_manager->Initialize();

    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();

    G4UImanager * ui_manager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    ui_manager->ApplyCommand("/control/execute macros/vis.mac"); 
    ui->SessionStart();
    
    delete ui;    //moms_to_daughter[MotherTrackID] = true;
    //moms_to_daughter[MotherTrackID] = true;
    //std::cout << "I found... " << stepping_action->moms_to_daughter.size()  <<  "moms\n";
    //std::cout << "I found... " << moms_to_daughters.size()  <<  "moms\n";

    DSOutFile->Write();
    DSOutFile->Close();
    return 0;
}


