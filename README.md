# WIP Sofle Choc RP2040 Mod

Firmware for the [Sofle Choc v2.1](https://github.com/josefadamcik/SofleKeyboard/tree/master/Sofle_Choc) by Brian Low
and hardware mods for RP2040 compatibility.

* Keyboard Maintainer: [Paul Rogalinski-Pinter](https://github.com/pulsar256/sofle_choc_rp2040)
* Hardware Supported:
    * [Sofle Choc v2.1](https://github.com/josefadamcik/SofleKeyboard/tree/master/Sofle_Choc)
    * [ProMicro RP2040](https://de.aliexpress.com/item/1005006599393967.html)
* [3d Printed Enclosure](https://www.printables.com/model/1168416-sofle-choc-case-travel-enclosure-and-tilt-stand)

![Sofle Choc](doc/sofle_choc.jpg)

## Build environment setup

Set up QMK [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) according to the official
documentation. Make sure to set the `user.qmk_home` configuration option and point it to your qmk_firmware directory,
for example:

```shell
qmk config user.qmk_home=$HOME/qmk_firmware
```

## Build

```shell
make make build
```

## Flash

```shell
make make flash
```

## Bootloader

Enter the bootloader using one of the methods:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the
  keyboard
* **Physical reset button**: On the microcontroller board, hold down the boot button and power on or reset the board.
* double tap the reset button once the initial version of this firmware has been flashed 

## Required Hardware Modifications

The ProMicro RP2040 is a 3.3V system while the AVR ProMicro which is used in the PCB Design is a 5V Board. In the PCB
design the RGB LED power is fed from the microcontroller board. In this modification we are going to reroute USB 5V to
the RGB LED VCC Rail and also to power the split MCU via TRRS, isolate the microcontroller breakout board's 3.3V rail
from the PCB and hook up the OLED directly to the back of the mcu breakout board.

![Isolate 3.3V rail from PCB](doc/isolate.png)
![Bridge USB 5V rail to PCB](doc/bridge.png)
![OLED Wiring](doc/oled.png)
![OLED Mounting](doc/oled_mount.png)

## Acknowledgements

- Embedded font "Minecraft Standard" by Marek Poláček licensed under CC PD
