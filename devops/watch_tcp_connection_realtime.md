实时监测统计tcp连接数

    watch -n 1 -d 'netstat -nt | grep ESTABLISHED | wc -l'