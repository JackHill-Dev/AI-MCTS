#pragma once
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Scene.h"
#include "Player.h"
#include "Weapon.h"
#include "Armour.h"
#include "Consumable.h"



class ShopScene :
    public Scene
{
public:
	ShopScene(Interface* rng);
	~ShopScene();
	void Init();
	void Load();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	

	void PlaceItems();
	void SetupShopInv(); // For testing
	void ManageShopInventory(std::vector<Item*> inv, Act act, std::pair<int, int> mousePos);
	void ManagePlayerInventory(std::vector<Item*> inv, Act act, std::pair<int, int> mousePos);
	void GenerateGrids();
	void DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY);
	void RegeneratePlayerInventory(); // This function accomodates for the change in resolution
	
	Player mShop;
	UIText mPlayerGoldText;
	UIText mShopGoldText;
	// SFX
	Mix_Music* bg_Music;
	Mix_Chunk* buySell_SFX;
	Mix_Chunk* pCantBuy_SFX;
	Mix_Chunk* button_Click_SFX;
	Mix_Chunk* shop_Entry_SFX;
	Mix_Chunk* leave_SFX;
	RenderObject* pExitButton;
	ToolTip mTooltip;
	ToolTip playerToolTip;
	ItemObject* playerItemHovered;
	ItemObject* shopItemHovered;
	bool startOnce = false;
	int mHighestCharacter;
	
	int RandomRange(int min, int max);	
	std::vector<ItemObject> playerInv;
	std::vector<ItemObject> shopInv;

	UIText buyControlsTxt;

	
};

