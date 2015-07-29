# The People's Pixel

This project combines a Raspberry Pi and Arduino Uno, along with necessary peripherals, to form a compact
system capable of performing user-initiated image capture and presentation, such as would be typical in a "photo-booth" machine.

# Dependencies
libgphoto2

Linux frame buffer application(FBI)


# Set up

After installing Raspbian Wheezy and getting your user setup per the instructions above...

1: Run the command:
``` $ df -h ```
to make sure your file system is roughly size the of your sdcard (less the size of the OS. You can confirm the size of the card with $ sudo fdisk -l). If for some reason the file system is really small compared what you were expecting, run

``` $ sudo raspi-config ```
and select the option for increasing the size of the filesystem. Exit the config app.

2: Run the command:

``` $ sudo apt-get update ```

3: Run the command:

``` $ sudo raspi-config ```
and select advanced options. Then select the option for enabling i2c hardware at startup. Exit the config app.

4: Run the command:

``` $ sudo nano /etc/modprobe.d/raspi-blacklist.conf ```
'i2c-bcm2708' shouldn't be blacklisted so make sure that line is commented out. i.e.
``` #blacklist i2c-bcm2708 ```
Save the file if changed and exit nano. (If the file is empty then just move on)


5: Run the command:

``` $ sudo nano /etc/modules ``` Append the lines...
```
i2c-bcm2708 
i2c-dev 
```
if they're not already there. Save the file if changed and exit nano.


6: Reboot the raspberry-pi

7: Install git (It might already be installed - confirm with $ git --version):

``` $ sudo apt-get install git ```

8: Get libgphoto2 and development files

``` $ sudo apt-get install libgphoto2-2 libgphoto2-2-dev```

9: Get the Linux frame buffer application

```$ sudo apt-get install fbi```

10: Clone the peoples-pixel repo:

```$ cd ~ ```
```$ git clone https://github.com/agnash/peoples-pixel.git```

11: Run...
```
$ cd peoples-pixel/raspberry-pi
$ sudo ./setup.bash
$ pp 
```
(the actual program...will fail unless camera and Arduino is properly configured, powered on and connected)
