#!/bin/bash
#
# Usage: script <username> <password> <build>
#
# Example ./copy_logs_from_production.sh marko hubbabubba current
#

username=x64joxer
password=root
destination_folder=/home/x64joxer/Pulpit
source_folder=Checkers

instance_1_server=192.168.0.12

servers=("$instance_1_server" "$instance_2_server" "$instance_3_server" "$instance_4_server" "$instance_5_server" "$instance_6_server" "$instance_7_server" "$instance_8_server" "$instance_9_server" )
i=1
for server in ${servers[@]}; do
  expect -c "
            # exp_internal 1 # uncomment for debugging
            spawn /usr/bin/scp -rp $folder $username@$server:$destination_folder 
            expect { 
              \"yes/no\" { send \"yes\r\"; exp_continue; } 
              \"*assword\" { send $password\r\n; interact } 
              eof { exit }
            }
            exit
            "
  let "i=i+1"
done
