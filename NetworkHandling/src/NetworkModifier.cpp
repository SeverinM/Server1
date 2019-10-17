#include "NetworkModifier.h"
#include <cstdlib>

NetworkModifier::NetworkModifier(std::queue<PlayerPacket*>* firstPP, float min, float max, float loss, float random)
{
	_pp = firstPP;
	if (_minLag > _maxLag)
	{
		float temp = _minLag;
		_minLag = _maxLag;
		_maxLag = temp;
	}
	_step = _maxLag - _minLag;
	_lossProbability = loss;
	_probabilityRandom = random;
}

void NetworkModifier::Update(float elapsed)
{
	std::list <std::pair<float, PlayerPacket*>>::iterator it = _bufferLag.begin();
	while (it != _bufferLag.end())
	{
		//Lag delay ended , transfer to true buffer
		it->first -= elapsed;
		if (it->first <= 0)
		{
			_pp->push(it->second);
			_bufferLag.erase(it);
			continue;
		}
		it++;
	}
}

void NetworkModifier::AddPacket(PlayerPacket* pp)
{
	float randomLoss = rand() % 100;
	if (randomLoss < _lossProbability)
	{
		delete pp;
		pp = NULL;
		return;
	}

	if (_minLag == 0 && _maxLag == 0)
	{
		_pp->push(pp);
	}
	else
	{
		float randomLag = (rand() % (int)_step) + _minLag;
		_bufferLag.push_back(std::pair(randomLag, pp));
	}
}