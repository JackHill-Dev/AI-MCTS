//void CombatScene::SwitchTurn()
//{
//	playerTurn = !playerTurn;
//	if (playerTurn)
//	{
//		for (auto i : team)
//		{
//			i.character->movement.first = i.character->movement.second;
//
//			//i.first->movement.first = i.first->movement.second;
//		}
//		LoadHand();
//	}
//	else
//		for (auto i : enemy)
//		{
//			i.character->movement.first = i.character->movement.second;
//			//i.first->movement.first = i.first->movement.second;
//		}
//}
//
//CombatScene* CombatScene::Load(std::vector<Character*> player, std::vector<Character*> anemy)
//{
//	int v = 0;
//	for (auto i : player)
//	{
//		Unit newUnit = Unit(*AddObject(i->GetObjName(), mapp.tiles[0][v].pos.first, mapp.tiles[0][v].pos.second, Game), i, mapp.tiles[0][v]);
//		team.push_back(newUnit);
//		v++;
//	}
//	v = 0;
//	for (auto i : anemy)
//	{
//		Unit newUnit = Unit(*AddObject(i->GetObjName(), mapp.tiles[14][v].pos.first, mapp.tiles[14][v].pos.second, Game), i, mapp.tiles[14][v]);
//		enemy.push_back(newUnit);
//		v++;
//	}
//	LoadHand();
//
//	return this;
//}
//bool InRange(tile* first, tile* second, int range)
//{
//	if (first->pos.first == second->pos.first || first->pos.first == second->pos.first - 32 || first->pos.first == second->pos.first + 32)
//		if (first->pos.second == second->pos.second || first->pos.second == second->pos.second - 32 || first->pos.second == second->pos.second + 32)
//			return true;
//	return false;
//}
//
//
//std::vector<tile*> CalculatePath(tile* first, tile* second)
//{
//	std::vector<tile*> path;
//
//	tile* currentTile = first;
//	while (currentTile != second)
//	{
//
//		if (second->pos.first > currentTile->pos.first)
//		{
//			currentTile = currentTile->right;
//			path.push_back(currentTile);
//		}
//		else
//			if (second->pos.first < currentTile->pos.first)
//			{
//				currentTile = currentTile->left;
//				path.push_back(currentTile);
//			}
//
//
//		if (second->pos.second > currentTile->pos.second)
//		{
//			currentTile = currentTile->up;
//			path.push_back(currentTile);
//		}
//		else
//			if (second->pos.second < currentTile->pos.second)
//			{
//				currentTile = currentTile->down;
//				path.push_back(currentTile);
//
//			}
//
//
//
//	}
//
//	return path;
//}
//
//void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
//{
//	bool busy = false;
//
//	if (team.size() <= 0 || enemy.size() <= 0)
//		mgr->LoadScene(0);
//
//
//	for (auto i : team)
//		if (i.busy)
//			i.Move(dTime);
//	for (auto i : enemy)
//		if (i.busy)
//			i.Move(dTime);
//
//
//	if (act == Act::Click && !busy && playerTurn)
//	{
//		if (endTurn->InBounds(mouse.first, mouse.second))
//		{
//			SwitchTurn();
//		}
//		else
//		{
//
//			if (current == Selection::Any)
//			{
//				if (selectedCard == nullptr)
//				{
//					int index = 0;
//					while (selectedCard == nullptr && index < playerHand.size())
//					{
//						if (playerHand[index]->getObj()->InBounds(mouse.first, mouse.second))
//						{
//							selectedCard = playerHand[index];
//							selectedCard->getObj()->tint = SDL_Color{ 255,255,0 };
//							current = Selection::Team;
//						}
//						index++;
//					}
//				}
//				if (selectedCard == nullptr && character == nullptr)
//				{
//					int index = 0;
//
//					while (character == nullptr && index < team.size())
//					{
//						if (team[index].object.InBounds(mouse.first, mouse.second))
//						{
//							character = &team[index];
//							team[index].object.tint = SDL_Color{ 255,255,0 };
//							current = Selection::Ground;
//						}
//						index++;
//					}
//				}
//
//			}
//
//			else if (current == Selection::Ground)
//			{
//
//
//
//				if (character != nullptr)
//					for (int i = 0; i < 15; ++i)
//						for (int p = 0; p < 15; ++p)
//							if (mapp.tiles[i][p].availiable && mapp.tiles[i][p].square->InBounds(mouse.first, mouse.second))
//							{
//
//								character->occupiedTile.availiable = true;
//								character->occupiedTile = mapp.tiles[i][p];
//								character->occupiedTile.availiable = false;
//								character->busy = true;
//
//
//							}
//				if (character != nullptr)
//					character->object.Untint();
//				character = nullptr;
//
//				current = Selection::Any;
//
//
//			}
//			else if (current == Selection::Team)
//			{
//				if (character == nullptr)
//				{
//					int index = 0;
//
//					while (character == nullptr && index < team.size())
//					{
//						if (team[index].object.InBounds(mouse.first, mouse.second))
//						{
//							character = &team[index];
//							team[index].object.tint = SDL_Color{ 255,255,0 };
//							current = Selection::Enemy;
//						}
//						index++;
//					}
//					if (character == nullptr)
//					{
//						if (selectedCard != nullptr)
//						{
//							current = Selection::Any;
//							selectedCard->getObj()->Untint();
//							selectedCard = nullptr;
//
//						}
//
//					}
//				}
//			}
//			else if (current == Selection::Enemy)
//			{
//				target = nullptr;
//				int index = 0;
//				while (index < enemy.size() && target == nullptr)
//				{
//
//					if (enemy[index].object.InBounds(mouse.first, mouse.second))
//					{
//						target = &enemy[index];
//					}
//
//					index++;
//				}
//
//
//				selectedCard->getObj()->Untint();
//				character->object.Untint();
//
//				if (target != nullptr)
//				{
//					Cast(selectedCard);
//
//					selectedCard = nullptr;
//				}
//				character->object.Untint();
//				character = nullptr;
//
//				if (selectedCard != nullptr)
//				{
//					selectedCard->getObj()->Untint();
//					selectedCard = nullptr;
//				}
//
//
//
//				current = Selection::Any;
//
//			}
//		}
//
//
//
//
//
//	}
//	else if (act == Act::MouseUpdate)
//	{
//		if (hovered != nullptr)
//		{
//			if ((character == nullptr || hovered != &character->object) && (selectedCard == nullptr || hovered != selectedCard->getObj()))
//				hovered->Untint();
//			hovered = nullptr;
//		}
//		if (current == Selection::Any)
//		{
//			int index = 0;
//			while (hovered == nullptr && index < playerHand.size())
//			{
//				if (playerHand[index]->getObj()->InBounds(mouse.first, mouse.second))
//				{
//					hovered = playerHand[index]->getObj();
//					hovered->tint = SDL_Color{ 0,255,0 };
//
//				}
//				++index;
//			}
//
//			if (hovered == nullptr)
//			{
//				index = 0;
//				while (hovered == nullptr && index < team.size())
//				{
//					if (team[index].object.InBounds(mouse.first, mouse.second))
//					{
//						hovered = &team[index].object;
//						hovered->tint = SDL_Color{ 0,255,0 };
//					}
//					index++;
//				}
//			}
//
//
//		}
//		else if (current == Selection::Team)
//		{
//
//
//
//			int index = 0;
//			while (hovered == nullptr && index < team.size())
//			{
//				if (team[index].object.InBounds(mouse.first, mouse.second))
//				{
//					hovered = &team[index].object;
//					hovered->tint = SDL_Color{ 0,255,0 };
//				}
//				index++;
//			}
//
//		}
//		else if (current == Selection::Ground)
//		{
//
//			for (int i = 0; i < 15; i++)
//			{
//				int t = 0;
//				while (t < 15 && hovered == nullptr)
//				{
//					if (mapp.tiles[i][t].square->InBounds(mouse.first, mouse.second))
//					{
//						hovered = mapp.tiles[i][t].square;
//						if (mapp.tiles[i][t].availiable)
//							hovered->tint = SDL_Color{ 0,255,0 };
//						else
//							hovered->tint = SDL_Color{ 255,0,0 };
//					}
//					t++;
//				}
//			}
//		}
//		else if (current == Selection::Enemy)
//		{
//
//
//
//			int index = 0;
//			while (hovered == nullptr && index < team.size())
//			{
//				if (enemy[index].object.InBounds(mouse.first, mouse.second))
//				{
//
//
//
//					hovered = &enemy[index].object;
//
//					if (selectedCard != nullptr && InRange(&character->occupiedTile, &enemy[index].occupiedTile, 1))
//					{
//
//						hovered->tint = SDL_Color{ 0,255,0 };
//
//					}
//					else
//						hovered->tint = SDL_Color{ 255,0,0 };
//				}
//				index++;
//			}
//
//		}
//	}
//
//
//	if (!playerTurn && !busy)
//	{
//		bool validLeft = false;
//		for (auto i : enemy)
//			if (i.character->movement.first > 0)
//				validLeft = true;
//
//
//		if (validLeft)
//		{
//			for (int i = 0; i < enemy.size(); i++)
//			{
//				if (enemy[i].character->movement.first > 0)
//				{
//					enemy[i].occupiedTile.availiable = true;
//
//					std::vector<tile*> path = CalculatePath(&enemy[i].occupiedTile, &team[0].occupiedTile);
//
//					if (path.size() > enemy[i].character->movement.first)
//					{
//						enemy[i].occupiedTile = *path[enemy[i].character->movement.first - 1];
//						enemy[i].character->movement.first -= enemy[i].character->movement.first;
//					}
//					else
//					{
//						enemy[i].occupiedTile = *path.back();
//						enemy[i].character->movement.first = 0;
//					}
//
//
//
//					enemy[i].occupiedTile.availiable = false;
//					enemy[i].busy = true;
//				}
//
//			}
//		}
//		else
//			SwitchTurn();
//
//
//
//	}
//
//}
//
//void CombatScene::Cast(Card* card)
//{
//	if (card != nullptr && character != nullptr && target != nullptr && CalculatePath(&character->occupiedTile, &target->occupiedTile).size() <= 1)
//	{
//
//		card->Cast(character->character, target->character);
//
//		if (target->character->GetHealth() <= 0)
//		{
//			DeleteCharacter(target);
//
//
//		}
//
//		target = nullptr;
//		selectedCard = nullptr;
//
//
//
//
//
//
//
//		mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), card->getObj()));
//
//		delete (card->getObj());
//
//		playerHand.erase(std::find(playerHand.begin(), playerHand.end(), card));
//
//	}
//	//card->getObj() = nullptr;
//}
