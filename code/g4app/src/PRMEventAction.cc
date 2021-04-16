#include "PRMEventAction.hh"
#include "PRMRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
PRMEventAction::PRMEventAction(PRMRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
PRMEventAction::~PRMEventAction(){}
//------------------------------------------------------------------------------
void PRMEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void PRMEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
