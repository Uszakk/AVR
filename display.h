//Definitions and declarations for display.c
#include <avr/io.h>

//Definitions of control pins (RS, RW, EN)
#define LCD_CONTROL_DDR DDRB
#define LCD_CONTROL_PORT PORTB
#define LCD_RS 5
#define LCD_RW 6
#define LCD_EN 7

//Definitions of data pins (D0-D7)
#define LCD_DATA_DDR DDRD
#define LCD_DATA_PORT PORTD
#define LCD_DATA_PIN PIND
#define LCD_D0 0
#define LCD_D1 1
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

//Output commands
#define LCD_8BIT_MODE 0x30
#define LCD_2LINE_MODE 0x28
#define LCD_5X8FONT_MODE 0x20
#define LCD_OFF 0x08
#define LCD_ON 0x0C
#define LCD_CLEAR 0x01
#define LCD_INCREMENT_ADDR 0x06
#define LCD_CURSOR_SHIFT 0x04
#define LCD_SET_ADDR 0x80
#define LCD_ROW_OFFSET 0x40
