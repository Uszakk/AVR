// Basic functions for operating a 1602 LCD
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

/**
 * @brief Initializes the LCD display.
 * Configures control and data pins, sets the display to 8-bit mode, 
 * clears the display, and enables cursor shifting.
 */
void lcd_init(void) {
        // Configure control pins as output
        LCD_CONTROL_DDR |= (_BV(LCD_RS) | _BV(LCD_RW) | _BV(LCD_EN));
        // Set control pins low
        LCD_CONTROL_PORT &= ~(_BV(LCD_RS) | _BV(LCD_RW) | _BV(LCD_EN));
        // Configure data pins as output
        LCD_DATA_DDR = 0xFF;
        // Set data pins low
        LCD_DATA_PORT = 0;

        // Wait for power-up stabilization
        _delay_ms(20);

        // Set LCD to 8-bit mode (repeated to ensure proper initialization)
        lcd_output_cmd(LCD_8BIT_MODE);
        _delay_ms(5);
        lcd_output_cmd(LCD_8BIT_MODE);
        _delay_ms(5);
        lcd_output_cmd(LCD_8BIT_MODE);
        _delay_ms(5);

        // Set LCD to 8-bit mode, 2-line display, 5x8 font
        lcd_output_cmd(LCD_8BIT_MODE | LCD_2LINE_MODE | LCD_5X8FONT_MODE);
        lcd_check_busy();

        // Turn off the display
        lcd_output_cmd(LCD_OFF);
        lcd_check_busy();

        // Clear the display
        lcd_output_cmd(LCD_CLEAR);
        lcd_check_busy();

        // Set entry mode to increment address and shift cursor
        lcd_output_cmd(LCD_INCREMENT_ADDR | LCD_CURSOR_SHIFT);
        lcd_check_busy();

        // Turn on the display
        lcd_output_cmd(LCD_ON);
        lcd_check_busy();
}

/**
 * @brief Sends a command to the LCD.
 * @param cmd The command byte to send.
 * Sets the data pins to the specified command and triggers an enable pulse.
 */
void lcd_output_cmd(uint8_t cmd) {
        // Set the data port to the command
        LCD_DATA_PORT = cmd;
        // Trigger an enable pulse to latch the command
        lcd_pulse_enable();
}

/**
 * @brief Sends data to the LCD.
 * @param data The data byte to send.
 * Sends a byte of data (character) to the LCD by setting the RS pin and triggering an enable pulse.
 */
void lcd_output_data(uint8_t data) {
        // Set RS to indicate data mode (writing to CGRAM)
        LCD_CONTROL_PORT |= _BV(LCD_RS);
        // Set the data port to the data byte
        LCD_DATA_PORT = data;
        // Trigger an enable pulse to latch the data
        lcd_pulse_enable();
        // Reset RS to command mode
        LCD_CONTROL_PORT &= ~_BV(LCD_RS);
}

/**
 * @brief Waits for the LCD to be ready by checking the busy flag.
 * Configures the data pins for reading, checks the busy flag (D7), and waits until the flag is cleared.
 */
void lcd_check_busy(void) {
        // Set RW to read mode
        LCD_CONTROL_PORT |= _BV(LCD_RW);
        // Configure data pins as input
        LCD_DATA_DDR = 0;
        // Enable pull-up resistors on data pins
        LCD_DATA_PORT = 0xFF;

        // Wait until the busy flag (D7) is cleared
        do{
                lcd_pulse_enable();
        }while (LCD_DATA_PIN & _BV(LCD_D7));
	// DEBUG
	// PORTA = 0x01;
	// ENDDEBUG
        // Disable pull-up resistors
        LCD_DATA_PORT = 0;
        // Reconfigure data pins as output
        LCD_DATA_DDR = 0xFF;
        // Set RW back to write mode
        LCD_CONTROL_PORT &= ~_BV(LCD_RW);
}

/**
 * @brief Generates a short enable pulse for the LCD.
 * The enable pin is driven high and then low to latch data or commands into the LCD.
 */
void lcd_pulse_enable(void) {
        // Set enable pin high
        LCD_CONTROL_PORT |= _BV(LCD_EN);
        // Short delay
        _delay_us(1);
        // Set enable pin low
        LCD_CONTROL_PORT &= ~_BV(LCD_EN);
        // Short delay
        _delay_us(1);
}

/**
 * @brief Outputs a string to the LCD display.
 * Sends each character of the string to the LCD until the null terminator is encountered.
 * @param str Pointer to the null-terminated string to be displayed.
 */
void lcd_output_string(char* str) {
        // Loop through each character until the null terminator is reached
        while (*str != '\0') {
                // Output the current character to the LCD
                lcd_output_data(*str);
                // Move to the next character in the string
                str++;
        }
}

/**
 * @brief Sets the DDRAM address to position the cursor.
 * Calculates the DDRAM address based on the row and column, and sends the address command to the LCD.
 * @param row The row number (starting from 0).
 * @param col The column number (starting from 0).
 */
void lcd_output_position(uint8_t row, uint8_t col) {
        // Calculate the DDRAM address based on the row offset and column
        uint8_t addr = LCD_ROW_OFFSET * row + col;
        // Send the command to set the DDRAM address
        lcd_output_cmd(LCD_SET_ADDR | addr);
}

