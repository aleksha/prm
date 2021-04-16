mkdir run_init
cp -v scattering/init_lepton.txt run_init/input_g4.txt
cp -v build_g4/exec_PRM run_init/
cp -v configs/mac/run_init.mac run_init/run.mac
cp -v configs/seeds/seed_init run_init/seed
cd run_init
echo "Starting init lepton tracking"
./exec_PRM run.mac >> inLOG
echo "Done! (see run_init/inLOG for details)"
cd ../
