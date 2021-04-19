import ROOT
import ostap.fixes.fixes
from ostap.core.core import cpp, Ostap
from ostap.core.core import pwd, cwd, ROOTCWD
from ostap.core.core import rootID, funcID, funID, fID, histoID, hID, dsID
from ostap.core.core import VE
from ostap.histos.histos import h1_axis, h2_axes, h3_axes
from ostap.histos.graphs import makeGraph, hToGraph, hToGraph2, hToGraph3, lw_graph
import ostap.trees.trees
import ostap.trees.cuts
import ostap.histos.param
import ostap.histos.compare
import ostap.io.root_file
import ostap.math.models
import ostap.fitting.roofit 
import ostap.fitting.models as Models

fname = "FADC.root"
dirs  = ["0010","0100","0300","0500","1000","1500","2000"]
freq  = [   10.,  100.,  300.,  500., 1000., 1500., 2000.]

rfiles = []
tts    = []

for d in dirs:
    rfiles.append( ROOT.TFile( d + "/" + fname,"READ") )
    
for rf in rfiles:
    tts.append( rf["out_tree"] )
    
def TotE( tt ):
    res = []
    for e in tt:
        E = 0.
        if e.is_fired_00:
            E += e.energy_00
        if e.is_fired_01:
            E += e.energy_01
        if e.is_fired_02:
            E += e.energy_02
        res.append( (E, e.inTp) )
    return res


data = []

for tt in tts:
    data.append( TotE( tt ) )
    
def Scatter( dd ):
	x = []
	y = []
	for d in dd:
		x.append( d[0] )
		y.append( d[1] )
	g = makeGraph(x,y)
	return g

gg = []
for dd in data:
    gg.append( Scatter( dd ) )


def SimpleCalib( g , suffix ):
    f = ROOT.TF1("fs_"+suffix,"pol1",0,100000)
    f.SetLineWidth(3)
    f.SetLineColor(4)
    r = g.Fit(f,"QS") 
    return f

fs = []
i=0
for g in gg:
    fs.append( SimpleCalib(g, dirs[i] ) )
    i+=1


from statistics import median, mean, stdev

def MedianCalib( d , suffix , steps=10, minY=1.4, maxY=1.6):
    f = ROOT.TF1("fm_"+suffix,"pol1",0,100000)
    f.SetLineWidth(3)
    f.SetLineColor(2)
    
    xm = []
    ym = []
    for s in range(steps):
        y_min = minY + s*(maxY-minY)/steps
        y_max = minY + (s+1)*(maxY-minY)/steps
        ym.append( 0.5*(y_max+y_min) )
        ds = []
        for pair in d:
            if pair[1]>y_min:
                if pair[1]<y_max:
                    ds.append( pair[0] )
        xm.append( median(ds) )
    gt = makeGraph(xm,ym)
    gt.SetMarkerSize(1)
    gt.SetMarkerStyle(24)
    gt.SetMarkerColor(2)
    rt = gt.Fit(f,"QS") 
    return f, gt

	

fm = []
gm = []
i=0
for d in data:
    ers = MedianCalib( d, dirs[i] )
    fm.append( ers[0] )
    gm.append( ers[1] )
    i+=1


cs_reso = []
cm_reso = []

i=0
xf = []
sf = []
mf = []

hs = ROOT.TH1F("hs",";;",100,-0.2,0.2)
hm = ROOT.TH1F("hm",";;",100,-0.2,0.2)
hs.blue()
hm.red()

gps2=[]
gpm2=[]
for dp in data:
    hs.Reset()
    hm.Reset()
    csr = []
    cmr = []
    for pp in dp:
        csr.append( fs[i].Eval(pp[0]) - pp[1] )
        hs.Fill( fs[i].Eval(pp[0]) - pp[1]  ) 
        cmr.append( fm[i].Eval(pp[0]) - pp[1] )
        hm.Fill( fm[i].Eval(pp[0]) - pp[1]  ) 
    print( dirs[i] + " kHz\t" + str( stdev( csr ) ) + "\t" + str( stdev(cmr) ) )
    xf.append( freq[i] )
    sf.append( stdev( csr ) )
    mf.append( stdev( cmr ) )
    cs_reso.append(csr)
    cm_reso.append(cmr)
    
    gaus_s = ROOT.TF1("gaus_s","gaus(0)",-0.08,0.08)
    gaus_m = ROOT.TF1("gaus_m","gaus(0)",-0.08,0.08)
    gaus_s.SetLineColor(4)
    gaus_m.SetLineColor(2)
    gaus_s.SetLineWidth(3)
    gaus_m.SetLineWidth(3)
    hs.Fit(gaus_s,"R")
    hm.Fit(gaus_m,"R")
    
    hs.Draw()
    hm.Draw("same")
    gps2.append( gaus_s.GetParameter(2) )
    gpm2.append( gaus_m.GetParameter(2) )
    canvas.Print("Reso_" + dirs[i] + ".png")
    gg[i].Draw("AP")
    gm[i].Draw("P same")
    canvas.Print("Calib_" + dirs[i] + ".png")
    i+=1
    
 
gfs = makeGraph(xf,sf)
gfm = makeGraph(xf,mf)
gfg = makeGraph(xf,gpm2)
gfl = makeGraph(xf,gps2)

gfs.SetMarkerStyle(20)
gfl.SetMarkerStyle(24)
gfm.SetMarkerStyle(20)
gfg.SetMarkerStyle(24)

gfs.SetMarkerColor(2)
gfl.SetMarkerColor(2)
gfm.SetMarkerColor(4)
gfg.SetMarkerColor(4)

gfs.SetLineColor(2)
gfl.SetLineColor(2)
gfm.SetLineColor(4)
gfg.SetLineColor(4)

gfs.SetLineWidth(2)
gfm.SetLineWidth(2)
gfg.SetLineWidth(2)
gfl.SetLineWidth(2)

gfg.SetLineStyle(7)
gfl.SetLineStyle(7)


gfm.SetMinimum(0)

gfm.Draw("APL")
gfs.Draw("PL same")
gfg.Draw("PL same")
gfl.Draw("PL same")
canvas.Print("FreqReso.png")
		
		
		
		
		
		
		
		
		
		
		
		
