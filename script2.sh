#! /bin/bash

max=0
test_nb=1000
value_nb=100
min_val=0
max_val=5000
for i in `seq 1 $test_nb`
do
	arg=`shuf -i $min_val-$max_val -n $value_nb`
	current=`./push_swap $arg | wc -l`
	if [ $current -gt $max ]
	then
		max="$current"
		worst="$arg"
	fi
done
worst=`echo $worst | sed 's/\n/ /g'`
echo "for $test_nb different tests with $value_nb different random values between $min_val and $max_val:\nmax count of instructions is $max\nit was reached with this list : \n$worst"
echo "for $test_nb different tests with $value_nb different random values between $min_val and $max_val:\nmax count of instructions is $max\nit was reached with this list : \n$worst\n" >> results
