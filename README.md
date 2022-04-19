# IoT-Group11-Room-Reservation
A Prototype task for Internet-Of-Thing course

---
passwd for pi: fin2019

passwd for root: rass

```
WiFi101 firmware check.

WiFi101 shield: DETECTED
Firmware version installed: 19.5.2
Latest firmware version available : 19.6.1

Check result: NOT PASSED
 - The firmware version on the shield do not match the
   version required by the library, you may experience
   issues or failures.
```

From [Adafruit WINC1500 WiFi Shield for Arduino  Updating Firmware ], it states

```
If you're running 19.5.2 there is no need to update to 19.5.4, despite what the WiFi101 library says it should work just fine and you could brick your device by updating, it is not perfectly foolproof! Thanks :)
```

Ref: [here](https://forum.arduino.cc/t/quest-to-get-wpa2-enterprise-working-on-the-atwinc1500-with-arduino/556245)

[Customized WiFi101 library for the Adafruit Feather M0+ WINC1500](https://github.com/cicchiello/WiFi101_FM0_WINC1500_19.6.1)

upgrade the ATWINC1500 (B version) from firmware version 19.4.4 to 19.6.1, and customize the WiFi101 library to expose the newly supported WPA2 Enterprise EAP (several flavors) authentication functionality.

---
### ~~Set up as Access Point~~

```
         (dhcp)         bridge
           ╱    wifi    ┌───────┐
mobile-phone <~.~.~.~.> │(wlan0)│            
                        │    br0│RPi
      4G-Dongle <──────>|(eth1) │╲      
           ╲    wired   └───────┘╱    
         (dhcp)            192.168.66.1
```
Follow this [instruction](https://snikt.net/blog/2019/06/22/building-an-lte-access-point-with-a-raspberry-pi/)

## Pi hotspot name : piiot1
## Pi password: 12345678
