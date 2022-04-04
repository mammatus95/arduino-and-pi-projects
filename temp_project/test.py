import serial
import time

# adapt name (baud rate has to be the same than in the arduino sketch)
s = serial.Serial('/dev/ttyACM0', 9600)
#s.open() not needed anymore

# Arduino resets after a serial connection
print("Waiting 5s for Arduino...")
time.sleep(5)

s.write('test')
try:
    while True:
        response = s.readline()
        print(response)
except KeyboardInterrupt:
    s.close()
except:
    s.close()