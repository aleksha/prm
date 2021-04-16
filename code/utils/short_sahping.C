// Scale factor.
// #define SCALE 0.62
// #define SCALE 0.673286 // 1.4 µs shaping.
#define SCALE 1.885 // 0.5 µs shaping.

// Signal shaping function realized in preamplifiers.
Double_t shaping(double t)
{
   Double_t e1 = 0.02207760*exp(-3.64674*SCALE*t);
   Double_t e2 = -0.02525950*exp(-3.35196*SCALE*t)*cos(1.74266*SCALE*t);
   Double_t e3 = 0.00318191*exp(-2.32467*SCALE*t)*cos(3.57102*SCALE*t);
   Double_t e4 = 0.01342450*exp(-3.35196*SCALE*t)*sin(1.74266*SCALE*t);
   Double_t e5 = -0.00564406*exp(-2.32467*SCALE*t)*sin(3.57102*SCALE*t);
   return SCALE*945*(e1 + e2 + e3 + e4 + e5);
}
