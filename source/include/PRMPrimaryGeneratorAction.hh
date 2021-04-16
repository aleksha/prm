#ifndef PRMPrimaryGeneratorAction_h
#define PRMPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class PrimaryGenerator;

/// The primary generator action class with particle gun.

class PRMPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PRMPrimaryGeneratorAction();
    virtual ~PRMPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

  private:
    PrimaryGenerator* fPrimaryGenerator; // pointer a to object of primary gen class

};
//------------------------------------------------------------------------------
#endif
