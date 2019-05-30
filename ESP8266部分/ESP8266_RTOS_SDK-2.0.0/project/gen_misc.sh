#!/bin/bash

:<<!
******NOTICE******
MUST set SDK_PATH & BIN_PATH firstly!!!
example:
export SDK_PATH=~/share/ESP8266_RTOS_SDK-2.0.0
export BIN_PATH=~/share/ESP8266_RTOS_SDK-2.0.0/bin
!

export SDK_PATH=~/Share/ESP8266_RTOS_SDK-2.0.0
export BIN_PATH=~/Share/ESP8266_RTOS_SDK-2.0.0/bin

echo "gen_misc.sh version 20150911"
echo ""

if [ $SDK_PATH ]; then
    echo "SDK_PATH:"
    echo "$SDK_PATH"
    echo ""
else
    echo "ERROR: Please export SDK_PATH in gen_misc.sh firstly, exit!!!"
    exit
fi

if [ $BIN_PATH ]; then
    echo "BIN_PATH:"
    echo "$BIN_PATH"
    echo ""
else
    echo "ERROR: Please export BIN_PATH in gen_misc.sh firstly, exit!!!"
    exit
fi

#echo "Please check SDK_PATH & BIN_PATH, enter (Y/y) to continue:"
#read input

#if [[ $input != Y ]] && [[ $input != y ]]; then
#    exit
#fi

#echo ""

echo "Please follow below steps(1-5) to generate specific bin(s):"
echo "STEP 1: use boot_v1.2+ by default"
boot=new


app=1

spi_speed=40

spi_mode=QIO

spi_size_map=3

make clean

make BOOT=$boot APP=$app SPI_SPEED=$spi_speed SPI_MODE=$spi_mode SPI_SIZE_MAP=$spi_size_map
