echo "";
echo "Merging all hits in tracking detectors";
cd output;
rm -rf all;
cp ../code/reco/merge_all.py ./;
python3 merge_all.py;
mv merge_all.py scripts_done;
mkdir all;
mv temp1.data all/out.true;
rm temp*.data;
mv out.data tpc.data all/;
cd ../;
echo "Done!";
echo "";
