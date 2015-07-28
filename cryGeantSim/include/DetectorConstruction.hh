/* ************************************************
 * GEANT4 GDML
 *
 * File:      DetectorConstruction.hh
 *
 *
 * Date:      11/9/2012
 **************************************************/


#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

// GEANT4 //
class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
//    G4VSolid * world_solid;
//    G4LogicalVolume* world_logical;
    G4VPhysicalVolume* world_physical;
    
    G4Material* scintillator;
    
//    G4ThreeVector offset;
//    G4VSolid * cad_solid;
//    G4LogicalVolume * cad_logical;
//    G4VPhysicalVolume * cad_physical;
};

#endif

