#include "OverworldMapScene.h"

using jsonf = nlohmann::json;

OverworldMapScene::OverworldMapScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pOverworld = AddObject("overworldObj", 640, 360, Map);
	mLegend.pLegendObj = AddObject("legendObj", 1190, 180, UI);
	mLegend.pLegendObj->SetScale({ 0.9, 0.9 });
	pArmyViewerButton = AddObject("armyViewerButtonObj", 200, 700, UI);
	pLegendButton = AddObject("legendButtonObj", 1070, 700, UI);
	pSettingsButton = AddObject("settingsBtnObj", 780, 700, UI);
	pMenuButton = AddObject("menuButtonObj", 490, 700, UI);

	mOverworldButtons.push_back(pArmyViewerButton);
	mOverworldButtons.push_back(pLegendButton);
	mOverworldButtons.push_back(pSettingsButton);
	mOverworldButtons.push_back(pMenuButton);
	mBackgroundMus = Mix_LoadMUS("Assets/Music/Overworld.mp3");
	
	Init();
}

void OverworldMapScene::Init()
{
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");
	button_Click_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
}

void OverworldMapScene::Load()
{

	SaveFile();

	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mBackgroundMus, -1, mgr->fadeTime);
	}

	LoadNodes();

	if (mLegendOn == true)
	{
		ShowLegend();
	}
	else
	{
		HideLegend();
	}

	mCurrentNode = mgr->GetPlayer()->currentNode;

	for (auto i : mMap[mCurrentNode].adjacentNodes)
	{
		i->obj->tint = { 0,0,255 };
	}

	for (auto character : mgr->GetPlayer()->GetParty())
	{
		character->SetDeadStatus(false);
	}

	mMap[mCurrentNode].obj->tint = { 255,0,0 };

}

void OverworldMapScene::LoadNodes()
{
	for (auto i : mLayers[Game])
	{
		delete i;
	}

	mLayers[Game].clear();
	mMap.clear();
	
	mSeed = mgr->GetSeed();

	if(mSeed == 0)
	for (int i = 1; i < 4; i++)
	{
		mSeed += std::pow((rand() % 100),i);
	}

	std::pair<int, int> center = std::make_pair(640, 360);
	int squaresize = 350;

	srand(mSeed);
	SaveFile();

	const double PI = 3.14159265358979732384626433832795;
	double m_radius = 300;

	std::vector<std::pair<double, double>> points;
	points.push_back(center);

	for (int i = 0; i < 300; i++)
	{
		double theta = 2 * 3.14159265358979323846264 * Uniform();
		double r = sqrt(Uniform());

		std::pair<double, double> point = std::make_pair(
			center.first + r * m_radius * cos(theta),
			center.second + r * m_radius * sin(theta));
		
		bool allow = true;

		for (auto p : points)
			if (!(std::abs(p.first - point.first) > 15 && std::abs(p.second - point.second) > 10))
				allow = false;
				
			if(allow)
				points.push_back(point);		
	};

	int i = 0;	

	points.erase(points.begin());

	int shopamount = 0;

	for (auto& i : points)
	{
		bool shop = false;
		if (rand() % 6 == 5 && shopamount < 5)
		{
			shopamount++;
			shop = true;
			mMap.push_back(new_Node(AddObject("shopNodeObj", i.first, i.second, Game), shop, std::rand() % 100 + 10));
		}
		else
		{
			mMap.push_back(new_Node(AddObject("nodeObj", i.first, i.second, Game), shop, std::rand() % 100 + 10));
		}
	}

	mMap.push_back(new_Node(AddObject("battleNodeObj", center.first, center.second, Game), false, 0));
	pBoss = &mMap.back();

	for (auto &i : mMap)
	{
		int adjacentCount = 3;

		while (i.adjacentNodes.size() < adjacentCount)
		{
			int lowestDistance = INT_MAX;
			new_Node* node = nullptr;

			for (auto& n : mMap)
			{
				auto ind = std::find_if(i.adjacentNodes.begin(), i.adjacentNodes.end(), [n](new_Node* nod) {return n.obj == nod->obj; });
				int range = std::abs(i.obj->GetPos().first - n.obj->GetPos().first) + std::abs(i.obj->GetPos().second - n.obj->GetPos().second);

				if (i.obj != n.obj && range < lowestDistance && ind == i.adjacentNodes.end())
				{
					node = &n;
					lowestDistance = range;
				}			
			}

			if (node == nullptr)
			{
				std::cout << "ERROR cant find node!";
				break;
			}
			else
			{
				i.adjacentNodes.push_back(node);
				node->adjacentNodes.push_back(&i);
			}
		}
	}		
}

// Handles mouse events such as hovering and navigation between scenes - EH
void OverworldMapScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	if (act == Act::MouseUpdate)
	{
		int t = 0;

		for (auto& i : mMap)
		{
			if (t != mCurrentNode)
			{
				bool found = (std::find_if(mMap[mCurrentNode].adjacentNodes.begin(), mMap[mCurrentNode].adjacentNodes.end(), [i](new_Node* node) {return i.obj == node->obj; }) != mMap[mCurrentNode].adjacentNodes.end());
				if (!found)
					i.obj->Untint();
			}
			t++;
		}
		t = 0;
		for (auto button : mOverworldButtons)
		{
			if (button->InBounds(mousePos.first, mousePos.second))
			{
				OnHover(button);
			}
			else
			{
				OnLeave(button);
			}
		}
	}

	if (act == Act::Click)
	{
		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			pMenuButton->Untint();
			mgr->LoadScene(Scenes::MainMenu);

		}

		else if (pArmyViewerButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			mgr->LoadScene(Scenes::Party);
			pArmyViewerButton->Untint();
		}

		else if (pSettingsButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			mgr->LoadScene(Scenes::SettingsPage);
			pSettingsButton->Untint();
		}

		else if (pLegendButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);

			if (mLegendOn == true)
			{
				HideLegend();
			}
			else
			{
				ShowLegend();
			}
		}
		else
		{
			int t = 0;
			for (auto& i : mMap)
			{
				if (t != mCurrentNode)
				{
					bool found = (std::find_if(mMap[mCurrentNode].adjacentNodes.begin(), mMap[mCurrentNode].adjacentNodes.end(), [i](new_Node* node) {return i.obj == node->obj; }) != mMap[mCurrentNode].adjacentNodes.end());
					if (!found)
						i.obj->Untint();
				}

				if (i.obj->InBounds(mousePos.first, mousePos.second))
				{
					if (std::find_if(mMap[mCurrentNode].adjacentNodes.begin(), mMap[mCurrentNode].adjacentNodes.end(), [i](new_Node* node) {return i.obj == node->obj; }) != mMap[mCurrentNode].adjacentNodes.end())
					{
						mMap[mCurrentNode].obj->Untint();
						for (auto a : mMap[mCurrentNode].adjacentNodes)
							a->obj->Untint();
						mCurrentNode = t;
						mgr->GetPlayer()->currentNode = mCurrentNode;
						mMap[mCurrentNode].obj->tint = { 255,0,0 };
						for (auto a : i.adjacentNodes)
							a->obj->tint = { 0,0,255 };
						if (&i == pBoss)
						{
							mgr->PlaySFX(button_Click_SFX, 0, 1);
							mgr->LoadScene(Scenes::Boss);
						}
						else
							if (i.shop)
							{
								mgr->LoadScene(Scenes::Shops);
							}
							else
							{
								if (true)
								{
									std::vector<Character*> enemy;
									int number = 0;

									// Protects new players by ensuring you aren't outnumbered at first level
									if (mgr->GetPlayer()->GetParty()[0]->GetLevel() == 1)
									{
										number = 1;//std::rand() % 3 + 1;
									}
									else
									{
										number = 1; //std::rand() % 4 + 1;
									}

									// This seeds on current time to ensure enemy stats are random and different from other enemies - EH
									srand(time(0));
									const int& healthOffset = 5;
									for (int i = 0; i < number; ++i)
									{	
										
										std::pair<int, int> health = ScaleEnemyStats();
										health.first += healthOffset;
										health.second += healthOffset;
										enemy.push_back(new Character("portrait", "maleObj", " ", UnitClass::NoClass, 0, std::make_pair(100, 200), false, health, ScaleEnemyStats(), ScaleEnemyStats(), ScaleEnemyStats()));
									}

									mgr->LoadCombatScene(enemy, i.seed);
								}
								mgr->PlaySFX(button_Click_SFX, 0, 1);
							}
						mgr->PlaySFX(button_Click_SFX, 0, 1);
					}
				}
				t++;
			}
		}
	}
}

void OverworldMapScene::SaveFile()
{
	std::ofstream file("Savedata.Json");
	nlohmann::json characters;

	for (auto i : mgr->GetPlayer()->GetParty())
	{
		std::string armour = "NONE", weapon = "NONE";
		if (i->mWeaponEquipSlot != nullptr)
		{
			weapon = i->mWeaponEquipSlot->GetName();
		}
		if (i->ArmourEquipSlot != nullptr)
		{
			armour = i->ArmourEquipSlot->GetName();
		}

		characters.push_back({ {"Portrait", i->GetPortraitName()}, {"Object", i->GetObjName()}, {"Name", i->GetClassName(i->GetStats().cClass)}, {"Class", i->GetStats().cClass}, {"Level", i->GetLevel()},
							   {"Experience", i->GetStats().experience}, {"Dead", i->GetDeadStatus()},
							   { "Health", i->GetStats().health}, {"Strength", i->GetStats().strength},{"Intelligence", i->GetStats().intelligence},{"Agility", i->GetStats().agility},
							   {"Weapon", weapon}, {"Armour", armour} });
	}

	nlohmann::json playerInventory;

	for (auto item : mgr->GetPlayer()->GetInventory())
	{
		playerInventory.push_back({ item->GetName() });
	}

	nlohmann::json j;
	j["Saves"]["Save"]["Seed"] = mgr->GetSeed();
	j["Saves"]["Save"]["Gold"] = mgr->GetPlayer()->GetGold();
	j["Saves"]["Save"]["Inventory"] = playerInventory;
	j["Saves"]["Save"]["Characters"] = characters;
	j["Saves"]["Save"]["CurrentNode"] = mCurrentNode;

	file << j;
}

void OverworldMapScene::ShowLegend()
{
	mLegend.pLegendObj->SetVisible(true);
	mLegendOn = true;

	mLegend.pNormalNode = AddObject("nodeObj", 1150, 150, UI);
	mLegend.pNormalNode->Tint({ 255,0,0 });
	mLegend.pHoveredNode = AddObject("nodeObj", 1230, 150, UI);
	mLegend.pHoveredNode->Tint({ 0,0,255 });

	mLegend.pShopNode = AddObject("shopNodeObj", 1150, 230, UI);
	mLegend.pShopNode->Tint({ 255,0,0 });
	mLegend.pHoveredShop = AddObject("shopNodeObj", 1230, 230, UI);
	mLegend.pHoveredShop->Tint({ 0,0,255 });

	mLegend.pBossNode = AddObject("battleNodeObj", 1150, 300, UI);
	mLegend.pBossNode->Tint({ 255,0,0 });
	mLegend.pHoveredBoss = AddObject("battleNodeObj", 1230, 300, UI);
	mLegend.pHoveredBoss->Tint({ 0,0,255 });

	mLegend.mLegendObjects.push_back(mLegend.pNormalNode);
	mLegend.mLegendObjects.push_back(mLegend.pHoveredNode);
	mLegend.mLegendObjects.push_back(mLegend.pShopNode);
	mLegend.mLegendObjects.push_back(mLegend.pHoveredShop);
	mLegend.mLegendObjects.push_back(mLegend.pBossNode);
	mLegend.mLegendObjects.push_back(mLegend.pHoveredBoss);

	mSceneText.clear();
	
	for (auto object : mLegend.mLegendObjects)
	{
		object->SetVisible(true);
	}
	
	mLegend.mHeaderText.text = "LEGEND";
	mLegend.mHeaderText.textColor = Black;
	mLegend.mHeaderText.pos = { 1190, 45 };
	mLegend.mHeaderText.SetTextScale(120, 35);

	mLegend.mCurrentLabel.text = "CURRENT";
	mLegend.mCurrentLabel.textColor = Black;
	mLegend.mCurrentLabel.pos = { 1150, 85 };
	mLegend.mCurrentLabel.SetTextScale(50, 30);

	mLegend.mAdjacentLabel.text = "ADJACENT";
	mLegend.mAdjacentLabel.textColor = Black;
	mLegend.mAdjacentLabel.pos = { 1225, 85 };
	mLegend.mAdjacentLabel.SetTextScale(60, 30);

	mLegend.mStandardNodeLabel.text = "STANDARD";
	mLegend.mStandardNodeLabel.textColor = Black;
	mLegend.mStandardNodeLabel.pos = { 1190, 115 };
	mLegend.mStandardNodeLabel.SetTextScale(60, 30);

	mLegend.mShopNodeLabel.text = "SHOP";
	mLegend.mShopNodeLabel.textColor = Black;
	mLegend.mShopNodeLabel.pos = { 1190, 195 };
	mLegend.mShopNodeLabel.SetTextScale(60, 30);

	mLegend.mBossNodeLabel.text = "BOSS";
	mLegend.mBossNodeLabel.textColor = Black;
	mLegend.mBossNodeLabel.pos = { 1190, 265 };
	mLegend.mBossNodeLabel.SetTextScale(60, 30);

	mLegend.mInstructionText.text = "Click node to travel";
	mLegend.mInstructionText.textColor = Black;
	mLegend.mInstructionText.pos = { 1190, 340 };
	mLegend.mInstructionText.SetTextScale(140, 40);

	mSceneText.push_back(&mLegend.mHeaderText);
	mSceneText.push_back(&mLegend.mCurrentLabel);
	mSceneText.push_back(&mLegend.mAdjacentLabel);
	mSceneText.push_back(&mLegend.mStandardNodeLabel);
	mSceneText.push_back(&mLegend.mShopNodeLabel);
	mSceneText.push_back(&mLegend.mBossNodeLabel);
	mSceneText.push_back(&mLegend.mInstructionText);
}

void OverworldMapScene::HideLegend()
{
	mLegendOn = false;
	mLegend.pLegendObj->SetVisible(false);
	mSceneText.clear();

	for (auto object : mLegend.mLegendObjects)
	{
		object->SetVisible(false);
	}
}

void OverworldMapScene::OnHover(RenderObject* rObj)
{
	rObj->tint = Lime;
}

void OverworldMapScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

bool OverworldMapScene::IsCombat()
{
	srand(time(NULL));
	int v = rand() % 10;
	return  v > 5;
}

std::pair<int, int> OverworldMapScene::ScaleEnemyStats()
{	
	int randomStat = 0;

	randomStat = (rand() % 8) + (2 * (mgr->GetPlayer()->GetParty()[0]->GetLevel()));

	return std::make_pair(randomStat, randomStat);
}

double OverworldMapScene::Uniform()
{
	return (double)rand() / RAND_MAX;
}




