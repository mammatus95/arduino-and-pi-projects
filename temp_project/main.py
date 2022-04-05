import serial
import time
from datetime import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import numpy as np

dht11_hum  = []
dht11_temp = []
resistance = []
temp_r     = []
date_stamp = []

def pick_data(line_string,time_stamp):
    line_string = str(line_string).replace("\\r\\n'","").replace("b'","")
    #print(line_string)
    data = line_string.split(";")
    dht11_hum.append(float(data[1]))
    dht11_temp.append(float(data[0]))
    resistance.append(float(data[2]))
    temp_r.append(float(data[3]))
    date_stamp.append(time_stamp)
    print(float(data[1]),";",data[0],";",data[2],";",data[3],";",time_stamp)

def create_plot(dht11_temp,temp_r,date_stamp):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    
    ax.plot(date_stamp,dht11_temp,'b-',label="Temp DHT11")
    ax.plot(date_stamp,temp_r,'r--',label="Temp DHT11")
    ax.xaxis.set_major_formatter(mdates.DateFormatter('%m.%d %H:%M'))
    if len(date_stamp) < 150:
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=1))
    elif (len(date_stamp) < 700):
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=3))
    else:
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=5))
    #ax.tick_params(axis='x', labelrotation=45)
    plt.legend()
    plt.savefig("messdaten_" + now.strftime("%d.%m.%Y") + ".png")
    plt.close()

# adapt name (baud rate has to be the same than in the arduino sketch)
s = serial.Serial('/dev/ttyACM0', 9600)
#s.open() not needed anymore
# Arduino resets after a serial connection
#time.sleep(5)

i=1
try:
    while True:
        time.sleep(5)
        response = s.readline()
        now = datetime.today()
        try:
            pick_data(response,now)
            if (i % 5) == 0:
                create_plot(dht11_temp,temp_r,date_stamp)
        except:
            print(response)
            pass

        i+=1
except KeyboardInterrupt:
    s.close()
except:
    print(response)
    s.close()