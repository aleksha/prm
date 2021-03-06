# External dependencies

Envoirment, external data as well as event generator have to be set 
in advance.

## Enviorment

This project is tested with `conda` package solution.
First one have to setup and configure `conda`:
```bash
cd ~/
wget http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
source ~/miniconda3/etc/profile.d/conda.sh
conda config --add channels conda-forge
```

Second, create `Geant4` envoirment:
```bash
conda env create -f environment.yml
conda activate prm-env
```
During the rest of the tutorials you are expected to have `prm-env` environment activated.


## Still need :-(

Second, create `Geant4` envoirment:
```bash
conda create --name g4-mc geant4 compilers cmake make
conda activate g4-mc
```

## Event generator

It's better to use automatic config version for the `ESEPP`.
```bash
git clone https://github.com/nuramatov/esepp.git
cd esepp
make
```

Instead of cloning from github one can download a frozen version:
```bash
wget http://adzyuba.web.cern.ch/adzyuba/d/esepp.tar.gz
tar zxvf esepp.tar.gz
cd esepp/
make
```

If you want to run it manually, please, edit `config.ini` and run it:
```bash
cp ../../configs/esepp/config.ini ./
python start.py config.ini
```
or run
```bash
./prm esepp
```
in the project direcory.

## Other externals

### Beamfile

Beam properties for the AMBER experiment are provided by the beam group.
The file is use either to randomly select a beam event, either to 
generate beam-like muon (a task for future).

### Noise data

To generate a noise event an input file with noise example is needed.
It contains 5000 examples of FADC spectra taken with alpha source for
the anodes far from alpha track.

### How to get them?

This should work presuming that you are in `external/` directory:

```bash
rm -rf beam noise;
mkdir beam noise;
cd noise;
wget http://adzyuba.web.cern.ch/adzyuba/d/dump.txt;
cd ../beam;
wget http://adzyuba.web.cern.ch/adzyuba/d/beamfile_prm_mu100.root
cd ../../;
```
