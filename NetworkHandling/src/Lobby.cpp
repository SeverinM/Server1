#include "Lobby.h"

void Lobby::PlayerLeft(Player plyr)
{

}

void Lobby::AddPlayer(Player* plyr)
{
	_players.push_back(plyr);
	plyr->AddObserver(this);
}