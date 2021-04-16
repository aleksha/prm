# Ostap  session by adzyuba started at Tue Mar  2 16:11:49 2021
# Command from CWD=/home/adzyuba/amber-prm-pilot-run/beamfile 
# ostap beamfile_prm_mu100.root
rfile.ls()
tree = rfile["BeamFile"]
tree.Print()
tree.Draw("Y:X","particleFlag==2","colz")
h_xy = ROOT.TH2F("h_xy",";;",80,-40,40,80,-40,40)
tree.Draw("Y:X>>h_xy","particleFlag==2")
h_xy.Draw("colz")
canvas >> "xy_profile_mm"
ls
tree.Draw("dYdZ:dXdZ","particleFlag==2","colz")
h_dvg = ROOT.TH2F("h_dvg",";;",50,-2.5,2.5,50,-2.5,2.5)
tree.Draw("dYdZ:dXdZ>>h_dvg","particleFlag==2")
h_dvg.Draw("colz")
canvas >> "dvg_xy_mrad"
ls
import scipy.stats as stat
stat.dir()
stat.ls()
stat.pearsonr()
x=[] ; y=[]; dx=[]; dy=[]
for ev in tree.withCuts("particleFlag==2"):
    x.append( tree.X )
    y.append( tree.Y )
    dx.append( tree.dXdZ )
    dy.append( tree.dYdZ )
    
stat.pearsonr(x,y)
help(stat.pearsonr)
stat.pearsonr(x,dx)
stat.pearsonr(y,dy)
tree.Draw("X:dXdZ","particleFlag==2","colz")
tree.Draw("Y:dYdZ","particleFlag==2","colz")
tree.Draw("P","particleFlag==2")
len(x)
h_xdx = ROOT.TH2F("h_xdx",";;",80,-40,40,2.5,50,-2.5,2.5)
h_ydy = ROOT.TH2F("h_ydy",";;",80,-40,40,50,-2.5,2.5)
h_xdx = ROOT.TH2F("h_xdx",";;",80,-40,40,50,-2.5,2.5)
tree.Draw("Y:dYdZ>>h_ydy","particleFlag==2","colz")
tree.Draw("dYdZ:Y>>h_ydy","particleFlag==2","colz")
h_ydy.Draw("colz")
tree.Draw("dXdZ:X>>h_xdx","particleFlag==2","colz")
h_xdx.Draw("colz")
help( ROOT.TFoam )
tree.Draw("dXdZ:Y","particleFlag==2","colz")
tree.Draw("dYdZ:X","particleFlag==2","colz")
tree.Draw("dYdZ:P","particleFlag==2","colz")
tree.Draw("dXdZ:P","particleFlag==2","colz")
tree.Draw("X:P","particleFlag==2","colz")
tree.Draw("Y:P","particleFlag==2","colz")
tree.Draw("Y:X","particleFlag==2","colz")
tree.Draw("Y","particleFlag==2","colz")
tree.Draw("X","particleFlag==2","colz")
tree.Draw("Y","particleFlag==2","colz")
tree.statCovs()
tree.statCov()
tree.statCov("X","Y")
tree.statVar("X")
# Ostap  session by adzyuba   ended at Tue Mar  2 17:18:07 2021 [3978.4s]
