#!/bin/python

import time
import serial
from serial import Serial
from datetime import datetime

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()


print('Log app for arduino CAN.')

now = datetime.now() # current date and time
date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
f= open("logs/log.csv","w+")
f.write(date_time)
f.close();

# input=1
while 1 :
    # # get keyboard input
    # input = raw_input(">> ")
    #     # Python 3 users
    #     # input = input(">> ")
    # if input == 'exit':
    #     ser.close()
    #     exit()
    # else:
    #     # send the character to the device
    #     # (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
    #     ser.write(input + '\r\n')
        out = ""
    #     # let's wait one second before reading output (let's give device time to answer)
    #     time.sleep(1)
        while ser.inWaiting() > 0:
            out += str(ser.readline(), 'ASCII')

        if out != '':
            # print(out)

            f= open("logs/log.csv","a+")
            f.write("%s" % out)
            f.close();
