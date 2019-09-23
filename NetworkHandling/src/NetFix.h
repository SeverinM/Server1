#pragma once
#include "SFML/Network.hpp"
#include "PlayerManager.h"
#include <vector>

using namespace sf;

class NetFix
{
	protected:
		UdpSocket _socket;
		TcpListener _listener;
		static NetFix* _instance;
		bool _isInit = false;
		int _port;
		PlayerManager* _manager;

	public:
		static NetFix* GetInstance();
		inline bool IsInitialized() { return _isInit; }
		void Update();
		void Init(int port, PlayerManager * man);
		inline IpAddress GetLocalAdress() { return IpAddress::getLocalAddress(); }
		inline IpAddress GetPublicAdress() { return IpAddress::getPublicAddress(); }
};