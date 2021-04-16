{

  std::ifstream f1("data/v1.tzt"  , std::ios::in);
  std::ifstream f2("data/v2.tzt"  , std::ios::in);
  std::ifstream f3("data/v3.tzt"  , std::ios::in);

  std::ifstream f1s("data/s1.tzt"  , std::ios::in);
  std::ifstream f2s("data/s2.tzt"  , std::ios::in);
  std::ifstream f3s("data/s3.tzt"  , std::ios::in);

  int ch1, ch2, ch3;
  double val1, val2, val3;

  int ch1s, ch2s, ch3s;
  double val1s, val2s, val3s;

  TH1F* h1 = new TH1F("h1",";time, #mus; ",176,0,0.04*176);
  TH1F* h2 = new TH1F("h2",";time, #mus; ",176,0,0.04*176);
  TH1F* h3 = new TH1F("h3",";time, #mus; ",176,0,0.04*176);

  TH1F* h1s = new TH1F("h1s",";time, #mus; ",176,0,0.04*176);
  TH1F* h2s = new TH1F("h2s",";time, #mus; ",176,0,0.04*176);
  TH1F* h3s = new TH1F("h3s",";time, #mus; ",176,0,0.04*176);

  h1s->SetLineColor(1);
  h2s->SetLineColor(2);
  h3s->SetLineColor(4);

  h1s->SetLineWidth(2);
  h2s->SetLineWidth(2);
  h3s->SetLineWidth(2);

  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);

  h1->SetFillColor(1);
  h2->SetFillColor(2);
  h3->SetFillColor(4);

  h1->SetFillStyle(3005);
  h2->SetFillStyle(3004);
  h3->SetFillStyle(3005);


  for(int i=0; i<175; i++){
    f1 >> ch1 >> val1;
    f2 >> ch2 >> val2;
    f3 >> ch3 >> val3;

    f1s >> ch1s >> val1s;
    f2s >> ch2s >> val2s;
    f3s >> ch3s >> val3s;

    cout << ch1 << "  " << val1 << "\t\t";
    cout << ch2 << "  " << val2 << "\t\t";
    cout << ch3 << "  " << val3 << "\t\n";

    h1->SetBinContent(ch1+1,val1);
    h2->SetBinContent(ch2+1,val2);
    h3->SetBinContent(ch3+1,val3);

    h1s->SetBinContent(ch1s+1,val1s/0.357176);
    h2s->SetBinContent(ch2s+1,val2s/0.357176);
    h3s->SetBinContent(ch3s+1,val3s/0.357176);
  }

  t1 = TLatex(3, 0.070, "Response func.");
  t2 = TLatex(3, 0.063, "W_{2} = 10.0 mm/#mus");
  t3 = TLatex(3, 0.056, "W_{2} =  7.5 mm/#mus");

  ts = TLatex(2, 0.04,  "Shaded : 1.4 #mus shaping");
  te = TLatex(2, 0.033, "Empty  : 0.5 #mus shaping");

  t2.SetTextColor(2);
  t3.SetTextColor(4);

cout << " I   l "  <<  h1->Integral() <<"\n";
cout << " III l "  <<  h2->Integral() <<"\n";
cout << " III l "  <<  h3->Integral() <<"\n";
cout << " I   s "  <<  h1s->Integral() <<"\n";
cout << " II  s "  <<  h2s->Integral() <<"\n";
cout << " III s "  <<  h3s->Integral() <<"\n";

//  h2->Scale( 1. / h2->Integral() );
//  h3->Scale( 1. / h3->Integral() );
//  h1s->Scale( 1. / h1s->Integral() );
//  h2s->Scale( 1. / h2s->Integral() );
//  h3s->Scale( 1. / h3s->Integral() );

  TCanvas* canv = new TCanvas("canv", "canv", 800,800);
  gStyle->SetOptStat(0);
  h1s->Draw();
  h2s->Draw("same");
  h3s->Draw("same");
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  t1.Draw("same");
  t2.Draw("same");
  t3.Draw("same");
  te.Draw("same");
  ts.Draw("same");

  canv->Print("different_W2_shaping.png");

  f1.close();
  f2.close();
  f3.close();
  f1s.close();
  f2s.close();
  f3s.close();

}
