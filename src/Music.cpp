#include "Music.h"
#include "Resources.h"

Music::Music(void) : music(nullptr)
{
}

Music::Music(std::string file)
{
    Open(file);
}

void Music::Play(int times)
{
    Mix_PlayMusic(music.get(), times);
}

void Music::Stop(void)
{
    Mix_FadeOutMusic(10);
}

void Music::Open(std::string file)
{
    music = Resources::GetMusic(file);
}

bool Music::IsOpen(void)
{
    return (music != nullptr);
}
