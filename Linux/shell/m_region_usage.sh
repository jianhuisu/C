#！/bin/bash
FSMAX="80"
remote_user='root'
remote_ip=(IP地址列表)
 ip_num='0'
while [ "$ip_num" -le "$(expr ${#remote_ip[@]} -l)"]
do
        read_num='1'
        ssh "$remote_user"@"${remote_ip[$ip_num]}"  df -h > /tmp/diskcheck_tmp
        grep '^/dev/*'  /tmp/diskcheck_tmp | awk '{print $5}'|sed 's/\%//g'  > /tmp/diskcheck_num_tmp
          while [ "$read_num" -le $(wc -l < /tmp/diskcheck_num_tmp) ]
            do
                    size=$(sed -n "$read_num" 'p'  /tmp/diskcheck_num_tmp)
                            if [ "size" -gt "$FSMAX" ]
                            then
                                    $(grep '^/dev/*'  /tmp/diskcheck_tmp |sed -n $read_num'p'  > /tmp/disk_check_mail)
                                    $(echo ${remote_ip[$ip_num]}) >> /tmp/disk_check_mail)
                                    $(mail  -s "diskcheck_alert"  admin  <  /tmp/disk_check_mail)
                            fi
                    read_num=$(expr  $read_num + 1)
            done
        ip_num=$(expr  $ip_num + 1)
done