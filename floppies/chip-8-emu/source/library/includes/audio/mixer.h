#ifndef MIXER_H
#define MIXER_H

#include <audio/audio.h>

int init_mixer();
void close_mixer();
Audio load_audio(const char * path);
void play_audio(Audio audio);
void free_audio(Audio audio);

#endif