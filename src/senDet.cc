#include "senDet.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

senDet::senDet(G4String name)
:G4VSensitiveDetector(name),
collectionID(-1)
{
collectionName.insert(“DetectorHits");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void senDet::Initialize(G4HCofThisEvent* hce)
{
  if(collectionID<0) collectionID = GetCollectionID(0);
  hitsCollection = new MyHitsCollection
  (SensitiveDetectorName,collectionName[0]);
  hce->AddHitsCollection(collectionID,hitsCollection); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool senDet::ProcessHits(G4Step* step,
                                     G4TouchableHistory*)
{

  MyHit* aHit = new MyHit();

  hitsCollection->insert(aHit);
return true; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void senDet::EndOfEvent(G4HCofThisEvent*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
