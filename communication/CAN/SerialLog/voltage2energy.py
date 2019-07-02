import csv

import numpy as np

def voltage2energy( volt, curveX, curveY ):
    np.interp(volt, curveX, curveY)
