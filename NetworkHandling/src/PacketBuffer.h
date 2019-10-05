#pragma once
#include <queue>
#include "Utils.h"

class PacketBuffer
{
	protected:
		unsigned int _size;
		queue<PlayerPacket*> _packets;

	public:
		PacketBuffer(unsigned int maxSize);
		virtual PlayerPacket* Pop();
		virtual void Insert(PlayerPacket * packet);
};