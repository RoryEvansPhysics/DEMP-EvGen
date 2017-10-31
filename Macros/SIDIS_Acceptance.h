#include <iostream>

using namespace std;

class SIDIS_Acceptance{

    public:

        SIDIS_Acceptance(){ Init(); }

        virtual ~SIDIS_Acceptance(){
           file_ele->Close();
           file_pos->Close();
           file_neu->Close();
           file_pip->Close();
           file_pim->Close();
        }

        void Init(){/*{{{*/
            //CLEO
            TString ele_filename = "./CLEO_SIDIS_He3/acceptance_solid_CLEO_SIDIS_3he_negative_output.root";
            TString pos_filename = "./CLEO_SIDIS_He3/acceptance_solid_CLEO_SIDIS_3he_positive_output.root";
            TString neu_filename = "./CLEO_SIDIS_He3/acceptance_solid_CLEO_SIDIS_3he_neutral_output.root";
            TString pip_filename = "./CLEO_SIDIS_He3/acceptance_solid_CLEO_SIDIS_3he_positive_output.root";
            TString pim_filename = "./CLEO_SIDIS_He3/acceptance_solid_CLEO_SIDIS_3he_negative_output.root";
           
            TCanvas * dummycavans=new TCanvas();
            file_ele=new TFile(ele_filename.Data(),"r");
            accep_ele_forward=(TH2F*)file_ele->Get("acceptance_forwardangle"); 
            accep_ele_large=(TH2F*)file_ele->Get("acceptance_largeangle");    

            file_pos=new TFile(pos_filename.Data(),"r");
            accep_pos_forward=(TH2F*)file_ele->Get("acceptance_forwardangle"); 
            accep_pos_large=(TH2F*)file_ele->Get("acceptance_largeangle");    

            file_neu=new TFile(neu_filename.Data(),"r");
            accep_neu_forward=(TH2F*)file_neu->Get("acceptance_forwardangle");
            accep_neu_large=(TH2F*)file_neu->Get("acceptance_largeangle");   
       
            file_pip=new TFile(pip_filename.Data(),"r");
            accep_pip_forward=(TH2F*)file_pip->Get("acceptance_forwardangle");
            accep_pip_large=(TH2F*)file_pip->Get("acceptance_largeangle");   
   
            file_pim=new TFile(pim_filename.Data(),"r");
            accep_pim_forward=(TH2F*)file_pim->Get("acceptance_forwardangle");
            accep_pim_large=(TH2F*)file_pim->Get("acceptance_largeangle");   
        }/*}}}*/

        double GetAcc(TString kPID, TString kRegion, double kP, double kTheta){/*{{{*/
            int theta_bin=int(kTheta/0.2)+1;    //0.2 degree per bin
			int p_bin=int(kP/0.05)+1;      //0.05 GeV per bin for mom
			double acc=0.0;

            if(kRegion=="FA"||kRegion=="fa"||kRegion=="Forward"||kRegion=="forward"){
                if(kPID=="e-"||kPID=="ele"||kPID=="electron")
                    acc=accep_ele_forward->GetBinContent(theta_bin,p_bin);
                else if(kPID=="e+"||kPID=="pos"||kPID=="positron")
                    acc=accep_pos_forward->GetBinContent(theta_bin,p_bin);
                else if(kPID=="neutron"||kPID=="photon"||kPID=="neu"||kPID=="pho"||kPID=="n"||kPID=="g")
                    acc=accep_neu_forward->GetBinContent(theta_bin,p_bin);
                else if(kPID=="pip"||kPID=="pionp"||kPID=="pi+")
                    acc=accep_pip_forward->GetBinContent(theta_bin,p_bin);
                else if(kPID=="pim"||kPID=="pionm"||kPID=="pi-")
                    acc=accep_pim_forward->GetBinContent(theta_bin,p_bin);
                else{
                    cerr<<"*** ERROR, I don't know this particle = "<<kPID.Data()<<endl;
                    return 0.0;
                }
            }
            if(kRegion=="LA"||kRegion=="la"||kRegion=="large"||kRegion=="Large"){
                if(kPID=="e-"||kPID=="ele"||kPID=="electron")
                    acc=accep_ele_large->GetBinContent(theta_bin,p_bin);
                else if(kPID=="e+"||kPID=="pos"||kPID=="positron")
                    acc=accep_pos_large->GetBinContent(theta_bin,p_bin);
                else if(kPID=="neutron"||kPID=="photon"||kPID=="neu"||kPID=="pho"||kPID=="n"||kPID=="g")
                    acc=accep_neu_large->GetBinContent(theta_bin,p_bin);
                else if(kPID=="pip"||kPID=="pionp"||kPID=="pi+")
                    acc=accep_pip_large->GetBinContent(theta_bin,p_bin);
                else if(kPID=="pim"||kPID=="pionm"||kPID=="pi-")
                    acc=accep_pim_large->GetBinContent(theta_bin,p_bin);
                else{
                    cerr<<"*** ERROR, I don't know this particle = "<<kPID.Data()<<endl;
                    return 0.0;
                }
            }

            return acc;
        }/*}}}*/
      
    private:
        /*{{{*/
        TFile *file_ele;
        TH2F *accep_ele_forward;
        TH2F *accep_ele_large;  
        TFile *file_pos;
        TH2F *accep_pos_forward;
        TH2F *accep_pos_large;  
        TFile *file_neu;
        TH2F *accep_neu_forward;
        TH2F *accep_neu_large; 
        TFile *file_pip;
        TH2F *accep_pip_forward;
        TH2F *accep_pip_large; 
        TFile *file_pim;
        TH2F *accep_pim_forward;
        TH2F *accep_pim_large; 
 /*}}}*/
};
