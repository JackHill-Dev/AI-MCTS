#pragma once
#include "Scene.h"
#include "Character.h"

struct CharacterCard
{
	UIText name;
	UIText level;
	UIText strength;
	UIText health;
	UIText intelligence;
	UIText agility;
	UIText movement;
};



class PartyViewerScene : public Scene
{
public:
	PartyViewerScene(Interface* mgr);
	void Load();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	RenderObject* mCloseBtn;
	RenderObject* mInventoryBtn;
	Mix_Chunk* button_SFX;
	Mix_Music* mMenuMusic;

	void Init();
	void GetCharacterPortraits();
	void GetCharacterStatistics();

	UIText DrawStat(std::string statName, int stat, SDL_Color textColor, std::pair<int,int> pos);
	std::vector<Character*> mParty;
	std::vector<CharacterCard> characterCards;

};

