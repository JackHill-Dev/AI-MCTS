#pragma once
#include "CombatScene.h"


typedef CombatScene::Unit Unit;
typedef CombatScene::tile Tile;

class MCTS_Action
{
public:
	MCTS_Action() {}
	virtual void Execute() = 0;
};

class MCTS_Move_Action : public MCTS_Action
{
public:
	MCTS_Move_Action() {}
	MCTS_Move_Action(Unit* UnitToMove, Tile* targetTile);

	void Execute() override;
private:

	Unit* characterToMove;
	Tile* targetTile;
	//std::vector<Tile*> PathToMoveOn;
	
	//int amountToMoveBy;
};

class MCTS_EndTurn_Action : public MCTS_Action
{
public:
	MCTS_EndTurn_Action() {};
	void Execute() override;
};

class MCTS_Card_Action : public MCTS_Action
{
public:
	MCTS_Card_Action() = delete;
	MCTS_Card_Action(Unit* caster, Card* cardToCast, Unit* enemeyUnit);
	void Execute() override;
private:
	Card* cardToCast;
	Unit* player;
	Unit* enemyTarget;
};




