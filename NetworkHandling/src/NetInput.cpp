#include "NetInput.h"
#include <iostream>

void NetInput::Treat(PlayerPacket* packet)
{
	if (packet != nullptr)
	{
		std::cout << packet->content << std::endl;
		std::cout << packet->content.size() << std::endl;
	}
}

NetInput::NetInput(PlayerManager* pM)
{
	_pM = pM;
}