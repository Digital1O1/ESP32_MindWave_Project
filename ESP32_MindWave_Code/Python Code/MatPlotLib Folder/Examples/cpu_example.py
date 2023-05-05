# Reference : https://towardsdatascience.com/plotting-live-data-with-matplotlib-d871fac7500b

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
import psutil
import collections

'''
    Deque
        - Double ended queue
        - Ordered collection of items similar to the queue
'''


cpu = collections.deque(np.zeros(10))
ram = collections.deque(np.zeros(10))
# print("CPU: {}".format(cpu))
# print("Memory: {}".format(ram))


def my_function():
    cpu.popleft()
    cpu.append(psutil.cpu_percent(interval=1))
    ram.popleft()
    ram.append(psutil.virtual_memory().percent)


cpu = collections.deque(np.zeros(10))
ram = collections.deque(np.zeros(10))
# test
my_function()
my_function()
my_function()
print("CPU: {}".format(cpu))
print("Memory: {}".format(ram))

# function to update the data
def my_function(i):
    # get data
    cpu.popleft()
    cpu.append(psutil.cpu_percent())
    ram.popleft()
    
    ram.append(psutil.virtual_memory().percent)
    # clear axis
    ax.cla()
    ax1.cla()
    # plot cpu
    ax.set_title("CPU USAGE")
    ax.set_ylabel('CPU RESOURCES USED')
    ax.plot(cpu)
    ax.scatter(len(cpu)-1, cpu[-1])
    ax.text(len(cpu)-1, cpu[-1]+2, "{}%".format(cpu[-1]))
    ax.set_ylim(0,100)
    # plot memory
    ax1.set_title("RAM USAGE")
    ax1.set_ylabel('RAM RESOURCES USED')

    ax1.plot(ram)
    ax1.scatter(len(ram)-1, ram[-1])
    ax1.text(len(ram)-1, ram[-1]+2, "{}%".format(ram[-1]))
    ax1.set_ylim(0,100)
    
    
# start collections with zeros
cpu = collections.deque(np.zeros(10))
ram = collections.deque(np.zeros(10))
# define and adjust figure
fig = plt.figure(figsize=(12,6), facecolor='#DEDEDE')
ax = plt.subplot(121)
ax1 = plt.subplot(122)
ax.set_facecolor('#DEDEDE')
ax1.set_facecolor('#DEDEDE')

# animate
ani = FuncAnimation(fig, my_function, interval=500)
plt.show()