mkdir run_scat
cp -v scattering/scat_lepton.txt run_scat/input_g4.txt
cp -v build_g4/exec_PRM run_scat/
cp -v configs/mac/run_scat.mac run_scat/run.mac
cp -v configs/seeds/seed_scat run_scat/seed
cd run_scat
echo "Starting scat lepton tracking"
./exec_PRM run.mac >> inLOG
echo "Done! (see run_scat/inLOG for details)"
cd ../
