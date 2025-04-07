import time
import csv
import argparse
from datetime import datetime

def read_sensor(path):
    with open(path, 'r') as f:
        return int(f.read().strip())

def main(duration):
    end_time = time.time() + duration
    with open('sensor_log.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Timestamp', 'Temp (°C)', 'Pressure (hPa)'])
        while time.time() < end_time:
            temp = read_sensor('/sys/kernel/virtual_sensor/temp')
            pressure = read_sensor('/sys/kernel/virtual_sensor/pressure')
            now = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            writer.writerow([now, temp, pressure])
            print(f"{now} - Temp: {temp}°C | Pressure: {pressure} hPa")
            time.sleep(5)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--duration', type=int, default=30, help='Duration in seconds to log data')
    args = parser.parse_args()
    main(args.duration)

