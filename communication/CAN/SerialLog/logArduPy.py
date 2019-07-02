#!/usr/bin/python3

import time
import serial
from serial import Serial
from datetime import datetime
import struct
import sys
# from collections import namedtuple
import csv

import mysql.connector as sql



mydb = sql.connect(
host="sql126.main-hosting.eu",
user="u322154547_root",
passwd="oceanos_2019",
database = "test"
)



# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
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
        out = datetime.now().strftime("%d/%m/%Y, %H:%M:%S, %f") + ', ' + str(arduinoInput,'ASCII')

        print(out)

        f= open(filename,"a+")
        f.write("%s" % out)
        f.close()

        elems = out.split(',')

        speed = elems[0+3].strip()
        throttle = elems[1+3].strip()
        current = elems[2+3].strip()
        voltage = elems[3+3].strip()
        contTemp = elems[4+3].strip()
        motTemp = elems[5+3].strip()
        motErrCode = elems[6+3].strip()
        cntrStat = elems[7+3].strip()
        swStat = elems[8+3].strip()

        mycursor = mydb.cursor()
        mycursor.execute("INSERT INTO motor (speed, throttle, current, voltage, contrTemp, motorTemp, motErrCode, cntrStat, swStat) VALUES ('"+speed+"','"+throttle+"','"+current+"','"+voltage+"','"+contTemp+"','"+motTemp+"','"+motErrCode+"','"+cntrStat+"','"+swStat+"')")
        mydb.commit()
