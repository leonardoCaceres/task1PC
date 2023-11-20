#!/bin/bash

# Compile the C++ code with OpenMP
g++ cPC.cpp -o teste -fopenmp

# Define values for N and T
N_values=(5 6 7 8)
T_values=(1 4 16 64 256)

# Loop over N and T values and run the executable
for N in "${N_values[@]}"; do
    for T in "${T_values[@]}"; do
        echo "Running ./teste $N $T"
        ./teste $N $T
        echo "-----------------------"
    done
done

