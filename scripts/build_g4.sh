echo "\nprm: build Geant4 app \n"
rm -rf build_g4
mkdir build_g4
cd build_g4
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ ../source
make -j4
cd ../
echo "Done!"
