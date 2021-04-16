# Beamfile

## How to get and convert beamfile

```bash
wget http://adzyuba.web.cern.ch/adzyuba/d/beamfile_prm_mu100.root
```

To create input file for Geant4 application to simulate beam noise 
one should edit and run `create_input_beam.py` scripts. It will
randomly select certain number of events and put them into an input file.
```bash
conda deactivate
conda activate pres-mc
ostap -b beamfile_prm_mu100.root create_input_beam.py
```
**Note:** same event can appear in the input file more than once!

## Brief description

> The beam file for the 100 GeV muon beam 7.4 m downstream of the last quadrupole.
> This is for the optimized focussed beam at the target. In the beam file the
> columns are arranged as step no. (not important), Particle Flag ( 2 = beam muon,
> 3= halo flagged muon), X (mm), Y (mm), Z (m), X’ (mrad), Y’ (mrad), P (GeV/c).
> It includes all particles within +- 3m transversely.
> 
> In Halo software, which is used to generate this beam file, any muon which
> touches any material of the beam line  (even if its few microns) are flagged as
> halo muons. Each row represents one event.
> 
> Coordinates:
> 
> Position	Beam line [m]	COMPASS [m]	Comment
>  Q36 (QUAD36)	1123.3		- 7.1
>  PRM Target	1129.4		- 1.0		May change
>  COMPASS origin	1130.4		+ 0.0
>  Beam file focus	1130.7		+ 0.3
>  SM1 (BEND10)	1134.0		+ 3.6
>  SM2 (BEND11)	1148.7		+18.3
