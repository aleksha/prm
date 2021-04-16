#include "PRMDetectorConstruction.hh"
#include "PRMActionInitialization.hh"

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // Detector construction
  runManager->SetUserInitialization(new PRMDetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  runManager->SetUserInitialization(new PRMActionInitialization());
  
  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UImanager->ApplyCommand(command+fileName);


  delete runManager;
}
//-----------------------------------------------------------------------------
