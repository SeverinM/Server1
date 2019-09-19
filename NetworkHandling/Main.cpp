#include "src/NetFix.h"
#include <iostream>
#include <string>

int main()
{
	NetFix* nf = NetFix::GetInstance();
	nf->Init();

	std::string a;
	std::cin >> a;

	return 0;
}