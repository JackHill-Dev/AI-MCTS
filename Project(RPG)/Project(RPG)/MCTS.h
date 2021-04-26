#pragma once
#include <vector>
#include <random>
#include <chrono>

#include "MCTS_State.h"



class MCTS
{
public:
	MCTS() {}
	MCTS(MCTS_State&);
	//std::vector<MCTS_Action> GeneratePossibleMoves();

	
	void Search(MCTS_State* intialState);
	void Select();
	void Expand()
	{
		// state.GeneratePossibleActions()

	}
	MCTS_State Simulate()
	{
		
		// Play through player turn and update state
		// Play through enemy turn and update state
	}
	void BackPropogation(MCTS_State* endState);
	
	void Play()
	{
		// check if any moves are possible
			// if possible then check current strategy
				// if exploration
					// choose random action to execute
				// if exploitation
					// choose element with highest score
	}

	
private:
	void SimulateEnemyTurn(MCTS_State* state);
	int searchCount = 0;
	MCTS_State initialState;
	std::vector<MCTS_State*> branches;

};

