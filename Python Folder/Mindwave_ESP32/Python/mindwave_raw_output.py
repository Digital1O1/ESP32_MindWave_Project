import mindwave
import time

# Uncomment this if using Mac OS
# headset = mindwave.Headset('/dev/tty.MindWaveMobile-DevA')
print("CONNECTING TO HEADSET...")

headset = mindwave.Headset('COM11')
print("PROGRAM STARTED...")
time.sleep(2)

while True:
    time.sleep(.5)
    print("Raw value: %s, Attention: %s, Meditation: %s" %
          (headset.raw_value, headset.attention, headset.meditation))
    print("Waves: {}".format(headset.waves))
