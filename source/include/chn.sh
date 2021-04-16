mv MUPActionInitialization.hh   PRMActionInitialization.hh  ; sed -i 's/MUP/PRM/g' PRMActionInitialization.hh  ;
mv MUPDetectorConstruction.hh   PRMDetectorConstruction.hh  ; sed -i 's/MUP/PRM/g' PRMDetectorConstruction.hh  ;
mv MUPEventAction.hh            PRMEventAction.hh           ; sed -i 's/MUP/PRM/g' PRMEventAction.hh           ;
mv MUPPrimaryGeneratorAction.hh PRMPrimaryGeneratorAction.hh; sed -i 's/MUP/PRM/g' PRMPrimaryGeneratorAction.hh;
mv MUPRunAction.hh              PRMRunAction.hh             ; sed -i 's/MUP/PRM/g' PRMRunAction.hh             ;
mv MUPSteppingAction.hh         PRMSteppingAction.hh        ; sed -i 's/MUP/PRM/g' PRMSteppingAction.hh        ;
