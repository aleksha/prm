cd output;
cp -v ../code/reco/find_track.C ./;
root -b find_track.C+;
cp -v ../analyse/fit_ang.py ./;
cp -v ../analyse/Functions.py ./;
ostap -b fit_ang.py ;
mv find_track.C fit_ang.py Functions.py scripts_done/;
if [ -d "all/" ]; then
  mv *png *root all/;
else
  mkdir all;
  mv *png *root all/;
fi
rm -rf *.d *.so *.pcm *pycache*;
cd ../;
