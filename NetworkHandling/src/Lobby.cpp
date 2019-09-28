#include "Lobby.h"
#include "PlayerManager.h"

void Lobby::PlayerLeft(unsigned int plyr)
{

}

void Lobby::AddPlayer(unsigned int plyr)
{
	_players.push_back(plyr);
	Player* player = PlayerManager::GetInstance()->FindPlayer(plyr);
	if (player != nullptr)
	{
		player->AddObserver(this);
		player->SetPlayerState(PlayerState::InLobby);
	}
}

Room* Lobby::CreateRoom(unsigned int nbPlayer)
{
	Room* rm = new Room(nbPlayer);
	_rooms.push_back(rm);
	return rm;
}
