echo "";
echo "Merging all hits in tracking detectors";
cd output;
rm -rf all;
cp ../code/reco/merge_hits.py ./;
python3 merge_hits.py;
mv merge_hits.py scripts_done;
mkdir all;
mv temp1.data all/out.true;
mv out.data all/;
cd ../;
echo "Done!";
echo "";
