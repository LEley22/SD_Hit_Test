#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "SenDet.hh"
#include "G4VisAttributes.hh"
#include "G4UImanager.hh"
#include "G4GenericMessenger.hh"

//detConstruc for Array2

class G4VPhysicalVolume;
class G4LogicalVolume;
class SenDetClass;

class detectorConstruction : public G4VUserDetectorConstruction
{
    public:
        detectorConstruction();
        ~detectorConstruction();

        std::vector<G4VisAttributes*> fVisAttributes();

        void ConstructSDandField();

        virtual G4VPhysicalVolume * Construct();

    private:
        G4LogicalVolume *detLogic, *WindowLogic;
        G4LogicalVolume *TargetLogic;

        G4GenericMessenger * Messenger;

        G4double Thickness;

        G4Box * worldSolid, *TargetSolid, *detSolid, *WindowSolid, *AlFilterSolid, *SimpleSphereSolid;//*TopSolid, *LowASolid, *LowBSolid, *LowFoilSolid;

        G4LogicalVolume * worldLogic, * AlFilLogic, *SimpleSphereLogic; // *LowALogic, *LowBLogic, *LowFoilLogic; 

        G4VPhysicalVolume * worldPhysical, *TargetPhysical, *detPhysical, *WindowPhysical, *AlPhysical, *SimpleSpherePhysical;// *HoleyPhysical, *LowAPhysical, *LowBPhysical, *LowFoilPhysical, *AlSpherePhysical;

        G4Material * air, *vacuum, *Tantalum, *Tungsten, *Aluminium, *Titanium, *Beryllium, *Steel, *Oil, *Gold, *PMMA;

        G4Element * Cr, *Ni, *Mo, *Mn, *Fe, *C, *H, *O, *Si;

        void DefineMaterials();

};

#endif
