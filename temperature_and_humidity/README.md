Temperature and Humidity Sensor
===============================

Requirements
------------

1. In this project I used a 3 pin temperature and humidity sensor.
2. Install the library in the lib folder into your arduino libraries folder


Example to install the library
------------------------------

Note: In the copy example, if you're arduino folder is in root access then
make sure to use sudo.

`cp -Rv lib/DHT11 /path/to/arduino/libraries`

Building and uploading
----------------------

For my projects I use ano.
`ano build && sudo ano upload`

Viewing the data
----------------

`sudo ano serial`

This will show the serial output every 2 seconds.

To exit out of the serial: CTRL + A, CTRL + Q
