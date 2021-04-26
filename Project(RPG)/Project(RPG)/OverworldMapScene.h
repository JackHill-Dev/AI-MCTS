#pragma once
#include "json.hpp"
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <set>
#include <SDL.h>
#include <fstream>

struct new_Node
{
	new_Node(RenderObject* obj, bool shop, int seed) :obj(obj), shop(shop), seed(seed)
	{

	}

	std::vector<new_Node*> adjacentNodes;
	RenderObject* obj;
	bool shop = false;
	int seed = 0;
};

struct Legend
{
	UIText mStandardNodeLabel;
	UIText mShopNodeLabel;
	UIText mBossNodeLabel;
	UIText mCurrentLabel;
	UIText mAdjacentLabel;
	UIText mHeaderText;
	UIText mInstructionText;

	RenderObject* pLegendObj = nullptr;
	RenderObject* pNormalNode = nullptr;
	RenderObject* pHoveredNode = nullptr;
	RenderObject* pShopNode = nullptr;
	RenderObject* pHoveredShop = nullptr;
	RenderObject* pBossNode = nullptr;
	RenderObject* pHoveredBoss = nullptr;

	std::vector<RenderObject*> mLegendObjects;
};

class OverworldMapScene : public Scene
{

private:

	int mCurrentNode = 0;
	int mSeed;

	bool mLegendOn = true;

	RenderObject* pOverworld = nullptr;
	RenderObject* pLegendButton = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pSaveButton = nullptr;
	RenderObject* pSettingsButton = nullptr;
	RenderObject* pArmyViewerButton = nullptr;

	std::vector<RenderObject*> mOverworldButtons;

	Mix_Music* mBackgroundMus = nullptr;
	Mix_Chunk* button_Click_SFX;
	Mix_Chunk* confirm_SFX;
	Mix_Chunk* back_SFX;

	SDL_Color Lime = SDL_Color{ 0,255, 0 };
	SDL_Color Black = SDL_Color{ 0,0,0 };

	std::vector<new_Node> mMap;
	new_Node* pBoss = nullptr;

	Legend mLegend;

	void Init();
	void SaveFile();
	void LoadNodes();
	void ShowLegend();
	void HideLegend();
	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);
	bool IsCombat();
	double Uniform();
	std::pair<int, int> ScaleEnemyStats();

protected:

public:

	OverworldMapScene(Interface* mObjMgr);
	void Load();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
};


