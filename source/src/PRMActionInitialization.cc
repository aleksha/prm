//------------------------------------------------------------------------------
#include "PRMActionInitialization.hh"
#include "PRMPrimaryGeneratorAction.hh"
#include "PRMRunAction.hh"
#include "PRMEventAction.hh"
#include "PRMSteppingAction.hh"
//------------------------------------------------------------------------------
PRMActionInitialization::PRMActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
PRMActionInitialization::~PRMActionInitialization(){}
//------------------------------------------------------------------------------
void PRMActionInitialization::BuildForMaster() const
{
  PRMRunAction* runAction = new PRMRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void PRMActionInitialization::Build() const
{
  SetUserAction(new PRMPrimaryGeneratorAction);

  PRMRunAction* runAction = new PRMRunAction;
  SetUserAction(runAction);

  PRMEventAction* eventAction = new PRMEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new PRMSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
