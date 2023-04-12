#ifndef LCD_H
#define LCD_H

#include <pin.h>

union data_pins
{
    struct s
    {
        digital_pin db4;
        digital_pin db5;
        digital_pin db6;
        digital_pin db7;
    } s;
    digital_pin all[4];
};
typedef union data_pins data_pins;

struct lcd
{
    digital_pin rs;
    digital_pin rw;
    digital_pin e;
    data_pins data_pins;
};
typedef struct lcd lcd;

void lcd_init(lcd *lcd);
void lcd_write_char(lcd *lcd, char c);
void lcd_write(lcd *lcd, const uint8_t * data, size_t size);
void lcd_move_cursor(lcd *lcd, int x, int y);
void lcd_clear(lcd *lcd);

#endif