#include "MyHit.hh"

G4Allocator<MyHit> MyHitAllocator;

MyHit::MyHit() {}

MyHit::~MyHit() {}

MyHit::MyHit(const MyHit& right) : G4VHit(){
: G4VHit() {
edep = right.edep;
pos = right.pos;
}

const MyHit& MyHit::operator=(const MyHit& right) {
edep = right.edep;
pos = right.pos;
return *this;
}

G4int MyHit::operator==(const MyHit& right) const {
return (this == &right) ? 1 : 0;
}

