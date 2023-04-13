#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <uartlib.h>
#include <lcd.h>
#include <lcd_writer.h>

int main(void)
{
    _delay_ms(200);

    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;

    printf("Start\n");

    lcd lcd;
    lcd_init(&lcd);

    lcd_writer lcd_writer;
    lcd_writer_init(&lcd_writer, &lcd);

    FILE lcd_file = lcddev_open(&lcd_writer);
    stdout = &lcd_file;
    
    printf("hello\nworld");

    while (1)
    {
        _delay_ms(500);
    }
    return 0;
}
