#include <avr/io.h>
#include <lcd.h>
#include <stdio.h>

#define LOG() printf("%s\n", __func__)

void init_lcd_pins(lcd *lcd)
{
    LOG();
    digital_pin *pins[7] = {&lcd->rs, &lcd->rw, &lcd->e,
                            &lcd->data_pins.all[0], &lcd->data_pins.all[1],
                            &lcd->data_pins.all[2], &lcd->data_pins.all[3]};

    for (int i = 0; i < 7; ++i)
    {
        set_out(pins[i]);
        set_low(pins[i]);
    }
}

// sets pin addresses
void init_lcd_members(lcd *lcd)
{
    LOG();
    digital_pin rs = {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD1)};
    digital_pin rw = {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD2)};
    digital_pin e = {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD3)};
    data_pins dataPins = {
        .s = {
            {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD4)},
            {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD5)},
            {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD6)},
            {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD7)}}};

    lcd->rs = rs;
    lcd->rw = rw;
    lcd->e = e;
    lcd->data_pins = dataPins;
}

void set_4_lsb(lcd *lcd, uint8_t data)
{
    for (int i = 0; i < 4; ++i)
    {
        if (data & _BV(i))
            set_high(&lcd->data_pins.all[i]);
        else
            set_low(&lcd->data_pins.all[i]);
    }
}

void set_4_msb(lcd *lcd, uint8_t data)
{
    set_4_lsb(lcd, data >> 4);
}

void write_command(lcd * lcd, uint8_t command)
{
    //1. write 4 msb, 2. write 4 lsb
    LOG();
    // command
    set_low(&lcd->rs);
    // write
    set_low(&lcd->rw);
    // 
}

void setup_4bit_mode(lcd *lcd)
{
    LOG();
    // command
    set_low(&lcd->rs);
    // write
    set_low(&lcd->rw);
    // 0b0000
}

void init_lcd_device(lcd *lcd)
{
    LOG();
    setup_4bit_mode(lcd);
}

void init_lcd(lcd *lcd)
{
    init_lcd_members(lcd);
    init_lcd_pins(lcd);
    init_lcd_device(lcd);
}