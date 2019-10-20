#include "PacketBuffer.h"

PacketBuffer::PacketBuffer(unsigned int maxSize)
{
	_size = maxSize;
	_modifier = new NetworkModifier(&_packets, 0, 0, 50, 0);
}

PlayerPacket* PacketBuffer::Pop()
{
	if (_packets.empty())
		return NULL;

	PlayerPacket* packet = _packets.front();
	_packets.pop();
	return packet;
}

void PacketBuffer::Insert(PlayerPacket* packet)
{
	if (_packets.size() < _size)
		_modifier->AddPacket(packet);
}