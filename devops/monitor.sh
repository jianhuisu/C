#!/bin/bash

# desk space
# monitor space ,when Use% outnumber 70% , send mail

for LINE in $(df | grep -v Filesystem)
do
    # trans every line to a  array use xiaokuohao
    # arr=($LINE)
    #echo $(arr[1])
    #IFS=$IFS_old
    echo $LINE
done
