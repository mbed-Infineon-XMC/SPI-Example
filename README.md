# SPI Example

The following guide describes how to communicate with the on board SPI-Flash memory.

In this example a byte (0xAA) is programes to flash address 0x00. Afterwards a byte is read from address 0x00.
If the write byte is equal to the read byte LED1 is turnd on, if not LED2 is turned on.

>> Check the Datasheet from the FLASH memory. [LINK](http://www.mouser.com/ds/2/100/002-00650_S25FL032P_32-Mbit_3.0_V_Flash_Memory_Dat-933047.pdf)

## Step 1: Download mbed CLI

* [Mbed CLI](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/dev_tools/cli/#installing-mbed-cli) - Download and install mbed CLI.

## Step 2: Import startup project

Import SPI-Example project from GitHub.

```
mbed import https://github.com/mbed-Infineon-XMC/SPI-Example.git
```

## Step 3: Install ARM GCC toolchain

* [GNU ARM toolchain](https://launchpad.net/gcc-arm-embedded) - Download and install the last stable version of the ARM GCC toolchain.
* Open the file "mbed_settings.py" and add the ARM GCC install path.

Example:
```
#GCC_ARM_PATH = "home/bin/arm_gcc_toolchain/gcc-arm-none-eabi-5_4-2016q2/arm-none-eabi/bin"
```
## Step 4: Compile project

Navigate into the project folder and execute the following command:
```
cd SPI-Example.git/
mbed compile -m XMC_4500_RELAX_KIT -t GCC_ARM
```
mbed creates a BUID directory where you can find the executables (bin, elf, hex ...).

## Step 5: Flash to board

* [Segger JLink](https://www.segger.com/downloads/jlink) - Install the JLink software for your platform.
* Navigate to the BUILD directory and execute the following JLinkExe commands.
```
$ JLinkExe
J-LINK> device xmc4500-1024
J-LINK> h
J-Link> loadfile SPI-Example.git.hex
J-Link> r
J-Link> g
```
* Choose SWD, 4000kHz as interface settings!!
