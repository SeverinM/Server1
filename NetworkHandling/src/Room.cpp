#include "Room.h"
#include "PlayerManager.h"

unsigned int Room::_ID = 0;

Room::Room(unsigned int nbPlayers)
{
	_maxPlayer = nbPlayers;
	_id = ++_ID;
}

void Room::PlayerLeft(unsigned int plyr)
{

}

void Room::AddPlayer(unsigned int id)
{
	_playersInRoom.push_back(id);
	Player * player = PlayerManager::GetInstance()->FindPlayer(id);
	if (player != nullptr && player->GetPlayerState() == PlayerState::InLobby)
	{
		player->SetPlayerState(PlayerState::InRoom);
	}
	else
	{
		std::cout << "Player not exist or not in lobby" << std::endl;
	}
}