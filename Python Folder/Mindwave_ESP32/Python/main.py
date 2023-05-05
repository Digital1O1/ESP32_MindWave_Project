import mindwave
import time
import serial

serial_Port = serial.Serial('COM9')
serial_Port.baudrate = 115200
serial_Port.bytesize = 8
serial_Port.parity = 'N'
serial_Port.stopbits = 1
serial_Port.timeout = 0.050


# Uncomment this if using Mac OS
# headset = mindwave.Headset('/dev/tty.MindWaveMobile-DevA')
print("CONNECTING TO HEADSET...")
# time.sleep(7)

headset = mindwave.Headset('COM11')
# print("Headset value : ", headset)
print("PROGRAM STARTED...")
time.sleep(2)

while True:
    time.sleep(.5)
    test = bytearray(str(headset.attention), 'utf8')
    serial_Port.write(test)
    serial_Port.write(b'\r\n')
    print("Raw value: %s, Attention: %s" %(headset.raw_value, headset.attention))
    #print("Raw value: %s, Attention: %s, Meditation: %s" %(headset.raw_value, headset.attention, headset.meditation))
    #print("Raw value : %s Attention : %s",headset.raw_value, headset.attention)
#     print("Raw value: %s, Attention: %s, Meditation: %s" %
#           (headset.raw_value, headset.attention, headset.meditation))
#     print("Waves: {}".format(headset.waves))
