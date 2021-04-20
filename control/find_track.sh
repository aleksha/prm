cd output;
cp -v ../code/reco/find_track.C .;
root -b find_track.C+;
rm *.d *.so *.pcm;
mv find_track.C scripts_done/;
if [ -d "all/" ]; then
  mv *png all/;
else
  mkdir all;
  mv *png all/;
fi
cd ../;
