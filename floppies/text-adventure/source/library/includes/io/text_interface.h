#ifndef TEXT_INTERFACE_H
#define TEXT_INTERFACE_H

typedef enum {
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE
} Color;

void clear_screen();
void put_text(const char * text, ...);
void put_color_text(Color color, const char * text, ...);
void get_text(char * buffer);

#endif