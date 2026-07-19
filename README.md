# Car Black Box Event Data Recorder using PIC18F4580

A real-time **Car Black Box / Event Data Recorder** implemented using the **PIC18F4580 microcontroller**. The system monitors vehicle parameters such as **speed, gear status, and collision events**, timestamps them using an RTC, and stores the events in external EEPROM for later analysis.

---

## Features

* Real-time clock using **DS1307 RTC**
* Speed monitoring using **ADC and potentiometer**
* Gear control using **Matrix Keypad**
* Collision event detection
* Event logging to **External EEPROM**
* **View Log** on 16×2 CLCD
* **Download Log** through UART to **Tera Term**
* **Set Time** functionality with blinking field editing
* **Clear Log** functionality

---

## System Overview

The dashboard continuously displays:

* **Speed**
* **Current Gear**
* **Current Time (12-hour format with AM/PM)**

Whenever:

* A **gear change** occurs, or
* A **collision** is detected,

the system stores an event record in EEPROM.

### Event Record Format (16 Bytes)

| Field            |    Size |
| ---------------- | ------: |
| Time (HH:MM:SS)  | 8 bytes |
| Event Type (G/C) |  1 byte |
| Gear             |  1 byte |
| Speed            | 3 bytes |
| Reserved         | 3 bytes |

A maximum of **10 events** are stored in EEPROM.

---

## Menu Options

Press **MK_SW11** to enter the menu.

### Available Options

1. **View Log** – Browse stored events on CLCD
2. **Download Log** – Send logs through UART to Tera Term
3. **Set Time** – Edit RTC time
4. **Clear Log** – Erase all stored events

Use:

* **MK_SW1** → Scroll Down / Increment
* **MK_SW2** → Scroll Up / Decrement
* **MK_SW11** → Enter / Select
* **MK_SW12** → Exit / Back

---

## Hardware Used

* PIC18F4580 Microcontroller
* DS1307 RTC Module
* 24Cxx External EEPROM
* 16×2 Character LCD
* Matrix Keypad
* Potentiometer
* UART Interface
* I2C Bus

---

## Software & Tools

* **Embedded C**
* **MPLAB X IDE**
* **XC8 Compiler**
* **Tera Term**
* **GitHub**

---

## Communication Protocols

### I2C

Used for:

* DS1307 RTC communication
* External EEPROM read/write operations

### UART

Used for:

* Downloading logs to a PC through Tera Term

---

## Key Functionalities Implemented

### RTC Time Management

* 12-hour mode configuration
* AM/PM handling
* BCD conversion for DS1307 registers
* Runtime time updates

### EEPROM Management

* Fixed-size record storage
* Sequential event logging
* Event indexing
* Log count management

### User Interface

* Menu-driven navigation
* Field-wise blinking while editing time
* Real-time dashboard updates
* Scrollable log viewing

---

## Example UART Log Output

```text
==============================
 CAR BLACK BOX EVENT LOG
==============================

Log 1
Time  : 08:15:23 PM
Event : GEAR CHANGE
Gear  : 3
Speed : 045 km/h

------------------------------

Log 2
Time  : 08:17:41 PM
Event : COLLISION
Gear  : 4
Speed : 062 km/h

==============================
 END OF LOG
==============================
```

---

## Learning Outcomes

Through this project, I gained hands-on experience in:

* **Embedded C programming**
* **PIC18F4580 peripheral interfacing**
* **I2C protocol implementation**
* **UART serial communication**
* **RTC configuration and BCD handling**
* **External EEPROM memory management**
* **Menu-driven embedded UI design**
* **Debugging real-time embedded applications**

---

## Project Structure

```text
main.c
menu.c
view_log.c
download_log.c
clear_log.c
set_log.c
store_eeprom.c
adc.c
clcd.c
matrix_keypad.c
i2c.c
ds1307.c
external_eeprom.c
uart.c
```

---

## Author

**Pratham Gorey**
