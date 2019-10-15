#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define MAX_INPUT_SIZE 100

typedef struct{
    bool is_running;
} GameState;

void game_loop();
GameState init_game_state();
void apply_input_to_game_state(const char * input, GameState * game);

#endif