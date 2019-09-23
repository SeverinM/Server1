#include "src/NetFix.h"
#include "src/NetInput.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main()
{
	NetFix* nf = NetFix::GetInstance();
	NetInput* nI = new NetInput();

	PlayerManager* pM = new PlayerManager();
	nf->Init(54000, pM);

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		nf->Update();
		pM->Update(1);
		nI->Treat(nf->GetNextPacket());
		nI->Treat(pM->GetNextPacket());
	}

	return 0;
}