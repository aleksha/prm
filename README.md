# prm

An application to simulate features of the backup solution
for an AMBER and PRES PRM runs. It uses Geant4. To start type:
```bash
cd # you may want to choose other directory
git clone https://github.com/aleksha/prm.git
cd prm
```

## Software setup

To setup software, please, go to `external` direcory 
and follow instructions in `README.md`.
This will allow you to:
  * Configure enviorment
  * Download and compile ESEPP event generator

Next, by running:
```bash
./prm get-ext
```
one can download beamfile and dump for the noise data.

## To start new project

To prepare to simulate AMBER pilot run event, type:
```bash
./prm setup-pilot
```
It will create `output` directories with proper subdirectories,
which contain mac and seed files, as well as `input_g4.txt`.

In future two other options will be available:
```bash
./prm setup-pilot
./prm setup-amber
```

### Electronic noise

See information in the `code/noise` directory.
The speeded-up version is in use.

A configuration file is `configs/noise/config_noise.py`.
Dump file should be in `externals/noise/` directory (see above).
To create noise events, please, use next command:
```bash
./prm run-noise
```


## Build `Geant4` app

First you must activete proper envoirment and then run command:
```bash
conda activate g4-mc
./prm build
```
As a result an `exec_PRM` application should be compiled.

**Note:** that this application always needs an `input_g4.txt` file with
particles to trace!


## Full event

The idea is to create events, which contains:
  1. Elastic scattering ( initial particle / scattered particle /  recoil proton )
  2. Beam noise (for certain beam frequency)
  3. Electronic noise

First as well as second step are done with a `Geant4` application.
The third is done with a `python` application. 


### Beam noise and scattering event

Next step is to run application for a beam noise.
It uses an input file, which must be created.
Follow instructions in `beamfile/README.md`.

Please, use `run_beam.sh` script to create particles, which will be later
used for the beam noise production.

To create three scattering particles see `scattering/` directory.
After input files will be created, please, use
`run_init.sh`, `run_scat.sh` and `run_prot.sh` scripts.

```bash
source scripts/run_beam.sh
source scripts/run_init.sh
source scripts/run_scat.sh
source scripts/run_prot.sh
```

You can also use `./prm` shell app.
```bash
./prm build
./prm run-all
./prm clean
```

**Note:** initial lepton goes backward in time (this will be 
accounted on the reco-stage).

