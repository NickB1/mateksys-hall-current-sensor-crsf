# Mateksys-hall-current-sensor-crsf
Alternative firmware for Mateksys hall current sensor (https://www.mateksys.com/?portfolio=hcs-150a) to output CRSF telemetry.  
![2024-12-04 20_18_57-Window](https://github.com/user-attachments/assets/4b29c2b6-9260-473b-897e-aff8a6bdbf73)  
The sensor contains a Gigadevice GD32F150G8 microcontroller.  
The project can be built in the Arduino IDE using the following prerequisites.
* ArduinoCore-GD32
    * https://github.com/CommunityGD32Cores/ArduinoCore-GD32
* AlfredoCRSF library
    * https://github.com/AlfredoSystems/AlfredoCRSF
 
# Programming

*   Download and install the GD32 All-In-One Programmer
    *   https://www.gd32mcu.com/en/download/7?kw=GD32F1
*   Connect a usb to serial cable to the sensor (I used this one https://www.tinytronics.nl/en/communication-and-signals/serial/usb/ft232-3.3-5v-ttl-usb-serial-port-adapter-with-cable)
    *   Black cable to G
    *   Red cable to 5V
    *   White cable to TX
    *   Green cable to RX
*   To get the board in bootloader mode the BOOT1 pin need to be pulled high on startup
    *   You can do this by connecting the pin marked "Bt" to the pin named "3" (markings are on the bottom side of the board)
    *   I bridged these pins using a pushbutton for easy programming
*   Open the GD32AllInOneProgrammer tool and configure the following
    *   Port Name: serial port name of the usb to serial cable
    *   Part Number: GD32F150G8U6TR
*   Press Connect
*   After connecting a "Remove Protection" button will become visible
    *   ![2024-12-04 20_21_15-Window](https://github.com/user-attachments/assets/c29483dc-f2f4-4080-9533-abee79247c45)
*   Press this button, after successful removal of the protection powercycle the board and reconnect the GD32AllInOneProgrammer tool
*   In the Download section, browse to the bin file
*   Click download, the progress bar should start
*   After successful programming, remove the bridge between the "Bt" and "3" pin and repower the board
*   The blue LED should now start blinking
*   You can now connect the sensor to the CRSF port of a receiver and see telemetry come in for battery voltage, current and capacity
*   Programming through the Arduino IDE is also possible when the microcontroller is put into bootloader mode

![mateksys-hall--current-sensor-crsf-1](https://github.com/user-attachments/assets/a56ba00c-96ff-404f-92e8-6b8f984a367a)
![mateksys-hall--current-sensor-crsf-2](https://github.com/user-attachments/assets/02d4a67e-9ab3-49eb-aedb-f4d15016d355)
