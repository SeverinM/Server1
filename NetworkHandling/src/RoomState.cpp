#include "RoomState.h"
#include <iostream>

void DefaultRoomState::PlayerEntered(Player* entered)
{
	std::cout << "Entering default state" << std::endl;
	_players.push_back(entered);
}

void DefaultRoomState::PlayerLeft(Player* entered)
{
	std::list<Player*>::iterator it = std::find(_players.begin(), _players.end(), entered);
	if (it != _players.end())
	{
		_players.erase(it);
	}
}

bool DefaultRoomState::UnInit()
{
	return true;
}

bool DefaultRoomState::Init()
{
	return true;
}

void DefaultRoomState::Update(float elapsed)
{

}