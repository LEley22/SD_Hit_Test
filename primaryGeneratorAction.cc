#include "primaryGeneratorAction.hh"

primaryGeneratorAction::primaryGeneratorAction() //info in here to allow overrun by macro files
{
    ParticleGun = new G4ParticleGun(1); //no of particles per event

     G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();

    G4String particleName = "e-";
    G4ParticleDefinition * particle = particleTable->FindParticle("e-");

    G4ThreeVector momentum(0.,0.,1.); //momentum direction
    
    ParticleGun->SetParticleMomentumDirection(momentum);
    ParticleGun->SetParticleDefinition(particle);
}

primaryGeneratorAction::~primaryGeneratorAction()
{

    delete ParticleGun;
}

void primaryGeneratorAction::GeneratePrimaries(G4Event * anEvent)
{
    //random number generator over a circle of radius r (where r is number multiplier in R)
    //G4UniformRand creates uniformly random output over interval 0 to 1
    //assumes therefore perfect electron beam
    G4double R = ((0.5*mm)*(pow(G4UniformRand(),0.5))); 
    G4double theta = ((2*M_PI)*(G4UniformRand()));  //COMMENTED OUT BUT KEPT IN CASE CHANGE MIND
    
    ParticleGun->SetParticlePosition(G4ThreeVector(R*cos(theta), R*sin(theta), -0.1*m));
     ParticleGun->GeneratePrimaryVertex(anEvent);
}
