#include "NetInput.h"
#include <iostream>

void NetInput::Treat(PlayerPacket* packet)
{
	if (packet != nullptr)
	{
		std::cout << packet->content << std::endl;
		if (packet->content == CONNECT_KEY)
		{
			std::cout << "Joining" << std::endl;
			_lobby.AddPlayer(packet->idPlayer);
		}
		if (packet->content == CREATE_ROOM)
		{
			Room* rm = _lobby.CreateRoom(2);
			std::cout << "Room" << std::endl;
			rm->AddPlayer(packet->idPlayer);
		}
	}
}

NetInput::NetInput(PlayerManager* pM)
{
	_pM = pM;
}