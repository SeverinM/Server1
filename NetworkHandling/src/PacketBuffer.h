#pragma once
#include "NetworkModifier.h"

class PacketBuffer
{
	protected:
		unsigned int _size;
		queue<PlayerPacket*> _packets;
		NetworkModifier* _modifier;

	public:
		PacketBuffer(unsigned int maxSize);
		virtual PlayerPacket* Pop();
		virtual void Insert(PlayerPacket * packet);
		inline void Update(float elapsed)
		{
			if (_modifier != NULL)
			{
				_modifier->Update(elapsed);
			}
		}
};