#ifndef ExG4DetectorConstruction01_h
#define ExG4DetectorConstruction01_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "ExG4DetectorSD.hh"

class ExG4DetectorConstruction01 : public G4VUserDetectorConstruction
{
  public:
    
    ExG4DetectorConstruction01();
    ~ExG4DetectorConstruction01();
    
    virtual G4VPhysicalVolume* Construct();
    
private:
    G4LogicalVolume *logicDet11;
    virtual void ConstructSDandField();

};


#endif
