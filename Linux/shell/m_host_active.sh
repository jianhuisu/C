#!/bin/bash
if ping -c 1 192.168.1.1 >/dev/null;then
        echo "OK."
else
        echo "NO!"
fi
