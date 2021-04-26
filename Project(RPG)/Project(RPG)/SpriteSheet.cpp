#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string path, int textureSizeX, int textureSizeY, float nCellSizeX, float nCellSizeY, bool fillScreen) : mFilePath(path), fillScreen(fillScreen), mCellSizeX(nCellSizeX),  mCellSizeY(nCellSizeY), textureSize(std::make_pair(textureSizeX,textureSizeY))
{
	if(!anims.count("default"))
		anims.insert(std::make_pair("default", Animation("default", { std::make_pair(0,0) })));
	//anims["default"] =  Animation("default", { std::make_pair(0,0) });
}

SDL_Texture* SpriteSheet::GetTexture()
{
	return mTexture;
}

bool SpriteSheet::SetTexture(SDL_Texture* texture)
{
	if (mTexture == nullptr)
	{
		mTexture = texture;
		return true;
	}
	return false;
}
std::pair<float, float> SpriteSheet::GetTextureSize()
{
	return textureSize;
}
std::pair<float, float> SpriteSheet::GetCellSize()
{
	return std::make_pair(mCellSizeX, mCellSizeY);
}
Animation* SpriteSheet::GetAnim(std::string name)
{
	if(anims.find(name) == anims.end())
		return &anims["default"];
	if (&anims[name] == nullptr)
		return &anims["default"];
	return &anims[name];
}
void SpriteSheet::AddAnim(std::string name, Animation anim)
{
	anims[name] = anim;
}