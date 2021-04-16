#ifndef PRMActionInitialization_h
#define PRMActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class PRMActionInitialization : public G4VUserActionInitialization
{
  public:
    PRMActionInitialization();
    virtual ~PRMActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


