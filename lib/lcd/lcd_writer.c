#include <lcd_writer.h>

#define LANE_SIZE 16

static void lcd_writer_apply_cursor_pos(lcd_writer *lw)
{
    lcd_move_cursor(lw->lcd, lw->cursor.x, lw->cursor.y);
}

void lcd_writer_init(lcd_writer *lw, lcd *lcd)
{
    lw->lcd = lcd;
    lw->cursor.x = 0;
    lw->cursor.y = 0;

    lcd_clear(lw->lcd);
    lcd_writer_apply_cursor_pos(lw);
}

static void lcd_writer_next_y(lcd_writer *lw)
{
    if (lw->cursor.y == 0)
    {
        lw->cursor.y = 1;
        lw->cursor.x = 0;
    }
    else
    {
        lw->cursor.y = 0;
        lw->cursor.x = 0;
        lcd_clear(lw->lcd);
    }
    lcd_writer_apply_cursor_pos(lw);
}

static void lcd_writer_next_x(lcd_writer *lw)
{
    if (lw->cursor.x >= LANE_SIZE)
    {
        lw->cursor.x = 0;
        lcd_writer_next_y(lw);
    }
    lw->cursor.x++;
}

int lcddev_putchar(char c, FILE *stream)
{
    lcd_writer *lw = stream->udata;
    if (c == '\n')
        lcd_writer_next_y(lw);
    else if (c == '\r')
    {
        // do nothing
    }
    else
    {
        lcd_writer_next_x(lw);
        lcd_write_char(lw->lcd, c);
    }

    return 0;
}

FILE lcddev_open(lcd_writer *lw)
{
    FILE file;
    memset(&file, 0, sizeof(FILE));
    file.udata = lw;
    file.put = lcddev_putchar;
    file.get = NULL;
    file.flags = _FDEV_SETUP_WRITE;

    return file;
}