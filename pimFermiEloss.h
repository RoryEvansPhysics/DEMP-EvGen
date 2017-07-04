#include <iostream>
#include "TRandom.h"
#include "TRandom2.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"

using namespace std;

int fNEvents;
int fNFile;
double fElectron_Kin_Col_GeV;
double fElectron_Kin_Col;
double fRand;


// --------------------------------------------------------------------------------------
TRandom2 *fRandom;

TFile *f;
TTree t1("t1","Pion Form Fator Study");
//TTree t1;

double fLumi;
double fuBcm2;
double fPI;
double fDEG2RAD;
double fEBeam;
double fScatElec_Theta_I;
double fScatElec_Theta_F;
double fPion_Theta_I;
double fPion_Theta_F;
double fScatElec_E_Hi;
double fScatElec_E_Lo;
double fPSF;

bool print;
bool allset;
bool kCalcFermi;
bool kCalcBremss;
bool kCalcIon;
bool kSConserve;

int fWLessShell;
int fWLess1P9;
int fWSqNeg;
int fSDiff;
int fLundRecorded;
int fNRecorded;
int fNGenerated;

double fMandSConserve;
double fTop_Pion_Mom;
double fBot_Pion_Mom;
double fPion_Mom_Same;
double fEnergyConserve;
double fXMomConserve;
double fYMomConserve;
double fZMomConserve;
double fXMomConserve_RF;
double fYMomConserve_RF;
double fZMomConserve_RF;

double fDiff;
double fRatio;
double fPion_Alpha;
double fPion_Beta;
double fS_I_RF;
double fS_F_RF;
double fS_I_Col;
double fS_F_Col;
double fS_I_RF_GeV;
double fS_F_RF_GeV;
double fS_I_Col_GeV;
double fS_F_Col_GeV;

double fProton_Energy_Col;
double fProton_Mom_Col;
double fProton_Theta_Col;
double fProton_Phi_Col;
double fProton_MomZ_Col;
double fProton_MomX_Col;
double fProton_MomY_Col;
double fProton_Energy_Col_GeV;
double fProton_Mom_Col_GeV;
double fProton_MomX_Col_GeV;
double fProton_MomY_Col_GeV;
double fProton_MomZ_Col_GeV;

double fTarget_Energy_Col;
double fTarget_Mom_Col;
double fTarget_Theta_Col;
double fTarget_Phi_Col;
double fTarget_MomZ_Col;
double fTarget_MomX_Col;
double fTarget_MomY_Col;
double fTarget_Energy_Col_GeV;
double fTarget_Mom_Col_GeV;
double fTarget_MomX_Col_GeV;
double fTarget_MomY_Col_GeV;
double fTarget_MomZ_Col_GeV;

double fTarget_Pol0_Col;
double fTarget_PolX_Col;
double fTarget_PolY_Col;
double fTarget_PolZ_Col;
double fTarget_Pol0_RF;
double fTarget_PolX_RF;
double fTarget_PolY_RF;
double fTarget_PolZ_RF;

double fBetaX_Col_RF;
double fBetaY_Col_RF;
double fBetaZ_Col_RF;
double fBeta_Col_RF;
double fGamma_Col_RF;

double fProton_MomX_RF;
double fProton_MomY_RF;
double fProton_MomZ_RF;
double fProton_Mom_RF;
double fProton_Energy_RF;
double fProton_MomX_RF_GeV;
double fProton_MomY_RF_GeV;
double fProton_MomZ_RF_GeV;
double fProton_Mom_RF_GeV;
double fProton_Energy_RF_GeV;

double fScatElec_Angle;    
double fScatElec_Alpha_RF;    
double fScatElec_Beta_RF;

double fVertex_X;
double fVertex_Y;
double fVertex_Z;
double fProton_Kin_Col_GeV;
double fElectron_Mass;
double fElectron_Mass_GeV;
double fProton_Mass;
double fProton_Mass_GeV;
double fNeutron_Mass;
double fNeutron_Mass_GeV;
double fPion_Mass;
double fPion_Mass_GeV;
double fPiion_Phi;
double fAlpha;
double fPi;
double fMom_Ratio;
double fMom_Dif;
double fPionEnergyCMLess;
double fSNotEqual;
double fMode_Epsi;
double fRecoilProton_Mass;
double fRecoilProton_Mass_GeV;

double fElectron_Energy_Col;
double fElectron_MomZ_Col;
double fElectron_MomX_Col;
double fElectron_MomY_Col;
double fElectron_Theta_Col;
double fElectron_Phi_Col;
double fElectron_Mom_Col;
double fElectron_Energy_Col_GeV;
double fElectron_Mom_Col_GeV;
double fElectron_MomX_Col_GeV;
double fElectron_MomY_Col_GeV;
double fElectron_MomZ_Col_GeV;
double fElectronEnergyLess;
double fElectronThetaLess;
double fRadiation_Lenght_Air;
double fElectron_Targ_Thickness;
double fElectron_Targ_Thickness_RadLen;
double fElectron_Targ_BT;
double fElectron_Targ_Bremss_Loss;
double fElectron_Targ_Ion_Loss;
double fElectron_Air_Thickness;
double fElectron_Air_Thickness_RadLen;
double fElectron_Air_BT;
double fElectron_Air_Bremss_Loss;
double fElectron_Air_Ion_Loss;
double fElectron_Corrected_Energy_Col;
double fElectron_Corrected_Mom_Col;
double fElectron_Corrected_MomX_Col;
double fElectron_Corrected_MomY_Col;
double fElectron_Corrected_MomZ_Col;
double fElectron_Corrected_Theta_Col;
double fElectron_Corrected_Phi_Col;
double fElectron_Delta_Mom_Col;
double fElectron_Corrected_Energy_Col_GeV;
double fElectron_Corrected_Mom_Col_GeV;
double fElectron_Corrected_MomX_Col_GeV;
double fElectron_Corrected_MomY_Col_GeV;
double fElectron_Corrected_MomZ_Col_GeV;
double fElectron_Delta_Mom_Col_GeV;

double fScatElec_Energy_Col;
double fScatElec_MomZ_Col;
double fScatElec_MomX_Col;
double fScatElec_MomY_Col;
double fScatElec_Theta_Col;
double fScatElec_Phi_Col;
double fScatElec_Mom_Col;
double fScatElec_Energy_Col_GeV;
double fScatElec_Mom_Col_GeV;
double fScatElec_MomX_Col_GeV;
double fScatElec_MomY_Col_GeV;
double fScatElec_MomZ_Col_GeV;
double fScatElecEnergyLess;
double fScatElecThetaLess;
double fScatElec_Targ_Thickness;
double fScatElec_Targ_Thickness_RadLen;
double fScatElec_Targ_BT;
double fScatElec_Targ_Bremss_Loss;
double fScatElec_Targ_Ion_Loss;
double fScatElec_Air_Thickness;
double fScatElec_Air_Thickness_RadLen;
double fScatElec_Air_BT;
double fScatElec_Air_Bremss_Loss;
double fScatElec_Air_Ion_Loss;
double fScatElec_Corrected_Energy_Col;
double fScatElec_Corrected_Mom_Col;
double fScatElec_Corrected_MomX_Col;
double fScatElec_Corrected_MomY_Col;
double fScatElec_Corrected_MomZ_Col;
double fScatElec_Corrected_Theta_Col;
double fScatElec_Corrected_Phi_Col;
double fScatElec_Delta_Mom_Col;
double fScatElec_Corrected_Energy_Col_GeV;
double fScatElec_Corrected_Mom_Col_GeV;
double fScatElec_Corrected_MomX_Col_GeV;
double fScatElec_Corrected_MomY_Col_GeV;
double fScatElec_Corrected_MomZ_Col_GeV;
double fScatElec_Delta_Mom_Col_GeV;

double fPion_Targ_Thickness;
double fPion_Targ_Thickness_RadLen;
double fPion_Targ_BT;
double fPion_Targ_Bremss_Loss;
double fPion_Targ_Ion_Loss;
double fPion_Air_Thickness;
double fPion_Air_Thickness_RadLen;
double fPion_Air_BT;
double fPion_Air_Bremss_Loss;
double fPion_Air_Ion_Loss;
double fPion_Theta_Col;
double fPion_Phi_Col;
double fPion_Energy_Col;
double fPion_Mom_Col;
double fPion_MomZ_Col;
double fPion_MomX_Col;
double fPion_MomY_Col;
double fPion_Energy_Col_GeV;
double fPion_Mom_Col_GeV;
double fPion_MomX_Col_GeV;
double fPion_MomY_Col_GeV;
double fPion_MomZ_Col_GeV;
double fPion_Corrected_Theta_Col;
double fPion_Corrected_Phi_Col;
double fPion_Corrected_Energy_Col;
double fPion_Corrected_Mom_Col;
double fPion_Corrected_MomX_Col;
double fPion_Corrected_MomY_Col;
double fPion_Corrected_MomZ_Col;
double fPion_Delta_Mom_Col;
double fPion_Corrected_Energy_Col_GeV;
double fPion_Corrected_Mom_Col_GeV;
double fPion_Corrected_MomX_Col_GeV;
double fPion_Corrected_MomY_Col_GeV;
double fPion_Corrected_MomZ_Col_GeV;
double fPion_Delta_Mom_Col_GeV;

double fNeutron_Targ_Thickness;
double fNeutron_Targ_Thickness_RadLen;
double fNeutron_Targ_BT;
double fNeutron_Targ_Bremss_Loss;
double fNeutron_Targ_Ion_Loss;
double fNeutron_Air_Thickness;
double fNeutron_Air_Thickness_RadLen;
double fNeutron_Air_BT;
double fNeutron_Air_Bremss_Loss;
double fNeutron_Air_Ion_Loss;
double fNeutron_Theta_Col;
double fNeutron_Phi_Col;
double fNeutron_Energy_Col;
double fNeutron_Mom_Col;
double fNeutron_MomZ_Col;
double fNeutron_MomX_Col;
double fNeutron_MomY_Col;
double fNeutron_Energy_Col_GeV;
double fNeutron_Mom_Col_GeV;
double fNeutron_MomX_Col_GeV;
double fNeutron_MomY_Col_GeV;
double fNeutron_MomZ_Col_GeV;
double fNeutron_Corrected_Theta_Col;
double fNeutron_Corrected_Phi_Col;
double fNeutron_Corrected_Energy_Col;
double fNeutron_Corrected_Mom_Col;
double fNeutron_Corrected_MomX_Col;
double fNeutron_Corrected_MomY_Col;
double fNeutron_Corrected_MomZ_Col;
double fNeutron_Delta_Mom_Col;
double fNeutron_Corrected_Energy_Col_GeV;
double fNeutron_Corrected_Mom_Col_GeV;
double fNeutron_Corrected_MomX_Col_GeV;
double fNeutron_Corrected_MomY_Col_GeV;
double fNeutron_Corrected_MomZ_Col_GeV;
double fNeutron_Delta_Mom_Col_GeV;

double fRecoilProton_Energy_RF;
double fRecoilProton_Mom_RF;
double fRecoilProton_MomX_RF;
double fRecoilProton_MomY_RF;
double fRecoilProton_MomZ_RF;
double fRecoilProton_Energy_RF_GeV;
double fRecoilProton_Mom_RF_GeV;
double fRecoilProton_MomX_RF_GeV;
double fRecoilProton_MomY_RF_GeV;
double fRecoilProton_MomZ_RF_GeV;
double fRecoilProton_Theta_RF;
double fRecoilProton_Phi_RF;

double fRecoilProton_Targ_Thickness;
double fRecoilProton_Targ_Thickness_RadLen;
double fRecoilProton_Targ_BT;
double fRecoilProton_Targ_Bremss_Loss;
double fRecoilProton_Targ_Ion_Loss;
double fRecoilProton_Air_Thickness;
double fRecoilProton_Air_Thickness_RadLen;
double fRecoilProton_Air_BT;
double fRecoilProton_Air_Bremss_Loss;
double fRecoilProton_Air_Ion_Loss;
double fRecoilProton_Theta_Col;
double fRecoilProton_Phi_Col;
double fRecoilProton_Energy_Col;
double fRecoilProton_Mom_Col;
double fRecoilProton_MomZ_Col;
double fRecoilProton_MomX_Col;
double fRecoilProton_MomY_Col;
double fRecoilProton_Energy_Col_GeV;
double fRecoilProton_Mom_Col_GeV;
double fRecoilProton_MomX_Col_GeV;
double fRecoilProton_MomY_Col_GeV;
double fRecoilProton_MomZ_Col_GeV;
double fRecoilProton_Corrected_Theta_Col;
double fRecoilProton_Corrected_Phi_Col;
double fRecoilProton_Corrected_Energy_Col;
double fRecoilProton_Corrected_Mom_Col;
double fRecoilProton_Corrected_MomX_Col;
double fRecoilProton_Corrected_MomY_Col;
double fRecoilProton_Corrected_MomZ_Col;
double fRecoilProton_Delta_Mom_Col;
double fRecoilProton_Corrected_Energy_Col_GeV;
double fRecoilProton_Corrected_Mom_Col_GeV;
double fRecoilProton_Corrected_MomX_Col_GeV;
double fRecoilProton_Corrected_MomY_Col_GeV;
double fRecoilProton_Corrected_MomZ_Col_GeV;
double fRecoilProton_Delta_Mom_Col_GeV;

/* double  fMaximumLabSigma; */
/* double  fFraction_MaximumLabSigma; */
/* double  fZA_Qsq_Sigma_Max; */
/* double  fZA_W_Sigma_Max; */
/* double  fZA_ScatElec_Theta_Sigma_Max; */
/* double  fZA_ScatElec_Energy_Sigma_Max; */
/* double  fZA_Epsilon_Sigma_Max; */
/* double  fZA_X_Sigma_Max; */
/* double  fZA_T_Sigma_Max; */
/* double  fZASigma3_Max; */
/* double  fZA_PiqVec_Theta_RF_Sigma_Max; */
/* double  fPion_Theta_CM_Max; */
/* double  fQsq_Steps; */
/* double  fScatElec_Mom_Steps; */
/* double  fScatElec_Energy_Steps; */
/* double  fZASigmaPara_Max; */

double fSSAsym;
double fSineAsym;
double fInvariantDif;
double fT_GeV;
double fProton_Kin_Col;
double fQsq_Value;
double fQsq_Dif;
double fQsq_GeV;
double fQsq;
double fW_GeV_Col;
double fW_Col;
double fW;
double fW_GeV;
double fWSq;
double fWSq_GeV;
double fWSq_PiN;
double fWSq_PiN_GeV;

double fElec_ScatElec_Theta_RF;
double fScatElec_Cone_Phi_RF;
double fScatElec_Theta_RF;
double fScatElec_Phi_RF;
double fScatElec_Mom_RF;
double fScatElec_Energy_RF;
double fScatElec_MomX_RF;
double fScatElec_MomZ_RF;
double fScatElec_MomY_RF;
double fScatElec_Energy_RF_GeV;
double fScatElec_Mom_RF_GeV;
double fScatElec_MomX_RF_GeV;
double fScatElec_MomY_RF_GeV;
double fScatElec_MomZ_RF_GeV;

double fElectron_Theta_RF;
double fElectron_Phi_RF;
double fElectron_Energy_RF;
double fElectron_Mom_RF;
double fElectron_MomX_RF;
double fElectron_MomZ_RF;
double fElectron_MomY_RF;
double fElectron_Energy_RF_GeV;
double fElectron_Mom_RF_GeV;
double fElectron_MomX_RF_GeV;
double fElectron_MomZ_RF_GeV;
double fElectron_MomY_RF_GeV;

double fPhoton_Energy_RF_GeV;
double fPhoton_Mom_RF_GeV;
double fPhoton_Energy_RF;
double fPhoton_Mom_RF;

double fProton_Energy_CM;
double fProton_Mom_CM;
double fProton_Energy_CM_GeV;
double fProton_Mom_CM_GeV;

double fPhoton_Energy_CM;
double fPhoton_Mom_CM;
double fPhoton_Energy_CM_GeV;
double fPhoton_Mom_CM_GeV;

double fPion_Theta_CM;
double fPion_Phi_CM;
double fPion_Energy_CM;
double fPion_Mom_CM;
double fPion_Energy_CM_GeV;
double fPion_Mom_CM_GeV;

double fNeutron_Theta_CM;
double fNeutron_Phi_CM;
double fNeutron_Energy_CM;
double fNeutron_Energy_CM_GeV;
double fNeutron_Mom_CM;
double fNeutron_Mom_CM_GeV;

double fBeta_CM_RF;
double fGamma_CM_RF;

double fPhoton_MomZ_RF;
double fPhoton_MomX_RF;
double fPhoton_MomY_RF;
double fPhoton_Theta_RF;
double fPhoton_Phi_RF;

double fPion_Energy_RF;
double fPion_Energy_RF_GeV;

double fPiqVec_Theta_RF;
double fPion_Mom_RF;
double fPion_Mom_RF_GeV;
double fPion_MomX_RF;
double fPion_MomY_RF;
double fPion_MomZ_RF;
double fPion_Theta_RF;
double fPion_Phi_RF;
double fPion_MomX_RF_GeV;
double fPion_MomY_RF_GeV;
double fPion_MomZ_RF_GeV;


double fT_Para;
double fT_Para_GeV;
double fT;
double fEpsilon;
double fx;
double fy;
double fz;
double fNeutron_Energy_RF;
double fNeutron_Energy_RF_GeV;
double fNeutron_Mom_RF;
double fNeutron_Mom_RF_GeV;
double fNeutron_qVec_Theta_RF;
double fNeutron_MomX_RF;
double fNeutron_MomY_RF;
double fNeutron_MomZ_RF;
double fNeutron_Theta_RF;
double fNeutron_Phi_RF;
double fPhoton_MomX_RF_GeV;
double fPhoton_MomY_RF_GeV;
double fPhoton_MomZ_RF_GeV;
double fNeutron_MomX_RF_GeV;
double fNeutron_MomY_RF_GeV;
double fNeutron_MomZ_RF_GeV;

double fPhoton_Theta_Col;
double fPhoton_Phi_Col;
double fPhoton_Energy_Col;
double fPhoton_Mom_Col;
double fPhoton_MomX_Col;
double fPhoton_MomZ_Col;
double fPhoton_MomY_Col;
double fPhoton_Energy_Col_GeV;
double fPhoton_Mom_Col_GeV;
double fPhoton_MomX_Col_GeV;
double fPhoton_MomZ_Col_GeV;
double fPhoton_MomY_Col_GeV;

double fWFactor;
double fA;
double fFlux_Factor_Col;
double fFlux_Factor_RF;
double fJacobian_CM;
double fJacobian_CM_RF;
double fJacobian_CM_Col;
double fZASig_T;
double fZASig_L;
double fZASig_LT;
double fZASig_TT;
double ftestsig;
double fZASig_L2;

double fZASigma_UU;
double fZASigma_UT;
double fZASigma_Lab;
double fZASigma_UUPara;
double fEventWeight;
double fEventWeightMax;
double fZAWFactor;
double fRR;

double fElectron_Mom_Sq_RF;
double fElectron_Mom_Sq_Col;
double fProton_Mom_Sq_Col;
double fProton_Mom_Sq_CM;
double fProton_Mom_Sq_RF;
double fPhoton_Mom_Sq_Col;
double fPhoton_Mom_Sq_CM;
double fPhoton_Mom_Sq_RF;
double fPion_Mom_Sq_Col;
double fPion_Mom_Sq_CM;
double fPion_Mom_Sq_RF;
double fNeutron_Mom_Sq_Col;
double fNeutron_Mom_Sq_CM;
double fNeutron_Mom_Sq_RF;
double fScatElec_Mom_Sq_Col;
double fScatElec_Mom_Sq_RF;

double fAsym_Hermes_1;
double fAsym_Hermes_2;
double fAsym_Hermes_3;
double fAsym_Hermes_4;
double fAsym_Hermes_5;
double fAsym_Hermes_6;

double fCoef_Hermes_1;
double fCoef_Hermes_2;
double fCoef_Hermes_3;
double fCoef_Hermes_4;
double fCoef_Hermes_5;
double fCoef_Hermes_6;

double fCoef_ZA_1;
double fCoef_ZA_2;
double fCoef_ZA_3;
double fCoef_ZA_4;
double fCoef_ZA_5;
double fCoef_ZA_6;

double fPhi_Pion_LeptonPlane_RF;
double fPhi_TargPol_LeptonPlane_RF;
double fTheta_Pion_Photon_RF;

double fMomentum[300];
double fProb[300] = {    
6.03456,    6.02429,    6.01155,    5.99636,    5.97873,    5.95869,    5.93626,    5.91147,    5.88435,    5.85493,
5.82325,    5.78935,    5.75326,    5.71504,    5.67472,    5.63235,    5.58799,    5.54169,     5.4935,    5.44347,		   
5.39167,    5.33816,    5.28299,    5.22623,    5.16794,    5.10818,    5.04703,    4.98455,    4.92081,    4.85588,
4.78982,    4.71692,    4.63621,    4.55583,    4.47582,    4.39621,    4.31702,    4.23828,    4.16002,    4.08227,
4.00506,     3.9284,    3.85233,    3.77686,    3.70202,    3.62783,    3.55432,    3.48149,    3.40937,    3.33798,
3.26733,    3.19745,    3.12834,    3.06002,    2.99251,    2.92581,    2.85995,    2.79493,    2.73075,    2.66744,
2.605,      2.54344,    2.48276,    2.41728,    2.35244,    2.28922,    2.22759,    2.16751,    2.10895,    2.05186,
1.99621,    1.94198,    1.88913,    1.83762,    1.78743,    1.73851,    1.69086,    1.64442,    1.59918,    1.55511,			   
1.51217,    1.47035,    1.42961,    1.38993,    1.35128,    1.31364,    1.27698,    1.24129,    1.20653,    1.17269,			   
1.13973,    1.10765,    1.07642,    1.04601,    1.01626,   0.986934,   0.958443,   0.930759,   0.903861,   0.877727,			   
0.852335,   0.827665,   0.803696,   0.780409,   0.757785,   0.735806,   0.714452,   0.693708,   0.673555,   0.653978,			   
0.63496,   0.616485,   0.598538,   0.581105,    0.56417,   0.547721,   0.531743,   0.516223,   0.501148,   0.486506,			   
0.472284,    0.45847,   0.445054,   0.432024,   0.419368,   0.407077,   0.395125,   0.383513,   0.372237,   0.361289,			   
0.350658,   0.340336,   0.330314,   0.320583,   0.311135,   0.301962,   0.293056,   0.284409,   0.276014,   0.267863,			   
0.25995,   0.252268,   0.244809,   0.237569,   0.230539,   0.223715,   0.217091,    0.21066,   0.204417,   0.198357,			   
0.192474,   0.186763,   0.181219,   0.175838,   0.170615,   0.165545,   0.160623,   0.155843,   0.151185,   0.146666,			   
0.142282,   0.138028,   0.133902,   0.129898,   0.126013,   0.122245,   0.118588,   0.115041,   0.111599,   0.108261,			   
0.105021,   0.101879,  0.0988298,  0.0958719,  0.0930022,  0.0902182,  0.0875173,   0.084897,  0.0823549,  0.0798886,			   
0.0774961,  0.0751749,  0.0729231,  0.0707385,  0.0686192,  0.0665631,  0.0645685,  0.0626335,  0.0607563,  0.0589545,			   
0.057219,  0.0555322,   0.053893,  0.0523001,  0.0507522,  0.0492481,  0.0477867,  0.0463667,  0.0449872,  0.0436468,			   
0.0423448,  0.0410798,  0.0398511,  0.0386576,  0.0374982,  0.0363722,  0.0352785,  0.0342164,  0.0331849,  0.0321831,			   
0.0312104,  0.0302658,  0.0293486,  0.0284581,  0.0275935,   0.026754,  0.0259391,  0.0251479,  0.0243799,  0.0236344,			   
0.0229107,  0.0221901,  0.0214923,  0.0208167,  0.0201626,  0.0195293,  0.0189162,  0.0183226,  0.0177478,  0.0171913,			   
0.0166525,  0.0161308,  0.0156257,  0.0151366,  0.0146629,  0.0142044,  0.0137603,  0.0133303,  0.0129139,  0.0125107,			   
0.0121203,  0.0117421,   0.011376,  0.0110214,   0.010678,  0.0103455,  0.0100234, 0.00971153, 0.00940947, 0.00911693,			   
0.00883361,  0.0085592, 0.00829385, 0.00803735, 0.00778883, 0.00754804, 0.00731474,  0.0070887, 0.00686967, 0.00665746,			   
0.00645184, 0.00625261, 0.00605957, 0.00587252, 0.00569128, 0.00551567, 0.00534551, 0.00518063, 0.00502086, 0.00486605,			   
0.00471604, 0.00457069, 0.00442984, 0.00429336,  0.0041611, 0.00403295, 0.00390877, 0.00378843, 0.00367182, 0.00355882,			   
0.00344932, 0.00334321, 0.00324038, 0.00314073, 0.00304505,  0.0029524, 0.00286252, 0.00277533, 0.00269076, 0.00260872,			   
0.00252913, 0.00245194, 0.00237706, 0.00230444, 0.00223399, 0.00216566, 0.00209939, 0.00203512, 0.00197277, 0.00191231 };


class pim {

 public:
  double test();
  void Initilize();
  void setrootfile( string myRootFile );
  double fermiMomentum();

};
