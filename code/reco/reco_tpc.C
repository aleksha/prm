#include <fstream>
#include <iostream>
#include <iomanip>

// To be copied into output dir ad run there
#include "../code/reco/fadc.cc"
#include "../code/reco/histo_funcs.cc"
#include "../configs/reco/config_tpc.h"

#include "TGraph.h"
#include "TH1F.h"
#include "TH1S.h"
#include "TH2S.h"
#include "TF1.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TLatex.h"

fadc_info info[12];
TH1F* hFADC[12];
double Digi[175];

double time_shifts[1000];
int ts;

int get_pad2(double x, double y, double z){
    // central pad R = 10 mm
    // other rinrs with width = 40 mm
    // numberinf inner-to-outer

    double l;
    l = sqrt(x*x+y*y);

    if(z<0){
        if( l>161.5 && l<=200.5) return  5;
        if( l>125.5 && l<=161.5) return  4;
        if( l> 83.5 && l<=125.5) return  3;
        if( l> 44.5 && l<= 83.5) return  2;
        if( l>  5.5 && l<= 44.5) return  1;
        if( l<= 5.5)             return  0;
    }

    if( l>161.5 && l<=200.5) return 11;
    if( l>125.5 && l<=161.5) return 10;
    if( l> 83.5 && l<=125.5) return  9;
    if( l> 44.5 && l<= 83.5) return  8;
    if( l>  5.5 && l<= 44.5) return  7;
    if( l<= 5.5)             return  6;

    return -1;
}

void load_Digi(){
  int channel ;
  double digi;

  if(ADD_SHAPING){
      std::ifstream fDIGI("../configs/reco/digi.calib" , std::ios::in);
      while( fDIGI >> channel >> digi ) Digi[channel]=digi;
      fDIGI.close();
  } else{
      for(int dd=0;dd<175;dd++){
          if(dd<22){
            Digi[dd]=1./22.;
          } else{
            Digi[dd]=0;
          }
      }
  }
}




void reco_tpc( int Evts=MY_EVTS){

  int N_e, Nsub;
  int N_s=0;
  double l, X, Y, Z, t_anod, d_anod, tt;

  load_Digi();

//==============================================================================
// run it
//==============================================================================

    int ev, vol;
    double dE,x,y,z,t,ll, path_length, Val;
    double xi,yi,zi,ti,xf,yf,zf,tf;
    double dx, dy, dz, dt;
    double xd, yd, zd; // smeared by transverse and longitudional diffusion

    int EVENT=0;
    int tEv=0;

    int fpad;

    TString pFADC;

    for(int pad=0;pad<12;pad++){
        if(pad<10){
            pFADC.Form ("hFADS_0%d", pad);
        } else{
            pFADC.Form ("hFADS_%d", pad);
        }
        hFADC[pad] = new TH1F( pFADC," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
//        hFADC[pad]->GetXaxis()->SetRangeUser(0,20000);
//        hFADC[pad]->GetXaxis()->SetRangeUser(90000,100000);
//        hFADC[pad]->GetYaxis()->SetRangeUser(8000,16000);
        hFADC[pad]->SetMinimum(0);
    }

    std::ifstream fPROT("all/tpc.data" , std::ios::in);
    std::ifstream fNOIS("noise/noise.data"  , std::ios::in);
    std::ofstream fOUT("./signal.data"  , std::ios::trunc);


    while( fPROT >> ev >> vol >> dE >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){

        if(ev>EVENT){

            // Electronic Noise
            if( ADD_NOISE ){
                for(int p=0;p<12;p++){
                    for(int nbin=1;nbin<2694;nbin++){
                        fNOIS >> Val;
                        if( nbin<2551 ){
                            hFADC[p]->SetBinContent( nbin, hFADC[p]->GetBinContent(nbin) + Val );
                        }
                    }
                }
            }

            // Eval signal info
            for(int p=0;p<12;p++){
                info[p] = eval_info( hFADC[p] );
            }

            if( WRITE_ASCII ){
                for(int ss=CH_START;ss<CH_STOP;ss++)
                    fOUT << hFADC[ CH_WRITE ]->GetBinContent(ss) << " " ;
                fOUT << "\n" ;
            }

//            if( !(ev%5) ) std::cout << "PROCESSED: "<< ev << " events\n";
            std::cout << "PROCESSED: "<< ev << " events\n";

            if(ev==Evts) break;

            for(int p=0;p<12;p++){ hFADC[p]->Reset(); }

            EVENT=ev;
        }


        if( vol==10 ){

            N_e = int( dE/ I_av );
            ll = 1000.*sqrt(pow(xf-xi,2)+pow(yf-yi,2)+pow(zf-zi,2));
            Nsub = int(N_e/Ne_MAX);
            if(Nsub < int(ll/Ll_MAX)) Nsub = int(ll/Ll_MAX);

            if(Nsub<1) Nsub=1;

            if(N_e>0){
                dx = (xf-xi)/Nsub;
                dy = (yf-yi)/Nsub;
                dz = (zf-zi)/Nsub;
                dt = (tf-ti)/Nsub;
                N_s = 0;
                for(int ee=0;ee<Nsub;ee++){
                    x = xi + 0.5*dx + dx*ee;
                    y = yi + 0.5*dy + dy*ee;
                    z = zi + 0.5*dz + dz*ee;
                    t = ti + 0.5*dt + dt*ee;
                    fpad = get_pad2(x,y,z);

                    if( z<0){
                        path_length = z-Z_anode_1+10.;
                    } else{
                        path_length = Z_anode_2-10.- z;
                    }

                    if(ADD_DIFFUSION){
                        x = x + gRandom->Gaus(0,DIFF_P*sqrt(path_length/10.));
                        y = y + gRandom->Gaus(0,DIFF_P*sqrt(path_length/10.));
                        z = z + gRandom->Gaus(0,DIFF_L*sqrt(path_length/10.));
                    }


                    if(fpad>-1){
                      t_anod = t + ( path_length / W1)  ;
                      tt = 20;
                      for(int iii = 0 ; iii<125; iii++  ){
                          hFADC[fpad]->Fill(t_anod + tt, Calib*Digi[iii]*N_e/Nsub);
                          tt = tt + 40 ;
                        }
                    }
                }
            }
        }
    }

    fPROT.close();
    fNOIS.close();
    fOUT.close();

//==============================================================================
// finishing
//==============================================================================
    if( DRAW_LAST ){
        TCanvas* canv = new TCanvas("canv","canv",1200,300);
        gStyle->SetOptStat(0);
        for(int p=0;p<12;p++){
            hFADC[p]->Draw("hist");
            if(p<10){pFADC.Form("FADS_0%d.png",p);}
            else{ pFADC.Form("FADS_%d.png",p);}
            canv->Print( pFADC );
        }
        canv->Close();
    }

    gSystem->Exit(0);

}
