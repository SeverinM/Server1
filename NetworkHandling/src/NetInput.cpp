#include "NetInput.h"
#include <iostream>

void NetInput::Treat(PlayerPacket* packet)
{
	if (packet != nullptr)
	{
		std::cout << packet->content << std::endl;
		if (packet->content == CONNECT_KEY && _lobby.RequestEnter(packet->player))
		{
			packet->player->ChangePlace(&_lobby);
		}
		if (packet->content == CREATE_ROOM)
		{
			Room* rm = _lobby.CreateRoom(2);
			if (rm->RequestEnter(packet->player))
			{
				packet->player->ChangePlace(rm);
			}
		}
	}
}

NetInput::NetInput(PlayerManager* pM)
{
	_pM = pM;
}