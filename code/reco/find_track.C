#include <fstream>
#include <iostream>
#include <iomanip>

#include "../configs/reco/config_track.h"
#include "../code/reco/fadc.cc"
#include "../code/reco/histo_funcs.cc"
#include "../code/reco/track.cc"

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

struct hits_info
{
    TVector3  vect[EVENT_SIZE];
    double    time[EVENT_SIZE];
    int n;
};


hits_info info[10];


void fill_info(int vol, double x, double y, double z, double t){
    info[vol].vect[ info[vol].n ].SetX( x + gRandom->Gaus( 0, RESO ) );
    info[vol].vect[ info[vol].n ].SetY( y + gRandom->Gaus( 0, RESO ) );
    info[vol].vect[ info[vol].n ].SetZ( z                            );
    info[vol].time[ info[vol].n ] = t;
    info[vol].n++;
}

void print_info(){ 
    for(int i=0;i<10;i++)
        std::cout << info[i].n << "\t";
    std::cout << "\n";

}


void reset_info(){ 
    for(int i=0;i<10;i++)
        info[i].n=0; 
}


void find_track(){

    int ev, vol;
    double dE, x, y, z, t;
    

    std::ifstream fMERGED("all/out.data" , std::ios::in);

    int EVENT = 0;
/*
    int nGood=0;
    int nBad =0;

    float Ang, Vtx, Dis;
    TH1F* hVtx  = new TH1F("hVtx" ,";Z_{rec}, mm;Evts", 300, -600,  600);
    TH1F* hDis  = new TH1F("hDis" ,";#DeltaL_{rec}, mm;Evts", 100,    0,  1);
    TH1F* hAng  = new TH1F("hAng" ,";angle,#mu rad;Evts", 150, 0, 1500);
*/
    while( fMERGED >> ev >> vol >> dE >> x >> y >> z >> t ){
        if(ev>EVENT){

/*
            if( good_event2() ){ 
                nGood++;
                Ang  = calc_angle3();
                Vtx  = calc_vertex();
                Dis  = calc_distance();
                if( Ang>0 && Ang<1500) {
                    hAng->Fill( Ang );
                    hVtx->Fill( Vtx );
                    hDis->Fill( Dis );
                }
            } else {nBad++;}
*/
            std::cout << EVENT << "\t";
            print_info();
            
            reset_info();
            EVENT = ev;
        }
        
        if( t>-50 && t<100050 ) fill_info(vol, x, y, z, t);
    }

/*
    TCanvas* canv = new TCanvas("canv","canv",800,600);
    hAng->Fit("gaus");
    hAng->Draw();
    canv->Print("ANG.png");
*/

    fMERGED.close();
    gSystem->Exit(0);

}


