# smart-usb-hub
a custom usb hub for tinkers that can interface with smart home systems and provide data on power usage of a device.

2020-08-26
version 1 is created, has 3 usb ports, mosfet is rated for 3 amps, external power supply notifies the MCU which can allow increased current alotment in programming. eg: max 500ma under usb input vs max 5A (shared by all ports) under power supply usage (current limited by dc-dc converter)

INA219 shunt is 0.1ohm 1% toleance which allows for sense current up to 3.2Amps.

**LTC4412 sense pin output needs to be confirmed for voltage tolerance on MCU pin A0**

board allows for buttons to be placed and allows for software control of outputs -- newpixels give the ability to iniicate status of ports. 4 pin header spot has been added for the use of an I2C LCD.

current design allows for various arengments of a custom 3D printed case that allows the hub to me mounted in various ways

current board size is 100*75mm

posibility of adding I2C port expander to increase amount of usb ports / possible mosfet controllable power cut off.

next designs will hopefully include "hub" functionality.
