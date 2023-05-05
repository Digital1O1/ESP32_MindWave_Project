# Reference link : http://firmlyembedded.co.za/useful-python-script-to-send-and-receive-serial-data/
# https://github.com/xanthium-enterprises/CrossPlatform-Serial-Port-Programming-using-Python-and-PySerial
import time
import serial
import mindwave
serial_Port = serial.Serial('COM9')
serial_Port.baudrate = 115200
serial_Port.bytesize = 8
serial_Port.parity = 'N'
serial_Port.stopbits = 1
serial_Port.timeout = 0.050


count = 0
print(serial_Port.name)

while 1:
    # serial_Port.write(b'Hello')
    test = bytearray(str(count), 'utf8')
    serial_Port.write(test)
    serial_Port.write(b'\r\n')
    # serial_Port.write(b'\n')
    # serial_Port.write('\n')
    # serial_Port.write((count).encode())

    print(count)
    time.sleep(1)
    count += 1
