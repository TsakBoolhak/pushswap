#! /bin/bash

max=0
test_nb=10000
value_nb=9
min_val=1
max_val=9
for i in `seq 1 $test_nb`
do
	arg=`shuf -i $min_val-$max_val -n $value_nb`
	arg=`echo $arg | sed 's/\n/ /g'`
	current=`./push_swap $arg | wc -l`
	error=`./push_swap $arg | ./checker_linux $arg`
	if [ $error != "OK" ]
	then
		echo "$arg\n$error\n" >> error
	else
		echo "$arg\n$error\n" >> ok
	fi
	if [ $current -gt $max ]
	then
		max="$current"
		worst="$arg"
	fi
done
echo "for $test_nb different tests with $value_nb different random values between $min_val and $max_val:\nmax count of instructions is $max\nit was reached with this list : \n$worst"
echo "for $test_nb different tests with $value_nb different random values between $min_val and $max_val:\nmax count of instructions is $max\nit was reached with this list : \n$worst\n" >> results
