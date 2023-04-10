#ifndef LCD_H
#define LCD_H

#include <pin.h>

union data_pins
{
    struct s
    {
        digital_pin d4;
        digital_pin d5;
        digital_pin d6;
        digital_pin d7;
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

void init_lcd(lcd *lcd);

#endif