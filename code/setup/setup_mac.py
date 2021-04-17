
mac_prefix = """ /control/verbose 0
/tracking/verbose 0
/event/verbose 0
/run/verbose 0
/random/resetEngineFrom seed
/run/initialize
/run/beamOn"""
exec(open("../../configs/global_config.py").read())

with open("run.mac","w") as mac:
    mac.write( mac_prefix + " " +str( EVENTS_GEN ) + "\n" )
