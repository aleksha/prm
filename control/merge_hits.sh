echo "";
echo "Merging all hits in tracking detectors";
cd output;
rm -rf all;
cp ../code/reco/merge_hits.py ./;
python3 merge_hits.py;
mv merge_hits.py scripts_done;
rm temp*.data;
mkdir all;
mv out.data all/;
cd ../;
echo "Done!";
echo "";
