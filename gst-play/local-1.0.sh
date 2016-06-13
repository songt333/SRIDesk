gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,format=BGRx,width=800,height=600 ! videoconvert ! ximagesink
