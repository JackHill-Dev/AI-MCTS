#pragma once
#include "Scene.h"
#include "Card.h"
#include <deque>

class CombatScene :
    public Scene
{

public:

    struct tile
    {
		tile() {}
        RenderObject* square = NULL;
        std::pair<float, float> pos;
        bool availiable = true;
        tile* up;
        tile* down;
        tile* right;
        tile* left;
        std::vector<tile*> adjacentTiles;
        
    };

	struct UIStats
	{
		UIStats() {}
		UIText* health;
		UIText* movement;
		UIText* strength;
		UIText* intelligence;
		UIText* agility;
		RenderObject* object;
		UIStats(std::pair<float, float> position, UIText* health, UIText* movement, UIText* strength, UIText* intelligence, UIText* agility, RenderObject* object) : health(health), movement(movement), strength(strength), intelligence(intelligence), agility(agility), object(object)
		{

			float scale = 30;

			object->SetPos(std::make_pair(position.first, position.second));
			object->scale = std::make_pair(0.7, 0.4);
			health->pos = std::make_pair(position.first - 80, position.second);
			health->SetTextScale(scale, scale);
			health->textColor = SDL_Color{178, 34, 34};
			movement->pos = std::make_pair(position.first -40, position.second);
			movement->SetTextScale(scale, scale);
			movement->textColor = SDL_Color{ 31, 30, 29 };
			strength->pos = std::make_pair(position.first, position.second);
			strength->SetTextScale(scale, scale);
			strength->textColor = SDL_Color{ 151, 112, 15 };
			intelligence->pos = std::make_pair(position.first + 40, position.second);
			intelligence->SetTextScale(scale, scale);
			intelligence->textColor = SDL_Color{ 50, 50, 150 };
			agility->pos = std::make_pair(position.first + 80, position.second);
			agility->SetTextScale(scale, scale);
			agility->textColor = SDL_Color{ 0, 100, 0 };
		}
		void SetVisibility(bool visible)
		{
			object->SetVisible(visible);
			health->isVisible = visible;
			movement->isVisible = visible;
			strength->isVisible = visible;
			intelligence->isVisible = visible;
			agility->isVisible = visible;
		}
		void UpdateStats(Character* character)
		{
			auto s = character->GetStats();

			health->text = std::to_string(s.health.first) + "/" + std::to_string(s.health.second);
			movement->text = std::to_string(s.movement.first) + "/" + std::to_string(s.movement.second);
			strength->text = std::to_string(s.strength.first) + "/" + std::to_string(s.strength.second);
			intelligence->text = std::to_string(s.intelligence.first) + "/" + std::to_string(s.intelligence.second);
			agility->text = std::to_string(s.agility.first) + "/" + std::to_string(s.agility.second);
		}

	};

    struct Unit
    {
		Unit() {}
		UIStats visualStats;
		std::vector<tile*> currentPath;
		RenderObject* object;
		RenderObject* profile;
        Character* character;
        bool busy = false;
		tile* occupiedTile;

		void Update()
		{
			visualStats.UpdateStats(character);
		}

		Unit(Character* character, tile* tile, RenderObject* object, RenderObject* profile, UIStats visualStats) : object(object), character(character), occupiedTile(tile), profile(profile), visualStats(visualStats)
		{
			object->SetPos(occupiedTile->pos);
			occupiedTile->availiable = false;
			visualStats.UpdateStats(character);
		}
		bool SetTarget(std::vector<tile*> path)
		{
			occupiedTile->availiable = true;
			occupiedTile = path.back();
			occupiedTile->availiable = false;
			currentPath = path;
			busy = true;
			return false;
		}
		void Move(double dTime)
		{
			if (currentPath.size() > 0)
			{
				std::pair<double, double> target = currentPath.front()->pos;
				double xPos = object->GetPos().first;
				double yPos = object->GetPos().second;
				double yDistance = target.second - object->GetPos().second;
				double xDistance = target.first - object->GetPos().first;

				if (yDistance != 0)
				{
					if (std::abs(yDistance) < 1.f)
						yPos = target.second;

					if (yDistance > 0)
					{
						yPos += dTime * 0.1f;
						object->SetAnim("WalkUp");
					}
					else if (yDistance < 0)
					{
						yPos -= dTime * 0.1f;
						object->SetAnim("WalkDown");
					}
				}
				else
				{
					if (std::abs(xDistance) < 1.f)
					{
						xPos = target.first;
						//object->SetAnim("LookUp");
						//currentPath.pop_front();
						currentPath.erase(currentPath.begin());
					}
					else
					{
						if (xDistance > 0)
						{
							xPos += dTime * 0.1f;
							object->SetAnim("WalkRight");

						}
						else if (xDistance < 0)
						{
							xPos -= dTime * 0.1f;
							object->SetAnim("WalkLeft");

						}
					}
				}
				object->SetPos(std::make_pair(xPos, yPos));

			}
			else
			{
				busy = false;
				object->SetAnim("LookUp");
			}
		}
		
    };

	void Load(std::vector<Character*> enemyTeam, int seed);
	CombatScene() {};
    CombatScene(Interface* objmg);
	virtual ~CombatScene();
    void Update(double dTime, Act act,std::pair<int, int> mouse) override;
	// Public functions and variables for MCTS implementation
	std::deque<Unit> GetPlayerTeam() { return team; }
	std::deque<Unit> GetEnemyTeam() { return enemy; }
	std::vector<Card*> GetPlayerHand() { return playerHand; }
	std::vector<tile*> CalculatePath(tile* start, tile* end);
	double GetDistance(tile* start, tile* end) { return std::abs(std::sqrt(std::pow(end->pos.first - start->pos.first, 2) + std::pow(end->pos.second - start->pos.second, 2))) / 32; }
	bool OutOfRange(Unit* caster, Unit* target,   Card card);
	bool OutOfRange(Unit* caster, Unit* target, const std::pair<Card*, RenderObject*>* card);
	tile mapp[10][10];
	bool playerTurn = false; // Is it the players turn
	CombatScene* Clone() { return new CombatScene(*this); }
private:

	void RunAi();
	void Cast(Unit* caster, Unit* target, const std::pair<Card*, RenderObject*>* card);
	void RemoveUnit(Unit* unit);
	
	std::pair<Card*, RenderObject*> GateEnemyDeckByLevel();


	typedef CombatScene::tile tile;
	typedef CombatScene::Unit Unit;

    std::vector<Character> chars{};
    std::vector<Card*> playerHand{};
	std::vector<Card*> deck;
	std::vector<std::pair<Card*, RenderObject*>> playerhand;
	std::vector<std::pair<Card*, RenderObject*>> enemyHand;

	std::pair<Card*, RenderObject*>* selectedCard = nullptr;
	std::pair<Card*, RenderObject*> hoveredCard;
	std::pair<double, double> centre = { 640,360 };

	std::deque <Unit> team{};
	std::deque <Unit> enemy{};
	std::deque<RenderObject*> hovered;
	
	enum Selection { Team, Enemy, Ground, UICard, Any };
	Selection current = Any;


	const int gridTileLength = 10;
	double fightScene = 0;
	
	
	RenderObject* endTurn;
	RenderObject* pExit;
	Unit* character = nullptr;
	Unit* target;
	
	Mix_Music* pCombat_music;
	Mix_Chunk* pSlash_sfx;
	Mix_Chunk* pMagic_SFX;
	Mix_Chunk* pShoot_SFX;
	Mix_Chunk* pHeal_SFX;
	Mix_Chunk* pButtonClick_SFX;
	Mix_Chunk* pError_SFX;
	
};

