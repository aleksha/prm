#-------------------------------------------------------------------------------
import ostap.fitting.models as Models
from   ostap.utils.timing import timing
from   ostap.histos.histos  import h1_axis
from Functions import *
#-------------------------------------------------------------------------------
rfile = ROOT.TFile("histo_trk.root","READ")
hh = rfile["hAng"]
#ds = rfile["ds_k"]
#-------------------------------------------------------------------------------
im = ROOT.RooRealVar ('im'   , 'im'                 ,   200. , 1500. )
pk = ROOT.RooRealVar ('pk'   , 'peak   '   , 525. ,  450. , 600. )
sg = ROOT.RooRealVar ('sg'   , 'sigma'     , 30,  10 , 60 )
#-------------------------------------------------------------------------------
sig_ga = Models.Gauss_pdf( 'sig_ga', xvar=im,   mean=pk, sigma=sg )
bkg0 = Models.Bkg_pdf ( 'bkg0' , xvar = im , power = 0 )
#-------------------------------------------------------------------------------
model= Models.Fit1D   ( signal = sig_ga , background = bkg0 )
#-------------------------------------------------------------------------------
r, w = model.fitHisto( hh , draw=True , silent=True)
#    r, w = model.fitTo(ds, draw=True, nbins=100, ncpu=1)
#-------------------------------------------------------------------------------
print(r)
#-------------------------------------------------------------------------------
h = w.pullHist()
draw_param( r, w, h, 90, im, 1.3*hh.GetMaximum(), name="Angle", XTitle ="Angle",
                Prefix="f" , Type="png", var_Units = "#murad")
#-------------------------------------------------------------------------------
