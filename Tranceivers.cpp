#include "Tranceivers.h"
#include "UserEquipment.h"

// Constructors
Tranceiver::Tranceiver(UserEquipment * newTranceiver, double Y, double X)
{
	this->tranceiverID = newTranceiver->getObjID();
	this->user = newTranceiver;
}

TranceiverList::TranceiverList()
{
	this->limit = 0;
	this->Tranceivers.reserve(this->limit);
}

TranceiverList::TranceiverList(int lim)
{
	this->limit = lim;
	this->Tranceivers.reserve(this->limit);
}

// TODO: Figure out how to redefine operators
Tranceiver & TranceiverList::operator[](int x)
{
	if (x < this->limit && x > 0 && x < (int)this->Tranceivers.size())
	{
		return this->Tranceivers[x];
	}
	else
	{
		return this->Tranceivers[0];
	}
}

bool TranceiverList::operator+(Tranceiver* newTranceiver)
{
	if ((int)this->Tranceivers.size() < limit - 1)
	{
		this->Tranceivers.push_back(*newTranceiver);
		return true;
	}
	else
	{
		return false;
	}

}
