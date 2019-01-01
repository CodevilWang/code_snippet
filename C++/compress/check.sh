#!/bin/bash
i=0
while ((i < 100)); do
    ./p4d
    if [ $? -ne 0 ];then
        echo "failed."
        exit 1 
    fi
    sleep 2
    ((i+=1))
done
