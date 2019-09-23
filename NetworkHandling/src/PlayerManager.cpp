#pragma once
#include "PlayerManager.h"

using namespace sf;

void PlayerManager::Update(float elapsed)
{
	if (alivesPlayer.size() == 0)
	{
		return;
	}

	std::list<std::pair<TcpSocket*, float>>::iterator it = alivesPlayer.begin();
	for (; it != alivesPlayer.end() ;)
	{
		(*it).second -= elapsed;
		std::cout << (*it).second << std::endl;
		if ((*it).second <= 0)
		{
			TcpSocket* sock = it->first;
			sock->disconnect();
			it = alivesPlayer.erase(it);
			delete sock;
		}
		else
		{
			char data[100];
			std::size_t received;
			if ((*it).first->receive(data, 100, received) == Socket::Done)
			{
				(*it).second = DEFAULT_TIMEOUT;
			}
			++it;
		}
	}
}