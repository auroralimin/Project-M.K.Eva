#include "Sound.h"
#include "Resources.h"

Sound::Sound(void) : chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file)
{	
	Open(file);
}

void Sound::Play(int times)
{
	channel = Mix_PlayChannel(-1, chunk.get(), times); 
}

void Sound::Stop(void)
{
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file)
{
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(void)
{
	return (chunk != nullptr);
}



