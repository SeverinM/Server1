#include "NetFix.h"
#include "NetInput.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "PacketBuffer.h"

#include "Instance.h"

using namespace s1;

double Consts::deltaTick = 0;
long long Consts::lastTick = 0;

int main()
{
	glfwInit();
	double value = SERVER_FREQUENCY;

	//How long before the next tick
	Consts::deltaTick = (1.0 / value);
	double accumulatedTime = 0;

	PacketBuffer* buffer = new PacketBuffer(10);
	NetFix* nf = new NetFix(buffer);

	PlayerManager* pM = PlayerManager::GetInstance();
	NetInput* nI = new NetInput(pM, buffer);

	nf->Init(DEFAULT_PORT, pM);

	long delta = 0;
	double seconds = 0;
	chrono::time_point<chrono::steady_clock> t1 = chrono::steady_clock::now();
	chrono::time_point<chrono::steady_clock> t2;

	while (true)
	{
		t1 = chrono::steady_clock::now();
		seconds = delta / (double)1000000.0;
		accumulatedTime += seconds;

		//Server tick
		while (accumulatedTime >= Consts::deltaTick)
		{
			Consts::lastTick = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			accumulatedTime -= Consts::deltaTick;
			nI->GetLobby()->Tick();
		}

		//Other updates
		nf->Update();
		pM->Update(seconds);
		nI->Update(seconds);
		buffer->Update(seconds);

		t2 = chrono::steady_clock::now();
		delta = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
	}

	return 0;
}