#!/bin/bash

# Compiler le programme C
gcc task3.c -o task3

# Nombre d'itérations
nombre_executions=1000
temps_total=0
max_elapsed_time=0  # Variable to store the maximum elapsed time

for ((i = 0; i < nombre_executions; i++)); do
    start_time=$(date +%s%N)  # Get start time in nanoseconds

    # Your program execution
    ./task3

    end_time=$(date +%s%N)    # Get end time in nanoseconds
    elapsed_time=$((end_time - start_time))

    # Convert nanoseconds to milliseconds
    elapsed_time_ms=$(echo "scale=3; $elapsed_time / 1000000" | bc)

    temps_total=$(echo "$temps_total + $elapsed_time_ms" | bc -l)

    # Check if the current iteration has a higher elapsed time
    if ((elapsed_time > max_elapsed_time)); then
        max_elapsed_time=$elapsed_time
    fi
done

temps_moyen=$(echo "scale=3; $temps_total / $nombre_executions" | bc -l)

# Convert the maximum elapsed time to milliseconds
max_elapsed_time_ms=$(echo "scale=3; $max_elapsed_time / 1000000" | bc -l)

echo "Temps moyen d'execution sur $nombre_executions iterations : $temps_moyen milliseconds"
echo "Temps maximum d'execution sur $nombre_executions iterations : $max_elapsed_time_ms milliseconds"

