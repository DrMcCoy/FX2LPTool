FX2LPTool README
================

Tool to manipulate Cypress EZ-USB FX2LP devices.
Namely, it lets you easily change the USB vendor/product IDs stored in the devices' EEPROM.

For a list of vendor/product IDs for FX2-based logic analyzer, please see
[the fx2lafw page in the sigrok wiki](http://sigrok.org/wiki/Fx2lafw#Hardware_overview).

    Usage: fx2lptool <command> <vendor ID> <product ID> [<command options>]
    The vendor ID and product ID can be specified in decimal or, when
    prefixed with 0x, in hexadecimal, or, when prefixed with a 0, in octal.
    
    Valid commands are:
      - readeeprom
        Read the contents of the device's EEPROM
      - verifyid
        Verify the EEPROM contents with the vendor/product IDs
      - setid <new vendor ID> <new product ID>
        Set the vendor and product IDs.
        For known IDs, please see the README.md
    
    Examples:
    fx2lptool readeeprom 0x0925 0x3881
    fx2lptool verifyid 0x0925 0x3881
    fx2lptool setid 0x0925 0x3881 0x08A9 0x0014
