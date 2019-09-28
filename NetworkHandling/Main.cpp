#include "src/NetFix.h"
#include "src/NetInput.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main()
{
	NetFix* nf = NetFix::GetInstance();

	PlayerManager* pM = PlayerManager::GetInstance();
	NetInput* nI = new NetInput(pM);

	nf->Init(54000, pM);

	while (true)
	{
		int val = (1.0 / SERVER_FREQUENCY) * 1000.0;
		std::this_thread::sleep_for(std::chrono::milliseconds(val));
		nf->Update();
		pM->Update(val / (float)1000.0);
		nI->Treat(nf->GetNextPacket());
		nI->Treat(pM->GetNextPacket());
	}

	return 0;
}