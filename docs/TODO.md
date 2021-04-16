# TO do list

## Done
  * Check geometry to have proper pixel detector
  * Stepping action for detectors
  * Add scintillators
  * ESEPP install guide
  * Electronic noise simu
  * Rename build and run scripts (beam, scat and noise)
  * Scattering PrimaryGenerator action (pcode)
  * Change ideology for a `Geant4` app
  * Seeds management
  * mac-files mannagement
  * Scattering event generator
  * Shell scripts to `scripts/`
  * Add .gitignore
  * `docs/` dir
  * `./prm` bash application
  * noise commands to `./prm`
  * Add frozen version of ESEPP
  * TPC geometry check
  * Numbering to input files
  * TPC signal builder
  * Hits accounting
  * Detector setup config


## Updating in progress
  * Setup notes
  * Transfer to a new repository -- `prm/`

## To be done
  * Create beam noise event
  * Merge event

## Don't forget
  * ESEPP give a single energy!

## Not possible 
  * activate conda env from script 

This is because environmental variables are only passed to child 
processes. There isn't a built-in way of setting environmental variables 
of the parent shell. This is good in most cases and prevents programs from 
affecting the operating environment from which they were called

