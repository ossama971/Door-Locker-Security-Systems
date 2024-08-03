# Door Locker Security System

## Project Description

This projectwas developed as part of an embedded systems diploma to enhance security using a layered architecture model. The system uses two ATmega32 microcontrollers to provide robust and flexible door security. 

## Key Features

### 1. Human Machine Interface (HMI_ECU)
- **User Interaction**: This component handles all user interactions through a keypad and LCD.
- **Password Creation**: Allows users to set a 5-digit password with confirmation.
- **Main Menu**: Displays main menu options for door control and password management.

### 2. Control ECU
- **System Brain**: This module processes inputs and makes decisions to control the system.
- **Password Validation**: Compares entered passwords with the stored password in the EEPROM.
- **Error Handling**: Provides multiple attempts for password entry, activating a buzzer on incorrect entries.

### 3. Security Features
- **Password Storage**: Securely stores the password in the EEPROM with options for updates.
- **Open Door**: Activates the DC motor to unlock the door when the correct password is entered.
- **Change Password**: Allows users to change the existing password after validating the current one.

## Drivers Used  
- **GPIO**: General Purpose Input/Output for controlling various peripherals.
- **Keypad**: For user input of passwords.
- **LCD**: For displaying instructions, menu options, and status messages.
- **Timer**: For timing operations and delays.
- **UART**: For serial communication between microcontrollers.
- **I2C**: For communication with EEPROM.
- **EEPROM**: For storing and retrieving the password securely.
- **Buzzer**: For providing auditory feedback on incorrect password entries.
- **DC-Motor**: For controlling the door lock mechanism.

## Microcontroller
- **ATmega32**: The system utilizes two ATmega32 microcontrollers, one for the HMI_ECU and the other for the Control_ECU.

## System Sequence

1. **Create a System Password**
   - The system starts by prompting the user to set a 5-digit password and requests confirmation.

2. **Main Options**
   - Displays the main menu options on the LCD, allowing users to open the door or change the password.

3. **Open Door**
   - Users enter the password to unlock the door. The system validates the password and activates the DC motor to unlock the door if the password is correct.

4. **Change Password**
   - Users can change the existing password by entering the current password and setting a new one.

5. **Password Validation**
   - Ensures that the entered password matches the stored one. If not, users are given multiple chances to enter the correct password, with a buzzer indicating incorrect entries.

## Simulation Screenshots
*Include screenshots of the simulation here.*

## How to Use

1. **Initial Setup**
   - Power on the system and follow the prompts to set up the initial password.

2. **Operating the Door Lock**
   - Use the main menu to select the "Open Door" option and enter the password to unlock the door.
   - To change the password, select the "Change Password" option, enter the current password, and then set a new password.

3. **Error Handling**
   - If an incorrect password is entered, the buzzer will sound. You have multiple attempts to enter the correct password before the system locks out temporarily.
