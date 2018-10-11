#pragma once
#include <string>
#include <vector>

class Packet
{
public:
	int sender;
	int destination;
	std::string data;

	void operator=(const Packet& p);

	Packet();

	Packet(int sendr, int destin);

	Packet(int sendr, int destin, std::string str);

protected:
	std::string randomString();

};

// defines the vector of packets as having the type PacketBundle
typedef std::vector<Packet> PacketBundle;
