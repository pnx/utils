#!/bin/bash

PING=ping

while [ 1 ]; do
	# By the Power of Grayskull!
	$PING -w 3 -c 1 www.google.se &> /dev/null
	if [ $? -eq 0 ]; then
		# I have the power!
		echo "Interwebs is up!";
		break;
	fi
	sleep 10
done
