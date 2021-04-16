#===============================================================================
EVENTS   = 5000
X_POS    =    0.
Y_POS    =   18.
Z_POS    = -380.
T_P      = 2
USE_CORE = True
reDirect = True
#===============================================================================
rfile = ROOT.TFile('../beamfile/beamfile_prm_mu100.root', "READ")
rfile.ls()
tree = rfile["BeamFile"]
#===============================================================================
efile = ROOT.TFile("../esepp/\"events\"_mu-.root", "READ")
efile.ls()
ntp = efile["ntp"]
#===============================================================================
ev     = 0
length = len( tree )
in_list = []
while ev<EVENTS:
    in_list.append( (13, X_POS, Y_POS, -6299., 0., 0., 100. ) )
    ev+=1
#===============================================================================
from math import sin, cos, asin, pi, sqrt
esepp_init_list = []
esepp_scat_list = []
esepp_prot_list = []
m_l = 0.105658
m_p = 0.938272
ent = 0
for e in in_list:
    idx = in_list.index(e)
    Z_scat = Z_POS
    dZ = Z_scat - e[3]
    X_scat = e[1] + dZ*sin(e[4])
    Y_scat = e[2] + dZ*sin(e[5])
    esepp_init_list.append( (e[0] , X_scat, Y_scat, Z_scat, -100.*e[4], -100.*e[5], -100.) )
    lepton = ROOT.TVector3()
    proton = ROOT.TVector3()
    E_l = 100000.
    E_p = (m_p + T_P)*1000.
    l_p = sqrt( (0.001*E_l)**2 - m_l**2 )
    p_p = sqrt( (0.001*E_p)**2 - m_p**2 )
    lepton.SetMagThetaPhi( l_p, 0, 0 )
    proton.SetMagThetaPhi( p_p, 0.5*pi, 0 )
    lpt = l_p*lepton.Unit()
    prt = p_p*proton.Unit()
    esepp_scat_list.append( ( e[0] , X_scat, Y_scat, Z_scat, lpt.X(), lpt.Y(), lpt.Z() ) )
    esepp_prot_list.append( ( 2212 , X_scat, Y_scat, Z_scat, prt.X(), prt.Y(), prt.Z() ) )
    if len(esepp_prot_list)>EVENTS:
        break
    else:
        print(len(esepp_prot_list))
#===============================================================================
print( len(esepp_prot_list) )
#===============================================================================
def list2file( lst, fname ):
    out_file = open( fname ,"w" )
    idx=0
    for ev in lst:
        ss  = str( idx   ) + " "
        ss += str( ev[0] ) + " "
        ss += str( ev[1] ) + " "
        ss += str( ev[2] ) + " "
        ss += str( ev[3] ) + " "
        ss += str( ev[4] ) + " "
        ss += str( ev[5] ) + " "
        ss += str( ev[6] ) + "\n"
        out_file.write( ss )
        idx += 1
    out_file.close()
#===============================================================================
list2file( esepp_init_list, "init_lepton.txt" )
list2file( esepp_scat_list, "scat_lepton.txt" )
list2file( esepp_prot_list, "scat_proton.txt" )

rfile.Close()
efile.Close()

