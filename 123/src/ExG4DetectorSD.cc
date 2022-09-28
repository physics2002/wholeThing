#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "ExG4DetectorSD.hh"
#include <vector>

#include<G4UserRunAction.hh>
#include<G4Run.hh>

ExG4DetectorSD::ExG4DetectorSD(G4String name):G4VSensitiveDetector(name)
{}

G4bool ExG4DetectorSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    G4int copyNo = touchable->GetVolume()->GetCopyNo();

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep==0.) return false;
    G4cout << edep/keV << " " << posDetector << " " << copyNo << G4endl;
    

    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->FillNtupleDColumn(0, edep);
    man->AddNtupleRow();

    return true;
}


ExG4DetectorSD::~ExG4DetectorSD()
{}

