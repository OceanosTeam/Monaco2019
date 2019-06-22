#!/bin/bash

touch logs/log.csv
# echo < /dev/ttyACM0
# tail -f /dev/ttyACM0 # >> logs/log.csv

# read -r line < /dev/ttyACM0
# echo -n $line >> logs/log.csv

cat /dev/ttyACM0
