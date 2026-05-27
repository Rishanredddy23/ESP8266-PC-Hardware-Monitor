import psutil
import serial
import time
import wmi

# CHANGE THIS TO YOUR NODEMCU COM PORT
ser = serial.Serial('COM4', 115200)

# OpenHardwareMonitor
w = wmi.WMI(namespace="root\\OpenHardwareMonitor")

while True:

    # CPU + RAM
    cpu = int(psutil.cpu_percent())
    ram = int(psutil.virtual_memory().percent)

    # DEFAULT VALUES
    cpu_temp = 0
    gpu = 0
    gpu_temp = 0

    # READ SENSORS
    sensors = w.Sensor()

    for sensor in sensors:

        # CPU TEMP
        if sensor.SensorType == u'Temperature':

            if 'CPU Package' in sensor.Name:
                cpu_temp = int(sensor.Value)

        # GPU LOAD
        if sensor.SensorType == u'Load':

            if sensor.Name == 'GPU Core':
                gpu = int(sensor.Value)

        # GPU TEMP
        if sensor.SensorType == u'Temperature':

            if sensor.Name == 'GPU Core':
                gpu_temp = int(sensor.Value)

    # SEND DATA
    data = f"{cpu},{cpu_temp},{ram},{gpu},{gpu_temp}\n"

    ser.write(data.encode())

    print(data)

    time.sleep(1)