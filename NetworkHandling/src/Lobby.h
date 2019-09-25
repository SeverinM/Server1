#pragma once
#include "Room.h"
#include <list>
#include "PlayerObservable.h"

class Lobby : PlayerObservable
{
public:
	void PlayerLeft(Player plyr);
	void AddPlayer(Player* plyr);
};