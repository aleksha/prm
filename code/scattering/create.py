#===============================================================================
exec(open("../configs/global_config.py").read())
#===============================================================================
EVENTS = EVENTS_GEN
#===============================================================================
rfile = ROOT.TFile('../external/beam/beamfile_prm_mu100.root', "READ")
rfile.ls()
tree = rfile["BeamFile"]
#===============================================================================
efile = ROOT.TFile("../external/esepp/\"events\"_mu-.root", "READ")
efile.ls()
ntp = efile["ntp"]
#===============================================================================
ev     = 0
length = len( tree )
in_list = []
while ev<EVENTS:
    tree.GetEntry( ROOT.gRandom.Integer(length) )
    if USE_CORE:
        while tree.particleFlag!=2:
            tree.GetEntry( ROOT.gRandom.Integer(length) )
    in_list.append( (13, tree.X, tree.Y, -6299., tree.dXdZ*0.001, tree.dYdZ*0.001, 100. ) )
    ev+=1
#===============================================================================
from math import sin, cos, asin, pi, sqrt
esepp_init_list = []
esepp_scat_list = []
esepp_prot_list = []
m_l = 0.105658
m_p = 0.938272
for e in in_list:
    idx = in_list.index(e)
    Z_scat = ROOT.gRandom.Rndm()*800.-400.
    dZ = Z_scat - e[3]
    X_scat = e[1] + dZ*sin(e[4])
    Y_scat = e[2] + dZ*sin(e[5])
    ntp.GetEntry( idx )
    esepp_init_list.append( (e[0] , X_scat, Y_scat, Z_scat, -100.*e[4], -100.*e[5], -100.) )
    direction = ROOT.TVector3(e[4],e[5], cos( asin( sqrt(e[4]**2+e[5]**2) ) ) ).Unit()
    lepton = ROOT.TVector3()
    proton = ROOT.TVector3()
    l_p = sqrt( (0.001*ntp.E_l)**2 - m_l**2 )
    p_p = sqrt( (0.001*ntp.E_p)**2 - m_p**2 )
    lepton.SetMagThetaPhi( l_p, ntp.theta_l, ntp.phi_l )
    proton.SetMagThetaPhi( p_p, ntp.theta_p, ntp.phi_p )
    # transforms v1 from the rotated frame (z' parallel to direction, x' in the theta plane 
    #   and y' in the xy plane as well as perpendicular to the theta plane) to the (x,y,z) frame
    lepton.RotateUz(direction)
    proton.RotateUz(direction)
    lpt = l_p*lepton.Unit()
    prt = p_p*proton.Unit()
    esepp_scat_list.append( ( e[0] , X_scat, Y_scat, Z_scat, lpt.X(), lpt.Y(), lpt.Z() ) )
    esepp_prot_list.append( ( 2212 , X_scat, Y_scat, Z_scat, prt.X(), prt.Y(), prt.Z() ) )
#===============================================================================
def list2file( lst, fname ):
    out_file = open( fname ,"w" )
    for ev in lst:
        idx = lst.index( ev )
        ss  = str( idx   ) + " "
        ss += str( ev[0] ) + " "
        ss += str( ev[1] ) + " "
        ss += str( ev[2] ) + " "
        ss += str( ev[3] ) + " "
        ss += str( ev[4] ) + " "
        ss += str( ev[5] ) + " "
        ss += str( ev[6] ) + " 0.0\n" # scattering occurs in t=0
        out_file.write( ss )
    out_file.close()
#===============================================================================
list2file( esepp_init_list, "init_lepton.txt" )
list2file( esepp_scat_list, "scat_lepton.txt" )
list2file( esepp_prot_list, "scat_proton.txt" )

rfile.Close()
efile.Close()

