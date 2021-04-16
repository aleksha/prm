//------------------------------------------------------------------------------
#include "PRMDetectorConstruction.hh"
//------------------------------------------------------------------------------
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "../../configs/geom/geom_config.h"
//------------------------------------------------------------------------------
PRMDetectorConstruction::PRMDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0), fLV01(0), fLV02(0), fLV03(0), fLV04(0), fLV05(0), fLV06(0), fLV07(0), fLV08(0), fLV10(0)
{ }
//------------------------------------------------------------------------------
PRMDetectorConstruction::~PRMDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* PRMDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();

  G4String name;
  //G4double z, a, density;
  //G4double temperature, pressure;
  //G4int ncomponents, natoms;
  //G4double fractionmass;

  // Elements
  //G4Element* H  = new G4Element("Hydrogen", "H",  z=  1, a= 1.008*g/mole);
  //#G4Element* C  = new G4Element("Carbon",   "C",  z=  6, a= 12.00*g/mole);
  //G4Element* N  = new G4Element("Nitrogen", "N",  z=  7, a= 14.01*g/mole);
  //G4Element* O  = new G4Element("Oxygen",   "O",  z=  8, a= 16.00*g/mole);
  //G4Element* Al = new G4Element("Aluminium","Al", z= 13, a= 26.9815385*g/mole);
  //G4Element* Ar = new G4Element("Argon",    "Ar", z= 18, a= 39.95*g/mole);
  //G4Element* Cu = new G4Element("Copper",   "Cu", z= 29, a= 63.546*g/mole);


  //Gases
  //G4Material* CH4Gas = new G4Material(name="CH4Gas",density=13.661*kg/m3,ncomponents=2);
  //CH4Gas->AddElement(H,4);
  //CH4Gas->AddElement(C,1);
  //G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 33.213 *kg/m3 );
  // Use 95% Ar, 5% Methane for electron detector gas. Percentage per volume
  //G4Material* ArCH4 = new G4Material(name="ArCH4"  , density = 32.2354*kg/m3, ncomponents=2);
  //ArCH4->AddMaterial (  ArGas,  fractionmass = 0.978811);
  //ArCH4->AddMaterial( CH4Gas,  fractionmass = 0.021189);
  //Solids
  //G4Material *SiSolid = new G4Material("SiSolid", 14, 28.0855   *g/mole,  2.33  * g/cm3 );
  //G4Material *AlSolid = new G4Material("AlSolid", 13, 26.9815385*g/mole,  2.700 * g/cm3 );
  //G4Material *CuSolid = new G4Material("CuSolid", 29, 63.543    *g/mole,  8.96  * g/cm3 );
  //G4Material* Mylar = new G4Material(name="Mylar", 1.39*g/cm3, 3);
  //Mylar->AddElement(O,2);
  //Mylar->AddElement(C,5);
  //Mylar->AddElement(H,4);

  //G4Material* CarbonFiber = new G4Material(name="CarbonFiber",0.145*g/cm3, 1);
  //CarbonFiber->AddElement(C,1);

  G4int ncomponents, natoms;
  G4double density;

  G4Element* H  = nist->FindOrBuildElement(1);
  G4Element* C  = nist->FindOrBuildElement(6);
  G4Element* O  = nist->FindOrBuildElement(8);
  G4Element* Si = nist->FindOrBuildElement(14);

  G4Material* G10 = new G4Material("G10", density=1.700*g/cm3, ncomponents=4);
  G10->AddElement(Si,natoms=1); G10->AddElement(O,natoms=2);
  G10->AddElement(C ,natoms=3); G10->AddElement(H,natoms=3);

  G4Material* sci = new G4Material(name="sci", density = 1.032*g/cm3, ncomponents=2);
  sci->AddElement(C, natoms=9);
  sci->AddElement(H, natoms=10);

//------------------------------------------
//   World
//------------------------------------------
  G4double w_xy =   610.0*mm;
  G4double w_z  = 12600.0*mm;

  G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* w_mat = nist->FindOrBuildMaterial("G4_He");

//  bool NoMaterial = true ;
//  G4Material* no_mat = nist->FindOrBuildMaterial("G4_Galactic");

//------------------------------------------
//   Si layers
//------------------------------------------

  // Geometrical parameters of Si layers
  G4double l_xy   = 300.000*mm;
  G4double lSi_z  =   0.250*mm;
  G4double lSc_z  =  10.000*mm;
  G4double lG10_z =   1.500*mm;

  // x-pozitiion of Si layers
  G4double l00_x = xPOS_Si0*mm ;
  G4double l01_x = xPOS_Si1*mm ;
  G4double l02_x = xPOS_Si2*mm ;
  G4double l03_x = xPOS_Si3*mm ;
  G4double l04_x = xPOS_Si4*mm ;
  G4double l05_x = xPOS_Si5*mm ;
  G4double l06_x = xPOS_Si6*mm ;
  G4double l07_x = xPOS_Si7*mm ;

  G4double lsc_x = xPOS_Sci*mm ;
  
  // y-pozitiion of Si layers
  G4double l00_y = yPOS_Si0*mm ;
  G4double l01_y = yPOS_Si1*mm ;
  G4double l02_y = yPOS_Si2*mm ;
  G4double l03_y = yPOS_Si3*mm ;
  G4double l04_y = yPOS_Si4*mm ;
  G4double l05_y = yPOS_Si5*mm ;
  G4double l06_y = yPOS_Si6*mm ;
  G4double l07_y = yPOS_Si7*mm ;
  G4double lsc_y = yPOS_Sci*mm ;
  
  // z-pozitiion of Si layers
  G4double l00_z = zPOS_Si0*mm + 0.5 * lSi_z;
  G4double l01_z = zPOS_Si1*mm + 0.5 * lSi_z;
  G4double l02_z = zPOS_Si2*mm + 0.5 * lSi_z;
  G4double l03_z = zPOS_Si3*mm + 0.5 * lSi_z;
  G4double l04_z = zPOS_Si4*mm - 0.5 * lSi_z;
  G4double l05_z = zPOS_Si5*mm - 0.5 * lSi_z;
  G4double l06_z = zPOS_Si6*mm - 0.5 * lSi_z;
  G4double l07_z = zPOS_Si7*mm - 0.5 * lSi_z;

  G4double lsc_z = zPOS_Sci*mm + lSi_z + 50.*mm + 0.5*lSc_z;
  
  // z-pozitiion of PCB for Si layers
  G4double lG0_z = l00_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG1_z = l01_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG2_z = l02_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG3_z = l03_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG4_z = l04_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG5_z = l05_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG6_z = l06_z - 0.5 * lSi_z - 0.5 * lG10_z;
  G4double lG7_z = l07_z - 0.5 * lSi_z - 0.5 * lG10_z;

  //G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* SiSolid = nist->FindOrBuildMaterial("G4_Si");


//------------------------------------------
// H_2 gas, 20 atm.
//------------------------------------------

  G4double lUNIT_z   = 400.0*mm; // length of one TPC unit

  G4double lH2_z =   lUNIT_z*2 ; // 2 anodes (1 cathode in the center)

  // 20 atm --> 1.6347 kg/m3
  // 8 atm for pilot run
  G4Material *H2Gas = new G4Material("H2Gas", 1, 1.008*g/mole, (8.*1.6347/20.)*kg/m3 );

//------------------------------------------
// Be windows
//------------------------------------------
  //G4Material *BeSolid = new G4Material("BeSolid",  4,  9.01218  *g/mole,  1.848 * g/cm3 );
  G4Material* BeSolid = nist->FindOrBuildMaterial("G4_Be");

  G4double rBe_in  = 34.5*mm;
  G4double rBe_out = 35.5*mm;
  G4double dBeTPC  = 20.*mm;

  G4double l20_z = -0.5*lH2_z - dBeTPC - rBe_out;
  G4double l21_z =  0.5*lH2_z + dBeTPC + rBe_out;

//------------------------------------------
// Anode + Cathode + Grid
//------------------------------------------

  G4double ll_xy =  299.000*mm;
  G4double l_Sx  =   15.000*mm;
  G4double l_Sy  =   30.000*mm;
  G4double l_Gx  =  150.000*mm;
  G4double l_Gy  =  150.000*mm;

  //G4Material* AlSolid = nist->FindOrBuildMaterial("G4_Be");
  G4Material* CuSolid = nist->FindOrBuildMaterial("G4_Cu");
  //G4Material* WSolid  = nist->FindOrBuildMaterial("G4_W" );
  G4Material* Kapton  = nist->FindOrBuildMaterial("G4_KAPTON" );

  G4double lKa_z = 0.050*mm;
  G4double lCu_z = 0.010*mm;
  G4double lAl_z = 0.050*mm;
  G4double lGAP_z = 10.0*mm;

  G4double lW_z  = (3.14159265*0.05*0.05) * mm; // grid 1 mm / step, diameter 100um / 1 direction
//  G4double lW_z  = (3.14159265*0.025*0.025) * mm; // grid 1 mm / step, diameter 100um / 1 direction

  G4double l40_z = -0.5*lH2_z + 0.5*lKa_z                ;
  G4double l41_z =  0.5*lH2_z - 0.5*lKa_z                ;

  G4double l50_z = -0.5*lH2_z + lKa_z + 0.5*lCu_z                ;
  G4double l51_z =  0.5*lH2_z - lKa_z - 0.5*lCu_z                ;

  G4double l60_z = -0.5*lH2_z + lKa_z + lCu_z + lGAP_z + 0.5*lW_z                ;
  G4double l61_z =  0.5*lH2_z - lKa_z - lCu_z - lGAP_z - 0.5*lW_z                ;

  G4double l70_z =  0.0*mm; // Just one cathode in the center of TPC

//=====================================================================================

  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // LVs
  G4Box* solidLV00 = new G4Box("LV00", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV01 = new G4Box("LV01", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV02 = new G4Box("LV02", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV03 = new G4Box("LV03", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV04 = new G4Box("LV04", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV05 = new G4Box("LV05", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV06 = new G4Box("LV06", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);
  G4Box* solidLV07 = new G4Box("LV07", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSi_z);

  G4Box* solidLV08 = new G4Box("LV08", 0.5*l_Sx, 0.5*l_Sy, 0.5*lSc_z);

  G4Box* solidLVG0 = new G4Box("LVG0", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG1 = new G4Box("LVG1", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG2 = new G4Box("LVG2", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG3 = new G4Box("LVG3", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG4 = new G4Box("LVG4", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG5 = new G4Box("LVG5", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG6 = new G4Box("LVG6", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);
  G4Box* solidLVG7 = new G4Box("LVG7", 0.5*l_Gx, 0.5*l_Gy, 0.5*lG10_z);

  G4Box* solidLVW0 = new G4Box("LVW0", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW1 = new G4Box("LVW1", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW2 = new G4Box("LVW2", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW3 = new G4Box("LVW3", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW4 = new G4Box("LVW4", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW5 = new G4Box("LVW5", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW6 = new G4Box("LVW6", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);
  G4Box* solidLVW7 = new G4Box("LVW7", 0.5*l_Sx, 0.5*l_Sy, 0.5*lG10_z);

  //G4Box* solidLV10 = new G4Box("LV10", 0.5*l_xy, 0.5*l_xy, 0.5*lH2_z);
  G4Tubs* solidLV10  = new G4Tubs( "LV10" , 0.*mm, 0.5*l_xy, 0.5*lH2_z, 0.*deg, 360.*deg );

  G4Sphere* solidLV20 = new G4Sphere( "LV20", rBe_in, rBe_out, 0.0*deg, 360.0 *deg,  0.0*deg,  90.0*deg);
  G4Sphere* solidLV21 = new G4Sphere( "LV21", rBe_in, rBe_out, 0.0*deg, 360.0 *deg, 90.0*deg, 180.0*deg);

  //G4Box* solidLV40 = new G4Box("LV40", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);
  //G4Box* solidLV41 = new G4Box("LV41", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);
  //G4Box* solidLV50 = new G4Box("LV50", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);
  //G4Box* solidLV51 = new G4Box("LV51", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);
  //G4Box* solidLV60 = new G4Box("LV60", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );
  //G4Box* solidLV61 = new G4Box("LV61", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );
  //G4Box* solidLV70 = new G4Box("LV70", 0.5*ll_xy, 0.5*ll_xy, 0.5*lAl_z);

  G4Tubs* solidLV40  = new G4Tubs( "LV40" , 0.*mm, 0.5*ll_xy, 0.5*lKa_z, 0.*deg, 360.*deg );
  G4Tubs* solidLV41  = new G4Tubs( "LV41" , 0.*mm, 0.5*ll_xy, 0.5*lKa_z, 0.*deg, 360.*deg );
  G4Tubs* solidLV50  = new G4Tubs( "LV50" , 0.*mm, 0.5*ll_xy, 0.5*lCu_z, 0.*deg, 360.*deg );
  G4Tubs* solidLV51  = new G4Tubs( "LV51" , 0.*mm, 0.5*ll_xy, 0.5*lCu_z, 0.*deg, 360.*deg );
  G4Tubs* solidLV60  = new G4Tubs( "LV60" , 0.*mm, 0.5*ll_xy, 0.5*lW_z , 0.*deg, 360.*deg );
  G4Tubs* solidLV61  = new G4Tubs( "LV61" , 0.*mm, 0.5*ll_xy, 0.5*lW_z , 0.*deg, 360.*deg );
  G4Tubs* solidLV70  = new G4Tubs( "LV70" , 0.*mm, 0.5*ll_xy, 0.5*lAl_z, 0.*deg, 360.*deg );

  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00 , SiSolid, "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01 , SiSolid, "LV01");
  G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02 , SiSolid, "LV02");
  G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03 , SiSolid, "LV03");
  G4LogicalVolume* logicLV04 = new G4LogicalVolume(solidLV04 , SiSolid, "LV04");
  G4LogicalVolume* logicLV05 = new G4LogicalVolume(solidLV05 , SiSolid, "LV05");
  G4LogicalVolume* logicLV06 = new G4LogicalVolume(solidLV06 , SiSolid, "LV06");
  G4LogicalVolume* logicLV07 = new G4LogicalVolume(solidLV07 , SiSolid, "LV07");

  G4LogicalVolume* logicLV08 = new G4LogicalVolume(solidLV08 , sci, "LV08");

  G4LogicalVolume* logicLVG0 = new G4LogicalVolume(solidLVG0 , G10, "LVG0");
  G4LogicalVolume* logicLVG1 = new G4LogicalVolume(solidLVG1 , G10, "LVG1");
  G4LogicalVolume* logicLVG2 = new G4LogicalVolume(solidLVG2 , G10, "LVG2");
  G4LogicalVolume* logicLVG3 = new G4LogicalVolume(solidLVG3 , G10, "LVG3");
  G4LogicalVolume* logicLVG4 = new G4LogicalVolume(solidLVG4 , G10, "LVG4");
  G4LogicalVolume* logicLVG5 = new G4LogicalVolume(solidLVG5 , G10, "LVG5");
  G4LogicalVolume* logicLVG6 = new G4LogicalVolume(solidLVG6 , G10, "LVG6");
  G4LogicalVolume* logicLVG7 = new G4LogicalVolume(solidLVG7 , G10, "LVG7");

  G4LogicalVolume* logicLVW0 = new G4LogicalVolume(solidLVW0 , w_mat, "LVW0");
  G4LogicalVolume* logicLVW1 = new G4LogicalVolume(solidLVW1 , w_mat, "LVW1");
  G4LogicalVolume* logicLVW2 = new G4LogicalVolume(solidLVW2 , w_mat, "LVW2");
  G4LogicalVolume* logicLVW3 = new G4LogicalVolume(solidLVW3 , w_mat, "LVW3");
  G4LogicalVolume* logicLVW4 = new G4LogicalVolume(solidLVW4 , w_mat, "LVW4");
  G4LogicalVolume* logicLVW5 = new G4LogicalVolume(solidLVW5 , w_mat, "LVW5");
  G4LogicalVolume* logicLVW6 = new G4LogicalVolume(solidLVW6 , w_mat, "LVW6");
  G4LogicalVolume* logicLVW7 = new G4LogicalVolume(solidLVW7 , w_mat, "LVW7");
//---
  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , H2Gas  , "LV10");
//  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , w_mat  , "LV10");
  G4LogicalVolume* logicLV20 = new G4LogicalVolume(solidLV20 , BeSolid, "LV20");
  G4LogicalVolume* logicLV21 = new G4LogicalVolume(solidLV21 , BeSolid, "LV21");
  G4LogicalVolume* logicLV40 = new G4LogicalVolume(solidLV40 ,  Kapton, "LV40");
  G4LogicalVolume* logicLV41 = new G4LogicalVolume(solidLV41 ,  Kapton, "LV41");
  G4LogicalVolume* logicLV50 = new G4LogicalVolume(solidLV50 , CuSolid, "LV50");
  G4LogicalVolume* logicLV51 = new G4LogicalVolume(solidLV51 , CuSolid, "LV51");
  G4LogicalVolume* logicLV60 = new G4LogicalVolume(solidLV60 , CuSolid, "LV60");
  G4LogicalVolume* logicLV61 = new G4LogicalVolume(solidLV61 , CuSolid, "LV61");
  G4LogicalVolume* logicLV70 = new G4LogicalVolume(solidLV70 , BeSolid, "LV70");

  //G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00 , w_mat, "LV00");
  //G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01 , w_mat, "LV01");
  //G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02 , w_mat, "LV02");
  //G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03 , w_mat, "LV03");
  //G4LogicalVolume* logicLV04 = new G4LogicalVolume(solidLV04 , w_mat, "LV04");
  //G4LogicalVolume* logicLV05 = new G4LogicalVolume(solidLV05 , w_mat, "LV05");
  //G4LogicalVolume* logicLV06 = new G4LogicalVolume(solidLV06 , w_mat, "LV06");
  //G4LogicalVolume* logicLV07 = new G4LogicalVolume(solidLV07 , w_mat, "LV07");
  //G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , w_mat, "LV10");
  //G4LogicalVolume* logicLV20 = new G4LogicalVolume(solidLV20 , w_mat, "LV20");
  //G4LogicalVolume* logicLV21 = new G4LogicalVolume(solidLV21 , w_mat, "LV21");
  //G4LogicalVolume* logicLV40 = new G4LogicalVolume(solidLV40 , w_mat, "LV40");
  //G4LogicalVolume* logicLV41 = new G4LogicalVolume(solidLV41 , w_mat, "LV41");
  //G4LogicalVolume* logicLV50 = new G4LogicalVolume(solidLV50 , w_mat, "LV50");
  //G4LogicalVolume* logicLV51 = new G4LogicalVolume(solidLV51 , w_mat, "LV51");
  //G4LogicalVolume* logicLV60 = new G4LogicalVolume(solidLV60 , w_mat, "LV60");
  //G4LogicalVolume* logicLV63 = new G4LogicalVolume(solidLV63 , w_mat, "LV63");
  //G4LogicalVolume* logicLV70 = new G4LogicalVolume(solidLV70 , w_mat, "LV70");


  G4ThreeVector l00_pos; l00_pos.set( l00_x, l00_y, l00_z ); // Si 1
  G4ThreeVector l01_pos; l01_pos.set( l01_x, l01_y, l01_z ); // Si 2
  G4ThreeVector l02_pos; l02_pos.set( l02_x, l02_y, l02_z ); // Si 3
  G4ThreeVector l03_pos; l03_pos.set( l03_x, l03_y, l03_z ); // Si 4
  G4ThreeVector l04_pos; l04_pos.set( l04_x, l04_y, l04_z ); // Si 5
  G4ThreeVector l05_pos; l05_pos.set( l05_x, l05_y, l05_z ); // Si 6
  G4ThreeVector l06_pos; l06_pos.set( l06_x, l06_y, l06_z ); // Si 7
  G4ThreeVector l07_pos; l07_pos.set( l07_x, l07_y, l07_z ); // Si 8

  G4ThreeVector l08_pos; l08_pos.set( lsc_x, lsc_y, lsc_z ); // Sci

  G4ThreeVector lG0_pos; lG0_pos.set( l00_x, l00_y, lG0_z ); // PCB 1
  G4ThreeVector lG1_pos; lG1_pos.set( l01_x, l01_y, lG1_z ); // PCB 2
  G4ThreeVector lG2_pos; lG2_pos.set( l02_x, l02_y, lG2_z ); // PCB 3
  G4ThreeVector lG3_pos; lG3_pos.set( l03_x, l03_y, lG3_z ); // PCB 4
  G4ThreeVector lG4_pos; lG4_pos.set( l04_x, l04_y, lG4_z ); // PCB 5
  G4ThreeVector lG5_pos; lG5_pos.set( l05_x, l05_y, lG5_z ); // PCB 6
  G4ThreeVector lG6_pos; lG6_pos.set( l06_x, l06_y, lG6_z ); // PCB 7
  G4ThreeVector lG7_pos; lG7_pos.set( l07_x, l07_y, lG7_z ); // PCB 8

  G4ThreeVector l10_pos; l10_pos.set( 0, 0, 0     ); // H2 gas   -- TPC volume
  G4ThreeVector l20_pos; l20_pos.set( 0, 0, l20_z ); // Be       -- entrance window
  G4ThreeVector l21_pos; l21_pos.set( 0, 0, l21_z ); // Be       -- exit window
  G4ThreeVector l40_pos; l40_pos.set( 0, 0, l40_z ); // Kapton 1 -- anode
  G4ThreeVector l41_pos; l41_pos.set( 0, 0, l41_z ); // Kapton 2 -- anode
  G4ThreeVector l50_pos; l50_pos.set( 0, 0, l50_z ); // Cu 1     -- anode
  G4ThreeVector l51_pos; l51_pos.set( 0, 0, l51_z ); // Cu 2     -- anode
  G4ThreeVector l60_pos; l60_pos.set( 0, 0, l60_z ); // W 1      -- grid
  G4ThreeVector l61_pos; l61_pos.set( 0, 0, l61_z ); // W 2      -- grid
  G4ThreeVector l70_pos; l70_pos.set( 0, 0, l70_z ); // Al 1     -- cathode

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  // - Si Trackers
  new G4PVPlacement(0, l00_pos, logicLV00, "LV00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "LV01", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l02_pos, logicLV02, "LV02", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l03_pos, logicLV03, "LV03", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l04_pos, logicLV04, "LV04", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l05_pos, logicLV05, "LV05", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l06_pos, logicLV06, "LV06", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l07_pos, logicLV07, "LV07", logicWorld, false, 0, checkOverlaps);  
  // Sci
  new G4PVPlacement(0, l08_pos, logicLV08, "LV08", logicWorld, false, 0, checkOverlaps);  
  // - PCB for carrier board
  new G4PVPlacement(0, lG0_pos, logicLVG0, "LVG0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG1_pos, logicLVG1, "LVG1", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG2_pos, logicLVG2, "LVG2", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG3_pos, logicLVG3, "LVG3", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG4_pos, logicLVG4, "LVG4", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG5_pos, logicLVG5, "LVG5", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG6_pos, logicLVG6, "LVG6", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG7_pos, logicLVG7, "LVG7", logicWorld, false, 0, checkOverlaps);
  // windows in PCBs
  new G4PVPlacement(0, lG0_pos, logicLVW0, "LVW0", logicLVG0, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG1_pos, logicLVW1, "LVW1", logicLVG1, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG2_pos, logicLVW2, "LVW2", logicLVG2, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG3_pos, logicLVW3, "LVW3", logicLVG3, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG4_pos, logicLVW4, "LVW4", logicLVG4, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG5_pos, logicLVW5, "LVW5", logicLVG5, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG6_pos, logicLVW6, "LVW6", logicLVG6, false, 0, checkOverlaps);
  new G4PVPlacement(0, lG7_pos, logicLVW7, "LVW7", logicLVG7, false, 0, checkOverlaps);
  // - H2 TPC
  new G4PVPlacement(0, l10_pos, logicLV10, "LV10", logicWorld, false, 0, checkOverlaps);
  // - Be windows 
  new G4PVPlacement(0, l20_pos, logicLV20, "LV20", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l21_pos, logicLV21, "LV21", logicWorld, false, 0, checkOverlaps);
  // Kapton -- anode
  new G4PVPlacement(0, l40_pos, logicLV40, "LV40", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l41_pos, logicLV41, "LV41", logicLV10, false, 0, checkOverlaps);
  // Cu -- anode
  new G4PVPlacement(0, l50_pos, logicLV50, "LV50", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l51_pos, logicLV51, "LV51", logicLV10, false, 0, checkOverlaps);
  // W -- grid
  new G4PVPlacement(0, l60_pos, logicLV60, "LV60", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l61_pos, logicLV61, "LV61", logicLV10, false, 0, checkOverlaps);
  // Al -- cathode
  new G4PVPlacement(0, l70_pos, logicLV70, "LV70", logicLV10, false, 0, checkOverlaps);


  fLV00 = logicLV00;
  fLV01 = logicLV01;
  fLV02 = logicLV02;
  fLV03 = logicLV03;
  fLV04 = logicLV04;
  fLV05 = logicLV05;
  fLV06 = logicLV06;
  fLV07 = logicLV07;
  fLV08 = logicLV08;
  fLV10 = logicLV10;

  return physWorld;
}
//------------------------------------------------------------------------------
