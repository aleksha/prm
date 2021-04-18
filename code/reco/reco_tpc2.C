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
#include "TH2F.h"
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
TH1F* hINIT[12];
TH2F* h2;
TTree* out_tree;

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


double path_length( double z ){
	if( z<0 ){ return z-Z_anode_1+10.; }
    return  Z_anode_2-10.- z;
}


void reco_tpc2( int Evts=MY_EVTS ){

  int N_e, Nsub;
  int N_s=0;
  double l, X, Y, Z, t_anod, d_anod, tt;

  load_Digi();

//==============================================================================
// run it
//==============================================================================

    int ev, vol;
    double dE,x,y,z,t,ll,Val;
    double xi,yi,zi,ti,xf,yf,zf,tf;
    double dx, dy, dz, dt;
    double xd, yd, zd; // smeared by transverse and longitudional diffusion

    int EVENT=0;
    int tEv=0;

    int fpad;

    TString pFADC, pINIT;

    for(int pad=0;pad<12;pad++){
        if(pad<10){
            pFADC.Form ("hFADS_0%d", pad);
            pINIT.Form ("hINIT_0%d", pad);
        } else{
            pFADC.Form ("hFADS_%d", pad);
            pINIT.Form ("hINIT_%d", pad);
        }
        hFADC[pad] = new TH1F( pFADC," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        hINIT[pad] = new TH1F( pINIT," ;time, ns; voltage, a.u.", 2550+125, -125.*40., 40.*2550. );
//        hFADC[pad]->GetXaxis()->SetRangeUser(0,20000);
//        hFADC[pad]->GetXaxis()->SetRangeUser(90000,100000);
        if(  ADD_NOISE )  hFADC[pad]->GetYaxis()->SetRangeUser(8000,16000);
        if( !ADD_NOISE )  hFADC[pad]->GetYaxis()->SetRangeUser(   0,16000);
//        hFADC[pad]->SetMinimum(0);
        hINIT[pad]->SetMinimum(0);
    }
    
    h2 = new TH2F("h2",";time, ns; anode", 2550, 0., 40.*2550, 12,-0.5,11.5);

    TH1F *hSL = new TH1F("hSL",";l, mm;", 3500, -3500, 3500);
    TH1F *hST = new TH1F("hST",";t, ch;", 3500, -3500, 3500);
    std::ifstream fINIT("prot/input_g4.txt" , std::ios::in);
    std::ifstream fPROT("all/tpc.data"      , std::ios::in);
    std::ifstream fNOIS("noise/noise.data"  , std::ios::in);
    std::ofstream fOUT("./signal.data"      , std::ios::trunc);

    int inEv, inPcode;
    double inX, inY, inZ, inT;
    double inPx, inPy, inPz;
    double inTp;
    double m_p = 0.938272;

    out_tree = new TTree("out_tree","tpc");
    for(int pad=0;pad<12;pad++){
        // Histo
        if(pad<10){ pFADC.Form ("hFADC_0%d", pad); } else{ pFADC.Form ("hFADC_%d", pad); }
        out_tree->Branch( pFADC, "TH1F",&hFADC[pad],32000,0);
        
        if(pad<10){ pFADC.Form ("is_fired_0%d", pad); } else{ pFADC.Form ("is_fired_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].is_fired );

        if(pad<10){ pFADC.Form ("av_0%d", pad); } else{ pFADC.Form ("av_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].average );

        if(pad<10){ pFADC.Form ("base_0%d", pad); } else{ pFADC.Form ("base_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].base );

        if(pad<10){ pFADC.Form ("peak_0%d", pad); } else{ pFADC.Form ("peak_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].peak );

        if(pad<10){ pFADC.Form ("mbp_0%d", pad); } else{ pFADC.Form ("mbp_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].mbp );

        if(pad<10){ pFADC.Form ("start_0%d", pad); } else{ pFADC.Form ("start_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].start );

        if(pad<10){ pFADC.Form ("end_0%d", pad); } else{ pFADC.Form ("end_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].end );

        if(pad<10){ pFADC.Form ("energy_0%d", pad); } else{ pFADC.Form ("energy_%d", pad); }
        out_tree->Branch( pFADC, &info[pad].energy );
    }

    out_tree->Branch("inX",&inX);
    out_tree->Branch("inY",&inY);
    out_tree->Branch("inZ",&inZ);
    out_tree->Branch("inT",&inT);
    out_tree->Branch("inPx",&inPx);
    out_tree->Branch("inPy",&inPy);
    out_tree->Branch("inPz",&inPz);
    out_tree->Branch("inTp",&inTp);
    
    int same_pad=0;
    int steps = 0;
    float E_same = 0.;
    float E_diff = 0.;
    float t_anod_f, t_anod_i, bc;

    while( fPROT >> ev >> vol >> dE >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){

        if(ev>EVENT){
        
            for(int p=0;p<12;p++){
                for(int bin=1;bin<2551+125;bin++){
                    bc = hINIT[p]->GetBinContent(bin);
                    for(int iii = 0 ; iii<125; iii++  ){
                        hFADC[p]->Fill( 40.*(bin+iii-125)-20., Digi[iii]*bc );
                    }}}

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
            std::cout << ev << "\t" << same_pad << "\t" << steps ;
            std::cout       << "\t" << 100.*same_pad/steps ;
            std::cout       << "\t" << 100.*E_same/(E_same+E_diff) << "\n";
            same_pad=0; steps=0;
            E_same = 0.;
            E_diff = 0.;

            fINIT >> inEv >> inPcode >> inX >> inY >> inZ >> inPx >> inPy >> inPz >> inT ;
            inTp = 1000.*( sqrt(m_p*m_p+inPx*inPx+inPy*inPy+inPz*inPz) - m_p);

            out_tree->Fill();
            if(ev==Evts) break;

            for(int p=0;p<12;p++){ hFADC[p]->Reset(); hINIT[p]->Reset(); }
            h2->Reset();
            EVENT=ev;
        }

        if( vol==10 ){
        
        	steps++;
        	if( get_pad2(xi,yi,zi) == get_pad2(xf,yf,zf) ){
        	    same_pad++; E_same += dE;
        	} else{ E_diff += dE; }
        	
            N_e = int( dE/ I_av );
            ll = 1000.*sqrt(pow(xf-xi,2)+pow(yf-yi,2)+pow(zf-zi,2));

       	    t_anod_f = tf + ( path_length(zf) / W1 );
       	    t_anod_i = tf + ( path_length(zi) / W1 );
       	    
       	    Nsub = int( fabs(t_anod_f - t_anod_i) );
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
					t_anod = t + ( path_length(z) / W1)  ;
                    if(fpad>-1){
                      t_anod = t + ( path_length(z) / W1)  ;
                      tt = 20;
                      h2->Fill(t_anod + tt, fpad, Calib*N_e/Nsub);
                      hINIT[fpad]->Fill(t_anod + tt, Calib*N_e/Nsub);
                    }
                }
            }
      	    
      	    hST->Fill( (t_anod_f - t_anod_i)/40. );
            hSL->Fill(ll/1000.);

        }
        
    }

    fPROT.close();
    fINIT.close();
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
//            hINIT[p]->Draw("hist");
            if(p<10){pFADC.Form("FADS_0%d.png",p);}
            else{ pFADC.Form("FADS_%d.png",p);}
            canv->Print( pFADC );
        }
        canv->Close();
    }

    TFile *out_file = new TFile("FADC.root","RECREATE");
    out_tree->Write();
    out_file->Write();
    out_file->Close();
 
    gSystem->Exit(0);

}
