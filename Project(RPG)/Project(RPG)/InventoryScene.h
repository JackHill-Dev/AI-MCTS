#pragma once
#include "Scene.h"

struct characterInventory
{
	characterInventory(Character* character, RenderObject* portrait, RenderObject* weaponSlot, RenderObject* armourSlot) :portrait(portrait), weaponSlot(weaponSlot), armourSlot(armourSlot), character(character)
	{

	}
	Character* character;
	RenderObject* portrait;
	RenderObject* weaponSlot;
	RenderObject* armourSlot;

};

class InventoryScene :
	public Scene
{
public:
	InventoryScene(Interface* mgr);
	virtual ~InventoryScene();
	void Load();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	void Init();
	void DrawGrid(int offsetX, int offsetY, int gridBoundsX);
private:
	bool itemPickedUp = false;
	RenderObject* pCloseBtn;
	Mix_Chunk* pButton_SFX;
	Mix_Chunk* pDrink_SFX;
	Mix_Chunk* pGrab_SFX;
	Mix_Chunk* pDrop_SFX;
	ToolTip mToolTip;
	std::vector< std::pair<RenderObject*, ItemObject*>> playerInvGrid;
	std::vector<ItemObject> itemObjects;
	std::vector<characterInventory> characters;
	std::vector<Character*> mParty;
	// temp
	int it = 1;
	int pos;
	bool bHasitemPickedUp = false;
	std::vector<RenderObject*>::iterator freePos;
};

