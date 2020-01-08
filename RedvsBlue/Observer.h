#pragma once
#include "GameObject.h"
#include "Global.h"

class Observer
{
public:
	//Observer();
	virtual ~Observer() {}
	virtual void onNotify(const GameObject& gameObject, Event event) = 0;
};

