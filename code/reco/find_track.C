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
//    std::cout << "\n";

}


void reset_info(){ 
    for(int i=0;i<10;i++)
        info[i].n=0; 
}


float calc_Ls( TVector3 v1, TVector3 v2, TVector3 v4){
    
    double x3,y3;
    TVector3 uv = (v2-v1).Unit();

    x3 = v2.X() + (v4.Z()-v2.Z())*uv.X();
    y3 = v2.Y() + (v4.Z()-v2.Z())*uv.Y();

    return sqrt( pow(x3-v4.X(),2) + pow(y3-v4.Y(),2) ) ;

}


struct trk_pair
{
    TVector3  v1;
    TVector3  v2;
    TVector3  v3;
    TVector3  v4;
    double     z;
    double     a;
    double     d;
};

trk_pair tp[EVENT_SIZE];
int tpn=0;

void make_pairs(){

    TVector3  v1, v2, v3, v4;

    bool fine[EVENT_SIZE][8];
    for(int s=0;s<9;s++)
        for(int i=0;i<info[s].n;i++)
            fine[i][s]=true;


    // Remove close hits
    for(int s=0;s<8;s++){
      for(int i=0;i<info[s].n-1;i++){    
        for(int j=i+1;j<info[s].n;j++){
          if( (info[s].vect[i]-info[s].vect[j]).Mag() < 0.05 ){
            fine[j][s]=false;
          }
    }}}
    
    // Remove straight             
    for(int St1=0;St1<2;St1++){
      for(int i=0;i<info[St1].n;i++){

      v1 = info[St1].vect[i]; 

      for(int St2=2;St2<4;St2++){
        for(int j=0;j<info[St2].n;j++){
         v2 = info[St2].vect[j]; 


          for(int St3=4;St3<6;St3++){
            for(int k=0;k<info[St3].n;k++){
              v3 = info[St3].vect[k]; 
              if( calc_Ls(v1,v2,v3) < 0.25 ){
                fine[i][St1]=false;
                fine[j][St2]=false;
                fine[k][St3]=false;


                for(int St4=6;St4<8;St4++){
                  for(int l=0;l<info[St1].n;l++){
                    v4 = info[St4].vect[l]; 
                    if( calc_Ls(v1,v2,v4) < 0.450 ){
                      fine[l][St4]=false;
                    }
                 }}
                
              }
          }}
          
    }} }}


    double Dist, Ang, Vtx;
    // Create pairs
    for(int St1=0;St1<2;St1++){
      for(int i=0;i<info[St1].n;i++){
        if( fine[i][St1] ){
          v1 = info[St1].vect[i]; 

          for(int St2=2;St2<4;St2++){
            for(int j=0;j<info[St2].n;j++){
              if( fine[j][St2] ){
                v2 = info[St2].vect[j]; 

                for(int St3=4;St3<6;St3++){
                  for(int k=0;k<info[St3].n;k++){
                    if( fine[k][St3] ){
                       v3 = info[St3].vect[k]; 
 
                       for(int St4=6;St4<8;St4++){
                         for(int l=0;l<info[St1].n;l++){
                           if( fine[l][St4] ){
                             v4 = info[St4].vect[l];
                             
                              Dist = Distance( v1, v2, v3, v4 ) ;
                              if( Dist < 0.2){
                                Ang = 1000.*1000.*(v4-v3).Angle(v2-v1);
                                if( Ang>200. && Ang<1500.){
                                  tp[ tpn ].v1 = v1;
                                  tp[ tpn ].v2 = v2;
                                  tp[ tpn ].v3 = v3;
                                  tp[ tpn ].v4 = v4;
                                  tp[ tpn ].a  = Ang;
                                  tp[ tpn ].d  = Dist;
                                  tp[ tpn ].z  = Vertex( v1, v2, v3, v4 ).Z();
                                  tpn++;
                                }
                              }
    }}}}}}}}}}}}
    
    
}


void find_track(){

    int ev, vol;
    double dE, x, y, z, t;
    

    std::ifstream fMERGED("all/out.data" , std::ios::in);

    int EVENT = 0;
    int nMult = 0;
    tpn=0;
/*
    int nGood=0;
    int nBad =0;

    float Ang, Vtx, Dis;
*/
    TH1F* hVtx  = new TH1F("hVtx" ,";Z_{rec}, mm;Evts", 300, -600,  600);
    TH1F* hDis  = new TH1F("hDis" ,";#DeltaL_{rec}, mm;Evts", 100,    0,  1);
    TH1F* hAng  = new TH1F("hAng" ,";angle,#mu rad;Evts", 150, 0, 1500);

    while( fMERGED >> ev >> vol >> dE >> x >> y >> z >> t ){
        if(ev>EVENT){


            make_pairs();
            std::cout << EVENT << "\t";
            print_info();
            std::cout << "  ---> " << tpn << "\n";
            if(tpn>1) nMult++;
            for(int cand=0;cand<tpn;cand++){
                hAng->Fill( tp[ cand ].a );
                hVtx->Fill( tp[ cand ].z );
                hDis->Fill( tp[ cand ].d );            
            }
            
            reset_info();
            tpn=0;
            EVENT = ev;
        }
        
        if( t>-50 && t<100050 ) fill_info(vol, x, y, z, t);
    }


    std::cout << " Multiple candidates : " << 100.*float(nMult) / float(EVENT-1) << " %\n";

    TCanvas* canv = new TCanvas("canv","canv",800,600);
    hAng->Fit("gaus");
    hAng->Draw();
    canv->Print("cANG.png");
    hVtx->Draw();
    canv->Print("cVTX.png");
    hDis->Draw();
    canv->Print("cDIS.png");
    fMERGED.close();
    gSystem->Exit(0);

}


