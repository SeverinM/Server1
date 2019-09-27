#pragma once
#include "Utils.h"
#include "Lobby.h"
#include "PlayerManager.h"

class NetInput
{
	public:
		void Treat(PlayerPacket* pp);
		NetInput(PlayerManager* pM);

	protected :
		Lobby _allLobies[3];
		PlayerManager * _pM;
};