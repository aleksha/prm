cd output;
cp -v ../code/reco/reco_track.C .;
root -b reco_track.C+;
rm *.d *.so *.pcm;
mv reco_track.C scripts_done/;
if [ -d "all/" ]; then
  mv *png all/;
else
  mkdir all;
  mv *png all/;
fi
cd ../;
