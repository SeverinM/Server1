#pragma once
#include "Room.h"
#include <list>
#include "PlayerObservable.h"
#include "Room.h"

class Lobby : public PlayerObservable
{
public:
	void PlayerLeft(Player plyr);
	void AddPlayer(Player* plyr);

protected:
	list<Player*> _players;
	list<Room*> _rooms;
};