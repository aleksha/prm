echo "prm: build Geant4 app"
cd build
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ source/
make -j4
cd ../
echo "Done!"
