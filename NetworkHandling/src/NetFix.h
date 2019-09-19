#pragma once
#include "SFML/Network.hpp"

using namespace sf;

class NetFix
{
	protected:
		UdpSocket _socket;
		static NetFix* _instance;
		bool _isInit = false;
		int _port;

	public:
		static NetFix* GetInstance();
		inline bool IsInitialized() { return _isInit; }
		void Update();
		void Init(int port = 54000);
		inline IpAddress GetLocalAdress() { return IpAddress::getLocalAddress(); }
		inline IpAddress GetPublicAdress() { return IpAddress::getPublicAddress(); }
};