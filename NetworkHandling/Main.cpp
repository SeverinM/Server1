#include "src/NetFix.h"
#include "src/NetInput.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "src/Utils.h"

#include "Instance.h"

using namespace s1;

int main()
{
	glfwInit();
	Instance* instance = new Instance(800,600);
	instance->Init("../WorldVisual/src/shader");

	NetFix* nf = NetFix::GetInstance();

	PlayerManager* pM = PlayerManager::GetInstance();
	NetInput* nI = new NetInput(pM);

	nf->Init(DEFAULT_PORT, pM);

	while (!instance->Update(0.1) && !glfwWindowShouldClose(instance->GetWindow()))
	{
		int val = (1.0 / SERVER_FREQUENCY) * 1000.0;
		//std::this_thread::sleep_for(std::chrono::milliseconds(val));
		nf->Update();
		pM->Update(val / (float)1000.0);
		nI->Treat(nf->GetNextPacket());
		nI->Treat(pM->GetNextPacket());
	}

	return 0;
}