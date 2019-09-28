#pragma once
#include "Room.h"
#include <list>
#include "PlayerObservable.h"
#include "Room.h"

class Lobby : public PlayerObservable
{
public:
	void PlayerLeft(unsigned int plyr);
	void AddPlayer(unsigned int plyr);
	Room * CreateRoom(unsigned int nbPlayer);

protected:
	list<unsigned int> _players;
	list<Room*> _rooms;
};