echo "Setup AMBER-pilot geometry"
cp -v ../configs/geom/pilot/geom_config.h ../configs/geom/;
cp -v ../configs/geom/pilot/PRMDetectorConstruction.hh ../source/include/ ;
cp -v ../configs/geom/pilot/PRMDetectorConstruction.cc ../source/src/ ;
echo "Setup is done. You can try to build app."
