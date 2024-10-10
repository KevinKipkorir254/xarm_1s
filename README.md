# PROCESS TO RUNNING THIS
1. connect to the Xarm, open device manager and 
update the drivers to make sure the data is being
posted as a HID.

## SETTING UP WSL TO ACCESS THE USB PORT.
1. Open an ubuntu terminal and a windows terminal.
2. On the windows terminal as amin run 'usbipd list' with this you will know the avaible connected devices.
```bash
usbipd list
```
3. Then run 'usbipd bind --force --busid 4-4', the 4-4 should be the appropriate bus ID.
```bash
usbipd bind --busid 4-4
```
4. Run 'usbipd attach --wsl --busid <busid>'.
```bash
usbipd attach --wsl --busid <busid>
```
5. On WSL command prompt run 'lsusb' this will ensure you have the USB can be accessed properly.
```bash
lsusb
```
6. In case we are to dettach for example to run some arduino code from windows run 'usbipd detach --busid <busid>'.
```bash
usbipd detach --busid <busid>
```
7. Run 'dmesg | grep tty' to see the available ports.
```bash
dmesg | grep dev
```
with this you should be able to share the HID, next is to change the rules to allow the hardware interface to access this HID

##CHANGING THE RULES

1. Identify the USB Device:
   First, we needed to identify the USB device. We used the `lsusb` command to list all USB devices:
   ```
   lsusb
   ```
   We looked for a line that corresponded to the XArm device, which would look something like:
   ```
   Bus 001 Device 123: ID 0483:5750 STMicroelectronics XArm Device
   ```
   Note the Vendor ID (0483) and Product ID (5750).

2. Create a udev Rule:
   We created a new udev rule file to give non-root users permission to access the device. We created a file named `99-xarm.rules` in the `/etc/udev/rules.d/` directory:
   ```
   sudo nano /etc/udev/rules.d/99-xarm.rules
   ```

3. Add the Rule:
   In this file, we added the following line:
   ```
   SUBSYSTEM=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5750", MODE="0666", GROUP="plugdev"
   ```
   This rule does the following:
   - It applies to USB devices (SUBSYSTEM=="usb")
   - It matches the Vendor ID and Product ID of our XArm device
   - It sets the device file permissions to 0666 (read and write for all users)
   - It assigns the device to the "plugdev" group

4. Save and Exit:
   We saved the file and exited the text editor.

5. Reload udev Rules:
   We reloaded the udev rules to apply our changes:
   ```
   sudo udevadm control --reload-rules && sudo udevadm trigger
   ```

6. Add User to plugdev Group:
   We added our user to the plugdev group:
   ```
   sudo usermod -a -G plugdev $USER
   ```

7. Log Out and Log Back In:
   For the group changes to take effect, we logged out and then logged back in.

8. Verify Permissions:
   After reconnecting the XArm device, we verified that the permissions were set correctly:
   ```
   ls -l /dev/bus/usb/001/123
   ```
   (Replace 001 and 123 with the correct bus and device numbers from step 1)
   The output should show that the device file is readable and writable by all users.

9. Test Access:
   We then compiled and ran our test.c program without using sudo:
   ```
   gcc -o test_xarm test_xarm.c -lhidapi-libusb
   ./test_xarm
   ```
   If successful, this demonstrated that we could now access the device without root privileges.

By following these steps, we ensured that both our test program and the ROS 2 hardware interface could read from and write to the XArm HID device without requiring root privileges, improving the security and usability of our setup.

## FINALLY RUN THE PROJECT
1. go to the root folder
2.run
```bash
source setup.bash
```
3.Run
```bash
ros2 launch xarm_1s_description xarm_1s_ros2_control.launch.py
```


