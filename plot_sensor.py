import matplotlib.pyplot as plt
import csv
from datetime import datetime

timestamps = []
temperatures = []
pressures = []

with open('sensor_log.csv', 'r') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        timestamps.append(datetime.strptime(row['Timestamp'], '%Y-%m-%d %H:%M:%S'))
        temperatures.append(int(row['Temp (°C)']))
        pressures.append(int(row['Pressure (hPa)']))

plt.figure(figsize=(10, 5))

plt.subplot(2, 1, 1)
plt.plot(timestamps, temperatures, label='Temperature (°C)', color='red')
plt.ylabel('Temperature (°C)')
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(timestamps, pressures, label='Pressure (hPa)', color='blue')
plt.ylabel('Pressure (hPa)')
plt.xlabel('Timestamp')
plt.grid(True)

plt.tight_layout()
plt.show()

