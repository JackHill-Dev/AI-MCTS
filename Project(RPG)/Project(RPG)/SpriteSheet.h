#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "Globals.h"
#include <map>
class SpriteSheet
{

private:
	SDL_Texture* mTexture;
	const float mCellSizeX;
	const float mCellSizeY;
	std::pair<int, int> textureSize;
	std::map<std::string,Animation> anims;
public:
	const bool fillScreen;
	const std::string mFilePath;

	bool SetTexture(SDL_Texture* texture);
	std::pair<float, float> GetTextureSize();
	SpriteSheet(std::string path, int textureSizeX, int textureSizeY, float nCellSizeX, float nCellSizeY ,bool fillScreen);
	SDL_Texture* GetTexture();
	std::pair<float, float> GetCellSize();
	Animation* GetAnim(std::string name);
	void AddAnim(std::string name, Animation anim);
};