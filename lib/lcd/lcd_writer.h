#ifndef LCD_WRITER_H
#define LCD_WRITER_H

#include <stdio.h>
#include <lcd.h>

struct lcd_writer
{
    lcd *lcd;
    struct cursor
    {
        int x;
        int y;
    } cursor;
};
typedef struct lcd_writer lcd_writer;

void lcd_writer_init(lcd_writer *lw, lcd *lcd);
void lcd_writer_write(lcd_writer *lw, char c);

int lcddev_putchar(char c, FILE *stream);
int lcddev_getchar(FILE *stream);
FILE lcddev_open(lcd_writer *lw);

#endif