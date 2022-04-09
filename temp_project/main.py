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

def calc_ntc2(RT):
    TR = 298.15 #K #reference temperature 25°C
    RR = 4700 #Ohm #reference resistance
    B = 3500  #3500 //3950
    # 4050 temp changes are to low
    RT *= 10 #convert to Ohm

    temp = TR/(1-(TR/B)*np.log(RR/RT))
    return temp - 273.15

def pick_data(line_string,time_stamp):
    line_string = str(line_string).replace("\\r\\n'","").replace("b'","")
    #print(line_string)
    data = line_string.split(";")
    dht11_hum.append(float(data[0]))
    dht11_temp.append(float(data[1]))
    resistance.append(float(data[2]))
    temp_r.append(float(data[3]))
    print(float(data[1]),";",data[0],";",data[2],";",data[3],";",time_stamp)

def create_plot(dht11_temp,temp_r1,date_stamp):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    
    ax.plot(date_stamp,dht11_temp,'b-',label="Temp DHT11")
    ax.plot(date_stamp,temp_r1,'r-',label="Temp NTC 4k7")
    ax.xaxis.set_major_formatter(mdates.DateFormatter('%m.%d %H:%M'))
    if len(date_stamp) < 100:
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=1))
    elif (len(date_stamp) < 300):
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=3))
    elif (len(date_stamp) < 500):
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=5))
    else:
        ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=10))
        ax.tick_params(axis='x', labelrotation=45)
    plt.title("Temepraturmessung " + now.strftime("%d.%m.%Y"))
    plt.legend()
    plt.savefig("messdaten_" + now.strftime("%d.%m.%Y") + ".png")
    plt.close()
    
    """
    # Create some mock data
    t = np.arange(0.01, 10.0, 0.01)
    data1 = dht11_temp.to_numpy()
    data2 = np.sin(2 * np.pi * t)

    fig, ax1 = plt.subplots()

    color = 'tab:red'
    ax1.set_xlabel('time (s)')
    ax1.set_ylabel('exp', color=color)
    ax1.plot(t, data1, color=color)
    ax1.tick_params(axis='y', labelcolor=color)

    ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

    color = 'tab:blue'
    ax2.set_ylabel('sin', color=color)  # we already handled the x-label with ax1
    ax2.plot(t, data2, color=color)
    ax2.tick_params(axis='y', labelcolor=color)

    fig.tight_layout()  # otherwise the right y-label is slightly clipped
    plt.savefig("messdaten_" + now.strftime("%d.%m.%Y") + ".png")
    plt.close()
    """

port ='/dev/ttyACM0'
speed=9600
fd_log = open("logfile.log", "w")

# adapt name (baud rate has to be the same than in the arduino sketch)
s = serial.Serial(port, speed)
fd_log.write("Open port for serial interface {} with a speed of {} Bit/s\n".format(port,speed) )
#s.open() not needed anymore

# Arduino resets after a serial connection
time.sleep(5)

i=1
try:
    while True:
        if (i % 5) == 0:
            s.close()
            s = serial.Serial(port, speed)
            create_plot(dht11_temp,temp_r,date_stamp)
        time.sleep(5)
        
        response = s.readline()
        if len(response) >= 27: #28
            now = datetime.today()
            try:
                pick_data(response,now)
                date_stamp.append(now)
            except Exception as e:
                fd_log.write("{} ERROR : {}\n".format(now.strftime("%Y.%m.%d %H:%M"),e) )
                fd_log.write("{} \n\n".format(response))
                pass
            
            i+=1
except KeyboardInterrupt:
    fd_log.write("{} ERROR : KeyboardInterrupt\n".format(now.strftime("%Y.%m.%d %H:%M")) )
    s.close()
    fd_log.close()
except Exception as e:
    fd_log.write("{} ERROR : {}\n".format(now.strftime("%Y.%m.%d %H:%M"),e) )
    fd_log.close()
    s.close()

fd_log.close()
