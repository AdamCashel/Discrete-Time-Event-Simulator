#!/bin/bash
rm sim.data
for ((i = 1; i <= 30; i++)); do
 ./program2 1 $i 0.06 0.01
 cp sim.data /data/sim-1-$i-001.data
done