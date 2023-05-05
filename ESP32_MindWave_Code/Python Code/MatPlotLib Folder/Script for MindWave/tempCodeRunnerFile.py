    dataToESP32 = bytearray(str(headset.attention), "utf8")
    serial_Port.write(dataToESP32)
    serial_Port.write(b"\r\n")