#pragma once
#include "Player.h"

class Player;
class Command;

class PlayerPlace
{
	public:
		virtual void PlayerLeft(Player * player) = 0;
		virtual void PlayerEnter(Player* player) = 0;
		virtual bool RequestEnter(Player* player) = 0;
		virtual void TransmitCommand(Command cmd) = 0;
};