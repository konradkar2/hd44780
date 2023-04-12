#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <uartlib.h>
#include <lcd.h>

int main(void)
{
    _delay_ms(500);
    
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;

    printf("Start\n");

    lcd lcd;
    lcd_init(&lcd);
    lcd_write(&lcd, "testtesttesttest_test");
    lcd_clear(&lcd);
    lcd_move_cursor(&lcd, 5, 1);
    lcd_write(&lcd, "dupa");
    lcd_move_cursor(&lcd, 0, 0);
    lcd_write(&lcd, "dupa");

    while (1)
    {
        _delay_ms(500);
    }
    return 0;
}
