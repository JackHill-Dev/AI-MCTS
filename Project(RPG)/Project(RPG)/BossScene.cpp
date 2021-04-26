#include "BossScene.h"
#include <deque>

BossScene::BossScene(Interface* objmg) : Scene(objmg)
{
	pCombat_music = Mix_LoadMUS("Assets/Music/Boss.mp3");

	pSlash_sfx = Mix_LoadWAV("Assets/SFX/slash.wav");
	pMagic_SFX = Mix_LoadWAV("Assets/SFX/zapsplat_magic_impact_hard_.wav");
	pHeal_SFX = Mix_LoadWAV("Assets/SFX/Healchoir.wav");
	pShoot_SFX = Mix_LoadWAV("Assets/SFX/fork_media_warfare_arrow_pass_by.wav");
	pButtonClick_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	pError_SFX = Mix_LoadWAV("Assets/SFX/ErrorSound.wav");
}

BossScene::~BossScene()
{
	for (auto& obj : hovered)
	{
		obj = nullptr;
	}

	endTurn = nullptr;
	pExit = nullptr;

	character = nullptr;
	target = nullptr;

	if (this->selectedCard != nullptr)
	{
		selectedCard->first = nullptr;
		selectedCard->second = nullptr;
		selectedCard = nullptr;
	}


	for (auto& hand : playerhand)
	{
		hand.first = nullptr;
		hand.second = nullptr;
	}
	for (auto& hand : enemyHand)
	{
		hand.first = nullptr;
		hand.second = nullptr;
	}

	pCombat_music = nullptr;
	pSlash_sfx = nullptr;
	pMagic_SFX = nullptr;
	pHeal_SFX = nullptr;
	pShoot_SFX = nullptr;
	pButtonClick_SFX = nullptr;
	pError_SFX = nullptr;

	hoveredCard.first = nullptr;
	hoveredCard.second = nullptr;
}

void BossScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{

	if (fightScene <= 0)
	{

		for (auto& c : team)
		{
			c.visualStats.SetVisibility(true);
			c.object->SetVisible(true);
		}
		for (auto& c : enemy)
		{
			c.visualStats.SetVisibility(true);
			c.object->SetVisible(true);
		}


		for (auto e : mLayers[Effects])
		{
			delete(e);
		}
		mLayers[Effects].clear();

		// Win Condition
		if (enemy.size() <= 0)
		{
			for (auto i : team)
				RemoveUnit(&i);

			for (auto i : enemy)
				RemoveUnit(&i);

			// Flips a bool in player to display the 'Game Cleared' state. Woo! - EH
			mgr->GetPlayer()->GameCleared();
			mgr->LoadScene(Scenes::WinLoseStateScreen);
		}


		for (auto i : team)
		{
			if (i.character->GetHealth() <= 0)
			{
				i.character->Die();
				RemoveUnit(&i);

				// Lose Condition - EH
				if (team.size() <= 0)
				{
					for (auto i : enemy)
						RemoveUnit(&i);

					for (auto i : team)
						RemoveUnit(&i);
					mgr->LoadScene(Scenes::WinLoseStateScreen);
				}
			}
			else
			{
				i.Update();
			}
		}

		for (auto i : enemy)
		{
			if (i.character->GetHealth() <= 0)
			{
				RemoveUnit(&i);
			}
			else
			{
				i.Update();
			}
		}

		bool scenebusy = false;
		if (playerTurn)
		{
			for (auto& i : team)
				if (i.busy)
				{
					i.Move(dTime);
					scenebusy = true;
				}
			if (!scenebusy)
			{
				if (act == Act::Click)
				{
					if (!hovered.empty())
					{
						for (auto& i : hovered)
						{
							if (character != nullptr && character->object != nullptr && character->object == i)
							{

							}
							else
								if (selectedCard != nullptr && selectedCard->second != nullptr && selectedCard->second == i)
								{

								}
								else
									i->Untint();
						}
					}
					hovered.clear();

					if (endTurn->InBounds(mouse.first, mouse.second))
					{
						mgr->PlaySFX(pButtonClick_SFX, 0, 1);
						endTurn->Untint();

						for (int i = 0; i < playerhand.size(); ++i)
						{
							mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), playerhand[i].second));

						}
						playerhand.clear();
						playerTurn = false;
						for (auto& i : enemy)
						{
							i.character->GetStats().movement.first = i.character->GetStats().movement.second;
							i.character->GetStats().strength.first = i.character->GetStats().strength.second;

						}
						for (int i = 0; i < 5; i++)
						{
							enemyHand.push_back(std::make_pair(new Card(10, "BossAttack", 1.5, "cardObj", "BossAttackObj", 1, 5, 0, 0), nullptr));
						}
					}
					else
						if (current == Selection::Any)
						{
							bool found = false;


							for (auto& i : playerhand)
								if (i.second->InBounds(mouse.first, mouse.second))
								{
									mgr->PlaySFX(pButtonClick_SFX, 0, 1);
									selectedCard = &i;
									found = true;
									i.second->tint = SDL_Color{ 255,255,0 };
									hovered.push_back(i.second);

									current = Selection::Team;
								}

							if (!found)
								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										mgr->PlaySFX(pButtonClick_SFX, 0, 1);
										character = &i;
										character->object->tint = SDL_Color{ 255,255,0 };
										character->profile->tint = SDL_Color{ 255,255,0 };
										if (selectedCard != nullptr)
											current = Selection::Enemy;
										current = Selection::Ground;
									}
						}
						else
						{
							switch (current)
							{
							case(Selection::Ground):

								for (int i = 0; i < gridTileLength; i++)
									for (int x = 0; x < gridTileLength; x++)
										if (mapp[i][x].square->InBounds(mouse.first, mouse.second) && &mapp[i][x] != character->occupiedTile)
										{
											auto path = CalculatePath(character->occupiedTile, &mapp[i][x]);
											int distance = path.size();
											if (distance <= character->character->GetStats().movement.first)
											{
												character->SetTarget(path);

												character->character->GetStats().movement.first -= distance;
											}
										}
								character->object->Untint();
								character->profile->Untint();
								character = nullptr;
								mgr->PlaySFX(pButtonClick_SFX, 0, 1);
								current = Selection::Any;

								break;
							case(Selection::Team):
								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										mgr->PlaySFX(pButtonClick_SFX, 0, 1);

										if ((i.character->GetStats().strength.first >= selectedCard->first->Values().stamCost)
											&& (i.character->GetStats().agility.first >= selectedCard->first->Values().agilCost)
											&& (i.character->GetStats().intelligence.first >= selectedCard->first->Values().intCost))
										{
											character = &i;
											character->object->tint = SDL_Color{ 255,255,0 };
											character->profile->tint = SDL_Color{ 255,255,0 };
											current = Selection::Enemy;
										}

									}
								if (character == nullptr)
								{
									mgr->PlaySFX(pError_SFX, 0, 1);
									selectedCard->second->Untint();
									selectedCard = nullptr;
									current = Selection::Any;
								}
								break;
							case(Selection::Enemy):

								if (selectedCard->first->Values().damage < 0)
								{

									for (auto& i : team)
									{
										if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second) && &i != character)
										{
											target = &i;
										}
									}
								}

								else
								{
									for (auto& i : enemy)
									{
										if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
										{
											target = &i;
										}
									}
								}

								if (target == nullptr)
								{
									mgr->PlaySFX(pError_SFX, 0, 1);
									character->object->Untint();
									character->profile->Untint();
									character = nullptr;
									selectedCard->second->Untint();
									selectedCard = nullptr;
									current = Selection::Any;
								}
								else
								{
									Cast(character, target, selectedCard);
									target = nullptr;
									character = nullptr;
									selectedCard = nullptr;
									current = Selection::Any;
								}
								break;
							}

						}
				}
				else
					if (act == Act::MouseUpdate)
					{
						if (endTurn->InBounds(mouse.first, mouse.second))
						{
							endTurn->Tint({ 0,255,0 });
						}
						else
						{
							endTurn->Untint();
						}

						if (hoveredCard.first != nullptr)
						{
							hoveredCard.second->scale = std::make_pair(0.42f, 0.42f);
							hoveredCard.second->SetPos({ hoveredCard.second->GetPos().first, 650 });

							hoveredCard.first = nullptr;
							hoveredCard.second = nullptr;

							for (int i = 0; i < playerhand.size(); ++i)
							{
								float x = 100 * (i - ((float)playerhand.size() / 2 - 0.5f));

								float xpos = centre.first + x;
								playerhand[i].second->SetPos(std::make_pair(xpos, 650));
							}

						}
						if (!hovered.empty())
						{
							for (auto& i : hovered)
							{
								if (character != nullptr && character->object != nullptr && character->object == i)
								{

								}
								else
									if (selectedCard != nullptr && selectedCard->second != nullptr && selectedCard->second == i)
									{

									}
									else
										if (hoveredCard.first != nullptr && hoveredCard.second != nullptr && selectedCard->second == i)
										{

										}
										else
											i->Untint();
							}
						}
						hovered.clear();
						if (current == Selection::Any)
						{
							bool found = false;

							for (auto& i : playerhand)
								if (i.second->InBounds(mouse.first, mouse.second))
								{
									if (hoveredCard.first != nullptr)
									{
										hoveredCard.second->scale = std::make_pair(0.42f, 0.42f);
										hoveredCard.second->SetPos({ hoveredCard.second->GetPos().first, 650 });
										hoveredCard.first = nullptr;
										hoveredCard.second = nullptr;

									}
									found = true;
									
									hovered.push_back(i.second);
									hoveredCard = i;

									int offset = -60;

									for (int c = 0; c < playerhand.size(); ++c)
									{
										float x = 100 * (c - ((float)playerhand.size() / 2 - 0.5f));

										float xpos = centre.first + x;
										if (playerhand[c] == i)
										{
											offset = 60;
											i.second->scale = { 1,1 };
											i.second->SetPos(std::make_pair(xpos, 550));
										}
										else
											playerhand[c].second->SetPos(std::make_pair(xpos + offset, 650));

									}

								}

							if (!found)
							{
								for (auto& i : team)
								{
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										found = true;
										i.object->tint = SDL_Color{ 0,255,0 };
										i.profile->tint = SDL_Color{ 0, 255, 0 };

										hovered.push_back(i.object);
										hovered.push_back(i.profile);
									}
								}

								for (auto& i : enemy)
								{
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										found = true;
										i.object->tint = SDL_Color{ 255, 0, 0 };
										i.profile->tint = SDL_Color{ 255, 0, 0 };

										hovered.push_back(i.object);
										hovered.push_back(i.profile);
									}
								}
							}
						}
						else
							switch (current)
							{
							case(Selection::Team):

								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{

										if (i.character->GetStats().strength.first > 5)
										{

											i.object->tint = SDL_Color{ 0, 255, 0 };
											i.profile->tint = SDL_Color{ 0,255,0 };
										}
										else
										{
											i.object->tint = SDL_Color{ 255, 0, 0 };
											i.profile->tint = SDL_Color{ 255, 0, 0 };
										}

										hovered.push_back(i.object);
										hovered.push_back(i.profile);
									}

								break;
							case(Selection::Enemy):

								for (auto& i : enemy)
									if (i.object->InBounds(mouse.first, mouse.second))
									{
										if (OutOfRange(character, &i, selectedCard) == true)
										{
											i.object->tint = SDL_Color{ 105,105,105 };
											i.profile->tint = SDL_Color{ 105,105,105 };
										}
										else
										{
											i.object->tint = SDL_Color{ 0, 255, 0 };
											i.profile->tint = SDL_Color{ 0, 255, 0 };
										}

										hovered.push_back(i.object);
										hovered.push_back(i.profile);

									}

								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) && &i != character)
									{
										if (OutOfRange(character, &i, selectedCard) == true)
										{
											i.object->tint = SDL_Color{ 105,105,105 };
											i.profile->tint = SDL_Color{ 105,105,105 };
										}
										else
										{
											i.object->tint = SDL_Color{ 0, 255, 0 };
											i.profile->tint = SDL_Color{ 0, 255, 0 };
										}

										hovered.push_back(i.profile);
										hovered.push_back(i.object);

									}

								break;
							case(Selection::Ground):
								bool found = false;
								for (int i = 0; i < gridTileLength; i++)
									for (int t = 0; t < gridTileLength; t++)
										if (!found && mapp[i][t].square->InBounds(mouse.first, mouse.second))
										{
											auto path = CalculatePath(character->occupiedTile, &mapp[i][t]);
											int distance = path.size();

											found = true;

											for (int x = 0; x < path.size(); x++)
											{
												if (path[x] != character->occupiedTile && path[x]->availiable && x < character->character->GetStats().movement.first)
													path[x]->square->tint = SDL_Color{ 0,255,0 };
												else
													path[x]->square->tint = SDL_Color{ 255,0,0 };

												hovered.push_back(path[x]->square);
											}
										}
								break;
							}
					}
			}
		}
		else
		{
			for (auto& i : enemy)
				if (i.busy)
				{
					i.Move(dTime);
					scenebusy = true;
				}
			if (!scenebusy)
			{
				RunAi();
			}

		}
	}
	else
		fightScene -= (dTime / 1000);
}

void BossScene::Load()
{
	for (int i = 0; i < 10; i++)
	{
		for (int t = 0; t < 10; t++)
			mapp[i][t].availiable = true;
	}
	for (auto t : mSceneText)
		delete t;
	mSceneText.clear();
	playerTurn = false;
	int v = 0;

	enemyHand.clear();
	playerhand.clear();

	enemy.clear(); team.clear();
	for (auto& layer : mLayers)
	{
		for (auto obj : layer)
			delete obj;
		layer.clear();
	}

	mgr->FadeInMusic(pCombat_music, -1, mgr->fadeTime);

	endTurn = AddObject("EndTurnButtonObj", centre.first, 40, UI);
	endTurn->scale = std::make_pair(1, 1);
	AddObject("castleBackgroundObj", 640, 360, Background);

	for (double i = 0; i < gridTileLength; i++)
	{
		for (double x = 0; x < gridTileLength; x++)
		{

			mapp[(int)i][(int)x].square = (AddObject("stoneTileObj", (i - 4.5) * 32 + centre.first, x * 32 - 5 * 32 + centre.second - 32, Background));
			mapp[(int)i][(int)x].pos = std::make_pair((i - 4.5) * 32 + centre.first, x * 32 - 5 * 32 + centre.second - 32);


		}
	}
	for (int i = 0; i < gridTileLength; i++)
	{
		for (int x = 0; x < gridTileLength; x++)
		{

			if (x > 0)
			{
				mapp[i][x].down = (&mapp[i][x - 1]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].down);
			}
			if (x < gridTileLength - 1)
			{
				mapp[i][x].up = (&mapp[i][x + 1]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].up);
			}
			if (i > 0)
			{
				mapp[i][x].left = (&mapp[i - 1][x]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].left);
			}
			if (i < gridTileLength - 1)
			{
				mapp[i][x].right = (&mapp[i + 1][x]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].right);
			}

		}
	}

	for (auto i : mgr->GetPlayer()->GetParty())
	{
	
		UIText* health = new UIText();
		UIText* movement = new UIText();
		UIText* str = new UIText();
		UIText* intel = new UIText();
		UIText* agil = new UIText();

		mSceneText.push_back(health);
		mSceneText.push_back(movement);
		mSceneText.push_back(str);
		mSceneText.push_back(intel);
		mSceneText.push_back(agil);
		Unit unit = Unit(i, &mapp[v][9], AddObject(i->GetObjName(), 0, 0, Game), AddObject(i->GetPortraitName(), 250, 125 + 150 * v, UI), UIStats(std::make_pair(250, 125 + 150 * v + 75), health, movement, str, intel, agil,AddObject("statBackgroundObj", 250, 125 + 150 * v, UI)));
		
		unit.profile->scale = std::make_pair(0.6f, 0.47f);
		team.push_back(unit);
		v++;
	}
	v = 0;

	UIText* health = new UIText();
	UIText* movement = new UIText();
	UIText* str = new UIText();
	UIText* intel = new UIText();
	UIText* agil = new UIText();

	mSceneText.push_back(health);
	mSceneText.push_back(movement);
	mSceneText.push_back(str);
	mSceneText.push_back(intel);
	mSceneText.push_back(agil);

	Unit boss = Unit(new Character("", "", "", UnitClass::NoClass, 0, std::make_pair(1000, 3000), false, std::make_pair(60,60), std::make_pair(25,25), std::make_pair(25,25), std::make_pair(25,25)), &mapp[4][3], AddObject("daemonBoss", 500, 500, Game), AddObject("bossPortraitObj", 1000, 250, Game), UIStats(std::make_pair(1000, 250 + 75), health, movement, str, intel, agil,AddObject("statBackgroundObj", 250, 125 + 150 * v, UI)));
	
	boss.profile->scale = std::make_pair(0.3f, 0.3f);
	boss.object->scale = { 2,2 };
	enemy.push_back(boss);
	for (int i = 0; i < 5; i++)
	{
		enemyHand.push_back(std::make_pair(new Card(10, "BossAttack", 1.5, "cardObj", "BossAttackObj", 1, 5, 0, 0), nullptr));

	}

}

void BossScene::Cast(Unit* caster, Unit* target, const std::pair<Card*, RenderObject*>* card)
{
	auto d = card->first->GetEffect();
	auto stats = &caster->character->GetStats();
	auto dist = GetDistance(caster->occupiedTile, target->occupiedTile);
	target->object->Untint();
	target->profile->Untint();
	caster->object->Untint();
	caster->profile->Untint();

	if (dist <= card->first->Values().range + 1 &&
		stats->strength.first >= card->first->Values().stamCost)
	{
		if (card->first->GetCardName().find("Slash") != std::string::npos)
		{
			mgr->PlaySFX(pSlash_sfx, 0, 1);
		}

		else if (card->first->GetCardName().find("Magic") != std::string::npos)
		{
			mgr->PlaySFX(pMagic_SFX, 0, 1);
		}

		else if (card->first->GetCardName().find("Shoot") != std::string::npos)
		{
			mgr->PlaySFX(pShoot_SFX, 0, 1);
		}

		else if (card->first->GetCardName().find("Heal") != std::string::npos)
		{
			mgr->PlaySFX(pHeal_SFX, 0, 1);
		}

		else
		{
			mgr->PlaySFX(pSlash_sfx, 0, 1);
		}

		card->first->Cast(caster->character, target->character);
		caster->character->GetStats().strength.first -= card->first->Values().stamCost;
		caster->character->GetStats().intelligence.first -= card->first->Values().intCost;
		caster->character->GetStats().agility.first -= card->first->Values().agilCost;

		AddObject(card->first->GetEffect().first, centre.first, centre.second, Effects);
		fightScene = card->first->GetEffect().second;

		for (auto& c : team)
		{
			c.visualStats.SetVisibility(false);
		}
		for (auto& c : enemy)
		{
			c.visualStats.SetVisibility(false);
		}

		if (playerTurn)
		{

			for (int i = 0; i < playerhand.size(); ++i)
			{
				if (playerhand[i].second == card->second)
				{
					mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), card->second));
					playerhand[i].first = nullptr;
					playerhand.erase(playerhand.begin() + i);
				}
			}

			for (int i = 0; i < playerhand.size(); ++i)
			{
				float x = 100 * (i - ((float)playerhand.size() / 2 - 0.5f));

				float xpos = centre.first + x;
				playerhand[i].second->SetPos(std::make_pair(xpos, 650));
			}
		}
		else
		{
			for (int i = 0; i < enemyHand.size(); ++i)
			{
				if (enemyHand[i].first == card->first)
				{

					enemyHand[i].first = nullptr;
					enemyHand.erase(enemyHand.begin() + i);
				}
			}
		}

	}
}

void BossScene::RemoveUnit(Unit* unit)
{
	unit->visualStats.SetVisibility(false);
	unit->visualStats.object->SetVisible(false);
	unit->profile->SetVisible(false);
	auto p = std::find(mLayers[Game].begin(), mLayers[Game].end(), unit->object);
	mLayers[Game].erase(p);
	delete unit->object;
	unit->occupiedTile->availiable = true;
	auto i = std::find_if(team.begin(), team.end(), [unit](Unit u) {
		return (u.character == unit->character);
		});
	if (i != team.end())
	{
		team.erase(i);
	}
	else
	{
		i = std::find_if(enemy.begin(), enemy.end(), [unit](Unit u) {
			return (u.character == unit->character);
			});
		if (i == enemy.end())
			std::cout << "Error, enemy not found error 01";
		enemy.erase(i);
	}
}

void BossScene::RunAi()
{

	bool validAction = false;
	for (auto& i : enemy)
	{
		auto stats = &i.character->GetStats();
		if (!validAction)
		{
			std::deque<std::pair<Card*, RenderObject*>> validCards;

			for (auto& c : enemyHand)
			{
				if (stats->strength.first >= c.first->Values().stamCost && stats->intelligence.first >= c.first->Values().intCost && stats->agility.first >= c.first->Values().agilCost)
					validCards.push_back(c);
			}

			if (!validCards.empty())
			{
				for (auto e : team)
				{
					if (!validAction)
						for (auto c : validCards)
						{
							if (GetDistance(i.occupiedTile, e.occupiedTile) <= c.first->Values().range && !validAction)
							{
								validAction = true;
								Cast(&i, &e, &c);
							}
						}

					
				}
			}

			if (!validAction)
			{
				int dist = 0;
				Unit* target = nullptr;
				if (!validCards.empty())
				{
					for (auto& e : team)
					{
						int distToTarget = GetDistance(i.occupiedTile, e.occupiedTile);
						if (target == nullptr || distToTarget < dist)
						{
							dist = distToTarget;
							target = &e;
						}
					}

					if (target != nullptr)
					{
						auto path = CalculatePath(i.occupiedTile, target->occupiedTile);
						while (path.size() > stats->movement.first)
						{
							path.pop_back();
						}
						if (!path.empty())
						{
							stats->movement.first -= path.size();
							i.SetTarget(path);
							validAction = true;
						}
					}
				}
			}
		}
	}

	if (!validAction)
	{
		for (int i = 0; i < enemyHand.size(); ++i)
		{
			delete enemyHand[i].first;

		}

		enemyHand.clear();
		for (int i = 0; i < playerhand.size(); ++i)
		{
			mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), playerhand[i].second));

		}

		playerhand.clear();
		std::vector<Card*> temp;
		std::sample(mgr->GetPlayer()->deck.begin(), mgr->GetPlayer()->deck.end(), std::back_inserter(temp), 5, std::mt19937{ std::random_device{}() });

		for (int i = 0; i < temp.size(); ++i)
		{
			float x = 100 * (i - 2.0);

			float xpos = centre.first + x;
			playerhand.push_back(std::make_pair(temp[i], AddObject(temp[i]->GetObjName(), xpos, 650, UI)));
			playerhand.back().second->scale = std::make_pair(0.42f, 0.42f);
		}

		for (auto i : team)
		{
			i.character->GetStats().strength.first = i.character->GetStats().strength.second;
			i.character->GetStats().intelligence.first = i.character->GetStats().intelligence.second;
			i.character->GetStats().agility.first = i.character->GetStats().agility.second;
			i.character->GetStats().movement.first = i.character->GetStats().movement.second;
		}
		playerTurn = true;
	}
}

std::vector<BossScene::tile*> BossScene::CalculatePath(tile* start, tile* end)
{
	struct pathNode
	{
		pathNode(tile* node) : node(node)
		{

		}
		tile* node;
		int hcost = 1000;
		int gcost = 1000;
		int fcost = 1000;
		pathNode* prev = nullptr;
	};

	std::vector<pathNode*> map;

	for (int i = 0; i < gridTileLength; i++)
		for (int t = 0; t < gridTileLength; t++)
			map.push_back(new pathNode(&mapp[i][t]));

	std::vector<pathNode*> open;
	std::vector<pathNode*> closed;

	pathNode* current = *std::find_if(map.begin(), map.end(), [start](pathNode* node)
		{
			return node->node == start;
		});
	current->fcost = 0;
	current->hcost = 0;
	current->gcost = 0;
	open.push_back(current);
	while (!open.empty() && !(current->node == end))
	{
		open.erase(std::find(open.begin(), open.end(), current));
		closed.push_back(current);

		for (auto& i : current->node->adjacentTiles)
		{
			auto it = std::find_if(closed.begin(), closed.end(), [i](pathNode* nod) {return i == nod->node; });
			if (it == closed.end() && (i->availiable || i == end))
			{
				it = std::find_if(open.begin(), open.end(), [i](pathNode* nod) {return i == nod->node; });
				if (it == open.end())
				{
					auto p = std::find_if(map.begin(), map.end(), [i](pathNode* nod) {return i == nod->node; });
					if (p == map.end())
						std::cerr << "tile not found";
					open.push_back(*p);
					it = open.end() - 1;
				}
				auto node = open[it - open.begin()];
				node->prev = current;
				node->gcost = 10 + current->gcost;
				node->hcost = GetDistance(node->node, end);
				node->fcost = node->gcost + node->hcost;
			}
		}
		int currentValue = INT_MAX;
		for (auto& i : open)
		{
			if (i->fcost < currentValue)
			{
				current = i;
				currentValue = current->fcost;
			}
		}
	}

	std::vector<tile*> path;
	path.push_back(current->node);
	while (current->prev != nullptr)
	{
		path.push_back(current->prev->node);
		current = current->prev;
	}
	std::reverse(path.begin(), path.end());
	if (!end->availiable)
		path.erase(path.end() - 1);

	return path;
}

bool BossScene::OutOfRange(Unit* caster, Unit* target, const std::pair<Card*, RenderObject*>* card)
{
	double offset = - 1.0; // Boss is a large unit so he occupies more space than a tile.
	auto dist = GetDistance(caster->occupiedTile, target->occupiedTile) + offset;

	if (dist > card->first->Values().range)
	{
		return true;
	}
	else
	{
		return false;
	}
}







