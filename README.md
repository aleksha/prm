# prm

A simple `Geant4` application to simulate features of the backup solution
for an AMBER and PRES PRM runs. To start type:
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

By running
```bash
./prm get-ext
```
one can download beamfile and dump for the noise data.



## Full event

The idea is to create events, which contains:
  1. Elastic scattering ( initial particle / scattered particle /  recoil proton )
  2. Beam noise (for certain beam frequency)
  3. Electronic noise

First as well as second step are done with a `Geant4` application.
The third is done with a `python` application. 

### Choose subproject


For PRES experiment:
```bash
./prm setup-pres
```

For AMBER pilot run:
```bash
./prm setup-pilot
```

For AMBER main run:
```bash
./prm setup-amber
```

### Build `Geant4` app

```bash
mkdir build_g4
cd build_g4
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ ../source
make -j4
```
As a result an `exec_PRM` application should be compiled.

You can use a `build_g4.sh` script to do this.
```bash
source scripts/build_g4.sh
```

**Note:** that this application always needs an `input_g4.txt` file with
particles to trace!

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

### Electronic noise

See information in the `noise` directory.
The speeded-up version is in use.
