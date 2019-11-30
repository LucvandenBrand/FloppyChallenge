#ifndef TEXT_INTERFACE_H
#define TEXT_INTERFACE_H

typedef enum {
    NORMAL,
    RED,
    GREEN,
    BLUE,
    WHITE
} Color;

void clear_screen();
void put_text(const char * text, ...);
void put_color_text(Color color, const char * text, ...);
void set_text_color(Color color);
void get_text(char * buffer);

#endif