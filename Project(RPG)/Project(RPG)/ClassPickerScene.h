#pragma once
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>
#include <numeric>

// Enum which facilitates the basic FSM(Finite State Machine) pattern -EH
enum CharacterPickerState
{
	ClassView = 0,
	WarriorView = 1,
	RogueView = 2,
	MageView = 3,
	BackgroundView = 4,
	VillagerView = 5,
	ScholarView = 6,
	NobleView = 7,
};

class ClassPickerScene : public Scene
{

private:

	UIText mHeader;
	UIText mHeaderInstruction;
	UIText mFlavourText1;
	UIText mFlavourText2;
	UIText mFlavourText3;
	UIText mFlavourText4;
	UIText mFooterInstruction;

	RenderObject* pBackBtn;
	RenderObject* pRejectBtn;
	RenderObject* pYesBtn;
	RenderObject* pWarriorIcon;
	RenderObject* pRogueIcon;
	RenderObject* pMageIcon;
	RenderObject* pVillagerIcon;
	RenderObject* pScholarIcon;
	RenderObject* pNobleIcon;
	RenderObject* pScrollBg;

	Mix_Music* bg_Music;
	Mix_Chunk* confirm_SFX;
	Mix_Chunk* back_SFX;
	std::vector<Character*> mCharacters;
	std::vector<RenderObject*> mIcons;
	std::vector<RenderObject*> mButtons;
	std::vector<int> currentPartyGold;
	std::vector<std::pair<int, int>> mCharacterStats;

	CharacterPickerState currentState;
	CharacterPickerState previousState;

	SDL_Color Lime = SDL_Color{ 0, 255, 0 };

	bool isFocused = false;
	const bool mBaseDeadStatus = false;

	int PartyCount = 0;
	const int mBaseLevel = 1;
	const int mVillagerGold = 50;
	const int mScholarGold = 100;
	const int mNobleGold = 150;
	const int maxPartySize = 1; // currently set to one for retricting AI scope

	// Allows these factors to be consistent and easily changed during playtesting and polish phase - EH
	const std::pair<int, int> mStatBuff = {2, 2};
	const std::pair<int, int> mStatDebuff = {-1, -1};
	const std::pair<int, int> mBaseXp = { 0,100 };
	const std::pair<int, int> mBaseClassBuff = { 12, 12 };
	const std::pair<int, int> mBaseClassDebuff = { 9,9 };
	const std::pair<int, int> mBaseClassStat = { 10,10 };
	const std::pair<int, int> mBaseHealth{ 15,15 };

	void GeneratePartyFromChoices();

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

	void SetUpClassView(CharacterPickerState originState);
	void SetUpWarriorView(CharacterPickerState originState);
	void SetUpRogueView(CharacterPickerState originState);
	void SetUpMageView(CharacterPickerState originState);

	void SetUpBackgroundView(CharacterPickerState originState);
	void SetUpVillagerView(CharacterPickerState originState);
	void SetUpScholarView(CharacterPickerState originState);
	void SetUpNobleView(CharacterPickerState originState);

protected:

public:

	ClassPickerScene(Interface* mObjMgr);

	void Load();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
	
};

