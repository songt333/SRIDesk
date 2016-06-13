#!/bin/bash

function isnum
{
	if `echo $1 | grep -q [^[:digit:]]`; then
		return 1
	else
		return 0
	fi
}

disk=
ram=512
res=1024x768
dev=/dev/video0
driver=std

while getopts "h:m:r:v:d:" OPTION
do
	case $OPTION in
		h)
			disk=$OPTARG
			;;
		m)
			ram=$OPTARG
			;;
		r)
			res=$OPTARG
			;;
		v)
			if isnum $OPTARG ; then
				dev="/dev/video$OPTARG"
			else
				dev=$OPTARG
			fi
			;;
		d)
			driver=$OPTARG
			;;

		?)
			exit 1
			;;
	esac
done

if [ -z $disk ]; then
	echo "no image specified!"
	exit 1
fi

~/local/bin/qemu-system-x86_64 -hda $disk -m $ram -video $res -vdev $dev -vga $driver -usbdevice tablet
