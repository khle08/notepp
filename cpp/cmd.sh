#!/bin/bash
#!/usr/bin/env bash

# If using the 1st method below, the one of the above 2 shebang lines will not necessary.
# If using the 2nd method below, one of the shebang line should be included above.

# [!] When terminal window is used to run script, it is useful to send PW to "sudo".
#     However, when the program is demonized in background, PW can nolonger be accepted.
#     The only way to run program behind with root permission is to execute it in "sudo su" mode.

if [ "$1" = "jetson" ]
then
    # 1st method
    echo "$2" | sudo -S sh -c "echo $3 > /sys/devices/pwm-fan/target_pwm"
    # 2nd method
    # sudo -S <<< "$2" sh -c "echo $3 > /sys/devices/pwm-fan/target_pwm"
    # 3rd method
    # sh -c "echo $3 > /sys/devices/pwm-fan/target_pwm"
else
    # Do sth to control the fan of other linux system
    echo "null"
fi
