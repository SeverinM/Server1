#pragma once
#include "Player.h"
#include "PlayerObservable.h"

class Room : public PlayerObservable
{
	protected:
		int _maxPlayer;
		Player** _playersInRoom;
};