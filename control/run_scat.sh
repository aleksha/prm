cd output/scat/;
cp -v ../../build/exec_PRM ./;
echo "Starting scattered lepton app";
./exec_PRM run.mac >> inLOG;
echo "Done! (see output/scat/inLOG for details)";
cd ../../;
