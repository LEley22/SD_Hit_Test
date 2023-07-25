//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B4/B4d/src/EventAction.cc
/// \brief Implementation of the B4d::EventAction class

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    sumValue += *(it.second);
  }
  return sumValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
   // Get hist collections IDs
  if ( detHCID == -1 ) {
    detHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("Det/Edep");
    filterHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("Filter/Edep");
  }

  // Get sum values from hits collections
  //
  auto detEdep = GetSum(GetHitsCollection(detHCID, event));
  auto FilterEdep = GetSum(GetHitsCollection(FilterHCID, event));

  G4AnalysisManager * man = G4AnalysisManager::Instance();

  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // man->FillNtupleIColumn(0, evt);                 //fill N tuple 
  // man->FillNtupleDColumn(1, posPhoton[0]);
  // man->FillNtupleDColumn(2, posPhoton[1]);
  // man->FillNtupleDColumn(3, posPhoton[2]);
  // man->FillNtupleDColumn(4, edep1);  //take INITIAL energy of photon at end (detector is air so should not affect E)
  // man->AddNtupleRow(0);
    
  man->FillH1(0, detEdep);
  man->FillH1(0, FilterEdep);

  // man->FillH2(0, posPhoton[0], posPhoton[1], 0.0); //ID, x, y, weighting

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
