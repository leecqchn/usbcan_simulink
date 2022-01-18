# usbcan_simulink
ZLG USB can s-function driver for simulink realtime.


### compile you usbcan driver.
this is a demo driver for usbcan-u-e serial(20), for another serial, just replace the device ID in can_conf.c can_read.c and can_transmit.c

eg. (mex  can_transmit.c -Lusbcan_lib\ -lControlCAN -Iusbcan_lib\ )

### get specific can id data from can_read s-function.
for test, we just get some CAN ID for me, if you need another can id and data, please change the can_read.c and re-compile the s-function.



### start simulink demo test.
A demo test model has been provided, which include can_conf, can_read and can_transimit.