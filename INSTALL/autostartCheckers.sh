#!/bin/bash

export DISPLAY=:0.0
FILE=/home/x64joxer/Checkers/flag.txt

while true; do

if [ -f $FILE ];
then
   killall Checkers
   rm $FILE
   echo "File $FILE exists."
else
   echo "File $FILE does not exist."
fi

if [ "$(pidof Checkers)" ]
  then
     sleep 10 	
  else
     /home/x64joxer/Checkers/Checkers &	    	
     sleep 10       
fi

done
