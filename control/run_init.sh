cd output/init/;
cp -v ../../build/exec_PRM ./;
echo "Starting init app";
./exec_PRM run.mac >> inLOG;
echo "Done! (see output/init/inLOG for details)";
cd ../../;
