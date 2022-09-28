#include "ExG4DetectorConstruction01.hh"
#include "ExG4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction()
{ }


ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ }



G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  

  G4NistManager* nist = G4NistManager::Instance();
    

//  G4double det_sizeXY = 25*cm, det_sizeZ = 0.15*cm;


  G4Material* det_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
  G4double rindexPolystyrene[2] = {1.59, 1.59};
  
  G4MaterialPropertiesTable *mptPolystyrene = new G4MaterialPropertiesTable();
  mptPolystyrene->AddProperty("RINDEX", energy, rindexPolystyrene, 2);
  det_mat->SetMaterialPropertiesTable(mptPolystyrene);

  G4bool checkOverlaps = false;

//-------------------------------------------------------------------------------------------
    
  // Detector parameters
  // Параметры детектора,
  //
  //В этой части программы описывается цилиндр из полистерола (М.Г. Коротков)
  G4double innerRadius = 0.*cm;
  G4double R = 0.0125*cm;
  G4double D = 0.025*cm;
  G4double hx = 0.5*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;
  
  G4RotationMatrix rotm  = G4RotationMatrix();
  rotm.rotateY(90*deg);

  G4double world_sizeXY = 10*cm;
  G4double world_sizeZ  = 10*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  // Создание объема для мира, определяется просто сама форма объема, берем параллелепипед
  G4Box* solidWorld =
    new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);
    
    

  // Логический объем, здесь подключается материал, из которого сделан объем
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");            
                                             
                                             
                                             

  //Физический объем, а теперь наш логический объем помещаем в "ральный" мир
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);        
                     
  ///////////////////////////////////////////////////////////////////////////////////////////

  G4Tubs* solidDet11 = new G4Tubs("solidDet11", innerRadius, R, hx, startAngle, spanningAngle);

  //Логический объем
  logicDet11 = new G4LogicalVolume(solidDet11, det_mat, "logicDet11");        

  //Физический объем детектора
  for(G4int i = 0; i < 50; i++)
  {
    new G4PVPlacement(G4Transform3D(rotm, G4ThreeVector(0,0,(D + i*D))), logicDet11, "physDet", logicWorld, false, i, checkOverlaps);
  }
  for(G4int i = 0; i < 50; i++)
  {
    new G4PVPlacement(G4Transform3D(rotm, G4ThreeVector(0,0.866025404*D,(D + i*D) + 0.5*D)), logicDet11, "physDet", logicWorld, false, i+50, checkOverlaps);
  }  

  for(G4int i = 0; i < 50; i++)
  {
    new G4PVPlacement(G4Transform3D(rotm, G4ThreeVector(0,0.866025404*2*D,(D + i*D))), logicDet11, "physDet", logicWorld, false, i+100, checkOverlaps);
  }
  
  for(G4int i = 0; i < 50; i++)
  {
    new G4PVPlacement(G4Transform3D(rotm, G4ThreeVector(0,0.866025404*3*D,(D + i*D) + 0.5*D)), logicDet11, "physDet", logicWorld, false, i+150, checkOverlaps);
  }

  for(G4int i = 0; i < 50; i++)
  {
    new G4PVPlacement(G4Transform3D(rotm, G4ThreeVector(0,0.866025404*4*D,(D + i*D))), logicDet11, "physDet", logicWorld, false, i+200, checkOverlaps);
  }

  for(G4int i = 0; i < 50; i++)
  {
    new G4PVPlacement(G4Transform3D(rotm, G4ThreeVector(0,0.866025404*5*D,(D + i*D) + 0.5*D)), logicDet11, "physDet", logicWorld, false, i+250, checkOverlaps);
  }  
  return physWorld;
}


void ExG4DetectorConstruction01::ConstructSDandField()
{
    ExG4DetectorSD *sensDet = new ExG4DetectorSD("SensitiveDetector");

    logicDet11->SetSensitiveDetector(sensDet);
}
