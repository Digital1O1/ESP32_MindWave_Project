import mindwave
import time

# headset = mindwave.Headset('/dev/tty.MindWaveMobile-DevA')
print("CONNECTING TO HEADSET")
headset = mindwave.Headset('COM10')
print("PROGRAM STARTED....")

time.sleep(2)

while True:
    time.sleep(.5)
    print("Raw value: %s, Attention: %s, Meditation: %s" %
          (headset.raw_value, headset.attention, headset.meditation))
    print("Waves: {}".format(headset.waves))
