OUT="results.csv"

echo "n,t,d,result" > "$OUT"

N=(100000 1000000 10000000 100000000)
T=(1 2 4 8 16)
D=(u n e)

make clean
make

for d in "${D[@]}"; do
    for n in "${N[@]}"; do
        for t in "${T[@]}"; do

            echo "n = $n t = $t d = $d"

            result=$(./sort_program.exe "$n" "$t" "$d")

            echo "$n,$t,$d,$result" >> "$OUT"

        done
    done
done