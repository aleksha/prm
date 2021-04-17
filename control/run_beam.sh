cd output/beam/;
cp -v ../../build/exec_PRM ./;
echo "Starting beam app";
./exec_PRM run.mac >> inLOG;
echo "Done! (see output/beam/inLOG for details)";
cd ../../;
