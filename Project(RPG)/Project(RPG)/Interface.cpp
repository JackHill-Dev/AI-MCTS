#include "Interface.h"



Interface::Interface(int* seed,bool* brunning, std::map<std::string, RenderObject*>* objP, Scenes* currentScene, std::pair<std::vector<Character*>, int>* currentEnemies, Player* player, Settings* settings, std::map<std::string, Item*>* nItems) : seed(seed),objects(objP), currentScene(currentScene), running(brunning), currentCombat(currentEnemies), pPlayer(player), pSettings(settings), items(nItems)
{}

RenderObject* Interface::RequestObject(std::string name)
{
	return (*objects)[name]->Clone(); // Returns a clone of the object, a "deep" pointer copy
}

Item* Interface::RequestItem(std::string name)
{
	return (*items)[name]->Clone();
}

void Interface::PlayMusic(Mix_Music* pMusic, int loops) // overload for testing until the database and import manager classes are created
{
	Mix_VolumeMusic(10); // this is the volume at which the music is playing, 10 I believe is quite high, the volume range goes from 0-128 -JP
	Mix_PlayMusic(pMusic, loops);	//Will add and overrite current music with pointer to file, and determine how many times it will repeat
}
void Interface::FadeInMusic(Mix_Music* pMusic, int loops, int ms)
{
	Mix_FadeInMusic(pMusic, loops, ms);
}
void Interface::FadeOutMusic(int ms)
{
	Mix_FadeOutMusic(ms);
}
void Interface::PlaySFX(Mix_Chunk* pSfx, int loops, int channel)
{
	Mix_PlayChannel(channel, pSfx, loops); //This is where we can play sound effects, the different channels allow multiple sound effects to play at once
}

void Interface::SetMasterVolume(int channel, int musVolume, int sfxVolume)
{
	Mix_VolumeMusic(musVolume);
	Mix_Volume(channel, sfxVolume);
}


void Interface::StopMusic() // This stops the music playing regardless of loops remaining
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void Interface::LoadScene(Scenes scene)
{
	prevScene = *currentScene; 
	*currentScene = scene;
	SDL_Delay(100);
}

void Interface::LoadPreviousScene()
{
	Scenes origin = *currentScene; // Added this in so we can still keep track of the Scene this was called from - EH
	*currentScene = prevScene;
	prevScene = origin;
}

void Interface::SetWindowSize()
{
	SDL_SetWindowSize(mWnd, pSettings->w, pSettings->h);
	SDL_SetWindowPosition(mWnd, SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK);
}

void Interface::SetFullScreen()
{
	if (pSettings->bIsFullScreen)
		SDL_SetWindowFullscreen(mWnd, SDL_WINDOW_FULLSCREEN); 
	else
		SDL_SetWindowFullscreen(mWnd, 0); // Go back to windowed mode
}
