sudo modprobe v4l2loopback
./v4l2loopback-ctl set-caps "video/x-raw-rgb,red_mask=255,green_mask=65280,blue_mask=16711680, width=800,height=600" /dev/video0
