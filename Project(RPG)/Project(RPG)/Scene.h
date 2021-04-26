#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include "RenderObject.h"
#include "Globals.h"
#include "GameObjects.h"

#include "Interface.h"

struct UIText
{
	SDL_Texture* mFontTexture = nullptr;
	SDL_Surface* mTempTextSurface = nullptr;
	std::string text;
	std::pair<int, int> pos;
	std::pair<float, float> scale = std::make_pair(70,50);
	SDL_Color textColor;
	bool isVisible = true;
	bool bWrapped = false;

	std::string AddTab() { return "        "; } //TTF Doesn't support tabs. Tabs are 8 whitespaces long typically - EH

	std::pair<float, float>SetTextScale(float x, float y) 
	{ 
		scale = std::make_pair(x, y); 
		return scale;
	}
};

struct ItemObject
{
	Item* _item;
	RenderObject* obj;
	bool bPickedUp = false;

	ItemObject() {}
	ItemObject(Item* i, RenderObject* r) : _item(i), obj(r) {}
};

struct ToolTip
{
	ToolTip() {}
	ToolTip( RenderObject* itemObj, RenderObject* bg, UIText desc, std::pair<int, int> pos) : pBackground(bg),pItemImage(itemObj), mDescription(desc), mPos(pos)
	{
		pBackground->SetPos(mPos);
		pBackground->SetScale({ 4,4 });
		mDescription.pos = { mPos.first, mPos.second + 30 };
		pItemImage->SetPos({ mPos.first, mPos.second - 50 });

		pBackground->SetVisible(false);
		pItemImage->SetVisible(false);
		mDescription.isVisible = false;
		mDescription.textColor = SDL_Color{ 255,255,255 };

	}

	void Show()
	{
		pBackground->SetVisible(true);
		pItemImage->SetVisible(true);
		mDescription.isVisible = true;
	}
	void Hide()
	{
		pBackground->SetVisible(false);
		pItemImage->SetVisible(false);
		mDescription.isVisible = false;
	}
	void SetPos(std::pair<int, int> pos)
	{
		pBackground->SetPos(pos);
		pItemImage->SetPos({ pos.first, pos.second - 50 });
		mDescription.pos = { pos.first, pos.second + 30 };
	}

	RenderObject* pBackground = nullptr;
	RenderObject* pItemImage = nullptr;
	UIText mDescription;
	std::pair<int, int> mPos;
};

class Scene
{
private:
	
	std::string name;
	int counter = 0;
	SDL_Surface* mSurface = nullptr;
	
	TTF_Font* mFont;
protected:
	std::vector<std::vector<RenderObject*>> mLayers;
	std::vector<UIText*> mSceneText;

	virtual void Update(double dTime, Act act, std::pair<int, int> mousePos);
	
	Interface* mgr;
public:
	Scene() {}
	Scene(Interface* objmg);
	virtual ~Scene();
	void SceneUpdate(double dTime, Act act, std::pair<int, int> mousePos);

	void Draw(SDL_Renderer* rnd);
	
	
	void Clear(SDL_Renderer* rnd);
	RenderObject* AddObject(std::string obj, double x, double y, Layer layerNum);
};

