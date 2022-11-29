
for i in {0..9}
do
    for j in {0..4}
    do
        ./play ./output/q$((i+1))-$((j)).csv $i
    done
done