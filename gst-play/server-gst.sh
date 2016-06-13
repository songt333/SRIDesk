#!/bin/bash

function isnum
{
	if `echo $1 | grep -q [^[:digit:]]`; then
		return 1
	else
		return 0
	fi
}

dev=/dev/video0
width=1024
height=768
host=127.0.0.1

while getopts "d:h:w:t:" OPTION
do
	case $OPTION in
		d)
			if isnum $OPTARG ; then
				dev="/dev/video$OPTARG"
			else
				dev=$OPTARG
			fi
			;;
		h)
			height=$OPTARG
			;;
		w)
			width=$OPTARG
			;;
		t)
			host=$OPTARG
			;;

		?)
			exit 1
			;;
	esac
done

gst-launch-1.0 v4l2src device=$dev ! video/x-raw,format=BGRx,width=$width,height=$height ! videoconvert ! x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=$host port=1234
