#ifndef senDet_h
#define senDet_h 1

#include "G4VSensitiveDetector.hh"

#include "Hit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

{

class senDet : public G4VSensitiveDetector
{
  public:
    senDet(const G4String& name,
                  const G4String& hitsCollectionName,
                  G4int nofCells);
    ~senDet() override = default;

    // methods from base class
    void   Initialize(G4HCofThisEvent* hitCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    void   EndOfEvent(G4HCofThisEvent* hitCollection) override;

  private:
    HitsCollection* fHitsCollection = nullptr;
    G4int CollectionID
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


