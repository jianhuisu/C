## 语法结构

#### 三种循环

for

    for i in $(ls -l) ; do
        echo $i
    done

while

    #!/bin/bash
    read PW
    
    while [ "$PW" != "secret" ]
    do
      echo "please try again"
      read PW
    done
    
    echo "success login "

until

    #!/bin/bash
    
    COUNTER=20
    until [ $COUNTER -lt 10 ]; do
        echo COUNTER $COUNTER
    let COUNTER-=1
    done

#### switch

    #!/bin/bash
    
    read -p "input your name :" name

    case $name in
            "xusanduo")
            echo $name
            ;;

            "xusanduo1")
            echo $name
            ;;
            "xusanduo2")
            echo $name
            ;;
            "xusanduo3")
            echo $name
            ;;
            *)
            echo "DEFAULT"
            ;;
    esac