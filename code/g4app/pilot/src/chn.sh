mv MUPActionInitialization.cc   PRMActionInitialization.cc  ; sed -i 's/MUP/PRM/g' PRMActionInitialization.cc  ;
mv MUPDetectorConstruction.cc   PRMDetectorConstruction.cc  ; sed -i 's/MUP/PRM/g' PRMDetectorConstruction.cc  ;
mv MUPEventAction.cc            PRMEventAction.cc           ; sed -i 's/MUP/PRM/g' PRMEventAction.cc           ;
mv MUPPrimaryGeneratorAction.cc PRMPrimaryGeneratorAction.cc; sed -i 's/MUP/PRM/g' PRMPrimaryGeneratorAction.cc;
mv MUPRunAction.cc              PRMRunAction.cc             ; sed -i 's/MUP/PRM/g' PRMRunAction.cc             ;
mv MUPSteppingAction.cc         PRMSteppingAction.cc        ; sed -i 's/MUP/PRM/g' PRMSteppingAction.cc        ;
