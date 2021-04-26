#include "MCTS.h"
std::mt19937 random_number_engine_mcts(time(0));

int RandomNumberGenerator(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine_mcts);
}

MCTS::MCTS(MCTS_State& initState)
{
	std::cout << "-----------" << std::endl;
	std::cout << "Initial State" << std::endl;
	std::cout << "-----------" << std::endl;
	initialState = initState;

	Search(&initState);
}


void MCTS::Search(MCTS_State* state)
{
	std::cout << "-----------" << std::endl;
	std::cout << "New State" << std::endl;
	std::cout << "-----------" << std::endl;

	if(state->possibleActions.empty())
		state->GeneratePossibleActions();

	// Random policy
	int random =  RandomNumberGenerator(0, state->possibleActions.size() - 1);
	// Simulate that action on state
	auto cardAction = std::find_if(state->possibleActions.begin(), state->possibleActions.end(), [](MCTS_Action* a) { return static_cast<MCTS_Card_Action*>(a) != nullptr; });
	if (cardAction != state->possibleActions.end())
	{
		MCTS_Action* act = *cardAction;
		act->Execute();
	}
	else
		state->possibleActions[random]->Execute();

	state->SimulateEnemyTurn();

	
	MCTS_State*  newState = new MCTS_State(state); 
	// Save the parent state for use in back propogation
	
	++state->timesVisited;
	
	state->nextStates.push_back(newState);

	if (!state->Winner())
	{
		newState->parentState = state;
		++newState->timesVisited;
		++searchCount;
		Search(newState);
	
	}
	else
	{
		if(state->isLeafNode)
			BackPropogation(state);
	}


}

void MCTS::Select()
{
	std::cout << "-----------" << std::endl;
	std::cout << "New Search" << std::endl;
	std::cout << "-----------" << std::endl;

	
	for (int i = 0; i < 200; ++i)
	{
		initialState.ResetInitialState();
		Search(branches[0]);
	}

	MCTS_State play;
	int UCB1 = 0;
	int tempUCB1 = 0;
	// UCB1
	for (auto& b : branches)
	{
		tempUCB1 = 0;
		for (auto& s : b->nextStates)
		{
			tempUCB1 = s->GetUCB1Value();
			if (tempUCB1 > UCB1)
			{
				UCB1 = tempUCB1;
				play = *s;
			}
		}
		
	}


}

void MCTS::BackPropogation(MCTS_State* state)
{
	if (state->parentState != nullptr)
	{
		if(state->enemyTeam[0].character->GetStats().health.first <= 0)
		state->parentState->wins += 1;

		BackPropogation(state->parentState);
	}
	else
		branches.push_back(state);

}


