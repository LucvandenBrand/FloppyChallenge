#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

typedef struct {
    Mix_Chunk * mix_chunk;
} Audio;

#endif