#include <audio/mixer.h>
#include <SDL_mixer.h>

int init_mixer()
{
    return Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0;
}

void close_mixer()
{
    Mix_Quit();
}

Audio load_audio(const char * path)
{
    Audio audio;
    audio.mix_chunk = Mix_LoadWAV(path);
    return audio;
}

void play_audio(Audio audio)
{
    Mix_PlayChannel(-1, audio.mix_chunk, 0);
}

void free_audio(Audio audio)
{
    Mix_FreeChunk(audio.mix_chunk);
}