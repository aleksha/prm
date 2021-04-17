echo "";
echo "Setup AMBER-pilot geometry";
mkdir build;
cd build;
cp -r -v ../code/g4app/pilot source
cd source;
cp -v ../../configs/geom/amber-pilot/geom_config.h ./;
cd ../../;
echo "Make output/ directory";
mkdir output;
mkdir output/scripts_done;
# ==== INIT LEPTON
mkdir output/init;
cd output/init;
cp -v ../../code/setup/setup_mac.py ./ ;
python setup_mac.py ;
cp -v ../../configs/seeds/seed_init seed;
cd ../../;
# ==== SCAT LEPTON
mkdir output/scat;
cd output/scat;
cp -v ../../code/setup/setup_mac.py ./ ;
python setup_mac.py ;
cp -v ../../configs/seeds/seed_scat seed;
cd ../../;
# ===== PROTON
mkdir output/prot;
cd output/prot;
cp -v ../../code/setup/setup_mac.py ./ ;
python setup_mac.py ;
cp -v setup_mac.py ../scripts_done/ ;
cp -v ../../configs/seeds/seed_prot seed;
cd ../../;
# ===== CREATING input_g4.txt
cd output
cp -r ../code/scattering/create.py ./;
ostap -b create.py;
mv init_lepton.txt init/input_g4.txt;
mv scat_lepton.txt scat/input_g4.txt;
mv scat_proton.txt prot/input_g4.txt;
mv create.py scripts_done;
# ===== BEAM NOISE
mkdir output/beam;
cp -r ../code/scattering/create_beam.py ./;
ostap -b create_beam.py;
mv rand_beam.txt run.mac beam/ ;
cp -r ../configs/seeds/seed_beam beam/seed;
echo "Setup is done. You can try to build app.";
echo "";
echo "Don't forget:";
echo "   conda activate g4-mc";
echo "";
