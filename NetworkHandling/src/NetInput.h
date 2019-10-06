#pragma once
#include "Utils.h"
#include "Lobby.h"
#include "PlayerManager.h"
#include "PacketBuffer.h"

class NetInput
{
	public:
		void Update(double elapsed);
		Command GenerateCommand(PlayerPacket * packet);
		NetInput(PlayerManager* pM, PacketBuffer * buffer);
		inline Lobby* GetLobby() { return &_lobby; }

	protected :
		Lobby _lobby;
		PlayerManager * _pM;
		PacketBuffer* _buffer;
};