
# electronic-noise

This project contains a tool to create a spectrum of the electronic noise
for the Flash ADC used with ACTAF. The code is tested with Python 3, but 
is expected to run with Python 2.7 as well.

More on https://github.com/aleksha/electronic-noise

## How to use tool

To generate events:
```bash
conda activate pres-mc
wget http://adzyuba.web.cern.ch/adzyuba/d/dump.txt
python3 anode_noise.py
cat temp_*txt > noise.data
rm temp_*txt
```

Generated events will be stored into `noise.data` file.
Each line will contain a ADC value separated by space-character.