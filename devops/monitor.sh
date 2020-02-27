#!/bin/bash

# Description: monitor host disk space
# Author:   guangsu
# 为什么你记住暗恋对象的电话只用一遍 如果你能参透这其中的奥秘 这一本书就会进入到你的脑海

local_ip=$(ifconfig eno1 | grep 'inet ' | awk '{print $2}')
mail_to=root
std_line=90

function send_mail() {
  echo "warning : $1 disk usage is greater than $3% " | mail -s "$2"  $2
}

# monitor space ,when Use% outnumber 70% , send mail
for LINE in $(df -hP | awk '{if(NR>1) print int($5)}')
do
    if [ $LINE -ge $std_line ]; then
      send_mail $local_ip $mail_to $std_line
    fi
done
