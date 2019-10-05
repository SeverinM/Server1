#pragma once
#include "Room.h"
#include <list>
#include "PlayerPlace.h"
#include "Room.h"

//Contains a list of room 
class Lobby : public PlayerPlace
{
public:
	void PlayerLeft(Player * player) override;
	void PlayerEnter(Player* player) override;
	bool RequestEnter(Player * player) override;
	Room * CreateRoom(unsigned int nbPlayer);
	void Tick();

protected:
	std::list<Player*> _allPlayers;
	list<Room*> _rooms;
};