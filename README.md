# Proiect PM 2025 

### Andrei-Daniel Lungu

### Sistem automat de udare a plantelor

##### Prerequisites:

Download esp-idf framework
  
```
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
```
Install esp32c6
```
./install.sh esp32c6
```
Enable ESP-IDF medium
```
source export.sh
```
Clone the project inside esp-idf directory
```
git clone https://github.com/D9nni/PM-Plant-Watering-System
```
##### Build: 

Inside downloaded directory, run
```
idf.py build
```

#### How it works

First, modify WIFI_SSID and WIFI_PASS from wifi.h to correspond to your wifi network. 

After you flash the code on esp32-c6 the microcontroller will connect to wifi and get an IP address, which can be read from serial or detected by your router.

Access the address from browser and you will get a webpage containg many buttons where you can ask values of humidity, temperature and command water pump.

Normally, the microcontroller checks the humidity level once per 10 seconds and if it is under 45 the watering system will be started for 10 seconds.

Every activity is logged and you can get logs from webpage.

