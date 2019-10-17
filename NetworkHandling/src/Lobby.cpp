#include "Lobby.h"
#include "PlayerManager.h"
#include <sstream>

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
	std::string str = SerializeRooms();
	player->Send(str.c_str() , str.size(), NetworkProtocol::UDP);
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

std::string Lobby::SerializeRooms()
{
	std::ostringstream oss;
	std::list<Room*>::iterator it;
	oss << "LBY";
	for (it = _rooms.begin(); it != _rooms.end(); it++)
	{
		oss << (*it)->Serialize();
	}
	return oss.str();
}
