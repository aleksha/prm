cd noise;
python3 anode_noise.py;
cat temp_*txt > noise.data;
rm temp_*txt;
cd ../;
