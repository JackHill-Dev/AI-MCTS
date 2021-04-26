#include "PartyViewerScene.h"

PartyViewerScene::PartyViewerScene(Interface* mgr) : Scene(mgr)
{
	// Add background to scene
	AddObject("ShopBGObj", 640, 360, Background);
	// Add close button to scene
	mCloseBtn = AddObject("CloseBtnObj", 1200, 50, UI);
	mInventoryBtn = AddObject("inventoryButtonObj", 640, 700, UI);
	button_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	mMenuMusic = Mix_LoadMUS("Assets/Music/MenuMusic.mp3");

	characterCards.reserve(3);

	for (int i = 0; i < characterCards.capacity(); ++i)
	{
		characterCards.emplace_back(CharacterCard());
	}

	Init();

}

void PartyViewerScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	if (act == Act::MouseUpdate)
	{
		if (mInventoryBtn->InBounds(mousePos.first, mousePos.second))
		{
			mInventoryBtn->Tint({ 0,255,0 });
		}
		else
		{
			mInventoryBtn->Untint();
		}
		if (mCloseBtn->InBounds(mousePos.first, mousePos.second))
		{
			mCloseBtn->Tint({ 0,255,0 });
		}
		else
		{
			mCloseBtn->Untint();
		}
	}

	// Check if close button has been pressed 
	if (act == Act::Click && mCloseBtn->InBounds(mousePos.first, mousePos.second))
	{
		mgr->PlaySFX(button_SFX, 0, 1);
		mgr->LoadScene(Overworld); 	// Go to previous scene that opened the party viewer
		mCloseBtn->Untint();
	}
		
	if (act == Act::Click && mInventoryBtn->InBounds(mousePos.first, mousePos.second))
	{
		mgr->PlaySFX(button_SFX, 0, 1);
		mgr->LoadScene(Scenes::InventoryScreen); // Inventory screen
		mInventoryBtn->Untint();
	}

	mSceneText.clear();

	GetCharacterStatistics();
}


void PartyViewerScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();
	GetCharacterPortraits();
}

void PartyViewerScene::Load()
{
	for (auto a : mLayers[Game])
		delete a;
	mLayers[Game].clear();
	mParty = mgr->GetPlayer()->GetParty();
	GetCharacterPortraits();
	GetCharacterStatistics();

	if (mgr->GetPreviousScene() != Scenes::InventoryScreen)
	{
		mgr->FadeInMusic(mMenuMusic, -1, mgr->fadeTime);
	}
}

void PartyViewerScene::GetCharacterPortraits()
{
	int offsetX = 390; // Allows for equal seperation of portraits and frames
	
	// Get all party memebers from player
	for (Character* c : mParty)
	{
		AddObject(c->GetPortraitName(), offsetX, 180, Game); // Get all of their portrait render objects and add them to the scene
		offsetX += 250;							
	}
	offsetX = 390;
	// Add character frame object for each party memeber
	for (int i = 0; i < mParty.size(); ++i)
	{
		AddObject("characterFrameObj", offsetX, 350, Background);
		offsetX += 250;
	}
}

void PartyViewerScene::GetCharacterStatistics()
{
	int offsetX = 390;
	int offsetY = 330;
	int i = 0;
	for (Character* c  : mParty) 
	{

		characterCards[i].name =  UIText{ nullptr, nullptr, "Name: " + c->GetClassName(c->GetClass()), std::make_pair(offsetX, offsetY), std::make_pair<float,float>(160, 60), SDL_Color{31,30,29} };
		offsetY += 50;

		//+" Next: " + std::to_string(c->GetStats().experience.second - c->GetStats().experience.first + "XP"
		characterCards[i].level =  UIText{ nullptr, nullptr, "Level: " + std::to_string(c->GetStats().level) + " XP: " + std::to_string(c->GetStats().experience.first) + "/" + std::to_string(c->GetStats().experience.second), std::make_pair(offsetX, offsetY), std::make_pair<float,float>(160, 60), SDL_Color{31,30,29} };
		offsetY += 50;
		characterCards[i].health =  UIText{ nullptr, nullptr, "Health: " + std::to_string(c->GetStats().health.first) + "/" + std::to_string(c->GetStats().health.second), std::make_pair(offsetX, offsetY), std::make_pair<float,float>(160, 60), SDL_Color{178,34,34} };
		offsetY += 50;

		characterCards[i].strength = DrawStat("Strength", c->GetStats().strength.second, SDL_Color{ 151,112,15 }, std::make_pair(offsetX, offsetY));
	
		offsetY += 50;
		characterCards[i].agility = DrawStat("Agility", c->GetStats().agility.second, SDL_Color{ 0,100,0 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		characterCards[i].intelligence = DrawStat("Intelligence", c->GetStats().intelligence.second, SDL_Color{ 50,50,150 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		characterCards[i].movement = DrawStat("Movement", c->GetStats().movement.second, SDL_Color{ 31,30,29 }, std::make_pair(offsetX, offsetY));

		mSceneText.push_back(&characterCards[i].name);
		mSceneText.push_back(&characterCards[i].level);
		mSceneText.push_back(&characterCards[i].health);
		mSceneText.push_back(&characterCards[i].intelligence);
		mSceneText.push_back(&characterCards[i].agility);
		mSceneText.push_back(&characterCards[i].strength);
		mSceneText.push_back(&characterCards[i].movement);

		offsetX += 250;
		offsetY = 330;

		++i;
	}
}

UIText PartyViewerScene::DrawStat(std::string statName, int stat, SDL_Color textColor, std::pair<int, int> pos)
{
	std::string statTxt = statName + ": " + std::to_string(stat);
	return  UIText{ nullptr, nullptr, statTxt, pos, std::make_pair<float,float>(160, 60), textColor };
}

