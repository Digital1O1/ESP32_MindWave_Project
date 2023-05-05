import mindwave, time

print("Program started")
# h1 = mindwave.Headset('/dev/tty.MindWave', '625f')
# h2 = mindwave.Headset('/dev/tty.MindWave2', 'a662')

print("Connecting headsets")
# With headband sticker
#h1 = mindwave.Headset('COM10')
#print(h1)
# No sticker
h2 = mindwave.Headset('COM10')
#print(h2)


#Issue is here
# With sticker
#h2 = mindwave.Headse0t('COM10')
print("Headsets connected")
time.sleep(2)

# h1.connect()
# print("Connecting h1...")
# while h1.status != 'connected':
#     time.sleep(0.5)
#     if h1.status == 'standby':
#         h1.connect()
#         print ("Retrying connect...")
# print ("Connected h1.")

#h2.connect()
# print ("Connecting h2...")
# while h2.status != 'connected':
#     time.sleep(0.5)
#     if h2.status == 'standby':
#         h2.connect()
#         print ("Retrying connect...")
#print ("Connected h2.")

while True:
    #print("Attention 1: %s, Meditation 1: %s \t Attention 2: %s, Meditation 2: %s" % (
    #    h1.attention, h1.meditation, h2.attention, h2.meditation))
    print ("Attention 2: %s, Meditation 2: %s" % (h2.attention, h2.meditation))
    time.sleep(.5)
