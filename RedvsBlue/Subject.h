#pragma once
#include "Observer.h"

class Subject
{
public :
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

private:
	Observer* observers_[MAX_OBSERVERS];
	int numObservers;
};

