#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyEventAction::EndOfEventAction(const G4Event* evt) {
  static int CHCID = -1;
If(CHCID<0) CHCID = G4SDManager::GetSDMpointer()->GetCollectionID("myDet/collection1");
  
G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
MyHitsCollection* myDetColl = 0;
if(HCE)
{ myDetColl = (MyHitsCollection*)(HCE->GetHC(CHCID)); }
if(myDetColl) {
int n_hit = myDetColl->entries();
  
G4cout<<“My detector has ”<<n_hit<<" hits."<<G4endl;
  
for(int i1=0;i1<n_hit;i1++) {
MyHit* aHit = (*myDetColl)[i1];
aHit->Print();
}
}
}

}
