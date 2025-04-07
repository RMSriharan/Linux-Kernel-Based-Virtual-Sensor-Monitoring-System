# Linux Kernel-Based Virtual Sensor Monitoring System

Simulates virtual temperature and pressure sensors using a custom Linux kernel module and exposes them via the `/sys` filesystem. A Python script logs and plots the data in real-time.

## 🔧 Components

- Kernel module (`sensor_monitor.c`)
- SysFS interface (`/sys/kernel/virtual_sensor/`)
- Python logger (`read_sensor.py`)
- Python plotter (`plot_sensor.py`)

## 🚀 How to Run

```bash
make
sudo insmod sensor_monitor.ko
ls /sys/kernel/virtual_sensor/
python3 read_sensor.py --duration 60
python3 plot_sensor.py
