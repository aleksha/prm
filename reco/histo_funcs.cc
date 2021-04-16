#include "TH1F.h"

void smearTH1(TH1F* h, TH1F* s, int window=5, int nbins=2550){
  int current_bin;
//  if( !(window%2) ) window++ ;
  for(int bin=1;bin<nbins+1;bin++){
      if( (bin<1+window/2) || (bin>nbins+1-window/2) ){
          s->SetBinContent( bin,  h->GetBinContent(bin) );
      }
      else{
          for(int w=0;w<window;w++){
              current_bin = bin + w - window/2;
              s->SetBinContent( bin, h->GetBinContent(current_bin)/window + s->GetBinContent( bin ) );
          }
      }
  }
}

void derivTH1(TH1F* h, TH1F* d, int nbins=2550){
  for(int bin=2;bin<nbins;bin++)
      d->SetBinContent(bin, h->GetBinContent(bin) - h->GetBinContent(bin-1) );
}

