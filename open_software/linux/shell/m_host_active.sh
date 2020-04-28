#!/bin/bash
if ping -c 1 172.16.226.70 > /dev/null; then
        echo "OK."
else
        echo "NO!"
fi
