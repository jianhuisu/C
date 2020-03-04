#!/bin/bash

for item in $( find /etc/ -name passwd )
do
    cat -n $item
done

# equal => find /etc/ -name passwd | xargs cat -n