# IoT_Lamp
Internet of Things Lamp created by the Three Sexy Guys (tm)

Based on the following original work: 
* Flask Raspberry Pi tutorial by Matt Richardson:
http://mattrichardson.com/Raspberry-Pi-Flask/

# Components
* RF24 Drivers: These are Arduino drivers (and all-important configuration details) for a specific radio frequency chipset. 
* Weblamp Python file: This is for the Flask Python webserver, which hosts the "control panel" for the lamp, also running functions to send and receive messages from devices, and update their status.
* HTML under Weblamp/templates: The HTML template that defines functionality and presentation of the control panel.

# Raspberry Pi Installation

First off, make sure your RPi is fully up to date

```
sudo apt-get update
sudo apt-get upgrade
```

Instead of sudo apt-get updrade, you can run the following command:

```
sudo apt-get dist-upgrade
```

This intelligently upgrades your distribution to include dependencies.
Instructions to install and build the RF24 Library are taken from [this repository](https://github.com/TMRh20/RF24)
At the command prompt of your RPi, run the following command:
```
wget http://tmrh20.github.io/RF24Installer/RPi/install.sh   
```
Make the file executable
```
chmod +x install.sh  
```
Run it and choose your options:
```
./install.sh  
```

Accept all the options for installing additional libraries and to compile.

After the library has finished compiling then run the code in this repository.
