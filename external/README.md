# External dependencies

## Enviorment

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

If you want to run it manually? please, edit `config.ini` and run it:
```bash
cp ../configs/esepp/config.ini ./
python start.py config.ini
```

## Beamfile


## Noise data
