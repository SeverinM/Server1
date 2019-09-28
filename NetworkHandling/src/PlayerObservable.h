#pragma once
#include "Player.h"

class Player;

class PlayerObservable
{
	public:
		virtual void PlayerLeft(unsigned int plyr) = 0;
};