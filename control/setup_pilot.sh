echo "";
echo "Setup AMBER-pilot geometry";
mkdir build;
cd build;
cp -r -v ../code/g4app/pilot source
cd source;
cp -v ../../configs/geom/amber-pilot/geom_config.h ./;
cd ../../;
echo "Make output/ directory";
mkdir output;
echo "Setup is done. You can try to build app.";
echo "";
