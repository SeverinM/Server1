#pragma once
#include "Player.h"

class Player;

class PlayerObservable
{
	public:
		virtual void PlayerLeft(Player plyr) = 0;
};