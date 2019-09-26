#include "NetInput.h"
#include <iostream>

void NetInput::Treat(PlayerPacket* packet)
{
	if (packet != nullptr)
	{
		std::string protStr = (packet->protocol == NetworkProtocol::TCP ? "TCP" : "UDP");
		std::cout << packet->content << " : " << protStr << " : " << std::endl;
		if (packet->content == CONNECT_KEY)
		{
		}
	}
}