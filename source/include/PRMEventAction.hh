#ifndef PRMEventAction_h
#define PRMEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class PRMRunAction;

/// Event action class
///

class PRMEventAction : public G4UserEventAction
{
  public:
    PRMEventAction(PRMRunAction* runAction);
    virtual ~PRMEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    PRMRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

