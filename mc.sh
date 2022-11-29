make

for i in {0..500}
do
    ./play ./output/mc$((i+1)).csv 9
done

python3 mc.py