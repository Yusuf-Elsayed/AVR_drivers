# AVR Calculator

## Description

The AVR Calculator is a simple calculator implemented on an AVR microcontroller, enabling users to perform basic arithmetic operations (addition, subtraction, multiplication, and division) with two numbers entered via a keypad. The result is displayed on an LCD screen.

## Features

- Supports addition, subtraction, multiplication, and division operations.
- Handles invalid operator inputs gracefully, displaying an error message.
- Prevents division by zero and displays an error message in such cases.
- Supports clearing the display and resetting the calculator by pressing the '*' key.
- Provides feedback on the LCD display for user interactions.

## Hardware Requirements

- AVR Microcontroller
- Keypad
- LCD Display
- Appropriate connections and power supply

## Usage

1. Connect the AVR microcontroller, keypad, and LCD display according to the hardware setup.
2. Compile and flash the AVR Calculator code onto the microcontroller.
3. Use the keypad to enter two numbers and an operator.
4. Press '#' to calculate the result.
5. Press '*' to clear the display and reset the calculator.
6. Handle errors gracefully, such as invalid input or division by zero.

## Error Handling

The AVR Calculator effectively handles various error scenarios:

1. **Invalid Operator Input**: When an operator key pressed is not 'A', 'B', 'C', or 'D', the code displays "Invalid Entry!" on the LCD and continues to wait for a valid operator.

2. **Invalid Equal Sign Input**: When the equal sign key pressed is not '#', the code displays "Invalid Entry!" on the LCD and continues to wait for a valid equal sign.

3. **Division by Zero**: If the operator is division ('A') and the second key is '0', the code displays "Invalid Div by 0!" on the LCD and continues to wait for valid input.

4. **Reset**: Pressing the '*' key clears the display and resets the input values, allowing for a new calculation.

## Author

This Calculator application, including drivers for the LCD and Keypad, was developed by [Yusuf-Elsayed](https://github.com/Yusuf-Elsayed/).