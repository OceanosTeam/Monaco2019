#!/bin/python

import time
import serial
from serial import Serial
from datetime import datetime
import struct
import sys
# from collections import namedtuple
import csv

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM1',
    baudrate=9600,
    timeout = 1
)

ser.isOpen()
ser.flush()

# ser.setRTS(True)

time.sleep(2)


print('Log app for arduino CAN.')

now = datetime.now() # current date and time
date_time = now.strftime("%d/%m/%Y, %H:%M:%S")
filename = "logs/can_log_"+now.strftime("%d%m%Y-%H-%M")+".csv";
f= open(filename,"w+")
f.write(date_time + '\n')
f.write('date, time, microseconds, speed, throttle, current, voltage, contTemp, motTemp, motErrCode, cntrStat, swStat\n')
f.close()

# input=1
while 1 :
        ser.write(b'S')
        # time.sleep(0.1)

        # arduinoInput = ser.read(26)
        # speed, throttle, current, voltage, contTemp, motTemp, motErrCode, cntrStat, swStat = struct.unpack("<iHffiiHcc", arduinoInput)
        # out = str(speed) + ', ' + str(throttle) + ', ' + str(current) + ', ' + str(voltage) + ', ' + str(contTemp) + ', ' + str(motTemp) + ', ' + str(motErrCode) + ', ' + str(cntrStat) + ', ' + str(swStat) + '\n'

        arduinoInput = ser.readline()
        out = str(arduinoInput,'ASCII')

        print(datetime.now().strftime("%d/%m/%Y, %H:%M:%S, %f") + ', ' + out)

        f= open(filename,"a+")
        f.write("%s" % out)
        f.close()

        elems = out.split(',')
        
        speed = int(elems[0])
        throttle = int(elems[1])
        current = float(elems[2])
        voltage = float(elems[3])
        contTemp = int(elems[4])
        motTemp = int(elems[5])
        motErrCode = int(elems[6])
        cntrStat = int(elems[7])
        swStat = int(elems[8])
        # print(str(speed))
        # x = float(n) for n in line.split(',')
