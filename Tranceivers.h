#pragma once
#include <vector>
class UserEquipment;


class Tranceiver
{
public:
	int tranceiverID;
	double y, x;
	UserEquipment* user;

	Tranceiver(UserEquipment* newTranceiver, double Y, double X);
};

class TranceiverList
{
protected:
	int limit;

public:
	std::vector<Tranceiver> Tranceivers;

	TranceiverList();
	TranceiverList(int lim);

	Tranceiver& operator[](int x);

	bool operator+(Tranceiver* newTranceiver);

};
