#pragma once
#include "Utils.h"
#include <queue>
#include <list>

class NetworkModifier
{
	protected:
		std::queue<PlayerPacket*> * _pp;
		std::list <std::pair<float, PlayerPacket*>> _bufferLag;
		int _minLag;
		int _maxLag;
		float _lossProbability;
		float _probabilityRandom;
		float _step;

	public:
		NetworkModifier(std::queue<PlayerPacket*>* firstPP, float min = 0, float max = 0, float loss = 0, float random = 0);
		void Update(float elapsed);
		void AddPacket(PlayerPacket * pp);
};