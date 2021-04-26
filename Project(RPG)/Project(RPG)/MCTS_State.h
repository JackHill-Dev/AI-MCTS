#pragma once
#include "CombatScene.h"
#include "Character.h"
#include "MCTS_Action.h"
#include "Player.h"
#include "RenderObject.h"
#include "Card.h"

#include <cmath>
#include <vector>
#include <deque>

struct CombatScene::Unit;
struct CombatScene::tile;

typedef CombatScene::Unit Unit;
typedef CombatScene::tile Tile;

class MCTS_State
{
public:
	MCTS_State() = default;
	MCTS_State(CombatScene& cs);
	MCTS_State(MCTS_State* state);
	~MCTS_State();
	// Make sure this is called straight after the contructor for the state so data is consistent
	void GeneratePossibleActions();
	void SimulateEnemyTurn();
	void ResetInitialState();
	int GetUCB1Value() { return  (wins / timesVisited) +  sqrt(parentState->timesVisited / timesVisited); }
	bool Winner();
	bool operator==(MCTS_State& state)
	{
		return this == &state;
	}
	std::vector<MCTS_Action*> possibleActions;
	std::vector<MCTS_State*> nextStates;
	std::vector<MCTS_State> previousStates;
	MCTS_State* parentState = nullptr;
	// Data needed for states and actions
	Player player;
	std::deque<Unit> playerTeam;
	std::deque<Unit> enemyTeam;
	bool isLeafNode = false;
	int timesVisited = 0;
	int wins = 0;
	

private:
	void Move(Tile& targetTile);

	std::vector<Card> playerCards =
	{
		{7, "magicCard", 4, "MagicObj", "",0.75, 0, 5, 0},
		{10, "slashCard", 5, "slashObj", "",0.5, 5, 0, 0},
		{5, "arrowCard", 4, "arrowObj", "",0.75, 0, 0, 5}
	};

	std::vector<Card> enemyCards =
	{
		{7, "magicCard", 4, "MagicObj", "",0.75, 0, 5, 0},
		{10, "slashCard", 5, "slashObj", "",0.5, 5, 0, 0},
		{5, "arrowCard", 4, "arrowObj", "",0.75, 0, 0, 5}
	};



	Tile map[10][10];
	CombatScene* csDeepCopy;
	// mcts specific vars
	//int timesVisited = 0;
	//int wins = 0; // This is set to true in the back propogation part if the leaf node is a win
	
	//MCTS_EndTurn_Action endTurn;
};

