import mindwave
import time
import serial

print("Establish serial port 1 ")
serial_Port = serial.Serial('COM9')
serial_Port.baudrate = 115200
serial_Port.bytesize = 8
serial_Port.parity = 'N'
serial_Port.stopbits = 1
serial_Port.timeout = 0.050
print("Establish serial port CONNECTED")

# print("Establish serial port 2 ")

# Headset with stickers
# serial_Port2 = serial.Serial('COM11')
# serial_Port2.baudrate = 115200
# serial_Port2.bytesize = 8
# serial_Port2.parity = 'N'
# serial_Port2.stopbits = 1
# serial_Port2.timeout = 0.050
# print("Establish serial port CONNECTED2")

# Uncomment this if using Mac OS
# headset = mindwave.Headset('/dev/tty.MindWaveMobile-DevA')
print("CONNECTING TO HEADSET...")
# time.sleep(7)

headset = mindwave.Headset('COM10')
# headset2 = mindwave.Headset('COM11')
# print("Headset value : ", headset2)
# # print("Headset value : ", headset)
# print("PROGRAM STARTED...")
# time.sleep(2)

while True:
    time.sleep(.5)
    test = bytearray(str(headset.attention), 'utf8')
    serial_Port.write(test)
    serial_Port.write(b'\r\n')
#    print("Attention : ", headset.attention)
    print("Raw value: %s, Attention: %s, Meditation: %s" %
          (headset.raw_value, headset.attention, headset.meditation))
#     print("Waves: {}".format(headset.waves))
    # print("Raw value: %s, Attention: %s, Meditation: %s" %
    #       (headset2.raw_value, headset2.attention, headset2.meditation))
    # print("Waves: {}".format(headset2.waves))
