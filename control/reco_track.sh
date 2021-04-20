cd output;
cp -v ../code/reco/reco_track.C .;
root -b reco_track.C+;
rm *.d *.so *.pcm;
mv reco_track.C scripts_done/;
cd ../;
