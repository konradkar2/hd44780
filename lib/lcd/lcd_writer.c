#include <lcd_writer.h>

#define LANE_SIZE 16

void lcd_writer_init(lcd_writer *lw, lcd *lcd)
{
    lw->lcd = lcd;
    lw->cursor.x = 0;
    lw->cursor.y = 0;

    lcd_clear(&lw->lcd);
    lcd_move_cursor(&lw->lcd, lw->cursor.x, lw->cursor.y);
}

void lcd_writer_write(lcd_writer *lw, const char *text)
{
    if(strlen > LANE_SIZE)
    {
        lcd_clear(&lw->lcd);
        lcd_move_cursor(&lw->lcd, lw->cursor.x, lw->cursor.y);

        lcd_write(&lw->lcd, text);
    }
}