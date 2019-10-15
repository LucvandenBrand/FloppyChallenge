#include <io/text_interface.h>
#include <game.h>

int main()
{
    clear_screen();
    put_text("o------------------Text-Adventure----------------o\n");
    game_loop();

    put_text("\nTHE END, See https://floppychallenge.com for more!\n");
    put_text("o------------------------------------------------o\n");
    return 0;
}
