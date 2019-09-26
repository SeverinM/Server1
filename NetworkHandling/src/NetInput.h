#pragma once
#include "Utils.h"
#include "Lobby.h"

class NetInput
{
	public:
		void Treat(PlayerPacket* pp);

	protected :
		Lobby _allLobies[3];
};