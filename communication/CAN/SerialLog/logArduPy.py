#!/usr/bin/python3

import time
import serial
from serial import Serial
from datetime import datetime
import struct
import sys
# from collections import namedtuple
import numpy as np
import mysql.connector as sql
from scipy import interpolate

from sys import argv
import gps
import requests
import socket

lat = 0
lon = 0
spe_gps = 0

# battFile = open('oceanos_cell_discharge_capacity_14s.csv', mode='r')
# csv_reader = csv.DictReader(battFile)
Vdata = np.genfromtxt('oceanos_cell_discharge_capacity_14s.csv', dtype=float, delimiter=',', names=True)
vx = Vdata['voltage']
vy = Vdata['Percentage']
fvolt = interpolate.interp1d(vx, vy)

localdb = sql.connect(
host="127.0.0.1",
user="root",
password="a75033207",
database = "ocdb"
)

session = gps.gps("localhost", "2947")
session.stream(gps.WATCH_ENABLE | gps.WATCH_NEWSTYLE)

'''
hostdb = sql.connect(
host="sql126.main-hosting.eu",
user="u322154547_root",
passwd="oceanos_2019",
database = "test"
)
'''

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
f.write('date, time, microseconds, speed, throttle, current, voltage, contTemp, motTemp, motErrCode, cntrStat, swStat, Discharge\n')
f.close()

while 1 :
        ser.write(b'S')

        arduinoInput = ser.readline()
        out = datetime.now().strftime("%d/%m/%Y, %H:%M:%S, %f") + ', ' + str(arduinoInput,'ASCII')

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
        
 
        rep = session.next()
        localcursor = localdb.cursor()
        try :
            if (rep["class"] == "TPV"):
                lat = rep.lat
                lon = rep.lon
                spe_gps = rep.speed
                sendQuery_GPS = "INSERT INTO gps (Latitude, Longitude, Speed) VALUES ('"+str(lat)+"','"+str(lon)+"','"+str(spe_gps)+"')"
                localcursor.execute(sendQuery_GPS)
                localdb.commit()
        except Exception as e :
            pass
        
        # print(Vdata['Percentage'])
        energy = fvolt(float(voltage))

        # print(energy)
        out = out.strip('\n').strip('\r') + ', ' + str(energy) + ', ' + str(lat) + ', ' + str(lon) + ', ' + str(spe_gps) +'\n'

        f= open(filename,"a+")
        f.write("%s" % out)
        f.close()
        
        print(out)
        sendQuery_CAN = "INSERT INTO motor (speed, throttle, current, voltage, contrTemp, motorTemp, motErrCode, cntrStat, swStat, energy) VALUES ('"+speed+"','"+throttle+"','"+current+"','"+voltage+"','"+contTemp+"','"+motTemp+"','"+motErrCode+"','"+cntrStat+"','"+swStat+"','"+str(energy)+"')"
        
        localcursor.execute(sendQuery_CAN)
        localdb.commit()
                
        '''
        hostcursor = hostdb.cursor()
        hostcursor.execute("INSERT INTO motor (speed, throttle, current, voltage, contrTemp, motorTemp, motErrCode, cntrStat, swStat, energy) VALUES ('"+speed+"','"+throttle+"','"+current+"','"+voltage+"','"+contTemp+"','"+motTemp+"','"+motErrCode+"','"+cntrStat+"','"+swStat+"','"+str(energy)+"')")
        hostdb.commit()
        '''
        
