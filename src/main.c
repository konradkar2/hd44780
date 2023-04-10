#include <avr/io.h>
#include <util/delay.h>
#include <avr8-stub.h>
#include "app_api.h"
#include <avr/interrupt.h>

struct digital_pin
{
    volatile uint8_t *dir;
    volatile uint8_t *value;
    uint8_t mask;
};
typedef struct digital_pin digital_pin;

void set_out(digital_pin *pin)
{
    *pin->dir |= pin->mask;
}

void set_in(digital_pin *pin)
{
    *pin->dir &= ~pin->mask;
}

void set_high(digital_pin *pin)
{
    *pin->value |= pin->mask;
}

void set_low(digital_pin *pin)
{
    *pin->value &= ~pin->mask;
}

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

void init_lcd_pins(lcd *lcd)
{
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

void init_lcd_device(lcd *lcd)
{
    //command
    set_low(&lcd->rs);
    
}

void init_lcd(lcd *lcd)
{
    init_lcd_members(lcd);
    init_lcd_pins(lcd);
    init_lcd_device(lcd);
}

int main(void)
{
    // debug_init();
    // sei();
    // breakpoint();

    lcd lcd;
    init_lcd(&lcd);
    while (1)
    {
        set_low(&lcd.data_pins.s.d6);
        _delay_ms(500);
        set_high(&lcd.data_pins.s.d6);
        _delay_ms(500);
    }
    return 0;
}
