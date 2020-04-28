#!/bin/bash

DATE=$(date +%F" "%H:%M)
IP=$(ifconfig eno1 | awk '{print $2}')
MAIL="guangsujiange"

if ! which vmstat &>/dev/null; then
  echo "vmstat command no found, Please install procps package."
  exit 1
fi

US=$(vmstat 5 5 | awk  '{if(NR==3) print $13}')
SY=$(vmstat 5 5 | awk  '{if(NR==3) print $14}')
IDLE=$(vmstat 5 5 | awk '{if(NR==3) print $15}')
WAIT=$(vmstat 5 5 | awk '{if(NR==3) print $16}')

echo $DATE