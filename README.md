# nRF52 Flashy 

## Overview
nRF52 Flashy is a Mynewt PWM example app for nRF52 based microcontrollers. 
This project relies on the mynewt\_nordic repository for the nRF52 PWM 
driver implementation.

## Building

1. Download and install Apache Newt.

You will need to download the Apache Newt tool, as documented in the [Getting Started Guide](http://mynewt.apache.org/os/get_started/introduction/).

2. Download the Apache Mynewt Core and Mynewt Nordic packages.

```no-highlight
    $ newt install
```
3. Build the flashy app for one of the existing targets (ada\_feather\_flashy
or nrf52\_flashy) or create a new target for your desired nRF52 based board.

```no-highlight
    $ newt build my_blinky_sim
```

## Supported Boards

There are currently targets for Adafruit Feather Pro and nRF52dk, but 
Any nRF52 based MCU should work with this app. All you'd need to do is 
copy one of existing targets and change the BSP.
