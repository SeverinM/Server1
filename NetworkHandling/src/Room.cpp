#include "Room.h"
#include "PlayerManager.h"

unsigned int Room::_ID = 0;

Room::Room(unsigned int nbPlayers)
{
	_maxPlayer = nbPlayers;
	_id = ++_ID;
}

void Room::PlayerLeft(Player * player)
{
	std::list<Player*>::iterator it = std::find(_playersInRoom.begin(), _playersInRoom.end(), player);
	if (it != _playersInRoom.end())
	{
		_playersInRoom.erase(it);
	}
}

void Room::PlayerEnter( Player* player)
{
	std::cout << "Entering room" << std::endl;
	player->SetPlayerState(PlayerState::InRoom);
	_playersInRoom.push_back(player);
}

bool Room::RequestEnter(Player * player)
{
	return (_maxPlayer > _playersInRoom.size() && player->GetPlayerState() == PlayerState::InLobby);
}