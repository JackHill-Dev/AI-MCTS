#include "MCTS_State.h"
#include <random>
#include <chrono>

std::mt19937 random_number_engine_mcts_state(time(0));

int RandomRange(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine_mcts_state);
}

MCTS_State::MCTS_State(CombatScene& cs)
{
	csDeepCopy = cs.Clone();
	playerTeam = csDeepCopy->GetPlayerTeam();

	for (auto& p : playerTeam)
	{
		for (int x = 0; x < 10; ++x)
			for (int y = 0; y < 10; ++y)
				if (p.occupiedTile->pos == csDeepCopy->mapp[x][y].pos)
				{
					p.occupiedTile = &csDeepCopy->mapp[x][y];
					p.character = csDeepCopy->GetPlayerTeam()[0].character;
				}
	}

	for (auto& e : enemyTeam)
	{
		e.character = csDeepCopy->GetEnemyTeam()[0].character;
	}

	enemyTeam = csDeepCopy->GetEnemyTeam();
	enemyTeam[0].character->GetStats().health.first = 25;
	enemyTeam[0].character->GetStats().health.second = 25;
	//playerCards = csDeepCopy->GetPlayerHand();
	//player = p;
	//map = cs.mapp;

}

MCTS_State::MCTS_State(MCTS_State* state)
{
	//action.Execute(*csDeepCopy);
	csDeepCopy = state->csDeepCopy;
	playerTeam = state->playerTeam;
	enemyTeam = state->enemyTeam;
	playerCards = state->playerCards;
}

MCTS_State::~MCTS_State()
{
	for (auto action : possibleActions)
	{
		delete action;
		action = nullptr;
	}

	for (auto* state : nextStates)
	{
		delete state;
		state = nullptr;
	}
	// delete csDeepCopy
}

void MCTS_State::GeneratePossibleActions()
{

	// loop through current state's party/units
	for (auto& a : playerTeam)
	{
		// loop through current cards
		for (auto& c : playerCards)
		{
			// check if ally unit is within range to use the card and unit has enough resources to use the action
			for (auto& e : enemyTeam)
				if (!csDeepCopy->OutOfRange(&a, &e, c))
				{
					// Then add this as a possible action
					MCTS_Card_Action* cardAction = new MCTS_Card_Action(&a,&c, &e);
					possibleActions.push_back(cardAction);
				}
		}


		// Find all tiles within range of player
		for (int x = 0; x < 10; ++x)
			for (int y = 0; y < 10; ++y)
			{
				int dist = csDeepCopy->GetDistance(a.occupiedTile, &csDeepCopy->mapp[x][y]);
				if (csDeepCopy->GetDistance(a.occupiedTile, &csDeepCopy->mapp[x][y]) < a.character->GetStats().movement.first && &csDeepCopy->mapp[x][y].availiable)
				{

					MCTS_Move_Action* moveAction = new MCTS_Move_Action(&a, &csDeepCopy->mapp[x][y]);
					possibleActions.push_back(moveAction);
				}
			}

	}
	
	// There will always be the option of ending the turn so add it to the possible actions
	//MCTS_EndTurn_Action endTurn;
//	possibleActions.push_back(&endTurn);

}

void MCTS_State::SimulateEnemyTurn()
{
	// Temp vector of possible tiles for enemy to move to
	std::vector<Tile*> tiles;

	for (int x = 0; x < 10; ++x)
		for (int y = 0; y < 10; ++y)
		{
			if(csDeepCopy->GetDistance(enemyTeam[0].occupiedTile, &csDeepCopy->mapp[x][y]) < enemyTeam[0].character->GetStats().movement.first&&& csDeepCopy->mapp[x][y].availiable)
			{
				tiles.push_back(&csDeepCopy->mapp[x][y]);
			}
		}

	// Move the enemy in the state
	enemyTeam[0].occupiedTile->availiable = true;
	enemyTeam[0].occupiedTile = tiles[RandomRange(0, tiles.size() - 1)];
	enemyTeam[0].occupiedTile->availiable = true;
	// Check to see if enemy can damage player
	if (!csDeepCopy->OutOfRange(&enemyTeam[0], &playerTeam[0], enemyCards[0]) && enemyTeam[0].character->GetStats().health.first > 0)
	{
		std::cout << "Enemy card attack" << std::endl;
		// if it can, cast card and deal damge
		std::cout << playerTeam[0].character->GetStats().health.first << std::endl;
		enemyCards[0].Cast(enemyTeam[0].character, playerTeam[0].character);
		std::cout << playerTeam[0].character->GetStats().health.first << std::endl;
	}
	
	
}

void MCTS_State::ResetInitialState()
{
	playerTeam[0].character->GetStats().health.first = 15;
	playerTeam[0].occupiedTile = &csDeepCopy->mapp[0][9];

	enemyTeam[0].occupiedTile = &csDeepCopy->mapp[9][0];
	enemyTeam[0].character->GetStats().health.first = 25;
}

bool MCTS_State::Winner()
{
	if (playerTeam[0].character->GetStats().health.first <= 0)
	{
		isLeafNode = true;
		return true;
	}
	if (enemyTeam[0].character->GetStats().health.first <= 0)
	{
		++wins;
		isLeafNode = true;
		return true;
	}

	return false;
}

void MCTS_State::Move(Tile& targetTile)
{
	playerTeam[0].occupiedTile = &targetTile;
}
