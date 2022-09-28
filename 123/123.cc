#include <iostream>
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh" 
#include "ExG4DetectorConstruction01.hh"
#include "FTFP_BERT.hh"
#include "ExG4ActionInitialization01.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc,char** argv)
{
    
     G4UIExecutive* ui = 0;
     if ( argc == 1 )
     {
       ui = new G4UIExecutive(argc, argv);
     }
    
   CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
   CLHEP::HepRandom::setTheSeed(time(NULL));

G4RunManager* runManager = new G4RunManager;

runManager->SetUserInitialization(new ExG4DetectorConstruction01);

runManager->SetUserInitialization(new FTFP_BERT);

runManager->SetUserInitialization(new ExG4ActionInitialization01);

runManager->Initialize();

G4VisManager* visManager = new G4VisExecutive;
visManager->Initialize();

G4UImanager* UImanager = G4UImanager::GetUIpointer();


if ( ! ui ) {
  // batch mode
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UImanager->ApplyCommand(command+fileName);
    //std::cout << aRun;
}
else {
  // interactive mode
  UImanager->ApplyCommand("/control/execute init_vis.mac");
  ui->SessionStart();
  delete ui;
}


 delete visManager;
 delete runManager;
return 0;
}
