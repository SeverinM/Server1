#include "NetInput.h"
#include <iostream>

void NetInput::Treat(PlayerPacket* packet)
{
	if (packet != nullptr)
	{
		std::cout << packet->content << " : " << packet->protocol <<  std::endl;
	}
}