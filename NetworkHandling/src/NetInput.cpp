#include "NetInput.h"
#include <iostream>

void NetInput::Treat(PlayerPacket* packet)
{
	if (packet != nullptr)
	{
		if (packet->content == CONNECT_KEY)
		{
		}
	}
}

NetInput::NetInput(PlayerManager* pM)
{
	_pM = pM;
}