#include "NetInput.h"
#include <iostream>

void NetInput::Update(double elapsed)
{
	PlayerPacket* packet = _buffer->Pop();
	if (packet != nullptr)
	{
		std::cout << packet->content << std::endl;
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

NetInput::NetInput(PlayerManager* pM, PacketBuffer * buffer)
{
	_pM = pM;
	_buffer = buffer;
}