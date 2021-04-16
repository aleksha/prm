#include <fstream>
#include <iostream>
#include <iomanip>

#include "TGraph.h"
#include "TH1F.h"
#include "TH1S.h"
#include "TH2S.h"
#include "TF1.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TMath.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TLatex.h"

struct fadc_info
{
    double average;
    double peak;
    double mbp; // maximum bin position
    double max; // maximum bin content
    double base;
    double start;
    double end;
    double energy;
    bool is_fired;
};


double find_peak(TH1F* h){
    TGraph* gn;
    TF1* poln;
    double pn_x[21];
    double pn_y[21];
    int nn_min;
    double xn_min, xn_max, xn_len;

    nn_min = h->GetMaximumBin()-10 ;

    xn_min = h->GetXaxis()->GetBinCenter( nn_min );
    xn_max = h->GetXaxis()->GetBinCenter( h->GetMaximumBin()+10  );

    xn_len = xn_max-xn_min;

    poln = new TF1("poln","[0]+[1]*x+[2]*x*x", xn_min-0.05*xn_len, xn_max+0.05*xn_len);

    for(int g=0;g<21;g++){
        pn_x[g] = h->GetXaxis()->GetBinCenter( nn_min + g );
        pn_y[g] = h->GetBinContent           ( nn_min + g );
    }
    gn = new TGraph(21,pn_x,pn_y);
    gn->Fit( poln , "Q");

    return (-0.5)*poln->GetParameter(1) / poln->GetParameter(2) ;

}

bool check_fired(TH1F*h, fadc_info i, double threshold=1.02, int window = 10, int nbins=2550){
  bool isf = false;
  double running_sum=0;
  for(int bin=1;bin<window+1;bin++){
      running_sum += ( h->GetBinContent(bin)*(1./window) );
  }
  for(int bin=1;bin<nbins-window+1;bin++){
      if( running_sum > i.average*threshold ) isf = true ;
      running_sum -= ( h->GetBinContent( bin )              ) / window;
      running_sum += ( h->GetBinContent( bin + window + 1 ) ) / window;
  }
  return isf;
}

double correct_base(TH1F* h, int ch_left=50, int ch_right=100, int nbins=2550){
  int max_bin = h->GetMaximumBin() ;
  int bin_low = max_bin - ch_left  ;
  int bin_high= max_bin + ch_right ;
  double base = 0;
  int counted_bins = 0;
  for(int bin=1;bin<nbins+1;bin++){
      if( (bin < bin_low) || ( bin > bin_high) ){
          base += h->GetBinContent(bin);
          counted_bins++;
          //std::cout << "  ---> " << bin  << " " << max_bin << "\n";
      }
  }

  return base/counted_bins;
}


double eval_start(TH1F* h, fadc_info i, int mb, double slope){
  double value = 0.5*(h->GetBinContent(mb-1) + h->GetBinContent(mb));
  double point = 40.*mb - 20.;
  return point-((value-i.base)/slope);
}

double eval_start2(TH1F* h, fadc_info i, double min_sig=0.3, double max_sig=0.8){
  TGraph* g;
  TF1* pol1;
  double low  = i.base + min_sig*(i.max-i.base);
  double high = i.base + max_sig*(i.max-i.base);
  double x[100], y[100];
  int len=0;
  int max_bin = h->GetMaximumBin();

  for(int bin=max_bin;bin>max_bin-100;bin--){
      if(h->GetBinContent(bin)<high){
          if(h->GetBinContent(bin)>low){
              x[len]= h->GetXaxis()->GetBinCenter( bin );
              y[len]= h->GetBinContent( bin );
              len++;
          }
          else break;
      }
  }

  pol1 = new TF1("poln","[0]+[1]*x", 0, 100000);
  g = new TGraph(len,x,y);
  g->Fit( pol1 , "Q");
  return (i.base-pol1->GetParameter(0)) / pol1->GetParameter(1) ;
}

double eval_end2(TH1F* h, fadc_info i, double min_sig=0.3, double max_sig=0.8){
  TGraph* g;
  TF1* pol1;
  double low  = i.base + min_sig*(i.max-i.base);
  double high = i.base + max_sig*(i.max-i.base);
  double x[100], y[100];
  int len=0;
  int max_bin = h->GetMaximumBin();

  for(int bin=max_bin;bin<max_bin+100;bin++){
      if(h->GetBinContent(bin)<high){
          if(h->GetBinContent(bin)>low){
              x[len]= h->GetXaxis()->GetBinCenter( bin );
              y[len]= h->GetBinContent( bin );
              len++;
          }
          else break;
      }
  }

  pol1 = new TF1("poln","[0]+[1]*x", 0, 100000);
  g = new TGraph(len,x,y);
  g->Fit( pol1 , "Q");
  return (i.base-pol1->GetParameter(0)) / pol1->GetParameter(1) ;
}

double eval_energy(TH1F* h, fadc_info i){
  double energy = 0 ;
  double bin_center = 20.;

  for(int bin=1;bin<2551;bin++){
    if(bin_center>i.start){
      if(bin_center>i.end)
        break;
      energy += ( h->GetBinContent(bin) - i.base );
    }
    bin_center += 40;
  }

  return energy;
}

fadc_info eval_info(TH1F* h, int nbins=2550){
    fadc_info h_info;
    h_info.is_fired = false;

    h_info.average = 0;
    for(int bin=1;bin<nbins+1;bin++) h_info.average += h->GetBinContent(bin);
    h_info.average = h_info.average / nbins;

    h_info.mbp = h->GetXaxis()->GetBinCenter( h->GetMaximumBin() ) ;
    h_info.max = h->GetBinContent( h->GetMaximumBin() ) ;
    h_info.peak = find_peak( h );

    h_info.is_fired = check_fired( h, h_info );

    if( h_info.is_fired ){
        h_info.base   = correct_base( h         );
        h_info.start  = eval_start2( h, h_info );
        h_info.end    = eval_end2  ( h, h_info );
        h_info.energy = eval_energy( h, h_info );
    }
    else{
        h_info.base   = h_info.average;
        h_info.start  = -1;
        h_info.end    = -1;
        h_info.energy = -1;
    }

    return h_info;
}

void print_info(fadc_info i){
    std::cout << "f: " << i.is_fired << "  ";
    std::cout << "a: " << i.average  << "  ";
    std::cout << "b: " << i.base     << "  ";
    std::cout << "p: " << i.peak     << "  ";
    std::cout << "m: " << i.mbp      << "  ";
    std::cout << "m: " << i.start    << "  ";
    std::cout << "m: " << i.end      << "  ";
    std::cout << "s: " << i.energy   << "\n";
}

