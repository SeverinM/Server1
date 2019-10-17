#pragma once
#include "Room.h"
#include <list>
#include "PlayerPlace.h"

//Contains a list of room 
class Lobby : public PlayerPlace
{
public:
	void PlayerLeft(Player * player) override;
	void PlayerEnter(Player* player) override;
	bool RequestEnter(Player * player) override;
	void TransmitCommand(Command cmd) override {};
	Room * CreateRoom(unsigned int nbPlayer);
	void Tick();
	std::string SerializeRooms();

protected:
	std::list<Player*> _allPlayers;
	list<Room*> _rooms;
};