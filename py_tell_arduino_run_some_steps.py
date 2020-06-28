import serial
import time

#ser = serial.Serial('/dev/ttyACM0', 9600)
ser = serial.Serial('/dev/ttyUSB0', 9600)

'''
ser = serial.Serial(
        port='/dev/ttyS0', #Replace ttyS0 with ttyAM0 for Pi1,Pi2,Pi0
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
'''

while 1:
    print('Input how many steps of RPi platform to move: ')
    input_str = input()
    print(input_str.encode())
    ser.write(input_str.encode())
    time.sleep(1)
    
    
        #ser.write("Write counter: %d \n"%(counter))
        #time.sleep(1)
        #counter += 1
