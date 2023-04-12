#include <avr/io.h>
#include <lcd.h>
#include <util/delay.h>
#include <string.h>

#define LCD_CLEAR _BV(0)

#define LCD_FS _BV(5)
#define LCD_8BIT _BV(4)
#define LCD_4BIT 0
#define LCD_2LINE _BV(3)
#define LCD_1LINE 0
#define LCD_FONT_5x10 _BV(2)
#define LCD_FONT_5x8 0

#define LCD_DISPLAY_CTRL _BV(3)
#define LCD_DISPLAY_ON _BV(2)
#define LCD_DISPLAY_OFF 0
#define LCD_CURSOR_ON _BV(1)
#define LCD_CURSOR_OFF 0
#define LCD_CURSOR_BLINK_ON _BV(0)
#define LCD_CURSOR_BLINK_OFF 0

#define LCD_ENTRY_MODE _BV(2)
#define LCD_INCREMENT _BV(1)
#define LCD_DECREMENT 0
#define LCD_ACCOMPANY_DISPLAY_SHIFT _BV(0)
#define LCD_DONT_ACCOMPANY_DISPLAY_SHIFT 0


#define LCD_DDRAM_SET _BV(7)
#define LCD_1LINE_ADDR 0x0
#define LCD_2LINE_ADDR 0x40

static void lcd_init_pins(lcd *lcd)
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

static void lcd_init_members(lcd *lcd)
{
    digital_pin rs = {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD2)};
    digital_pin rw = {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD3)};
    digital_pin e = {.dir = &DDRD, .value = &PORTD, .mask = _BV(PD4)};
    data_pins dataPins = {.s.db4 = {.dir = &DDRD, .value = &PORTD, .mask = 0x0 | _BV(PD5)},
                          .s.db5 = {.dir = &DDRD, .value = &PORTD, .mask = 0x0 | _BV(PD6)},
                          .s.db6 = {.dir = &DDRD, .value = &PORTD, .mask = 0x0 | _BV(PD7)},
                          .s.db7 = {.dir = &DDRB, .value = &PORTB, .mask = 0x0 | _BV(PB0)}};

    lcd->rs = rs;
    lcd->rw = rw;
    lcd->e = e;
    lcd->data_pins = dataPins;
}

static void send_pulse(lcd *lcd)
{
    int delayUs = 1;
    set_low(&lcd->e);
    _delay_us(delayUs);
    set_high(&lcd->e);
    _delay_us(delayUs);
    set_low(&lcd->e);
    _delay_us(100);
}

static void set_4_lsb(lcd *lcd, uint8_t data)
{
    for (int i = 3; i >= 0; --i)
    {
        if (data & _BV(i))
            set_high(&lcd->data_pins.all[i]);
        else
            set_low(&lcd->data_pins.all[i]);
    }
}

static void write4_lsb(lcd *lcd, uint8_t data)
{
    set_4_lsb(lcd, data);
    _delay_us(5);

    send_pulse(lcd);
}

static void write4_msb(lcd *lcd, uint8_t data)
{
    write4_lsb(lcd, data >> 4);
}

static void write_command(lcd *lcd, uint8_t command)
{
    set_low(&lcd->rs);
    set_low(&lcd->rw);

    write4_msb(lcd, command);
    write4_lsb(lcd, command);
    _delay_us(100);
}

void lcd_write_char(lcd *lcd, char c)
{
    lcd_write(lcd, &c, 1);
}

void lcd_write(lcd *lcd, const uint8_t * data, size_t size)
{
    set_high(&lcd->rs);
    set_low(&lcd->rw);

    for (size_t i = 0; i < size; ++i)
    {
        write4_msb(lcd, data[i]);
        write4_lsb(lcd, data[i]);
    }
}

void lcd_move_cursor(lcd * lcd, int x, int y)
{
    if(x > 16)
        x = 0;
    if(y > 1)
        y = 0;
    
    uint8_t addr = x + (y == 0 ? LCD_1LINE_ADDR : LCD_2LINE_ADDR); 
    write_command(lcd, LCD_DDRAM_SET + addr);
}

void lcd_clear(lcd * lcd)
{
    write_command(lcd, LCD_CLEAR);
    _delay_ms(2);
}


void lcd_init_device(lcd *lcd)
{
    set_low(&lcd->rw);
    set_low(&lcd->rs);

    write4_msb(lcd, LCD_FS | LCD_8BIT);
    _delay_ms(5);
    write4_msb(lcd, LCD_FS | LCD_8BIT);
    _delay_ms(5);
    write4_msb(lcd, LCD_FS | LCD_8BIT);
    _delay_us(50);
    write4_msb(lcd, LCD_FS | LCD_4BIT);

    write_command(lcd, LCD_FS | LCD_4BIT | LCD_2LINE | LCD_FONT_5x8);
    write_command(lcd, LCD_DISPLAY_CTRL | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_CURSOR_BLINK_ON);
    write_command(lcd, LCD_ENTRY_MODE | LCD_DONT_ACCOMPANY_DISPLAY_SHIFT | LCD_INCREMENT);
    lcd_clear(lcd);
}

void lcd_init(lcd *lcd)
{
    lcd_init_members(lcd);
    lcd_init_pins(lcd);
    lcd_init_device(lcd);
}