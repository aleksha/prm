mkdir run_prot
cp -v scattering/scat_proton.txt run_prot/input_g4.txt
cp -v build_g4/exec_PRM run_prot/
cp -v configs/mac/run_prot.mac run_prot/run.mac
cp -v configs/seeds/seed_prot run_prot/seed
cd run_prot
echo "Starting proton tracking"
./exec_PRM run.mac >> inLOG
echo "Done! (see run_prot/inLOG for details)"
cd ../
