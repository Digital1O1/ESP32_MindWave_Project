import mindwave
import time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
import collections
import time
import datetime
import serial
import random
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

# print("COLLECTING 10 UNIQUE EEG DATA POINTS WHEN PROGRAM STARTS")
# print("HAVE USER FOCUS ON A KEYWORD")


headset = mindwave.Headset("COM11")
count_down = 5

# for _ in range(5):
#     print("Program starting in : ", count_down)
#     count_down -= 1
#     time.sleep(1)
print("PROGRAM STARTED")


time.sleep(2)

print("SAMPLING IN PROGRESS...")

time = []
raw_values = []
attention_values = []
threshold_values = []
attention_average = []
ignore_value = 0
sample_flag = 0
# sample_counter = 0
sample_counter = 0
eeg_data_point = 0

raw_values = collections.deque([], maxlen=10)
attention_values = collections.deque([], maxlen=10)
threshold_values = collections.deque([], maxlen=10)
time = collections.deque([], maxlen=10)


def plot_Mindwave_data(i):
    global sample_counter
    global attention_average
    global threshold
    global sample_flag
    global old_value
    global ignore_value
    # raw_values.popleft()

    ax.cla()
    ax1.cla()

    ax.set_title("RAW VALUES")
    ax.set_xlabel("Elasped Time (ms)")
    ax.set_ylabel("Signal Amplitude")
    current_time = datetime.datetime.now()
    time.append(current_time.strftime("%S.%f")[:-3])
    raw_values.append(abs(headset.raw_value))
    # ax.plot(time, raw_values)
    ax.set_xticklabels(time, rotation=45)
    ax.plot(time, raw_values)
    # ax.set_ylim(0, 100)

    ax1.set_title("ATTENTION VALUES")
    ax1.set_xlabel("Elasped Time (ms)")
    ax1.set_ylabel("Signal Amplitude")

    # time.append(current_time.second)
    attention_values.append(headset.attention)
    new_value = int(headset.attention)

    # ax1.plot(time, attention_values)
    # ax1.plot(time, attention_values, label="Attention Values")
    # ax1.plot(time, threshold_values, label="Set Threshold")
    # ax1.set_xticklabels(time, rotation=45)
    # ax1.set_xticklabels(rotation=45)
    # ax1.plot(time, attention_values)
    # ax1.set_ylim(0, 100)

    # Put values into list here and iterate sample counter
    if sample_flag == 0 and sample_counter != 10 and old_value != new_value:
        # attention_average = new_value
        attention_average.append(new_value)
        sample_counter += 1
        print("COLLECTED %s / 10 EEG DATA POINTS" % (sample_counter))

    # Ignore if values are the same
    if old_value == new_value:
        # print("Incoming value : ", random2)
        # print("Old value : ", old_value)
        ignore_value = new_value

    # Calculate average of the first 10 samples
    if sample_counter == 10 and sample_flag == 0:
        print("\nSAMPLING COMPLETE!")
        print("CALCULATING EEG THRESHOLD...")
        threshold = sum(attention_average) / len(attention_average)
        print("THRESHOLD TO BREAK : ", threshold)
        # print("Flag status : ", sample_flag)
        sample_flag = 1

    threshold_values.append(threshold)
    ax1.plot(time, attention_values, label="Attention Values")
    ax1.plot(time, threshold_values, label="Set Threshold")

    ax1.set_xticklabels(time, rotation=45)
    # ax1.set_xticklabels(rotation=45)
    #ax1.plot(time, attention_values)
    # ax1.set_ylim(0, 100)

    ax1.legend(loc="upper right", shadow=True, fancybox=True)

    if new_value > threshold and sample_flag == 1:
        print(
            "\nCurrent threshold value [ %s ] || Attention value sent to ESP [ %s ] "
            % (threshold, new_value),
        )
        # print("Sent to esp : ", new_value)
        # print(
        #     "Raw value: %s, Attention: %s, Meditation: %s"
        #     % (headset.raw_value, headset.attention, headset.meditation)
        # )
        #dataToESP32 = bytearray(str(headset.attention), "utf8")
        dataToESP32 = bytearray(str(1), "utf8")
        serial_Port.write(dataToESP32)
        serial_Port.write(b"\r\n")
    else:
        dataToESP32 = bytearray(str(0), "utf8")
        serial_Port.write(dataToESP32)
        serial_Port.write(b"\r\n")

    old_value = headset.attention


threshold = 0
old_value = 0
fig = plt.figure(figsize=(12, 6), facecolor="#DEDEDE")
ax = plt.subplot(121)
ax1 = plt.subplot(122)
ax.set_facecolor("#DEDEDE")
ax1.set_facecolor("#DEDEDE")

ani = FuncAnimation(fig, plot_Mindwave_data, interval=250, cache_frame_data=False )
plt.show()
