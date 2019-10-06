#include "Lobby.h"
#include "PlayerManager.h"

void Lobby::PlayerLeft( Player * player)
{
	std::list<Player*>::iterator it = std::find(_allPlayers.begin(), _allPlayers.end(), player);
	if (it != _allPlayers.end())
	{
		_allPlayers.erase(it);
	}
}

void Lobby::PlayerEnter(Player* player)
{
	std::cout << "Entering lobby" << std::endl;
	player->SetPlayerState(PlayerState::InLobby);
	_allPlayers.push_back(player);
	player->Send("Entered lobby", 100, NetworkProtocol::UDP);
}

Room* Lobby::CreateRoom(unsigned int nbPlayer)
{
	Room* rm = new Room(nbPlayer);
	_rooms.push_back(rm);
	return rm;
}

bool Lobby::RequestEnter(Player * player)
{
	return player->GetPlayerState() == PlayerState::InServer;
}

void Lobby::Tick()
{
	list<Room*>::iterator it = _rooms.begin();
	while (it != _rooms.end())
	{
		(*it)->Tick();
		it++;
	}
}
