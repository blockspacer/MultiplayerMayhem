#pragma once
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Net 
{
private:
	UdpSocket socket;
	int localPort = 8081;

	int remotePort = 8080;
	IpAddress remoteIp = "127.0.0.1";
public:
	Net();
	~Net();
	void Send();
	string Receive();

	// Temp value
	static bool IsPlayer1;
};