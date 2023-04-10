#include <avr/io.h>
#include <util/delay.h>
#include <avr8-stub.h>
#include "app_api.h"
#include <avr/interrupt.h>
#include <uartlib.h>
#include <lcd.h>

int main(void)
{
    _delay_ms(100);
    
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;

    printf("Start\n");

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
