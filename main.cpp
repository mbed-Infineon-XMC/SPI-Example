/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************* Includes */
#include "mbed.h"

/******************************************************************** Defines */
#define CMD_READ                            0x03
#define CMD_PROGRAM                         0x02
#define CMD_WRITE_EN                        0x06
#define CMD_ERASE                           0x20
#define CMD_STATUS                          0x05
#define CMD_DUMMY                           0xFF

#define FLASH_ADDR_BYTE_0                   0x00
#define FLASH_ADDR_BYTE_1                   0x00
#define FLASH_ADDR_BYTE_2                   0x00

#define SPI_REC_BUFF_SIZE                   100
#define WRITE_BYTE                          0xAA

#define STATUS_WIP_MASK                     0x01 // WIP: Write in progress bit

/******************************************************************** Globals */
SPI spi(P1_5, P1_4, P1_10);    // mosi, miso, sclk
DigitalOut cs(P1_8);
DigitalOut led1(LED1);
DigitalOut led2(LED2);

const char data_program[5] = {CMD_PROGRAM, FLASH_ADDR_BYTE_0, FLASH_ADDR_BYTE_1, FLASH_ADDR_BYTE_2, WRITE_BYTE};
const char data_read[5] = {CMD_READ, FLASH_ADDR_BYTE_0, FLASH_ADDR_BYTE_1, FLASH_ADDR_BYTE_2, CMD_DUMMY};
const char data_erase[4] = {CMD_ERASE, FLASH_ADDR_BYTE_0, FLASH_ADDR_BYTE_1, FLASH_ADDR_BYTE_1};
const char data_status[2] = {CMD_STATUS, CMD_DUMMY};

char spi_receive_buffer[SPI_REC_BUFF_SIZE] = { 0 };

/****************************************************************** Functions */

/**
 * Wait until WIP bit is 0
 */
static void waitForWip(void){

    // Check if write is in progress
    do {
        cs = 0;
        spi.write(data_status, sizeof(data_status), spi_receive_buffer, 2);
        cs = 1;
        wait_us(500);
    }while(spi_receive_buffer[1] & STATUS_WIP_MASK);
}

/**
 * Main Function
 */
int main() {

    // Set SPI format and frequency
    spi.format(8, 0);               // 8 byte, Mode=0
    spi.frequency(1000000);         // f = 1Mhz
    cs = 1;                         // Set chip select to 0
    wait(0.1);

    // Switch off LED1 & LED2
    led1 = 0;
    led2 = 0;

    // Enable write
    cs = 0;
    spi.write(CMD_WRITE_EN);
    cs = 1;

    // Erase sector 0
    cs = 0;
    spi.write(data_erase, sizeof(data_erase), spi_receive_buffer, 0);
    cs = 1;

    // Check if write is in progress
    waitForWip();

    // Enable write
    cs = 0;
    spi.write(0x06);
    cs = 1;

    // Write byte to address 0x00000
    cs = 0;
    spi.write(data_program, sizeof(data_program), spi_receive_buffer, 0);
    cs = 1;

    // Check if write is in progress
    waitForWip();

    // Read byte from address 0x00000
    cs = 0;
    spi.write(data_read, sizeof(data_read), spi_receive_buffer, 5);
    cs = 1;

    // Check if write byte is equal to read byte
    if(spi_receive_buffer[4] == WRITE_BYTE){
        // Switch on LED1
        led1 = 1;
        led2 = 0;
    }else{
        // Switch on LED2
        led1 = 0;
        led2 = 1;
    }

    while(1){
        wait(1);
    }
}

/*EOF*/
