echo "Setup AMBER main geometry"
cp -v ../configs/geom/amber/geom_config.h ../configs/geom/;
cp -v ../configs/geom/amber/PRMDetectorConstruction.hh ../source/include/ ;
cp -v ../configs/geom/amber/PRMDetectorConstruction.cc ../source/src/ ;
echo "Setup is done. You can try to build app."
