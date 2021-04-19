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
Beam evants are also generated here.

In future two other options will be available:
```bash
./prm setup-pilot
./prm setup-amber
```

## Build `Geant4` app

First you must activate proper envoirment and then run command:
```bash
./prm build
```
As a result an `exec_PRM` application should be compiled.

**Note:** that this application always needs an `input_g4.txt` file with
particles to trace!


## Events with a beam noise

Next command will run four prepared runners:
```bash
./prm run
```

For the initial lepton times will be reversed by a dedicated script,
which is in the chain. All events stored in different
`out.data`  and `tpc.data` files  will be merged and stored in
the `output/all` directory.


## Electronic noise

See information in the `code/noise` directory.
The speeded-up version is in use.

A configuration file is `configs/noise/config_noise.py`.
Dump file should be in `externals/noise/` directory (see above).
To create noise events, please, use next command:
```bash
./prm run-noise
```

## Reconstruction

### TPC signals

```bash
./prm reco-tpc
```

This will prepare `all/FADC.root` where FADC histograms, derived informationa 
as well as Monte-Carlo truth information is stored;



## Bunch of working commands

Assuming externals are installed

```bash
./prm clean
./prm setup-pilot
./prm build
./prm run
./prm run-noise
./prm reco-tpc
```

## Data analysis

Some scripts can be found in the `analysis/` directory.
