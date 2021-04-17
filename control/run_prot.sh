cd output/prot/;
cp -v ../../build/exec_PRM ./;
echo "Starting scattered proton app";
./exec_PRM run.mac >> inLOG;
echo "Done! (see output/prot/inLOG for details)";
cd ../../;
