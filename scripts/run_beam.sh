mkdir run_beam
cp -v beamfile/rand_input.txt run_beam/input_g4.txt
cp -v build_g4/exec_PRM run_beam/
cp -v configs/mac/run_beam.mac run_beam/run.mac
cp -v configs/seeds/seed_beam run_beam/seed
cd run_beam
echo "Starting beam app"
./exec_PRM run.mac >> inLOG
echo "Done! (see run_beam/inLOG for details)"
cd ../
