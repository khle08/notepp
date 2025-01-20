#!/bin/bash

# sudo apt install util-linux

# e.g. Target time: 7:30 AM tomorrow
# >>> ./wakeup.sh tomorrow 7:30
# The linux system will be suspended until 7:30

target_time=$(date -d "$1 $2" +%s)
current_time=$(date +%s)
seconds_diff=$((target_time - current_time))

# Wake up the system after the calculated time
sudo rtcwake -m mem -s $seconds_diff