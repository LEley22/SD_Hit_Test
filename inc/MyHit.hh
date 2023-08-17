#ifndef detHit_h
#define detHit_h 1

#include "G4VHit.hh"
#include “G4THitsCollection.hh”
#include "G4Allocator.hh"

class MyHit : public G4VHit
{

public:
        MyHit();
        ~MyHit();
        MyHit(const MyHit&);
        const MyHit& operator=(const MyHit&);
        int operator==(const MyHit&) const;

        inline void* operator new(size_t);
        inline void  operator delete(void*);

        virtual void Draw();

};

typedef G4THitsCollection<MyHit> MyHitsCollection;
extern G4Allocator<MyHit> MyHitAllocator;

inline void* MyHit::operator new(size_t){
  aHit = (void *) MyHitAllocator.MallocSingle();
  return aHit;
}

inline void detHit::operator delete(void* aHit){
 hitAllocator->FreeSingle((MyHit*) aHit);
}

#endif
