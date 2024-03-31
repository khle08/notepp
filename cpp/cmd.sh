#!/bin/bash
#!/usr/bin/env bash

bluetoothctl << EOF
EOF

# # It takes some time to get the scanning result
# nmcli d wifi rescan
# # s: second / m: minute / h: hour / d: day
# sleep 5s
# # After scanning, the list will be more complete
# nmcli d wifi list
