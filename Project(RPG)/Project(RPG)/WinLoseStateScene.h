#pragma once
#include "Scene.h"
#include "Actions.h"
#include "Character.h"
#include <SDL.h>

struct PlayerCharacter
{
	RenderObject* rObj;
	Character* pCharacter;
};

class WinLoseStateScene : public Scene
{

private:

	UIText mHeader;
	UIText mHeaderInstruction;
	UIText mFlavourText1;
	UIText mFlavourText2;
	UIText mFlavourText3;
	UIText mFlavourText4;
	UIText mFlavourText5;
	UIText mFlavourText6;
	UIText mGoldLootText;
	UIText mLevelUpText1;
	UIText mLevelUpText2;
	UIText mLevelUpText3;

	UIText mFooterInstruction;

	RenderObject* pBackground = nullptr;
	RenderObject* pGameClearBanner = nullptr;
	RenderObject* pConfirmButton = nullptr;
	RenderObject* pContinueButton = nullptr;
	RenderObject* pRejectButton = nullptr;
	RenderObject* pQuitButton = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pLeftSprite = nullptr;
	RenderObject* pCentreSprite = nullptr;
	RenderObject* pRightSprite = nullptr;
	RenderObject* pStrengthButton = nullptr;
	RenderObject* pAgilityButton = nullptr;
	RenderObject* pIntelligenceButton = nullptr;

	Mix_Music* Victory_Music = nullptr;
	Mix_Music* Defeat_Music = nullptr;

	Mix_Chunk* Victory_Sfx = nullptr;
	Mix_Chunk* Button_Sfx = nullptr;
	Mix_Chunk* Error_Sfx = nullptr;

	SDL_Color Lime = SDL_Color{ 0, 255, 0 };
	SDL_Color DimGray = SDL_Color{ 105,105,105 };
	SDL_Color Gold = SDL_Color{ 255,215,0 };

	PlayerCharacter* pFirstCharacter = nullptr;
	PlayerCharacter* pSecondCharacter  = nullptr;
	PlayerCharacter* pThirdCharacter   = nullptr;
	PlayerCharacter* pTargetCharacter =	nullptr;

	std::vector<std::string> mNames;
	std::vector<RenderObject*> pAllButtons;
	std::vector<RenderObject*> pStatButtons;
	std::vector<PlayerCharacter*> pCharacters;

	int mStatPoints = 0;
	int mStrPoints = 0;
	int mAgiPoints = 0;
	int mIntPoints = 0;
	int mDividedXp = 0;

	void SetUpButtons();
	void PickState();
	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);
	void SetUpWinState();
	void SetUpLoseState();
	void SetUpLevelUpState(PlayerCharacter*& pc);
	void SetUpGameClearState();
	
protected:

public:

	WinLoseStateScene(Interface* mObjMgr);

	void Load();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
};

