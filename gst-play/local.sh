gst-launch-0.10 v4l2src device=/dev/video0 ! video/x-raw-rgb,width=800,height=600,depth=32 ! ffmpegcolorspace ! ximagesink
