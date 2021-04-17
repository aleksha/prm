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
out_file = open("rand_beam.txt","w")
beam_events = 0
while ev<EVENTS:
    times = []
    current_time = 0.0
    while current_time>-100000.:  #100us =100000ns
        current_time -= ROOT.gRandom.Exp( 1000./BEAM_FREQ )
        times.append( current_time )
    current_time = 0.0
    while current_time<100000.:  #100us =100000ns
        current_time += ROOT.gRandom.Exp( 1000./BEAM_FREQ )
        times.append( current_time )
    for tb in times:
        tree.GetEntry( ROOT.gRandom.Integer(length) )
        if USE_CORE:
            while tree.particleFlag!=2:
                tree.GetEntry( ROOT.gRandom.Integer(length) )
        ss  = str(ev) + " 13 " + str(tree.X) + " " + str(tree.Y) + " -6299. "
        ss += str(tree.P*tree.dXdZ*0.001) + " " + str(tree.P*tree.dYdZ*0.001) + " "  + str(tree.P) + " "
        ss += str(tb) + "\n"
        beam_events += 1
        out_file.write( ss )
    if not ev%10:
        print( str(ev)+ " BEAM EVENTS")
    ev+=1
#===============================================================================
out_file.close()
rfile.Close()
efile.Close()
#===============================================================================
mac_prefix = """ /control/verbose 0
/tracking/verbose 0
/event/verbose 0
/run/verbose 0
/random/resetEngineFrom seed
/run/initialize
/run/beamOn"""

with open("run.mac","w") as mac:
    mac.write( mac_prefix + " " +str( beam_events ) + "\n" )

