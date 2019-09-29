#include "Room.h"
#include "PlayerManager.h"

unsigned int Room::_ID = 0;

Room::Room(unsigned int nbPlayers)
{
	_maxPlayer = nbPlayers;
	_id = ++_ID;
	_roomState = new DefaultRoomState();
}

void Room::PlayerLeft(Player * player)
{
	_roomState->PlayerLeft(player);
}

void Room::PlayerEnter(Player* player)
{
	player->SetPlayerState(PlayerState::InRoom);
	_roomState->PlayerEntered(player);
}

bool Room::RequestEnter(Player * player)
{
	return (_maxPlayer > _roomState->GetSize() && player->GetPlayerState() == PlayerState::InLobby);
}