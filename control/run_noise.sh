rm -rf output/noise ;
mkdir output/noise ;
cd output/noise ;
cp ../../code/noise/anode_noise.py ./ ;
cp ../../configs/noise/config_noise.py ./ ;
python3 anode_noise.py;
cat temp_*txt > noise.data;
rm temp_*txt config_noise.py anode_noise.py ;
cd ../../;
