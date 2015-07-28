/* ************************************************
 * GEANT4 VCGLIB/CAD INTERFACE
 *
 * File:      DetectorConstruction.cc
 *
 *
 * Date:      11/8/2012
 **************************************************/

// USER //
#include "DetectorConstruction.hh"
//#include "barDetector.hh"

// GEANT4 //
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

//#include "G4GDMLParser.hh"


DetectorConstruction::DetectorConstruction()
{;}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  G4VSensitiveDetector* CryoDetector;

  //Define materials
  G4NistManager * nist_manager = G4NistManager::Instance();
  G4Material * air = nist_manager->FindOrBuildMaterial("G4_AIR");

  //Argon
  G4double z;
  G4String name;
  G4String symbol;
  G4int nElem;
  G4double a = 39.95*g/mole;
  G4Element* Ar40 = new G4Element(name="Argon",symbol="Ar40",z=18., a);
    G4double density = 1.390*g/cm3;
  G4Material* lAr = new G4Material(name="liquidArgon", density, nElem=1);
    lAr->AddElement(Ar40,1.0);
  
  //Carbon
  G4Element* C12 = new G4Element
    (name="Carbon", symbol="C12", z=6., a=12.0*g/mole);
  G4Material* Carbon = new G4Material
    (name="Carbon", density=2.15*g/cm3, 1);
  Carbon->AddElement(C12, 1.0);
  
  //world volume
  G4double worldX = 16.7*m;
  G4double worldY = 16.7*m;
  G4double worldZ = 20.5*m;
  
  G4Box* world_solid = new G4Box("world_solid",worldX,worldY,worldZ);
  G4LogicalVolume* world_logical = new G4LogicalVolume(world_solid, air,"world_logical",0,0,0);
  G4VPhysicalVolume* world_physical = new G4PVPlacement(0, G4ThreeVector(), world_logical, "world_physical", 0, false, 0);
  
  //room
  G4double RRMin = 0;
  G4double RRMax = 16.7*m;
  G4double RDz = 10.25*m;
  G4double RSPhi = 0;
  G4double RDPhi = (2*pi)*rad;
  
  G4ThreeVector Rtrans(0,0,-10.25*m);
  G4RotationMatrix* Rrot = new G4RotationMatrix;
  
  G4Tubs* room_solid = new G4Tubs("room_solid", RRMin, RRMax, RDz, RSPhi,RDPhi);
  G4LogicalVolume* room_logical = new G4LogicalVolume(room_solid, air,"room_logical",0,0,0);
  G4VPhysicalVolume* room_physical = new G4PVPlacement(Rrot, Rtrans, room_logical, "room_physical", world_logical,false, 0);

  //roof
  G4double TRMin = 0;
  G4double TRMax = 7.5*m;
  G4double TDz = 0.585*m;
  G4double TSPhi = 0;
  G4double TDPhi = (2*pi)*rad;
  
  G4ThreeVector Ttrans(0,0,9.665*m);
  G4RotationMatrix* Trot = new G4RotationMatrix;
  
  G4Tubs* top_solid = new G4Tubs("top_solid", TRMin, TRMax, TDz, TSPhi,TDPhi);
  G4LogicalVolume* top_logical = new G4LogicalVolume(top_solid, Carbon,"top_logical",0,0,0);
  G4VPhysicalVolume* top_physical = new G4PVPlacement(Trot, Ttrans, top_logical,
                                       "top_physical", room_logical,false, 0);
  
  //Dirt/Concrete
  G4double ERMin = 7.5*m;
  G4double ERMax = 16.7*m;
  G4double EDz = 5.905*m;
  G4double ESPhi = 0;
  G4double EDPhi = (2*pi)*rad;
  
  G4ThreeVector Etrans(0,0,-4.345*m);
  G4RotationMatrix* Erot = new G4RotationMatrix;
  
  G4Tubs* earth_solid = new G4Tubs("earth_solid", ERMin, ERMax, EDz, ESPhi,EDPhi);
  G4LogicalVolume* earth_logical = new G4LogicalVolume(earth_solid, Carbon,"earth_logical",0,0,0);
  G4VPhysicalVolume* earth_physical = new G4PVPlacement(Erot, Etrans, earth_logical, "earth_physical", room_logical,false, 0);

  //Cryo Stuff
  G4double cX = 5.2*m;
  G4double cY = 1.25*m;
  G4double cZ = 1.15*m;
  G4Box* cryo_solid = new G4Box("Cryostat",cX,cY,cZ);
  
  G4ThreeVector Ctrans(0,0,-7.10*m);
  G4RotationMatrix* Crot = new G4RotationMatrix;
  
  G4LogicalVolume* cryo_logical = new G4LogicalVolume(cryo_solid,lAr,"cryo_logical",0,0,0);
  G4VPhysicalVolume* cryo_physical = new G4PVPlacement(Crot,Ctrans,cryo_logical,"cryo_physical",room_logical,false,0);
  
// //Sensitive Detectors
// G4SDManager* SDman = G4SDManager::GetSDMpointer();
// G4String SDname;
// 
// CryoDetector = new barDetector(SDname="/CryoDetector");
// SDman->AddNewDetector(CryoDetector);
// cryo_logical->SetSensitiveDetector(CryoDetector);

  
  return world_physical;
}
