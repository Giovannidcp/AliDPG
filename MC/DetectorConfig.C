/*
 * AliDPG - ALICE Experiment Data Preparation Group
 * Detector configuration script
 *
 */

/*****************************************************************/
/*****************************************************************/
/*****************************************************************/

enum EDetector_t {
  kDetectorDefault,
  kDetectorMuon,
  kDetectorPhosOnly,
  kDetectorNoZDC,
  kDetectorRun3,
  kDetectorCustom,
  kNDetectors
};

const Char_t *DetectorName[kNDetectors] = {
  "Default",
  "Muon",
  "PhosOnly",
  "NoZDC",
  "Run3",
  "Custom"
};

/*****************************************************************/
/*****************************************************************/
/*****************************************************************/

enum EMagnet_t {
  kMagnetDefault,
  kMagnetOff,
  kMagnet5kG,
  kNMagnets
};

const Char_t *MagnetName[kNMagnets] = {
  "Default",
  "Off",
  "5kG"
};

/*****************************************************************/
/*****************************************************************/
/*****************************************************************/

Int_t iABSO   = 1;
Int_t iACORDE = 1;
Int_t iAD     = 1;
Int_t iDIPO   = 1;
Int_t iEMCAL  = 1;
Int_t iFMD    = 1;
Int_t iFRAME  = 1;
Int_t iHALL   = 1;
Int_t iITS    = 1;
Int_t iMAG    = 1;
Int_t iMUON   = 1;
Int_t iPHOS   = 1;
Int_t iPIPE   = 1;
Int_t iPMD    = 1;
Int_t iHMPID  = 1;
Int_t iSHIL   = 1;
Int_t iT0     = 1;
Int_t iTOF    = 1;
Int_t iTPC    = 1;
Int_t iTRD    = 1;
Int_t iVZERO  = 1;
Int_t iZDC    = 1;
Int_t iMFT    = 0;
Int_t iFIT    = 0;
  
void DetectorDefault();
void DetectorMuon();
void DetectorRun3();
void DetectorInit(Int_t tag);
void DetectorInitRun3(Int_t tag);

/*****************************************************************/

void
DetectorConfig(Int_t tag)
{

  printf(">>>>> DetectorConfig: %s \n", DetectorName[tag]);

  switch (tag) {

    // kDetectorDefault
  case kDetectorDefault:
  case kDetectorPhosOnly:
    DetectorDefault();
    break;
    
    // kDetectorMuon
  case kDetectorMuon:
    DetectorMuon();
    break;
    
    // kDetectorNoZDC
  case kDetectorNoZDC:
    DetectorDefault();
    iZDC = 0;
    break;

    // kDetectorRun3
  case kDetectorRun3:
    DetectorRun3();
    break;
    
    // kDetectorCustom
  case kDetectorCustom:
    if ((gROOT->LoadMacro("DetectorCustom.C")) != 0) {
      printf("ERROR: cannot find DetectorCustom.C\n");
      abort();
      return;
    }
    gROOT->ProcessLine("DetectorCustom();");
    break;
    
  }

  if( tag == kDetectorRun3 )
    DetectorInitRun3(tag);
  else
    DetectorInit(tag);
}

/*****************************************************************/

void
DetectorDefault()
{
  /*
   * DetectorDefault
   * configures the detectors to the default 
   * configuration automatically according to year/period
   *
   */
  
  Int_t year = atoi(gSystem->Getenv("CONFIG_YEAR"));
  UInt_t mask = strtol(gSystem->Getenv("CONFIG_DETECTORMASK"), 0, 16);

  iABSO   = 1;
  iACORDE = 1;
  iAD     = year < 2015 ? 0 : 1;
  iDIPO   = 1;
  iEMCAL  = 1;
  iFMD    = 1;
  iFRAME  = 1;
  iHALL   = 1;
  iITS    = 1;
  iMAG    = 1;
  iMUON   = 1;
  iPHOS   = 1;
  iPIPE   = 1;
  iPMD    = 1;
  iHMPID  = 1;
  iSHIL   = 1;
  iT0     = 1;
  iTOF    = 1;
  iTPC    = 1;
  iTRD    = 1;
  iVZERO  = 1;
  iZDC    = mask & (1 << AliDAQ::DetectorID("ZDC")); // ZDC disabled if not in readout

}
  
/*****************************************************************/

void
DetectorMuon()
{
  /*
   * DetectorMuon
   * configures the detectors to the Muon 
   * configuration automatically according to year/period
   *
   */
  
  Int_t year = atoi(gSystem->Getenv("CONFIG_YEAR"));
  
  iABSO   = 1;
  iACORDE = 0;
  iAD     = year < 2015 ? 0 : 1;
  iDIPO   = 1;
  iEMCAL  = 0;
  iFMD    = 1;
  iFRAME  = 1;
  iHALL   = 1;
  iITS    = 1;
  iMAG    = 1;
  iMUON   = 1;
  iPHOS   = 0;
  iPIPE   = 1;
  iPMD    = 0;
  iHMPID  = 0;
  iSHIL   = 1;
  iT0     = 1;
  iTOF    = 0;
  iTPC    = 0;
  iTRD    = 0;
  iVZERO  = 1;
  iZDC    = 0;

}
  
/*****************************************************************/

void DetectorRun3()
{
  /*
   * Detector configuration for Run3 MC
   *
   */
  
  Int_t year = atoi(gSystem->Getenv("CONFIG_YEAR"));
  UInt_t mask = strtol(gSystem->Getenv("CONFIG_DETECTORMASK"), 0, 16);

  iABSO   = 1;
  iACORDE = 0;
  iAD     = 0;
  iDIPO   = 1;
  iEMCAL  = 1;
  iFMD    = 0;
  iFRAME  = 1;
  iHALL   = 1;
  iITS    = 1;
  iMAG    = 1;
  iMUON   = 1;
  iPHOS   = 1;
  iPIPE   = 1;
  iPMD    = 0;
  iHMPID  = 1;
  iSHIL   = 1;
  iT0     = 0;
  iTOF    = 1;
  iTPC    = 1;
  iTRD    = 1;
  iVZERO  = 0;
  iZDC    = 1;
  iMFT    = 0; // removed MFT for the time being
  iFIT    = 1;

}

/*****************************************************************/

void
DetectorInit(Int_t tag)
{
  /*
   * DetectorInit
   * initialise the detectors to the default 
   * configuration automatically according to year/period
   *
   */
  
  Int_t year = atoi(gSystem->Getenv("CONFIG_YEAR"));


  //=================== Alice BODY parameters =============================
  AliBODY *BODY = new AliBODY("BODY", "Alice envelop");
  
  
  if (iMAG)
    {
      //=================== MAG parameters ============================
      // --- Start with Magnet since detector layouts may be depending ---
      // --- on the selected Magnet dimensions ---
      AliMAG *MAG = new AliMAG("MAG", "Magnet");
    }
  

  if (iABSO)
    {
      //=================== ABSO parameters ============================
      AliABSO *ABSO = new AliABSOv3("ABSO", "Muon Absorber");
    }

  if (iDIPO)
    {
      //=================== DIPO parameters ============================

      AliDIPO *DIPO = new AliDIPOv3("DIPO", "Dipole version 3");
    }

  if (iHALL)
    {
      //=================== HALL parameters ============================

      AliHALL *HALL = new AliHALLv3("HALL", "Alice Hall");
    }


  if (iFRAME)
    {
      //=================== FRAME parameters ============================

      if (year < 2015) {
 	AliFRAMEv2 *FRAME = new AliFRAMEv2("FRAME", "Space Frame");
	FRAME->SetHoles(1);
      }
      else {
 	AliFRAMEv3 *FRAME = new AliFRAMEv3("FRAME", "Space Frame");
	FRAME->SetHoles(1);
      }
    }

  if (iSHIL)
    {
      //=================== SHIL parameters ============================

      AliSHIL *SHIL = new AliSHILv3("SHIL", "Shielding Version 3");
    }


  if (iPIPE)
    {
      //=================== PIPE parameters ============================

      AliPIPE *PIPE = new AliPIPEv3("PIPE", "Beam Pipe");
    }
 
  if (iITS)
    {
      //=================== ITS parameters ============================
      
      AliITS *ITS  = new AliITSv11("ITS","ITS v11");
      if( tag == kDetectorPhosOnly)
	ITS->DisableStepManager();
    }

  if (iTPC)
    {
      //============================ TPC parameters =====================

      AliTPC *TPC = new AliTPCv2("TPC", "Default");
      if (isGeant4 || isFluka) 
	TPC->SetPrimaryIonisation(1);
      if( tag == kDetectorPhosOnly)
	TPC->DisableStepManager();
    }


  if (iTOF) {
    //=================== TOF parameters ============================

    AliTOF *TOF = new AliTOFv6T0("TOF", "normal TOF");
    if( tag == kDetectorPhosOnly)
      TOF->DisableStepManager();
  }


  if (iHMPID)
    {
      //=================== HMPID parameters ===========================

      AliHMPID *HMPID = new AliHMPIDv3("HMPID", "normal HMPID");
      if( tag == kDetectorPhosOnly)
	HMPID->DisableStepManager();
    }


  if (iZDC)
    {
      //=================== ZDC parameters ============================

      AliZDC *ZDC;
      if (year == 2010) {
	ZDC = new AliZDCv3("ZDC", "normal ZDC");
	ZDC->SetSpectatorsTrack();
        ZDC->SetLumiLength(0.);
      }
      else if (year < 2015) {
	ZDC = new AliZDCv3("ZDC", "normal ZDC");
	//Collimators aperture
	ZDC->SetVCollSideCAperture(0.85);
	ZDC->SetVCollSideCCentre(0.);
	ZDC->SetVCollSideAAperture(0.75);
	ZDC->SetVCollSideACentre(0.);
	//Detector position
	ZDC->SetYZNC(1.6);
	ZDC->SetYZNA(1.6);
	ZDC->SetYZPC(1.6);
	ZDC->SetYZPA(1.6);
      }
      else {
	ZDC = new AliZDCv4("ZDC", "normal ZDC");
	ZDC->SetLumiLength(0.);
	ZDC->SetVCollSideCAperture(2.8);
	ZDC->SetVCollSideCApertureNeg(2.8);
      }
      if( tag == kDetectorPhosOnly)
	ZDC->DisableStepManager();
    }

  if (iTRD)
    {
      //=================== TRD parameters ============================

      AliTRDgeometry *geoTRD;
      if (isGeant4) {
	AliTRDtestG4 *TRD = new AliTRDtestG4("TRD", "TRD slow simulator");
	TRD->SetScaleG4(1.11);
	if( tag == kDetectorPhosOnly) TRD->DisableStepManager();
	geoTRD = TRD->GetGeometry();
      }
      else 
      {
	AliTRD *TRD = new AliTRDv1("TRD", "TRD slow simulator");
	if( tag == kDetectorPhosOnly) TRD->DisableStepManager();
	geoTRD = TRD->GetGeometry();
      }
      
      // Partial geometry: modules at 0,1,7,8,9,16,17
      // starting at 3h in positive direction

      if ((year == 2010) || (year == 2009)) {
	geoTRD->SetSMstatus(2,0);
	geoTRD->SetSMstatus(3,0);
	geoTRD->SetSMstatus(4,0);
	geoTRD->SetSMstatus(5,0);
	geoTRD->SetSMstatus(6,0);
	geoTRD->SetSMstatus(11,0);
	geoTRD->SetSMstatus(12,0);
	geoTRD->SetSMstatus(13,0);
	geoTRD->SetSMstatus(14,0);
	geoTRD->SetSMstatus(15,0);
	geoTRD->SetSMstatus(16,0);	
      }
      else if (year == 2011) {
	geoTRD->SetSMstatus(2,0);
	geoTRD->SetSMstatus(3,0);
	geoTRD->SetSMstatus(4,0);
	geoTRD->SetSMstatus(5,0);
	geoTRD->SetSMstatus(6,0);
	geoTRD->SetSMstatus(12,0);
	geoTRD->SetSMstatus(13,0);
	geoTRD->SetSMstatus(14,0);
      }
      else if ((year == 2012) || (year ==2013)) {
	geoTRD->SetSMstatus(4,0);
	geoTRD->SetSMstatus(5,0);
	geoTRD->SetSMstatus(12,0);
	geoTRD->SetSMstatus(13,0);
	geoTRD->SetSMstatus(14,0);
      }
    }
  
  if (iFMD)
    {
      //=================== FMD parameters ============================
      
      AliFMD *FMD = new AliFMDv1("FMD", "normal FMD");
      if( tag == kDetectorPhosOnly)
	FMD->DisableStepManager();
    }

  if (iMUON)
    {
      //=================== MUON parameters ===========================
      // New MUONv1 version (geometry defined via builders)
      AliMUON *MUON = new AliMUONv1("MUON", "default");
      // activate trigger efficiency by cells
      MUON->SetTriggerEffCells(1); // backward compatibility
      MUON->SetTriggerResponseV1(2); // backward compatibility
      if( tag == kDetectorPhosOnly)
	MUON->DisableStepManager();
    }

  if (iPHOS)
    {
      //=================== PHOS parameters ===========================

      if (year < 2015) {
	AliPHOS *PHOS = new AliPHOSv1("PHOS", "noCPV_Modules123");
      }
      else {
	AliPHOS *PHOS = new AliPHOSv1("PHOS", "Run2");
      }
	
    }


  if (iPMD)
    {
      //=================== PMD parameters ============================

      AliPMD *PMD = new AliPMDv1("PMD", "normal PMD");
      if( tag == kDetectorPhosOnly)
	PMD->DisableStepManager();
    }

  if (iT0)
    {
      //=================== T0 parameters ============================
      AliT0 *T0 = new AliT0v1("T0", "T0 Detector");
      if( tag == kDetectorPhosOnly)
	  T0->DisableStepManager();
    }

  if (iEMCAL)
    {
      //=================== EMCAL parameters ============================

      //Cannot use EMCAL as name since it collides with EMCAL namespace definition
      AliEMCAL *EMCAL_DET = new AliEMCALv2("EMCAL", "EMCAL_COMPLETE12SMV1_DCAL_8SM");
      // by default Run2 configuration name but the proper geometry name is taken 
      // automatically depending on the anchor run 
      // 2010 - 4 SM, 2011 - 10 SM, 2012 - 12 SM, >2014 - 20 SM
      
      if( tag == kDetectorPhosOnly)
	EMCAL_DET->DisableStepManager();
      
    }

  if (iACORDE)
    {
      //=================== ACORDE parameters ============================

      AliACORDE *ACORDE = new AliACORDEv1("ACORDE", "normal ACORDE");
      if( tag == kDetectorPhosOnly)
	ACORDE->DisableStepManager();
    }

  if (iVZERO)
    {
      //=================== ACORDE parameters ============================
      
      AliVZERO *VZERO = new AliVZEROv7("VZERO", "normal VZERO");
      if( tag == kDetectorPhosOnly)
	VZERO->DisableStepManager();
    }  

  if (iAD){
     if (!isFluka){ // does not work for now with Fluka
        //=================== AD parameters ============================
        AliAD *AD = new AliADv1("AD", "normal AD");
        if( tag == kDetectorPhosOnly)
        AD->DisableStepManager();
     }
     else {
	    Printf("AD is disabled, as we are using Fluka");
     }
  }

}

/*****************************************************************/

void DetectorInitRun3(Int_t tag)
{
  /*
   * DetectorInit
   * initialise the detectors to the default 
   * configuration automatically according to year/period
   *
   */
  
  Int_t year = atoi(gSystem->Getenv("CONFIG_YEAR"));


  //=================== Alice BODY parameters =============================
  AliBODY *BODY = new AliBODY("BODY", "Alice envelop");
  
  
  if (iMAG)
    {
      //=================== MAG parameters ============================
      // --- Start with Magnet since detector layouts may be depending ---
      // --- on the selected Magnet dimensions ---
      AliMAG *MAG = new AliMAG("MAG", "Magnet");
    }
  

  if (iABSO)
    {
      //=================== ABSO parameters ============================
      AliABSO *ABSO = new AliABSOv3("ABSO", "Muon Absorber");
    }

  if (iDIPO)
    {
      //=================== DIPO parameters ============================

      AliDIPO *DIPO = new AliDIPOv3("DIPO", "Dipole version 3");
    }

  if (iHALL)
    {
      //=================== HALL parameters ============================

      AliHALL *HALL = new AliHALLv3("HALL", "Alice Hall");
    }


  if (iFRAME)
    {
      //=================== FRAME parameters ============================

      if (year < 2015) {
 	AliFRAMEv2 *FRAME = new AliFRAMEv2("FRAME", "Space Frame");
	FRAME->SetHoles(1);
      }
      else {
 	AliFRAMEv3 *FRAME = new AliFRAMEv3("FRAME", "Space Frame");
	FRAME->SetHoles(1);
      }
    }

  if (iSHIL)
    {
      //=================== SHIL parameters ============================

      AliSHIL *SHIL = new AliSHILv3("SHIL", "Shielding Version 3");
    }


  if (iPIPE)
    {
      //=================== PIPE parameters ============================

      AliPIPE *PIPE = new AliPIPEv3("PIPE", "Beam Pipe");
    }
 
  if (iITS)
    {
      //=================== ITS parameters ============================
      //      CreateITSUv2ALP3();
      gROOT->ProcessLine(".x $ALICE_ROOT/ITSMFT/ITS/itsuTestBench/CreateITSUv2ALP3.C");
    }

  if (iTPC)
    {
      //============================ TPC parameters =====================

      AliTPC *TPC = new AliTPCv2("TPC", "Default");
      if (isGeant4) TPC->SetPrimaryIonisation(1);
    }


  if (iTOF)
    {
    //=================== TOF parameters ============================

    AliTOF *TOF = new AliTOFv6T0("TOF", "normal TOF");
    }


  if (iHMPID)
    {
      //=================== HMPID parameters ===========================

      AliHMPID *HMPID = new AliHMPIDv3("HMPID", "normal HMPID");
    }


  if (iZDC)
    {
      //=================== ZDC parameters ============================

      AliZDC *ZDC;
      if (year == 2010) {
	ZDC = new AliZDCv3("ZDC", "normal ZDC");
	ZDC->SetSpectatorsTrack();
        ZDC->SetLumiLength(0.);
      }
      else if (year < 2015) {
	ZDC = new AliZDCv3("ZDC", "normal ZDC");
	//Collimators aperture
	ZDC->SetVCollSideCAperture(0.85);
	ZDC->SetVCollSideCCentre(0.);
	ZDC->SetVCollSideAAperture(0.75);
	ZDC->SetVCollSideACentre(0.);
	//Detector position
	ZDC->SetYZNC(1.6);
	ZDC->SetYZNA(1.6);
	ZDC->SetYZPC(1.6);
	ZDC->SetYZPA(1.6);
      }
      else {
	ZDC = new AliZDCv4("ZDC", "normal ZDC");
	ZDC->SetLumiLength(0.);
	ZDC->SetVCollSideCAperture(2.8);
	ZDC->SetVCollSideCApertureNeg(2.8);
      }
    }

  if (iTRD)
    {
      //=================== TRD parameters ============================

      AliTRDgeometry *geoTRD;
      if (isGeant4) {
	AliTRDtestG4 *TRD = new AliTRDtestG4("TRD", "TRD slow simulator");
	TRD->SetScaleG4(1.11);
	geoTRD = TRD->GetGeometry();
      }
      else 
      {
	AliTRD *TRD = new AliTRDv1("TRD", "TRD slow simulator");
	geoTRD = TRD->GetGeometry();
      }
    }
  
  if (iMUON)
    {
      //=================== MUON parameters ===========================
      // New MUONv1 version (geometry defined via builders)
      AliMUON *MUON = new AliMUONv1("MUON", "default");
      // activate trigger efficiency by cells
      MUON->SetTriggerEffCells(1); // backward compatibility
      MUON->SetTriggerResponseV1(2); // backward compatibility
    }

  if (iPHOS)
    {
      //=================== PHOS parameters ===========================

      if (year < 2015) {
	AliPHOS *PHOS = new AliPHOSv1("PHOS", "noCPV_Modules123");
      }
      else {
	AliPHOS *PHOS = new AliPHOSv1("PHOS", "Run2");
      }
	
    }

  if (iEMCAL)
    {
      //=================== EMCAL parameters ============================

      //Cannot use EMCAL as name since it collides with EMCAL namespace definition
      AliEMCAL *EMCAL_DET = new AliEMCALv2("EMCAL", "EMCAL_COMPLETE12SMV1_DCAL_8SM");
      // by default Run2 configuration name but the proper geometry name is taken 
      // automatically depending on the anchor run 
      // 2010 - 4 SM, 2011 - 10 SM, 2012 - 12 SM, >2014 - 20 SM
      
    }

  if (iACORDE)
    {
      //=================== ACORDE parameters ============================

      AliACORDE *ACORDE = new AliACORDEv1("ACORDE", "normal ACORDE");
    }

  if (iMFT)
    {
      AliMFT *MFT = new AliMFT("MFT", "normal MFT");
    }

  if(iFIT)
    {
      AliFIT *fit = new AliFITv7("FIT","FIT");
    } 

}
