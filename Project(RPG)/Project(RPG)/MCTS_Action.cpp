#include "MCTS_Action.h"


MCTS_Move_Action::MCTS_Move_Action(Unit* UnitToMove, Tile* target)
{
	characterToMove = UnitToMove;
	targetTile = target;
}

MCTS_Card_Action::MCTS_Card_Action(Unit* caster,Card* castingCard, Unit* enemeyUnit)
{
	cardToCast = castingCard;
	enemyTarget = enemeyUnit;
	player = caster;
}

void MCTS_Move_Action::Execute()
{
	std::cout << "Movement action" << std::endl;
	std::cout << "move from tile: " << characterToMove->occupiedTile->pos.first << ',' << characterToMove->occupiedTile->pos.second << std::endl;

	characterToMove->occupiedTile->availiable = true;
	characterToMove->occupiedTile = targetTile;
	characterToMove->occupiedTile->availiable = false;

	std::cout << "To tile:" << characterToMove->occupiedTile->pos.first << ',' <<  characterToMove->occupiedTile->pos.second << std::endl;;
}



void MCTS_Card_Action::Execute()
{
	std::cout << "Card Action, " <<  cardToCast->GetCardName() << std::endl;
	std::cout <<  enemyTarget->character->GetStats().health.first << std::endl;
	cardToCast->Cast(player->character, enemyTarget->character);
	std::cout << enemyTarget->character->GetStats().health.first << std::endl;
}

void MCTS_EndTurn_Action::Execute()
{
	std::cout << "END TURN";
	//cs.playerTurn = false;
}


//std::vector<MCTS_Action> MCTS::GeneratePossibleMoves()
//{
//	// Temp vector of actions
//	std::vector<MCTS_Action> possibleMoves;
//
//	std::deque<Unit> playerCurrentParty = CombatScene::GetPlayerTeam();// = initialPlayer.GetParty();
//	std::deque<Card*> playerCurrentDeck = initialPlayer.deck;
//	// loop through current state's party/units
//		// loop through current cards
//			// check if ally unit is within range to use the card and unit has enough resources to use the action
//				// Then add this as a possible action
//		//  if not in range but has resources can ally get within range
//			// loop through all avalible grid positions that are within the unit movement
//				// Simulate moving to the poistion to try and cast card
//					// if can cast then add to possible actions
//					
//	// There will always be the option of ending the turn so add it to the possible actions
//	possibleMoves.push_back(MCTS_EndTurn_Action());
//	// return final list of possible actions
//	return possibleMoves;
//
//	
//}




