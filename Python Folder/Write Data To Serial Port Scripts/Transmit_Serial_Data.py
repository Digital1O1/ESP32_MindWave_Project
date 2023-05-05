import time
import serial

ser = serial.Serial('COM9', 115200, timeout=0.050)
count = 0

while 1:
    ser.write(count)
    print("Sending to serial port : ", count)
    time.sleep(1)
    count += 1
