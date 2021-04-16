# prm

A simple `Geant4` application to simulate features of the backup solution
for an AMBER and PRES PRM runs.

## Software setup

### Enviorment

This project is tested with `conda` package solution.
First one have to setup and configure `conda`:
```bash
wget http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
source ~/miniconda3/etc/profile.d/conda.sh
conda config --add channels conda-forge
```

Second, create `Geant4` envoirment:
```bash
conda create --name g4-mc geant4 compilers cmake make
conda activate g4-mc
```

Third, create envoirment for `ESEPP`, `ROOT` and `OstapHEP`.
To setup enviorment, please, follow this: https://github.com/aleksha/pres-mc 

### Get source of the project

Now, let's get the project:
```bash
cd # you may want to choose other directory
git clone https://github.com/aleksha/prm.git
cd prm
```

### ESEPP preparation

It's better to use automatic config version for the `ESEPP`.
```bash
git clone https://github.com/nuramatov/esepp.git
cd esepp
make
```
Edit `config.ini` and run it:
```bash
cp ../configs/esepp/config.ini ./
python start.py config.ini
```

Instead of cloning from github one can download a frozen version:
```bash
wget http://adzyuba.web.cern.ch/adzyuba/d/esepp.tar.gz
tar zxvf esepp.tar.gz
cd esepp/
make
```

## Full event

The idea is to create events, which contains:
  1. Elastic scattering ( initial particle / scattered particle /  recoil proton )
  2. Beam noise (for certain beam frequency)
  3. Electronic noise

First as well as second step are done with a `Geant4` application.
The third is done with a `python` application. 

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
