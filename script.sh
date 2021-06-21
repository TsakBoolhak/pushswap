#! /bin/bash

for i in `seq 1 1`
do
    arg=`shuf -i 2-2000 -n 100 `
    echo $arg >list
    sed -i 's/ /\n/g' list
    sed -zi 's/solved\nin\n/solved in /g' list
    sed -zi 's/\ntries/ tries/g' list
    arg=`sed -z 's/\n/ /g' <<<"$arg" `
    ret=`./push_swap $arg`
    echo "$ret"
    if [ "$ret" ]
    then    
        error=`echo "$ret" | ./checker $arg 2>&1`
    else 
        error=`echo -n "$ret" | ./checker $arg 2>&1`
    fi
    echo -n $error >>error
   # if [[ $error != "OK" ]]
   # then 
   #      echo $arg >>error
   # fi
    ret=`echo "$ret" | wc -l`
    if [[ $ret -ge 0 ]]
    then
        echo " solved in $ret tries">>error
        echo " solved in $ret tries">>list
	echo "" >>list
	echo " solved in $ret tries"
    fi

done
