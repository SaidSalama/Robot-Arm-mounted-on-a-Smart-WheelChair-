# -*- coding: utf-8 -*-
"""
Created on Sun Jun 25 11:21:18 2023

@author: saids
"""
'''
import serial
import serial.tools.list_ports as list_ports
#from voice_control import Vocal_Command

all_ports = list_ports.comports()
print(all_ports)

# Each entry in the `all_ports` list is a serial device. Check it's
# description and device attributes to learn more
first_serial_device = all_ports[0]
print(first_serial_device.device)  # the `port_name`
print(first_serial_device.description)  # perhaps helpful to know if this is your device

port_name = "COM5"  # the name / address we found for our device

ser = serial.Serial(
    port=port_name,
    baudrate=9600,
    bytesize=serial.EIGHTBITS,  # set this to the amount of data you want to send
    )

# the information we want to send: 8 bits = 1 byte
#byte_to_send =  # send a "1"
ser.write(b'A') 

# After measurements are done, close the connection
ser.close()

#print(Vocal_Command.Get_Direction())

# Python code transmits a byte to Arduino /Microcontroller
'''

from voice_control import Vocal_Command



#############################################################################

import serial

import time

SerialObj = serial.Serial('COM5') # COMxx   format on Windows
                                   # ttyUSBx format on Linux

SerialObj.baudrate = 9600  # set Baud rate to 9600
SerialObj.bytesize = 8     # Number of data bits = 8
SerialObj.parity   ='E'    # No parity
SerialObj.stopbits = 1     # Number of Stop bits = 1
    
time.sleep(1)
while True:
    d=Vocal_Command.Get_Direction()
    if 'stop' in d:
        SerialObj.write(b'4')
        break
    elif 'right' in d:
        SerialObj.write(b'2')
    elif 'left' in d:
        SerialObj.write(b'3')
    elif 'go' in d:
        SerialObj.write(b'1')
    time.sleep(1)
