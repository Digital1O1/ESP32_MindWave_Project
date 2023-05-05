import mindwave
import time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
import collections
import time
import datetime
import serial


import serial

from pprint import pprint

serial_Port = serial.Serial("COM9")
serial_Port.baudrate = 115200
serial_Port.bytesize = 8
serial_Port.parity = "N"
serial_Port.stopbits = 1
serial_Port.timeout = 0.050

current_time = time.time()

# headset = mindwave.Headset('/dev/tty.MindWaveMobile-DevA')
print("CONNECTING TO HEADSET")


headset = mindwave.Headset("COM10")
#headset.connect()
# headset.serial_close
# headset.serial_open

# headset = mindwave.Headset('COM10',"C464E3E8E9B3")
# headset2 = mindwave.Headset('COM12',"C464E3EAA308")

print("PROGRAM STARTED....")

# pprint(vars(headset))
# print("-----------------")
# pprint(vars(headset2))

# exit()

time.sleep(2)


# headset.raw_value = collections.deque(np.zeros(10))
# print("Raw Value: {}".format(headset.raw_value))
# print("Memory: {}".format(ram))

time = []
raw_values = []
attention_values = []


raw_values = collections.deque([], maxlen=10)
attention_values = collections.deque([], maxlen=10)
time = collections.deque([], maxlen=10)


def plot_Mindwave_data(i):
    # raw_values.popleft()

    ax.cla()
    ax1.cla()

    ax.set_title("RAW VALUES")
    ax.set_xlabel("Elasped Time (ms)")

    ax.set_ylabel("Signal Amplitude")
    current_time = datetime.datetime.now()
    time.append(current_time.strftime("%S.%f")[:-3])
    raw_values.append(abs(headset.raw_value))
    #ax.plot(time, raw_values)
    ax.set_xticklabels(time, rotation = 45)

    ax.plot(time, raw_values)
    # ax.set_ylim(0, 100)

    ax1.set_title("ATTENTION VALUES")
    ax1.set_xlabel("Elasped Time (ms)")

    ax1.set_ylabel("Signal Amplitude")
    # time.append(current_time.second)
    attention_values.append(headset.attention)
    ax1.plot(time, attention_values)
    ax1.set_xticklabels(time, rotation = 45)
    # ax1.set_xticklabels(rotation=45)

    ax1.plot(time, attention_values)
    # ax1.set_ylim(0, 100)

    dataToESP32 = bytearray(str(headset.attention), "utf8")
    serial_Port.write(dataToESP32)
    serial_Port.write(b"\r\n")

    print(
        "Raw value: %s, Attention: %s, Meditation: %s"
        % (headset.raw_value, headset.attention, headset.meditation)
    )


fig = plt.figure(figsize=(12, 6), facecolor="#DEDEDE")
ax = plt.subplot(121)
ax1 = plt.subplot(122)
ax.set_facecolor("#DEDEDE")
ax1.set_facecolor("#DEDEDE")

ani = FuncAnimation(fig, plot_Mindwave_data, interval=250)
plt.show()
