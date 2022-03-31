#!/bin/python3

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


Vdata = np.genfromtxt('oceanos_cell_discharge_capacity_14s.csv', dtype=float, delimiter=',', names=True)
vx = Vdata['voltage']
vy = Vdata['Percentage']
f = interpolate.interp1d(vx, vy)

# print(vx)

energy = f(57.0)


print(energy)
