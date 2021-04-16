echo "Setup PRES geometry"
cp -v ../configs/geom/pres/geom_config.h ../configs/geom/;
cp -v ../configs/geom/pres/PRMDetectorConstruction.hh ../source/include/ ;
cp -v ../configs/geom/pres/PRMDetectorConstruction.cc ../source/src/ ;
echo "Setup is done. You can try to build app."
