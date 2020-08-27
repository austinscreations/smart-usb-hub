# smart-usb-hub
a custom usb hub for tinkers that can interface with smart home systems and provide data on power usage of a device.

2020-08-27
version 2 is created, has 4 usb ports, mosfet is rated for 3 amps, external power supply notifies the MCU which can allow increased current alotment in programming. eg: max 500ma under usb input vs max 5A (shared by all ports) under power supply usage (current limited by dc-dc converter)

INA219 shunt is 0.1ohm 2W 1% toleance which allows for sense current up to 3.2Amps.

version 2 now includes 4 ports using usb2514 for hub control.

board allows for buttons to be placed and allows for software control of outputs -- newpixels give the ability to iniicate status of ports. 4 pin header spot has been added for the use of an I2C LCD.

current design allows for various arengments of a custom 3D printed case that allows the hub to me mounted in various ways

current board size is 100*75mm

