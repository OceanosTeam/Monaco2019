#!/bin/python

import time
import serial
from serial import Serial
from datetime import datetime
import struct
import sys
from collections import namedtuple

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=115200,
    # parity=serial.PARITY_ODD,
    # stopbits=serial.STOPBITS_TWO,
    # bytesize=serial.SEVENBITS,
    timeout = 1
)

ser.isOpen()
ser.flush()

# ser.setRTS(True)

time.sleep(2)


print('Log app for arduino CAN.')

now = datetime.now() # current date and time
date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
f= open("logs/log.csv","w+")
f.write(date_time + '\n')
f.write('speed, throttle, current, voltage, contTemp, motTemp, motErrCode, cntrStat, swStat\n')
f.close()

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
        # out = ""
    #     # let's wait one second before reading output (let's give device time to answer)
    #     time.sleep(1)
        # byte = struct.pack('>B',0x53)
        # byte = b'\x53'
        # print(str(sys.getsizeof(byte)))
        ser.write(b'S')

        arduinoInput = ser.read(26)
        speed, throttle, current, voltage, contTemp, motTemp, motErrCode, cntrStat, swStat = struct.unpack("<iHffiiHcc", arduinoInput)

        print(str(speed))
        out = str(speed) + ', ' + str(throttle) + ', ' + str(current) + ', ' + str(voltage) + ', ' + str(contTemp) + ', ' + str(motTemp) + ', ' + str(motErrCode) + ', ' + str(cntrStat) + ', ' + str(swStat) + '\n'

        f= open("logs/log.csv","a+")
        f.write("%s" % out)
        f.close();
