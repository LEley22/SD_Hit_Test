#include "detectorConstruction.hh"
#include "SenDet.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4UserLimits.hh"
#include <fstream>
#include <iostream>
#include <string>
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

//G4Array2 detConstruct



detectorConstruction::detectorConstruction()//constructor
{
    Thickness = 6;
    G4RunManager* runManager = G4RunManager::GetRunManager();
    Messenger = new G4GenericMessenger(this, "/detector/", "thickness");
    Messenger->DeclareProperty("thickness", Thickness, "Target thickness");
    runManager->GeometryHasBeenModified();

    DefineMaterials();

}


detectorConstruction::~detectorConstruction() //destructor
{
  if(TargetLogic)
  {
    delete TargetLogic;
    delete worldLogic;
  }
}


void detectorConstruction::DefineMaterials()
{
    //Manager
    G4NistManager* nist = G4NistManager::Instance();
    //Materials
    air = nist->FindOrBuildMaterial("G4_AIR");
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    Tantalum = nist->FindOrBuildMaterial("G4_Ta");  //tantalum (material)
    Aluminium = nist->FindOrBuildMaterial("G4_Al");  //aluminium (material)
    Titanium = nist->FindOrBuildMaterial("G4_Ti");  //titanium (material)
    Tungsten= nist->FindOrBuildMaterial("G4_W");  //tungsten (material)
    Beryllium = nist->FindOrBuildMaterial("G4_Be");  //beryllium (material)
    Gold = nist->FindOrBuildMaterial("G4_Au");  //beryllium (material)
   
    //Elements
    Cr = nist->FindOrBuildElement("Cr"); //chromium
    Ni = nist->FindOrBuildElement("Ni");  //nickel
    Mo = nist->FindOrBuildElement("Mo");  //molybdenum
    Mn = nist->FindOrBuildElement("Mn");  //manganese
    O = nist->FindOrBuildElement("O");  //oxygen
    Fe = nist->FindOrBuildElement("Fe");  //iron
    C = nist->FindOrBuildElement("C");  //carbon
    H = nist->FindOrBuildElement("H");  //hydrogen
    Si = nist->FindOrBuildElement("Si");  //hydrogen


    //Mixtures/Compounds etc.
    G4double SteelDensity = 8.0 * g/cm3;
    Steel = new G4Material("Steel", SteelDensity, 6);
    G4double fracmass;
    Steel->AddElement(Fe, fracmass = 66.5 *perCent);
    Steel->AddElement(Cr, fracmass = 17*perCent);
    Steel->AddElement(Ni, fracmass = 12*perCent);
    Steel->AddElement(Mo, fracmass = 2.5 *perCent);
    Steel->AddElement(Mn, fracmass = 1*perCent);
    Steel->AddElement(Si, fracmass = 1*perCent);

    G4double OilDensity = 0.89 * g/cm3;
    Oil = new G4Material("Oil", OilDensity, 2);
    G4int Natoms;
    Oil->AddElement(C, Natoms = 19);
    Oil->AddElement(H, Natoms = 38);

        //PMMA
   G4double PMMAdensity = 1.190*g/cm3;

   PMMA = new G4Material("PMMA", PMMAdensity, 3);
   PMMA->AddElement(C, Natoms = 5);
   PMMA->AddElement(H,Natoms = 8);
   PMMA->AddElement(O, Natoms = 2);
}


G4VPhysicalVolume * detectorConstruction::Construct()
{
  
//WORLD CREATION//
    worldSolid = new G4Box("worldSolid", 0.5*m, 0.5*m, 1.*m); //name and half size in m

    worldLogic = new G4LogicalVolume(worldSolid,   //call solid
                                      vacuum,         //material to be made of
                                      "worldLogic"); //name

    worldPhysical = new G4PVPlacement(0,    //rotation
                                                        G4ThreeVector(0,0,0), //location
                                                        worldLogic, //logic volume
                                                        "worldPhysical", //name
                                                        0, //mother volume (0 as it is mother)
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps

    // TARGET CREATION


    TargetSolid = new G4Box("TargetSolid", 8*cm, 12*cm, 1.25 * um); //name and half size in m
    //half thickness is 6um for 90 keV, 9 um for 120 keV

    G4cout << "Thickness is " << Thickness << G4endl;

    TargetLogic = new G4LogicalVolume(TargetSolid,   //call solid
                                                        Gold,         //material to be made of
                                                        "TargetLogic"); //name

    TargetPhysical = new G4PVPlacement(0,    //rotation
                                                        G4ThreeVector(0,0,0*m), //location
                                                        TargetLogic, //logic volume
                                                        "TargetPhysical", //name
                                                        worldLogic, //mother volume (0 as it is mother)
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps
    
    // Be Window


    WindowSolid = new G4Box("WindowSolid", 8*cm, 12*cm, 250 * um); //name and half size in m


    WindowLogic = new G4LogicalVolume(WindowSolid,   //call solid
                                                        Beryllium,         //material to be made of
                                                        "WindowLogic"); //name

    WindowPhysical = new G4PVPlacement(0,    //rotation
                                                        G4ThreeVector(0,0,251.25*um), //location
                                                        WindowLogic, //logic volume
                                                        "WindowPhysical", //name
                                                        worldLogic, //mother volume (0 as it is mother)
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps



//FILTER CREATION
//REGULATORY MIN AL (COMMENT OUT WHICH IS WANTED)
   AlFilterSolid = new G4Box("AlFilterSolid", 8*cm, 12*cm, 1 *mm); //name and half size in m

   AlFilLogic = new G4LogicalVolume(AlFilterSolid,   //call solid
                                                       Aluminium,         //material to be made of
                                                       "AlFilLogic"); //name

   AlPhysical = new G4PVPlacement(0,    //rotation
                                                       G4ThreeVector(0,0,0.2*m), //location
                                                       AlFilLogic, //logic volume
                                                       "AlPhysical", //name
                                                       worldLogic, //mother volume
                                                       false,
                                                       0, //copy number
                                                       true); //check overlaps

//PHANTOM CONSTRUCTION 
//SIMPLE PHANTOM 

    G4double SimpleSphere = 2.5 * cm;
    G4Orb* SimpleSphereSolid = new G4Orb("SipmeSphere", SimpleSphere); //name, mR

    G4LogicalVolume* SimpleSphereLogic = new G4LogicalVolume(SimpleSphereSolid, Aluminium, "SimpleSphereLogic"); //non-holey logical volume

    SimpleSpherePhysical = new G4PVPlacement(0,
        G4ThreeVector(0 * cm, 0 * cm, 30 * cm),
        SimpleSphereLogic,
        "SimpleSpherePhysical",
        worldLogic,
        false,
        0,
        true);


//PMMA PROPER PHANTOM
//Bottom Layer (A)
//    LowASolid = new G4Box("LowASolid", 8*cm, 12*cm, 4.975*mm); //name and half size in m

//    LowALogic = new G4LogicalVolume(LowASolid,   //call solid
//                                                            PMMA,         //material to be made of
//                                                            "LowALogic"); //name

//    LowAPhysical = new G4PVPlacement(0,    //rotation
//                                                            G4ThreeVector(0,0,0.445025*m), //location
//                                                            LowALogic, //logic volume
//                                                            "LowAPhysical", //name
//                                                            worldLogic, //mother volume
//                                                            false,
//                                                            0, //copy number
//                                                            true); //check overlaps

// // //Bottom Layer (B)
//    LowBSolid = new G4Box("LowBSolid", 8*cm, 12*cm, 4.975*mm); //name and half size in m

//    LowBLogic = new G4LogicalVolume(LowBSolid,   //call solid
//                                                                PMMA,         //material to be made of
//                                                                "LowBLogic"); //name

//    LowBPhysical = new G4PVPlacement(0,    //rotation
//                                                                G4ThreeVector(0,0,0.434975*m), //location
//                                                                LowBLogic, //logic volume
//                                                                "LowBPhysical", //name
//                                                                worldLogic, //mother volume
//                                                                false,
//                                                                0, //copy number
//                                                                true); //check overlaps

// //     //Bottom Layer (Foil)
//    LowFoilSolid = new G4Box("LowFoilSolid", 8*cm, 12*cm, 0.05*mm); //name and half size in m

//    LowFoilLogic = new G4LogicalVolume(LowFoilSolid,   //call solid
//                                                                    PMMA,         //CHANGE BACK TO AL TO BE PROPER FILTER
//                                                                    "LowFoilLogic"); //name

//    LowFoilPhysical = new G4PVPlacement(0,    //rotation
//                                                                    G4ThreeVector(0,0,0.44*m), //location
//                                                                    LowFoilLogic, //logic volume
//                                                                    "LowFoilPhysical", //name
//                                                                    worldLogic, //mother volume
//                                                                    false,
//                                                                    0, //copy number
//                                                                    true); //check overlaps

//     //Top Layer + Air Bubble
//     TopSolid = new G4Box("TopSolid", 8 * cm, 12 * cm, 2.5 * mm); //name and half size in m

//     //  TopLogic = new G4LogicalVolume(TopSolid, PMMA, "TopLogic"); //non-holey logical volume

//     // TopPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.4275 * m), TopLogic, "TopPhysical", worldLogic, false, 0, true);

//     // Bubble Space Creator
//    G4double BubbleRad = 0.5 * mm;
//    G4Orb* BubbleSolid = new G4Orb("Bubble", BubbleRad); //name, mR

// double A[25];
// double B[25];

// double objectDiameter = 0.1;  // Diameter of each sphere in cm

// G4SubtractionSolid* Holey = nullptr; // Declare Holey variable


// double layerMinX = -8.0;  // Minimum X position of the layer in cm
// double layerMaxX = 8.0;   // Maximum X position of the layer in cm
// double layerMinY = -12.0; // Minimum Y position of the layer in cm
// double layerMaxY = 12.0;  // Maximum Y position of the layer in cm

// int numObjectsX = 5;  // Number of objects in the X dimension
// int numObjectsY = 5;  // Number of objects in the Y dimension

// double totalWidth = layerMaxX - layerMinX - (numObjectsX * objectDiameter);  // Remaining width after placing objects
// double totalHeight = layerMaxY - layerMinY - (numObjectsY * objectDiameter);  // Remaining height after placing objects

// double spacingX = totalWidth / (numObjectsX + 1);  // Spacing between objects in X dimension
// double spacingY = totalHeight / (numObjectsY + 1);  // Spacing between objects in Y dimension

// double startX = layerMinX + spacingX + (objectDiameter / 2.0);  // Start X position adjusted for half the object diameter
// double startY = layerMinY + spacingY + (objectDiameter / 2.0);  // Start Y position adjusted for half the object diameter

// // Placement loop
// int index = 0;
// for (int i = 0; i < numObjectsY; ++i) {
//     for (int j = 0; j < numObjectsX; ++j) {
//         // Calculate the position of the sphere
//         double posX = startX + j * (objectDiameter + spacingX);
//         double posY = startY + i * (objectDiameter + spacingY);

//         std::cout << "Placing sphere at (" << posX << ", " << posY << ")" << std::endl;

//         A[index] = posX;
//         B[index] = posY;
//         index++;
//     }
// }

// // Perform subtraction using positions
// for (int i = 0; i < 25; ++i) {
//     Holey = new G4SubtractionSolid("Holey",
//         TopSolid,
//         BubbleSolid,
//         0,
//         G4ThreeVector(A[i] * cm, B[i] * cm, 0 * cm));
// }

// G4LogicalVolume* logicHoley = new G4LogicalVolume(Holey, PMMA,
//     "logicHoley",
//     0, 0, 0);

// HoleyPhysical = new G4PVPlacement(0,  // Rotation
//     G4ThreeVector(0, 0, 0.4275 * m),  // Location
//     logicHoley,  // Logical volume
//     "HoleyPhys",  // Name
//     worldLogic,  // Mother volume
//     false,
//     0,  // Copy number
//     true);  // Check overlaps

//     //Al sphere Creator
//     G4double AlRad = 0.5 * mm;
//     G4Orb* AlSphereSolid = new G4Orb("AlSphere", AlRad); //name, mR

//     G4LogicalVolume* AlSphereLogic = new G4LogicalVolume(AlSphereSolid, Aluminium, "AlSphereLogic"); //non-holey logical volume

//     for (int i = 0; i < 25; ++i) {
//     AlSpherePhysical = new G4PVPlacement(0,
//         G4ThreeVector(A[i] * cm, B[i] * cm, 0 * cm),
//         AlSphereLogic,
//         "AlSpherePhysical",
//         logicHoley,
//         false,
//         0,
//         true);
// }






//DETECTOR CREATION
    detSolid = new G4Box("detSolid", 8*cm, 12*cm, 0.01*m); //name and half size in m
    //to match ipioni (which is 43 x 43 bin with 1cm/pixel you need 43/2 cm widths)


    detLogic = new G4LogicalVolume(detSolid,   //call solid
                                                        vacuum,         //material to be made of
                                                        "detLogic"); //name

    G4ThreeVector DetPosition = G4ThreeVector(0.,0.,0.46*m); 
    detPhysical = new G4PVPlacement(0,    //rotation
                                                        DetPosition, //location
                                                        detLogic, //logic volume
                                                        "detPhysical", //name
                                                        worldLogic, //mother volume
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps

//VIS ATTRIBUTES (FOR UI)

    G4VisAttributes* visAtt1 = new G4VisAttributes(G4Colour(0.0,1.0,1.0)); //detector is cyan
    visAtt1->SetForceSolid(true);
    detLogic->SetVisAttributes(visAtt1);

    G4VisAttributes* visAtt2 = new G4VisAttributes(G4Colour(0.0,0.0,1.0)); //target is blue
    visAtt2->SetForceSolid(true);
    TargetLogic->SetVisAttributes(visAtt2);

  //   G4VisAttributes* visAtt4 = new G4VisAttributes(G4Colour(0.5,0.5,0.5)); //aluminium is grey
  //   visAtt4->SetForceSolid(true);
  //   LowALogic->SetVisAttributes(visAtt4);

  //   G4VisAttributes* visAtt5 = new G4VisAttributes(G4Colour(1.0,0.5,1.0)); //oil is pink
  //   visAtt5->SetForceSolid(true);
  //   LowBLogic->SetVisAttributes(visAtt5);

  //   G4VisAttributes* visAtt6 = new G4VisAttributes(G4Colour(0.0,0.1,0.0)); //titanium is green
  //   visAtt6->SetForceSolid(true);
  //   LowFoilLogic->SetVisAttributes(visAtt6);

  //  G4VisAttributes* visAtt7 = new G4VisAttributes(G4Colour(0.0,0.5,0.5)); //steel is ??
  //  visAtt7->SetForceSolid(true);
  //  logicHoley->SetVisAttributes(visAtt7);

     G4VisAttributes* visAtt7 = new G4VisAttributes(G4Colour(0.0,0.5,0.5)); //steel is ??
   visAtt7->SetForceSolid(true);
   SimpleSphereLogic->SetVisAttributes(visAtt7);

   G4VisAttributes* visAtt8 = new G4VisAttributes(G4Colour(0.0,0.5,0.5)); //steel is ??
   visAtt7->SetForceSolid(true);
   AlFilLogic->SetVisAttributes(visAtt7);
 //USER LIMITS

  // Set a minimum kinetic energy for charged particles
//   G4UserLimits* fStepLimit = new G4UserLimits();
//   fStepLimit->SetUserMinEkine(15*keV);
//   G4LogicalVolumeStore* store = G4LogicalVolumeStore::GetInstance();
//   std::vector<G4LogicalVolume*>::iterator it;
//   for (it=store->begin(); it!=store->end(); it++){
//     (*it)->SetUserLimits(fStepLimit);
//   }



return worldPhysical;
}

void detectorConstruction::ConstructSDandField()
{

    SenDetClass *senDet  = new SenDetClass("SensitiveDetector");
    detLogic -> SetSensitiveDetector(senDet);

}
