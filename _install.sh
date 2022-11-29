#!/bin/bash

cale=`pwd`
newcale="$cale/nscan"
# echo $newcale
sudo ln -s $newcale /usr/bin/nscan 2> /dev/null

if [[ $? -eq 0 ]]
then
    echo "Installing..."
    for i in {1..50}
    do
        echo -n "#"
        sleep 0.1
    done
    echo "#"
    echo "Done!"
else
    echo "File already exists!"
fi




