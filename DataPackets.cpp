#include <string>
#include <cstdlib>
#include <vector>
#include "DataPackets.h"

// packet constructors
void Packet::operator=(const Packet& p)
{
	this->sender = p.sender;
	this->destination = p.destination;
	this->data = p.data;
}

Packet::Packet()
{
	this->sender = 0;
	this->destination = 0;
	this->data = randomString();
}

Packet::Packet(int sendr, int destin)
{
	this->sender = sendr;
	this->destination = destin;
	this->data = randomString();
}

Packet::Packet(int sendr, int destin, std::string str)
{
	this->sender = sendr;
	this->destination = destin;
	this->data = str;
}

// generates a random string for the packet
std::string Packet::randomString()
{
	const std::string alphaNum = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm`1234567890-=~!@#$%^&*()_+[];',./<>?:{}|";

	std::string randomStr = "";
	int strLen = rand() % 50 + 1;

	int charSelect;
	for (int c = 0; c < strLen; c++)
	{
		charSelect = rand() % (alphaNum.length());
		randomStr += alphaNum[charSelect];
	}
	return randomStr;
}
