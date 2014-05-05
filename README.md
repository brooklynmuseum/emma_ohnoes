emma-ohnoes
===========
Emma O, judge of hell judges your cloud infrastructure.

Requirements
------------
A http://www.temboo.com account and a TembooAccount.h file to store your Temboo creds
Access to a 3D printer with:
* Transparent blue-ish PLA plastic
* Opaque black PLA plastic
An Arduino Yún
Two 10mmLEDs of the low-voltage variety. Blue and red were used for this project
An ethernet connection to a DHCP-enabled network and ethernet cable
A USB wall adapter and micro-usb cable

Setup
-----
In the emma_ohnoes.ino file, change the targetUrl variable to the site you want to check the availability for, or a custom AWS health check page to check on specific infrastructure metrics (See: http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/health-checks-creating-deleting.html#health-checks-creating). If the URL returns any other HTTP status code except 200 OK, Emma O will start pulsing a furious red, otherwise he'll glow a serene blue.

Usage
-----
Plug it in, give it a few minutes until Emma turns blue, then wait for US-EAST-1 to start failwhaling to see Emma turn red.

License
-------
This page is distributed under the MIT license. Please see the included copy of the license for deets.