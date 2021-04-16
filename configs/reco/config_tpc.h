
int MY_EVTS = 500;

//--- Beam events
bool ADD_BEAM = false;
double BeamFrequency = 2.0; // MHz

//--- Anodes positions
double Z_anode_1 = -400.;
double Z_anode_2 =  400.;


//--- Calibration data
double Calib   = 200./151.;
int Ne_MAX = 100; // max nubmer of e- per substep
int Ll_MAX = 40 ; // um, length of substep

double I_av = 36.5*0.001*0.001; // MeV --> 36.5 eV to create e-ion pair
double W1 = 4.0*0.001; // mm/ns

//--- Shapung
bool ADD_SHAPING = true;

//--- Diffusion
bool  ADD_DIFFUSION = true;
double DIFF_P =0.06; // parameter is obtained from German Korolev (PNPI)
double DIFF_L =0.08; // parameter is obtained from German Korolev (PNPI)

//--- Noise
bool ADD_NOISE = true;

//--- Draw lact event 
bool DRAW_LAST   = true;

//--- Write ASCII
bool WRITE_ASCII = true;
int  CH_WRITE    = 1;
int  CH_START    = 1;
int  CH_STOP     = 501;
