go mod init cPC


N_values=(5 6 7 8)
T_values=(1 4 16 64 256)

for N in "${N_values[@]}"; do
    for T in "${T_values[@]}"; do
        echo "Running ./teste $N $T"
        go run . $N $T
        echo "-----------------------"
    done
done

