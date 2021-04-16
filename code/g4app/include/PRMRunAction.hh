#ifndef PRMRunAction_h
#define PRMRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class PRMRunAction : public G4UserRunAction
{
  public:
    PRMRunAction();
    virtual ~PRMRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

