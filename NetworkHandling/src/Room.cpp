#include "Room.h"
#include "PlayerManager.h"

unsigned int Room::_ID = 0;

Room::Room(unsigned int nbPlayers)
{
	_maxPlayer = nbPlayers;
	_id = ++_ID;
	_roomState = new VisualRoomState();
	_roomState->Init();
}

void Room::Tick()
{
	if (_roomState->GetIsInit())
	{
		_roomState->Tick();
	}
}

void Room::PlayerLeft(Player * player)
{
	_roomState->PlayerLeft(player);
}

void Room::PlayerEnter(Player* player)
{
	player->SetPlayerState(PlayerState::InRoom);
	_roomState->PlayerEntered(player);
	string ent = "Entered room";
	player->Send(ent.c_str(), ent.size(), NetworkProtocol::UDP);
}

bool Room::RequestEnter(Player * player)
{
	return (_maxPlayer > _roomState->GetSize() && player->GetPlayerState() == PlayerState::InLobby);
}